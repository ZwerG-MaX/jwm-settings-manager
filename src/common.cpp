/*
 * linuxcommon.cpp
 * 
 * Copyright 2016 Israel Dahl <israeldahl@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#ifndef SOURCE_LINUX_COMMON_CPP
#define SOURCE_LINUX_COMMON_CPP

#define LINUX_COMMON__NS_BEGIN namespace linuxcommon { 
#define LINUX_COMMON__NS_END }
#include "../include/common.hpp"
LINUX_COMMON__NS_BEGIN

	///STRING FUNCTIONS
	std::string get_cache_dir(){
		std::string cacheFile;
		const char* xdgcache =  getenv("XDG_CACHE_HOME");
		if(xdgcache==NULL){
			const char* home = getenv("HOME");
			if(home==NULL){return NULL;}
			else{
				std::string temp = home;
				temp+="/.cache";
				cacheFile=temp;
			}
		}
		else{
			cacheFile=xdgcache;
		}
		if(cacheFile.compare("")==0){return "";}
		if(!test_dir(cacheFile)){mkdir_p(cacheFile.c_str());}
		return 	cacheFile;
	}
	std::string get_symlinkpath(std::string symlink){
		std::vector<char> buf(400);
		size_t len;
		do{
			buf.resize(buf.size() + 100);
			len = ::readlink(symlink.c_str(), &(buf[0]), buf.size());
		}
		while(buf.size() == len);
		if (len > 0){
			buf[len] = '\0';
			return (std::string(&(buf[0])));
		}
		echo_error("Error with symlink");
		return "";
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
	std::string quote_xml(std::string input){
		std::string amp="&#09;";
		input=sed_i(input,"&",amp);
		std::string tab="&#09;";
		//input=sed_i(input,'\t',tab);
		std::string newline="&#10;";
		//input=sed_i(input,'\n',newline);
		std::string exclame="&#33;";
		input=sed_i(input,"!",exclame);
		std::string quote="&#34;";
		input=sed_i(input,"\"",quote);
		std::string dolla="&#36;";
		input=sed_i(input,"$",dolla);
		std::string percent="&#37;";
		input=sed_i(input,"%",percent);
		std::string single_quote="&#39;";
		input=sed_i(input,"'",single_quote);
		std::string open_paren="&#40;";
		input=sed_i(input,"(",open_paren);
		std::string close_paren="&#41;";
		input=sed_i(input,")",close_paren);
		std::string astrix="&#42;";
		input=sed_i(input,"*",astrix);
		std::string plus="&#43;";
		input=sed_i(input,"+",plus);
		std::string comma="&#44;";
		input=sed_i(input,",",comma);
		std::string minus="&#45;";
		input=sed_i(input,"-",minus);
		std::string period="&#46;";
		input=sed_i(input,".",period);
		std::string forward_slash="&#47;";
		input=sed_i(input,"/",forward_slash);
		std::string colon="&#58;";
		input=sed_i(input,":",colon);
		std::string lt="&#60;";
		input=sed_i(input,"<",lt);
		std::string eq="&#61;";
		input=sed_i(input,"=",eq);
		std::string gt="&#62;";
		input=sed_i(input,">",gt);
		std::string question="&#63;";
		input=sed_i(input,"?",question);
		std::string at="&#64;";
		input=sed_i(input,"@",at);
		std::string open_brack="&#91;";
		input=sed_i(input,"[",open_brack);
		std::string back_slash="&#92;";
		input=sed_i(input,"\\",back_slash);
		std::string close_brack="&#93;";
		input=sed_i(input,"]",close_brack);
		std::string carrot="&#94;";
		input=sed_i(input,"^",carrot);
		std::string underscore="&#95;";
		input=sed_i(input,"_",underscore);
		std::string prog_apos="&#96;";
		input=sed_i(input,"`",prog_apos);
		std::string open_squig="&#123;";
		input=sed_i(input,"{",open_squig);
		std::string pipe="&#124;";
		input=sed_i(input,"|",pipe);
		std::string close_squig="&#125;";
		input=sed_i(input,"}",close_squig);
		std::string tilde="&#126;";
		input=sed_i(input,"~",tilde);
		return input;
	}
	std::string sed_i(std::string input, std::string remove, std::string replace){
		unsigned int xmlfix=0;
		unsigned int oldFind=0;
		while(input.find(remove,oldFind)<input.length()){
			xmlfix = input.find(remove,oldFind);
			oldFind=xmlfix+4;
			std::string tempPRE,tempPOST,temp;
			if(xmlfix<input.length()){
				temp=input;
				tempPOST=input;
				tempPRE = temp.erase(xmlfix,std::string::npos);
				tempPOST = input.erase(0,xmlfix+1);
				input = tempPRE + replace + tempPOST;
			}
		}
		return input;
	}
	std::string term_out(std::string terminal_Command_You_Want_Output_From) {
		if(terminal_Command_You_Want_Output_From.compare("")==0){return "";}
		const char* LANG=getenv("LANG");
		std::string LOCALE;
		if(LANG==NULL){
			LANG=getenv("LANGUAGE");
			if(LANG!=NULL){
				std::string tmp=LANG;
				unsigned int find=tmp.find(".UTF-8");
				if(find>tmp.length()){tmp+=".UTF-8";}
				LOCALE=tmp;
			}
		}
		else{
			LOCALE=LANG;
		}
		if(LOCALE.compare("")!=0){setlocale(LC_ALL, LOCALE.c_str());}
		std::string result="";
		const int max_buffer = 1024;
		char buffer[max_buffer];
		FILE *command_p = popen(terminal_Command_You_Want_Output_From.c_str(), "r");
		if (command_p){
			while( fgets(buffer, sizeof(buffer), command_p) !=NULL){result.append(buffer);}
			pclose(command_p);
		}
		else{ return "";}
		if (result.compare("")==0){return "";}
		int end = result.length();
		if((end-1) == 0){return "";}
		if((end) == 0){return "";}
		//std::cout<<result<<"Length="<<result.length();
		return result.erase(end-1,1);
	}
	std::string current_path(int whichPath){
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
		return result;
	}
	std::string current_directory(){
		char buff [ PATH_MAX ];
		if(getcwd(buff,PATH_MAX)==0){
			int error = errno;
			switch ( error ){
				case EACCES:
				throw std::runtime_error("Access denied");
				case ENOMEM:
					throw std::runtime_error("Insufficient storage"); 
				default: {
					std::ostringstream str;
					str << "Unrecognised error" << error;
					throw std::runtime_error(str.str());
					
				}
			}
		}
		if(buff==NULL){return "";}
		std::string dirToOpen=(buff);
		unsigned int finder=dirToOpen.rfind('/');
		if(finder+1!=dirToOpen.length()){
			dirToOpen+="/";
		}
		return dirToOpen;
	}
	std::string get_gtk_theme(){
		std::string gtkrc2_result, gtkrc3_result,gtk2;
		std::string GSETTINGS=term_out("which gsettings");
		std::string GCONF2=term_out("which gconftool-2");
		if(GSETTINGS.find("gsettings")<GSETTINGS.length()){
			gtkrc3_result=term_out(GSETTINGS+" get org.gnome.desktop.interface icon-theme");
			//gtkrc3_result=remove_cruft(gtkrc3_result,"gtk-icon-theme-name=");
			gtkrc3_result=remove_cruft(gtkrc3_result,"\'");
			gtkrc3_result=remove_cruft(gtkrc3_result,"\'");
			return gtkrc3_result;
		}
		if(GCONF2.find("gconftool-2")<GCONF2.length()){
			gtk2=term_out(GCONF2+" --get /desktop/gnome/interface/icon_theme");
			return gtk2;
		}
		const char* home = getenv("HOME");
		if(home==NULL){return "hicolor";}
		std::string HOME=home;
		//CHECK/SET GTKRC FILES
		std::string GTKRC2=HOME + "/.gtkrc-2.0";
		const char* xdg_config_home=getenv("XDG_CONFIG_HOME");
		std::string XDG_CONFIG_HOME;
		if (xdg_config_home!=NULL){
			XDG_CONFIG_HOME=xdg_config_home;
		}
		else{
			XDG_CONFIG_HOME=HOME +"/.config";
		}
		std::string GTKRC3=XDG_CONFIG_HOME + "/gtk-3.0/settings.ini";
		if(test_file(GTKRC3.c_str())){
			gtkrc3_result=get_line_with_equal(GTKRC3,"gtk-icon-theme-name=");
			gtkrc3_result=remove_cruft(gtkrc3_result,"gtk-icon-theme-name=");
			gtkrc3_result=remove_cruft(gtkrc3_result,"\"");
			gtkrc3_result=remove_cruft(gtkrc3_result,"\"");
			return gtkrc3_result;
		}
		if(test_file(GTKRC2.c_str())){
			gtkrc2_result=get_line_with_equal(GTKRC2,"gtk-icon-theme-name=");
			gtkrc2_result=remove_cruft(gtkrc2_result,"\"");
			gtkrc2_result=remove_cruft(gtkrc2_result,"\"");
			return gtkrc2_result;
		}
		return "hicolor";
	}
	
	std::string remove_cruft(std::string StringInput, std::string CruftToRemove){
		if((StringInput.compare("")==0)||(CruftToRemove.compare("")==0)){return StringInput;}
		unsigned int found=0;
		unsigned int cruftLength=CruftToRemove.length();
		found=StringInput.find(CruftToRemove);
		if(found>StringInput.length()){return StringInput;}
		std::string temp=StringInput;
		temp=temp.erase(0,found+cruftLength);
		if(temp.compare("")!=0){return temp;}
		std::string temp2=StringInput;
		temp2=temp2.erase(found,std::string::npos);
		if(temp2.compare("")!=0){return temp2;}
		echo_error("There was a problem removing the cruft.... Giving you back your string");
		return StringInput;
	}
	std::string find_xdg_data_dir_subdir(std::string subdir){
		std::vector<std::string> xdgDataDirs = desktop_dirs();
		std::string dirToOpen;
		for( std::vector<std::string>::iterator it = xdgDataDirs.begin();
		it!=xdgDataDirs.end();
		++it){
			dirToOpen=*it;
			unsigned int finder=dirToOpen.rfind('/');
			if(finder+1==dirToOpen.length()){
				dirToOpen+=subdir;
			}
			else{
				dirToOpen+="/";
				dirToOpen+=subdir;
			}
			if(test_dir(dirToOpen)){
				if(finder+1==dirToOpen.length()){
					return dirToOpen;
				}
				else{
					dirToOpen+="/";
					return dirToOpen;
				}
			}
			else{echo_error(dirToOpen+" does not exist");}
		}
		return "";
	}
	std::string find_xdg_config_dir_subdir(std::string subdir){
		std::vector<std::string> xdgDataDirs = xdg_conf_dirs();
		std::string dirToOpen;
		for( std::vector<std::string>::iterator it = xdgDataDirs.begin();
		it!=xdgDataDirs.end();
		++it){
			dirToOpen=*it;
			unsigned int finder=dirToOpen.rfind('/');
			if(finder+1==dirToOpen.length()){
				dirToOpen+=subdir;
			}
			else{
				dirToOpen+="/";
				dirToOpen+=subdir;
			}
			if(test_dir(dirToOpen)){
				if(finder+1==dirToOpen.length()){
					return dirToOpen;
				}
				else{
					dirToOpen+="/";
					return dirToOpen;
				}
			}
		}
		return "";
	}
	std::string color_double_to_string(const double *rgb){
		char tmp[8];
		std::snprintf(tmp, sizeof(tmp), "#%02x%02x%02x", int(rgb[0]), int(rgb[1]), int(rgb[2]));
		return tmp;
	}
	std::string look_for_file_in_subdirs(std::string fileWITHOUTpath,std::string dir){
		if((dir.compare("")==0)||(fileWITHOUTpath.compare("")==0))return "";
		if(!test_dir(dir))return "";
		std::string ANSWERS;
		DIR *mydir=NULL;
		struct dirent *entryPointer=NULL;
		mydir=opendir(dir.c_str());
		if(mydir!=NULL){
			while ((entryPointer=readdir(mydir))!=NULL){
				if(((entryPointer->d_type == DT_LNK)||(entryPointer->d_type == DT_REG))&&(entryPointer->d_name[0]!='.')){
					std::string fullpath=entryPointer->d_name;
					if(dir.rfind('/')!=dir.length()-1){dir+="/";}
					fullpath=dir+fullpath;
					unsigned int findIT = fullpath.find(fileWITHOUTpath);
					if(findIT<=fullpath.length()){
						if(ANSWERS.rfind(",")!=ANSWERS.length()-1)ANSWERS+=",";
						ANSWERS+=fullpath;
					}
				}
				if((entryPointer->d_type==DT_DIR)&&(entryPointer->d_name[0]!='.')){
					std::string fullpath=entryPointer->d_name;
					if(dir.rfind('/')!=dir.length()-1){dir+="/";}
					fullpath=dir+fullpath;
					std::string thisAnswer=look_for_file_in_subdirs(fileWITHOUTpath,fullpath);
					if(thisAnswer.compare("")!=0){
						if(ANSWERS.rfind(",")!=ANSWERS.length()-1){
							ANSWERS+=",";
						}
						ANSWERS+=thisAnswer;
					}
				}
				
			}
		}
		closedir(mydir);
		if(ANSWERS.compare("")!=0){
			return ANSWERS;
		}
		return "";
	}
	std::string look_for_first_file_in_subdirs(std::string fileWITHOUTpath,std::string dir){//,std::string answer){
		//echo("std::string look_for_first_file_in_subdirs(std::string "+fileWITHOUTpath+",std::string "+dir);//+",std::string "+answer+")");
		if((dir.compare("")==0)||(fileWITHOUTpath.compare("")==0)){
			echo_error("std::string look_for_first_file_in_subdirs(std::string fileWITHOUTpath,std::string dir) requires non empty variables to work\nMUST EXIT");
			return "";
		}
		if(!test_dir(dir)){
			echo_error(dir+" is not a directory\nMUST EXIT");
			return "";
		}
		std::string ANSWERS;
		DIR *mydir=NULL;
		struct dirent *entryPointer=NULL;
		mydir=opendir(dir.c_str());
		std::string finalAnswer;
		if(mydir!=NULL){
			while ((entryPointer=readdir(mydir))!=NULL){
				std::string fullpath=entryPointer->d_name;
				if(dir.rfind('/')!=dir.length()-1){dir+="/";}
				fullpath=dir+fullpath;
				if(((entryPointer->d_type == DT_LNK)||(entryPointer->d_type == DT_REG))&&(entryPointer->d_name[0]!='.')){
					std::string tempFINDER="/"+fileWITHOUTpath;
					//echo("FINDER:"+tempFINDER+"\nfullpath="+fullpath);
					unsigned int findIT = fullpath.find(tempFINDER);
					if(findIT<=fullpath.length()){
						if(entryPointer->d_type == DT_LNK){
							std::string temporary=get_symlinkpath(fullpath);
							echo("SYMLINK="+fullpath+"\nFile="+temporary);
							if(temporary.compare("")!=0){
								closedir(mydir);
								if(temporary.find("/")>temporary.length()){temporary=dir+temporary;}
								echo("Symlink="+temporary);
								finalAnswer=temporary;
								return temporary;
							}
						}
						else{
							closedir(mydir);
							finalAnswer=fullpath;
							return fullpath;
						}
					}
				}
				if((entryPointer->d_type==DT_DIR)&&(entryPointer->d_name[0]!='.')){
					std::string thisAnswer=look_for_first_file_in_subdirs(fileWITHOUTpath,fullpath);//,thisAnswer);
					if(thisAnswer.compare("")!=0){
						if(test_file(thisAnswer)){
							closedir(mydir);
							finalAnswer=thisAnswer;
							return thisAnswer;
						}
					}
				}
			}
		}
		else{echo_error(dir+" cannot be opened\nMUST EXIT");}
		echo("Final Answer="+finalAnswer);
		return finalAnswer;
	}
	std::string look_for_icon_file(std::string fileWITHOUTpath){//,std::string answer){
		std::string dir=find_xdg_data_dir_subdir("icons");
		echo("std::string look_for_icon_file(std::string "+fileWITHOUTpath+")");
		std::string gtktheme=get_gtk_theme();
		if(dir.rfind('/')!=dir.length()-1){dir+="/";}
		std::string testingDIR=dir+gtktheme;
		if(testingDIR.rfind('/')!=testingDIR.length()-1){testingDIR+="/";}
		if(test_dir(testingDIR)){dir=testingDIR;}
		if(fileWITHOUTpath.compare("")==0){
			echo_error("std::string testingDIR(std::string fileWITHOUTpath) requires non empty variables to work\nMUST EXIT");
			return "";
		}
		//echo("GTKtheme="+gtktheme+"\nDir="+dir);
		if(!test_dir(dir)){
			echo_error(dir+" is not a directory\nTrying to look in icons directories");
			dir=find_xdg_data_dir_subdir("icons");
			if(!test_dir(dir)){
				echo_error(dir+" is not a directory\nMUST EXIT");
				return "";
			}
			return look_for_first_file_in_subdirs(fileWITHOUTpath,dir);
		}
		std::string ANSWERS;
		DIR *mydir=NULL;
		struct dirent *entryPointer=NULL;
		mydir=opendir(dir.c_str());
		std::string finalAnswer;
		if(mydir!=NULL){
			while ((entryPointer=readdir(mydir))!=NULL){
				std::string fullpath=entryPointer->d_name;
				if(dir.rfind('/')!=dir.length()-1){dir+="/";}
				fullpath=dir+fullpath;
				if((entryPointer->d_type == DT_REG)&&(entryPointer->d_name[0]!='.')){
					std::string tempFINDER="/"+fileWITHOUTpath;
					unsigned int findIT = fullpath.find(tempFINDER);
					if(findIT<=fullpath.length()){
						closedir(mydir);
						finalAnswer=fullpath;
						return fullpath;
					}
				}
				if((entryPointer->d_type==DT_DIR)&&(entryPointer->d_name[0]!='.')){
					std::string thisAnswer=look_for_first_file_in_subdirs(fileWITHOUTpath,fullpath);//,thisAnswer);
					if(thisAnswer.compare("")!=0){
						if(test_file(thisAnswer)){
							closedir(mydir);
							finalAnswer=thisAnswer;
							return thisAnswer;
						}
					}
				}
			}
		}
		else{echo_error(dir+" cannot be opened\nMUST EXIT");}
		echo("Final Answer="+finalAnswer);
		return finalAnswer;
	}
#ifdef LINUX_COMMON_HAS_X
	std::string x_color_from_name(const char *colorName){
	/* Paul Sladen, 2014-08-13, Public Domain
	* XLookupColor() -> RGB colour value example, per request on
	* http://irclogs.ubuntu.com/2014/08/13/%23ubuntu-devel.html#t19:52
	* grep MistyRose /usr/share/X11/rgb.txt | awk '{printf("%02x%02x%02x\n",$1,$2,$3);}'
	* http://manpages.ubuntu.com/manpages/man3/XQueryColor.3.html
	* gcc xlookupcolour.c -o xlookupcolour -lX11 && ./xlookupcolour red yellow blue
	modified for use in this program by Israel <israeldahl@gmail.com>
	Thanks Sladen for the quick help!!!!
	*/
		Display *dpy;
		Colormap map;
		int scr;
		XColor rgb, nearest_rgb;
