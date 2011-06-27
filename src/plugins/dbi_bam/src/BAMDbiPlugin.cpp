/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2011 UniPro <ugene@unipro.ru>
 * http://ugene.unipro.ru
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <U2Core/AppContext.h>
#include <U2Core/DbiDocumentFormat.h>
#include <U2Core/DocumentUtils.h>
#include <U2Core/TaskSignalMapper.h>
#include <U2Core/AddDocumentTask.h>
#include <U2Core/TextUtils.h>
#include <U2Core/ProjectModel.h>

#include <U2Gui/OpenViewTask.h>
#include <U2Gui/MainWindow.h>

#include <U2Misc/DialogUtils.h>

#include "Dbi.h"
#include "Exception.h"
#include "ConvertToSQLiteDialog.h"
#include "ConvertToSQLiteTask.h"
#include "BAMDbiPlugin.h"
#include "LoadBamInfoTask.h"


#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtGui/QMainWindow>

namespace U2 {
namespace BAM {

extern "C" Q_DECL_EXPORT Plugin* U2_PLUGIN_INIT_FUNC() {
    BAMDbiPlugin* plug = new BAMDbiPlugin();
    return plug;
}

BAMDbiPlugin::BAMDbiPlugin() : Plugin(tr("BAM format support"), tr("Interface for indexed read-only access to BAM files"))
{
    //Disabled until deciding it's future
    //AppContext::getDocumentFormatRegistry()->registerFormat(new DbiDocumentFormat(DbiFactory::ID, "bam", tr("BAM File"), QStringList("bam")));
    AppContext::getDbiRegistry()->registerDbiFactory(new DbiFactory());

    {
        MainWindow *mainWindow = AppContext::getMainWindow();
        if (NULL != mainWindow) {
            QAction *converterAction = new QAction(tr("Import BAM/SAM File..."), this);
            connect(converterAction, SIGNAL(triggered()), SLOT(sl_converter()));
            mainWindow->getTopLevelMenu(MWMENU_TOOLS)->addAction(converterAction);

            AppContext::getDocumentFormatRegistry()->getImportSupport()->addDocumentImporter(new BAMImporter());
        }
    }
}

void BAMDbiPlugin::sl_converter() {
    try {
        if(!AppContext::getDbiRegistry()->getRegisteredDbiFactories().contains("SQLiteDbi")) {
            throw Exception(tr("SQLite DBI plugin is not loaded"));
        }
        LastOpenDirHelper lod;
        QString fileName = QFileDialog::getOpenFileName(AppContext::getMainWindow()->getQMainWindow(), tr("Open BAM/SAM file"), lod.dir, tr("Assembly Files (*.bam *.sam)"));
        if (!fileName.isEmpty()) {
            lod.url = fileName;
            GUrl sourceUrl(fileName);
            QList<FormatDetectionResult> detectedFormats = DocumentUtils::detectFormat(sourceUrl);
            bool sam = false;
            if (!detectedFormats.isEmpty()) {
                if (detectedFormats.first().format->getFormatId() == BaseDocumentFormats::SAM) {
                    sam = true;
                }
            }
            LoadInfoTask* task = new LoadInfoTask(sourceUrl, sam);
            connect(new TaskSignalMapper(task), SIGNAL(si_taskFinished(Task*)), SLOT(sl_infoLoaded(Task*)));
            AppContext::getTaskScheduler()->registerTopLevelTask(task);
        }
    } catch(const Exception &e) {
        QMessageBox::critical(NULL, tr("Error"), e.getMessage());
    }
}

void BAMDbiPlugin::sl_infoLoaded(Task* task) {
    LoadInfoTask* loadInfoTask = qobject_cast<LoadInfoTask*>(task);
    bool sam = loadInfoTask->isSam();
    if(!loadInfoTask->hasError()) {
        const GUrl& sourceUrl = loadInfoTask->getSourceUrl();
        BAMInfo& bamInfo = loadInfoTask->getInfo();
        ConvertToSQLiteDialog convertDialog(sourceUrl, bamInfo, sam);
        if(QDialog::Accepted == convertDialog.exec()) {
            GUrl destUrl = convertDialog.getDestinationUrl();
            ConvertToSQLiteTask *task = new ConvertToSQLiteTask(sourceUrl, destUrl, loadInfoTask->getInfo(), sam);
            if(convertDialog.addToProject()) {
                connect(new TaskSignalMapper(task), SIGNAL(si_taskFinished(Task*)), SLOT(sl_addDbFileToProject(Task*)));
            }
            AppContext::getTaskScheduler()->registerTopLevelTask(task);
        }
    }
}

void BAMDbiPlugin::sl_addDbFileToProject(Task * task) {
    ConvertToSQLiteTask * convertToBAMTask = qobject_cast<ConvertToSQLiteTask*>(task);
    if(convertToBAMTask == NULL) {
        assert(false);
        return;
    }
    if(convertToBAMTask->hasError() || convertToBAMTask->isCanceled()) {
        return;
    }
    GUrl url = convertToBAMTask->getDestinationUrl();
    assert(!url.isEmpty());
    Project * prj = AppContext::getProject();
    if(prj == NULL) {
        QList<GUrl> list;
        list.append(url);
        AppContext::getTaskScheduler()->registerTopLevelTask(AppContext::getProjectLoader()->openWithProjectTask(list));
        return;
    }
    Document * doc = prj->findDocumentByURL(url);
    if(doc != NULL && doc->isLoaded()) {
        return;
    }
    AddDocumentTask * addTask = NULL;
    if(doc == NULL) {
        IOAdapterFactory * iof = AppContext::getIOAdapterRegistry()->getIOAdapterFactoryById(BaseIOAdapters::url2io(url.getURLString()));
        assert(iof != NULL);
        DocumentFormat * df = AppContext::getDocumentFormatRegistry()->getFormatById("usqlite");
        if(df == NULL) {
            assert(false);
            return;
        }
        doc = new Document(df, iof, url);
        addTask = new AddDocumentTask(doc);
    }
    LoadUnloadedDocumentAndOpenViewTask * openViewTask = new LoadUnloadedDocumentAndOpenViewTask(doc);
    if(addTask != NULL) {
        openViewTask->addSubTask(addTask);
        openViewTask->setMaxParallelSubtasks(1);    
    }
    AppContext::getTaskScheduler()->registerTopLevelTask(openViewTask);
}

//////////////////////////////////////////////////////////////////////////
// BAM importer
BAMImporter::BAMImporter() : DocumentImporter("bam-importer", tr("BAM file import")){
    extensions << "bam";
    importerDescription = tr("BAM files importer is used to convert conventional BAM and SAM files into UGENE database format. Having BAM or SAM file converted into UGENE DB format you get an fast and efficient interface to your data with an option to change the content");
}

FormatDetectionScore BAMImporter::checkData(const QByteArray& rawData, const GUrl& url) {
    QString s;
    bool ok = url.lastFileSuffix().toLower() == "bam" 
                && TextUtils::contains(TextUtils::BINARY, rawData.constData(), rawData.length());
    if (ok) {
        return FormatDetection_VeryHighSimilarity;
    }
    return FormatDetection_NotMatched;
}

DocumentProviderTask* BAMImporter::createImportTask(const FormatDetectionResult& res, bool showWizard) {
    return new BAMImporterTask(res.url, showWizard);
}


BAMImporterTask::BAMImporterTask(const GUrl& url, bool _useGui) 
: DocumentProviderTask(tr("BAM file import: %1").arg(url.fileName()), TaskFlags_NR_FOSCOE)
{
    useGui = _useGui;
    convertTask = NULL;
    loadDocTask = NULL;
    loadInfoTask = new LoadInfoTask(url, false);
    addSubTask(loadInfoTask);

    documentDescription = url.fileName();
}

QList<Task*> BAMImporterTask::onSubTaskFinished(Task* subTask) {
    QList<Task*> res;
    if (loadInfoTask == subTask) {
        ConvertToSQLiteDialog convertDialog(loadInfoTask->getSourceUrl(), loadInfoTask->getInfo(), false);
        convertDialog.hideAddToProjectOption();
        int rc = convertDialog.exec();
        if (rc == QDialog::Accepted) {
            GUrl destUrl = convertDialog.getDestinationUrl();
            convertTask = new ConvertToSQLiteTask(loadInfoTask->getSourceUrl(), destUrl, loadInfoTask->getInfo(), false);
            res << convertTask;
        } else {
            stateInfo.setCanceled(true);
        }
    } else if (convertTask == subTask) {
        loadDocTask = LoadDocumentTask::getDefaultLoadDocTask(convertTask->getDestinationUrl());
        res << loadDocTask;
    } else {
        assert(subTask == loadDocTask);
        resultDocument = loadDocTask->takeDocument();
    }
    return res;
}

} // namespace BAM
} // namespace U2
