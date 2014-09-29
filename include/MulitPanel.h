#ifndef MULTIPANEL_H
#define MULTIPANEL_H

#include "flPanel.h"
#include "Config.h"


class MultiPanel : public Config, public flPanel
{
    public:
        //How many panels?
        unsigned int numPanels();
        void choosePanel(unsigned int panel, tinyxml2::XMLElement* tray);

        ///Which Panel?
        //set the counter variable
        void setWhichPanel(unsigned int panel);
        //find the numerical value of whichPanel counter variable
        unsigned int getWhichPanel();
        const char* getPanel();
        //check the attributes of the element passed in
        std::string checkLayout(tinyxml2::XMLElement* tray);
        std::string checkAlign(tinyxml2::XMLElement* tray);
        std::string getHalign(tinyxml2::XMLElement* tray);
        std::string getValign(tinyxml2::XMLElement* tray);
        //get the position of the panel passed in (top, bottom, right, left)
        std::string getPanelLayout(tinyxml2::XMLElement* tray);
        //add a Panel
        void addPanel(Fl_Menu_Button *o);
        void saveWhichPanel(std::string align);

        MultiPanel();
        virtual ~MultiPanel();
    protected:
    private:
};

#endif // MULTIPANEL_H
