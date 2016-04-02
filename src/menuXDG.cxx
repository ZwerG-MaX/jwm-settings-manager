
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
 * g++ -finline-small-functions -ffunction-sections -fdata-sections -fmerge-all-constants -fomit-frame-pointer -mno-accumulate-outgoing-args -fno-unwind-tables -fno-asynchronous-unwind-tables -Os menuXDG.cxx -o menuXDG
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

//functions
//string vectors
std::vector<std::string> xdgmenufiles();
std::vector<std::string> desktop_dirs();
std::vector<std::string> desktop_paths();
std::vector<std::string> split_paths(const char* envVar, const char* incasenothingexists);
std::vector<std::string> sortArray(std::vector<std::string> thisPath);
//strings
std::string getDDItem(std::string directory, std::string lineToGet);
std::string getDDName(std::string directory);
std::string chopTAG(std::string line);
std::string loop_desktopfiles(std::string categoryToGet,std::string dirToOpen);
std::string grep(std::string args, std::string filename);
std::string get_line(std::string filename, std::string line);
std::string get_name(std::string filename);
std::string make_menu();
std::string make_menu_xdg();
std::string term_out(std::string terminal_Command_You_Want_Output_From);
std::string exec_line(std::string filename);
std::string icon_line(std::string filename);
std::string name_line(std::string filename);
std::string cat_line(std::string filename);
std::string makeXDGmenu(std::vector<std::string> cats,std::vector<std::string> dirs);

//boolean
bool test_file(const char* fileWithFullPATH);
bool no_display(std::string filename);
bool only_show(std::string filename);
bool not_showin(std::string filename);
bool terminal(std::string filename);

//void
void outXML(std::string message);

int main() {
    std::cout<<"<?xml version=\"1.0\"?>\n<JWM>"<<std::endl;
    std::string result = make_menu_xdg();
    std::cout<<result<<"\n</JWM>"<<std::endl;
	return 0;
}
void outXML(std::string message){
	std::cout<<"<!--"<<message<<"-->"<<std::endl;
	}
	
////////////////////////////////////////////////////////////////////////////////////////////////////string
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
  args = LINE.find(" %");
  // remove only 2 characters  maybe later check to see if there is a space after it to determine if it is a shell script 
  if (args < LINE.length())LINE = LINE.erase(args,3);
  equals = LINE.find_first_of("=");
  if (equals < LINE.length())LINE= LINE.erase(0,equals+1);
  return LINE;
}

