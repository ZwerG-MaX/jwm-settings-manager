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

#ifndef FLICONS_H
#define FLICONS_H

#include "Config.h"
#include "../fltk/jwm-icons.h"

class flIcons : public Config
{
    public:
        void getIcons(Fl_Browser *o);

        ///TODO: JWM needs to support SVG (i.e. recompile Debian package)
        /* or this program needs to convert them to png.
         * also, it would be good to eventually have a browser of directory names
         * That the user could choose.. I.e.
         * Box  then this gets ALL the subdirectories and automatically adds them in
         * There would have to be a 'size' selection, so only 32x32 icons (or whatever)
         * would be shown.
         */

        void addIcons(const char * path);
        void removeIcons(const char * icons);

        flIcons();
        virtual ~flIcons();
    protected:
    private:
};

#endif // FLICONS_H
