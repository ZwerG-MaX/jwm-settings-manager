/*                 Joe's Window Manager Configuration
 *
 * This program configures JWM using pugixml and FLTK
 *
 *         Copyright (C) 2016  Israel <israeldahl@gmail.com>
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
 *
 *
 * You may redistribute this, but you must keep this comment in place
 * Jesus is my Lord, and if you don't like it feel free to ignore it.
 */
#ifndef TEST_H
#define TEST_H
#include <X11/Xlib.h>
//icon includes
#include <X11/xpm.h>
#include <FL/x.H>
//FLTK includes
#include <FL/fl_ask.H> //errorJWM
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_PNG_Image.H>
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
#include <list>
//getExtention for icons
#include <dirent.h>
//gettext
#include <libintl.h>
#include "common.hpp"
#include "pugixml.hpp"

///Boolean//////////////////////////////////////////////////////////////
//A
bool addButtonToLastTray(std::string attribute, std::string value, std::string text);
bool addElement(std::string element);
bool addElementAndSub(std::string element, std::string subelelemnt);
bool addElementWithText(std::string element, std::string text);
bool addElementWithTextAfter(std::string element, std::string text);
bool addElementWithAttribute(std::string element, std::string attribute, std::string value);
bool addElementWithTextAndAttribute(std::string element, std::string attribute, std::string value,std::string text);
bool addElementWithTextAndAttribute(std::string element, std::string attribute, std::string value, std::string attribute2, std::string value2,std::string text);
bool addElementWithSubAndText(std::string element, std::string subelement, std::string text);
bool addMenuElement(unsigned int whichMenu,std::string element);
bool addSubElement(unsigned int whichElement,std::string element, std::string subelelemnt);
bool addSubElementWithText(unsigned int whichElement,std::string element, std::string subelelemnt, std::string text);
bool addSubElementWithTextandAttribute(unsigned int whichElement,std::string element, std::string subelelemnt, std::string text,std::string attribute, std::string value);
bool addSubElementWithAttribute(unsigned int whichElement,std::string element, std::string subelelemnt, std::string attribute, std::string value);
bool addSubNodewithText(pugi::xml_node node,std::string element,std::string text);
bool addSubNodewithAttributeAndText(pugi::xml_node node,std::string element,std::string attribute, std::string value, std::string text);
//C
bool changeCursorTheme(Fl_Browser *o);
bool checkDE(std::string file);
bool checkExec(std::string exec);
bool checkFlBrowserItem(Fl_Browser* o);
bool checkVector(std::vector<std::string> myVec,std::string item);
//D
bool deleteElements(std::string element);
bool deleteSubElement(std::string element, int whichElement);
//E
bool editMenuItem(int menu, int item, std::string text);
bool editMenuItem(int menu, int item, std::string attribute,std::string value);
//G
bool getIcons(Fl_Browser *o);
bool getMenuItems(Fl_Browser* menuElement,std::string menu,Fl_Browser* menuElementText);
bool getMenus(Fl_Browser* rootnode);
//I
bool isColor(std::string text);
bool isElement(std::string element);
bool isElement(std::string element, std::string subelement);
bool isElement(std::string element, std::string subelement, std::string SUBsubelement);
//bool isElement(std::string element, std::string subelement, std::string SUBsubsubelement);
bool isExec(std::string exec);
bool isImage(std::string filename);
bool isMenu(std::string rootNumber);
bool isRootMenu(std::string rootmenu);
bool isSVG(std::string filename);
bool isTrayElement(std::string element);
//L
bool load();
bool load(std::string filename);
bool load(std::string filename, bool saveTemp);
bool loadTemp();
//N
bool newVersionJWM();
//P
bool populateFLBrowser(Fl_Browser *o,std::string element);
bool populateFLBrowser(Fl_Browser *o,std::string element,std::string subelement, unsigned int whichMainElement);
bool populateFLBrowser2Attr(Fl_Browser *o,std::string element,std::string attribute1, std::string attribute2);
//R
bool removeMenu(std::string value);
//S
bool saveChanges();
bool saveChanges(std::string filename,bool restart, bool reload);
bool saveChangesTemp();
bool saveChangesTempOverwrite();
bool saveChangesTempOverwrite(std::string myhomie);
bool saveNoRestart();
bool setAttribute(pugi::xml_node node,std::string attribute,std::string value);
bool setLastTrayButtonAttribute(std::string attribute,std::string value);
bool setElementText(std::string element, std::string text);
bool setElementText(unsigned int whichElement, std::string element, std::string subelement, std::string text);
bool setElementText(std::string element, std::string subelement, std::string text);
bool setElementText(std::string element, std::string subelement, std::string SUBsubsubelement, std::string text);
bool setElementInt(std::string element, unsigned int text);
bool setElementInt(std::string element, std::string subelement, unsigned int text);
bool setElementInt(std::string element, std::string subelement, std::string SUBsubsubelement, unsigned int text);
bool setElementFloat(std::string element, double* text);
bool setElementFloat(std::string element, std::string subelement, double* text);
bool setElementFloat(std::string element, std::string subelement, std::string SUBsubsubelement, double* text);
bool setElementAttribute(unsigned int whichElement, std::string element, std::string attribute, std::string value);
bool setElementAttribute(unsigned int whichElement, std::string element, std::string subelement, std::string attribute, std::string value);
bool setElementAttribute(std::string element, std::string attribute, std::string value);
bool setElementAttribute(std::string element, std::string subelement, std::string attribute, std::string value);
bool setElementAttribute(std::string element, std::string subelement, std::string SUBsubsubelement, std::string attribute, std::string value);
bool setElementAttributeANDtext(std::string element, std::string attribute, std::string value,std::string text);
bool setElementAttributeANDtext(std::string element, std::string subelement, std::string attribute, std::string value,std::string text);
bool setElementAttributeANDtext(std::string element, std::string subelement, std::string SUBsubsubelement, std::string attribute, std::string value,std::string text);
bool setElementColor(std::string element, const double* rgb);
bool setElementColor(std::string element, std::string subelement, const double* rgb);
bool setElementColor(std::string element, std::string subelement, std::string SUBsubsubelement, const double* rgb);
bool setJSMItem(std::string item, std::string value);
bool setNodeText(pugi::xml_node node,std::string text);
bool setNodeButtonTextByMask(pugi::xml_node node,std::string text,std::string attribute);
bool setRootMenuAttribute(int MENU, std::string attribute,std::string value);
bool setRootMenuHeight(std::string val, int height);
//T
bool testExec(std::string command); //linuxcommon wrapper
//String////////////////////////////////////////////////////////////////
//c
std::string checkListofExec(std::vector<std::string> list);
std::string colorToString(const double *rgb);
//f
std::string fixHomieInclude(std::string includeLine);
//g
std::string getAttribute(pugi::xml_node node,std::string attribute);
std::string getElementText(std::string element);
std::string getElementText(std::string element, std::string subelement);
std::string getElementText(unsigned int whichOne, std::string element, std::string subelement);
std::string getElementText(std::string element, std::string subelement, std::string SUBsubsubelement);
std::string getElementAttribute(std::string element, std::string attribute);
std::string getElementAttribute(std::string element, std::string subelement, std::string attribute);
std::string getElementAttribute(std::string element, std::string subelement, std::string SUBsubsubelement, std::string attribute);
std::string getElementAttributeFromElementWithAttributeAndValue(std::string element, std::string attribOfEle, std::string value, std::string subelement, std::string attribute);
std::string getElementAttributeFromElementWithAttributeAndValueAndText(std::string element, std::string attribOfEle, std::string value, std::string subelement, std::string attribute,std::string text);
std::string getElementAttribute(unsigned int whichElement,std::string element, std::string subelement, std::string attribute);
std::string getElementAttribute(unsigned int whichElement,std::string element, std::string attribute);
std::string getElementAttribute(unsigned int whichElement,std::string element,unsigned int whichItem, std::string subelement, std::string attribute);
std::string getEQUALvalue(std::string INTERNAL_LINE);
std::string getFirstColor(std::string element, std::string subelement);
std::string getItemText(pugi::xml_node node);
std::string getJSMItem(std::string item);
std::string getMenuAttribute(std::string MENU, std::string attribute);
std::string getMenuAttribute(int MENU, int subitem, std::string element, std::string attribute);
std::string getLayoutThing(std::string attribute,std::string vaule1,std::string value2,std::string value3,std::string layout);
std::string getPanelButtonIcon();
std::string getRootMenuAttribute(int MENU, std::string attribute);
std::string getSecondColor(std::string element, std::string subelement);
std::string getSmartHoriz(std::string layout);
std::string getSmartVert(std::string layout);
std::string getSmartLayout();
//h
std::string homePath();
std::string horizontalORvertical(int horizontalValue, int verticalValue);
//j
std::string joinColors(const double* rgb, const double* rgb2);
//m
std::string makeTempName(std::string filename);
std::string makeNOTtemp(std::string filename);
std::string menuButtonText(pugi::xml_node node);
//s
std::string splitColor(unsigned int first_or_second, std::string HTMLcolor);
//t
std::string terminal(std::string terminal);//linuxcommon wrapper
//const char*///////////////////////////////////////////////////////////
const char* convert(double num);
//unsigned int//////////////////////////////////////////////////////////
//c
unsigned int convert(const char* num);
unsigned int currentPanel();
//e
unsigned int elementCounter(std::string element);
//f
unsigned int flCOLOR(std::string color, unsigned int &c);//linuxcommon wrapper
unsigned int flCOLOR(std::string color);//linuxcommon wrapper
//g
unsigned int getActiveBackground(unsigned int c,std::string element);
unsigned int getActiveForeground(unsigned int c,std::string element);
unsigned int getBackground(unsigned int c,std::string element);
unsigned int getFontColor(unsigned int c,std::string element);
unsigned int getFontColor(unsigned int c,std::string element);
unsigned int getElementInt(std::string element);
unsigned int getElementInt(std::string element, std::string subelement);
unsigned int getElementInt(std::string element, std::string subelement, std::string SUBsubsubelement);
//n
unsigned int numPanels();
//s
unsigned int splitColor(std::string color, int one_or_two);
unsigned int switch_panel(Fl_Menu_Item *o);
//int///////////////////////////////////////////////////////////////////
int addMenuItem(Fl_Browser* root_menu, Fl_Input* add_label, Fl_Input* add_icon, Fl_Input* add_input, Fl_Input* add_tooltip, Fl_Check_Button* add_button, std::string result);
int addMenuAttrib(int whichMenu,std::string element,std::string attribute,const char *value);
int getIntAttribute(std::string element, std::string attribute);
int getIntAttribute(std::string element, std::string subelement, std::string attribute);
int newStyle();
int JWMversion();
int whichAlign(std::string align);
//float/////////////////////////////////////////////////////////////////
float getElementFloat(std::string element);
float getElementFloat(std::string element, std::string subelement);
float getElementFloat(std::string element, std::string subelement, std::string SUBsubsubelement);
float getOpacity(std::string element);
//const double* getBoxColor(Fl_Box*o);
//Vector////////////////////////////////////////////////////////////////
std::vector<std::string> AnythingVector(std::string element);
std::vector<std::string> IconPaths();
std::vector<std::string> Includes();
std::vector<std::string> XDGautostart();
std::vector<std::string> zoneSubdir(std::string thisDIR);
std::vector<std::string> zoneVector();
//void//////////////////////////////////////////////////////////////////
//A
void addCursorsToBrowser(Fl_Browser *o);
//C
void cancel();
void createElement(std::string element,std::string text);
void changeElementText(std::string element,std::string text,std::string NEWTEXT);
//D
void debug_out(std::string msg);
void deletePanelItem(int whichElement);
void deleteShortcut(std::string program);
//E
void errorOUT(std::string msg);
//G
void getShortcuts(Fl_Browser *o);
//L
void listAutostartXDG(Fl_Browser *o);
//M
void moveUp(int whichone);
void moveDown(int whichone);
//P
void populateDesc(Fl_Browser *o);
void populateOptions(Fl_Browser *o);
void populateApps(Fl_Browser *o);
//Q
void quit();
//R
void removeElement(unsigned int whichMainElement, std::string element,std::string subelement,std::string text);
void removeElement(unsigned int whichMainElement, std::string element,std::string subelement);
void removeElement(unsigned int whichMainElement, std::string element);
void removeElement(std::string element,std::string text);
void removeElementCompare2Attr(std::string element, std::string attribute, std::string value, std::string attribute2, std::string value2,std::string text);
void removeXDGautostart(bool NOT, bool ONLY, bool DE, std::string filename, std::string env);
//S
void setRootMenuAttribute(std::string menustring ,std::string attribute,std::string value);
//U
void under_mouse(Fl_Window *o);
//pugixml/////////////////////////////////////////////////////////////
//a
pugi::xml_node addNextSubelement(std::string element);
pugi::xml_node addNode(unsigned int whichElement,std::string element, std::string subelement);
//c
pugi::xml_node checkIncludes(unsigned int whichOne,std::string element);
pugi::xml_node checkIncludes(std::string element);
pugi::xml_node checkIncludes(std::string element,std::string subelement);
pugi::xml_node checkIncludes(std::string element,std::string subelement,std::string SUBsubelement);
pugi::xml_node compareNode(std::string element, std::string attribute, std::string value, std::string attribute2, std::string value2,std::string text);
//g
pugi::xml_node getCurrentTrayNode();
pugi::xml_node getLastSubNode(unsigned int whichElement,std::string element, std::string subelement);
pugi::xml_node getMenu(std::string text);
pugi::xml_node getMenu(int whichMenu);
pugi::xml_node getMenuButtonByMask(std::string text,int item);
pugi::xml_node getNode(unsigned int whichElement,std::string element,unsigned int whichNODE);
pugi::xml_node getNode(unsigned int whichElement,std::string element,unsigned int whichNODE, std::string subelement);
pugi::xml_node getRootMenu(std::string text);
pugi::xml_node getSubNode(unsigned int whichElement,std::string element,unsigned int whichSubElement, std::string subelement);
pugi::xml_node getTraySubElement(unsigned int whichElement);
//p
pugi::xml_node parseNodes(unsigned int whichElement,std::string element);
//variables/////////////////////////////////////////////////////////////
#endif
