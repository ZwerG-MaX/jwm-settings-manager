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
#include <dirent.h>

class flThemes : public Config
{

    public:
        ///Dynamic themes
        int loadTheme(std::string themePath);
        std::string getThemeItemText(const char* whichOne);
        unsigned int getThemeItemInt(const char* whichOne, const char* whatToGet,unsigned int &color2);
        unsigned int getThemeItemInt(const char* whichOne, const char* whatToGet);
        unsigned int getTheme2ItemInt(const char * whichElement, const char * whichElement2, const char* whatToGet,unsigned int &color2);
        void updateTheme(Fl_Box * button, Fl_Box * button_icon, Fl_Box *tray, Fl_Box *activeW,Fl_Box *activeW2,Fl_Box *activeW_text, Fl_Box *inactiveW, Fl_Box *inactiveW2,Fl_Box *inactiveW_text,Fl_Box *active_min_button, Fl_Box *active_max_button, Fl_Box *active_close_button, Fl_Box *inactive_min_button, Fl_Box *inactive_max_button, Fl_Box *inactive_close_button,std::string filename);
        void checkThemeVersion();
        std::string getMaxButton(){return getThemeItemText("ButtonMaxActive");}
        std::string getMinButton(){return getThemeItemText("ButtonMin");}
        std::string getCloseButton(){return getThemeItemText("ButtonClose");}

        unsigned int  getPanel();
        unsigned int  getPanelText();
        unsigned int getPanelButton();
        std::string getPanelButtonIcon();
        unsigned int getPanelButtonText();
        std::string getPanelLabel();
        unsigned int getWindow(unsigned int &color2);
        unsigned int getWindowText();
        unsigned int getActiveWindowText();
        unsigned int getActiveWindow(unsigned int &color2);
        bool themesExist();
        bool oldThemesExist();
        std::string userThemeDir(){return userThemePATH;};
        std::string sysThemeDir();
        bool checkForTheme(std::string theme);
        int populateThemes(Fl_Browser* o);
        int populateUserThemes(Fl_Browser* o);
        int saveAs(const char* filename);
        const char* getTheme(const char* whichTheme);
        void change(const char* themeName);
        void copier(std::string theme);
        void userTheme();
        void other(const char* themeName);
        tinyxml2::XMLDocument themeDoc;
        flThemes();
        virtual ~flThemes();
    protected:
        bool isOLDjwmrc;
        bool isNewTheme;
        std::string path;
        std::string userThemeName;
        std::string error;
        std::string themePATH;
        std::string userThemePATH;
        std::string OLDthemePATH;
        std::string bash;
    private:
};

#endif // FLTHEMES_H
