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
// generated by Fast Light User Interface Designer (fluid) version 1.0303

#ifndef jwm_menu_h
#define jwm_menu_h
#include <FL/Fl.H>
#include <libintl.h>
#include <FL/Fl_File_Chooser.H>
#include <string>
#include <stdlib.h>
#include <iostream>
#include "../include/jwmrc.hpp"
#include <FL/Fl_Select_Browser.H>
#include "../include/ui.hpp"
#include "../include/menu.hpp"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>

class MenuUI : public JSM_Menu {
public:
  int menuItemLineNumber; int JWMVERSION;int ROOTMENU;bool SUBMENU;int SUBSUB; 
  Fl_Double_Window* add_a_menu();
  Fl_Browser *list_browser;
  Fl_Input *new_menu_label;
  Fl_Slider *menu_height;
private:
  inline void cb_menu_height_i(Fl_Slider*, void*);
  static void cb_menu_height(Fl_Slider*, void*);
public:
  Fl_Check_Button *islabeled_button;
private:
  inline void cb_OK_i(Fl_Button*, void*);
  static void cb_OK(Fl_Button*, void*);
public:
  Fl_Value_Input *height_input;
private:
  inline void cb_height_input_i(Fl_Value_Input*, void*);
  static void cb_height_input(Fl_Value_Input*, void*);
public:
  Fl_Double_Window* add_window();
  Fl_Double_Window *adding_win;
  static unsigned char menu_Item_i18n_done;
  static Fl_Menu_Item menu_Item[];
private:
  inline void cb_Program_i(Fl_Menu_*, void*);
  static void cb_Program(Fl_Menu_*, void*);
  inline void cb_Restart_i(Fl_Menu_*, void*);
  static void cb_Restart(Fl_Menu_*, void*);
  inline void cb_Exit_i(Fl_Menu_*, void*);
  static void cb_Exit(Fl_Menu_*, void*);
  inline void cb_Separator_i(Fl_Menu_*, void*);
  static void cb_Separator(Fl_Menu_*, void*);
  inline void cb_Include_i(Fl_Menu_*, void*);
  static void cb_Include(Fl_Menu_*, void*);
  inline void cb_Desktops_i(Fl_Menu_*, void*);
  static void cb_Desktops(Fl_Menu_*, void*);
  inline void cb_SendTo_i(Fl_Menu_*, void*);
  static void cb_SendTo(Fl_Menu_*, void*);
  inline void cb_Stick_i(Fl_Menu_*, void*);
  static void cb_Stick(Fl_Menu_*, void*);
  inline void cb_Maximize_i(Fl_Menu_*, void*);
  static void cb_Maximize(Fl_Menu_*, void*);
  inline void cb_Minimize_i(Fl_Menu_*, void*);
  static void cb_Minimize(Fl_Menu_*, void*);
  inline void cb_Shade_i(Fl_Menu_*, void*);
  static void cb_Shade(Fl_Menu_*, void*);
  inline void cb_Move_i(Fl_Menu_*, void*);
  static void cb_Move(Fl_Menu_*, void*);
  inline void cb_Resize_i(Fl_Menu_*, void*);
  static void cb_Resize(Fl_Menu_*, void*);
  inline void cb_Kill_i(Fl_Menu_*, void*);
  static void cb_Kill(Fl_Menu_*, void*);
  inline void cb_Close_i(Fl_Menu_*, void*);
  static void cb_Close(Fl_Menu_*, void*);
  inline void cb_Menu_i(Fl_Menu_*, void*);
  static void cb_Menu(Fl_Menu_*, void*);
  inline void cb_Dynamic_i(Fl_Menu_*, void*);
  static void cb_Dynamic(Fl_Menu_*, void*);
public:
  Fl_Output *item_display;
  Fl_Input *add_icon;
  Fl_Input *add_label;
  Fl_Input *add_input;
  Fl_Input *add_tooltip;
private:
  inline void cb_OK1_i(Fl_Button*, void*);
  static void cb_OK1(Fl_Button*, void*);
public:
  Fl_Button *add_icon_button;
private:
  inline void cb_add_icon_button_i(Fl_Button*, void*);
  static void cb_add_icon_button(Fl_Button*, void*);
public:
  Fl_Button *add_prog_button;
private:
  inline void cb_add_prog_button_i(Fl_Button*, void*);
  static void cb_add_prog_button(Fl_Button*, void*);
public:
  Fl_Check_Button *add_button;
  Fl_Double_Window* conf_item_window();
  Fl_Double_Window *config_item_win;
  Fl_Input *item_prog_icon;
  Fl_Input *item_prog_label;
  Fl_Input *item_prog_input;
  Fl_Check_Button *item_conf_button;
  Fl_Button *item_prog_button;
private:
  inline void cb_item_prog_button_i(Fl_Button*, void*);
  static void cb_item_prog_button(Fl_Button*, void*);
  inline void cb_OK2_i(Fl_Button*, void*);
  static void cb_OK2(Fl_Button*, void*);
public:
  Fl_Button *item_icon_button;
private:
  inline void cb_item_icon_button_i(Fl_Button*, void*);
  static void cb_item_icon_button(Fl_Button*, void*);
public:
  Fl_Double_Window* conf_window();
  Fl_Double_Window *config_flwin;
  Fl_Input *prog_label;
private:
  inline void cb_OK3_i(Fl_Button*, void*);
  static void cb_OK3(Fl_Button*, void*);
public:
  Fl_Input *prog_root;
  Fl_Check_Button *menu_root_labeled;
  Fl_Slider *menu_height_slider;
private:
  inline void cb_menu_height_slider_i(Fl_Slider*, void*);
  static void cb_menu_height_slider(Fl_Slider*, void*);
public:
  Fl_Value_Input *menu_height_input;
private:
  inline void cb_menu_height_input_i(Fl_Value_Input*, void*);
  static void cb_menu_height_input(Fl_Value_Input*, void*);
public:
  Fl_Double_Window* configure_include();
  Fl_Double_Window *include_win;
  Fl_Input *include_input;
private:
  inline void cb_OK4_i(Fl_Button*, void*);
  static void cb_OK4(Fl_Button*, void*);
public:
  Fl_Input *old_include_input;
  Fl_Input *include_input_menu;
  Fl_Double_Window* make_window(std::string INPUTmenu);
  Fl_Double_Window *menu_window;
private:
  inline void cb__i(Fl_Button*, void*);
  static void cb_(Fl_Button*, void*);
public:
  Fl_Button *minus_root;
private:
  inline void cb_minus_root_i(Fl_Button*, void*);
  static void cb_minus_root(Fl_Button*, void*);
public:
  Fl_Browser *menuElement;
private:
  inline void cb_menuElement_i(Fl_Browser*, void*);
  static void cb_menuElement(Fl_Browser*, void*);
  inline void cb_1_i(Fl_Button*, void*);
  static void cb_1(Fl_Button*, void*);
public:
  Fl_Button *minus_element;
private:
  inline void cb_minus_element_i(Fl_Button*, void*);
  static void cb_minus_element(Fl_Button*, void*);
public:
  Fl_Browser *menuElementText;
private:
  inline void cb_menuElementText_i(Fl_Browser*, void*);
  static void cb_menuElementText(Fl_Browser*, void*);
public:
  Fl_Browser *root_menu;
private:
  inline void cb_root_menu_i(Fl_Browser*, void*);
  static void cb_root_menu(Fl_Browser*, void*);
public:
  Fl_Button *config_something;
private:
  inline void cb_config_something_i(Fl_Button*, void*);
  static void cb_config_something(Fl_Button*, void*);
public:
  Fl_Button *menu_bg_color;
private:
  inline void cb_menu_bg_color_i(Fl_Button*, void*);
  static void cb_menu_bg_color(Fl_Button*, void*);
public:
  Fl_Button *menu_bg_color_a;
private:
  inline void cb_menu_bg_color_a_i(Fl_Button*, void*);
  static void cb_menu_bg_color_a(Fl_Button*, void*);
public:
  Fl_Button *menu_font_color;
private:
  inline void cb_menu_font_color_i(Fl_Button*, void*);
  static void cb_menu_font_color(Fl_Button*, void*);
public:
  Fl_Slider *o_menu_slider;
private:
  inline void cb_o_menu_slider_i(Fl_Slider*, void*);
  static void cb_o_menu_slider(Fl_Slider*, void*);
public:
  Fl_Value_Input *o_menu_slider_v;
private:
  inline void cb_o_menu_slider_v_i(Fl_Value_Input*, void*);
  static void cb_o_menu_slider_v(Fl_Value_Input*, void*);
public:
  Fl_Button *menu_font_a;
private:
  inline void cb_menu_font_a_i(Fl_Button*, void*);
  static void cb_menu_font_a(Fl_Button*, void*);
  static unsigned char menu_decorations_i18n_done;
  static Fl_Menu_Item menu_decorations[];
  inline void cb_flat_i(Fl_Menu_*, void*);
  static void cb_flat(Fl_Menu_*, void*);
  inline void cb_motif_i(Fl_Menu_*, void*);
  static void cb_motif(Fl_Menu_*, void*);
public:
  Fl_Button *menu_outline;
private:
  inline void cb_menu_outline_i(Fl_Button*, void*);
  static void cb_menu_outline(Fl_Button*, void*);
public:
  Fl_Output *menu_deco;
private:
  inline void cb_Cancel_i(Fl_Button*, void*);
  static void cb_Cancel(Fl_Button*, void*);
public:
  Fl_Button *save_button;
private:
  inline void cb_save_button_i(Fl_Button*, void*);
  static void cb_save_button(Fl_Button*, void*);
public:
  Fl_Double_Window* nada_window();
  Fl_Double_Window *nada_win;
private:
  inline void cb_nada_win_i(Fl_Double_Window*, void*);
  static void cb_nada_win(Fl_Double_Window*, void*);
  inline void cb_Nothing_i(Fl_Button*, void*);
  static void cb_Nothing(Fl_Button*, void*);
public:
  Fl_Double_Window* submenu_window();
  Fl_Double_Window *subwin;
  Fl_Browser *submenu_items_browser;
private:
  inline void cb_submenu_items_browser_i(Fl_Browser*, void*);
  static void cb_submenu_items_browser(Fl_Browser*, void*);
public:
  Fl_Browser *submenu_items_value;
private:
  inline void cb_submenu_items_value_i(Fl_Browser*, void*);
  static void cb_submenu_items_value(Fl_Browser*, void*);
public:
  Fl_Button *config_sub;
private:
  inline void cb_config_sub_i(Fl_Button*, void*);
  static void cb_config_sub(Fl_Button*, void*);
  inline void cb_OK5_i(Fl_Button*, void*);
  static void cb_OK5(Fl_Button*, void*);
  inline void cb_2_i(Fl_Button*, void*);
  static void cb_2(Fl_Button*, void*);
  inline void cb_3_i(Fl_Button*, void*);
  static void cb_3(Fl_Button*, void*);
public:
  void add_an_item();
  void add_cb(int whichOne);
  void change_include();
  void choose_menu(std::string menu);
  void configure_item();
  void configure_submenu_item();
  void edit_a_menu();
  bool edit_a_submenu_item();
  void edit_an_item();
  void remove_an_item();
  void remove_a_menu();
  int save_cb();
  void select_sent_in(std::string thatMenu);
  void get_root_attrib(Fl_Input *o,std::string attribute);
  void get_root_height(Fl_Valuator *o);
  void mod_root_menu();
};
#endif
