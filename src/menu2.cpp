/*
 * jwm-menu generator
 * copyright Israel Dahl 2015
 * GPL3 license
 * 
 * But whoso keepeth his word,
 * in him verily is the love of God perfected:
 * hereby know we that we are in him.
 * 
 * 1John2:5 KJV Public Domain
 * 
 * g++ -finline-small-functions -ffunction-sections -fdata-sections -fmerge-all-constants -fomit-frame-pointer -mno-accumulate-outgoing-args -fno-unwind-tables -fno-asynchronous-unwind-tables -Os menu2.cpp -o menu2
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
std::string xdg_paths;
std::string stringXDG_PATH;
std::string::size_type XDG_pathPosition;
int num_XDG_PATHS;
std::vector<std::string> desktop_paths();
std::string loop_desktopfiles(std::string categoryToGet,std::string dirToOpen);
std::string grep(std::string args, std::string filename);
std::string get_line(std::string filename, std::string line);
std::string get_name(std::string filename);
std::string make_menu(int cat);
std::string term_out(std::string terminal_Command_You_Want_Output_From);
bool test_file(const char* fileWithFullPATH);
bool no_display(std::string filename);
bool only_show(std::string filename);
bool not_showin(std::string filename);
std::string exec_line(std::string filename);
std::string icon_line(std::string filename);
std::string name_line(std::string filename);
std::string cat_line(std::string filename);
std::string set_xdg_paths();
unsigned int numXDG_PATHS();
const char* thisXDG_PATH(int whichPath);
std::string getDefaultFilepath(std::string pathToGet);
void outXML(std::string message);
std::string showCategories();
int main(int argc, char *argv[]) {
	std::string command;
	int cat;
	/*
	 * acc 0
	 * art 1
	 * av 2
	 * dev 3
	 * ed 4
	 * game 5
	 * net 6
	 * off 7
	 * sett 8
	 * sys 9
	 */
	std::cout<<"<?xml version=\"1.0\"?>\n<JWM>"<<std::endl;
    xdg_paths = set_xdg_paths();
    stringXDG_PATH = xdg_paths;
    XDG_pathPosition = stringXDG_PATH.find_first_of(':');
    num_XDG_PATHS = numXDG_PATHS();
    std::string result;
    cat=0;
    if(argc>0){
        for(int i=1;i<argc;++i){
            command=argv[i];
            for(int i=0;i<argc;i++){
                if((command.compare("--acc")==0)||(command.compare("-a")==0)){
                    cat=10;

                }
                else if((command.compare("--art")==0)||(command.compare("-r")==0)){
                    cat=1;

                }
                else if((command.compare("--av")==0)||(command.compare("-v")==0)){
                    cat=2;

                }
                else if((command.compare("--dev")==0)||(command.compare("-d")==0)){
                    cat=3;

                }
                else if((command.compare("--ed")==0)||(command.compare("-e")==0)){
                    cat=4;

                }
                else if((command.compare("--game")==0)||(command.compare("-g")==0)){
                    cat=5;

                }
                else if((command.compare("--net")==0)||(command.compare("-n")==0)){
                    cat=6;

                }
                else if((command.compare("--off")==0)||(command.compare("-o")==0)){
                    cat=7;

                }
                else if((command.compare("--sett")==0)||(command.compare("-s")==0)){
                    cat=8;

                }
                else if((command.compare("--sys")==0)||(command.compare("-y")==0)){
                    cat=9;

                }
            }
        }
    }
    if(cat==0){
        result=showCategories();
    }
	if((cat<11)&&(cat>0)){result = make_menu(cat);}
    std::cout<<result<<"\n</JWM>"<<std::endl;
	return 0;
}
void outXML(std::string message){
	std::cout<<"<!--"<<message<<"-->"<<std::endl;
	}
std::string grep(std::string args, std::string filename) {
  ///Return the FIRST match of the 'args' from a file
  // this is like  line=`grep $args $filename` that only returns one line
      std::string line;
      int lengthofARGS = args.length();
      std::string subString;
      std::ifstream inputFileStrem (filename.c_str(), std::ifstream::in);
      if(inputFileStrem.is_open()){
          while (getline(inputFileStrem,line)){
              subString=line.substr(0,lengthofARGS);
              if(subString.compare(args)==0){return line;}
          }
      }
      return "";
}

std::string get_line(std::string filename, std::string line) {
  std::string LINE = grep(line,filename);
  unsigned int args = 0, equals = 0;
  args = LINE.find("%");
  // remove only 2 characters  maybe later check to see if there is a space after it to determine if it is a shell script 
  if (args < LINE.length())LINE = LINE.erase(args,2);
  equals = LINE.find("=");
  if (equals < LINE.length())LINE= LINE.erase(0,equals+1);
  return LINE;
}

