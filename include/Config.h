#ifndef CONFIG_H
#define CONFIG_H

//Color
#include <X11/Xlib.h>

//FLTK includes
#include <Fl/Fl_Menu_Button.h>
#include <Fl/Fl_Output.H>

//Ubuntu 14.04 is missing SetText() so I have to include this
#include "tinyxml2.h"

//Used for getting the user's Home directory
#include <stdlib.h>

//strtoul  for background string to unsigned int
#include <cstdlib>

//write recovery file directly from program
#include <fstream>

//MultiDesktop int from string
#include <cstdlib>
#include <cstdio>

//double to string
#include <sstream>

//Used by some sub-classes to check for files and folders
#include <sys/types.h>
#include <sys/stat.h>

//Hopefully you already know what these are for
#include <iostream>
#include <string>
#include <stdio.h>

class Config
{
    public:

    //get Color as a string and return a FL_Color
    //This handles the situation where there are 2 colors separated by a colon
    unsigned int getColor(std::string color, unsigned int &color2);
    std::string colorToString(const double *rgb);
    bool testElement(tinyxml2::XMLElement* element);
    //X11 colors
    std::string xColor(const char *colorName);

    //Error checking/fixing/reporting
    int checkFiles();
    void setRecoveryText(std::string &ConfigFile);
    int recover();
    void errorJWM(std::string message);
    void errorJWM(const char* message);
    //This is for the saving functions
    void saveChanges();
    void saveChangesTemp();
    std::string convert(int num);

    //checking executables
    bool testExec(const char* exec);

    //Cancel
    void cancel();

    //Setup functions for the paths
    void setFileName(std::string &defaultFile);
    std::string homePath();
    std::string homePathNoFile();
    std::string homePathTemp();

    //Loaders
    int load();
    int loadTemp();


/*  Autostart and MultiPanels are here to limit inheritance  there may be a better more clear way of doing this*/

//***************************************  AUTOSTART  ****************************************************

    //add
    void addAutostart(const char * program);

    //remove
    void removeAutostart(const char * program);

//************************************  MULTIPLE PANELS  *************************************************

    ///Which Panel?
    //How many panels?
    unsigned int numPanels();
    // calls numPanels() to find out how many panels there are and make Fl_Menu_Items for each one.
    unsigned int numPanels(Fl_Menu_Button* o);
    bool multipanel();
    //get the valign or halign value from the FLTK UI 'Current Panel:'
    const char* currentPanel();
    // tell it which panel to check (1,2,3,4,etc...) and it will return the layout
    const char* checkLayout(unsigned int panel);
    // tell it which panel to check (1,2,3,4,etc...) and it will return the halign or valign
    const char* getPanelLayout(unsigned int panel);
    //add a Panel
    void addPanel(Fl_Menu_Button *o);
    //
    const char* Panel_Info(Fl_Output *o);

/// FRIENDS from FLTK UI
    friend const char* get_vh();
    friend void Menu_CB();

    //constructor and destructor
    Config();
    virtual ~Config();

    ///Global variables
    std::string align;
    unsigned int counter;
    unsigned int whichPanel;
    //xmlDoc
    tinyxml2::XMLDocument doc;


    protected:

    std::string jwmrc;
    std::string recoveryText;
    std::string file;
    char* home;

    private:
};

#endif // CONFIG_H
