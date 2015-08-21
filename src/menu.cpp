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
std::string make_menu();
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
int main() {
    std::cout<<"<?xml version=\"1.0\"?>\n<JWM>"<<std::endl;
    xdg_paths = set_xdg_paths();
    stringXDG_PATH = xdg_paths;
    XDG_pathPosition = stringXDG_PATH.find_first_of(':');
    num_XDG_PATHS = numXDG_PATHS();
    std::string result = make_menu();
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
  equals = LINE.find("=");
  if (args < LINE.length())LINE = LINE.erase(args,std::string::npos);
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
     mylang = mylang.erase(found,std::string::npos);
     tempstr=name;
     tempstr+="[";
     tempstr+=mylang;
     tempstr+="]=";
     tryGet=get_line(filename,tempstr);
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
     mylang = mylang.erase(dash,std::string::npos);
     tempstr=name;
     tempstr+="[";
     tempstr+=mylang;
     tempstr+="]=";
     tryGet=get_line(filename,tempstr);
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
std::string make_menu(){
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
	std::string fullpath, result, name, icon, exec, tester, cat;
	std::string myterm=term_out("which x-terminal-emulator || which xterm");
	///Localization Directory files
	std::string DIR_EXT = ".directory";
	std::string INTRO = "jwm";
	std::string iconEQ = "Icon=";
	std::string MENU;
	std::string DD = "/usr/share/desktop-directories"; //getDefaultFilepath("/desktop-directories");
	//outXML(DD);
    if (DD.compare("")==0){return "\t<Program label=\"Could not find Desktop Directories\" icon=\"error\">xterm -e 'locate desktop-directories'</Program>\n";}
	//Accessories
	std::string accessories_FILE = DD + "/" + INTRO + "-accessories" + DIR_EXT;
	std::string A_NAME = get_name(accessories_FILE);
	std::string A_ICON = get_line(accessories_FILE,iconEQ);
	//Games
	std::string games_FILE = DD + "/" + INTRO + "-games" + DIR_EXT;
	std::string GAME_NAME = get_name(games_FILE);
	std::string GAME_ICON = get_line(games_FILE,iconEQ);
	//Graphics
	std::string graphics_FILE = DD + "/" + INTRO + "-graphics" + DIR_EXT;
	std::string G_NAME = get_name(graphics_FILE);
	std::string G_ICON = get_line(graphics_FILE,iconEQ);
	//AudioVideo
	std::string multimedia_FILE = DD + "/" + INTRO + "-multimedia" + DIR_EXT;
	std::string M_NAME = get_name(multimedia_FILE);
	std::string M_ICON = get_line(multimedia_FILE,iconEQ);
	//Network
	std::string network_FILE = DD + "/" + INTRO + "-network" + DIR_EXT;
	std::string I_NAME = get_name(network_FILE);
	std::string I_ICON = get_line(network_FILE,iconEQ);
	//Office
	std::string office_FILE = DD + "/" + INTRO + "-office" + DIR_EXT;
	std::string O_NAME = get_name(office_FILE);
	std::string O_ICON = get_line(office_FILE,iconEQ);
	//Other?
	std::string other_FILE = DD + "/" + INTRO + "-other" + DIR_EXT;
	std::string OTHER_NAME = get_name(other_FILE);
	std::string OTHER_ICON = get_line(other_FILE,iconEQ);
	//System
	std::string system_FILE = DD + "/" + INTRO + "-system" + DIR_EXT;
	std::string SYS_NAME = get_name(system_FILE);
	std::string SYS_ICON = get_line(system_FILE,iconEQ);
	//Settings
	std::string settings_FILE = DD + "/" + INTRO + "-settings" + DIR_EXT;
	std::string SETT_NAME = get_name(settings_FILE);
	std::string SETT_ICON = get_line(settings_FILE,iconEQ);
	//Development
	std::string development_FILE = DD + "/" + INTRO + "-development" + DIR_EXT;
	std::string D_NAME = get_name(development_FILE);
	std::string D_ICON = get_line(development_FILE,iconEQ);
	//Education
	std::string education_FILE = DD + "/" + INTRO + "-education" + DIR_EXT;
	std::string E_NAME = get_name(education_FILE);
	std::string E_ICON = get_line(education_FILE,iconEQ);
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
						if ((entryPointer->d_type == DT_DIR)){ //&&(entryPointer->d_name[0] != '.')
							//outXML(dirToOpen);
	if(AV.compare(AV1)!=0){AV+=loop_desktopfiles("AudioVideo",dirToOpen);}
	if(DEV.compare(DEV1)!=0){DEV+=loop_desktopfiles("Development",dirToOpen);}
	if(ED.compare(ED1)!=0){ED+=loop_desktopfiles("Education",dirToOpen);}
	if(GAME.compare(GAME1)!=0){GAME+=loop_desktopfiles("Game",dirToOpen);}
	if(ART.compare(ART1)!=0){ART+=loop_desktopfiles("Graphics",dirToOpen);}
	if(NET.compare(NET1)!=0){NET+=loop_desktopfiles("Network",dirToOpen);}
	if(OFF.compare(OFF1)!=0){OFF+=loop_desktopfiles("Office",dirToOpen);}
	if(SCI.compare(SCI1)!=0){SCI+=loop_desktopfiles("Science",dirToOpen);}
	if(SET.compare(SET1)!=0){SET+=loop_desktopfiles("Settings",dirToOpen);}
	if(SYS.compare(SYS1)!=0){SYS+=loop_desktopfiles("System",dirToOpen);}
	if(ACC.compare(ACC1)!=0){ACC+=loop_desktopfiles("Utility",dirToOpen);}
	if(AV.compare("")!=0){AV1 = AV;}
	if(DEV.compare("")!=0){DEV1 = DEV;}
	if(ED.compare("")!=0){ED1 = ED;}
	if(GAME.compare("")!=0){GAME1 = GAME;}
	if(ART.compare("")!=0){ART1 = ART;}
	if(NET.compare("")!=0){NET1 = NET;}
	if(OFF.compare("")!=0){OFF1 = OFF;}
	if(SCI.compare("")!=0){SCI1 = SCI;}
	if(SET.compare("")!=0){SET1 = SET;}
	if(SYS.compare("")!=0){SYS1 = SYS;}
	if(ACC.compare("")!=0){ACC1 = ACC;}
	//outXML(AV1 + ":" + DEV1 + ":" + ED1 + ":" + GAME1 + ":" + ART1 + ":" + NET1 + ":" + OFF1 + ":" + SCI1 + ":" + SET1 + ":" + SYS1 + ":" + ACC1 + ":" + AV + ":" + DEV + ":" + ED + ":" + GAME + ":" + ART + ":" + NET + ":" + OFF + ":" + SCI + ":" + SET + ":" + SYS + ":" + ACC);
						}
					}
				}
				closedir(dir);
			}
		}
