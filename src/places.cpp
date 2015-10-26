
/*
 * places-menu generator
 * copyright Israel Dahl 2015
 * GPL3 license
 * 
 * But whoso keepeth his word,
 * in him verily is the love of God perfected:
 * hereby know we that we are in him.
 * 
 * 1John2:5 KJV Public Domain
 * 
 * g++ -finline-small-functions -ffunction-sections -fdata-sections -fmerge-all-constants -fomit-frame-pointer -mno-accumulate-outgoing-args -fno-unwind-tables -fno-asynchronous-unwind-tables -Os menu.cpp -o menu
 */

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include <algorithm>
#include <float.h>
#include <sstream>
#include <float.h>
#include <dirent.h>

//global variables
std::string term_out(std::string terminal_Command_You_Want_Output_From);
bool test_file(const char* fileWithFullPATH);
void outXML(std::string message);
///places things
bool check_files();
bool testDir(const char* dirToTest);
//test exec things
bool testEXEC(const char* execToTest);
unsigned int howmanyPATHS();
const char* thisPATH(int whichPath);
//public (global) variables

const char* home;
std::string make_places();
std::string make_gtkplaces();
std::string make_full_menu();
std::string make_submenu_single(std::string whichDir, std::string whatName, std::string whatIcon);
std::string make_submenu(std::string whichDir, std::string whatName, std::string whatIcon, unsigned int levels_deep=0);
std::string subdir(std::string whichDir);
std::string make_home();
int main() {
	home = getenv("HOME");
    if(home==NULL){return 42;}
   const char* path = getenv("PATH");
    if(path==NULL){return 42;}
    //outXML(path);
    std::cout<<"<?xml version=\"1.0\"?>\n<JWM>"<<std::endl;
	std::string result;
	std::string gtk3bm;
	const char* xdg_conf = getenv("XDG_CONFIG_HOME");
	if(xdg_conf == NULL){
		gtk3bm = home;
		gtk3bm += "/.config/gtk-3.0/bookmarks";
	}
	else{
		gtk3bm = xdg_conf;
		gtk3bm += "/gtk-3.0/bookmarks";
	}
	// see what we have to make a menu with...
    if( !test_file(gtk3bm.c_str()) ){
		//NO GTK bookmarks
		if(!check_files()){
			//NO XDG variables
			outXML("HOME menu");
			result = make_home();
		}
		else{
			//XDG menu ONLY
			outXML("XDG Places Menu");
			result = make_places();
		}
	}
	else{
		//we have gtk bookmarks
		if(!check_files()){
			//no xdg variables
			result = make_gtkplaces();
		}
		else{
			//EVERYTHING
			outXML("XDG Places and GTK bookmarks Menu");
			result = make_full_menu();
		}
	}
    std::cout<<result<<"\n</JWM>"<<std::endl;
	return 0;
}
const char* thisPATH(int whichPath){
    unsigned int lastPath = 0;
    std::string result;
    if (whichPath >=1){lastPath = whichPath - 1;}
    else {lastPath = 0;}
    const char* path =getenv("PATH");
    std::string stringPATH;
    if(path == NULL){stringPATH = "/usr/bin";}
	else{stringPATH = path;}
	
    std::string::size_type firstPosition = stringPATH.find(':');
    if(firstPosition>stringPATH.length()){return stringPATH.c_str();}   
    std::string::size_type position = firstPosition;
    for (int i=1;i<=whichPath;i++){position = stringPATH.find(':',position+1);}
    for (unsigned int j=1;j<=lastPath;j++){firstPosition = stringPATH.find(':',firstPosition+1);}
    result = stringPATH.substr (firstPosition+1,((position-firstPosition)-1));
    return result.c_str();
}
unsigned int howmanyPATHS(){
	const char* path =getenv("PATH");
	std::string::size_type pathPosition =0;
	if(path==NULL){return 1;}
	std::string stringPATH = path;
	unsigned int howmany;
    for(howmany=1;(pathPosition!=std::string::npos);howmany++){
        pathPosition=stringPATH.find(':', pathPosition+1);
    }
    return howmany;
}
bool testEXEC(const char* execToTest){
	if(execToTest==NULL){return false;}
    std::string stringEXEC = execToTest;
	/// my cheat sheet
	//outXML("exec: " + stringEXEC);
	// /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
	std:: string testPATH, testExec;
	bool result = false;
	unsigned int numofpaths = howmanyPATHS();
    for (unsigned int i = 1; i <= numofpaths; i++){
		stringEXEC = execToTest;
        testPATH = thisPATH(i);
        
        stringEXEC = testPATH + "/" + stringEXEC;
        //outXML("testing:: "+stringEXEC);
        if ( test_file( stringEXEC.c_str() ) ){return true;}
    }
	return result;
}
bool testDir(const char* dirToTest){
	if(dirToTest==NULL){return false;}
	DIR *dir = NULL;
	dir = opendir(dirToTest);
	if (dir!=NULL){
		closedir(dir);
		return true;
	}	
	return false;
}

