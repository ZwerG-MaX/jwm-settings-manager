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

#include <libintl.h>
#include "jwm-menu.h"

void MenuUI::cb_OK_i(Fl_Button*, void*) {
  if(!checkFlBrowserItem(list_browser)){return;}
unsigned int line = list_browser->value();
const char* val = list_browser->text(line);
if (val==NULL){return;}
std::string menu = val;
addRoot(menu);
const char* menuLabel = new_menu_label->value();
if (menuLabel!=NULL){
  unsigned int islabeled = islabeled_button->value();
  //change label
  setRootMenuAttribute(val,"label",menuLabel);
  if(islabeled==0){setRootMenuAttribute(val,"labeled","true");}
  else{setRootMenuAttribute(val,"labeled","true");}
}
int height = menu_height->value();
setRootMenuHeight(val,height);
}
void MenuUI::cb_OK(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_OK_i(o,v);
}

void MenuUI::cb_add_prog_button_i(Fl_Button*, void*) {
  std::string result =choose_a_program();
if(result.compare("")!=0){add_input->value(result.c_str());};
}
void MenuUI::cb_add_prog_button(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_add_prog_button_i(o,v);
}

#include <FL/Fl_Image.H>
static const unsigned char idata_gear16[] =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,148,0,255,0,252,0,252,0,255,0,146,0,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,0,48,0,3,0,0,0,2,0,149,
0,255,0,255,0,255,0,255,0,147,0,2,0,0,0,2,0,24,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,20,0,151,0,218,0,79,0,0,0,2,0,149,0,255,0,255,0,255,0,255,0,147,0,1,0,0,0,
69,0,193,0,96,0,2,0,0,0,0,0,0,0,0,0,0,0,22,0,156,0,251,0,255,0,221,0,75,0,22,0,
169,0,255,0,255,0,255,0,255,0,167,0,22,0,73,0,217,0,255,0,231,0,89,0,2,0,0,0,0,
0,0,0,24,0,162,0,252,0,255,0,255,0,255,0,224,0,199,0,245,0,255,0,255,0,255,0,
255,0,245,0,200,0,225,0,255,0,255,0,255,0,228,0,85,0,2,0,0,0,0,0,46,0,212,0,255,
0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,
0,255,0,255,0,255,0,255,0,196,0,25,0,0,0,0,0,0,0,71,0,219,0,255,0,255,0,255,0,
255,0,255,0,246,0,209,0,172,0,172,0,209,0,246,0,255,0,255,0,255,0,255,0,255,0,
223,0,83,0,3,0,0,0,0,0,0,0,0,0,76,0,227,0,255,0,255,0,255,0,210,0,95,0,25,0,9,0,
10,0,25,0,95,0,210,0,255,0,255,0,255,0,225,0,77,0,1,0,0,0,0,0,2,0,2,0,0,0,23,0,
203,0,255,0,255,0,210,0,54,0,0,0,0,0,0,0,0,0,0,0,0,0,54,0,210,0,255,0,255,0,202,
0,23,0,0,0,2,0,2,0,147,0,149,0,148,0,169,0,246,0,255,0,246,0,94,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,94,0,246,0,255,0,246,0,169,0,148,0,149,0,147,0,254,0,255,
0,255,0,255,0,255,0,255,0,207,0,24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,207,
0,255,0,255,0,255,0,255,0,255,0,254,0,252,0,255,0,255,0,255,0,255,0,255,0,170,
0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,170,0,255,0,255,0,255,0,255,0,255,0,
252,0,252,0,255,0,255,0,255,0,255,0,255,0,170,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,9,0,170,0,255,0,255,0,255,0,255,0,255,0,252,0,254,0,255,0,255,0,255,0,255,
0,255,0,207,0,24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,207,0,255,0,255,0,255,
0,255,0,255,0,254,0,144,0,146,0,144,0,166,0,245,0,255,0,246,0,94,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,94,0,246,0,255,0,246,0,167,0,144,0,146,0,144,0,1,0,1,0,
0,0,36,0,220,0,255,0,255,0,210,0,54,0,0,0,0,0,0,0,0,0,0,0,0,0,54,0,210,0,255,
0,255,0,193,0,20,0,0,0,1,0,1,0,0,0,0,0,19,0,148,0,249,0,255,0,255,0,255,0,210,
0,95,0,25,0,9,0,10,0,25,0,95,0,210,0,255,0,255,0,255,0,187,0,26,0,0,0,0,0,0,0,
0,0,24,0,156,0,250,0,255,0,255,0,255,0,255,0,255,0,246,0,209,0,172,0,172,0,
209,0,246,0,255,0,255,0,255,0,255,0,253,0,162,0,23,0,0,0,0,0,0,0,96,0,246,0,255,
0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,
0,255,0,255,0,255,0,253,0,142,0,6,0,0,0,0,0,22,0,158,0,252,0,255,0,255,0,250,
0,183,0,191,0,246,0,255,0,255,0,255,0,255,0,244,0,218,0,247,0,255,0,255,0,255,
0,229,0,90,0,2,0,0,0,0,0,0,0,23,0,163,0,253,0,251,0,156,0,22,0,20,0,169,0,255,
0,255,0,255,0,255,0,166,0,33,0,142,0,249,0,255,0,225,0,85,0,2,0,0,0,0,0,0,0,0,
0,0,0,26,0,164,0,149,0,20,0,0,0,2,0,149,0,255,0,255,0,255,0,255,0,147,0,0,0,
16,0,149,0,216,0,80,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,0,13,0,0,0,0,0,2,0,
149,0,255,0,255,0,255,0,255,0,147,0,2,0,0,0,20,0,46,0,2,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,148,0,255,0,252,0,252,0,255,0,146,0,2,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0};
static Fl_RGB_Image image_gear16(idata_gear16, 24, 24, 2, 0);