//    const char *fallback_colours[] = {"red", "white", "blue", "pink", NULL};
		dpy = XOpenDisplay(NULL);
		scr = XDefaultScreen(dpy);
		map = DefaultColormap(dpy, scr);
		XLookupColor(dpy, map, colorName, &rgb, &nearest_rgb);
		//printf("%3d %3d %3d %s\n", rgb.red>>8, rgb.green>>8, rgb.blue>>8, colorName);
		int red = (int)rgb.red>>8;
		int green = (int)rgb.green>>8;
		int blue = (int)rgb.blue>>8;
		//std::cout<< "r= "<<red<<"  g= "<<green<<"  b= "<<blue<<'\n';
		char tmp[8];
		std::snprintf(tmp, sizeof(tmp), "#%02x%02x%02x", red, green, blue);
		std::string output = tmp;
		return output;
	}
#endif
	
	std::string convert_num_to_string(int num){
		std::string number;
		std::stringstream out;
		out << num;
		number = out.str();
		return number;
	}
	std::string get_line_with_equal(std::string filename, std::string line){
		if(line.compare("")==0){return "";}
		/*std::string tester=filename;
		if(test_file(line)){
			echo_error(line+" is actually a file");
			filename=line;
			line=tester;
		}*/
		if(filename.compare("")==0){return "";}
		if(!test_file(filename)){echo_error("No file sent in\n"+filename+","+line);}
		std::string thisLine;
		std::string subString;
		std::ifstream inputFileStream(filename.c_str(), std::ifstream::in);
		if(inputFileStream.is_open()){
			while (getline(inputFileStream,thisLine)){
				//echo_error(thisLine);
				if(thisLine.find(line)<thisLine.length()){
					unsigned int found =thisLine.find("=");
					if(found < thisLine.length()){
						subString=thisLine.substr(found+1,std::string::npos);
						return subString;
					}
				}
			}
		}
		else{echo_error("Could not open filestream for "+filename);}
		return "";
	}
	std::string remove_percentage(std::string line){
		if(line.compare("")==0){return line;}
		unsigned int percentfind=0;
		std::string tempstring;
		percentfind=line.find_first_of(" %",0);
		if(percentfind>line.length()){return line;}
		unsigned int semifind=line.find_first_of(";",percentfind);
		bool andis=false;
		bool semiis=false;
		if(semifind<line.length()){semiis=true;}
		unsigned int andfind=line.find_first_of("&",percentfind);
		if(andfind<line.length()){andis=true;}
		if(andis && semiis){
			if(andfind<semifind){tempstring=line.erase(percentfind, andfind);}
			else{tempstring=line.erase(percentfind, semifind);}
		}
		else if(andis){tempstring=line.erase(percentfind, andfind);}
		else if(semiis){tempstring=line.erase(percentfind, semifind);}
		else{tempstring=line.erase(percentfind, std::string::npos);}
		return tempstring;
	}
	std::string get_directory_from_filename(std::string filename){
		unsigned int finder=filename.rfind("/");
		if(finder<filename.length()){
			filename=filename.erase(finder,std::string::npos);
		}
		else{return "";} //return empty if there is no directory
		return filename;
	}
	const char* convert_num_to_string(double num){
		std::string number;
		std::stringstream out;
		out << num;
		number = out.str();
		if(number.compare("")==0){return NULL;}
		return number.c_str();
	}

	std::string test_file_in_vector_path(std::string fileWithNOPATH,std::vector<std::string> directories_to_check){
		//echo_error("test_file_in_vector_path... filepath ORIGINAL="+fileWithNOPATH);
		if(fileWithNOPATH.compare("")==0){return "";}
		std::string filePathRemoved=fileWithNOPATH;
		unsigned int found=filePathRemoved.rfind('/');
		if(found<filePathRemoved.length()){
			unsigned int len=filePathRemoved.length()-found;
			filePathRemoved=filePathRemoved.erase(0,len);
			//echo_error("test_file_in_vector_path... filepath removed="+filePathRemoved<);
		}
		for( std::vector<std::string>::iterator it = directories_to_check.begin();
		it!=directories_to_check.end();
		++it){
			std::string dirToOpen=*it;
			unsigned int finder=dirToOpen.rfind('/');
			if(finder+1==dirToOpen.length()){
				dirToOpen+=filePathRemoved;
				//echo_error("test_file_in_vector_path... dir to open="+dirToOpen);
			}
			else{
				dirToOpen+="/";
				dirToOpen+=filePathRemoved;
				//echo_error("test_file_in_vector_path... dir to open="+dirToOpen);
			}
			if(test_file(dirToOpen)){return dirToOpen;}
		}
		//echo_error("test_file_in_vector_path... found NO files");
		return "";
	}
	std::string fix_file_path_for_command_line(std::string filepath){
		std::string Filename=filepath;
		std::string escape = "\\ ";
		size_t start_pos = 0;
		while((start_pos = Filename.find(' ', start_pos)) != std::string::npos) {
			Filename.replace(start_pos, 1, escape);
			start_pos += escape.length(); // Handles case where 'to' is a substring of 'from'
			//std::cout<<Filename<<std::endl;
		}
		return Filename;
	}
	std::string file_to_string(std::string filename){
		if(filename.compare("")==0){return "";}
		if(!test_file(filename)){echo_error("No file sent in: "+filename);}
		std::string thisLine;
		std::string fullString;
		std::ifstream inputFileStream(filename.c_str(), std::ifstream::in);
		if(inputFileStream.is_open()){
			while (getline(inputFileStream,thisLine)){
				if(fullString.compare("")==0){fullString=thisLine;}
				else{fullString=fullString+"\n"+thisLine;}
			}
		}
		return fullString;
	}
	std::string get_shell_for_C(){
		std::string shell=term_out("which bash");
		if(shell.compare("")==0){
			if(!test_exec(shell)){
				shell=term_out("which sh");
				if(!test_exec(shell)){return "";}
				//TODO make this work for others
			}
		}
		shell=shell+" -c '";
		return shell;
	}
		///VECTOR FUNCTIONS
	std::vector<std::string> get_file_vector(std::string DIRECTORY,std::string file){
		std::vector<std::string> myVector;
		if(!test_dir(DIRECTORY)){return myVector;}
		if(DIRECTORY.compare("")==0){return myVector;}
		if(file.compare("")==0){return myVector;}
		DIR *mydir=NULL;
		struct dirent *entryPointer=NULL;
		mydir=opendir(DIRECTORY.c_str());
		if(DIRECTORY.rfind('/')!=DIRECTORY.length()-1){DIRECTORY+="/";}
		if(mydir!=NULL){
			while ((entryPointer=readdir(mydir))!=NULL){
				if((entryPointer->d_type == DT_REG)&&(entryPointer->d_name[0]!='.')){
					std::string fullpath=entryPointer->d_name;
					fullpath=DIRECTORY+fullpath;
					unsigned int findIT = fullpath.find(file);
					if(findIT<=fullpath.length()){
						myVector.push_back(fullpath);
					}
				}
				if((entryPointer->d_type==DT_DIR)&&(entryPointer->d_name[0]!='.')){
					std::string fullpath=entryPointer->d_name;
					fullpath=DIRECTORY+fullpath;
					if(fullpath.rfind('/')!=fullpath.length()-1){fullpath+="/";}
					std::string thisAnswer=look_for_file_in_subdirs(file,fullpath);
					if(thisAnswer.compare("")!=0){
						std::string temp=fullpath+file;
						myVector.push_back(temp);
					}
				}
				
			}
		}
		myVector=sort_array(myVector);
		return myVector;
		
	}
	std::vector<std::string> grep_lines(const char* args, const char* filename){
		std::vector<std::string> result;
		std::string line;
		std::string stringARGS = args;
		std::string sub;
		std::ifstream ifs (filename, std::ifstream::in);
		if(ifs.is_open()){
			while (getline(ifs,line)){
				if(line.find(stringARGS)<line.length()){result.push_back(line);}
			}
		}
		return result;
	
	}
	std::vector<std::string> comma_vector(std::string LINE,std::vector<std::string> Vector){
		//std::vector<std::string> itemsVector;
		std::string original,preComma,postComma;
		original=LINE;
		unsigned int found,finder;
		finder=original.length();
		for(found=original.find(",");found<finder;found=original.find(",")){
			preComma=original;
			postComma=original;
			preComma=preComma.erase(found,std::string::npos);
			if(preComma.compare("")!=0){Vector.push_back(preComma);}
			postComma=postComma.erase(0,found+1);
			original=postComma;
			finder=original.length();
		}
		if(postComma.compare("")!=0){Vector.push_back(postComma);}
		return Vector;
	}
	std::vector<std::string> sort_array(std::vector<std::string> thisPath){
		std::vector<std::string>::iterator it;
		std::sort (thisPath.begin(), thisPath.end());
		it = std::unique (thisPath.begin(), thisPath.end());
		thisPath.resize( std::distance(thisPath.begin(),it) );
		return thisPath;
	}
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
		//for(it=thisPath.begin();it<=thisPath.end();it++){echo(*it);}
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
		//for(it=thisPath.begin();it<=thisPath.end();it++){echo(*it);}
		return thisPath;
	}
	std::vector<std::string> file_to_vector(std::string filename){
		std::vector<std::string> fullString;
		if(filename.compare("")==0){return fullString;}
		if(!test_file(filename)){echo_error("No file sent in: "+filename);}
		std::string thisLine;
		std::ifstream inputFileStream(filename.c_str(), std::ifstream::in);
		if(inputFileStream.is_open()){
			while (getline(inputFileStream,thisLine)){fullString.push_back(thisLine);}
		}
		return fullString;
	}
	std::vector<std::string> desktop_dirs(){
		std::vector<std::string> desktop = split_paths("XDG_DATA_DIRS","/usr/local/share/:/usr/share/");
		const char *datahome = getenv("HOME");
		std::string thisXDG;
		if (datahome != NULL){
				thisXDG = datahome;
				thisXDG += "/.local/share/";
		}
		//std::vector<std::string> user = split_paths("XDG_DATA_HOME",thisXDG.c_str());
		return desktop;
	}
	std::vector<std::string> xdg_conf_dirs(){
		std::vector<std::string> desktop = split_paths("XDG_CONFIG_DIRS","/etc/xdg/xdg-torios:/etc/xdg");
		const char *datahome = getenv("HOME");
		std::string thisXDG;
		if (datahome != NULL){
				thisXDG = datahome;
				thisXDG += "/.config/";
		}
		std::vector<std::string> user = split_paths("XDG_CONFIG_HOME",thisXDG.c_str());
		//std::vector<std::string> dirs = join_string_vectors(user,desktop);
		return desktop;
	}
	std::string home_path(){
		const char* homer=getenv("HOME");
		if(homer==NULL){return "";}
		std::string homePath=homer;
		homePath+="/";
		return homePath;
	}
	std::vector<std::string> join_string_vectors(std::vector<std::string> vectorA,std::vector<std::string> vectorB){
		std::vector<std::string> bothVectors;
		bothVectors.reserve(vectorA.size()+vectorB.size());
		bothVectors.insert(bothVectors.end(),vectorA.begin(),vectorA.end());
		bothVectors.insert(bothVectors.end(),vectorB.begin(),vectorB.end());
		return bothVectors;
	}
