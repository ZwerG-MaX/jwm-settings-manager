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

//FLTK stuff
#include "../fltk/jwm-panel.h"
#include <Fl/Fl_Widget.h>
//All the common functions
#include "Config.h"

//This is for Adding in things like the Volume applet
#include "flAutostart.h"

class flPanel : public Config{

public:

    //How many panels?
    /*
    unsigned int numPanels();
    unsigned int numPanels(Fl_Menu_Button* o);
    bool multipanel();
    //check the attributes of the element passed in
    std::string checkLayout(tinyxml2::XMLElement* tray);
    std::string checkAlign(tinyxml2::XMLElement* tray);
    std::string getHalign(tinyxml2::XMLElement* tray);
    std::string getValign(tinyxml2::XMLElement* tray);
    //get the position of the panel passed in (top, bottom, right, left)
    std::string getPanelLayout(tinyxml2::XMLElement* tray);
*/    //add a Panel
    void addPanel(Fl_Menu_Button *o);

    //testers
    bool test(tinyxml2::XMLElement *element);

    //colors
    void setBackground(const double* rgb, const char * whichElement);
    unsigned int getBackground(unsigned int  &color2, const char * whichElement);
    void setActiveBackground(const double* rgb, const char * whichElement);
    unsigned int getActiveBackground(unsigned int  &color2, const char * whichElement);

    float getOpacity(const char* whichElement);
    void setOpacity(float &opacity, const char* whichElement);

    //Sizing
    void panelWidth(int &panelSize);
    void panelHeight(int &panelSize);
    void borderWidth(int &panelSize);
      //get the value for FLTK
    int getHeight();
    int getWidth();
    int getBorder();

    //Menu
    void menuLabel(const char * label);
    std::string getMenuLabel();
    std::string getMenuImage();
    void setMenuImage(const char* icon);

    //Layout and Positioning (including Autohide)
    int getCoordinate(const char * xy);
    void setCoordinate(const char * xy, int value);
    void panelLayout(const char* layout);
    void panelLayer(const char* layer);
    void panelPositionVert(const char* position);
    std::string getVertPosition();
    void panelPositionHoriz(const char* position);
    void panelAutohide(bool &yesOrNo);
    std::string getAutohide();

    //constructors and destructor
    flPanel();
    virtual ~flPanel();

    //Global variables
    std::string errorMessage;
    std::string align;
    unsigned int counter;
    unsigned int whichPanel;

private:

};

#endif
