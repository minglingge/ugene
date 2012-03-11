/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2012 UniPro <ugene@unipro.ru>
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

#ifndef _U2_GUI_GTKEYBOARDDRIVER_H_
#define _U2_GUI_GTKEYBOARDDRIVER_H_

#include <map>
#include <U2Core/U2OpStatus.h>

namespace U2 {

class GTKeyboardDriver {
public:
    //
    static void keyPress(U2OpStatus &os, int key);
    static void keyPress(U2OpStatus &os, int key, int modifiers);

    static void keyRelease(U2OpStatus &os, int key);
    static void keyRelease(U2OpStatus &os, int key, int modifiers);

    static void keyClick(U2OpStatus &os, int key);
    static void keyClick(U2OpStatus &os, int key, int modifiers);

    static void keySequence(U2OpStatus &os, QString str);
    static void keySequence(U2OpStatus &os, QString str, int modifiers);

    
    class keys : private std::map<QString, int> {
    public:
        keys();
        int operator [] (QString) const;
    };
    
    static keys key;

    /**
    * Example:
    * GTKeyboardDriver::keyClick(os, 'A'); // print 'a'
    * GTKeyboardDriver::keyClick(os, 'a'); // print 'a'
    *
    * GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["shift"], 'a'); // print 'A'
    * GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["SHIFT"], 'a'); // print 'A'
    * case in ["..."] does not matter
    */
    
protected:
    
};

} //namespace

#endif
