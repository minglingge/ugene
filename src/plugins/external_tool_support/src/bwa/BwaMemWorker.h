/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2020 UniPro <ugene@unipro.ru>
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

#ifndef _U2_BWAMEM_SUPPORT_WORKER_
#define _U2_BWAMEM_SUPPORT_WORKER_

#include "utils/BaseShortReadsAlignerWorker.h"

namespace U2 {

class DnaAssemblyToRefTaskSettings;

namespace LocalWorkflow {

class BwaMemWorker : public BaseShortReadsAlignerWorker {
    Q_OBJECT
public:
    BwaMemWorker(Actor *p);

protected:
    QVariantMap getCustomParameters() const;
    QString getDefaultFileName() const;
    QString getBaseSubdir() const;
    void setGenomeIndex(DnaAssemblyToRefTaskSettings &settings);
    QString getAlignerSubdir() const;
};    // BwaMemWorker

class BwaMemWorkerFactory : public BaseShortReadsAlignerWorkerFactory {
public:
    static const QString ACTOR_ID;

    BwaMemWorkerFactory()
        : BaseShortReadsAlignerWorkerFactory(ACTOR_ID) {
    }
    static void init();
    virtual Worker *createWorker(Actor *a);
};    // BwaMemWorkerFactory

}    // namespace LocalWorkflow
}    // namespace U2

#endif    // _U2_BWAMEM_SUPPORT_WORKER_
