#ifndef CONFIG_H
#define CONFIG_H
//This is for saveJWMRC(Fl_Double_Window *o) to show the main settings page
//#include "../fltk/jwm-settings.h"
//Color
#include <X11/Xlib.h>
//icon includes
#include <X11/xpm.h>
#include <FL/x.H>
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
//gettext
#include <libintl.h>
class Config
{
    public:
    //situate windows under the mouse pointer
    void under_mouse(Fl_Window *o);
    ///get Color as a string and return a FL_Color
    //This handles the situation where there are 2 colors separated by a colon
    unsigned int getColor(std::string color, unsigned int &color2);
    std::string colorToString(const double *rgb);
    //X11 colors
    std::string xColor(const char *colorName);
    std::string returnXColor(unsigned int color);

    /// ICON functions
    std::string getExtention();
    int EXTENTION(std::string filename); //only used by getExtention
    /*this returns an integer
    0 means svg
    1 means png
    2 means xpm
    42 means you'll have to go fish... that is kind of like a joke... sorry
    */
    std::vector<std::string> iconList(); //list IconPaths, except "/usr/share/pixmaps" || "/usr/share/icons" as those are not Icon THEMES..
/// Basic Functions for JWMRC files
    //Error checking/fixing/reporting
    int checkFiles();
    void setRecoveryText(std::string &ConfigFile);
    int recover();

    //Check for newer JWM style tags
    int newStyle();
    /*
    -1 is OLD
    0 is 2.3.0
    1 is 2.3.2++
    */
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
    bool comparedColon(const char* something, const char* text);
    bool isRootMenu(std::string rootmenu);
    bool isMenu(int rootnumber);
    bool isMenu(std::string includeLine);
    ///This is used externally to check if a cetain menu exists, and ADD or DELETE it  flPanel::switchMenu
    bool isMenu(const char* whichStyle);
    void addMenu(int rootnumber, const char* label, const char* icon, const char* whichStyle);
    void newMenu(const char* menu);
    void deleteMenu(int menu, const char* whichStyle);
    void addMenu(int rootnumber, const char* label, const char* icon);
    void labelMenu(const char * icon, int num,const char* label);
    void deleteMenu(int menu);
    std::string getLabelMenu(int menu);
    std::string getImageMenu(int menu);
    void setImageMenu(const char* icon, int menu);

///  MULTIPLE PANELS  /*************************************************
    //recovery function if no Tray Element exists...
    void createPanel();
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
    void updatePanels(int panel){recoverJSM(panel);}
    int loadJSM();
    int recoverJSM();
    void recoverJSM(int panel);
    void saveJSM();
    const char* getJSMelement(const char* element);
    void setJSMelement(const char* element, const char* value);
    //void updateJSM();
    std::string jsmPath();

///Multiuse/////////////////////////////////////////////////////////////////////////////////////////

    void addElement(const char* whichElement);
    bool isElement(const char* whichElement);
    bool isElement(const char* whichElement, const char* whichSUBElement);
    bool isElementText(const char* whichElement, std::string textTOcompare);
    void setAttribute(const char* whichElement, const char* attribute, const char* value);
    void setAttribute(const char* whichElement, const char* attribute, const char* value, const char* text);
    void setAttribute(const char* whichElement, const char* attribute, int &value);
    void setAttribute(const char* whichElement, const char* attribute, double &value);

    bool testElement(tinyxml2::XMLElement* element);
    //Create Element!
    void createElement(const char* whichElement);
    void createElement(const char* whichMainElement, const char* whichElementToCreate);
    void createElement(const char* whichMainElement, const char* whichSubElement, const char* whichElementToCreate);
    bool testElement(const char* whichElement);
    bool testElement(const char* whichElement,const char* whichSubElement);
    bool testElement(const char* whichElement,const char* whichSubElement, const char* whichSUBsubElement);

    const char* getElementAttribute(const char* whichElement, const char* attribute);
    const char* getElementAttribute(const char* whichElement,const char* whichSubElement,const char* attribute);
    int getIntAttribute(const char* whichElement, const char* attribute);
    void deleteElement(const char* whichElement);
    void setFGColor(const char* whichStyle, const char* ActiveORinactive, const double* rgb);
    void setELEMENTColor(const char* whichStyle, const char* ActiveORinactive, const double* rgb, const char* FGorBG);
    unsigned int getELEMENTColor(const char* whichStyle, const char* ActiveORinactive, unsigned int &color2, const char* FGorBG);
    unsigned int getFGColor(const char* whichStyle, const char* ActiveORinactive, unsigned int &color2);
    std::string desktopExec(std::string filename);
    std::string desktopFILE();
    void setDebug();
    void setDebugOff();
    bool isDebug();
    char* Get_Fl_Icon(char const** pIcon);
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
    std::string jwmrc;
    std::string recoveryText;
    std::string file;
    std::string JSMfile;
///Variables to be set in the constructor
    std::string homePathNoFiles;
    const char* configEnvHOME;/// = "$HOME/.config/";
    std::string homeConfig;/// = home+"/.config/";
    std::string torimenu;/// = "torimenu";
    std::string placesmenu;/// = "placesmenu";
    std::string gnomemenu;/// = "gnomeapps";
    std::string sysmenu;/// = "gnomesystem";

    char* home;
    char* path;
    std::string stringPATH;
    std::string::size_type pathPosition;
    int numPATHS;
    bool isNewStyle;
    std::string defaultPath;
    std::string defaultFilePath;
    std::string defaultFilePath230;
    std::string defaultOLDFilePath;
    const char* theMenuROOT;
    //default file path
    std::string  getDefaultFilepath();
    //XDG_DATA_DIRS
    const char* thisXDG_PATH(int whichPath);
    unsigned int numXDG_PATHS();
    bool DEBUG_ME;
    std::string xdg_paths;
    std::string set_xdg_paths();
    std::string stringXDG_PATH;
    std::string::size_type XDG_pathPosition;
    int num_XDG_PATHS;
};

#endif // CONFIG_H
