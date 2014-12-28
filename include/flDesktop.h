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


#ifndef FLDESKTOP_H_INCLUDED
#define FLDESKTOP_H_INCLUDED

//FLTK stuff
#include "../fltk/jwm-desktop.h"
#include "Config.h"
class flDesktop : public Config{

public:

    //Multi Desktop
    void useMultiDesktop(bool &multiValue, int &height, int &width); //use more than one desktop?
    int getMultiDeskWidth(); //how many wide
    int getMultiDeskHeight(); //how many tall
    bool multipleDesktops(); //finds out if there are mulitple desktops
    void setMultiDeskWidth(double width); //how many wide
    void setMultiDeskHeight(double height);  //how many tall

    const char * getBackground();// , const char * rgb, const char* rgb2) //Get JWM background
    /*If it is an image/command the rgb variables will be ignored.
     * if it is solid/gradient color the return value should be ignored in the UI
     */
    unsigned int getBackground(unsigned int &color2);  //get color background either single or gradient
    /*the variable the function is assigned to gets the first color, or a single color, and color2 is the second color.
     * if only one color is needed make the variable for color2 and don't use it.  This way both situations are automatically handled
     * ///TODO: fix this! make an overloaded function so each can be handled separately.
     */

    void setFlImage(Fl_Box * o, const char * filename);
    void setBackground(const double* rgb);
    void setBackground(const double* rgb, const double* rgb2);
    void setBackground(const char* type, const char* value);  //set background image, a tiled image or command.  type = image value = filename(or command)

    const char* whichFileManager();
    //ROX
    int addRoxFileAttribute(const char* element, const char* attribute, const char* value, const char* text);
    void useRox(bool rox);//Set Rox use to TRUE or FALSE
    bool roxActive(); //is rox in startup?
    bool roxExists(); //does the binary exist?
    bool configExists();
    void makeConfig();
    void createRoxDir();
    void recoverRox(); //did the file get deleted, or is there a wrong file used??
    void setRoxBackground(const char* type, const char* value);//change the rox background from jsm
    void setRoxBackground(const char* value);//change the rox background from jsm
    int loadRox(); /* this loads the Pinboard File... if it does not exist it should create it. by calling recoverRox()*/
    const char * getRoxBackground();
    void saveRox();
    std::string roxPath();

    bool test(tinyxml2::XMLElement *element);
    //constructors and destructor
    flDesktop();
    virtual ~flDesktop();

private:
    bool roxPresent;
    const char *roxCommand;
    bool m_useRox;
    bool m_usePCmanFM;
    std::string pcmanFMfilename;
    std::string roxFileName;
    tinyxml2::XMLDocument roxDoc;

};

#endif
