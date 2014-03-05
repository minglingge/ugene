/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2014 UniPro <ugene@unipro.ru>
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

#ifndef _U2_GT_CHECKBOX_H_
#define _U2_GT_CHECKBOX_H_

#include "api/GTGlobals.h"
#if (QT_VERSION < 0x050000) //Qt 5
#include <QtGui/QCheckBox>
#else
#include <QtWidgets/QCheckBox>
#endif

namespace U2 {

class GTCheckBox {
public:
    // fails if the comboBox is NULL or can't set checkbox i.e. it's not enabled
    static void setChecked(U2OpStatus& os, QCheckBox *checkBox, bool checked = true);
};

}
#endif // _U2_GT_CHECKBOX_H_
