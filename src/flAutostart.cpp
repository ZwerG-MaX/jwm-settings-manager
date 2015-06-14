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
#include "../include/flAutostart.h"
flAutostart::flAutostart(){
    tinyxml2::XMLDocument doc;
}

flAutostart::~flAutostart()
{
    //dtor
}



void flAutostart::getAutostart(Fl_Browser *o){
    if(!testElement("StartupCommand")){return;}
    for(const tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");node;node=node->NextSiblingElement("StartupCommand")){
        std::string value  = node->GetText();
        if(value.c_str() !=NULL){
            const char * v = value.c_str();
            o->add(v);
        }
        //std::cout<<value<<std::endl;
    }
}
/*
void flAutostart::addAutostart(const char * program){
    tinyxml2::XMLNode *trayNode = doc.FirstChildElement( "JWM" );
    tinyxml2::XMLNode *node = doc.NewElement("StartupCommand");
    trayNode->InsertEndChild(node);
    tinyxml2::XMLText *startup = doc.NewText(program);
    node->LinkEndChild(startup);
    saveChangesTemp();
}
 void flAutostart::removeAutostart(const char * program){
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");node;node=node->NextSiblingElement("StartupCommand")){
        std::string fromDoc = node->GetText();
        ///What was I doing here???  why was I looking for a space?
        //unsigned found = fromDoc.find(" ");
        //fromDoc = fromDoc.erase(0,found+1);
        ///probably delete this, unless I find a bug that I needed this for...
        const char* value  = fromDoc.c_str();
        std::string fromProgram = program;
        //std::cout<<"Value: "<<value<<" Program: "<<program<<std::endl;
        if(fromProgram.compare(value) ==0){
            node->DeleteChild(node);
            std::cout<<"deleted "<<program<<std::endl;
        }

    }
    saveChangesTemp();
 }
*/
void flAutostart::useROX(bool rox){
    if(rox){
        addAutostart("rox-filer -p pb_JWM");
    }
    else{
        removeAutostart("rox-filer -p pb_JWM");
    }
}