void MenuUI::cb_OK1_i(Fl_Button*, void*) {
  int resultant = save_cb();
if(resultant == 0){adding_win->hide();};
}
void MenuUI::cb_OK1(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_OK1_i(o,v);
}

void MenuUI::cb_add_icon_button_i(Fl_Button* o, void*) {
  std::string icon=choose_an_icon();
if(icon.compare("")!=0){
  add_icon->value(icon.c_str());
  makeWidgetIcon(icon,o,48);
};
}
void MenuUI::cb_add_icon_button(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_add_icon_button_i(o,v);
}

void MenuUI::cb_Program_i(Fl_Menu_*, void*) {
  add_cb(0);
}
void MenuUI::cb_Program(Fl_Menu_* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_Program_i(o,v);
}

void MenuUI::cb_Restart_i(Fl_Menu_*, void*) {
  add_cb(1);
}
void MenuUI::cb_Restart(Fl_Menu_* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_Restart_i(o,v);
}

void MenuUI::cb_Exit_i(Fl_Menu_*, void*) {
  add_cb(2);
}
void MenuUI::cb_Exit(Fl_Menu_* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_Exit_i(o,v);
}

void MenuUI::cb_Separator_i(Fl_Menu_*, void*) {
  add_cb(3);
}
void MenuUI::cb_Separator(Fl_Menu_* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_Separator_i(o,v);
}

void MenuUI::cb_Include_i(Fl_Menu_*, void*) {
  add_cb(4);
}
void MenuUI::cb_Include(Fl_Menu_* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_Include_i(o,v);
}

void MenuUI::cb_Desktops_i(Fl_Menu_*, void*) {
  add_cb(5);
}
void MenuUI::cb_Desktops(Fl_Menu_* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_Desktops_i(o,v);
}

void MenuUI::cb_SendTo_i(Fl_Menu_*, void*) {
  add_cb(6);
}
void MenuUI::cb_SendTo(Fl_Menu_* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_SendTo_i(o,v);
}

void MenuUI::cb_Stick_i(Fl_Menu_*, void*) {
  add_cb(7);
}
void MenuUI::cb_Stick(Fl_Menu_* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_Stick_i(o,v);
}

void MenuUI::cb_Maximize_i(Fl_Menu_*, void*) {
  add_cb(8);
}
void MenuUI::cb_Maximize(Fl_Menu_* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_Maximize_i(o,v);
}

void MenuUI::cb_Minimize_i(Fl_Menu_*, void*) {
  add_cb(9);
}
void MenuUI::cb_Minimize(Fl_Menu_* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_Minimize_i(o,v);
}

void MenuUI::cb_Shade_i(Fl_Menu_*, void*) {
  add_cb(10);
}
void MenuUI::cb_Shade(Fl_Menu_* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_Shade_i(o,v);
}

void MenuUI::cb_Move_i(Fl_Menu_*, void*) {
  add_cb(11);
}
void MenuUI::cb_Move(Fl_Menu_* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_Move_i(o,v);
}

void MenuUI::cb_Resize_i(Fl_Menu_*, void*) {
  add_cb(12);
}
void MenuUI::cb_Resize(Fl_Menu_* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_Resize_i(o,v);
}

void MenuUI::cb_Kill_i(Fl_Menu_*, void*) {
  add_cb(13);
}
void MenuUI::cb_Kill(Fl_Menu_* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_Kill_i(o,v);
}

void MenuUI::cb_Close_i(Fl_Menu_*, void*) {
  add_cb(14);
}
void MenuUI::cb_Close(Fl_Menu_* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_Close_i(o,v);
}

void MenuUI::cb_Menu_i(Fl_Menu_*, void*) {
  add_cb(15);
}
void MenuUI::cb_Menu(Fl_Menu_* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_Menu_i(o,v);
}

unsigned char MenuUI::menu_Item_i18n_done = 0;
Fl_Menu_Item MenuUI::menu_Item[] = {
 {"Program", 0,  (Fl_Callback*)MenuUI::cb_Program, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Restart", 0,  (Fl_Callback*)MenuUI::cb_Restart, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Exit", 0,  (Fl_Callback*)MenuUI::cb_Exit, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Separator", 0,  (Fl_Callback*)MenuUI::cb_Separator, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Include", 0,  (Fl_Callback*)MenuUI::cb_Include, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Desktops", 0,  (Fl_Callback*)MenuUI::cb_Desktops, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"SendTo", 0,  (Fl_Callback*)MenuUI::cb_SendTo, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Stick", 0,  (Fl_Callback*)MenuUI::cb_Stick, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Maximize", 0,  (Fl_Callback*)MenuUI::cb_Maximize, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Minimize", 0,  (Fl_Callback*)MenuUI::cb_Minimize, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Shade", 0,  (Fl_Callback*)MenuUI::cb_Shade, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Move", 0,  (Fl_Callback*)MenuUI::cb_Move, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Resize", 0,  (Fl_Callback*)MenuUI::cb_Resize, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Kill", 0,  (Fl_Callback*)MenuUI::cb_Kill, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Close", 0,  (Fl_Callback*)MenuUI::cb_Close, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Menu", 0,  (Fl_Callback*)MenuUI::cb_Menu, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0}
};

