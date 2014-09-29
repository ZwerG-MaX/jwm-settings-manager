/**       @file Joe's Window Manager Configuration - Panel
 *
 *         @author Israel <israel@torios.org>
 *         @section Copyright (C) 2014
 *         @section LICENSE
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
 * @section DESCRITPTION
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * This has been developed as a part of the ToriOS Project
 * This program configures JWM using tinyxml2 and FLTK
 *
 * You may redistribute this, but you must keep this comment in place
 * Jesus is my Lord, and if you don't like it feel free to ignore it.
 */
#ifndef FLTHEMES_H
#define FLTHEMES_H

#include <sys/types.h>
#include <sys/stat.h>
#include "../fltk/jwm-themes.h"
#include "Config.h"


class flThemes : public Config
{

    public:
        bool themesExist();
        bool checkForTheme(std::string theme);
        int saveAs(const char* filename);
        const char* getTheme(const char* whichTheme);
        void change(const char* themeName);
        void copier(std::string theme);
        void userTheme();
        const char* userName();
        void other(const char* themeName);
        flThemes();
        virtual ~flThemes();
    protected:
        std::string path;
        std::string userThemeName;
        std::string error;
        char* user;
    private:
};

#endif // FLTHEMES_H