if(ACC.compare("")!=0){MENU+="\t<Menu label=\""+A_NAME+"\" icon=\""+A_ICON +"\" height=\"0\">\n"+ACC+"\n\t</Menu>\n";}
if(ED.compare("")!=0){MENU+="\t<Menu label=\""+E_NAME+"\" icon=\""+E_ICON +" \" height=\"0\">\n"+ED+"\n\t</Menu>\n";}
if(NET.compare("")!=0){MENU+="\t<Menu label=\""+I_NAME+"\" icon=\""+I_ICON +" \" height=\"0\">\n"+NET+"\n\t</Menu>\n";}
if(OFF.compare("")!=0){MENU+="\t<Menu label=\""+O_NAME+"\" icon=\""+O_ICON +"\" height=\"0\">\n"+OFF+"\n\t</Menu>\n";}
if(GAME.compare("")!=0){MENU+="\t<Menu label=\""+GAME_NAME+"\" icon=\""+GAME_ICON +"\" height=\"0\">\n"+GAME+"\n\t</Menu>\n";}
if(ART.compare("")!=0){MENU+="\t<Menu label=\""+G_NAME+"\" icon=\""+G_ICON +" \" height=\"0\">\n"+ART+"\n\t</Menu>";}
if(AV.compare("")!=0){MENU+="\t<Menu label=\""+M_NAME+"\" icon=\""+M_ICON + " \" height=\"0\">\n"+AV+"\n\t</Menu>\n";}
if(DEV.compare("")!=0){MENU+="\t<Menu label=\""+D_NAME+"\" icon=\""+D_ICON + " \" height=\"0\">\n"+DEV+"\n\t</Menu>\n";}
if(SCI.compare("")!=0){MENU+="\t<Menu label=\""+OTHER_NAME+"\" icon=\""+OTHER_ICON + " \" height=\"0\">\n"+SCI+"\n\t</Menu>\n";}
if(SET.compare("")!=0){MENU+="\t<Menu label=\""+SETT_NAME+"\" icon=\""+SETT_ICON + " \" height=\"0\">\n"+SET+"\n\t</Menu>\n";}
if(SYS.compare("")!=0){MENU+="\t<Menu label=\""+SYS_NAME+"\" icon=\""+SYS_ICON + " \" height=\"0\">\n"+SYS+"\n\t</Menu>";}
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
  return result.erase(end-1,end);
}
bool test_file(const char* fileWithFullPATH) {
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
  strlang = lang;
  strlanguage =language;
  if (strlanguage.compare("")!=0){
    result=get_line(filename,(LOCALNAME+ strlanguage + LOCALEND));

    if(result.compare("")!=0){return result;}
    base_lang=strlanguage;
  }
  else{
    if (strlang.compare("")!=0){
        unsigned int dot = 0;
        dot=strlang.find('.');
        startbase=strlang.erase(dot,strlang.length());
        result=get_line(filename, (LOCALNAME+ startbase + LOCALEND));

        if(result.compare("")!=0){return result;}
        base_lang=startbase;
     }
     else{return get_line(filename,"Name=");}
  }

  underscore=base_lang.find('_');
  base_lang=base_lang.erase(underscore,base_lang.length());

  result=get_line( (LOCALNAME+ base_lang + LOCALEND) ,filename);

  if(result.compare("")!=0){return result;}

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
    std::string thisXDG =datadirs;
    if ((datadirs == NULL) || (thisXDG.compare("")==0)){
        thisXDG="/usr/local/share/:/usr/share/";
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
				}
				closedir(dir);
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
    std::string result;
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
    std::string thisXDG =datadirs;
    if ((datadirs == NULL) || (thisXDG.compare("")==0)){
        thisXDG="/usr/local/share/:/usr/share/";
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
