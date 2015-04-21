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

#include <time.h>  //Clock
#include <stdio.h> //Clock puts

#include <FL/Fl_Browser.H>
#include "Config.h"
#include "flAutostart.h"

class Apps : public Config {

    public:
        //shortcuts
        void addShortcut(const char* icon,  const char * program, const char* popup, int border);
        std::string desktopName(std::string filename);
        std::string desktopIcon(std::string filename);
        bool isExec(const char* text){return compared("exec:",text);}
        bool isRoot(const char* text){return compared("root:",text);}
        bool compared(const char* something, const char* text);
        bool isShortcuts();
        void getShortcuts(Fl_Browser *o);
        void deleteShortcut(std::string shortcut);
        void deleteALLshortcuts();
        void populate(Fl_Browser* o);
        void deletePanelItem(std::string whichItem);
        //xload
        bool xloadLoaded(){ return isTrayElement("Swallow","xload");}
        void deleteAppXload();
        void addAppXload();

        //clock
        ///Clock browser
        void populateClocks(Fl_Browser *o);
        ///Default clock
        void addClock(){addAPP("Clock","format","%a, %e %b %l:%M %p","xclock");} ///TODO add clock to jsm file and add a configurer...
        ///Delete clock for current panel
        void deleteClock(){deleteAPP("Clock");}
        bool isClock(){return isAPP("Clock" );}
        ///Change clock to a predefined style or user input
        void changeClock(std::string style);
        void changeClock(std::string style, std::string program);
        std::string getClock(const char* timeString);
        std::string getClock();
        std::string getClockProgram();

//---------------------------------------------  TaskList (Running App list) ----------------------------------------------
    bool isTaskList(){return isAPP("TaskList" );}
    void addTaskList(){addAPP("TaskList","maxwidth","256");}
    void deleteTaskList(){deleteAPP("TaskList");}
//---------------------------------------------  Pager (Desktop Switcher)----------------------------------------------
    bool isPager(){return isAPP("Pager");}
    void addPager(){addAPP("Pager");}
    void deletePager(){deleteAPP("Pager");}
//---------------------------------------------  Dock (Indicators) ----------------------------------------------
    bool isDock(){return isAPP("Dock");}
    void addDock(){addAPP("Dock");}
    void deleteDock(){deleteAPP("Dock");}
    void getIndicators(Fl_Browser *o);
        //Shutdown
        bool isShutdown(){return isMenu(9);}
        void addShutdown();
        void deleteShutdown();
        void setShutdownImage(const char * icon);

        //Places
        bool isPlaces(){return isMenu(7);}
        void addPlaces();
        void deletePlaces();

        //App Menu
        bool isAppMenu(){return isMenu(5);}
        void addAppMenu();
        void deleteAppMenu();

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

        bool isTrayElement(const char* element, std::string text);
        bool isAPP(const char* app);
        void addAPP(const char* app);
        void addAPP(const char* app, const char* attribute, const char* value);
        void addAPP(const char* app, const char* attribute, const char* value, const char* newText);
        void deleteAPP(const char* app);

        Apps();
        virtual ~Apps();
    protected:
        const char* volumeiconBin;
        const char* xfcepowerBin;
        const char* sdeskPowerBin;
        const char* sdeskPowerPlugin;
        bool xfcepower;
        bool sdeskpower;
        bool volumeiconExists;
        const char* nmapplet;
        const char* wicd;
        bool wicdExists;
        bool nmappletExists;
    private:
};

#endif // APPS_H
