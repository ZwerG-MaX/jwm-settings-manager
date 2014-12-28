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
#include <vector>

class Config
{
    public:

    ///get Color as a string and return a FL_Color
    //This handles the situation where there are 2 colors separated by a colon
    unsigned int getColor(std::string color, unsigned int &color2);
    std::string colorToString(const double *rgb);
    //X11 colors
    std::string xColor(const char *colorName);

    ///Error checking/fixing/reporting
    int checkFiles();
    void setRecoveryText(std::string &ConfigFile);
    int recover();
    void errorJWM(std::string message);
    void errorJWM(const char* message);
    //This is for the saving functions
    void saveChanges();
    void saveChangesTemp();
    std::string convert(int num);
    unsigned int convert(const char* num);
    const char* convert(double num);
    bool testElement(tinyxml2::XMLElement* element);
    //checking executables and files
    bool testExec(const char* exec);
    bool testFile(const char* fileWithFullPATH);


    //Cancel
    void cancel();

    //Setup functions for the paths
    void setFileName(std::string &defaultFile);
    std::string homePath();
    std::string homePathNoFile();
    std::string homePathTemp();
    unsigned int howmanyPATHS();
    const char* thisPATH(int whichPath);

    //Loaders
    int load();
    int loadTemp();


/*  Autostart and MultiPanels are here to limit inheritance  there may be a better more clear way of doing this*/

//***************************************  AUTOSTART  ****************************************************

    //add
    void addAutostart(const char * program);
    //remove
    void removeAutostart(const char * program);
    bool isAutostart(const char* program);
/// MENU ????????????????????????????????????????????????????????????????????????????????????????????????????????????????
    bool isMenu(int rootnumber);
    void addMenu(int rootnumber, const char* label, const char* icon);
    void labelMenu(const char * icon, int num,const char* label);
    void deleteMenu(int menu);
    std::string getLabelMenu(int menu);
    std::string getImageMenu(int menu);
    void setImageMenu(const char* icon, int menu);

///************************************  MULTIPLE PANELS  *************************************************
    ///Which Panel?
    //How many panels?
    int numPanels();
    bool multipanel();
    //get the valign or halign value from the FLTK UI 'Current Panel:'
    int currentPanel();
    // tell it which panel to check (1,2,3,4,etc...) and it will return the layout
    const char* checkLayout(unsigned int panel);
    const char* checkLayout(); //from ~/.jsm

    // tell it which panel to check (1,2,3,4,etc...) and it will return the halign or valign
    const char* getPanelLayout(unsigned int panel);
    const char* getPanelLayout();
    //const char* getHalign(unsigned int panel);
    //const char* getValign(unsigned int panel);
    const char* getAttribute(const char* attribute, unsigned int panel);
    ///CURRENT PANEL
    const char* getCurrentPanelLayout();
    const char* getJSMelement(const char* element);
    const char* getCurrentHalign();
    const char* getCurrentValign();
    //add a Panel
    void addPanel(Fl_Menu_Button *o);
    void changePanel(int panel);
    const char* Panel_Info(Fl_Output *o); ///DO I NEED T
    //TODO: make a smart checker to figure out if there are multiple panels in the same valign or halign.
///JSM our own little xml config for multipanels
    int loadJSM();
    int recoverJSM();
    void recoverJSM(int panel);
    void saveJSM();
    //void updateJSM();
    std::string jsmPath();
    std::string getIconExtention();
///Multiuse/////////////////////////////////////////////////////////////////////////////////////////
    void addElement(const char* whichElement);
    bool isElement(const char* whichElement);
    void setAttribute(const char* whichElement, const char* attribute, const char* value);
    void setAttribute(const char* whichElement, const char* attribute, const char* value, const char* text);
    void setAttribute(const char* whichElement, const char* attribute, int value);
    void setAttribute(const char* whichElement, const char* attribute, double value);
    void createElement(const char* whichElement);
    const char* getElementAttribute(const char* whichElement, const char* attribute);
    int getIntAttribute(const char* whichElement, const char* attribute);
    void deleteElement(const char* whichElement);

/// BASH-LIKE functions
    const char* grep(const char* args, const char* filename);
    std::vector<std::string> egrep(const char* args, const char* filename);

    //constructor and destructor
    Config();
    virtual ~Config();

    ///Global variables
    std::string align;
    unsigned int counter;
    unsigned int whichPanel;
    //xmlDoc
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLDocument jsm;

    protected:
    std::string iconExtention;
    std::string jwmrc;
    std::string recoveryText;
    std::string file;
    std::string JSMfile;

    char* home;
    char* path;
    std::string stringPATH;
    std::string::size_type pathPosition;
    int numPATHS;

    private:
};

#endif // CONFIG_H
