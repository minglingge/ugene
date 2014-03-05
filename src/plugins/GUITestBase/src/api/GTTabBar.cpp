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

#include "GTTabBar.h"
#include "GTWidget.h"
#include "GTMouseDriver.h"
#include "GTKeyboardDriver.h"

#if (QT_VERSION < 0x050000) //Qt 5
#include <QtGui/QToolButton>
#else
#include <QtWidgets/QToolButton>
#endif

namespace U2 {

#define GT_CLASS_NAME "GTTabBar"

#define GT_METHOD_NAME "setCurrentIndex"
void GTTabBar::setCurrentIndex(U2OpStatus& os, QTabBar *tabBar, int index) {

    GT_CHECK(tabBar != NULL, "QTabWidget* == NULL");

    if(tabBar->currentIndex() == index){
        return;
    }

    int tabsCount = tabBar->count();
    GT_CHECK(index>=0 && index<tabsCount, "invalid index");

    // TODO: set index by mouse/keyboard
    tabBar->setCurrentIndex(index);
    GTGlobals::sleep();

    int currIndex = tabBar->currentIndex();
    GT_CHECK(currIndex == index, "Can't set index");
}
#undef GT_METHOD_NAME

#undef GT_CLASS_NAME

}
