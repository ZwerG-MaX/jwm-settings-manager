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

flIcons::flIcons(){

#ifdef DEBUG_TRACK
  std::cerr<<"[flIcons]->"<<std::endl;
#endif // DEBUG

    tinyxml2::XMLDocument doc;
}

flIcons::~flIcons(){
    #ifdef DEBUG_TRACK
  std::cerr<<"<-[flIcons]"<<std::endl;
#endif // DEBUG

}

void flIcons::addIcons(std::string path){
    std::cout<<path<<std::endl;
    ///Make the rootNode
    tinyxml2::XMLNode *rootNode = doc.FirstChildElement( "JWM" );
    tinyxml2::XMLNode *iconNode = doc.FirstChildElement( "JWM" );
    ///make the new icon's node to hook onto (if the test doesn't fail)
    if (iconNode->LastChildElement("IconPath")){iconNode=iconNode->LastChildElement("IconPath");}
    ///Make the new icon node
    tinyxml2::XMLNode *node = doc.NewElement("IconPath");
    ///if there are other icons put it after them, otherwise just throw it at the end
    rootNode->InsertAfterChild(iconNode,node);
    ///make the text
    tinyxml2::XMLText *iconDir = doc.NewText(path.c_str());
    ///link the text to the icon node
    node->LinkEndChild(iconDir);
    /// save it temporarily incase the user decides to cancel
    saveChangesTemp();
}

void flIcons::getIcons(Fl_Browser *o){
    if(!testElement("IconPath")){return;}
    tinyxml2::XMLElement* node=doc.FirstChildElement("JWM");
    for(node = node->FirstChildElement("IconPath");node;node=node->NextSiblingElement("IconPath")){
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
    if(!testElement("IconPath")){return;}
    tinyxml2::XMLElement* node=doc.FirstChildElement("JWM");
    for(node = node->FirstChildElement("IconPath");node;node=node->NextSiblingElement("IconPath")){
        std::string fromDoc = node->GetText();
        const char* value  = fromDoc.c_str();
        if(DEBUG_ME){std::cerr<<"Value: "<<value<<" Icons: "<<fromProgram<<std::endl;}
        if(fromProgram.compare(value) ==0){
            node->DeleteChild(node);
            if(DEBUG_ME){std::cerr<<"deleted "<<fromProgram<<std::endl;}
        }

    }
    saveChangesTemp();
}
/// Icon theme FILES
std::string flIcons::currentIconTheme(){
    std::string gsett = "gsettings get org.gnome.desktop.interface icon-theme | sed \"s#'##g\" ";
    std::string result = returnTerminalOutput(gsett,"r");
    unsigned int found = result.find('=');
    if(found<result.length()){result=result.erase(0,found+1);}
    if(DEBUG_ME){std::cerr<<"current Icon Theme is: "<<result<<std::endl;}
    if(result.length()>2){return result.erase((result.length()-1),std::string::npos);}
    return "";
}

void flIcons::loadTheme(Fl_Browser *o){
    o->clear();
    std::list<std::string> themeList;
    std::string testPATH,stringTHEME,dirToOpen,NEWpath,result;
    std::string testIndex, fullpath;
    std::string currentTheme = currentIconTheme();
    unsigned int found = 0;
    int sizer = 0;
    //initialize directory reading variables to NULL
    DIR *dir = NULL;
    struct dirent *entryPointer = NULL;

    // if we can't find the xdg paths... return without trying to read them
    if(num_XDG_PATHS==0){return;}

    //lets loop through the xdg paths
    for (int i = 1; i <= num_XDG_PATHS; i++){

        //get the string equvalent for the integer representation if of the xdg path
        // something like
        /*
        1=/usr/share/
        2=/usr/local/share
        etc...
        */
        testPATH = thisXDG_PATH(i);
        std::cerr<<testPATH<<std::endl;
        //make sure this isn't blank
        if(testPATH.compare("")!=0){

            //look to see if we have a / at the end... remove it if we do...
            found = testPATH.find_last_of('/');
            if (found == testPATH.length()-1){testPATH=testPATH.substr(0,testPATH.length()-1);}

            //see if there is an icon directory
            dirToOpen = testPATH + "/icons/";
            dir = opendir(dirToOpen.c_str());
            if (dir!=NULL){
                //std::cout << "Process directory: " << dirToOpen.c_str() << std::endl;
                while ((entryPointer=readdir(dir)) != NULL){
                    if ((entryPointer->d_type == DT_DIR)&&(entryPointer->d_name[0] != '.')){
                        result = entryPointer->d_name;
                        fullpath=dirToOpen+result;
                        testIndex=fullpath+"/index.theme";
                        if(testFile(testIndex.c_str())){themeList.push_back(result.c_str());}
                    }
                }
                closedir(dir);
            }
        }

    }
    themeList.sort();
    themeList.unique();
    std::list<std::string>::iterator it = std::unique (themeList.begin(), themeList.end());
    themeList.resize(std::distance(themeList.begin(),it));
    for(it = themeList.begin(); it != themeList.end(); ++it){
        if(DEBUG_ME){std::cerr << "item: " << *it << "\nCurrent theme: "<<currentTheme<<std::endl;}
        stringTHEME = *it;
        o->add(stringTHEME.c_str());
        if((currentTheme.compare(stringTHEME)==0)&&(currentTheme.compare("")!=0)){
            sizer = o->size();
            if(DEBUG_ME){std::cerr << "Line Number" << sizer << "\nContents: "<<o->text(sizer)<<std::endl;}
        }
    }

    /*TODO:
      find current theme via gtkrc 2.0, gtk 3.0 or gsettings
    */
    o->redraw();
    o->select(sizer);
}

bool flIcons::useTheme(Fl_Browser *o){
    //get the user's choice number
    int themeNumber = o->value();
    //get the text using the number
    const char * item = o->text(themeNumber);
    if(item ==NULL){return false;}
    std::string currentOne= currentIconTheme();
    if(currentOne.compare(item)==0){return false;}
    std::string IconContent=searchthemes(currentOne);
	IconContent+=homeIcons(currentOne);
	return writeToFile(IconContent);
}

const char* flIcons::themegrep(const char* args, const char* filename,int line){
///Return the FIRST match of the 'args' from a file
// this is like  line=`grep $args $filename` that only returns one line
    std::string line2;
    const char* result;
    if(line<0){return "";}
    std::string lengthTEST = args;
    //int lengthofARGS = lengthTEST.length();
    std::ifstream inputFileStrem (filename, std::ifstream::in);
    if(inputFileStrem.is_open()){
        while (getline(inputFileStrem,line2)){
           result=strstr(line2.c_str(),args);
           //std::cout<<line<<std::endl;
            if(result!=NULL){
                return line2.c_str();
            }
        }
    }
    return "";
}
