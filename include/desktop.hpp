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
 
/**
 * @file desktop.hpp
 * @author Israel Dahl
 * @date 2015-2017
 *
 * @brief Functions for modifying desktop settings
 *
 */
#ifndef desktop_hpp
#define desktop_hpp
//std things
#include <libintl.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
//My stuff
#include "jwmrc.hpp"
#include "fltkfunctions.hpp"
//FLTK
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Value_Input.H>
class JSM_Desktop : public FLTK_FUNCTIONS
{
	public:
//void//////////////////////////////////////////////////////////////////

//A
 /** Run background, background1 and background2*/
		void allBGS(Fl_Box* Image, Fl_Box* Color1,Fl_Box* Color2, std::string choice, unsigned int num, Fl_Input *in);

//B
 /** Set the background image of an Fl_Box
  * @param o The Fl_Box
  * @param thisBG The background Image filename you send in
  * */
		void background(Fl_Box*o,std::string thisBG,unsigned int bgnum);
 /** Set the background color of an Fl_Box
  * @param o The Fl_Box
  * @param thisBG The background COLOR (HTML, or X11) you send in
  * */
		void background1(Fl_Box*o,std::string thisBG,unsigned int bgnum);
 /** Set the background color of an Fl_Box
  * @param o The Fl_Box
  * @param thisBG The background COLOR (HTML, or X11) you send in
  * */
		void background2(Fl_Box*o,std::string thisBG,unsigned int bgnum);
/** Open a file dialog to pick an image
  * @param background_displayer_thingie The Fl_Box with an image
  * @param current_bg the output showing the filename/type
  * @param color_display1 the single color box (to hide)
  * @param color_display2 the second color box (to hide)
  * */
		void bg_chooser_cb(Fl_Box *background_displayer_thingie,Fl_Output *current_bg,Fl_Box *color_display1,Fl_Box *color_display2,unsigned int bgnum);
/** Get the filename OR display text describing the background type
  * @param o The ouput for the background name
  * @param thisBG The background (file,solid,gradient,command,etc...)
  * */
		void bg_name(Fl_Output *o,std::string thisBG,unsigned int bgnum);

//N
/** set value for the number of desktops wide or high then make sure it is at least 1 If there are more than 1 each turn on the check button
 * @param whichone the attribute to set (width,height)
 * @param value The integer value for the attribute
 * @param num_desktop_w the output for the integer width
 * @param num_desktop_h output for the integer height
 * @param check the checkbox to toggle if multiple desktops exist/do not exist
 */
		void num_desktop_wh_cb(std::string whichone, int value,Fl_Value_Input* num_desktop_w,Fl_Value_Input* num_desktop_h, Fl_Check_Button* check);

//O
/** Choose a single color and save it to the file
 * @param color_display1 the box to color
 * @param color_display2 (hide this)
 * @param background_displayer_thingie (hide this)
 * @param current_bg set this to match the current background type
 */
		void one_color(Fl_Box *color_display1,Fl_Box *color_display2,Fl_Box *background_displayer_thingie,Fl_Output *current_bg,unsigned int bgnum);

//S
/** Set the background of the filemanager to match the jwmrc
 * @param type The type of background (solid,gradient,image...)
 * @param wallpaper the actual content of what the type displays
 */
		void setFMBackground(std::string type,std::string wallpaper);
/** create an SVG file of a color/colors and then set it as the background
 * @param color the color to turn into a solid svg, or gradient
 */
		void svgGradient(std::string color,unsigned int bgnum);

//T
/** Choose a two colors and save it to the file
 * @param color_display1 set this to the first color
 * @param color_display2 set this to the second color
 * @param background_displayer_thingie (hide this)
 * @param current_bg set this to match the current background type
 */
		void two_color(Fl_Box *color_display1,Fl_Box *color_display2,Fl_Box *background_displayer_thingie,Fl_Output *current_bg,unsigned int bgnum);

//U
/** Toggle the multiple desktops... if we are using them,
 * make it so we are not!
 * If we are not using them, add one to the right
 * @param num_desktop_w integer for how many desktops wide
 * @param num_desktop_h integer for how many desktops high
 */
		void useMultipleDesktops(Fl_Value_Input *num_desktop_w,Fl_Value_Input *num_desktop_h);


///bool//////////////////////////////////////////////////////////////////

//F
/** check if the default filemanager is running*/
		bool filemanagerRunning();
/** check a specific filemanager to see if it is running
 * @param filemanagerToCheck the filemanager to check
 */
		bool filemanagerRunning(std::string filemanagerToCheck);
/** open the filemanager's preferences dialog*/
		bool filemanagerPreferences();

//I
/** check to see if a filemanager is running*/
		bool icons_on_desktop();
/** a better function... just check if the filemanager is running */
		bool isIconsOnDesktop();

//M
/** check to see if multiple desktops exist*/
		bool multipleDesktops();

//R
/** get rid of the filemanager that is running*/
		bool removeIconsOnDesktop();

//S
/** set the background in the jwmrc, and possibly filemanager
 * @param type The type of background (solid,gradient,image,etc..)
 * @param result the background to set
 */
		bool setBackground(std::string type,std::string result,unsigned int bgnum);
/** make the desktop handled by a filemanager*/
		bool setIconsOnDesktop();

//U
/** Toggle the icons on the desktop
 * @param background_displayer_thingie used to redraw the background image for the user interface
 * @param thisBG the image to use
 */
		bool use_icons_on_desktop(Fl_Box *background_displayer_thingie,std::string thisBG);


///string////////////////////////////////////////////////////////////////
/** get the desktop background string from JWM*/
		std::string getBackground();
/** Figure out which filemanager is running*/
		std::string whichFileManagerRunning();
/** find the default filemanager from xdg-mime, or pick the first in the list*/
		std::string whichFileManager();
/** get the filemanager's background*/
		std::string getFMBackground();
/** get specific desktop background */
		std::string getBackground(unsigned int whichOne);


///vector////////////////////////////////////////////////////////////////
/** my list of filemanagers I currently support in vector<string> format*/
		std::vector<std::string> ListFileManagers();
};
#endif