void MenuUI::cb_item_prog_button_i(Fl_Button*, void*) {
  std::string result =choose_a_program();
if(result.compare("")!=0){
  item_prog_input->value(result.c_str());
  item_prog_input->redraw();
};
}
void MenuUI::cb_item_prog_button(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_item_prog_button_i(o,v);
}

void MenuUI::cb_OK2_i(Fl_Button*, void*) {
  configure_item();
config_flwin->hide();
}
void MenuUI::cb_OK2(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_OK2_i(o,v);
}

void MenuUI::cb_item_icon_button_i(Fl_Button* o, void*) {
  std::string icon=choose_an_icon();
if(icon.compare("")!=0){
  item_prog_icon->value(icon.c_str());
  makeWidgetIcon(icon,o,48);
};
}
void MenuUI::cb_item_icon_button(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_item_icon_button_i(o,v);
}

void MenuUI::cb_prog_button_i(Fl_Button*, void*) {
  std::string result =choose_a_program();
if(result.compare("")!=0){
  prog_input->value(result.c_str());
  prog_input->redraw();
};
}
void MenuUI::cb_prog_button(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_prog_button_i(o,v);
}

void MenuUI::cb_OK3_i(Fl_Button*, void*) {
  configure_item();
config_flwin->hide();
}
void MenuUI::cb_OK3(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_OK3_i(o,v);
}

void MenuUI::cb_icon_button_i(Fl_Button* o, void*) {
  std::string icon=choose_an_icon();
if(icon.compare("")!=0){
  item_prog_icon->value(icon.c_str());
  makeWidgetIcon(icon,o,48);
};
}
void MenuUI::cb_icon_button(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_icon_button_i(o,v);
}

void MenuUI::cb_OK4_i(Fl_Button*, void*) {
  include_win->hide();
change_include();
}
void MenuUI::cb_OK4(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_OK4_i(o,v);
}

void MenuUI::cb__i(Fl_Button*, void*) {
  add_a_menu()->show();
}
void MenuUI::cb_(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->parent()->user_data()))->cb__i(o,v);
}

void MenuUI::cb_1_i(Fl_Button*, void*) {
  remove_a_menu();
}
void MenuUI::cb_1(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->parent()->user_data()))->cb_1_i(o,v);
}

#include <FL/Fl_Bitmap.H>
static const unsigned char idata_minus[] =
{0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,0,
0,0,0};
static Fl_Bitmap image_minus(idata_minus, 16, 16);

void MenuUI::cb_menuElement_i(Fl_Browser* o, void*) {
  int linenum = o->value();
menuElementText->select(linenum);
}
void MenuUI::cb_menuElement(Fl_Browser* o, void* v) {
  ((MenuUI*)(o->parent()->parent()->user_data()))->cb_menuElement_i(o,v);
}

void MenuUI::cb_2_i(Fl_Button*, void*) {
  add_an_item();
}
void MenuUI::cb_2(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->parent()->user_data()))->cb_2_i(o,v);
}

void MenuUI::cb_3_i(Fl_Button*, void*) {
  remove_an_item();
}
void MenuUI::cb_3(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->parent()->user_data()))->cb_3_i(o,v);
}

void MenuUI::cb_menuElementText_i(Fl_Browser* o, void*) {
  int linenum = o->value();
menuElement->select(linenum);
}
void MenuUI::cb_menuElementText(Fl_Browser* o, void* v) {
  ((MenuUI*)(o->parent()->parent()->user_data()))->cb_menuElementText_i(o,v);
}

void MenuUI::cb_4_i(Fl_Button*, void*) {
  if(checkFlBrowserItem(menuElementText)){edit_an_item();}
else{
  if(checkFlBrowserItem(menuElement)){edit_a_menu();}
  else if(checkFlBrowserItem(root_menu)){submenu_window()->show();}
};
}
void MenuUI::cb_4(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->parent()->user_data()))->cb_4_i(o,v);
}

void MenuUI::cb_Cancel_i(Fl_Button*, void*) {
  cancel();
}
void MenuUI::cb_Cancel(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->parent()->user_data()))->cb_Cancel_i(o,v);
}

void MenuUI::cb_save_button_i(Fl_Button*, void*) {
  saveChanges();
//showSettings();
}
void MenuUI::cb_save_button(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->parent()->user_data()))->cb_save_button_i(o,v);
}

void MenuUI::cb_root_menu_i(Fl_Browser* o, void*) {
  int line = o->value();
const char* menu = o->text(line);
if(menu != NULL){
  std::string MENU=menu;
  choose_menu(MENU);
}
else{std::cerr<<"Problem getting this menu"<<std::endl;};
}
void MenuUI::cb_root_menu(Fl_Browser* o, void* v) {
  ((MenuUI*)(o->parent()->parent()->user_data()))->cb_root_menu_i(o,v);
}