std::string get_name(std::string filename){
  std::string tryGet,tempstr;
  std::string name="Name";
  std::string mylang = getenv("LANGUAGE");
  if(mylang.compare("")==0){
     mylang = getenv("LANG");
     unsigned int found = mylang.find('.');
     if(found < mylang.length()){
		mylang = mylang.erase(found,std::string::npos);
		tempstr=name;
		tempstr+="[";
		tempstr+=mylang;
		tempstr+="]=";
		tryGet=get_line(filename,tempstr);
	}
  }
  else{
     tempstr=name;
     tempstr+="[";
     tempstr+=mylang;
     tempstr+="]=";
     tryGet=get_line(filename,tempstr);
  }
  if( (tryGet.compare("")==0) && (mylang.compare("")!=0) ){
	unsigned int dash = mylang.find('_');
	if(dash<mylang.length()){
		mylang = mylang.erase(dash,std::string::npos);
		tempstr=name;
		tempstr+="[";
		tempstr+=mylang;
		tempstr+="]=";
		tryGet=get_line(filename,tempstr);
	}
  }
  if (tryGet.compare("")==0){
    tryGet=get_line(filename,"Name=");
  }
  return tryGet;
}
std::string loop_desktopfiles(std::string categoryToGet,std::string dirToOpen){
	std::string category,MenuEntry,EXEC,ICON,NAME,tester,result,fullpath,returnCAT;
	
		//dirent
	DIR *dir = NULL;
	struct dirent *entryPointer = NULL;
	dir = opendir(dirToOpen.c_str());
	std::string amp="&amp;";
	std::string ampPRE,ampPOST,tempAMP;
	//int
	if (dir!=NULL){
		while ((entryPointer=readdir(dir)) != NULL){
			if ((entryPointer->d_type == DT_REG)&&(entryPointer->d_name[0] != '.')){
				fullpath = entryPointer->d_name;
				result=dirToOpen+fullpath;
				tester=dirToOpen+fullpath;
				unsigned period = result.find_last_of(".");
				bool isDESKTOP = false;
				if(result.compare("")!=0){
					if(period<result.length()){
						std::string testDesktop = result.substr(period+1,std::string::npos);
						if(testDesktop.compare("desktop")==0){isDESKTOP = true;}
					}
				//make a line if it is a desktop
				if(isDESKTOP){
					if( (no_display(result)) || !(only_show(result)) || (not_showin(result)) ){
                        //outXML(result);
					}
					else{

					NAME=name_line(result);
					unsigned int xmlfix = NAME.find('&');
					if(xmlfix<NAME.length()){
						tempAMP=NAME;
						ampPOST=NAME;
						ampPRE = tempAMP.erase(xmlfix,std::string::npos);
						ampPOST = NAME.erase(0,xmlfix+1);
						NAME = ampPRE + amp + ampPOST;
					}
					ICON=icon_line(result);
					EXEC=exec_line(result);
					MenuEntry="\t\t<Program label=\""+NAME+"\" icon=\""+ICON+"\">"+EXEC+"</Program>\n";
					category=cat_line(result);
					//outXML(category);
					//outXML(result);

					if( category.compare(categoryToGet)==0){returnCAT+=MenuEntry;}
				}//nodisplay/notshow//onlyshow
			} //isDesktop
          }//result !empty
       }//dirent is file
     }//dirent !NULL
  }//directory !NULL
  closedir(dir);
 // outXML(returnCAT);
  return returnCAT;
}
std::string make_menu(int cat){
	std::string MenuEntry,NAME,ICON,EXEC,CATS,TERMIE,AV,DEV,ED,GAME,ART,NET,OFF,SCI,SET,SYS,ACC,category,testPATH;
	std::string AV1,DEV1,ED1,GAME1,ART1,NET1,OFF1,SCI1,SET1,SYS1,ACC1;
	AV1="0";
	DEV1="0";
	ED1="0";
	GAME1="0";
	ART1="0";
	NET1="0";
	OFF1="0";
	SCI1="0";
	SET1="0";
	SYS1="0";
	ACC1="0";
	//TODO: XDG paths
	std::string dirToOpen = "/usr/share/applications/";
	std::string pathToGet = "/applications/";
	std::string fullpath, result, name, icon, exec, tester, cattie;
	std::string myterm=term_out("which x-terminal-emulator || which xterm");
	///Localization Directory files
	std::string DIR_EXT = ".directory";
	std::string INTRO = "jwm";
	std::string iconEQ = "Icon=";
	std::string MENU;	
	std::vector<std::string> uniqueDirs = desktop_paths();
	unsigned int found = 0;
    //initialize directory reading variables to NULL
    DIR *dir = NULL;
    struct dirent *entryPointer = NULL;

		//lets loop through the xdg paths
		//for (int i = 1; i <= num_XDG_PATHS; i++){
		for( std::vector<std::string>::iterator it = uniqueDirs.begin();
			it!=uniqueDirs.end();
			++it){
        //get the string equvalent for the integer representation if of the xdg path
        // something like
        /*
        1=/usr/share/
        2=/usr/local/share
        etc...
        */
			testPATH = *it;
			//outXML(testPATH);
			//make sure this isn't blank
			if(testPATH.compare("")!=0){
				//look to see if we have a / at the end... remove it if we do...
				found = testPATH.find_last_of('/');
				if (found == testPATH.length()-1){testPATH=testPATH.substr(0,testPATH.length()-1);}
				//see if there is a pathToGet directory
				dirToOpen = testPATH + pathToGet;
				//outXML(dirToOpen);
				dir = opendir(dirToOpen.c_str());
				if (dir!=NULL){
					while ((entryPointer=readdir(dir)) != NULL){
						if (entryPointer->d_type == DT_DIR){ //&&(entryPointer->d_name[0] != '.')
							//outXML(dirToOpen);
	switch (cat){
		case 10:
			if(ACC.compare(ACC1)!=0){ACC+=loop_desktopfiles("Utility",dirToOpen);}
			if(ACC.compare("")!=0){ACC1 = ACC;}
			break;
		case 1:
			if(ART.compare(ART1)!=0){ART+=loop_desktopfiles("Graphics",dirToOpen);}
			if(ART.compare("")!=0){ART1 = ART;}
			break;
		case 2:
			if(AV.compare(AV1)!=0){AV+=loop_desktopfiles("AudioVideo",dirToOpen);}
			if(AV.compare("")!=0){AV1 = AV;}
			break;
		case 3:
			if(DEV.compare(DEV1)!=0){DEV+=loop_desktopfiles("Development",dirToOpen);}
			if(DEV.compare("")!=0){DEV1 = DEV;}
			break;
		case 4:
			if(ED.compare(ED1)!=0){ED+=loop_desktopfiles("Education",dirToOpen);}
			if(ED.compare("")!=0){ED1 = ED;}
			break;
		case 5:
			if(GAME.compare(GAME1)!=0){GAME+=loop_desktopfiles("Game",dirToOpen);}
			if(GAME.compare("")!=0){GAME1 = GAME;}
			break;
		case 6:
			if(NET.compare(NET1)!=0){NET+=loop_desktopfiles("Network",dirToOpen);}
			if(NET.compare("")!=0){NET1 = NET;}
			break;
		case 7:
			if(OFF.compare(OFF1)!=0){OFF+=loop_desktopfiles("Office",dirToOpen);}
			if(OFF.compare("")!=0){OFF1 = OFF;}
			break;
		case 8:
			if(SET.compare(SET1)!=0){SET+=loop_desktopfiles("Settings",dirToOpen);}
			if(SET.compare("")!=0){SET1 = SET;}
			break;
		case 9:
			if(SYS.compare(SYS1)!=0){SYS+=loop_desktopfiles("System",dirToOpen);}
			if(SYS.compare("")!=0){SYS1 = SYS;}
			break;
		default :
		    break;
	}
	
	}
	//outXML(AV1 + ":" + DEV1 + ":" + ED1 + ":" + GAME1 + ":" + ART1 + ":" + NET1 + ":" + OFF1 + ":" + SCI1 + ":" + SET1 + ":" + SYS1 + ":" + ACC1 + ":" + AV + ":" + DEV + ":" + ED + ":" + GAME + ":" + ART + ":" + NET + ":" + OFF + ":" + SCI + ":" + SET + ":" + SYS + ":" + ACC);
						}
					}
				}
				closedir(dir);
			}
if((ACC.compare("")!=0) && ( cat == 10)){MENU+=ACC;}
if((ART.compare("")!=0) && ( cat == 1)){MENU+=ART;}
if((AV.compare("")!=0) && ( cat == 2)){MENU+=AV;}
if((DEV.compare("")!=0) && ( cat == 3)){MENU+=DEV;}
if((ED.compare("")!=0) && ( cat == 4)){MENU+=ED;}
if((GAME.compare("")!=0) && ( cat == 5)){MENU+=GAME;}
if((NET.compare("")!=0) && ( cat == 6)){MENU+=NET;}
if((OFF.compare("")!=0) && ( cat == 7)){MENU+=OFF;}
if((SET.compare("")!=0) && ( cat == 8)){MENU+=SET;}
if((SYS.compare("")!=0) && ( cat == 9)){MENU+=SYS;}
  return MENU;
}//make_menu

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