///BOOLEAN FUNCTIONS
	bool look_for_string_in_vector(std::vector<std::string> vector_to_check,std::string item_to_find){
		for( std::vector<std::string>::iterator it = vector_to_check.begin();
		it!=vector_to_check.end();
		++it){
			std::string tmp=*it;
			if(tmp.compare(item_to_find)==0){return true;}
		}
		return false;
	}
	bool test_file(std::string fileWithFullPATH){
		if(fileWithFullPATH.compare("")==0){
			echo_error("Empty string sent into bool test_file(std::string fileWithFullPATH)");
			return false;
		}
		std::string dir=get_directory_from_filename(fileWithFullPATH);
		if(dir.compare("")==0){
			echo_error("Empty directory returned from std::string dir=get_directory_from_filename("+fileWithFullPATH+");");
			return false;
		}
		DIR *mydir=NULL;
		struct dirent *entryPointer=NULL;
		mydir=opendir(dir.c_str());
		if(mydir!=NULL){
			while ((entryPointer=readdir(mydir))!=NULL){
				if(entryPointer->d_type == DT_REG){
					std::string fullpath=entryPointer->d_name;
					if(dir.rfind('/')!=dir.length()-1){dir+="/";}
					fullpath=dir+fullpath;
					if(fullpath.compare(fileWithFullPATH)==0){
						//echo_error(fileWithFullPATH+" is a file!");
						closedir(mydir);
						return true;
					}
				}
			}
		}
		else{echo_error("could not open directory to search for "+fileWithFullPATH);}
		return false;
	}
	bool test_exec(std::string execToTest){
		if(execToTest.compare("")==0){return false;}
		/// my cheat sheet
		// /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
		std::string stringEXEC;
		std:: string testPATH, testExec;
		bool result = false;
		unsigned int numofpaths = items_in_path();
		for (unsigned int i = 1; i <= numofpaths; i++){
			stringEXEC = execToTest;
			testPATH = current_path(i);
			stringEXEC = testPATH + "/" + stringEXEC;
			//TODO check executable quality
			if(test_file(stringEXEC.c_str())){return true;}
		}
		return result;
	}
	bool test_dir(std::string dirToTest){
		if(dirToTest.compare("")==0){return false;}
		DIR *dir = NULL;
		dir = opendir(dirToTest.c_str());
		if (dir!=NULL){
			closedir(dir);
			return true;
		}
		return false;
	}
	bool save_string_to_file(std::string MSG,std::string filename){
		if(MSG.compare("")==0){return false;}
		if(filename.compare("")==0){return false;}
		unsigned int last=filename.rfind('/');
		//cannot be a directory
		if(last+1==filename.length()){return false;}
		///must have some path
		if(last<filename.length()){
			//generally assume they know what they are doing sending in a filename if it has at least one '/'
			std::string dircheck=filename;
			dircheck=dircheck.erase(last,std::string::npos);
			if(!test_dir(dircheck)){mkdir_p(dircheck);}
		}
		else{
			//lets put it in the user's $HOME if they didn't give a path.
			std::string temp=home_path();
			temp+=filename;
			filename=temp;
		}
		std::ofstream dest;
		dest.open(filename.c_str());
		if(!dest.is_open()){return false;}
		dest << MSG;
		dest.close();
		//if(dest.is_open()){return false;}
		return true;
	}
	bool has_file_extention_at_end(std::string filename,std::string extention){
		std::string extention_check;
		std::transform(filename.begin(), filename.end(), filename.begin(), ::tolower);
		std::transform(extention.begin(), extention.end(), extention.begin(), ::tolower);
		unsigned int found=filename.find(extention);
		unsigned int ext_len=extention.length();
		unsigned int file_len=filename.length();
		if(found<file_len){
			if(found==(file_len-ext_len)){return true;}
		}
		return false;
	}
	bool program_is_running(std::string program_line){
			//std::cout<<"bool program_is_running(std::string "<<program_line<<")"<<std::endl;
			if(program_line.compare("")==0){return false;}
			int pid=getProcIdByName(program_line);
			if(pid>0){return true;}
			std::string pgrepProg=term_out("which pgrep");
			if(pgrepProg.compare("")==0){
				//TODO: make a way for this to still check...
				return false;
			}
			//std::cout<<"pgrep is "+pgrepProg<<std::endl;
			std::string shell=get_shell_for_C();
			if(shell.compare("")==0)return false;
			//std::cout<<"Using shell command="+shell<<std::endl;
			std::string processline=program_line;
			std::string pgrep = shell + " "+pgrepProg+" "+program_line+ "'";
			//std::cout<<"Total command to run:\n"+pgrep<<std::endl;
			std::string returnVal=term_out(pgrep);
			if(returnVal.compare("")==0){return false;}
			return true;
	}
	bool pkill(std::string programname){
		int pid=getProcIdByName(programname);
		if(pid<=0){
			echo_error("Invalid process ID for "+programname);
			return false;
		}
		int result=kill(pid,SIGKILL);
		if(result==0){return true;}
		else{
			switch (errno){
				case EINVAL:
					// This should not happen normally....
					echo_error("Invalid SIGNAL sent to kill: "+programname);
				case EPERM:
					echo_error("You do not have permission to kill the process: "+programname);
				case ESRCH:
					echo_error("Cannot find the PID of: "+programname);
				default: echo_error("Invalid error inside pkill function");
			}
		}
		return false;
		
	}
	//INTEGER FUNCTIONS
	unsigned int convert_string_to_number(const char* num){
		if(num==NULL){return 0;}
		std::string empty="";
		if(empty.compare(num)==0){return 0;}
		std::stringstream out;
		out << num;
		unsigned int integer;
		out >> integer;
		return integer;
	}
	int getProcIdByName(std::string procName){
		int pid = -1;
		if(procName.compare("")==0){return -1;}
		// Open the /proc directory
		DIR *dp = opendir("/proc");
		if (dp != NULL){
			// Enumerate all entries in directory until process found
			struct dirent *dirp;
			while (pid < 0 && (dirp = readdir(dp))){
				// Skip non-numeric entries
				int id = atoi(dirp->d_name);
				if (id > 0){
					// Read contents of virtual /proc/{pid}/cmdline file
					std::string cmdPath = std::string("/proc/") + dirp->d_name + "/cmdline";
					std::ifstream cmdFile(cmdPath.c_str());
					std::string cmdLine;
					getline(cmdFile, cmdLine);
					if (!cmdLine.empty()){
						// Keep first cmdline item which contains the program path
						size_t pos = cmdLine.find('\0');
						if (pos != std::string::npos){cmdLine = cmdLine.substr(0, pos);}
						// Keep program name only, removing the path
						pos = cmdLine.rfind('/');
						if (pos != std::string::npos){cmdLine = cmdLine.substr(pos + 1);}
						// Compare against requested process name
						if (procName == cmdLine){pid = id;}
					}
				}
			}
		}
		closedir(dp);
		std::cout<<"Process Name="<<procName<<" pid="<<pid<<std::endl;
		return pid;
	}
	int mkdir_p(std::string dirToMake){
		if(test_dir(dirToMake.c_str())){return 0;}
		std::string temporaryDir=dirToMake;
		unsigned int last=dirToMake.rfind('/');
		if(last+1!=dirToMake.length()){dirToMake+="/";}
		//std::cout<<dirToMake<<std::endl;
		unsigned int found=dirToMake.find_first_of('/');
		while(found<dirToMake.length()){
			found++;
			temporaryDir=dirToMake;
			std::string testing=temporaryDir.erase(found,std::string::npos);
			found=dirToMake.find_first_of('/',found);
			if(!test_dir(testing.c_str())){
				if(mkdir(testing.c_str(), 0700)>0){return 1;}
				else{echo("Made: "+testing);}
			}
		}
		return 0;
	}
	int run_a_program(std::string program){
		std::string shell=get_shell_for_C();
		if(shell.compare("")!=0){
			shell+=program;
			shell+="'";
		}
		else{shell=program;}
		return system(shell.c_str());
	}
	int run_a_program_in_background(std::string program){
		std::string shell=get_shell_for_C();
		program += " &disown";
		if(shell.compare("")!=0){
			shell+=program;
			shell+="'";
		}
		else{shell=program;}
		return system(shell.c_str());
	}
	unsigned int items_in_path(){
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
	#ifdef LINUX_COMMON_HAS_X
	unsigned int get_fl_color(std::string color){
		unsigned int c=0;
		return get_fl_color(color,c);
	}
	unsigned int get_fl_color(std::string color, unsigned int &color2){
		//std::cout<<"Color string="<<color<<std::endl;
		if(color.compare("")==0){color="#000000";}
		const char* input =color.c_str();
		std::string c1, c2;
		unsigned int flColor;
		std::string::size_type position = color.find(':');
		std::string::size_type validator = color.find('#');
		if(validator==0){
			if (color.length()>7){
				if((color.find(':')!=std::string::npos) && (color.find('#',position+1)!=std::string::npos)){
					c1 = color.substr (1,6);
					c2 = color.substr (9,6);
					c1="0x"+c1+"00";
					c2="0x"+c2+"00";
					//std::cout<< "color c1 = "<<c1<<" color2 = "<<c2<<"\n";
					flColor = strtoul(c1.c_str(),0,16);
					color2 = strtoul(c2.c_str(),0,16);
					//std::cout<<"flColor1 = "<<flColor<<" flColor2 = "<<color2<<"\n";
					return flColor;
				}
				else {
					echo_error("not a valid color");
					return 0;
				}
			}
			else{
				c1 = color.substr (1,6);
				c1="0x"+c1+"00";
				flColor = strtoul(c1.c_str(),0,16);
				//std::cout<<"color = "<<c1<<"\n";
				//std::cout<<"flColor = "<<flColor<<"\n";
				color2 = 0;
				return flColor;
			}
		}
		else{
			std::string value= x_color_from_name(input);
			return get_fl_color(value, color2);
		}
	}
	#endif
	///VOID FUNCTIONS
	void print_file_to_stdout(std::string fileNameWithFullPath){
		if(fileNameWithFullPath.compare("")==0){return;}
		std::string line;
		std::ifstream inputFileStrem (fileNameWithFullPath.c_str(), std::ifstream::in);
		if(inputFileStrem.is_open()){
          while (getline(inputFileStrem,line)){
			  std::cout<<line<<std::endl;
          }
      }
	}
	void echo(std::string msg){
		#ifdef COMMON_XMLOUT
			std::cout<<"<!--"<<msg<<"-->"<<std::endl;
		#elif QUIET_ERROR
			//do nothing
		#else
			std::cout<<msg<<std::endl;
		#endif
	}
	void echo_error(std::string msg){
		#ifdef COMMON_XMLOUT
			std::cerr<<"<!--"<<msg<<"-->"<<std::endl;
		#elif QUIET_ERROR
			//do nothing
		#else
			std::cerr<<msg<<std::endl;
		#endif
	}
LINUX_COMMON__NS_END


#endif
