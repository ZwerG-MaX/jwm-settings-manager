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

/*Version 0.005*/

/*Project Includes*/
//JWM config stuff
#include "../include/flPanel.h"
#include "../include/flDesktop.h"
#include "../include/flWindow.h"
#include "../include/flKeyboard.h"
#include "../include/flAutostart.h"
#include "../include/flMouse.h"
#include "../include/Config.h"

//main UI

#include "../include/ui.h"
#include "../fltk/jwm-panel.h"
#include "../fltk/jwm-autostart.h"
#include "../fltk/jwm-keyboard.h"
#include "../fltk/jwm-desktop.h"
#include "../fltk/jwm-window.h"
#include "../fltk/jwm-mouse.h"
#include "../fltk/jwm-themes.h"
#include "../fltk/jwm-icons.h"

//For argc argv stuff
#include <iostream>
#include <iomanip>
#include <string>
void showHelp();

int main(int argc, char *argv[]){
    //make the UI
    UI ux;
    //integers for searching the argv
    std::string command;
    if(argc>0){
        for(int i=1;i<argc;++i){
            command=argv[i];
            for(int i=0;i<argc;i++){
                if((command.compare("--help")==0)||(command.compare("-h")==0)){
                    showHelp();
                    return 0;
                }
                else if((command.compare("--panel")==0)||(command.compare("-p")==0)){
                    ux.showPanel();
                    return 0;
                }
                else if((command.compare("--window")==0)||(command.compare("-w")==0)){
                    ux.showWindow();
                    return 0;
                }
                else if((command.compare("--desktop")==0)||(command.compare("-d")==0)){
                    ux.showDesktop();
                    return 0;
                }
                else if((command.compare("--autostart")==0)||(command.compare("-a")==0)){
                    ux.showAutostart();
                    return 0;
                }
                else if((command.compare("--font")==0)||(command.compare("-f")==0)){
                    ux.showFonts();
                    return 0;
                }
                else if((command.compare("--icons")==0)||(command.compare("-i")==0)){
                    ux.showIcons();
                    return 0;
                }
                else if((command.compare("--keyboard")==0)||(command.compare("-k")==0)){
                    ux.showKeyboard();
                    return 0;
                }
                else if((command.compare("--mouse")==0)||(command.compare("-m")==0)){
                    ux.showMouse();
                    return 0;
                }
                else if((command.compare("--themes")==0)||(command.compare("-t")==0)){
                    ux.showThemes();
                    return 0;
                }
                else if((command.compare("--recover")==0)||(command.compare("-r")==0)){
                    Config config;
                    config.recover();
                    return 0;
                }
                else if(command == "--halt"){
                    ux.jwmShutdown();
                    return 0;
                }
                else {
                    std::cout<< "Invalid command";
                    showHelp();
                    return 0;
                }
            }
        }
    }

    //What is this for again??
    Fl::visual(FL_RGB);

    Config config;
    config.checkFiles();
    config.load();
    config.saveChangesTemp();

    ux.showSettings();
    return 0;
}


void showHelp(){
    std::cout << "Usage: jwm-settings-manager [Option]\n\n"
        <<"jwm-settings-manager will open the Main settings screen if no options are supplied\n\n"
        <<"Options:\n"
        <<" -a --autostart   show autostart settings\n"
        <<" -d --desktop     show desktop settings\n"
        <<" -f --font        show font settings\n"
        <<" -h --help        show this listing\n"
        <<" -i --icons       show icon settings\n"
        <<" -k --keyboard    show keyboard settings\n"
        <<" -m --mouse       show mouse settings\n"
        <<" -p --panel       show panel settings\n"
        <<" -t --themes      show theme settings\n"
        <<" -w --window      show window settings\n"
        <<" -r --recover     recover settings file\n"
        <<" GUI ONLY OPTION\n"
        <<"  --halt           show shutdown menu\n"
        << std::endl;
}
