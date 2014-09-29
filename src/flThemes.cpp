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
#include "../include/flThemes.h"

flThemes::flThemes()
{
    user = getenv ("USER");
    path = homePathNoFile();
    userThemeName = "cp -f " + path + ".usertheme " + path + ".jwmrc";
    error =" failed please report this bug \n";
}

flThemes::~flThemes()
{
    //dtor
}
bool flThemes::themesExist(){
    struct stat sb;
    int mkdirError = 0;
    std::string userHomePath = homePathNoFile();
    const char* themeDir = "/usr/share/jwm-settings-manager/themes/";
    if (stat(themeDir, &sb) == 0 && S_ISDIR(sb.st_mode)){
        return true;
    }
    else {return false;}
}
bool flThemes::checkForTheme(std::string theme){
    struct stat sb;
    const char* themeName=theme.c_str();
    if (stat(themeName, &sb) == 0 && S_ISDIR(sb.st_mode)){
        return true;
    }
    else {return false;}
}
const char* flThemes::userName(){
    const char* answer = user;
    return user;
}
void flThemes::copier(std::string theme){
    bool existant = themesExist();
    if (existant){
        existant=checkForTheme(theme);
        std::string copyTheme = "cp "+ theme + " " + path +".jwmrc";
        std::cout<<copyTheme;
        if(system(userThemeName.c_str())!=0){
            std::cout<<userThemeName<<error;
        }
        if(system(copyTheme.c_str())!=0){
            std::cout<<copyTheme<<error;
        }
        copyTheme+="~";
        if(system(copyTheme.c_str())!=0){
            std::cout<<copyTheme<<error;
        }
    }
    else {errorJWM("Theme directory doesn't exist, cannot copy\n");}
}
void flThemes::other(const char* themeName){
    std::string theme = std::string(themeName);
    copier(theme);
}
void flThemes::change(const char* themeName){
    bool existant = themesExist();
    if (existant){
        std::string stringTheme = std::string(themeName);
        std::string theme = "/usr/share/jwm-settings-manager/themes/"+ stringTheme + "/" + stringTheme;
        std::string themeTest = "/usr/share/jwm-settings-manager/themes/"+ stringTheme + "/";
        existant = checkForTheme(themeTest);
        if (!existant){
            errorJWM("Theme doesn't exist, cannot get it\n");
            return;
        }
        ///Figure out how to check if a theme is in use in .jwmrc ???
        copier(theme);
    }
    else {errorJWM("Theme directory doesn't exist, cannot change theme\n");}
}
int flThemes::saveAs(const char* filename){
    bool existant = themesExist();
    if (existant){
        if(filename !=NULL||filename !=""){
            std::string copyTheme = "cp "+ path +".jwmrc "+ filename;
            if(system(copyTheme.c_str())!=0){
                std::cout<<copyTheme<<" failed please use a correct path\n";
                return 12;
            }
            std::cout<<copyTheme<<'\n';
            return 0;
        }
    }
    else {errorJWM("Theme directory doesn't exist, cannot copy\n");}
    return 1;
}
void flThemes::userTheme(){
    if(system(userThemeName.c_str())!=0){
        std::cout<<userThemeName<<error;
    }
}

const char* flThemes::getTheme(const char* whichTheme){
    bool existant = themesExist();
    if (existant){
        const char* result;
        std::string theme = whichTheme;
        std::string themeDir ="/usr/share/jwm-settings-manager/themes/" + theme + "/theme.png";
        std::string testDir ="/usr/share/jwm-settings-manager/themes/" + theme + "/";
        existant = checkForTheme(testDir);
        if (!existant){
            errorJWM("Theme doesn't exist, cannot get it\n");
            return "ERROR";
        }
        result = themeDir.c_str();
        return result;
    }
    else {errorJWM("Theme directory doesn't exist, cannot GET THE THEME\n");}
    return "Themes don't exist";
}
