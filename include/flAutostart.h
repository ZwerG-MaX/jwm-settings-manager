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

#ifndef FLAUTOSTART_H
#define FLAUTOSTART_H

#include "../fltk/jwm-autostart.h"
#include "Config.h"

class flAutostart : public Config
{
    public:
        //get
        void getAutostart(Fl_Browser *o);

        /*

        //add
        void addAutostart(const char * program);

        //remove
        void removeAutostart(const char * program);
        */

        //rox
        void useROX(bool rox);

        flAutostart();
        virtual ~flAutostart();
    protected:
    private:
};

#endif // FLAUTOSTART_H