bool no_display(std::string filename) {
  std::string result = get_line(filename,"NoDisplay=");
  if(result.compare("")==0){
    return false;
  }
  std::transform(result.begin(),result.end(),result.begin(),::tolower);
  if (result.compare("true")==0){return true;}
  else{return false;}

  return false;
}

bool only_show(std::string filename) {
  char* desktop = getenv("XDG_CURRENT_DESKTOP");
  char* desktop_session = getenv("DESKTOP_SESSION");
  std::string result = get_line(filename,"OnlyShowIn=");
  unsigned int found = 0;
  if(result.compare("")==0){
  //Only show in line doesn't exist
    return true;
  }
  //compare lower case words only
  std::transform(result.begin(),result.end(),result.begin(),::tolower);

  std::string temp1,temp2;
  temp2=result;

  for(unsigned int i = 0; i<result.length();i++){
    found = temp2.find_first_of(';');
    if(found < temp2.length()){
      temp2=temp2.erase(found,temp2.length());
      temp1 = result.erase(0,found+1);
      if (desktop !=NULL){
        if (temp2.compare(desktop)==0){return true;}
      }
      if (desktop_session !=NULL){
        if(temp2.compare(desktop_session)==0){return true;}
      }
      if (temp2.compare("unity")==0){return true;}
      temp2=temp1;
     }
     else{

     }
  }
  return false;
}

