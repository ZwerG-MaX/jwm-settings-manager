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
        void addButton(const char* icon,  const char * program, const char* popup, int border);
        std::string desktopName(std::string filename);
        std::string desktopIcon(std::string filename);
        //desktopExec is in Config
        //comparedColon is also in Config
        bool isExec(const char* text){return comparedColon("exec:",text);}
        bool isRoot(const char* text){return comparedColon("root:",text);}

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

//----------------------------------------- Clock --------------------------------
        //clock menu
        void createClockMenu(std::string thisClockMenu);
        const char* clockROOT;
        char clockCHAR;
        ///Clock browser
        void populateClocks(Fl_Browser *o);
        ///Default clock
        void addClock(); ///TODO add clock to jsm file and add a configurer...
        ///Delete clock for current panel
        void deleteClock(){deleteAPP("Clock");}
        bool isClock(){return isAPP("Clock" );}
        ///Change clock to a predefined style or user input
        void changeClock(std::string style);
        void changeClock(std::string style, std::string program);
        void setClockProgram(const char* program);
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
        /* Menu functions IN Config
        labelMenu
        isMenu
        addMenu
        deleteMenu
        getLabelMenu
        getImageMenu
        setImageMenu
        */

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

    //Menu
        const char* menuROOT;
        void removeMenuItem(Fl_Browser *elementName, Fl_Browser *elementText);
        int getMenus(Fl_Browser *menuBrowser);
        void ConfigMenuItem(Fl_Browser *elementName,
                            Fl_Browser *elementText,
                            Fl_Input *itemLabel,
                            Fl_Input *itemIcon,
                            Fl_Input *itemProgram,
                            Fl_Check_Button *itemCheck);

        int addMenuItem(Fl_Browser *menuElement,
                    Fl_Browser *menuElementText,
                    Fl_Input *add_label,
                    Fl_Input *add_icon,
                    Fl_Input *add_input,
                    Fl_Check_Button *add_button,
                    std::string whichElement);

        int createMenuItem(std::string whichElement, std::string whichMenu, Fl_Browser *menuElement,Fl_Browser *menuElementText);
        int createMenuItem(std::string whichElement, std::string whichMenu, Fl_Browser *menuElement,Fl_Browser *menuElementText, std::string text);
        int createMenu(const char* whichElement, Fl_Browser *menuElement,Fl_Browser *menuElementText);
        int removeMenu(const char* whichElement);
        void getMenuItems(Fl_Browser *elementName, const char* rootmenu, Fl_Browser *elementText);
        int setMenuAttribute(const char* whichElement, const char* attribute, std::string value, const char* rootmenu);
        int setMenuText(const char* whichElement, const char* text, const char* rootmenu, const char* oldtext);
        void listMenus(Fl_Browser *list_browser);
        void getLabel(Fl_Output* menulabel,const char* menu);

    //General
        bool isTrayElement(const char* element, std::string text);
        bool isAPP(const char* app);
        void addAPP(const char* app);
        void addAPP(const char* app, const char* attribute, const char* value);
        void addAPP(const char* app, const char* attribute, const char* value, const char* newText);
        void deleteAPP(const char* app);

        Apps();
        virtual ~Apps();
    protected:
        //battery apps
        const char* xfcepowerBin;
        const char* sdeskPowerBin;
        const char* sdeskPowerPlugin;
        bool xfcepower;
        bool sdeskpower;

        //volume apps
        const char* volumeiconBin;
        const char* gnomeVolume;
        bool volumeiconExists;
        bool gnomeVolumeExists;

        //network apps
        const char* nmapplet;
        const char* wicd;
        const char* wicd_tray;
        bool wicdExists;
        bool nmappletExists;

    private:
};

#endif // APPS_H
