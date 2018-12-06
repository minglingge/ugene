/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2018 UniPro <ugene@unipro.ru>
 * http://ugene.net
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

#ifndef _U2_METAPHLAN2_TASK_H_
#define _U2_METAPHLAN2_TASK_H_

#include <U2Core/ExternalToolRunTask.h>

namespace U2 {

class CalculateSequencesNumberTask;

struct  Metaphlan2TaskSettings {
    Metaphlan2TaskSettings();

    bool isPairedEnd;
    QString inputType;
    QString databaseUrl;
    int numberOfThreads;
    QString analysisType;
    QString taxLevel;
    bool normalizeByMetagenomeSize;
    int presenceThreshold;
    QString bowtie2OutputFile;
    QString outputFile;

    QString bowtie2ExternalToolPath;
    QString tmpDir;
    QString readsUrl;
    QString pairedReadsUrl;
};

class Metaphlan2ClassifyTask : public ExternalToolSupportTask {
    Q_OBJECT
public:
    Metaphlan2ClassifyTask(const Metaphlan2TaskSettings& settings);

    const QString& getBowtie2OutputUrl() const;
    const QString& getOutputUrl() const;

private:
    void prepare() override;
    QList<Task*> onSubTaskFinished(Task* subTask) override;
    QStringList getArguments();

    bool needToCountSequences;
    int sequencesNumber;
    const Metaphlan2TaskSettings settings;
    ExternalToolRunTask* classifyTask;
    CalculateSequencesNumberTask* calculateSequencesNumberTask;
};

}

#endif // _U2_METAPHLAN2_TASK_H_