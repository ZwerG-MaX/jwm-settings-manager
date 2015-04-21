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
// generated by Fast Light User Interface Designer (fluid) version 1.0302

#include <libintl.h>
#include "jwm-icons.h"

void IconsUI::cb_Cancel_i(Fl_Button*, void*) {
  cancel(icons_window);
UI ux;
ux.showSettings();
}
void IconsUI::cb_Cancel(Fl_Button* o, void* v) {
  ((IconsUI*)(o->parent()->parent()->user_data()))->cb_Cancel_i(o,v);
}

void IconsUI::cb_save_button_i(Fl_Button*, void*) {
  saveJWMRC(icons_window);
UI ux;
ux.showSettings();
}
void IconsUI::cb_save_button(Fl_Button* o, void* v) {
  ((IconsUI*)(o->parent()->parent()->user_data()))->cb_save_button_i(o,v);
}

void IconsUI::cb__i(Fl_Button*, void*) {
  std::string icon_choice = choose_icons();
add_icons(icon_choice);
}
void IconsUI::cb_(Fl_Button* o, void* v) {
  ((IconsUI*)(o->parent()->parent()->user_data()))->cb__i(o,v);
}

void IconsUI::cb_1_i(Fl_Button*, void*) {
  remove_icons();
}
void IconsUI::cb_1(Fl_Button* o, void* v) {
  ((IconsUI*)(o->parent()->parent()->user_data()))->cb_1_i(o,v);
}

#include <FL/Fl_Bitmap.H>
static unsigned char idata_minus[] =
{0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,0,
0,0,0};
static Fl_Bitmap image_minus(idata_minus, 16, 16);

Fl_Double_Window* IconsUI::make_window() {
  load();
  saveChangesTemp();
  { Fl_Double_Window* o = icons_window = new Fl_Double_Window(330, 295, gettext("Icons"));
    icons_window->color((Fl_Color)31);
    icons_window->user_data((void*)(this));
    { Fl_Scroll* o = new Fl_Scroll(0, 0, 330, 290);
      o->color((Fl_Color)31);
      { Fl_Button* o = new Fl_Button(205, 245, 57, 25, gettext("Cancel"));
        o->box(FL_GTK_UP_BOX);
        o->color((Fl_Color)80);
        o->selection_color((Fl_Color)81);
        o->labelcolor(FL_BACKGROUND2_COLOR);
        o->callback((Fl_Callback*)cb_Cancel);
      } // Fl_Button* o
      { save_button = new Fl_Button(271, 245, 45, 25, gettext("OK"));
        save_button->tooltip(gettext("Write to configuration file"));
        save_button->box(FL_GTK_UP_BOX);
        save_button->color((Fl_Color)61);
        save_button->selection_color((Fl_Color)59);
        save_button->labelcolor((Fl_Color)55);
        save_button->callback((Fl_Callback*)cb_save_button);
      } // Fl_Button* save_button
      { Fl_Button* o = new Fl_Button(10, 240, 35, 35, gettext("@+"));
        o->tooltip(gettext("Add the chosen icon path"));
        o->box(FL_GTK_UP_BOX);
        o->selection_color(FL_DARK1);
        o->callback((Fl_Callback*)cb_);
      } // Fl_Button* o
      { iconsBrowser = new Fl_Browser(10, 15, 310, 220);
        iconsBrowser->type(2);
        iconsBrowser->box(FL_GTK_DOWN_BOX);
        iconsBrowser->selection_color((Fl_Color)80);
        flIcons icons;
        icons.getIcons(iconsBrowser);
      } // Fl_Browser* iconsBrowser
      { Fl_Button* o = new Fl_Button(50, 240, 35, 35);
        o->box(FL_GTK_UP_BOX);
        o->image(image_minus);
        o->callback((Fl_Callback*)cb_1);
        o->align(Fl_Align(256));
      } // Fl_Button* o
      o->end();
    } // Fl_Scroll* o
    Config config;config.under_mouse(o);
    icons_window->end();
    icons_window->resizable(icons_window);
  } // Fl_Double_Window* icons_window
  return icons_window;
}

void IconsUI::add_icons(std::string icon_dir) {
  flIcons icons;
  if(icon_dir.compare("")!=0){
  	iconsBrowser->clear();
  	icons.addIcons(icon_dir.c_str());//input);
  	icons.getIcons(iconsBrowser);
  	iconsBrowser->redraw();
  }
  else{
  	fl_message("You have to select a directory to add, or type one in!");
  }
}

void IconsUI::remove_icons() {
  flIcons icons;
  int item_list_number = iconsBrowser->value();
  const char * item = iconsBrowser->text(item_list_number);
  std::string test_item = item;
  if (test_item.compare("") !=0){
  	iconsBrowser->clear();
  	icons.removeIcons(item);
  	icons.getIcons(iconsBrowser);
  	iconsBrowser->redraw();
  }
  else{
  	fl_message("Please click on an item to remove!");
  }
}

std::string IconsUI::choose_icons() {
  const char * f = "/usr/share/icons/";
  const char * m="Choose a Directory";
  int r = 0;
  const char *result = fl_dir_chooser(m,f,r);
  std::string result_string = result;
  if(result_string.compare("")!=0){
  	return result_string;
  }
  return "";
}
