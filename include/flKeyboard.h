/*                 Joe's Window Manager Configuration
 *
 * This program configures JWM using tinyxml2 and FLTK
 *
 *         Copyright (C) 2014  Israel <israel@torios.org>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * This has been developed as a part of the ToriOS Project
 * This has been developed by Israel<israel@torios.org>
 *
 *
 * You may redistribute this, but you must keep this comment in place
 * Jesus is my Lord, and if you don't like it feel free to ignore it.
 */

#ifndef FLKEYBOARD_H
#define FLKEYBOARD_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "Config.h"
#include "../fltk/jwm-keyboard.h"

class flKeyboard : public Config
{
    public:
        void getKeys(Fl_Browser *o);
        void addKey(const char * key, const char * shortcut);
        void addKey(const char * keyMod, const char * key, const char * shortcut);
        void deleteKey(std::string keyShortcut);
        void configureKey(std::string keyShortcut, std::string newmod1, std::string newmod2, std::string newmod3, std::string newkey, std::string newaction);
        std::string getMod(std::string keyShortcut);
        std::string getMod1(std::string keyShortcut);
        std::string getMod2(std::string keyShortcut);
        std::string getMod3(std::string keyShortcut);
        std::string getKey(std::string keyShortcut);
        std::string getAction(std::string keyShortcut);
        std::string grabbedKey();
        flKeyboard();
        virtual ~flKeyboard();
    protected:
    private:
};

#endif // FLKEYBOARD_H