void MenuUI::cb_nada_win_i(Fl_Double_Window* o, void*) {
  o->hide();
}
void MenuUI::cb_nada_win(Fl_Double_Window* o, void* v) {
  ((MenuUI*)(o->user_data()))->cb_nada_win_i(o,v);
}

void MenuUI::cb_Nothing_i(Fl_Button*, void*) {
  nada_win->hide();
}
void MenuUI::cb_Nothing(Fl_Button* o, void* v) {
  ((MenuUI*)(o->parent()->user_data()))->cb_Nothing_i(o,v);
}

Fl_Double_Window* MenuUI::add_a_menu() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(280, 125, gettext("Add a Menu"));
    w = o;
    o->user_data((void*)(this));
    { Fl_Browser* o = list_browser = new Fl_Browser(5, 5, 95, 100, gettext("Menu"));
      list_browser->tooltip(gettext("Determine which buttons on the root window activate the menu. This is a list \
of integers specifying buttons. The default is 123. Multiple root menus may be\
 used by specifying different buttons to activate them. Valid values in this l\
ist are 0 to 9 and a to z. The usual mouse buttons are 1 for the left button, \
2 for the middle button, 3 for the right button, and 4 and 5 for the scroll wh\
eel. Therefore, accessing root menus that are assigned to buttons 0, 6, 7, 8, \
9, or a letter will typically require the use of a tray button or key binding."));
      list_browser->type(2);
      list_browser->box(FL_FLAT_BOX);
      list_browser->selection_color((Fl_Color)80);
      list_browser->align(Fl_Align(130));
      listMenus(o);
    } // Fl_Browser* list_browser
    { new_menu_label = new Fl_Input(105, 40, 120, 30, gettext("Label"));
      new_menu_label->tooltip(gettext("The label to display at the top of the menu, normally this is NOT shown"));
      new_menu_label->box(FL_FLAT_BOX);
      new_menu_label->align(Fl_Align(FL_ALIGN_RIGHT));
    } // Fl_Input* new_menu_label
    { menu_height = new Fl_Slider(105, 5, 120, 30, gettext("Height"));
      menu_height->tooltip(gettext("The height of each menu item in pixels 0 indicates that the height of the fon\
t will determine the height. The default is 0."));
      menu_height->type(1);
      menu_height->box(FL_GTK_DOWN_BOX);
      menu_height->color((Fl_Color)41);
      menu_height->maximum(45);
      menu_height->align(Fl_Align(FL_ALIGN_RIGHT));
    } // Fl_Slider* menu_height
    { islabeled_button = new Fl_Check_Button(110, 75, 25, 25, gettext("Labeled        "));
      islabeled_button->tooltip(gettext("Determines if a label appears at the top of the menu, this will have no effec\
t if the label is not set"));
      islabeled_button->box(FL_FLAT_BOX);
      islabeled_button->down_box(FL_GTK_DOWN_BOX);
    } // Fl_Check_Button* islabeled_button
    { Fl_Button* o = new Fl_Button(215, 95, 60, 25, gettext("OK"));
      o->box(FL_FLAT_BOX);
      o->color((Fl_Color)61);
      o->labelcolor(FL_BACKGROUND2_COLOR);
      o->callback((Fl_Callback*)cb_OK);
    } // Fl_Button* o
    startup(o);
    o->xclass("jsm-panel");
    o->end();
  } // Fl_Double_Window* o
  return w;
}

Fl_Double_Window* MenuUI::add_window() {
  { Fl_Double_Window* o = adding_win = new Fl_Double_Window(295, 160, gettext("Add an Item"));
    adding_win->user_data((void*)(this));
    { add_label = new Fl_Input(130, 65, 160, 25, gettext("Label"));
      add_label->box(FL_FLAT_BOX);
    } // Fl_Input* add_label
    { add_icon = new Fl_Input(130, 35, 160, 25, gettext("Icon"));
      add_icon->box(FL_FLAT_BOX);
    } // Fl_Input* add_icon
    { add_input = new Fl_Input(130, 95, 160, 25, gettext("Program"));
      add_input->box(FL_FLAT_BOX);
    } // Fl_Input* add_input
    { add_button = new Fl_Check_Button(5, 125, 90, 25, gettext("Confirm"));
      add_button->box(FL_FLAT_BOX);
      add_button->down_box(FL_GTK_DOWN_BOX);
    } // Fl_Check_Button* add_button
    { add_prog_button = new Fl_Button(5, 90, 30, 30);
      add_prog_button->box(FL_FLAT_BOX);
      add_prog_button->color((Fl_Color)23);
      add_prog_button->image(image_gear16);
      add_prog_button->callback((Fl_Callback*)cb_add_prog_button);
    } // Fl_Button* add_prog_button
    { Fl_Button* o = new Fl_Button(230, 130, 60, 25, gettext("OK"));
      o->box(FL_FLAT_BOX);
      o->color((Fl_Color)61);
      o->labelcolor(FL_BACKGROUND2_COLOR);
      o->callback((Fl_Callback*)cb_OK1);
    } // Fl_Button* o
    { add_icon_button = new Fl_Button(5, 35, 50, 50);
      add_icon_button->box(FL_FLAT_BOX);
      add_icon_button->color((Fl_Color)23);
      add_icon_button->callback((Fl_Callback*)cb_add_icon_button);
    } // Fl_Button* add_icon_button
    { Fl_Menu_Button* o = new Fl_Menu_Button(5, 5, 115, 25, gettext("Item to add"));
      o->box(FL_FLAT_BOX);
      o->color((Fl_Color)23);
      if (!menu_Item_i18n_done) {
        int i=0;
        for ( ; i<16; i++)
          if (menu_Item[i].label())
            menu_Item[i].label(gettext(menu_Item[i].label()));
        menu_Item_i18n_done = 1;
      }
      o->menu(menu_Item);
    } // Fl_Menu_Button* o
    { item_display = new Fl_Output(130, 5, 160, 25);
      item_display->box(FL_FLAT_BOX);
    } // Fl_Output* item_display
    startup(o);
    adding_win->xclass("jsm-panel");
    adding_win->end();
  } // Fl_Double_Window* adding_win
  return adding_win;
}

