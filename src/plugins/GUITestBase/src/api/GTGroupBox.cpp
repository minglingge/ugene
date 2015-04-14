/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2015 UniPro <ugene@unipro.ru>
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

#include <QStyle>
#include <QStyleOption>

#include "GTGroupBox.h"
#include "GTWidget.h"

namespace U2 {

#define GT_CLASS_NAME "GTGroupBox"

#define GT_METHOD_NAME "setChecked"
void GTGroupBox::setChecked(U2OpStatus &os, QGroupBox *groupBox, bool checked) {
    GT_CHECK(groupBox != NULL, "QGroupBox is NULL");

    CHECK(groupBox->isChecked() != checked, );

    GT_CHECK(groupBox->isEnabled(), "QGroupBox is disabled");

    const QRect checkBoxRect = getCheckBoxRect(groupBox);
    const QPoint offset(5, checkBoxRect.height() / 2);
    GTWidget::click(os, groupBox, Qt::LeftButton, checkBoxRect.center() + offset);
    GTGlobals::sleep(100);

    GT_CHECK(checked == groupBox->isChecked(), "Can't set a new state");
}
#undef GT_METHOD_NAME

QRect GTGroupBox::getCheckBoxRect(QGroupBox *groupBox) {
    QStyleOptionGroupBox options;
    return groupBox->style()->subControlRect(QStyle::CC_GroupBox, &options, QStyle::SC_GroupBoxCheckBox);
}

#undef GT_CLASS_NAME

}   // namespace U2