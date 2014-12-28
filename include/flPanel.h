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
    const char* smartAlign(const char* layout);
    int whichAlign(const char* Align); //1 is valign 2 is halign 3 is unknown
    void setPanelText(const char* element);
    std::string getPanelText(const char* element);
    void deletePanel();

    //testers
    bool test(tinyxml2::XMLElement *element);

    //colors
    void setBackground(const double* rgb, const char * whichElement);
    unsigned int getBackground(unsigned int  &color2, const char * whichElement);
    void setActiveBackground(const double* rgb, const char * whichElement);
    unsigned int getActiveBackground(unsigned int  &color2, const char * whichElement);
    //Opacity
    float getOpacity(const char* whichElement);
    void setOpacity(float &opacity, const char* whichElement);
    void setPosition(const char* attribute, const char* value);
    void setValue(const char* attribute, int &value);
    void createValue(const char* attribute, const char* value);
    void createValue(const char* attribute, int &value);
    int getValue(const char* attribute);
    std::string getStringValue(const char* attribute);
    void setValue(const char* attribute, const char* value);
    const char* getValue(std::string attribute);
    //Width
    void panelWidth(int &panelSize){setValue("width", panelSize);}
    int getWidth(){return getValue("width");}
    //Height
    void panelHeight(int &panelSize){setValue("height",panelSize);}
    int getHeight(){return getValue("height");}
    //xy
    int getCoordinate(const char * xy){return getValue(xy);}
    void setCoordinate(const char * xy, int value){setValue(xy,value);}
    //Border
    void borderWidth(int &panelSize){setValue("border",panelSize);}
    int getBorder(){return getValue("border");}
    const char* horizontalORvertical(int horizontalValue, int verticalValue);

    //Menu
    void menuLabel(const char * label);
    std::string getMenuLabel(){return getLabelMenu(5);}
    std::string getMenuImage(){return getImageMenu(5);}
    void setMenuImage(const char* icon){setImageMenu(icon, 5);}

    //Layout and Positioning (including Autohide)
    void panelLayout(const char* layout){setValue("layout",layout);}
    void panelLayer(const char* layer){setValue("layer",layer);}
    void panelPositionVert(const char* position){setValue("valign",position);}
    std::string getVertPosition(){return getStringValue("valign");}
    void panelPositionHoriz(const char* position){setValue("halign",position);}
    void panelAutohide(bool &yesOrNo);
    std::string getAutohide(){return getStringValue("autohide");}

    ///JSM
    void setJSM(const char* element, const char* value);
    void updatePanels(int panel){recoverJSM(panel);}

    //constructors and destructor
    flPanel();
    virtual ~flPanel();

    //Global variables
    std::string errorMessage;
    std::string align;
    unsigned int counter;
    unsigned int whichPanel;
    unsigned int howmanyPanels;

private:

};

#endif
