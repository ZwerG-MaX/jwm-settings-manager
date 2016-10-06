//
// "$Id: keyboard.cxx 9303 2012-03-26 16:54:54Z manolo $"
//

//
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     http://www.fltk.org/COPYING.php
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

//
// Keyboard/event test program for the Fast Light Tool Kit (FLTK).
//
// Continuously display FLTK's event state.
//
// Known bugs:
//
// X insists on reporting the state *before* the shift key was
// pressed, rather than after, on shift key events.  I fixed this for
// the mouse buttons, but it did not seem worth it for shift.
//
// X servers do not agree about any shift flags after except shift, ctrl,
// lock, and alt.  They may also not agree about the symbols for the extra
// keys Micro$oft put on the keyboard.
//
// On IRIX the backslash key does not work.  A bug in XKeysymToKeycode?
//
#include "../include/keyboard.h"
#include "../fltk/keyboard-ui.h"

#include <string.h>


// these are used to identify which buttons are which:
void key_cb(Fl_Button*, void*) {}
void shift_cb(Fl_Button*, void*) {}
void wheel_cb(Fl_Dial*, void*) {}

// this is used to stop Esc from exiting the program:
int handle(int e) {
  return (e == FL_SHORTCUT); // eat all keystrokes
}

int MyWindow::handle(int msg) {
  if (msg==FL_MOUSEWHEEL)
  {
    roller_x->value( roller_x->value() + Fl::e_dx * roller_x->step() );
    roller_y->value( roller_y->value() + Fl::e_dy * roller_y->step() );
    return 1;
  }
  return 0;
}

struct keycode_table{int n; const char* text;} table[] = {
  {FL_Escape, "Escape"},
  {FL_BackSpace, "BackSpace"},
  {FL_Tab, "Tab"},
  {FL_Iso_Key, "Iso_Key"},
  {FL_Enter, "Enter"},
  {FL_Print, "Print"},
  {FL_Scroll_Lock, "Scroll_Lock"},
  {FL_Pause, "Pause"},
  {FL_Insert, "Insert"},
  {FL_Home, "Home"},
  {FL_Page_Up, "Page_Up"},
  {FL_Delete, "Delete"},
  {FL_End, "End"},
  {FL_Page_Down, "Page_Down"},
  {FL_Left, "Left"},
  {FL_Up, "Up"},
  {FL_Right, "Right"},
  {FL_Down, "Down"},
  {FL_Shift_L, "Shift"},
  {FL_Shift_R, "Shift"},
  {FL_Control_L, "Control"},
  {FL_Control_R, "Control"},
  {FL_Caps_Lock, "Caps_Lock"},
  {FL_Alt_L, "Alt"},
  {FL_Alt_R, "Alt"},
  {FL_Meta_L, "Meta"},
  {FL_Meta_R, "Meta"},
  {FL_Menu, "Menu"},
  {FL_Help, "Help"},
  {FL_Num_Lock, "Num_Lock"},
  {FL_KP_Enter, "Enter"},
  {FL_Volume_Down, "XF86AudioLowerVolume"},
  {FL_Volume_Up, "XF86AudioRaiseVolume"},
  {FL_Volume_Mute, "XF86AudioMute"},
  {FL_Media_Play,"XF86AudioPause"},
  {FL_Media_Stop,"XF86AudioStop"},
  {FL_Media_Prev,"XF86AudioPrev"},
  {FL_Media_Next,"XF86AudioNext"},
  {FL_Home_Page,"XF86HomePage"},
  {FL_Mail,"XF86Mail"},
  {FL_Search,"XF86Search"},
  {FL_Back,"XF86Back"},
  {FL_Forward,"XF86Forward"},
  {FL_Sleep,"XF86Standby"},
  {FL_Favorites,"XF86Favorites"}
};

//  {FL_Stop,"XF86??"},
//  {FL_Refresh,"XF86Refresh???"}
int main(int argc, char** argv) {
  Fl::add_handler(handle);
  MyWindow *window = make_window();
  window->show(argc,argv);
  while (Fl::wait()) {
    const char *str;
    
    // update all the buttons with the current key and shift state:
    for (int i = 0; i < window->children(); i++) {
      Fl_Widget* b = window->child(i);
      if (b->callback() == (Fl_Callback*)key_cb) {
	int i = b->argument();
	if (!i) i = b->label()[0];
        Fl_Button *btn = ((Fl_Button*)b);
        int state = Fl::event_key(i);
        if (btn->value()!=state)
	  btn->value(state);
      } else if (b->callback() == (Fl_Callback*)shift_cb) {
	int i = b->argument();
        Fl_Button *btn = ((Fl_Button*)b);
        int state = Fl::event_state(i);
        if (btn->value()!=state)
	  btn->value(state);
      }
    }

    // figure out the keyname:
    char buffer[100];
    const char *keyname = buffer;
    int k = Fl::event_key();
    if (!k)
      keyname = "0";
    else if (k < 256) {
      sprintf(buffer, "'%c'", k);
    } else if (k > FL_F && k <= FL_F_Last) {
      sprintf(buffer, "FL_F+%d", k - FL_F);
    } else if (k >= FL_KP && k <= FL_KP_Last) {
      sprintf(buffer, "FL_KP+'%c'", k-FL_KP);
    } else if (k >= FL_Button && k <= FL_Button+7) {
      sprintf(buffer, "FL_Button+%d", k-FL_Button);
    } else {
      sprintf(buffer, "0x%04x", k);
      for (int i = 0; i < int(sizeof(table)/sizeof(*table)); i++)
	if (table[i].n == k) {keyname = table[i].text; break;}
    }
    if (strcmp(key_output->value(), keyname))
      key_output->value(keyname);

    str = Fl::event_text();
    if (strcmp(text_output->value(), str))
      text_output->value(str);
  }
  return 0;
}

//
// End of "$Id: keyboard.cxx 9303 2012-03-26 16:54:54Z manolo $".
//
