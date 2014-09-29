#include "../include/MulitPanel.h"
#include "../include/Config.h"

MultiPanel::MultiPanel()
{
    //ctor
}

MultiPanel::~MultiPanel()
{
    //dtor
}
//************************************  MULTIPLE PANELS  *************************************************

unsigned int MultiPanel::numPanels(){
    unsigned int counter2 = 0;
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("Tray");node;node=node->NextSiblingElement()){
        std::string name = node->Name();
        std::string element = "Tray";
        if(name.compare(element)==0)
            counter2++;
    }
    std::cout<<counter2<<" panel(s) found\n";//DEBUG
    return counter2;
}


///WHICH PANEL
void MultiPanel::setWhichPanel(unsigned int panel){
    whichPanel = panel;
}
const char* MultiPanel::getPanel(){
    tinyxml2::XMLDocument panels;
    if (home!=NULL){
        std::string filename = std::string(home);
        filename += "/";
        filename +=".panels";
        panels.LoadFile( filename.c_str() );
        if (panels.ErrorID() !=0){
            printf("The file %s was not found.  Recovering now\n", filename.c_str());
            int sys = system("touch ~/.panels");
            if(sys!=0){/*do something?*/}
            panels.NewElement("Panels");
            panels.SaveFile(filename.c_str());

        }
        else{
            return (panels.FirstChildElement("Panels")->GetText());

        }
    }
    else {std::cout<< "There is an problem, you don't have a $HOME... this is a big problem\n";}
    return "top";
}
void MultiPanel::saveWhichPanel(std::string align){
    tinyxml2::XMLDocument panels;
    if (home!=NULL){
        std::string filename = std::string(home);
        filename += "/";
        filename +=".panels";
        panels.LoadFile( filename.c_str() );
        if (panels.ErrorID() !=0){
            printf("The file %s was not found.  Recovering now\n", filename.c_str());
            int sys = system("touch ~/.panels");
            if(sys!=0){/*do something?*/}
            panels.NewElement("Panels");
            panels.FirstChildElement("Panels")->SetText(align.c_str());
            panels.SaveFile(filename.c_str());
        }
        else{
            panels.FirstChildElement("Panels")->SetText(align.c_str());
            panels.SaveFile(filename.c_str());
        }
    }
    else std::cout<< "There is an problem, you don't have a $HOME... this is a big problem\n";
}
///check layout horizontal vertical
std::string MultiPanel::checkLayout(tinyxml2::XMLElement* tray){
    std::string layout = tray->Attribute("layout");
    std::cout<<layout<<std::endl;
    return layout;
}

std::string MultiPanel::checkAlign(tinyxml2::XMLElement* tray){
    std::string layout = checkLayout(tray);
    //if horizontal check halign
    //should be left or right
    if(layout.compare("horizontal")==0){
        std::string halign =getHalign(tray);
        std::cout<<halign<<std::endl;
        return halign;
    }
    //if verticle check valign
    //should be top or bottom
    else if(layout.compare("vertical")==0){
        std::string valign = getValign(tray);
        std::cout<<valign<<std::endl;
        return valign;
    }
    std::string error = "This shouldn't happen";
    std::cout<<error<<std::endl;
    return error;
}

std::string MultiPanel::getHalign(tinyxml2::XMLElement* tray){
    std::string halign = tray->Attribute("halign");
    std::cout<<halign<<std::endl;
    return halign;
}

std::string MultiPanel::getValign(tinyxml2::XMLElement* tray){
    std::string valign = tray->Attribute("valign");
    std::cout<<valign<<std::endl;
    return valign;
}

std::string MultiPanel::getPanelLayout(tinyxml2::XMLElement* tray){
    std::string whichOne = checkAlign(tray);
    std::string error = "This shouldn't happen";
    if(whichOne.compare(error)!=0){
        std::cout<<whichOne<<std::endl;

        return whichOne;
    }
    std::cout<<whichOne<<std::endl<<error<<std::endl;
    return error;

}


unsigned int MultiPanel::getWhichPanel(){
    return whichPanel;
}

void MultiPanel::choosePanel(unsigned int panel, tinyxml2::XMLElement* tray){
   ///Add this to all the functions??
   tinyxml2::XMLElement* node;
   unsigned int i = 0;
   for((node=doc.FirstChildElement("JWM")->FirstChildElement("Tray"));(i<=panel);i++){
       node=node->NextSiblingElement();
   }
   tray = node;
   //makes an integer number describing which panel
   setWhichPanel(panel);
}

///ADD PANEL

void MultiPanel::addPanel(Fl_Menu_Button* o){
    const char* out;
    tinyxml2::XMLNode *tray = doc.FirstChildElement("JWM");
    tinyxml2::XMLNode *node = doc.FirstChildElement("JWM")->FirstChildElement("Tray");
    tinyxml2::XMLNode *newTray = doc.NewElement("Tray");
    tinyxml2::XMLNode *spacer = doc.NewElement("Spacer");
    tray->InsertAfterChild(node,newTray);
    newTray->InsertEndChild(spacer);
    std::string label = "Panel ";
    saveChangesTemp();
    unsigned int panels = numPanels();
    std::string num = convert(panels);
    label+=num;
    out = label.c_str();
    o->add(out,0,0,0,0);
    setWhichPanel(panels);
}
//########################################### END MULTIPLE PANELS ###########################################