Fl_Double_Window* MenuUI::conf_item_window() {
  { Fl_Double_Window* o = config_item_win = new Fl_Double_Window(280, 125, gettext("Configure the Item"));
    config_item_win->user_data((void*)(this));
    { item_prog_icon = new Fl_Input(110, 5, 160, 25, gettext("Icon"));
      item_prog_icon->box(FL_FLAT_BOX);
    } // Fl_Input* item_prog_icon
    { item_prog_label = new Fl_Input(110, 35, 160, 25, gettext("Label"));
      item_prog_label->box(FL_FLAT_BOX);
    } // Fl_Input* item_prog_label
    { item_prog_input = new Fl_Input(110, 65, 160, 25, gettext("Program"));
      item_prog_input->box(FL_FLAT_BOX);
    } // Fl_Input* item_prog_input
    { item_conf_button = new Fl_Check_Button(5, 95, 90, 25, gettext("Confirm"));
      item_conf_button->box(FL_FLAT_BOX);
      item_conf_button->down_box(FL_GTK_DOWN_BOX);
    } // Fl_Check_Button* item_conf_button
    { item_prog_button = new Fl_Button(5, 60, 30, 30);
      item_prog_button->box(FL_FLAT_BOX);
      item_prog_button->color((Fl_Color)23);
      item_prog_button->image(image_gear16);
      item_prog_button->callback((Fl_Callback*)cb_item_prog_button);
    } // Fl_Button* item_prog_button
    { Fl_Button* o = new Fl_Button(210, 95, 60, 25, gettext("OK"));
      o->box(FL_FLAT_BOX);
      o->color((Fl_Color)61);
      o->labelcolor(FL_BACKGROUND2_COLOR);
      o->callback((Fl_Callback*)cb_OK2);
    } // Fl_Button* o
    { item_icon_button = new Fl_Button(5, 5, 50, 50);
      item_icon_button->box(FL_FLAT_BOX);
      item_icon_button->color((Fl_Color)23);
      item_icon_button->callback((Fl_Callback*)cb_item_icon_button);
    } // Fl_Button* item_icon_button
    startup(o);
    config_item_win->xclass("jsm-panel");
    config_item_win->end();
  } // Fl_Double_Window* config_item_win
  return config_item_win;
}

Fl_Double_Window* MenuUI::conf_window() {
  { Fl_Double_Window* o = config_flwin = new Fl_Double_Window(275, 130, gettext("Configure the Item"));
    config_flwin->user_data((void*)(this));
    { prog_icon = new Fl_Input(105, 5, 160, 25, gettext("Icon"));
      prog_icon->box(FL_FLAT_BOX);
    } // Fl_Input* prog_icon
    { prog_label = new Fl_Input(105, 35, 160, 25, gettext("Label"));
      prog_label->box(FL_FLAT_BOX);
    } // Fl_Input* prog_label
    { prog_input = new Fl_Input(105, 65, 160, 25, gettext("Program"));
      prog_input->box(FL_FLAT_BOX);
    } // Fl_Input* prog_input
    { conf_button = new Fl_Check_Button(5, 95, 90, 25, gettext("Confirm"));
      conf_button->box(FL_FLAT_BOX);
      conf_button->down_box(FL_GTK_DOWN_BOX);
    } // Fl_Check_Button* conf_button
    { prog_button = new Fl_Button(5, 60, 30, 30);
      prog_button->box(FL_FLAT_BOX);
      prog_button->color((Fl_Color)23);
      prog_button->image(image_gear16);
      prog_button->callback((Fl_Callback*)cb_prog_button);
    } // Fl_Button* prog_button
    { Fl_Button* o = new Fl_Button(205, 100, 60, 25, gettext("OK"));
      o->box(FL_FLAT_BOX);
      o->color((Fl_Color)61);
      o->labelcolor(FL_BACKGROUND2_COLOR);
      o->callback((Fl_Callback*)cb_OK3);
    } // Fl_Button* o
    { icon_button = new Fl_Button(5, 5, 50, 50);
      icon_button->box(FL_FLAT_BOX);
      icon_button->color((Fl_Color)23);
      icon_button->callback((Fl_Callback*)cb_icon_button);
    } // Fl_Button* icon_button
    startup(o);
    config_flwin->xclass("jsm-panel");
    config_flwin->end();
  } // Fl_Double_Window* config_flwin
  return config_flwin;
}

