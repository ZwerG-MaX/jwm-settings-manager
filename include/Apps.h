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

#ifndef APPS_H
#define APPS_H

#include "Config.h"
#include "flAutostart.h"

class Apps : public Config {

    public:
        //shortcuts
        void addShortcut(const char* icon,  const char * program, const char* popup, int border);
        void insertShortcut(const char* icon, const char * program, const char* popup, int border, tinyxml2::XMLElement* element);
        void insertShortcut(const char* icon, const char * program, const char* popup, int border);
        bool isShortcuts();
        void getShortcuts(Fl_Browser *o);
        void deleteShortcut(const char* shortcut);
        void deleteALLshortcuts();

        //xload
        void addAppXload();
        void deleteAppXload();
        bool xloadLoaded();

        //clock
        void changeClock(std::string style);
        void addClock();
        void deleteClock();
        bool isClock();
        std::string getClock();

        //TaskList
        bool isTaskList();
        void addTaskList();
        void deleteTaskList();

        //Pager
        bool isPager();
        void addPager();
        void deletePager();

        //Dock
        bool isDock();
        void addDock();
        void deleteDock();

        //Shutdown
        bool isShutdown();
        void addShutdown();
        void deleteShutdown();
        void setShutdownImage(const char * icon);

        //Places
        bool isPlaces();
        void addPlaces();
        void deletePlaces();

      //NetworkMonitor
        bool isNetworkMonitor();
        void addNetworkMonitor();
        void deleteNetworkMonitor();

    //Volume
        bool isVolume();
        void addVolume();
        void deleteVolume();

    //Battery
        bool isBattery();
        void addBattery();
        void deleteBattery();

        Apps();
        virtual ~Apps();
    protected:
        const char* volumeiconBin;
        const char* xfcepowerBin;
        bool xfcepower;
        bool volumeiconExists;
        const char* nmapplet;
        const char* wicd;
        bool wicdExists;
        bool nmappletExists;
    private:
};

#endif // APPS_H
