#ifndef CONFIG_H
#define CONFIG_H
//This is for saveJWMRC(Fl_Double_Window *o) to show the main settings page
//#include "../fltk/jwm-settings.h"
//Color
#include <X11/Xlib.h>
//FLTK includes
#include <FL/fl_ask.H> //errorJWM
#include <Fl/Fl_Menu_Button.h>
#include <Fl/Fl_Output.H>
#include <Fl/Fl_Double_Window.h>
#include <FL/Fl_File_Chooser.H>
//Ubuntu 14.04 is missing SetText() so I have to include this
#include "tinyxml2.h"
//Used for getting the user's Home directory
#include <stdlib.h>
//strtoul  for background string to unsigned int
#include <cstdlib>
//write recovery file directly from program
#include <fstream>
//MultiDesktop int from string
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
//getExtention for icons
#include <dirent.h>
class Config
{
    public:

    ///get Color as a string and return a FL_Color
    //This handles the situation where there are 2 colors separated by a colon
    unsigned int getColor(std::string color, unsigned int &color2);
    std::string colorToString(const double *rgb);
    //X11 colors
    std::string xColor(const char *colorName);

    /// ICON functions
    std::string getExtention();
    int EXTENTION(std::string filename); //only used by getExtention
    /*this returns an integer
    0 means svg
    1 means png
    2 means xpm
    42 means you'll have to go fish... that is kind of like a joke... sorry
    */
    std::vector<std::string> iconList(int &listcounter); //list IconPaths, except "/usr/share/pixmaps" || "/usr/share/icons" as those are not Icon THEMES..

/// Basic Functions for JWMRC files
    //Error checking/fixing/reporting
    int checkFiles();
    void setRecoveryText(std::string &ConfigFile);
    int recover();

    //Check for newer JWM style tags
    bool newStyle();
    bool newVersionJWM();

    //Display an Error message to cerr
    void errorJWM(std::string message);
    void errorJWM(const char* message);
    //Save
    void saveJWMRC(); //Fully save and reload
    void saveJWMRC(Fl_Double_Window *o); //Fully save and reload
    void saveChanges();
    void saveChangesTemp();
    //Load
    int load();
    int loadTemp();
    //Cancel
    void cancel();
    void cancel(Fl_Double_Window *o);
    //Setup functions for the paths
    void setFileName(std::string &defaultFile);
    std::string homePath();
    std::string homePathNoFile();
    std::string homePathTemp();
    unsigned int howmanyPATHS();
    const char* thisPATH(int whichPath);

/// Utility functions to convert numbers to strings and vice versa
    std::string convert(int num);
    unsigned int convert(const char* num);
    const char* convert(double num);
    std::string fixName(const char* filename);

///Functions for checking executables and files
    bool testExec(const char* exec);
    bool testFile(const char* fileWithFullPATH);

/// BASH-LIKE functions
/**
This contains functions that work like grep, and also that work like
VARIABLE=$(command)
where VARIABLE is a std::string
*/
    const char* grep(const char* args, const char* filename);
    std::string grep(const char* args, std::string filename){return grep(args,filename.c_str());}
    std::vector<std::string> egrep(const char* args, const char* filename);
    std::string returnTerminalOutput(std::string terminal_Command_You_Want_Output_From,const char* type);
    int run(const char* command);

/// AUTOSTART Functions ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //add
    void addAutostart(std::string program);
    //remove
    void removeAutostart(std::string program);
    bool isAutostart(std::string program);

/// MENU Functions /????????????????????????????????????????????????????????????????????????????????????????????????????????????????
    bool isMenu(int rootnumber);
    bool isMenu(std::string includeLine);
    ///This is used externally to check if a cetain menu exists, and ADD or DELETE it  flPanel::switchMenu
    bool isMenu(const char* whichStyle);
    void addMenu(int rootnumber, const char* label, const char* icon, const char* whichStyle);
    void deleteMenu(int menu, const char* whichStyle);
    void addMenu(int rootnumber, const char* label, const char* icon);
    void labelMenu(const char * icon, int num,const char* label);
    void deleteMenu(int menu);
    std::string getLabelMenu(int menu);
    std::string getImageMenu(int menu);
    void setImageMenu(const char* icon, int menu);
    ///Variables to be set in the constructor
    const char* configEnvHOME;/// = "$HOME/.config/";
    std::string homeConfig;/// = home+"/.config/";
    std::string torimenu;/// = "torimenu";
    std::string placesmenu;/// = "placesmenu";
    std::string gnomemenu;/// = "gnomeapps";
    std::string sysmenu;/// = "gnomesystem";

///  MULTIPLE PANELS  /*************************************************
    //How many panels?
    int numPanels();
    bool multipanel();
    int currentPanel();
    // tell it which panel to check (1,2,3,4,etc...) and it will return the layout
    const char* checkLayout(unsigned int panel);
    const char* checkLayout(); //from ~/.jsm
    // tell it which panel to check (1,2,3,4,etc...) and it will return the halign, valign, layout
    const char* getPanelLayout(unsigned int panel);
    const char* getPanelLayout();
    const char* getAttribute(const char* attribute, unsigned int panel);
    void changePanel(int panel);

///JSM our own little xml config for multipanels
/**
Basically this loads, recovers, or saves a file that is designed specifically for multipanel use,
it also will save the default clock program, and other defaults (as they are implemented)
*/
    int loadJSM();
    int recoverJSM();
    void recoverJSM(int panel);
    void saveJSM();
    const char* getJSMelement(const char* element);
    //void updateJSM();
    std::string jsmPath();

///Multiuse/////////////////////////////////////////////////////////////////////////////////////////
    bool testElement(tinyxml2::XMLElement* element);
    void addElement(const char* whichElement);
    bool isElement(const char* whichElement);
    bool isElement(const char* whichElement, const char* whichSUBElement);
    bool isElementText(const char* whichElement, std::string text);
    void setAttribute(const char* whichElement, const char* attribute, const char* value);
    void setAttribute(const char* whichElement, const char* attribute, const char* value, const char* text);
    void setAttribute(const char* whichElement, const char* attribute, int &value);
    void setAttribute(const char* whichElement, const char* attribute, double &value);

    //Create Element ?? How can I use this??  I think this would be really helpful :(
    void createElement(const char* whichElement);
    void createElement(const char* whichMainElement, const char* whichElementToCreate);
    void createElement(const char* whichMainElement, const char* whichSubElement, const char* whichElementToCreate);

    const char* getElementAttribute(const char* whichElement, const char* attribute);
    const char* getElementAttribute(const char* whichElement,const char* whichSubElement,const char* attribute);
    int getIntAttribute(const char* whichElement, const char* attribute);
    void deleteElement(const char* whichElement);
    void setFGColor(const char* whichStyle, const char* ActiveORinactive, const double* rgb);
    void setELEMENTColor(const char* whichStyle, const char* ActiveORinactive, const double* rgb, const char* FGorBG);
    void under_mouse(Fl_Window *o);
    unsigned int getELEMENTColor(const char* whichStyle, const char* ActiveORinactive, unsigned int &color2, const char* FGorBG);
    unsigned int getFGColor(const char* whichStyle, const char* ActiveORinactive, unsigned int &color2);
    std::string desktopExec(std::string filename);
    std::string desktopFILE();
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
    bool isNewStyle;

    private:
};

#endif // CONFIG_H
