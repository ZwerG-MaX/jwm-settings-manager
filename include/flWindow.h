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

#ifndef FLWINDOW_H
#define FLWINDOW_H

//FLTK stuff
#include "../fltk/jwm-window.h"

//All the common functions
#include "Config.h"

class flWindow : public Config{
    public:

    //buttons
    const char * getButton(const char* whichElement);
    void setButton(const char *button, const char* whichElement);
    std::string buttonPath();

    ///window colors
    //Active
    unsigned int getActiveWindowColor(unsigned int &color);
    void setActiveWindowColor(const double* rgb, const double* rgb2);
    void setActiveWindowColor(const double* rgb);
    //Inactive
    unsigned int getWindowColor(unsigned int &color);
    void setWindowColor(const double* rgb);
    void setWindowColor(const double* rgb, const double* rgb2);

    ///Opacity
    //Inactive
    float getOpacity();
    void windowOpacity(float &opacity);
    //Active
    float getActiveOpacity();
    void activeWindowOpacity(float &opacity);

    ///border
    //Active
    void setActiveBorderColor(const double* rgb);
    unsigned int getActiveBorderColor();
    //Inactive
    void setBorderColor(const double* rgb);
    unsigned int getBorderColor();

    //Border width
    int getBorderWidth();
    void setBorderWidth(int &border);
    //TitleBar Height
    int getBorderHeight();
    void setBorderHeight(int &border);

    ///font & button color
    //Inactive
    void setFontColor(const double* rgb);
    unsigned int getFontColor();
    //Active
    unsigned int getActiveFontColor();
    void setActiveFontColor(const double* rgb);

///General COLOR functions
    unsigned int getActiveColor(const char* element);
    unsigned int getActiveColor(const char* element, unsigned int &color2);
    void setActiveColor(const char* element, const double* rgb);
    void setActiveColor(const char* element, const double* rgb, const double* rgb2);
//Inactive
    unsigned int getInactiveColor(const char* element);
    unsigned int getInactiveColor(const char* element, unsigned int &color2);
    void setInactiveColor(const char* element, const double* rgb);
    void setInactiveColor(const char* element, const double* rgb, const double* rgb2);



    //ETCw
    void setThings(const char* thing, const char* mode);
    void setThings(const char* thing, const char* mode, int &distance);
    void setResize(const char *mode);
    void setMoveMode(const char *mode);
    void setFocusModel(const char *mode);
    void setSnap(const char *mode, int &distance);
    void setSnap(int &distance);
    int getSnap();

    bool isNewStyleWindow;

    flWindow();
    virtual ~flWindow();

    protected:
    private:
};

#endif // FLWINDOW_H
