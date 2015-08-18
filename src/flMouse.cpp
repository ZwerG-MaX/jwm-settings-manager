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

#include "../include/flMouse.h"

flMouse::flMouse(){
#ifdef DEBUG_TRACK
    std::cerr<<"[flMouse]->"<<std::endl;
#endif // DEBUG
    tinyxml2::XMLDocument doc;
}

flMouse::~flMouse(){
#ifdef DEBUG_TRACK
    std::cerr<<"<-[flMouse]"<<std::endl;
#endif // DEBUG
}

int flMouse::getDoubleClick(){
    if(!testElement("DoubleClickSpeed")){
        createElement("DoubleClickSpeed");
        //better set it to the default, since that is how it acts
        tinyxml2::XMLElement* fixer = doc.FirstChildElement( "JWM" )->FirstChildElement( "DoubleClickSpeed" );
        fixer->SetText(400);
        saveChanges();
        saveChangesTemp();
        return 400;
    }
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement( "DoubleClickSpeed" );
    std::string text = element->GetText();
    int result = strtol(text.c_str(),0,10);
    return result;
}
void flMouse::setDoubleClick(int &speed){
    //does it exist??
    if(!testElement("DoubleClickSpeed")){createElement("DoubleClickSpeed");}
    //point to it
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "DoubleClickSpeed");
    element->SetText(speed);
    saveChangesTemp();
}
int flMouse::getDelta(){
    //does it exist??
    if(!testElement("DoubleClickDelta")){
        createElement("DoubleClickDelta");
        //better set it to the default, since that is how it acts
        tinyxml2::XMLElement* fixer = doc.FirstChildElement( "JWM" )->FirstChildElement( "DoubleClickDelta" );
        fixer->SetText(2);
        saveChanges();
        saveChangesTemp();
        return 2;
    }
    //point to it
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement( "DoubleClickDelta" );
    std::string text = element->GetText();
    int result = strtol(text.c_str(),0,10);
    return result;

}
void flMouse::setDelta(int &delta){
//does it exist??
    if(!testElement("DoubleClickDelta")){createElement("DoubleClickDelta");}
    //point to it
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "DoubleClickDelta");
    element->SetText(delta);
    saveChangesTemp();

}

bool flMouse::isTap(){
    const char * program = "synclient MaxTapTime=0";
    if(!testElement("StartupCommand")){return false;}
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");
    node;node=node->NextSiblingElement("StartupCommand")){
        std::string fromDoc = node->GetText();
        //const char* value  = fromDoc.c_str();
        std::string fromProgram = program;
        if(fromProgram.compare(fromDoc) ==0){
            return true;
        }
    }
    return false;
}