bool check_files(){
// make sure the directories exist
    std::string configDir;
    testDir(configDir.c_str());
    //[ -d "${HOME}"/.config ] || mkdir "${HOME}"/.config

	// XDG DIRS
	// Lets make sure they have the file first
	const char* xdg_conf = getenv("XDG_CONFIG_HOME");
	if(xdg_conf ==NULL){
		const char* thaConfigDir = getenv("HOME");
		if(thaConfigDir == NULL){return false;}
		configDir = thaConfigDir;
		configDir+="/.config";
	}
	else{configDir=xdg_conf;}
	
	std::string userdirsfile= configDir + "user-dirs.dirs";
	if (!test_file(userdirsfile.c_str())){
	// if not see if we can make it
		if ( !testEXEC("xdg-user-dirs-update")){
			outXML("xdg-user-dirs-update doesn't exist in the PATH:( Please install it");
			return false;
		}
		else{system("xdg-user-dirs-update");}
		if (!testEXEC("xdg-user-dir")){
			outXML("xdg-user-dir doesn't exist in the PATH :( Please install it!");
			return false;
		}
	}
	return true;
}
std::string make_places(){
// these are all the XDG variables we want

//Not sure if we want these though...
#if 0
	std::string PUBLICSHARE=term_out(XDG_COMM + " PUBLICSHARE");
	std::string TEMPLATES=term_out(XDG_COMM + " TEMPLATES");
	std::string DESKTOP=term_out(XDG_COMM + " DESKTOP");
	std::string DESKTOP_NAME= DESKTOP;
	DESKTOP_NAME = DESKTOP_NAME.erase(0,length);
	std::string PUBLICSHARE_NAME= PUBLICSHARE;
	PUBLICSHARE_NAME = PUBLICSHARE_NAME.erase(0,length);
	std::string TEMPLATES_NAME= TEMPLATES;
	TEMPLATES_NAME = TEMPLATES_NAME.erase(0,length);
#endif
	
	//This is the stuff we really want
	std::string XDG_COMM="xdg-user-dir";
	std::string DOCUMENTS=term_out(XDG_COMM + " DOCUMENTS");
	std::string DOWNLOADS=term_out(XDG_COMM + " DOWNLOAD");
	std::string MUSIC=term_out(XDG_COMM + " MUSIC");
	std::string PICTURES=term_out(XDG_COMM + " PICTURES");
	std::string VIDEOS=term_out(XDG_COMM + " VIDEOS");

    std::string HOME = home;
	unsigned int length = HOME.length();
	length++;
	std::string VIDEOS_NAME= VIDEOS;
	VIDEOS_NAME = VIDEOS_NAME.erase(0,length);
	std::string DOCUMENTS_NAME = DOCUMENTS;
	DOCUMENTS_NAME = DOCUMENTS_NAME.erase(0,length);
	std::string DOWNLOADS_NAME= DOWNLOADS;
	DOWNLOADS_NAME = DOWNLOADS_NAME.erase(0,length);
	std::string MUSIC_NAME= MUSIC;
	MUSIC_NAME = MUSIC_NAME.erase(0,length);
	std::string PICTURES_NAME= PICTURES;
	PICTURES_NAME = PICTURES_NAME.erase(0,length);
	
	//temporary... eventually check file for this..
	std::string HOME_NAME;
	const char* user=getenv("USER");
	if(user != NULL){
		 HOME_NAME=user;
	}
	else{
		 HOME_NAME=term_out(XDG_COMM + " HOME");
		 HOME_NAME= HOME_NAME.erase(0,5);
	}
	
	std::string HOME_ICON="folder-home";
	std::string DOCUMENTS_ICON="folder-documents";
	std::string DOWNLOADS_ICON="folder-downloads";
	std::string MUSIC_ICON="folder-music";
	std::string PICTURES_ICON="folder-pictures";
	std::string VIDEOS_ICON="folder-video";
	std::string FOLDER_ICON="folder";
	std::string TRASH = HOME;
	std::string TRASH_NAME=" ";
	std::string TRASH_ICON="user-trash";
	//Make the menu...
	std::string MENU = make_submenu(HOME,HOME_NAME,HOME_ICON);
	MENU += make_submenu(DOCUMENTS,DOCUMENTS_NAME,DOCUMENTS_ICON);
	MENU += make_submenu( DOWNLOADS, DOWNLOADS_NAME, DOWNLOADS_ICON);
	MENU += make_submenu(MUSIC ,MUSIC_NAME, MUSIC_ICON);
	MENU += make_submenu( PICTURES, PICTURES_NAME, PICTURES_ICON);
	MENU += make_submenu(VIDEOS , VIDEOS_NAME, VIDEOS_ICON);
	TRASH+="/.local/share/Trash/files";
	MENU += make_submenu_single(TRASH , TRASH_NAME, TRASH_ICON);
	return MENU;
}
std::string make_full_menu(){
	std::string filename;
	const char* xdg_conf = getenv("XDG_CONFIG_HOME");
	const char* tempfile = getenv("HOME");
		if(tempfile == NULL){return "";}
	if(xdg_conf ==NULL){
		if(tempfile == NULL){return "";}
		filename = tempfile;
		filename += "/.config/";
	}
	else{filename = xdg_conf;}
	filename += "/gtk-3.0/bookmarks";
	//check for file or simply run make_places();
	if(!test_file(filename.c_str()) ){make_places();}
	
	std::string XDG_COMM="xdg-user-dir";
	std::string DOCUMENTS=term_out(XDG_COMM + " DOCUMENTS");
	std::string DOWNLOADS=term_out(XDG_COMM + " DOWNLOAD");
	std::string MUSIC=term_out(XDG_COMM + " MUSIC");
	std::string PICTURES=term_out(XDG_COMM + " PICTURES");
	std::string VIDEOS=term_out(XDG_COMM + " VIDEOS");

    std::string HOME = home;
	unsigned int length = HOME.length();
	length++;
	std::string VIDEOS_NAME= VIDEOS;
	VIDEOS_NAME = VIDEOS_NAME.erase(0,length);
	std::string DOCUMENTS_NAME = DOCUMENTS;
	DOCUMENTS_NAME = DOCUMENTS_NAME.erase(0,length);
	std::string DOWNLOADS_NAME= DOWNLOADS;
	DOWNLOADS_NAME = DOWNLOADS_NAME.erase(0,length);
	std::string MUSIC_NAME= MUSIC;
	MUSIC_NAME = MUSIC_NAME.erase(0,length);
	std::string PICTURES_NAME= PICTURES;
	PICTURES_NAME = PICTURES_NAME.erase(0,length);
	
	//temporary... eventually check file for this..
	std::string HOME_NAME;
	const char* user=getenv("USER");
	if(user != NULL){
		 HOME_NAME=user;
	}
	else{
		 HOME_NAME=term_out(XDG_COMM + " HOME");
		 HOME_NAME= HOME_NAME.erase(0,5);
	}
	
	std::string HOME_ICON="folder-home";
	std::string DOCUMENTS_ICON="folder-documents";
	std::string DOWNLOADS_ICON="folder-downloads";
	std::string MUSIC_ICON="folder-music";
	std::string PICTURES_ICON="folder-pictures";
	std::string VIDEOS_ICON="folder-video";
	std::string FOLDER_ICON="folder";
	std::string TRASH =term_out(XDG_COMM + " HOME");
	TRASH += "/.local/share/Trash/files";
	std::string TRASH_NAME=" ";
	std::string TRASH_ICON="user-trash";
	std::string MENU;
	
	if(tempfile != NULL){
		std::string tempHome = tempfile;
		MENU += make_submenu_single(tempHome,HOME_NAME,HOME_ICON);
	}
	//Make the menu...
	unsigned int found;
	std::string comparename,whatName,line;
	std::ifstream inputFileStrem (filename.c_str(), std::ifstream::in);	
	if(inputFileStrem.is_open()){
		while (getline(inputFileStrem,line)!=NULL){
			found=line.find_first_of(':');
			if(found < line.length()){
				line=line.erase(0,found+3);
				comparename=line;
				found = comparename.find_last_of('/');
				if(found < comparename.length()){
					comparename=comparename;
				}
			}
			whatName = line;
			found=line.find_first_of(' ');
			if(found< line.length()){
				whatName = whatName.erase(0,found+1);
				line=line.erase(found,std::string::npos);
				while ( line.find("%20")<line.length() ){
					found = line.find("%20");
					if(found < line.length() ){
						std::string temp1 = line;
						std::string temp2 = line;
						temp1 = temp1.erase(found, std::string::npos);
						temp2 = temp2.erase(0,found+3);
						line = temp1 + "\\ " + temp2;
				  
					}
				}
			}
			//
			unsigned int xmlfix;
			unsigned int oldFind =1;
			while(whatName.find('&',oldFind)<whatName.length()){
				xmlfix = whatName.find('&',oldFind);
				oldFind=xmlfix+4;
				std::string amp="&amp;";
				std::string ampPRE,ampPOST,tempAMP;
				if(xmlfix<whatName.length()){
					tempAMP=whatName;
					ampPOST=whatName;
					ampPRE = tempAMP.erase(xmlfix,std::string::npos);
					ampPOST = whatName.erase(0,xmlfix+1);
					whatName = ampPRE + amp + ampPOST;
				}
			}
			if( (line.compare(DOCUMENTS)==0) || (whatName.compare(DOCUMENTS_NAME)==0) ){
				MENU += make_submenu(DOCUMENTS,DOCUMENTS_NAME,DOCUMENTS_ICON);
			}
			else if( (line.compare(DOWNLOADS)==0) || (whatName.compare(DOWNLOADS_NAME)==0) ){
				MENU += make_submenu( DOWNLOADS, DOWNLOADS_NAME, DOWNLOADS_ICON);
			}
			else if( (line.compare(MUSIC)==0) || (whatName.compare(MUSIC_NAME)==0) ){
				MENU += make_submenu(MUSIC ,MUSIC_NAME, MUSIC_ICON);
			}
			else if( (line.compare(PICTURES)==0) || (whatName.compare(PICTURES_NAME)==0) ){
				MENU += make_submenu( PICTURES, PICTURES_NAME, PICTURES_ICON);
			}
			else if( (line.compare(VIDEOS)==0) || (whatName.compare(VIDEOS_NAME)==0) ){
				MENU += make_submenu(VIDEOS , VIDEOS_NAME, VIDEOS_ICON);
			}
			else{
				oldFind=1;
				while(line.find('&',oldFind)<line.length()){
				xmlfix = line.find('&',oldFind);
				oldFind=xmlfix+4;
				std::string amp="&amp;";
				std::string ampPRE,ampPOST,tempAMP;
				if(xmlfix<line.length()){
					tempAMP=line;
					ampPOST=line;
					ampPRE = tempAMP.erase(xmlfix,std::string::npos);
					ampPOST = line.erase(0,xmlfix+1);
					line = ampPRE + amp + ampPOST;
				}
			}
				MENU+=make_submenu(line, whatName,FOLDER_ICON);
			}
		}
	}
	else{outXML("inputFileStream didn't open..");}
	std::string blankname=" "; 
	MENU += make_submenu_single(TRASH , TRASH_NAME, TRASH_ICON);
	return MENU;
}
std::string make_home(){
	std::string MENU,ITEM,shortname,thisdir,dirToOpen;
	DIR *dir = NULL;
    struct dirent *entryPointer = NULL;
    unsigned int finder = 0;
    unsigned int len = 0;
    //make the initial Root opener
	std::string FOLDER_OPEN_ICON = "folder-open";
	std::string FOLDER_ICON = "folder";
	const char* file = getenv("HOME");
	if(file == NULL) {return "There is a problem... you have no $HOME";}
	dirToOpen=file;
	//make sure this isn't blank
	if(dirToOpen.compare("")!=0){
		dir = opendir(dirToOpen.c_str());
		if (dir!=NULL){
			while ((entryPointer=readdir(dir)) != NULL){
				if ((entryPointer->d_type == DT_DIR)&&(entryPointer->d_name[0] != '.')){
					thisdir=dirToOpen;
					len = thisdir.length();
					finder = thisdir.find_last_of('/');
					if(finder != len){
						thisdir+="/";
					}
					thisdir+=entryPointer->d_name;
					shortname=entryPointer->d_name;
					unsigned int xmlfix;
					unsigned int oldFind =1;
					while(shortname.find('&',oldFind)<shortname.length()){
						xmlfix = shortname.find('&',oldFind);
						oldFind=xmlfix+4;
						std::string amp="&amp;";
						std::string ampPRE,ampPOST,tempAMP;
						if(xmlfix<shortname.length()){
							tempAMP=shortname;
							ampPOST=shortname;
							ampPRE = tempAMP.erase(xmlfix,std::string::npos);
							ampPOST = shortname.erase(0,xmlfix+1);
							shortname = ampPRE + amp + ampPOST;
						}
					}
					MENU+=make_submenu(thisdir,shortname,FOLDER_ICON);
					}
			}
			closedir(dir);
		}
	}
	return MENU;
}
std::string make_gtkplaces(){
	std::string MENU;
	std::string HOME_ICON="folder-home";
	std::string DOCUMENTS_ICON="folder-documents";
	std::string DOWNLOADS_ICON="folder-downloads";
	std::string MUSIC_ICON="folder-music";
	std::string PICTURES_ICON="folder-pictures";
	std::string VIDEOS_ICON="folder-video";
	std::string FOLDER_ICON="folder";
	std::string TRASH_ICON="user-trash";
	std::string HOME = getenv("HOME");
	std::string TRASH = HOME;
	std::string line,filename,whatName;
	const char* xdg_conf = getenv("XDG_CONFIG_HOME");
	if(xdg_conf ==NULL){
		const char* temphome = getenv("HOME");
		if(temphome!=NULL){
			filename =temphome;
			filename+="/.config";
		}
		else{return "";}
	}
	else{filename = xdg_conf;}
	filename += "/gtk-3.0/bookmarks";
	if(!test_file(filename.c_str()) ){outXML(filename+" didn't exist");make_places();}
	else{outXML(filename + " exists");}
	unsigned int found;
	std::string comparename;
	std::ifstream inputFileStrem (filename.c_str(), std::ifstream::in);
	if(inputFileStrem.is_open()){
		while (getline(inputFileStrem,line)!=NULL){
			found=line.find_first_of(':');
			if(found < line.length()){
				line=line.erase(0,found+3);
				comparename=line;
				found = comparename.find_last_of('/');
				if(found < comparename.length()){
					comparename=comparename;
				}
			}
			whatName = line;
			found=line.find_first_of(' ');
			if(found< line.length()){
				whatName = whatName.erase(0,found+1);
				line=line.erase(found,std::string::npos);
				while ( line.find("%20")<line.length() ){
					found = line.find("%20");
					if(found < line.length() ){
						std::string temp1 = line;
						std::string temp2 = line;
						temp1 = temp1.erase(found, std::string::npos);
						temp2 = temp2.erase(0,found+3);
						line = temp1 + "\\ " + temp2;
				  
					}
				}
			}
			unsigned int xmlfix;
			unsigned int oldFind =1;
			while(whatName.find('&',oldFind)<whatName.length()){
				xmlfix = whatName.find('&',oldFind);
				oldFind=xmlfix+4;
				std::string amp="&amp;";
				std::string ampPRE,ampPOST,tempAMP;
				if(xmlfix<whatName.length()){
					tempAMP=whatName;
					ampPOST=whatName;
					ampPRE = tempAMP.erase(xmlfix,std::string::npos);
					ampPOST = whatName.erase(0,xmlfix+1);
					whatName = ampPRE + amp + ampPOST;
				}
			}
			MENU+=make_submenu(line, whatName,FOLDER_ICON);
          }
      }
      else{outXML("inputFileStream didn't open: "+filename);}
      std::string blankname=" "; 
      TRASH+="/.local/share/Trash/files";
      MENU+=make_submenu_single(TRASH,blankname,TRASH_ICON);
	return MENU;
}
std::string make_submenu_single(std::string whichDir, std::string whatName, std::string whatIcon){
	//this is mostly for Trash
	std::string MENU;
	unsigned int xmlfix;
	unsigned int oldFind =1;
	while(whatName.find('&',oldFind)<whatName.length()){
		xmlfix = whatName.find('&',oldFind);
		oldFind=xmlfix+4;
		std::string amp="\\&amp;";
		std::string ampPRE,ampPOST,tempAMP;
		if(xmlfix<whatName.length()){
			tempAMP=whatName;
			ampPOST=whatName;
			ampPRE = tempAMP.erase(xmlfix,std::string::npos);
			ampPOST = whatName.erase(0,xmlfix+1);
			whatName = ampPRE + amp + ampPOST;
		}
	}
	oldFind =1;
	while(whichDir.find(' ',oldFind)<whichDir.length()){
		xmlfix = whichDir.find(' ',oldFind);
		std::string amp="\\ ";
		oldFind=xmlfix+amp.length();
		std::string ampPRE,ampPOST,tempAMP;
		if(xmlfix<whichDir.length()){
				tempAMP=whichDir;
				ampPOST=whichDir;
				ampPRE = tempAMP.erase(xmlfix,std::string::npos);
				ampPOST = whichDir.erase(0,xmlfix+1);
				whichDir = ampPRE + amp + ampPOST;
		}
	}
	MENU="\t<Program icon=\"" + whatIcon + "\" label=\"" + whatName + "\">xdg-open ";
	MENU+=whichDir;
	MENU +="</Program>\n";
	return MENU;
}
std::string make_submenu(std::string dirToOpen, std::string whatName, std::string whatIcon,unsigned int levels_deep){
	std::string MENU,ITEM,shortname,thisdir;
	DIR *dir = NULL;
    struct dirent *entryPointer = NULL;
    unsigned int finder = 0;
    unsigned int len = 0;
    //make the initial Root opener
    thisdir = dirToOpen;
	std::string FOLDER_OPEN_ICON = "folder-open";
	ITEM+="\t<Program icon=\"" + FOLDER_OPEN_ICON + "\" label=\" \">xdg-open ";
	ITEM+=thisdir;
	ITEM +="</Program>\n";
	std::string FOLDER_ICON = "folder";
	MENU = "\t<Menu label=\"" + whatName + "\" icon=\"" + whatIcon + "\" height=\"0\">\n";
	for (unsigned int i = 0; i <=  levels_deep; i++){
		//make sure this isn't blank
		if(dirToOpen.compare("")!=0){
			dir = opendir(dirToOpen.c_str());
			if (dir!=NULL){
				while ((entryPointer=readdir(dir)) != NULL){
					if ((entryPointer->d_type == DT_DIR)&&(entryPointer->d_name[0] != '.')){
						thisdir=dirToOpen;
						len = thisdir.length();
						finder = thisdir.find_last_of('/');
						if(finder != len){
							thisdir+="/";
						}
						thisdir+=entryPointer->d_name;
						shortname=entryPointer->d_name;
						unsigned int xmlfix;
						unsigned int oldFind =1;
						while(shortname.find('&',oldFind)<shortname.length()){
						xmlfix = shortname.find('&',oldFind);
							std::string amp="&amp;";
							oldFind=xmlfix+amp.length();
							std::string ampPRE,ampPOST,tempAMP;
							if(xmlfix<shortname.length()){
								tempAMP=shortname;
								ampPOST=shortname;
								ampPRE = tempAMP.erase(xmlfix,std::string::npos);
								ampPOST = shortname.erase(0,xmlfix+1);
								shortname = ampPRE + amp + ampPOST;
							}
						}
						
						oldFind =1;
						while(thisdir.find('&',oldFind)<thisdir.length()){
						xmlfix = thisdir.find('&',oldFind);
							std::string amp="\\&amp;";
							oldFind=xmlfix+amp.length();
							std::string ampPRE,ampPOST,tempAMP;
							if(xmlfix<thisdir.length()){
								tempAMP=thisdir;
								ampPOST=thisdir;
								ampPRE = tempAMP.erase(xmlfix,std::string::npos);
								ampPOST = thisdir.erase(0,xmlfix+1);
								thisdir = ampPRE + amp + ampPOST;
							}
						}
						oldFind =1;
						while(thisdir.find(' ',oldFind)<thisdir.length()){
						xmlfix = thisdir.find(' ',oldFind);
							std::string amp="\\ ";
							oldFind=xmlfix+amp.length();
							std::string ampPRE,ampPOST,tempAMP;
							if(xmlfix<thisdir.length()){
								tempAMP=thisdir;
								ampPOST=thisdir;
								ampPRE = tempAMP.erase(xmlfix,std::string::npos);
								ampPOST = thisdir.erase(0,xmlfix+1);
								thisdir = ampPRE + amp + ampPOST;
							}
						}
						ITEM+="\t<Program icon=\"" + FOLDER_ICON + "\" label=\"" + shortname + "\">xdg-open ";
						ITEM+=thisdir;
						ITEM +="</Program>\n";
					}
				}
				closedir(dir);
			}
			else{outXML("Couldn't open: "+dirToOpen);}
		}
	}

	
	MENU+=ITEM;
	MENU +="\n\t</Menu>\n";
	return MENU;
}
std::string subdir(std::string whichDir){
	return "NOTHING!!!!!!!!!!!!";
}
void outXML(std::string message){
	std::cout<<"<!-- "<<message<<" -->"<<std::endl;
	}


std::string term_out(std::string terminal_Command_You_Want_Output_From) {
  std::string result="";
  const int max_buffer = 1024;
  char buffer[max_buffer];
  FILE *command_p = popen(terminal_Command_You_Want_Output_From.c_str(), "r");
  if (command_p){
    while(!feof(command_p)){
      if( fgets(buffer, sizeof(buffer), command_p) !=NULL){
        result.append(buffer);
      }
    }
    pclose(command_p);
  }
  else{ return "[returnTerminalOutput] Error from command run";}
  int end = result.length();
  if((end-1) == 0){return "";}
  return result.erase(end-1,end);
}
bool test_file(const char* fileWithFullPATH) {
  if(fileWithFullPATH==NULL){return false;}
  struct stat buffer;
  return (stat (fileWithFullPATH, &buffer) == 0);
}
