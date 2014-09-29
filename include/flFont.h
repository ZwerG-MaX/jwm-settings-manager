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
#ifndef FLFONT_H
#define FLFONT_H
#include "flPanel.h"
#include "flWindow.h"
#include "../fltk/jwm-fonts.h"
#include "Config.h"
#include <fontconfig/fontconfig.h>

class flFont : public Config
{
    public:
        //font name
        std::string getFontName(const char* whichElement);
        void setFontName(const char* name, const char* whichElement);
        std::string fontTest(const char* font);
        void missingFont(const char* whichElement);

        void fontconfigLIST(Fl_Browser *o);
        //Config options
        bool getAntialias(const char* whichElement);

        //Color
        void setFontColor(const double* rgb,const char* whichElement);
        unsigned int getFontColor(const char *element);

        //SIZE
        unsigned int getFontSize(const char* whichElement);
        void setSize(unsigned int &fontSize,const char* whichElement);

        ///WINDOW
        void setWindowFontColor(const double* rgb,const char* whichElement);
        unsigned int getWindowFontColor(const char *element);

        flFont();
        virtual ~flFont();
    protected:
    private:
};

#endif // FLFONT_H
