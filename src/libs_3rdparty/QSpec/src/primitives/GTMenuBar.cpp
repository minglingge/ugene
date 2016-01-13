/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2016 UniPro <ugene@unipro.ru>
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

#include "drivers/GTMouseDriver.h"
#include "primitives/GTMenuBar.h"

namespace HI {
#define GT_CLASS_NAME "GTMenuBar"

#define GT_METHOD_NAME "clickCornerMenu"
void GTMenuBar::clickCornerMenu(GUITestOpStatus &os, QMenuBar* mBar, GTGlobals::WindowAction action) {

    GT_CHECK(mBar != NULL, "QMenuBar is NULL");
    QWidget* cWidget = mBar->cornerWidget();
    GT_CHECK(cWidget != NULL, "Corner widget is NULL");
    QRect r = cWidget->rect();

    int num = (int)action;
    GT_CHECK(num>=0 && num<(int)GTGlobals::WindowActionCount, "action is not GTGlobals::WindowAction");

    GT_CHECK((int)GTGlobals::WindowActionCount != 0, "GTGlobals::WindowActionCount == 0");
    int oneWidth = r.width()/(int)GTGlobals::WindowActionCount;

    QPoint need((num+1)*oneWidth - oneWidth/2, r.height()/2);
    QPoint p = cWidget->mapToGlobal(need);

    GTMouseDriver::moveTo(os, p);
    GTGlobals::sleep(200);
    GTMouseDriver::click(os);
    GTGlobals::sleep(500);
}
#undef GT_METHOD_NAME

#undef GT_CLASS_NAME

}