Fl_Double_Window* MenuUI::configure_include() {
  { Fl_Double_Window* o = include_win = new Fl_Double_Window(390, 45, gettext("Edit Include Item"));
    include_win->user_data((void*)(this));
    { include_input = new Fl_Input(70, 5, 245, 25, gettext("Include"));
      include_input->box(FL_FLAT_BOX);
    } // Fl_Input* include_input
    { Fl_Button* o = new Fl_Button(320, 5, 60, 25, gettext("OK"));
      o->box(FL_FLAT_BOX);
      o->color((Fl_Color)61);
      o->labelcolor(FL_BACKGROUND2_COLOR);
      o->callback((Fl_Callback*)cb_OK4);
    } // Fl_Button* o
    { old_include_input = new Fl_Input(70, 5, 245, 25);
      old_include_input->box(FL_FLAT_BOX);
      old_include_input->hide();
    } // Fl_Input* old_include_input
    { include_input_menu = new Fl_Input(0, 5, 40, 25);
      include_input_menu->box(FL_FLAT_BOX);
      include_input_menu->hide();
    } // Fl_Input* include_input_menu
    startup(o);
    include_win->end();
  } // Fl_Double_Window* include_win
  return include_win;
}

Fl_Double_Window* MenuUI::make_window(std::string INPUTmenu) {
  load();
  { Fl_Double_Window* o = menu_window = new Fl_Double_Window(435, 150, gettext("Menu properties"));
    menu_window->color((Fl_Color)31);
    menu_window->user_data((void*)(this));
    { Fl_Scroll* o = new Fl_Scroll(0, -330, 1015, 580);
      o->color((Fl_Color)31);
      { Fl_Button* o = new Fl_Button(5, 115, 30, 30, gettext("@+"));
        o->tooltip(gettext("Add a menu"));
        o->box(FL_FLAT_BOX);
        o->color((Fl_Color)23);
        o->selection_color(FL_DARK1);
        o->callback((Fl_Callback*)cb_);
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(40, 115, 30, 30);
        o->tooltip(gettext("remove a menu"));
        o->box(FL_FLAT_BOX);
        o->color((Fl_Color)23);
        o->image(image_minus);
        o->callback((Fl_Callback*)cb_1);
        o->align(Fl_Align(256));
      } // Fl_Button* o
      { menuElement = new Fl_Browser(80, 5, 90, 105);
        menuElement->tooltip(gettext("Options: Menu, Dynamic, Include, Program, Separator, Desktops, SendTo, Stick,\
 Maximize, Minimize, Shade, Move, Resize, Kill, Close, Restart, Exit"));
        menuElement->type(2);
        menuElement->box(FL_FLAT_BOX);
        menuElement->selection_color((Fl_Color)80);
        menuElement->callback((Fl_Callback*)cb_menuElement);
      } // Fl_Browser* menuElement
      { Fl_Button* o = new Fl_Button(80, 115, 30, 30, gettext("@+"));
        o->tooltip(gettext("Add a menu item"));
        o->box(FL_FLAT_BOX);
        o->color((Fl_Color)23);
        o->selection_color(FL_DARK1);
        o->callback((Fl_Callback*)cb_2);
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(115, 115, 30, 30);
        o->tooltip(gettext("remove a menu item"));
        o->box(FL_FLAT_BOX);
        o->color((Fl_Color)23);
        o->image(image_minus);
        o->callback((Fl_Callback*)cb_3);
        o->align(Fl_Align(256));
      } // Fl_Button* o
      { menuElementText = new Fl_Browser(175, 5, 255, 105);
        menuElementText->tooltip(gettext("These options correspond to specific Root Menu items"));
        menuElementText->type(2);
        menuElementText->box(FL_FLAT_BOX);
        menuElementText->selection_color((Fl_Color)80);
        menuElementText->labeltype(FL_NO_LABEL);
        menuElementText->callback((Fl_Callback*)cb_menuElementText);
        menuElementText->align(Fl_Align(FL_ALIGN_TOP));
      } // Fl_Browser* menuElementText
      { Fl_Button* o = new Fl_Button(175, 115, 30, 30);
        o->tooltip(gettext("Configure"));
        o->box(FL_FLAT_BOX);
        o->color((Fl_Color)23);
        o->image(image_gear16);
        o->labelfont(1);
        o->callback((Fl_Callback*)cb_4);
        o->align(Fl_Align(FL_ALIGN_WRAP));
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(315, 120, 57, 25, gettext("Cancel"));
        o->box(FL_FLAT_BOX);
        o->color((Fl_Color)80);
        o->selection_color((Fl_Color)81);
        o->labelcolor(FL_BACKGROUND2_COLOR);
        o->callback((Fl_Callback*)cb_Cancel);
      } // Fl_Button* o
      { save_button = new Fl_Button(381, 120, 49, 25, gettext("OK"));
        save_button->tooltip(gettext("Write to configuration file"));
        save_button->box(FL_FLAT_BOX);
        save_button->color((Fl_Color)61);
        save_button->selection_color((Fl_Color)59);
        save_button->labelcolor((Fl_Color)55);
        save_button->callback((Fl_Callback*)cb_save_button);
      } // Fl_Button* save_button
      { Fl_Browser* o = root_menu = new Fl_Browser(5, 5, 65, 105, gettext(" "));
        root_menu->tooltip(gettext("The range of possible values is 0 to 9 inclusive as  well\n                  \
   as  a to z inclusive, providing for up to 36 menus.  Note\n                \
     that only the numeric values map to mouse buttons."));
        root_menu->type(2);
        root_menu->box(FL_FLAT_BOX);
        root_menu->selection_color((Fl_Color)80);
        root_menu->callback((Fl_Callback*)cb_root_menu);
        getMenus(o);
        if(INPUTmenu.compare("")!=0){select_sent_in(INPUTmenu);}
      } // Fl_Browser* root_menu
      o->end();
    } // Fl_Scroll* o
    startup(o);
    menu_window->xclass("jsm-panel");
    menu_window->end();
    menu_window->resizable(menu_window);
  } // Fl_Double_Window* menu_window
  return menu_window;
}

