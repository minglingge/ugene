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

#include <cctype>
#include "GTKeyboardDriver.h"

#if defined __linux__
    #define XK_LATIN1      // for latin symbol
    #define XK_MISCELLANY  // for action keys
    #include <X11/keysymdef.h>
    #include <X11/extensions/XTest.h>
#endif

namespace HI {

#if defined __linux__

#define GT_CLASS_NAME "GTKeyboardDriverLinux"

#define GT_METHOD_NAME "keyPress"
void GTKeyboardDriver::keyPress(GUITestOpStatus &os, char key, Qt::KeyboardModifier modifiers)
{
    GT_CHECK_NO_MESSAGE(key != 0, "key = 0");

    QByteArray display_name = qgetenv("DISPLAY");
    GT_CHECK_NO_MESSAGE(!display_name.isEmpty(), "Environment variable \"DISPLAY\" not found");

    Display *display = XOpenDisplay(display_name.constData());
    GT_CHECK_NO_MESSAGE(display != 0, "display is NULL");

    QList<Qt::Key> modifierKeys = modifiersToKeys(modifiers);
    foreach (Qt::Key mod, modifierKeys) {
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[mod]), 1, 0);
    }

    switch(key) {
    case '\n':
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Enter]), 1, 0);
        break;
    case '_':
        key = '-';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case '<':
        key = ',';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case '>':
        key = '.';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case '(':
        key = '9';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case '$':
        key = '4';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case '#':
        key = '3';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case ')':
        key = '0';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case ':':
        key = ';';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case '*':
        key = '8';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case '\"':
        key = '\'';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case '@':
        key = '2';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case '%':
        key = '5';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case '^':
        key = '6';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case '&':
        key = '7';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case '+':
        key = '=';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case '{':
        key = '[';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case '}':
        key = ']';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case '|':
        key = '\\';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    case '!':
        key = '1';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 1, 0);
        break;
    }

    XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 1, 0);
    XFlush(display);

    XCloseDisplay(display);
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "keyRelease"
void GTKeyboardDriver::keyRelease(GUITestOpStatus &os, char key, Qt::KeyboardModifier modifiers)
{
    GT_CHECK_NO_MESSAGE(key != 0, "key = ");

    QByteArray display_name = qgetenv("DISPLAY");
    GT_CHECK_NO_MESSAGE(!display_name.isEmpty(), "Environment variable \"DISPLAY\" not found");

    Display *display = XOpenDisplay(display_name.constData());
    GT_CHECK_NO_MESSAGE(display != 0, "display is NULL");

    switch(key) {
    case '\n':
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Enter]), 0, 0);
        break;
    case '_':
        key = '-';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;

    case '<':
        key = ',';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;

    case '>':
        key = '.';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;

    case '(':
        key = '9';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;

    case '$':
        key = '4';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;

    case '#':
        key = '3';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;

    case ')':
        key = '0';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;

    case ':':
        key = ';';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;

    case '*':
        key = '8';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;

    case '\"':
        key = '\'';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;
    case '@':
        key = '2';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;
    case '%':
        key = '5';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;
    case '^':
        key = '6';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;
    case '&':
        key = '7';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;
    case '+':
        key = '=';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;
    case '{':
        key = '[';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;
    case '}':
        key = ']';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;
    case '|':
        key = '\\';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;
    case '!':
        key = '1';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[Qt::Key_Shift]), 0, 0);
        break;

    default:
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
    }

    QList<Qt::Key> modifierKeys = modifiersToKeys(modifiers);
    foreach (Qt::Key mod, modifierKeys) {
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[mod]), 0, 0);
    }
    XFlush(display);

    XCloseDisplay(display);
}
#undef GT_METHOD_NAME

void GTKeyboardDriver::keyPress(GUITestOpStatus &os, Qt::Key key, Qt::KeyboardModifier modifiers){
    modifiersToKeys(modifiers);
    QByteArray display_name = qgetenv("DISPLAY");
    //GT_CHECK_NO_MESSAGE(!display_name.isEmpty(), "Environment variable \"DISPLAY\" not found");

    Display *display = XOpenDisplay(display_name.constData());
    //GT_CHECK_NO_MESSAGE(display != 0, "display is NULL");

    QList<Qt::Key> modifierKeys = modifiersToKeys(modifiers);
    foreach (Qt::Key mod, modifierKeys) {
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[mod]), 1, 0);
    }

    XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[key]), 1, 0);
    XFlush(display);

    XCloseDisplay(display);
}

void GTKeyboardDriver::keyRelease(GUITestOpStatus &os, Qt::Key key, Qt::KeyboardModifier modifiers){
    QByteArray display_name = qgetenv("DISPLAY");
    //GT_CHECK_NO_MESSAGE(!display_name.isEmpty(), "Environment variable \"DISPLAY\" not found");

    Display *display = XOpenDisplay(display_name.constData());
    //GT_CHECK_NO_MESSAGE(display != 0, "display is NULL");

    XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[key]), 0, 0);
    QList<Qt::Key> modifierKeys = modifiersToKeys(modifiers);
    foreach (Qt::Key mod, modifierKeys) {
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key[mod]), 0, 0);
    }
    XFlush(display);

    XCloseDisplay(display);
}

GTKeyboardDriver::keys::keys()
{
    ADD_KEY(Qt::Key_Backspace, XK_BackSpace);
    ADD_KEY(Qt::Key_Tab, XK_Tab);
    ADD_KEY(Qt::Key_Enter, XK_Return);
    ADD_KEY(Qt::Key_Shift, XK_Shift_L);
    ADD_KEY(Qt::Key_Control, XK_Control_L);
    ADD_KEY(Qt::Key_Alt, XK_Alt_L);
    ADD_KEY(Qt::Key_Escape, XK_Escape);
    ADD_KEY(Qt::Key_Space, XK_space);
    ADD_KEY(Qt::Key_Left, XK_Left);
    ADD_KEY(Qt::Key_Up, XK_Up);
    ADD_KEY(Qt::Key_Right, XK_Right);
    ADD_KEY(Qt::Key_Down, XK_Down);
    ADD_KEY(Qt::Key_Insert, XK_Insert);
    ADD_KEY(Qt::Key_Delete, XK_Delete);
    ADD_KEY(Qt::Key_Home, XK_Home);
    ADD_KEY(Qt::Key_End, XK_End);
    ADD_KEY(Qt::Key_PageUp, XK_Page_Up);
    ADD_KEY(Qt::Key_PageDown, XK_Page_Down);

// feel free to add other keys
// macro XK_* defined in X11/keysymdef.h
}

#undef GT_CLASS_NAME

#endif

} //namespace