bool not_showin(std::string filename) {
  char* desktop = getenv("XDG_CURRENT_DESKTOP");
  char* desktop_session = getenv("DESKTOP_SESSION");
  std::string result = get_line("NotShowIn=",filename);
  unsigned int found = 0;
  if(result.compare("")==0){
    return false;
  }
  std::transform(result.begin(),result.end(),result.begin(),::tolower);
  std::string temp1,temp2;
  temp2=result;
  for(unsigned int i = 0; i<result.length();i++){
    found = temp2.find_first_of(';');
    if(found < temp2.length()){
      temp2=temp2.erase(found,temp2.length());
      temp1 = result.erase(0,found+1);
    if (desktop !=NULL){
      if (temp2.compare(desktop)==0){
      return true;
      }
    }
    if (desktop_session !=NULL){
      if (temp2.compare(desktop_session)==0){
      return true;
      }
    }
      temp2=temp1;
    }
  }
  return false;
}
std::string exec_line(std::string filename) {
  std::string execline= get_line(filename,"TryExec=");
  if(execline.compare("")==0){execline= get_line(filename,"Exec=");}
  if(execline.compare("")!=0){return execline;}
  return "";
}

std::string icon_line(std::string filename) {
  std::string icon = get_line(filename,"Icon=");
  //outXML("icon:"+icon+"::");
  if ( icon.compare("")==0){return "application-default-icon";}
  return icon;
}

std::string name_line(std::string filename) {
  std::string base_lang,result,strlang,strlanguage,startbase,NAME,LOCALNAME,LOCALEND;
  NAME="Name";
  LOCALNAME="Name[";
  LOCALEND="]=";
  unsigned int underscore = 0;
  char* lang = getenv("LANG");
  char* language = getenv("LANGUAGE");
  if (lang!=NULL){
	strlang = lang;
    result=get_line(filename,(LOCALNAME+ strlanguage + LOCALEND));

    if(result.compare("")!=0){return result;}
    base_lang=strlanguage;
  }
  else{
    if (language!=NULL){
		strlanguage =language;
        unsigned int dot = 0;
        dot=strlang.find('.');
        if(dot<strlang.length()){
			startbase=strlang.erase(dot,strlang.length());
			result=get_line(filename, (LOCALNAME+ startbase + LOCALEND));

			if(result.compare("")!=0){return result;}
			base_lang=startbase;
		}
		else{return get_line(filename,"Name=");}
     }
     else{return get_line(filename,"Name=");}
  }

  underscore=base_lang.find('_');
  if(underscore<base_lang.length()){
	base_lang=base_lang.erase(underscore,base_lang.length());
	result=get_line( (LOCALNAME+ base_lang + LOCALEND) ,filename);
	if(result.compare("")!=0){return result;}
  }
  return get_line(filename,"Name=");
}