Fl_Double_Window* MenuUI::nada_window() {
  { nada_win = new Fl_Double_Window(220, 50, gettext("Nothing to Configure"));
    nada_win->callback((Fl_Callback*)cb_nada_win, (void*)(this));
    nada_win->when(FL_WHEN_CHANGED);
    { Fl_Button* o = new Fl_Button(5, 10, 210, 30, gettext("Nothing to Configure"));
      o->box(FL_FLAT_BOX);
      o->color((Fl_Color)80);
      o->labelcolor((Fl_Color)55);
      o->callback((Fl_Callback*)cb_Nothing);
    } // Fl_Button* o
    nada_win->end();
  } // Fl_Double_Window* nada_win
  return nada_win;
}

Fl_Double_Window* MenuUI::submenu_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(255, 200, gettext("Submenu"));
    w = o;
    o->user_data((void*)(this));
    { submenu_items_browser = new Fl_Browser(5, 5, 245, 160);
      submenu_items_browser->type(2);
      submenu_items_browser->box(FL_FLAT_BOX);
    } // Fl_Browser* submenu_items_browser
    { submenu_menu = new Fl_Output(10, 170, 25, 25);
      submenu_menu->hide();
    } // Fl_Output* submenu_menu
    { Fl_Input* o = new Fl_Input(115, 170, 135, 25);
      o->box(FL_FLAT_BOX);
    } // Fl_Input* o
    startup(o);
    o->end();
  } // Fl_Double_Window* o
  return w;
}

void MenuUI::add_an_item() {
  if(!checkFlBrowserItem(root_menu)){return;}
  add_window()->show();
}

void MenuUI::add_cb(int whichOne) {
  //Program 0
  //Restart 1
  //Exit 2
  //Separator 3
  //Include 4
  //Desktops 5
  //SendTo 6
  //Stick 7
  //Maximize 8
  //Minimize 9
  //Shade 10
  //Move 11
  //Resize 12
  //Kill 13
  //Close 14
  //Menu (height,label,icon,labeled)
  add_prog_button->hide();
  add_input->hide();
  add_button->hide();
  add_label->show();
  add_icon->show();
  add_icon_button->show();
  std::string result;
  switch (whichOne){
    case 0:
      result="Program";
      add_prog_button->show();
      add_input->show();
      break;
    case 1:
      result="Restart";
      break;
    case 2:
      result="Exit";
      add_button->show();
      add_button->copy_label("Confirm");
      break;
    case 3:
      result="Separator";
      add_label->hide();
      add_icon->hide();
      add_icon_button->hide();
      break;
    case 4:
      result="Include";
      add_input->show();
      add_label->hide();
      add_icon->hide();
      add_icon_button->hide();
      break;
    case 5:
      result="Desktops";
      break;
    case 6:
      result="SendTo";
      break;
    case 7:
      result="Stick";
      break;
    case 8:
      result="Maximize";
      break;
    case 9:
      result="Minimize";
      break;
    case 10:
      result="Shade";
      break;
    case 11:
      result="Move";
      break;
    case 12:
      result="Resize";
      break;
    case 13:
      result="Kill";
      break;
    case 14:
      result="Close";
      break;
    case 15:
      result="Menu";
      add_button->show();
      add_button->copy_label("Labeled");
      break;
  }
  item_display->value(result.c_str());
}

void MenuUI::change_include() {
  const char* old = old_include_input->value();
  if(old==NULL){return;}
  const char* new_include = include_input->value();
  if(new_include==NULL){return;}
  std::string newInclude=new_include;
  if(newInclude.compare(old)==0){return;}
  const char* menu = include_input_menu->value();
  if(menu==NULL){return;}
  std::string MENU = menu;
  std::cout<<"MENU: "<<MENU<<std::endl;
  changeMenuInclude(newInclude,old,MENU);
  if(getMenuItems(menuElement,menu,menuElementText)){
    menuElementText->copy_label(menu);
  }
}

void MenuUI::choose_menu(std::string menu) {
  if(getMenuItems(menuElement,menu,menuElementText)){
   debug_out("Got menu: "+menu);
  }
}

void MenuUI::configure_item() {
  if(!checkFlBrowserItem(menuElementText)){return;}
  const char* menu = menuElementText->label();
  if(ConfigMenuItem(menuElement,menuElementText,prog_label,prog_icon,prog_input,conf_button)){
    choose_menu(menu);
  }
}

