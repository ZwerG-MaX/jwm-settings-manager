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
#include <Fl/Fl_Menu_Button.H>
#include <Fl/Fl_Output.H>
#include <Fl/Fl_Double_Window.H>
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
#include <algorithm>
//getExtention for icons
#include <dirent.h>
//gettext
#include <libintl.h>
class Config
{
    public:
    void under_mouse(Fl_Window *o);/**< situate Fl_Window *o in the center of the screen*/
    unsigned int getColor(std::string color, unsigned int &color2);/**< get Color as a string and return a FL_Color*/
    std::string colorToString(const double *rgb);/**< This handles the situation where there are 2 colors separated by a colon*/
    std::string xColor(const char *colorName);/**< find the X11 color */
    std::string returnXColor(unsigned int color);

    /// ICON functions
    std::string getExtention();
    int EXTENTION(std::string filename); /**< this returns an integer
    0 means svg
    1 means png
    2 means xpm
    42 means you'll have to go fish... that is kind of like a joke... sorry
    */
    std::vector<std::string> iconList(); /**< list IconPaths, except "/usr/share/pixmaps" || "/usr/share/icons" as those are not Icon THEMES..*/
/// Basic Functions for JWMRC files
    //Error checking/fixing/reporting
    int checkFiles();
    int recover();
    std::string getFileName(std::string filename);
    std::string jwmrcOUT();
    int newStyle();/**< Check for newer JWM style tags
    -1 is OLD
    0 is 2.3.0
    1 is 2.3.2++
    */
    int jwmVersion();/**< Check for newer JWM
    -1 is OLD
    0 is 2.3.0
    1 is 2.3.1
    2 is 2.3.2
    3 is 2.3.3
    */
    int FULLjwmVersion(); //returns something like (234 for 2.3.4)
    bool newVersionJWM();/**< check if the installed binary of jwm is the newest version*/
    void write_out(std::string fileContents,std::string FILENAME);
    bool writeToFile(std::string fileContents);
    //Display an Error message to cerr
    void errorJWM(std::string message);
    void errorJWM(const char* message);
    //Save
    void saveJWMRC(); //Fully save and reload
    void saveJWMRC(Fl_Double_Window *o); //Fully save and reload
    void saveChanges();
    void saveNoRestart();
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
    bool isDir(std::string FullPathToDir);
/// BASH-LIKE functions
/**
This contains functions that work like grep, and also that work like
VARIABLE=$(command)
where VARIABLE is a std::string
*/
    const char* grep(const char* args, const char* filename);
    std::string grep(const char* args, std::string filename);
    std::vector<std::string> egrep(const char* args, const char* filename);
    std::string returnTerminalOutput(std::string terminal_Command_You_Want_Output_From,const char* type);
    std::string term_out(std::string terminal_Command_You_Want_Output_From);
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
    void setRootMenuHeight(const char* menu, int height);
    void setRootMenuAttribute(const char* menu, const char* attribute, const char* attributeValue);
    void addRoot(std::string rootmenu);
    bool isMenu(const char* rootnumber);
    bool isMenu(std::string includeLine);
    ///This is used externally to check if a cetain menu exists, and ADD or DELETE it  flPanel::switchMenu
    void addMenu(const char* rootnumber, const char* label, const char* icon, const char* whichStyle);
    void newMenu(const char* menu);
    void deleteMenu(const char* menu, const char* whichStyle);
    void addMenu(const char* rootnumber, const char* label, const char* icon);
    void labelMenu(const char * icon, const char* num,const char* label);
    void labelMenu(const char* menu,const char* label);
    void deleteMenu(const char* menu);
    std::string getLabelMenu(const char* menu);
    std::string getImageMenu(const char* menu);
    void setImageMenu(const char* menu, const char* icon);
    void trayButtonAttribute(const char* text,const char* attribute,const char* attributeValue);

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
    //base element with value (ROOT MENU)
    void createElement(const char* whichElement,std::string attribute, std::string attributeValue);
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
    ///ICONS//////////////////////
    std::string searchthemes(std::string THEME_TO_INHERIT);
    std::string PickOut(std::string line, std::string findThis, std::string OriginalVar);
    std::string homeIcons(std::string THEME_TO_USE);
    std::string removeCruft(std::string StringInput, std::string CruftToRemove);
    std::string getGTKtheme();
    std::string get_line(std::string filename, std::string line);
    std::string getUserIcons(std::string Directory);
    std::vector<std::string> commaVector(std::string LINE,std::vector<std::string>Vector);
    std::vector<std::string> iconThemeDirectories();
    std::vector<std::string> split_paths(const char* envVar, const char* incasenothingexists);
    std::vector<std::string> sortArray(std::vector<std::string> thisPath);
    std::vector<std::string> GetThemeFiles(std::string direcotry);
    //FONT stuff
    bool isFONT(std::string FONTNAME);
    std::string getDefaultFONT();

    //Set Window Icon
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
    bool testedFILE;
    char* home;
    char* path;
    std::string stringPATH;
    std::string::size_type pathPosition;
    int numPATHS;
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
