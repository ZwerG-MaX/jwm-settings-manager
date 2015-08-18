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
#include <FL/Fl_Browser.H>
#include "../fltk/jwm-themes.h"
#include "Config.h"
#include "flPanel.h"
#include "flWindow.h"
#include <dirent.h>

class flThemes : public Config
{

    public:
        ///Dynamic themes
        int loadTheme(std::string themePath);
        void checkThemeVersion();
        void updateTheme(Fl_Box * button, Fl_Box * button_icon, Fl_Box *tray, Fl_Box *activeW,Fl_Box *activeW2,Fl_Box *activeW_text, Fl_Box *inactiveW, Fl_Box *inactiveW2,Fl_Box *inactiveW_text,Fl_Box *active_min_button, Fl_Box *active_max_button, Fl_Box *active_close_button, Fl_Box *inactive_min_button, Fl_Box *inactive_max_button, Fl_Box *inactive_close_button,std::string filename);
        void modCurrentTheme(Fl_Box * button, Fl_Box * button_icon, Fl_Box *tray, Fl_Box *activeW,Fl_Box *activeW2,Fl_Box *activeW_text, Fl_Box *inactiveW, Fl_Box *inactiveW2,Fl_Box *inactiveW_text,std::string filename);

        //Multiuse functions to get colors, text, etc... from themes
        std::string getThemeItemText(const char* whichOne);
        unsigned int getThemeItemInt(const char* whichOne, const char* whatToGet,unsigned int &color2);
        unsigned int getThemeItemInt(const char* whichOne, const char* whatToGet);
        unsigned int getTheme2ItemInt(const char * whichElement, const char * whichElement2, const char* whatToGet);
        unsigned int getTheme2ItemInt_secondColor(const char * whichElement, const char * whichElement2, const char* whatToGet);
        const double* convertINTcolor2Double(unsigned int colorToConvert);
        const double* getItemColor(Fl_Box*o);
        bool isSVG(std::string filename);

        //button getters from theme file
        std::string getMaxButton(){return getThemeItemText("ButtonMax");}
        std::string getMaxActiveButton(){return getThemeItemText("ButtonMaxActive");}
        std::string getMinButton(){return getThemeItemText("ButtonMin");}
        std::string getCloseButton(){return getThemeItemText("ButtonClose");}

        ///used by the functions below
        unsigned int getActiveFG(const char* whichElement);
        unsigned int getActiveBG(const char* whichElement);

        //TaskList getters from theme file
        unsigned int getTaskActiveFG(){return getActiveFG("TaskListStyle");}
        unsigned int getTaskActiveBG(){return getActiveBG("TaskListStyle");}
        unsigned int getTaskFG(){return getThemeItemInt("TaskListStyle","Foreground");}
        unsigned int getTaskBG(){return getThemeItemInt("TaskListStyle","Background");}

        //menu getters
        unsigned int getMenuActiveFG(){return getActiveFG("MenuStyle");}
        unsigned int getMenuActiveBG(){return getActiveBG("MenuStyle");}
        unsigned int getMenuFG(){return getThemeItemInt("MenuStyle","Foreground");}
        unsigned int getMenuBG(){return getThemeItemInt("MenuStyle","Background");}

        //panel getters
        unsigned int getPanel(){return getThemeItemInt("TrayStyle","Background");}
        unsigned int getPanelButton(){return getThemeItemInt("TrayButtonStyle","Background");}
        unsigned int getPanelText(){return getThemeItemInt("TrayStyle","Foreground");}
        unsigned int getPanelButtonText(){return getThemeItemInt("TrayButtonStyle","Foreground");}
        std::string getPanelButtonIcon();
        std::string getPanelLabel();

        //window getters
        unsigned int getWindow(unsigned int &color2);
        unsigned int getWindow_secondColor();
        unsigned int getWindowText();
        unsigned int getActiveWindowText();
        unsigned int getActiveWindow();
        unsigned int getActiveWindow2();

        bool themesExist();
        bool oldThemesExist();
        int themeNewStyle();

        //mostly used in the FLTK file
        std::string userThemeDir(){return userThemePATH;};
        std::string sysThemeDir();
        bool checkForTheme(std::string theme);
        int populateThemes(Fl_Browser* o);
        int populateUserThemes(Fl_Browser* o);
        int saveAs(const char* filename);
        void copier(std::string theme);

        //TODO: check these functions and get rid of the unused old ones
        void change(const char* themeName);
        const char* getTheme(const char* whichTheme);
        void userTheme();
        void other(const char* themeName);
        tinyxml2::XMLDocument themeDoc;
        flThemes();
        virtual ~flThemes();
    protected:
        int isOLDjwmrc;
        bool isNewTheme;
        std::string path;
        std::string userThemeName;
        std::string error;
        std::string themePATH;
        std::string mydefaultPath;
        std::string userThemePATH;
        std::string OLDthemePATH;
        std::string themePATH230;
        std::string bash;
    private:
};

#endif // FLTHEMES_H