std::string get_name(std::string filename){
	std::string tryGet,tempstr;
	std::string name="Name";
	std::string mylang;
	const char* thisLang= getenv("LANGUAGE");
	if(thisLang==NULL){
		const char* myLANG = getenv("LANG");
		if(myLANG !=NULL){
			mylang=myLANG;
			unsigned int found = mylang.find('.');
			if(found < mylang.length()){
				mylang = mylang.erase(found,std::string::npos);
			}
			tempstr=name;
			tempstr+="[";
			tempstr+=mylang;
			tempstr+="]=";
			tryGet=get_line(filename,tempstr);
		}
	}
	else{
		mylang=thisLang;
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
	std::string category,MenuEntry,EXEC,ICON,NAME,termie,tester,result,fullpath,returnCAT;
	
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
	std::string dirToOpen = "/usr/share/applications/";
	std::string pathToGet = "/applications/";
	std::string fullpath, result, name, icon, exec, tester, cat;
	///Localization Directory files
	//TODO use other menus if available
	std::string DIR_EXT = ".directory";
	std::string INTRO = "jwm";
	std::string iconEQ = "Icon=";
	std::string MENU;
	std::string fallbackIcon = "applications-";
	//TODO xdg dirs
	std::string DD = "/usr/share/desktop-directories";
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
		//make sure this isn't blank
		if(testPATH.compare("")!=0){
			//look to see if we have a / at the end... remove it if we do...
			found = testPATH.find_last_of('/');
			if (found == testPATH.length()-1){testPATH=testPATH.substr(0,testPATH.length()-1);}
			//see if there is a pathToGet directory
			dirToOpen = testPATH + pathToGet;
			dir = opendir(dirToOpen.c_str());
			if (dir!=NULL){
				//outXML(dirToOpen);
				AV+=loop_desktopfiles("AudioVideo",dirToOpen);
				DEV+=loop_desktopfiles("Development",dirToOpen);
				ED+=loop_desktopfiles("Education",dirToOpen);
				GAME+=loop_desktopfiles("Game",dirToOpen);
				ART+=loop_desktopfiles("Graphics",dirToOpen);
				NET+=loop_desktopfiles("Network",dirToOpen);
				OFF+=loop_desktopfiles("Office",dirToOpen);
				SCI+=loop_desktopfiles("Science",dirToOpen);
				SET+=loop_desktopfiles("Settings",dirToOpen);
				SYS+=loop_desktopfiles("System",dirToOpen);
				ACC+=loop_desktopfiles("Utility",dirToOpen);		
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
  if((end-1) == 0){return "";}
  return result.erase(end-1,end);
}
std::string exec_line(std::string filename) {
	std::string execline= get_line(filename,"TryExec=");
	if(execline.compare("")==0){execline= get_line(filename,"Exec=");}
	if(terminal(filename)){
		std::string myterm=term_out("which x-terminal-emulator || which xterm");
		execline=myterm + " -e " + execline;
	}
	return execline;
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
	found = temp2.find_first_of(';');
	if(found>temp2.length()){return catline;}
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
std::string chopTAG(std::string line){
	unsigned int tLen=line.find_first_of('>');
	std::string temp = line;
	temp=temp.erase(0,tLen+1);
	tLen=temp.find_first_of('<');
	temp=temp.erase(tLen,std::string::npos);	
	return temp;
}
std::string getDDName(std::string directory){
	std::vector<std::string> uniqueDirs = desktop_paths();
	std::string testPATH,line;
	unsigned int found = 0;
	DIR *dirent = NULL;
	for( std::vector<std::string>::iterator it = uniqueDirs.begin();
		it!=uniqueDirs.end();
		++it){
			
		testPATH = *it;
		//make sure this isn't blank
		if(testPATH.compare("")!=0){
			//look to see if we have a / at the end... remove it if we do...
			found = testPATH.find_last_of('/');
			if (found == testPATH.length()-1){testPATH=testPATH.substr(0,testPATH.length()-1);}
			std::string tempdirName=testPATH;
			tempdirName+="/desktop-directories/";
			dirent = opendir(tempdirName.c_str());
			if (dirent!=NULL){
				tempdirName+=directory;
			}	if(get_name(tempdirName).compare("")!=0){line=get_name(tempdirName);}
			
		}
	}
	std::string amp="&amp;";
	std::string ampPRE,ampPOST,tempAMP;
	unsigned int xmlfix = line.find('&');
	if(xmlfix<line.length()){
		tempAMP=line;
		ampPOST=line;
		ampPRE = tempAMP.erase(xmlfix,std::string::npos);
		ampPOST = line.erase(0,xmlfix+1);
		line = ampPRE + amp + ampPOST;
	}
	return line;
}
std::string getDDItem(std::string directory, std::string lineToGet){
	std::vector<std::string> uniqueDirs = desktop_paths();
	std::string testPATH,line;
	unsigned int found = 0;
	DIR *dirent = NULL;
	for( std::vector<std::string>::iterator it = uniqueDirs.begin();
		it!=uniqueDirs.end();
		++it){
			
		testPATH = *it;
		//make sure this isn't blank
		if(testPATH.compare("")!=0){
			//look to see if we have a / at the end... remove it if we do...
			found = testPATH.find_last_of('/');
			if (found == testPATH.length()-1){testPATH=testPATH.substr(0,testPATH.length()-1);}
			std::string tempdirName=testPATH;
			tempdirName+="/desktop-directories/";
			dirent = opendir(tempdirName.c_str());
			if (dirent!=NULL){
				tempdirName+=directory;
				if(get_line(tempdirName,lineToGet).compare("")!=0){line=get_line(tempdirName,lineToGet);}
			}
		}
	}
	std::string amp="&amp;";
	std::string ampPRE,ampPOST,tempAMP;
	unsigned int xmlfix = line.find('&');
	if(xmlfix<line.length()){
		tempAMP=line;
		ampPOST=line;
		ampPRE = tempAMP.erase(xmlfix,std::string::npos);
		ampPOST = line.erase(0,xmlfix+1);
		line = ampPRE + amp + ampPOST;
	}
	return line;
}
std::string makeXDGmenu(std::vector<std::string> cats,std::vector<std::string> dirs){
	std::string MENU,menuTest,this_ICON,this_NAME,this_Exec,DESKTOPS, desktopTest,testDirFile,testPATH;
	std::string dirToOpen = "/usr/share/applications/";
	std::string pathToGet = "/applications/";
	std::string iconEQ = "Icon=";
    for( std::vector<std::string>::iterator itr = dirs.begin();
		itr!=dirs.end();
		++itr){
		testDirFile = *itr;
		if(getDDName(testDirFile).compare("")!=0){this_NAME = getDDName(testDirFile);}
		if(getDDItem(testDirFile,iconEQ).compare("")!=0){this_ICON = getDDItem(testDirFile,iconEQ);}
		for( std::vector<std::string>::iterator it = cats.begin();
		it!=cats.end();
		++it){
			std::vector<std::string> uniqueDirs = desktop_paths();
			unsigned int found = 0;
			unsigned int foundDesk = 0;
			unsigned int foundMENU = 0;
			//initialize directory reading variables to NULL
			std::string CATS=*it;
			DIR *dirent = NULL;
			for( std::vector<std::string>::iterator iter = uniqueDirs.begin();
				iter!=uniqueDirs.end();
				++iter){
				testPATH = *iter;
				//make sure this isn't blank
				if(testPATH.compare("")!=0){
					//look to see if we have a / at the end... remove it if we do...
					found = testPATH.find_last_of('/');
					if (found == testPATH.length()-1){testPATH=testPATH.substr(0,testPATH.length()-1);}
					//see if there is a pathToGet directory
					dirToOpen = testPATH + pathToGet;
					dirent = opendir(dirToOpen.c_str());
						if (dirent!=NULL){
							
							if( (this_ICON.compare("")!=0)&&(this_NAME.compare("")!=0) ){
								//outXML(dirToOpen);
								desktopTest=loop_desktopfiles(CATS,dirToOpen);
								foundMENU=MENU.find(desktopTest);
								if( foundMENU>MENU.length() ){
									foundDesk=DESKTOPS.find(desktopTest);
									if( foundDesk>DESKTOPS.length() ){DESKTOPS+=desktopTest;}
								}
							}
						}
				}
			}//desktop file path vector
			unsigned int menuFind=0;
			menuFind=MENU.find(this_NAME);
			if(menuFind>MENU.length()){
				if(DESKTOPS.compare("")!=0){MENU+="\t<Menu label=\""+this_NAME+"\" icon=\""+this_ICON +"\" height=\"0\">\n"+DESKTOPS+"\n\t</Menu>\n";}
			}
		}//categories vector
	}//dirs vector
	return MENU;
}
////////////////////////////////////////////////////////////////////////////////////////////////////BOOL
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
bool terminal(std::string filename) {
  std::string result = get_line(filename,"Terminal=");
  if(result.compare("")==0){
  //Only show in line doesn't exist
    return false;
  }
  //compare lower case words only
  std::transform(result.begin(),result.end(),result.begin(),::tolower);
  if(result.find("true")<result.length()){return true;}
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

////////////////////////////////////////////////////////////////////////////////////////////////////String Vectors


std::vector<std::string> desktop_paths(){
	std::vector<std::string> thisPath;
	std::vector<std::string>::iterator it;
	std::string thisXDG;
	const char* datadirs=getenv("XDG_DATA_DIRS");
    if (datadirs == NULL){
        thisXDG="/usr/local/share/:/usr/share/";
    }
    else{
		thisXDG=datadirs;
	}
    const char* datahome = getenv("XDG_DATA_HOME");
    if (datahome == NULL){
        datahome = getenv("HOME");
        if (datahome != NULL){
			thisXDG += ":";
			thisXDG += datahome;
			thisXDG += "/.local/share/";
		}
    }
    else{thisXDG = thisXDG + ":" + datahome;}
    unsigned int numberOfPaths;
    std::string tempXDG = thisXDG;
    unsigned int tryer;
    for (numberOfPaths=0;numberOfPaths<thisXDG.length();){
		tryer = tempXDG.find(":");
		tempXDG=tempXDG.erase(0,tryer+1);
		numberOfPaths++;
		
	}
    unsigned int lastPath = 0;
    std::string result;
    for (unsigned int whichPath=1;whichPath<=numberOfPaths;whichPath++){
		if (whichPath >=1){lastPath = whichPath - 1;}
		else {lastPath = 0;}
		std::string::size_type firstPosition = thisXDG.find_first_of(':');
		std::string::size_type position = thisXDG.find(':');
		for (unsigned int i=1;i<=whichPath;i++){position = thisXDG.find(':',position+1);}
		for (unsigned int j=1;j<=lastPath;j++){firstPosition = thisXDG.find(':',firstPosition+1);}
		result = thisXDG.substr (firstPosition+1,((position-firstPosition)-1));
		thisPath.push_back(result);    
	}
	std::sort (thisPath.begin(), thisPath.end());
	it = std::unique (thisPath.begin(), thisPath.end());
	thisPath.resize( std::distance(thisPath.begin(),it) );
	//for(it=thisPath.begin();it<=thisPath.end();it++){outXML(*it);}
	return thisPath;
}
std::vector<std::string> split_paths(const char* envVar, const char* incasenothingexists){
	std::vector<std::string> thisPath;
	std::vector<std::string>::iterator it;
	std::string thisXDG;
	const char* datadirs=getenv(envVar);
    if (datadirs == NULL){
        thisXDG=incasenothingexists;
    }
    else{
		thisXDG=datadirs;
	}
    unsigned int numberOfPaths;
    std::string tempXDG = thisXDG;
    unsigned int tryer=0;
    unsigned int xdgLen=0;
    xdgLen=thisXDG.length();
    for (numberOfPaths=0;tryer<xdgLen;){
		tryer = tempXDG.find(":");
		tempXDG=tempXDG.erase(0,tryer+1);
		xdgLen=tempXDG.length();
		numberOfPaths++;
		
	}
    unsigned int lastPath = 0;
    std::string result;
    for (unsigned int whichPath=1;whichPath<=numberOfPaths;whichPath++){
		if (whichPath >=1){lastPath = whichPath - 1;}
		else {lastPath = 0;}
		std::string::size_type firstPosition = thisXDG.find_first_of(':');
		std::string::size_type position = thisXDG.find(':');
		for (unsigned int i=1;i<=whichPath;i++){position = thisXDG.find(':',position+1);}
		for (unsigned int j=1;j<=lastPath;j++){firstPosition = thisXDG.find(':',firstPosition+1);}
		result = thisXDG.substr (firstPosition+1,((position-firstPosition)-1));
		thisPath.push_back(result);    
	}
	std::sort (thisPath.begin(), thisPath.end());
	it = std::unique (thisPath.begin(), thisPath.end());
	thisPath.resize( std::distance(thisPath.begin(),it) );
	//for(it=thisPath.begin();it<=thisPath.end();it++){outXML(*it);}
	return thisPath;
}
std::vector<std::string> desktop_dirs(){
	 std::vector<std::string> desktop = split_paths("XDG_DATA_DIRS","/usr/local/share/:/usr/share/");
	 const char *datahome = getenv("HOME");
	 std::string thisXDG;
     if (datahome != NULL){
			thisXDG = datahome;
			thisXDG += "/.local/share/";
	}
	std::vector<std::string> user = split_paths("XDG_DATA_HOME",thisXDG.c_str());
	return desktop;
}
std::string make_menu_xdg(){
	std::vector<std::string> catarray;
	std::string menu_filename,line,JWM_MENU;
	std::vector<std::string> confdirs_array=split_paths("XDG_CONFIG_DIRS","/etc/xdg:/etc/xdg/xdg-torios");
		//$XDG_CONFIG_DIRS/menus/${XDG_MENU_PREFIX}applications.menu
	const char* XDG_MENU_PREFIX=getenv("XDG_MENU_PREFIX");
	if(XDG_MENU_PREFIX==NULL){
		XDG_MENU_PREFIX="jwm-";
	}
	std::string menuNAME=XDG_MENU_PREFIX;
	menuNAME+="applications.menu";
	std::string FALLBACKmenuNAME = "lxde-applications.menu";
	std::string testPATH;
	std::vector<std::string> MENUS=xdgmenufiles();
	std::vector<std::string> directoryFiles;
	for( std::vector<std::string>::iterator it = MENUS.begin();
		it!=MENUS.end();
		++it){
		testPATH = *it;
		//make sure this isn't blank
		std::string nO="<Name>";
		std::string mO= "<Menu>";
		std::string mC= "</Menu>";
		std::string dO="<Directory>";
		std::string iO="<Include>";
		std::string aO="<And>";
		std::string cO="<Category>";
		std::string NOT="<Not>";
		std::string NOTc="</Not>";
		std::string appdirs="<DefaultAppDirs/>";
		std::string dirdirs="<DefaultDirectoryDirs/>";
		std::string mergedirs="<DefaultMergeDirs/>";
		std::string testEntry;
		bool AppDirs, DirDirs, MergeDirs,Include,No;
		AppDirs=false;
		DirDirs=false;
		MergeDirs=false;
		Include=false;
		No=false;
		unsigned int baseMenu=0;
		std::string BASENAME,tempCat, NAME,DIRECTORY,CATEGORY;
		if( (testPATH.find(menuNAME)<testPATH.length()) || (testPATH.find(FALLBACKmenuNAME)<testPATH.length()) ){
			//outXML(testPATH);
			std::ifstream inputFileStrem (testPATH.c_str(), std::ifstream::in);
			if(inputFileStrem.is_open()){	
				while (getline(inputFileStrem,line)){
					unsigned int length =line.length();
					//RESET if we reach the end of a category
					if( (line.find(mO)) < length ){
						baseMenu++;
					}
					if( (line.find(NOT)) < length ){No=true;}
					if( (line.find(mC)) < length ){
						if(baseMenu>1){
							catarray=sortArray(catarray);
							directoryFiles=sortArray(directoryFiles);
							unsigned int finder=0;
							testEntry=makeXDGmenu(catarray,directoryFiles);
							finder=JWM_MENU.find(testEntry);
							if(finder>JWM_MENU.length()){
								//outXML(JWM_MENU);
								JWM_MENU+=testEntry;
							}
							NAME="";
							catarray.clear();
							directoryFiles.clear();
							
						//Boolean reset
							AppDirs=false;
							DirDirs=false;
							MergeDirs=false;
							Include=false;
							No=false;
						}
					}
					if (NAME.compare("")==0){
						if( (line.find(nO)) < length ){
							if(BASENAME.compare("")==0){BASENAME=chopTAG(line);}
							else{
								NAME=chopTAG(line);
								if (NAME.compare("")!=0){
									//outXML("adding Category: " + NAME);
									catarray.push_back(NAME);
								}
							}
						}
					}
					else{
						if( (line.find(appdirs))<length ){AppDirs=true;}
						if( (line.find(dirdirs))<length ){DirDirs=true;}
						if( (line.find(mergedirs))<length ){MergeDirs=true;}
						if(!Include){
							if( (line.find(dO)) < length){
								DIRECTORY=chopTAG(line);
								//outXML("adding direcotry: " + DIRECTORY);
								directoryFiles.push_back(DIRECTORY);
							}
							if( (line.find(iO)) <length){Include=true;}
						}
						else{
							if(!No){
								if( (line.find(cO)) <length ){
									CATEGORY=chopTAG(line);
									//outXML("adding Category: " + CATEGORY);
									catarray.push_back(CATEGORY);
								}
								
							}
							else{if( (line.find(NOTc)) <length ){No=false;}}
						}
					}
					
					
					
					  //<Name>Applications</Name>  hopefully
					     //submenu
					        //name
					          //stuff
					          //
					     //endsub   
					//UNTIL //</Menu>
				}
			}
		}
		
	}
	return JWM_MENU;
}

std::vector<std::string> xdgmenufiles(){
		//$XDG_CONFIG_DIRS/menus/${XDG_MENU_PREFIX}applications.menu
	std::string dirToOpen = "/etc/xdg/menus/";
	std::string pathToGet = "/menus/";
	std::string testPATH,tester,result,fullpath;
	std::vector<std::string> MENUS;
    std::vector<std::string> uniqueDirs = split_paths("XDG_CONFIG_DIRS","/etc/xdg:/etc/xdg/xdg-torios");
	unsigned int found = 0;
    //initialize directory reading variables to NULL
    DIR *dir = NULL;
	struct dirent *entryPointer = NULL;
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
		//make sure this isn't blank
		if(testPATH.compare("")!=0){
			//look to see if we have a / at the end... remove it if we do...
			found = testPATH.find_last_of('/');
			if (found == testPATH.length()-1){testPATH=testPATH.substr(0,testPATH.length()-1);}
			//see if there is a pathToGet directory
			dirToOpen = testPATH + pathToGet;
			dir = opendir(dirToOpen.c_str());
			if(dir!=NULL){
		    while ((entryPointer=readdir(dir)) != NULL){
				if ((entryPointer->d_type == DT_REG)&&(entryPointer->d_name[0] != '.')){
					fullpath = entryPointer->d_name;
					result=dirToOpen+fullpath;
					tester=dirToOpen+fullpath;
					unsigned period = result.find_last_of(".");
					bool isMENU = false;
					if(result.compare("")!=0){
						if(period<result.length()){
							std::string testmenu = result.substr(period+1,std::string::npos);
							if(testmenu.compare("menu")==0){isMENU = true;}
						}
						if(isMENU){
							MENUS.push_back(result); 
						} //isMENU
					}//result !empty
				}//it is a file
			}//readdir is not NULL
			}//dir!=NULL
			closedir(dir);
		}//testPath is not ""
	}//directory looper
	
	return MENUS;
}
std::vector<std::string> sortArray(std::vector<std::string> thisPath){
    std::vector<std::string>::iterator it;
    std::sort (thisPath.begin(), thisPath.end());
	it = std::unique (thisPath.begin(), thisPath.end());
	thisPath.resize( std::distance(thisPath.begin(),it) );
    return thisPath;
}