void MenuUI::confirm_check() {
  if(!checkFlBrowserItem(menuElement)){return;}
  int LINEposition = menuElement->value();
  std::string NAME = menuElement->text(LINEposition);
  if(NAME.compare("Exit")!=0){conf_button->hide();}
}

void MenuUI::edit_a_menu() {
  if(checkFlBrowserItem(root_menu)){
    int line = root_menu->value();
    const char* menu = root_menu->text(line);
    std::string MENU=menu;
    conf_window()->show();
    std::string result = getLabel(MENU);
    prog_label->value(result.c_str());
  }
}

void MenuUI::edit_an_item() {
  if(!checkFlBrowserItem(menuElement)){return;}
  if(!checkFlBrowserItem(root_menu)){return;}
  if(!checkFlBrowserItem(menuElementText)){return;}
  int line = menuElement->value();
  const char* text = menuElement->text(line);
  int menuNum = root_menu->value();
  const char* menu = root_menu->text(menuNum);
  std::string EXIT="Exit";
  std::string RESTART="Restart";
  std::string iconattrib = "icon"; 
  std::string labelattrib = "label";
  std::string confirmattrib = "confirm";
  std::string ITEM = text;
  debug_out("edit Item: "+ITEM);
  int line2 = menuElementText->value();
  const char* text2 = menuElementText->text(line2);
  std::string ICON,LABEL;
  if(ITEM.compare("Program")==0){
    conf_item_window()->show();
    item_prog_input->value(text2);
    item_conf_button->hide();
    ICON = getItemIcon(text2,menu);
    LABEL = getItemLabel(text2,menu);
  }
  else if(ITEM.compare("Include")==0){
    std::string exec ="exec:";
    unsigned int exec_len = exec.length();
    std::string INCLUDE = text2;
    unsigned int found = INCLUDE.find(exec);
    if(found<INCLUDE.length()){
      INCLUDE=INCLUDE.erase(0,exec_len);
      std::cout<<"Include: "<<INCLUDE<<std::endl;
      configure_include()->show();
      include_input->value(INCLUDE.c_str());
      include_input_menu->value(menu);
      old_include_input->value(INCLUDE.c_str());
      
    }
  }
  else if(ITEM.compare("Menu")==0){
    submenu_window()->show();
    submenu_menu->value(menu);
  }
  else if(ITEM.compare("Dynamic")==0){
    debug_out("Dyanmic Menu!");
  }
  else if(ITEM.compare(EXIT)==0){
    conf_item_window()->show();
    item_prog_input->hide();
    item_prog_button->hide();
    ICON = getItemAttribute(EXIT,menu,iconattrib);
    LABEL = getItemAttribute(EXIT,menu,labelattrib);
    std::string confirm = getItemAttribute(EXIT,menu,confirmattrib); 
    if(confirm.compare("true")){item_conf_button->value(0);}
    else{item_conf_button->value(1);}
  }
  else if(ITEM.compare(RESTART)==0){
    conf_item_window()->show();
    item_prog_input->hide();
    item_prog_button->hide();
    ICON = getItemAttribute(RESTART,menu,iconattrib);
    LABEL = getItemAttribute(RESTART,menu,labelattrib);
    item_conf_button->hide();
  }
  else{
    nada_window()->show();
  }
  if(ICON.compare("")!=0){
    item_prog_icon->value(ICON.c_str());
    makeWidgetIcon(ICON,item_icon_button,48);
  }
  if(LABEL.compare("")!=0){item_prog_label->value(LABEL.c_str());}
}

void MenuUI::program_check() {
  if(!checkFlBrowserItem(menuElement)){return;}
  int LINEposition = menuElement->value();
  const char* nombre = menuElement->text(LINEposition);
  std::string NAME=nombre;
  if(NAME.compare("Program")!=0){
    prog_button->hide();
    prog_input->hide();
  }
  else{
    std::string TEXT = menuElementText->text(LINEposition);
    //prog_input->value(TEXT.c_str());
    //how do I do that??
  }
}

void MenuUI::remove_an_item() {
  std::cout<<"Remove"<<std::endl;
}

void MenuUI::remove_a_menu() {
  if(!checkFlBrowserItem(root_menu)){return;}
  int line = root_menu->value();
  const char* value = root_menu->text(line);
  removeMenu(value);
  getMenus(root_menu);
  menuElement->clear();
  menuElementText->clear();
}

int MenuUI::save_cb() {
  //save
  const char* label = add_label->value();
  if(label ==NULL){return 42;}
  const char* icon = add_icon->value();
  if(icon ==NULL){return 42;}
  const char* input = add_input->value();
  if(input ==NULL){return 42;}
  const char* result = item_display->value();
  if(result ==NULL){return 42;}
  std::cout<<"everything exists??"<<std::endl;
  return addMenuItem(menuElement, menuElementText, add_label, add_icon, add_input, add_button, result);
}

void MenuUI::select_sent_in(std::string thatMenu) {
  if(thatMenu.compare("")==0)return;
  choose_menu(thatMenu);
  int tot=root_menu->size();
  if(tot>0){
    for (int i=0;i!=tot;i++){
      const char* txt=root_menu->text(i);
      if((txt!=NULL)&&(thatMenu.compare(txt)==0)){root_menu->select(i);}
    }
  }
}