std::string cat_line(std::string filename){
	std::string AV,DEV,ED,GAME,ART,NET,OFF,SCI,SET,SYS,ACC,category,CAT;
	AV = "AudioVideo";
	DEV = "Development";
	ED = "Education";
	GAME = "Game";
	ART = "Graphics";
	NET = "Network";
	OFF = "Office";
	SCI = "Science";
	SET = "Settings";
	SYS = "System";
	ACC = "Utility";
	std::string temp1,temp2;
	unsigned int found;
	std::string catline = get_line(filename,"Categories=");
	temp2=catline;
	for(unsigned int i = 0; i<catline.length();i++){
		found = temp2.find_first_of(';');
		if(found < temp2.length()){
			temp2=temp2.erase(found,temp2.length());
			temp1 = catline.erase(0,found+1);
			category=temp2;
			temp2=temp1;
			if( category.compare(AV)==0){return AV;}
			else if( category.compare(DEV)==0){return DEV;}
			else if( category.compare(ED)==0){return ED;}
			else if( category.compare(GAME)==0){return GAME;}
			else if( category.compare(ART)==0){return ART;}
			else if( category.compare(NET)==0){return NET;}
			else if( category.compare(OFF)==0){return OFF;}
			else if( category.compare(SCI)==0){return SCI;}
			else if( category.compare(SET)==0){return SET;}
			else if( category.compare(SYS)==0){return SYS;}
			else if( category.compare(ACC)==0){return ACC;}
		}
	}
	return category;
}
std::string set_xdg_paths(){
// for more info see:
// http://freedesktop.org/wiki/Specifications/basedir-spec/

    const char* datadirs=getenv("XDG_DATA_DIRS");
    std::string thisXDG;
    if (datadirs == NULL){
        thisXDG="/usr/local/share/:/usr/share/";
    }
    else{
		thisXDG =datadirs;
	}
    const char* datahome = getenv("XDG_DATA_HOME");
    if (datahome == NULL){
        thisXDG += ":";
        datahome = getenv("HOME");
        thisXDG += datahome;
        thisXDG += "/.local/share/";

    }
    else{thisXDG = thisXDG + ":" + datahome;}
    if (thisXDG.compare("")==0){return "/usr/share/";}
    return thisXDG;
}
std::string getDefaultFilepath(std::string pathToGet){
    std::string testPATH,dirToOpen,fullpath;
    unsigned int found = 0;
    //initialize directory reading variables to NULL
    DIR *dir = NULL;
    struct dirent *entryPointer = NULL;

    // if we can't find the xdg paths... return without trying to read them
    if(num_XDG_PATHS==0){return "/usr/share/";}
    else{
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
			//make sure this isn't blank
			if(testPATH.compare("")!=0){
				//look to see if we have a / at the end... remove it if we do...
				found = testPATH.find_last_of('/');
				if (found == testPATH.length()-1){testPATH=testPATH.substr(0,testPATH.length()-1);}
				//see if there is an icon directory
				dirToOpen = testPATH + pathToGet;
				dir = opendir(dirToOpen.c_str());
				if (dir!=NULL){
					while ((entryPointer=readdir(dir)) != NULL){
						if ((entryPointer->d_type == DT_DIR)&&(entryPointer->d_name[0] != '.')){
							return dirToOpen;
						}
					}
					closedir(dir);
				}
			}
		}
    }
    return "";
}
unsigned int numXDG_PATHS(){
    //   howmany=($(echo "${XDG_DATA_DIRS//:/ }"));echo ${#howmany[@]}
    stringXDG_PATH=xdg_paths;
    XDG_pathPosition = stringXDG_PATH.find_first_of(':');
    if(XDG_pathPosition>stringXDG_PATH.length()){return 1;}
    unsigned int howmany;
    for(howmany=1;(XDG_pathPosition!=std::string::npos);howmany++){
        XDG_pathPosition=stringXDG_PATH.find(':', XDG_pathPosition+1);
    }
    return howmany;
}
const char* thisXDG_PATH(int whichPath){
// use this to get the string of the path to test.
// basically in bash speak...
// whichpath=1;howmany=($(echo "${XDG_DATA_DIRS//:/ }"));echo ${howmany[$whichpath]}
    stringXDG_PATH=xdg_paths;

//I used and modified the Config paths code to do this... TODO: refactor to use 1 function
    unsigned int lastPath = 0;
    std::string result="";
    if (whichPath >=1){lastPath = whichPath - 1;}
    else {lastPath = 0;}

    std::string::size_type firstPosition = stringXDG_PATH.find_first_of(':');
    std::string::size_type position = stringXDG_PATH.find(':');
    for (int i=1;i<=whichPath;i++){position = stringXDG_PATH.find(':',position+1);}
    for (unsigned int j=1;j<=lastPath;j++){firstPosition = stringXDG_PATH.find(':',firstPosition+1);}
    result = stringXDG_PATH.substr (firstPosition+1,((position-firstPosition)-1));
    return result.c_str();
}
std::vector<std::string> desktop_paths(){
	std::vector<std::string> thisPath;
	std::vector<std::string>::iterator it;
	const char* datadirs=getenv("XDG_DATA_DIRS");
    std::string thisXDG;
    if (datadirs == NULL){
        thisXDG="/usr/local/share/:/usr/share/";
    }
    else{
		thisXDG=datadirs;
	}
    const char* datahome = getenv("XDG_DATA_HOME");
    if (datahome == NULL){
        thisXDG += ":";
        datahome = getenv("HOME");
        thisXDG += datahome;
        thisXDG += "/.local/share/";

    }
    else{thisXDG = thisXDG + ":" + datahome;}
    unsigned int lastPath = 0;
    std::string result;
    for (int whichPath=1;whichPath<=num_XDG_PATHS;whichPath++){
		if (whichPath >=1){lastPath = whichPath - 1;}
		else {lastPath = 0;}
		std::string::size_type firstPosition = thisXDG.find_first_of(':');
		std::string::size_type position = thisXDG.find(':');
		for (int i=1;i<=whichPath;i++){position = thisXDG.find(':',position+1);}
		for (unsigned int j=1;j<=lastPath;j++){firstPosition = thisXDG.find(':',firstPosition+1);}
		result = thisXDG.substr (firstPosition+1,((position-firstPosition)-1));
		thisPath.push_back(result);    
	}
	std::sort (thisPath.begin(), thisPath.end());
	it = std::unique (thisPath.begin(), thisPath.end());
	thisPath.resize( std::distance(thisPath.begin(),it) );
	return thisPath;
}
std::string showCategories(){
	std::string MenuEntry,NAME,ICON,EXEC,CATS,TERMIE,AV,DEV,ED,GAME,ART,NET,OFF,SCI,SET,SYS,ACC,category,testPATH;
	std::string AV1,DEV1,ED1,GAME1,ART1,NET1,OFF1,SCI1,SET1,SYS1,ACC1;
	AV1="0";
	DEV1="0";
	ED1="0";
	GAME1="0";
	ART1="0";
	NET1="0";
	OFF1="0";
	SCI1="0";
	SET1="0";
	SYS1="0";
	ACC1="0";
	//TODO: XDG paths
	std::string dirToOpen = "/usr/share/applications/";
	std::string pathToGet = "/applications/";
	std::string fullpath, result, name, icon, exec, tester, cattie;
	std::string myterm=term_out("which x-terminal-emulator || which xterm");
	///Localization Directory files
	std::string DIR_EXT = ".directory";
	std::string INTRO = "jwm";
	std::string iconEQ = "Icon=";
	std::string MENU;
	std::string fallbackIcon = "applications-";
	std::string DD = "/usr/share/desktop-directories"; //getDefaultFilepath("/desktop-directories");
	//outXML(DD);
    if (DD.compare("")==0){return "\t<Program label=\"Could not find Desktop Directories\" icon=\"error\">xterm -e 'locate desktop-directories'</Program>\n";}
	//Accessories
	std::string A_NAME,A_ICON;
	std::string accessories_FILE = DD + "/" + INTRO + "-accessories" + DIR_EXT;
	if(test_file(accessories_FILE.c_str()) ){
		A_NAME = get_name(accessories_FILE);
		A_ICON = get_line(accessories_FILE,iconEQ);
	}
	if(A_NAME.compare("")==0){
		A_NAME = "Accessories";
	}
	if(A_ICON.compare("")==0){
		A_ICON = fallbackIcon + "accessories";
	}
	
	//Games
	std::string games_FILE = DD + "/" + INTRO + "-games" + DIR_EXT;
	std::string GAME_NAME,GAME_ICON;
	if(test_file(games_FILE.c_str()) ){
		GAME_NAME = get_name(games_FILE);
		GAME_ICON = get_line(games_FILE,iconEQ);
	}
	if(GAME_ICON.compare("")==0){
		GAME_NAME = "Games";
	}
	if(GAME_ICON.compare("")==0){
		GAME_ICON = fallbackIcon + "games";
	}
	//Graphics
	std::string graphics_FILE = DD + "/" + INTRO + "-graphics" + DIR_EXT;
	std::string G_NAME,G_ICON;
	if(test_file(graphics_FILE.c_str()) ){
		G_NAME = get_name(graphics_FILE);
		G_ICON = get_line(graphics_FILE,iconEQ);
	}
	if(G_NAME.compare("")==0){
		G_NAME = "Graphics";
	}
	if(G_ICON.compare("")==0){
		G_ICON = fallbackIcon + "graphics";
	}
	//AudioVideo
	std::string multimedia_FILE = DD + "/" + INTRO + "-multimedia" + DIR_EXT;
	std::string M_NAME, M_ICON;
	if(test_file(multimedia_FILE.c_str()) ){
		M_NAME = get_name(multimedia_FILE);
		M_ICON = get_line(multimedia_FILE,iconEQ);
	}
	if(M_NAME.compare("")==0){
		M_NAME = "Multimedia";
	}
	if(M_ICON.compare("")==0){
		M_ICON = fallbackIcon + "multimedia";
	}
	//Network
	std::string network_FILE = DD + "/" + INTRO + "-network" + DIR_EXT;
	std::string I_NAME,I_ICON;
	if(test_file(network_FILE.c_str()) ){
		I_NAME = get_name(network_FILE);
		I_ICON = get_line(network_FILE,iconEQ);
	}
	if(I_NAME.compare("")==0){
		I_NAME = "Internet";
	}
	if(I_ICON.compare("")==0){
		I_ICON = fallbackIcon + "internet";
	}
	//Office
	std::string office_FILE = DD + "/" + INTRO + "-office" + DIR_EXT;
	std::string O_NAME,O_ICON;
	if( test_file(office_FILE.c_str()) ){
		O_NAME = get_name(office_FILE);
		O_ICON = get_line(office_FILE,iconEQ);
	}
	if(O_NAME.compare("")==0){
		O_NAME = "Office";
	}
	if(O_ICON.compare("")==0){
		O_ICON = fallbackIcon + "office";
	}
	//Other?
	std::string other_FILE = DD + "/" + INTRO + "-other" + DIR_EXT;
	std::string OTHER_NAME,OTHER_ICON;
	if(test_file(other_FILE.c_str()) ){
		OTHER_NAME = get_name(other_FILE);
		OTHER_ICON = get_line(other_FILE,iconEQ);
	}
	if(OTHER_NAME.compare("")==0){
		OTHER_NAME = "Other";
	}
	if(OTHER_ICON.compare("")==0){
		OTHER_ICON = fallbackIcon + "other";
	}
	//System
	std::string system_FILE = DD + "/" + INTRO + "-system" + DIR_EXT;
	std::string SYS_NAME,SYS_ICON;
	if(test_file(system_FILE.c_str()) ){
		SYS_NAME = get_name(system_FILE);
		SYS_ICON = get_line(system_FILE,iconEQ);
	}
	if(SYS_NAME.compare("")==0){
		SYS_NAME = "System";
	}
	if(SYS_ICON.compare("")==0){
		SYS_ICON = fallbackIcon + "system";
	}
	//Settings
	std::string settings_FILE = DD + "/" + INTRO + "-settings" + DIR_EXT;
	std::string SETT_NAME,SETT_ICON;
	if(test_file(settings_FILE.c_str()) ){
		SETT_NAME = get_name(settings_FILE);
		SETT_ICON = get_line(settings_FILE,iconEQ);
	}
	if(SETT_NAME.compare("")==0){
		SETT_NAME = "Settings";
	}
	if(SETT_ICON.compare("")==0){
		SETT_ICON = "preferences-desktop";
	}
	//Development
	std::string development_FILE = DD + "/" + INTRO + "-development" + DIR_EXT;
	std::string D_NAME,D_ICON;
	if(test_file(development_FILE.c_str()) ){
		D_NAME = get_name(development_FILE);
		D_ICON = get_line(development_FILE,iconEQ);
	}
	if(D_NAME.compare("")==0){
		D_NAME = "Development";
	}
	if(D_ICON.compare("")==0){
		D_ICON = fallbackIcon + "development";
	}
	//Education
	std::string education_FILE = DD + "/" + INTRO + "-education" + DIR_EXT;
	std::string E_NAME,E_ICON;
	if(test_file(education_FILE.c_str()) ){
		E_NAME = get_name(education_FILE);
		E_ICON = get_line(education_FILE,iconEQ);	
	}
	if(E_NAME.compare("")==0){
		E_NAME = "Education";
	}
	if(E_ICON.compare("")==0){
		E_ICON = fallbackIcon + "science";
	}
	std::vector<std::string> uniqueDirs = desktop_paths();
	unsigned int found = 0;
    //initialize directory reading variables to NULL
    DIR *dir = NULL;
    struct dirent *entryPointer = NULL;

		//lets loop through the xdg paths
		//for (int i = 1; i <= num_XDG_PATHS; i++){
		for( std::vector<std::string>::iterator it = uniqueDirs.begin();
			it!=uniqueDirs.end();
			++it){
        //get the string equvalent for the integer representation if of the xdg path
        // something like
        /*
        1=/usr/share/
        2=/usr/local/share
        etc...
        */
			testPATH = *it;
			//outXML(testPATH);
			//make sure this isn't blank
			if(testPATH.compare("")!=0){
				//look to see if we have a / at the end... remove it if we do...
				found = testPATH.find_last_of('/');
				if (found == testPATH.length()-1){testPATH=testPATH.substr(0,testPATH.length()-1);}
				//see if there is a pathToGet directory
				dirToOpen = testPATH + pathToGet;
				//outXML(dirToOpen);
				dir = opendir(dirToOpen.c_str());
				if (dir!=NULL){
					while ((entryPointer=readdir(dir)) != NULL){
						if (entryPointer->d_type == DT_DIR){ //&&(entryPointer->d_name[0] != '.')
							//outXML(dirToOpen);
			if(ACC.compare(ACC1)!=0){ACC+=loop_desktopfiles("Utility",dirToOpen);}
			if(ACC.compare("")!=0){ACC1 = ACC;}
			if(ART.compare(ART1)!=0){ART+=loop_desktopfiles("Graphics",dirToOpen);}
			if(ART.compare("")!=0){ART1 = ART;}
			if(AV.compare(AV1)!=0){AV+=loop_desktopfiles("AudioVideo",dirToOpen);}
			if(AV.compare("")!=0){AV1 = AV;}
			if(DEV.compare(DEV1)!=0){DEV+=loop_desktopfiles("Development",dirToOpen);}
			if(DEV.compare("")!=0){DEV1 = DEV;}
			if(ED.compare(ED1)!=0){ED+=loop_desktopfiles("Education",dirToOpen);}
			if(ED.compare("")!=0){ED1 = ED;}
			if(GAME.compare(GAME1)!=0){GAME+=loop_desktopfiles("Game",dirToOpen);}
			if(GAME.compare("")!=0){GAME1 = GAME;}
			if(NET.compare(NET1)!=0){NET+=loop_desktopfiles("Network",dirToOpen);}
			if(NET.compare("")!=0){NET1 = NET;}
			if(OFF.compare(OFF1)!=0){OFF+=loop_desktopfiles("Office",dirToOpen);}
			if(OFF.compare("")!=0){OFF1 = OFF;}
			if(SET.compare(SET1)!=0){SET+=loop_desktopfiles("Settings",dirToOpen);}
			if(SET.compare("")!=0){SET1 = SET;}
			if(SYS.compare(SYS1)!=0){SYS+=loop_desktopfiles("System",dirToOpen);}
			if(SYS.compare("")!=0){SYS1 = SYS;}
	
	}
	//outXML(AV1 + ":" + DEV1 + ":" + ED1 + ":" + GAME1 + ":" + ART1 + ":" + NET1 + ":" + OFF1 + ":" + SCI1 + ":" + SET1 + ":" + SYS1 + ":" + ACC1 + ":" + AV + ":" + DEV + ":" + ED + ":" + GAME + ":" + ART + ":" + NET + ":" + OFF + ":" + SCI + ":" + SET + ":" + SYS + ":" + ACC);
						}
					}
				}
				closedir(dir);
			}
std::string A,R,V,D,E,G,N,O,S,Y,baseProgram;
baseProgram="exec:menu2 -";
A=baseProgram + "a";
R=baseProgram + "r";
V=baseProgram + "v";
D=baseProgram + "d";
E=baseProgram + "e";
G=baseProgram + "g";
N=baseProgram + "n";
O=baseProgram + "o";
S=baseProgram + "s";
Y=baseProgram + "y";

if(ACC.compare("")!=0){MENU+="\t<Dynamic label=\""+A_NAME+"\" icon=\""+A_ICON +"\" height=\"0\">\n"+A+"\n\t</Dynamic>\n";}
if(ART.compare("")!=0){MENU+="\t<Dynamic label=\""+G_NAME+"\" icon=\""+G_ICON +" \" height=\"0\">\n"+R+"\n\t</Dynamic>";}
if(AV.compare("")!=0){MENU+="\t<Dynamic label=\""+M_NAME+"\" icon=\""+M_ICON + " \" height=\"0\">\n"+V+"\n\t</Dynamic>\n";}
if(DEV.compare("")!=0){MENU+="\t<Dynamic label=\""+D_NAME+"\" icon=\""+D_ICON + " \" height=\"0\">\n"+D+"\n\t</Dynamic>\n";}
if(ED.compare("")!=0){MENU+="\t<Dynamic label=\""+E_NAME+"\" icon=\""+E_ICON +" \" height=\"0\">\n"+E+"\n\t</Dynamic>\n";}
if(GAME.compare("")!=0){MENU+="\t<Dynamic label=\""+GAME_NAME+"\" icon=\""+GAME_ICON +"\" height=\"0\">\n"+G+"\n\t</Dynamic>\n";}
if(NET.compare("")!=0){MENU+="\t<Dynamic label=\""+I_NAME+"\" icon=\""+I_ICON +" \" height=\"0\">\n"+N+"\n\t</Dynamic>\n";}
if(OFF.compare("")!=0){MENU+="\t<Dynamic label=\""+O_NAME+"\" icon=\""+O_ICON +"\" height=\"0\">\n"+O+"\n\t</Dynamic>\n";}
if(SET.compare("")!=0){MENU+="\t<Dynamic label=\""+SETT_NAME+"\" icon=\""+SETT_ICON + " \" height=\"0\">\n"+S+"\n\t</Dynamic>\n";}
if(SYS.compare("")!=0){MENU+="\t<Dynamic label=\""+SYS_NAME+"\" icon=\""+SYS_ICON + " \" height=\"0\">\n"+S+"\n\t</Dynamic>";}
  return MENU;

}
