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

#include <QTabWidget>
#include <QWebElement>
#include <QWebFrame>
#include <QWebView>

#include "api/GTWebView.h"
#include "primitives/GTWidget.h"

#include "GTUtilsDashboard.h"

namespace U2 {

#define GT_CLASS_NAME "GTUtilsDashboard"
QMap<QString, GTUtilsDashboard::Tabs> GTUtilsDashboard::initTabMap(){
    QMap<QString, GTUtilsDashboard::Tabs> result;
    result.insert("Overview", GTUtilsDashboard::Overview);
    result.insert("Input", GTUtilsDashboard::Input);
    result.insert("External Tools", GTUtilsDashboard::ExternalTools);
    return result;
}

const QMap<QString, GTUtilsDashboard::Tabs> GTUtilsDashboard::tabMap = initTabMap();

QWebView* GTUtilsDashboard::getDashboard(U2OpStatus &os){
    return GTWidget::findExactWidget<QWebView*>(os, "Dashboard");
}

QTabWidget* GTUtilsDashboard::getTabWidget(U2OpStatus &os){
    return GTWidget::findExactWidget<QTabWidget*>(os, "WorkflowTabView");
}

QWebElement GTUtilsDashboard::findElement(U2OpStatus &os, QString text, QString tag, bool exactMatch){
    return GTWebView::findElement(os, getDashboard(os), text, tag, exactMatch);
}

QWebElement GTUtilsDashboard::findTreeElement(U2OpStatus &os, QString text){
    return GTWebView::findTreeElement(os, getDashboard(os), text);
}

QWebElement GTUtilsDashboard::findContextMenuElement(U2OpStatus &os, QString text){
    return GTWebView::findContextMenuElement(os, getDashboard(os), text);
}

void GTUtilsDashboard::click(U2OpStatus &os, QWebElement el, Qt::MouseButton button){
    GTWebView::click(os, getDashboard(os), el, button);
}

bool GTUtilsDashboard::areThereProblems(U2OpStatus &os) {
    openTab(os, Overview);
    return GTWebView::doesElementExist(os, getDashboard(os), "Problems", "DIV", true);
}

#define GT_METHOD_NAME "openTab"
void GTUtilsDashboard::openTab(U2OpStatus &os, Tabs tab){
    QWebElement el = GTWebView::findElement(os, getDashboard(os), tabMap.key(tab), "A");
    GTWebView::click(os, getDashboard(os), el);
}

#undef GT_METHOD_NAME

#undef GT_CLASS_NAME
}

