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
    int dash, dash1;
    int help,panel,window,desktop,autostart,font,icons,keyboard,mouse,themes,recover,halt;
    int h,p,w,d,a,f,i,k,m,t,r;
    std::string command[argc];
    if(command !=NULL){
        for(int i=0;i<argc;i++){
            command[i]=argv[i];
            for(int i=0;i<argc;i++){
                /*
                dash1=command[i].find("-",0);
                if(dash1!=std::string::npos){
                    h = command[i].find("h", dash1 + 1);
                    p = command[i].find("p", dash1 + 1);
                    w = command[i].find("w", dash1 + 1);
                    d = command[i].find("d", dash1 + 1);
                    a = command[i].find("a", dash1 + 1);
                    f = command[i].find("f", dash1 + 1);
                    i = command[i].find("i", dash1 + 1);
                    k = command[i].find("k", dash1 + 1);
                    m = command[i].find("m", dash1 + 1);
                    t = command[i].find("t", dash1 + 1);
                    r = command[i].find("r", dash1 + 1);
                    if(h!=std::string::npos){
                        showHelp();
                        return 0;
                    }
                    else if(p!=std::string::npos){
                        ux.showPanel();
                        return 0;
                    }
                    else if(w!=std::string::npos){
                        ux.showWindow();
                        return 0;
                    }
                    else if(d!=std::string::npos){
                        ux.showDesktop();
                        return 0;
                    }
                    else if(a!=std::string::npos){
                        ux.showAutostart();
                        return 0;
                    }
                    else if(f!=std::string::npos){
                        ux.showFonts();
                        return 0;
                    }
                    else if(i!=std::string::npos){
                        ux.showIcons();
                        return 0;
                    }
                    else if(k!=std::string::npos){
                        ux.showKeyboard();
                        return 0;
                    }
                    else if(m!=std::string::npos){
                        ux.showMouse();
                        return 0;
                    }
                    else if(t!=std::string::npos){
                        ux.showThemes();
                        return 0;
                    }
                    else if(r!=std::string::npos){
                        Config config;
                        config.recover();
                        return 0;
                    }
                    else {
                    }
                }*/
            dash=command[i].find("--",0);
            if(dash!=std::string::npos){
                help = command[i].find("help", dash + 1);
                panel = command[i].find("panel", dash + 1);
                window = command[i].find("window", dash + 1);
                desktop = command[i].find("desktop", dash + 1);
                autostart = command[i].find("autostart", dash + 1);
                font = command[i].find("font", dash + 1);
                icons = command[i].find("icons", dash + 1);
                keyboard = command[i].find("keyboard", dash + 1);
                mouse = command[i].find("mouse", dash + 1);
                themes = command[i].find("themes", dash + 1);
                recover = command[i].find("recover", dash + 1);
                halt = command[i].find("halt", dash + 1);
                if(help!=std::string::npos){
                    showHelp();
                    return 0;
                }
                else if(panel!=std::string::npos){
                    ux.showPanel();
                    return 0;
                }
                else if(window!=std::string::npos){
                    ux.showWindow();
                    return 0;
                }
                else if(desktop!=std::string::npos){
                    ux.showDesktop();
                    return 0;
                }
                else if(autostart!=std::string::npos){
                    ux.showAutostart();
                    return 0;
                }
                else if(font!=std::string::npos){
                    ux.showFonts();
                    return 0;
                }
                else if(icons!=std::string::npos){
                    ux.showIcons();
                    return 0;
                }
                else if(keyboard!=std::string::npos){
                    ux.showKeyboard();
                    return 0;
                }
                else if(mouse!=std::string::npos){
                    ux.showMouse();
                    return 0;
                }
                else if(themes!=std::string::npos){
                    ux.showThemes();
                    return 0;
                }
                else if(recover!=std::string::npos){
                    Config config;
                    config.recover();
                    return 0;
                }
                else if(halt!=std::string::npos){
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
    }

    ///TODO add commandline arguments to run each utility alone
    //such as -panel to showPanel(panel);
    //and --recover to write the default file to $HOME

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
        <<"  --autostart   show autostart settings\n" //<<"  -a --autostart   show autostart settings\n"
        <<"  --desktop     show desktop settings\n" //<<"  -d --desktop     show desktop settings\n"
        <<"  --font        show font settings\n" //<<"  -f --font        show font settings\n"
        <<"  --help        show this listing\n" //<<"  -h --help        show this listing\n"
        <<"  --icons       show icon settings\n"//<<"  -i --icons       show icon settings\n"
        <<"  --keyboard    show keyboard settings\n"//<<"  -k --keyboard    show keyboard settings\n"
        <<"  --mouse       show mouse settings\n"//<<"  -m --mouse       show mouse settings\n"
        <<"  --panel       show panel settings\n"//<<"  -p --panel       show panel settings\n"
        <<"  --themes      show theme settings\n"//<<"  -t --themes      show theme settings\n"
        <<"  --window      show window settings\n"//<<"  -w --window      show window settings\n"
        <<"  --recover     recover settings file\n"//<<"  -r --recover     recover settings file\n"
        <<" GUI ONLY OPTION\n"
        <<"  --halt           show shutdown menu\n"
        << std::endl;
}
