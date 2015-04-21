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
#include "../include/flIcons.h"

flIcons::flIcons()
{
    tinyxml2::XMLDocument doc;
}

flIcons::~flIcons()
{
    //dtor
}

void flIcons::addIcons(const char* path){
    ///this will be used to check for a full Icon theme directory
    std::string iconPath = "/usr/share/icons";
    std::string tempPath = path;
    tempPath = tempPath.substr(0,16);
    std::cout<<tempPath<<std::endl;
    if(tempPath.compare(iconPath)==0){
        std::cout<<"They chose "<<path<<" which is in "<<iconPath<<std::endl;
        ///TODO: make this get all the subdirectories of the folder and check for sizes, etc...
    }
    else{std::cout<<"Custom Folder chosen\n";}

    bool tester = false;
    ///Make the rootNode
    tinyxml2::XMLNode *rootNode = doc.FirstChildElement( "JWM" );
    ///make the new icon's node to hook onto (if the test doesn't fail)
    tinyxml2::XMLNode *iconNode = doc.FirstChildElement( "JWM" )->LastChildElement("IconPath");
    ///Test to see if there are already Icon nodes existing
    for(tinyxml2::XMLElement* testNode=doc.FirstChildElement("JWM")->FirstChildElement("IconPath");
    testNode;testNode=testNode->NextSiblingElement("IconPath")){
        tester=true;
    }
    ///Make the new icon node
    tinyxml2::XMLNode *node = doc.NewElement("IconPath");
    ///if there are other icons put it after them, otherwise just throw it at the end
    if(tester){rootNode->InsertAfterChild(iconNode,node);}
    else{rootNode->InsertEndChild(node);}
    ///make the text
    tinyxml2::XMLText *iconDir = doc.NewText(path);
    ///link the text to the icon node
    node->LinkEndChild(iconDir);
    /// save it temporarily incase the user decides to cancel
    saveChangesTemp();
}

void flIcons::getIcons(Fl_Browser *o){
 for(const tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("IconPath");node;node=node->NextSiblingElement("IconPath")){
        std::string value  = node->GetText();
        if(value.c_str() !=NULL){
            const char * v = value.c_str();
            o->add(v);
        }
        //std::cout<<value<<std::endl;
    }
}

void flIcons::removeIcons(const char * icons){
    std::string fromProgram = icons;
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("IconPath");node;node=node->NextSiblingElement("IconPath")){
        std::string fromDoc = node->GetText();
        const char* value  = fromDoc.c_str();
        //std::cout<<"Value: "<<value<<" Icons: "<<fromProgram<<std::endl;
        if(fromProgram.compare(value) ==0){
            node->DeleteChild(node);
            //std::cout<<"deleted "<<fromProgram<<std::endl;
        }

    }
    saveChangesTemp();
}
