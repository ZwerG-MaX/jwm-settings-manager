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


#ifndef FLPANEL_H_INCLUDED
#define FLPANEL_H_INCLUDED
//Ubuntu 14.04 is missing SetText() so I have to include this
#include "tinyxml2.h"

//Used for getting the user's Home directory
#include <stdlib.h>

//strtoul  for background string to unsigned int
#include <cstdlib>

//write recovery file directly from program
#include <fstream>

//Hopefully you already know what these are for
#include <iostream>
#include <string>
#include <list>

//FLTK stuff
#include "../fltk/jwm-panel.h"
#include <Fl/Fl_Widget.h>
//All the common functions
#include "Config.h"

//This is for Adding in things like the Volume applet
#include "flAutostart.h"

class flPanel : public Config{

public:

   //add a Panel
    void addPanel();
    const char* smartPosition();
    const char* smartVertAlign(const char* layout);
    const char* smartHorizAlign(const char* layout);
    int whichAlign(const char* Align); //1 is valign 2 is halign 3 is unknown
    void setPanelText(const char* element);
    std::string getPanelText(const char* element);

    //delete a PANEL
    void deletePanel();

    //testers
    bool test(tinyxml2::XMLElement *element);
    //move
    void moveUp(std::string item);
    void moveDown(std::string item);
    int moveMenuDown(std::string menu);
    int deleteOldElement(std::string namesaver);
    ///colors  used by all the Panel stuff...
    //Inactive
    void setBackground(const double* rgb, const char * whichElement);
    unsigned int getBackground(unsigned int  &color2, const char * whichElement);
    void setFontColor(const double* rgb, const char * whichElement);
    unsigned int getFontColor(unsigned int  &color2, const char * whichElement);
    //Active
    void setActiveFontColor(const double* rgb, const char * whichElement);
    unsigned int getActiveFontColor(unsigned int  &color2, const char * whichElement);
    void setActiveBackground(const double* rgb, const char * whichElement);
    unsigned int getActiveBackground(unsigned int  &color2, const char * whichElement);
    //Opacity
    float getOpacity(const char* whichElement);
    void setOpacity(float &opacity, const char* whichElement);
    void setPosition(const char* attribute, const char* value);

    ///Generic Panel configurations
    void setValue(const char* attribute, int value);
    int getValue(const char* attribute);
    std::string getStringValue(const char* attribute);
    void setValue(const char* attribute, const char* value);
    const char* getValue(std::string attribute);

    ///used to configure xload and other Swallowed apps
    const char * getSubElementText(const char* whichElement);
    void setSubElementText(const char* whichElement,const char* value);
    const char* getSubElementAttribute(const char* whichElement,const char* attribute);
    void setSubElementAttribute(const char* whichElement,const char* attribute, const char* value);

    ///Border
    int getBorder();
    const char* horizontalORvertical(int horizontalValue, int verticalValue);

    ///Menu
    //Menu functions IN Config
    /*
        labelMenu
        isMenu
        addMenu
        deleteMenu
        getLabelMenu
        getImageMenu
        setImageMenu
    */
    //Menu functions IN Apps
    /*
        ///APPS
        isAppMenu
        addAppMenu
        deleteAppMenu
        ///PLACES
        isPlaces
        addPlaces
        deletePlaces
        ///SHUTDOWN
        isShutdown
        addShutdown
        deleteShutdown
        setShutdownImage
    */
    //menu functions here
    void menuLabel(const char * label);
    std::string getMenuLabel(){return getLabelMenu(rootMenu);}
    std::string getMenuImage(){return getImageMenu(rootMenu);}
    void setMenuImage(const char* icon){setImageMenu(icon, rootMenu);}

    //switchers
    void switchMenu(int whichStyle, const char* MenuName);
    void switchMenuInclude(std::string changeTHIS, std::string toTHIS);
    void switchButton(std::string OLD,std::string NEW,std::string tooltip,std::string icon);
    //VARIABLES for menu
    std::string torimenu;
    std::string gnomemenu;
    std::string sysmenu;// = "gnomesystem";

    ///Layout and Positioning (including Autohide)
    void panelLayout(const char* layout){setValue("layout",layout);}
    void panelLayer(const char* layer){setValue("layer",layer);}
    void panelPositionVert(const char* position){setValue("valign",position);}
    std::string getVertPosition(){return getStringValue("valign");}
    void panelPositionHoriz(const char* position){setValue("halign",position);}
    void panelAutohide(bool &yesOrNo);
    void panelAutohide(const char* hideWhere);
    std::string getAutohide();
        //Width (setter is in jwm-panel, but uses setValue)
    int getWidth(){return getValue("width");}
    //Height (setter is in jwm-panel, but uses setValue)
    int getHeight(){return getValue("height");}
    //xy
    int getCoordinate(const char * xy){return getValue(xy);}
    void setCoordinate(const char * xy, int value){setValue(xy,value);}

    ///JSM
    void setJSM(const char* element, const char* value);

    //constructors and destructor
    flPanel();
    virtual ~flPanel();

    ///Global variables
    int rootMenu;
    int systemMenu;
    std::string errorMessage;
    std::string align;
    const char* iconExt;
    unsigned int counter;
    unsigned int whichPanel;
    unsigned int howmanyPanels;

private:

};

#endif
