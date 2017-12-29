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
	///const char* functions////////////////////////////////////////////
	/**
	 * @param
	 */
	const char* convert_num_to_string(double num){
		std::string number;
		std::stringstream out;
		out << num;
		number = out.str();
		if(number.compare("")==0){return NULL;}
		return number.c_str();
	}
	///STRING FUNCTIONS/////////////////////////////////////////////////
	//C
	/** check a list of executables to see if thy exist and return the first working one
	 * @param list the std::vector<std::string> list of executables to check
	 */
	std::string check_list_of_exec(std::vector<std::string> list){
		for( std::vector<std::string>::iterator it = list.begin();
		it!=list.end();
		++it){
			std::string tmp=*it;
			bool tester=test_exec(tmp);
			if(tester){return tmp;}
		}
		return "";
	}
	/** turn a double red green blue value into an HTML string
	 * @param rgb the double to convert
	 */
	std::string color_double_to_string(const double *rgb){
		char tmp[8];
		std::snprintf(tmp, sizeof(tmp), "#%02x%02x%02x", int(rgb[0]), int(rgb[1]), int(rgb[2]));
		return tmp;
	}
	/** convert an integer number to a string
	 * @param num the number to convert
	 */
	std::string convert_num_to_string(int num){
		std::string number;
		std::stringstream out;
		out << num;
		number = out.str();
		return number;
	}
	/** convert an unsigned integer to a string
	 * @param num the unsigned int to convert
	 */
	std::string convert_unsigned_to_string(unsigned int num){
		std::string number;
		std::stringstream out;
		out << num;
		number = out.str();
		return number;
	}
	/** return the current working directory */
	std::string current_directory(){
		char buff [ PATH_MAX ];
		/** use getcwd and handle errors */
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
		/** conver the buffer into a string */
		std::string dirToOpen=(buff);
		unsigned int finder=dirToOpen.rfind('/');
		/** append a / to the end */
		if(finder+1!=dirToOpen.length()){
			dirToOpen+="/";
		}
		return dirToOpen;
	}
	/** pick a path from the $PATH variable
	 *  these are separated by :
	 * @param whichPath specify which path to get
	 */
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
	//G
	/**get the XDG_CACHE_HOME variable OR $HOME/.cache*/
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
	/** Get XDG_CONFIG_HOME or the equivalent*/
	std::string get_config_dir(){
		std::string cacheFile;
		const char* xdgcache =  getenv("XDG_CONFIG_HOME");
		if(xdgcache==NULL){
			std::string home = home_path();
			if(home.compare("")==0){return home;}
			else{
				home+=".config";
				cacheFile=home;
			}
		}
		else{
			cacheFile=xdgcache;
		}
		if(cacheFile.compare("")==0){return "";}
		cacheFile+="/";
		if(!test_dir(cacheFile)){mkdir_p(cacheFile.c_str());}
		return 	cacheFile;
	}
	/** return the directory portion of a filename
	 * @param filename the filename get the directory from
	 */
	std::string get_directory_from_filename(std::string filename){
		filename=translate_home(filename);
		unsigned int finder=filename.rfind("/");
		if(finder<filename.length()){
			filename=filename.erase(finder,std::string::npos);
		}
		else{return "";} /**return empty if there is no directory*/
		return filename;
	}
	/** use the get_gtk_item function to get an icon theme, or use hicolor if nothing is found*/	
	std::string get_gtk_icon_theme(){return get_gtk_themeitem("icon","hicolor");}
	/** get the gtk theme using the get_gtk_item function, or return Raleigh if nothing is found*/
	std::string get_gtk_widget_theme(){return get_gtk_themeitem("gtk","Raleigh");}
	/** get something from org.gnome.desktop.interface *-theme
	 * @param itemToGet this will be icon OR gtk only
	 * @param defaultTheme the default theme to return
	 */
	std::string get_gtk_item(std::string itemToGet, std::string defaultItem){
		std::string temp=sed_i(itemToGet,"-","_");
		std::string tmpGTK="gtk-"+itemToGet;
		return get_gtk_item(itemToGet,temp,tmpGTK,tmpGTK,defaultItem);
	}
	std::string get_gtk_item(std::string itemToGet,std::string configItem, std::string defaultItem){
		std::string temp=sed_i(itemToGet,"-","_");
		return get_gtk_item(itemToGet,temp,configItem,configItem,defaultItem);
	}
	std::string get_gtk_item(std::string itemToGetgtk3,std::string itemToGetgtk2,std::string gtk3fileopt,std::string gtk2fileopt, std::string defaultItem){
		std::string gtkrc2_result, gtkrc3_result,gtk2;
		std::string GSETTINGS=term_out("which gsettings");
		std::string GCONF2=term_out("which gconftool-2");
		if(GSETTINGS.find("gsettings")<GSETTINGS.length()){
			gtkrc3_result=term_out(GSETTINGS+" get org.gnome.desktop.interface "+itemToGetgtk3);
			gtkrc3_result=remove_cruft(gtkrc3_result,"\'");
			gtkrc3_result=remove_cruft(gtkrc3_result,"\'");
			if(gtkrc3_result.compare("")!=0){return gtkrc3_result;}
		}
		if(itemToGetgtk2.compare("")!=0){
			if(GCONF2.find("gconftool-2")<GCONF2.length()){
				gtk2=term_out(GCONF2+" --get /desktop/gnome/interface/"+itemToGetgtk2);
				if(gtk2.compare("")!=0){return gtk2;}
			}
		}
		const char* home = getenv("HOME");
		if(home==NULL){return defaultItem;}
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
		if(gtk3fileopt.compare("")!=0){
			std::string GTKRC3=XDG_CONFIG_HOME + "/gtk-3.0/settings.ini";
			if(test_file(GTKRC3.c_str())){
				gtkrc3_result=get_line_with_equal(GTKRC3,gtk3fileopt);
				gtkrc3_result=remove_cruft(gtkrc3_result,gtk3fileopt);
				gtkrc3_result=remove_cruft(gtkrc3_result,"\"");
				gtkrc3_result=remove_cruft(gtkrc3_result,"\"");
				if(gtkrc3_result.compare("")!=0){return gtkrc3_result;}
			}
		}
		if(gtk2fileopt.compare("")!=0){
			if(test_file(GTKRC2.c_str())){
				gtkrc2_result=get_line_with_equal(GTKRC2,gtk2fileopt);
				gtkrc2_result=remove_cruft(gtkrc2_result,gtk2fileopt);
				gtkrc2_result=remove_cruft(gtkrc2_result,"\"");
				gtkrc2_result=remove_cruft(gtkrc2_result,"\"");
				if(gtkrc2_result.compare("")!=0){return gtkrc2_result;}
			}
		}
		return defaultItem;
	}
	std::string get_gtk_themeitem(std::string itemToGet, std::string defaultTheme){
		std::string gtkrc2_result, gtkrc3_result,gtk2;
		if((itemToGet.compare("icon")!=0)&&(itemToGet.compare("")!=0)){
			itemToGet="";
		}
		std::string item=itemToGet;
		std::string GSETTINGS=term_out("which gsettings");
		std::string GCONF2=term_out("which gconftool-2");
		if(GSETTINGS.find("gsettings")<GSETTINGS.length()){
			std::string temp=item;
			if(item.compare("")==0)temp="gtk";
			gtkrc3_result=term_out(GSETTINGS+" get org.gnome.desktop.interface "+temp+"-theme");
			//gtkrc3_result=remove_cruft(gtkrc3_result,"gtk-icon-theme-name=");
			gtkrc3_result=remove_cruft(gtkrc3_result,"\'");
			gtkrc3_result=remove_cruft(gtkrc3_result,"\'");
			return gtkrc3_result;
		}
		if(GCONF2.find("gconftool-2")<GCONF2.length()){
			std::string temp="gtk";
			if(item.compare("")!=0)temp=item;
			gtk2=term_out(GCONF2+" --get /desktop/gnome/interface/"+temp+"_theme");
			return gtk2;
		}
		const char* home = getenv("HOME");
		if(home==NULL){return defaultTheme;}
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
			std::string temp;
			if(item.compare("")!=0)temp=item+"-";
			temp="gtk"+temp+"-theme-name=";
			gtkrc3_result=get_line_with_equal(GTKRC3,temp);
			gtkrc3_result=remove_cruft(gtkrc3_result,temp);
			gtkrc3_result=remove_cruft(gtkrc3_result,"\"");
			gtkrc3_result=remove_cruft(gtkrc3_result,"\"");
			return gtkrc3_result;
		}
		if(test_file(GTKRC2.c_str())){
			std::string temp;
			if(item.compare("")!=0)temp=item+"-";
			temp="gtk"+temp+"-theme-name=";
			gtkrc2_result=get_line_with_equal(GTKRC2,temp);
			gtkrc2_result=remove_cruft(gtkrc2_result,"\"");
			gtkrc2_result=remove_cruft(gtkrc2_result,"\"");
			return gtkrc2_result;
		}
		return defaultTheme;
	}
	/** this function gets the owner of the filename provided
	 * @param filename
	 */
	std::string get_file_owner(std::string filename){
		std::string result;
		struct stat info;
		if(stat(filename.c_str(), &info)==0){
			struct passwd *pw = getpwuid(info.st_gid);
			if(pw!=0){result=pw->pw_name;}
		}
		return result;
	}
	/** this function gets the group owner of the filename provided
	 * @param filename
	 */
	std::string get_file_group(std::string filename){
		std::string result;
		struct stat info;
		if(stat(filename.c_str(), &info)==0){
			struct group  *gr = getgrgid(info.st_gid);
			if(gr!=0){result=gr->gr_name;}
		}
		return result;
	}
	/** This function is used for files like *.desktop files to get a value
	 * @param filename the filename to look in
	 * @param line the line to look for
	 */
	std::string get_line_with_equal(std::string filename, std::string line){
		if(line.compare("")==0){return "";}
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
	/** This function is used for files like *.desktop files to get a value
	 * @param header The portion contained in '[ ]' to look for the item AFTER
	 * @param filename the file to look in
	 * @param line the line to find
	 */
	std::string get_line_with_equal_after_header(std::string header,std::string filename, std::string line){
		if(line.compare("")==0){return "";}
		if(header.compare("")==0){return "";}
		if(filename.compare("")==0){return "";}
		if(!test_file(filename)){echo_error("No file sent in\n"+filename+","+line);}
		std::string find_header=header;
		unsigned int open=header.find("[");
		unsigned int close=header.find("]");
		unsigned int header_length=header.length();
		if(open>header_length){find_header="["+find_header;}
		if(close>header_length){find_header=find_header+"]";}
		std::string result=grep_first_after(find_header,line,filename);
		unsigned int found =result.find("=");
		if(found < result.length()){result=result.substr(found+1,std::string::npos);}
		unsigned int space=result.find(" ");
		if(space==0){result=result.substr(space+1,std::string::npos);}
		return result;
	}
	/** This is a specialized internal function to return something akin to "bash -c '"*/
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
	/** This function dereferences a symlink to the actual file*/
	std::string get_symlinkpath(std::string symlink){
		struct stat statinfo;
		if((lstat(symlink.c_str(), &statinfo)>0)){return symlink;}
		if ((!S_ISLNK (statinfo.st_mode) && statinfo.st_nlink > 1)
		||
		(S_ISLNK (statinfo.st_mode))){
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
		}
		else{return symlink;}
		return symlink;
	}
	std::string get_user_name(){
		std::string temp;
		struct passwd *pw;
		uid_t uid;
		uid = geteuid ();
		pw = getpwuid (uid);
		if(pw!=0){temp=pw->pw_name;}
		return temp;
		
	}
    /** Return the FIRST match of the 'args' from a file
     * this is like  line=`grep -m 1 $args $filename`
	 * @param args the string to 'grep'
	 * @param filename the file to 'grep' from
	 */
    std::string grep(std::string args, std::string filename) {
      std::string line;
      int lengthofARGS = args.length();
      std::string subString;
      std::ifstream inputFileStrem (filename.c_str(), std::ifstream::in);
      /** check if the input file stream is open */
      if(inputFileStrem.is_open()){
          while (getline(inputFileStrem,line)){
              subString=line.substr(0,lengthofARGS);
              /** if found return it immediately */
              if(subString.compare(args)==0){return line;}
          }
      }
      return "";
	}
	/** Look for a string in a file AFTER a certain string
	 * @param after_this look for this first
	 * @param grep_this get this string
	 * @param filename the file to look in
	 */
	std::string grep_first_after(std::string after_this, std::string grep_this, std::string filename){
		echo("AFTER THIS="+after_this+"\nLOOK FOR="+grep_this+"\nIN="+filename);
		bool found_after_this=false;
		std::string line;
		int lengthofARGS = grep_this.length();
		std::string subString;
		std::ifstream inputFileStrem (filename.c_str(), std::ifstream::in);
		/** check if the input file stream is open */
		if(inputFileStrem.is_open()){
			while (getline(inputFileStrem,line)){
				subString=line.substr(0,lengthofARGS);
				if(line.find(after_this)<line.length()){
					echo("FOUND:"+after_this);
					found_after_this=true;}
				/** if found return it immediately */
				if(found_after_this){
					if(line.find(grep_this)<line.length()){return line;}
				}
			}
		}
		return "";
	}
	//H
	/** get the enviroment variable $HOME returned with an appended '/'*/
	std::string home_path(){
		const char* homer=getenv("HOME");
		if(homer==NULL){return "";}
		std::string homePath=homer;
		homePath+="/";
		return homePath;
	}
	//F
	/** turn a file into a newline separated string
	 * @param filename the file to read
	 */
	std::string file_to_string(std::string filename){
		if(filename.compare("")==0){return "";}
		/** make sure it is actually a file */
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
	/** find a sub directory in the $XDG_DATA_DIRS paths
	 * @param subdir the sub directory to find
	 */
	std::string find_xdg_data_dir_subdir(std::string subdir){
		/** use the desktop_dirs() function to get a vector of the XDG_DATA_DIRS */
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
	/** find a directory in the XDG_CONFIG_DIRS paths
	 * @param subdir the subdirectory to look for
	 */
	std::string find_xdg_config_dir_subdir(std::string subdir){
		/** use the xdg_conf_dirs() function to get a vector of the XDG_CONFIG_DIRS paths*/
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
	/** This function will escape spaces in filenames for use in terminal commands
	 * @param filepath the filename to fix up
	 */
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
	//L	
	/** look for a NON hidden file in a specific directory
	 * this will return a comma delimited list of choices
	 * @param fileWITHOUTpath a filename without a path
	 * @param dir the directory to recursively check
	 */
	std::string look_for_file_in_subdirs(std::string fileWITHOUTpath,std::string dir){
		if((dir.compare("")==0)||(fileWITHOUTpath.compare("")==0))return "";
		/** if it is not a directory return empty */
		if(!test_dir(dir))return "";
		/** remove the preceding path*/
		unsigned int found=fileWITHOUTpath.rfind('/');
		if(found<fileWITHOUTpath.length()){
			unsigned int len=fileWITHOUTpath.length()-found;
			fileWITHOUTpath=fileWITHOUTpath.erase(0,len);
		}
		std::string ANSWERS;
		DIR *mydir=NULL;
		struct dirent *entryPointer=NULL;
		mydir=opendir(dir.c_str());
		/** open the directory */
		if(mydir!=NULL){
			while ((entryPointer=readdir(mydir))!=NULL){
				/** find out if it is a symlink or regular file that is not hidden*/
				if(((entryPointer->d_type == DT_LNK)||(entryPointer->d_type == DT_REG))&&(entryPointer->d_name[0]!='.')){
					std::string fullpath=entryPointer->d_name;
					if(dir.rfind('/')!=dir.length()-1){dir+="/";}
					fullpath=dir+fullpath;
					unsigned int findIT = fullpath.find(fileWITHOUTpath);
					if(findIT<=fullpath.length()){
						/** add a comma at the end if there isn't one already*/
						if(ANSWERS.rfind(",")!=ANSWERS.length()-1)ANSWERS+=",";
						ANSWERS+=fullpath;
					}
				}
				/** find out if it is a directory that is not hidden*/
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
	/** find the first file in a subdirectory ONLY
	 * @param fileWITHOUTpath A filename without a path behind it (though it will be removed if it exists)
	 * @param dir the directory to look in
	 */
	std::string look_for_first_file_in_subdirs(std::string fileWITHOUTpath,std::string dir){
		//echo("std::string look_for_first_file_in_subdirs(std::string "+fileWITHOUTpath+",std::string "+dir);//+",std::string "+answer+")");
		if((dir.compare("")==0)||(fileWITHOUTpath.compare("")==0)){
			echo_error("std::string look_for_first_file_in_subdirs(std::string fileWITHOUTpath,std::string dir) requires non empty variables to work\nMUST EXIT");
			return "";
		}
		if(!test_dir(dir)){
			echo_error(dir+" is not a directory\nMUST EXIT");
			return "";
		}
		unsigned int found=fileWITHOUTpath.rfind('/');
		if(found<fileWITHOUTpath.length()){
			unsigned int len=fileWITHOUTpath.length()-found;
			fileWITHOUTpath=fileWITHOUTpath.erase(0,len);
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
				/** if it is a symlink or file check it */
				if(((entryPointer->d_type == DT_LNK)||(entryPointer->d_type == DT_REG))&&(entryPointer->d_name[0]!='.')){
					std::string tempFINDER="/"+fileWITHOUTpath;
					//echo("FINDER:"+tempFINDER+"\nfullpath="+fullpath);
					unsigned int findIT = fullpath.find(tempFINDER);
					if(findIT<=fullpath.length()){
						if(entryPointer->d_type == DT_LNK){
							/** if it is a symlink get the actual file */
							std::string temporary=get_symlinkpath(fullpath);
							//echo("SYMLINK="+fullpath+"\nFile="+temporary);
							if(temporary.compare("")!=0){
								closedir(mydir);
								if(temporary.find("/")>temporary.length()){temporary=dir+temporary;}
								//echo("Symlink="+temporary);
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
				/** if it is a directory look inside recursively */
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
			closedir(mydir);
		}
		else{echo_error(dir+" cannot be opened\nMUST EXIT");}
		echo("Final Answer="+finalAnswer);
		return finalAnswer;
	}
	/** look for an icon file in the normal XDG DATA DIRS paths, checking the current gtk icon theme first
	 * @param fileWITHOUTpath the icon filename (does not need an extention)
	 */
	std::string look_for_icon_file(std::string fileWITHOUTpath){
		std::string dir=find_xdg_data_dir_subdir("icons");
		echo("std::string look_for_icon_file(std::string "+fileWITHOUTpath+")");
		std::string gtktheme=get_gtk_icon_theme();
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
			closedir(mydir);
		}
		else{echo_error(dir+" cannot be opened\nMUST EXIT");}
		if(finalAnswer.compare("")!=0)echo("Final Answer="+finalAnswer);
		return finalAnswer;
	}
	//R
	/** remove something from a string
	 * @param StringInput the string to process
	 * @param CruftToRemove the cruft to remove
	 */
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
	/** remove a percentage symbol from the Exec= line in a desktop file
	 * @param line the line to process
	 */
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
	//S
	/** similar to 'sed' for a string
	 * @param input the initial string
	 * @param remove what you want gone
	 * @param replace what should replace it
	 */
	std::string sed_i(std::string input, std::string remove, std::string replace){
		unsigned int xmlfix=0;
		unsigned int oldFind=0;
		unsigned int length=input.length();
		unsigned int removeLength=remove.length();
		std::string modinput=input;
		while(modinput.find(remove,oldFind)<length){
			xmlfix = modinput.find(remove,oldFind);
			oldFind=xmlfix+replace.length();
			std::string tempPRE,tempPOST,temp;
			if(xmlfix<length){
				temp=modinput;
				tempPOST=modinput;
				tempPRE = temp.erase(xmlfix,std::string::npos);
				tempPOST = modinput.erase(0,xmlfix+removeLength);
				modinput = tempPRE + replace + tempPOST;
				length=modinput.length();
			}
		}
		return modinput;
	}
	//T
	/** return terminal output with the ending newline character removed
	 * @param terminal_Command_You_Want_Output_From the command to return output from
	 */
	std::string term_out(std::string terminal_Command_You_Want_Output_From) {
		if(terminal_Command_You_Want_Output_From.compare("")==0){return "";}
		/** set a locale so this works well */
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
	/** Find a file in a vector of directories
	 * @param fileWithNOPATH the file with no path (though if it exists it will be removed
	 * @param directories_to_check the vector of directories to check
	 */
	std::string test_file_in_vector_path(std::string fileWithNOPATH,std::vector<std::string> directories_to_check){
		//echo_error("test_file_in_vector_path... filepath ORIGINAL="+fileWithNOPATH);
		if(fileWithNOPATH.compare("")==0){return "";}
		std::string filePathRemoved=fileWithNOPATH;
		unsigned int found=filePathRemoved.rfind('/');
		/** remove the path */
		if(found<filePathRemoved.length()){
			unsigned int len=filePathRemoved.length()-found;
			filePathRemoved=filePathRemoved.erase(0,len);
			//echo_error("test_file_in_vector_path... filepath removed="+filePathRemoved);
		}
		for( std::vector<std::string>::iterator it = directories_to_check.begin();
		it!=directories_to_check.end();
		++it){
			std::string dirToOpen=*it;
			std::string result=dirToOpen;
			unsigned int finder=dirToOpen.rfind('/');
			if(finder+1==dirToOpen.length()){
				result+=filePathRemoved;
				//echo_error("test_file_in_vector_path... dir to open="+result);
			}
			else{
				result+="/";
				result+=filePathRemoved;
				//echo_error("test_file_in_vector_path... dir to open="+result);
			}
			//echo_error("looking for "+result);
			if(test_file(result)){return result;}
			else{
				std::string tmp=result;
				tmp=get_symlinkpath(tmp);
				//echo_error("symlnik returns:"+tmp);
				if(tmp.compare("")!=0){return test_file_in_vector_path(tmp,directories_to_check);}
			}
		}
		//echo_error("test_file_in_vector_path... found NO files");
		return "";
	}
	/** translate ~/ OR $HOME into full user's path to $HOME
	 * @param pathORfilename any path or filename
	 */
	std::string translate_home(std::string pathORfilename){
		std::string filename=pathORfilename;
		unsigned int tilde=filename.find("~/");
		if(tilde<filename.length()){
			filename=filename.erase(0,tilde+1);
			filename=home_path()+filename;
		}
		unsigned int HOMEVAR=filename.find("$HOME");
		if(HOMEVAR<filename.length()){
			filename=filename.erase(0,HOMEVAR+1);
			filename=home_path()+filename;
		}
		if(filename.compare("")==0)return pathORfilename;
		return filename;
	}
	std::string process_back_dir_in_filename(std::string filename){
		unsigned int finder = filename.find("../");
		std::string pwd=linuxcommon::current_directory();
		std::string tempPWD=pwd;
		std::string tempLoop=filename;
		int counter=3;
		echo_error("Initial process back dir="+tempLoop);
		while(finder<tempLoop.length()){
			tempLoop=tempLoop.substr(finder+counter,std::string::npos);
			unsigned int slash=tempPWD.rfind("/");
			if(slash==tempPWD.length()-1){
				tempPWD=tempPWD.substr(0,slash);
				slash=tempPWD.rfind("/");
			}
			tempPWD=tempPWD.substr(0,slash);
			echo_error("temploop="+tempLoop+"\ntempPWD"+tempPWD);
			tempLoop=tempPWD+tempLoop;
			if(tempLoop.compare("")!=0){filename=tempLoop;}
			finder = tempLoop.find("../");
		}
		if(filename.find("/")>1){filename="/"+filename;}
		echo_error("returning:"+filename);
		return filename;
	}
	//P
	/** This will dereference symlinks as well as translate ~/ and $HOME as well as ../
	 * @param filename the filename to process
	 */
	std::string process_filename(std::string filename){
		echo("Processing="+filename);
		std::string tmp=process_back_dir_in_filename(filename);
		echo(tmp);
		std::string tmp2=get_symlinkpath(tmp);
		if(tmp2.compare("")!=0)tmp=tmp2;
		echo(tmp);
		std:: string tmp3=translate_home(tmp);
		if(tmp3.compare("")!=0)tmp=tmp3;
		echo(tmp);
		return tmp;
	}
	//Q
	/** change characters XML doesn't like into ones it does
	 * @param input the string to modify
	 */
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
	//X
	#ifdef LINUX_COMMON_HAS_X
	/** get the HTML color from an X11 name
	 * @param colorName the name like MistyRose
	 */
	std::string x_color_from_name(const char *colorName){
	/** Paul Sladen, 2014-08-13, Public Domain
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
	///VECTOR FUNCTIONS/////////////////////////////////////////////////
	/** get a vector list of all possible current system groups*/
	std::vector <std::string> all_groups(){
		std::vector <std::string> GROUPvEC;
		struct group *groupsPtr = getgrent();
		if(groupsPtr != NULL){
			for(groupsPtr = getgrent();groupsPtr!=NULL;groupsPtr = getgrent()){
				GROUPvEC.push_back(groupsPtr->gr_name);
			}
		}
		else{echo_error("No groups found on system!");}
		setgrent();
		endgrent();
		return GROUPvEC;
	}
	/** get a vector list of all $USER groups */
	std::vector <std::string> get_current_user_groups(){
		std::vector <std::string> USERgroups;
		std::string tmp=get_user_name();
		if(tmp.compare("")!=0)return get_user_groups(tmp);
			const char* user=getenv("USER");
		if(user==NULL){
			echo_error("FAILED getting user");
			return USERgroups;
		}
		return get_user_groups(user);
	}
	/** Get all actual users (UID > 1000) excluding nobody*/
	std::vector <std::string> all_users(){
		struct passwd *pw = getpwent();
		std::vector <std::string> ALLusers;
		if(pw != NULL){
			for(pw = getpwent();pw!=NULL;pw = getpwent()){
				std::string TMP=pw->pw_name;
				std::string shell=pw->pw_shell;
				if( (shell.compare("/usr/sbin/nologin")!=0)&&(shell.compare("/bin/false")!=0) ){
					if(TMP.compare("sync")!=0){
						ALLusers.push_back(TMP);
					}
				}
			}
		}
		setpwent();
		endpwent();
		return ALLusers;
	}
	/** Get all the users including all processes*/
	std::vector <std::string> all_users_including_processes(){
		struct passwd *pw = getpwent();
		std::vector <std::string> ALLusers;
		if(pw != NULL){
			for(pw = getpwent();pw!=NULL;pw = getpwent()){
				std::string TMP=pw->pw_name;
				ALLusers.push_back(TMP);
			}
		}
		setpwent();
		endpwent();
		return ALLusers;
	}
	/** get a vector list of all USER's groups
	 * @param USER the user name to get the groups of
	 */
	std::vector <std::string> get_user_groups(std::string USER){
		std::vector <std::string> USERgroups;
	//echo_error("Getting groups for:"+USER)l;
		int ngroups=NGROUPS_MAX;
		struct passwd *pw;
		struct group *gr;
		gid_t groups[NGROUPS_MAX];
		pw = getpwnam(USER.c_str());
		if(getgrouplist(USER.c_str(),pw->pw_gid,groups, &ngroups) == -1){
			echo_error("FAILED getting groups for:"+USER);
			return USERgroups;
		}
		for (int j = 0; j < ngroups; j++) {
			gr = getgrgid(groups[j]);
			if (gr != NULL)USERgroups.push_back(gr->gr_name);
		}
		return USERgroups;
	}
	/** turn a comma delimited string into vector, and join the current items to the vector sent in
	 * @param LINE the comma delimited line
	 * @param Vector the vector to append to (can be empty)
	 */
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
	/** make a string vector from a string with a delimiter string
	 * @param string_to_become_vector The string to become the vector
	 * @param delimiter the delimiter
	 */
	std::vector<std::string> delimiter_vector_from_string(std::string string_to_become_vector,std::string delimiter){
		std::vector<std::string> Vector;
		std::string original,preComma,postComma;
		original=string_to_become_vector;
		unsigned int found,finder;
		finder=original.length();
		for(found=original.find(delimiter);found<finder;found=original.find(delimiter)){
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
	/** return a vector of the XDG_DATA_DIRS and XDG_DATA_HOME environment variables (or their equivalents) */
	std::vector<std::string> desktop_paths(){
		std::vector<std::string> thisPath;
		std::vector<std::string>::iterator it;
		std::string thisXDG;
		/** check the environment variables, or give them decent values*/
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
				if(thisXDG.compare("")!=0)thisXDG += ":";
				thisXDG += datahome;
				thisXDG += "/.local/share/";
			}
		}
		else{
			if(thisXDG.compare("")!=0)thisXDG+= ":";
			thisXDG += datahome;
		}
		unsigned int numberOfPaths;
		std::string tempXDG = thisXDG;
		unsigned int tryer;
		/** count the ':' for the vector creation */
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
	/** turn a file into a vector of strings
	 * @param filename the file to read
	 */
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
	/** return a vector of XDG_DATA_DIRS with a sane value if no environment variable is set*/
	std::vector<std::string> desktop_dirs(){
		std::vector<std::string> desktop = split_paths("XDG_DATA_DIRS","/usr/local/share/:/usr/share/");
		#if 0
		const char *datahome = getenv("HOME");
		std::string thisXDG;
		if (datahome != NULL){
				thisXDG = datahome;
				thisXDG += "/.local/share/";
		}
		#endif
		//std::vector<std::string> user = split_paths("XDG_DATA_HOME",thisXDG.c_str());
		return desktop;
	}
	/** Get a string vector of files similar to one you are searching for
	 * @param DIRECTORY the place to look
	 * @param file the filename to find
	 */
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
	/** return a vector of lines 'grep'd from a file
	 * @param args the thing to look for
	 * @param filename the file to look in
	 */
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
	/** join two string vectors
	 * @param vectorA the first vector
	 * @param vectorB the second vector
	 */
	std::vector<std::string> join_string_vectors(std::vector<std::string> vectorA,std::vector<std::string> vectorB){
		std::vector<std::string> bothVectors;
		bothVectors.reserve(vectorA.size()+vectorB.size());
		bothVectors.insert(bothVectors.end(),vectorA.begin(),vectorA.end());
		bothVectors.insert(bothVectors.end(),vectorB.begin(),vectorB.end());
		return bothVectors;
	}
	/** sort a vector for unique items only
	 * @param vector_to_sort the vector to sort
	 */
	std::vector<std::string> sort_array(std::vector<std::string> vector_to_sort){
		std::vector<std::string>::iterator it;
		std::sort (vector_to_sort.begin(), vector_to_sort.end());
		it = std::unique (vector_to_sort.begin(), vector_to_sort.end());
		vector_to_sort.resize( std::distance(vector_to_sort.begin(),it) );
		return vector_to_sort;
	}
	/** turn a ':' separated environment variable into a vector of strings
	 * @param envVar the environment variable to check and split into a vector
	 * @param incasenothingexists your backup plan if the variable proves to be empty
	 */
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
	/** return a vector of XDG_CONFIG_DIRS*/
	std::vector<std::string> xdg_conf_dirs(){
		std::vector<std::string> desktop = split_paths("XDG_CONFIG_DIRS","/etc/xdg/xdg-torios:/etc/xdg");
		#if 0
		const char *datahome = getenv("HOME");
		std::string thisXDG;
		if (datahome != NULL){
				thisXDG = datahome;
				thisXDG += "/.config/";
		}
		std::vector<std::string> user = split_paths("XDG_CONFIG_HOME",thisXDG.c_str());
		//std::vector<std::string> dirs = join_string_vectors(user,desktop);
		#endif
		return desktop;
	}
	///BOOLEAN FUNCTIONS////////////////////////////////////////////////
	/** append a string to a file
	 * @param STRING the string to append
	 * @param FILENAME the file to append it to
	 * this returns save_string_to_file()
	 */
	bool append_string_to_file(std::string STRING, std::string FILENAME){
		if(!test_file(FILENAME))return false;
		if(!file_is_writable(FILENAME))return false;
		std::string tmp=file_to_string(FILENAME);
		tmp+="\n";
		tmp+=STRING;
		return save_string_to_file(tmp,FILENAME);
	}
	/** see if a file has a certain extention (like .svg)
	 * @param filename the filename
	 * @param extention the extention to look for
	 */
	bool has_file_extention_at_end(std::string filename,std::string extention){
		std::string extention_check;
		std::transform(filename.begin(), filename.end(), filename.begin(), ::tolower);
		std::transform(extention.begin(), extention.end(), extention.begin(), ::tolower);
		unsigned int period = extention.find(".");
		//add period to extention
		if(period != 0)
			extention="."+extention;
		unsigned int found=filename.find(extention);
		unsigned int ext_len=extention.length();
		unsigned int file_len=filename.length();
		if(found<file_len){
			if(found==(file_len-ext_len)){return true;}
		}
		return false;
	}
	bool file_is_readable(std::string filename){
		if(!test_file(filename)){return false;}
		struct stat info;
		std::string file_owner,file_group;
		if(stat(filename.c_str(), &info)==0){
			struct passwd *pw = getpwuid(info.st_uid);
			struct group  *gr = getgrgid(info.st_gid);
			if(pw!=0){file_owner=pw->pw_name;}
			if(gr!=0){file_group=gr->gr_name;}
			if(info.st_mode &  S_IROTH)return true;
			std::string user=get_user_name();
			if(file_owner.compare(user)==0){
				if(info.st_mode &  S_IRUSR)return true;
			}
			//TODO get group of user and check group permissions
		}
		return false;
	}
	bool file_is_writable(std::string filename){
		if(!test_file(filename)){
			filename=get_directory_from_filename(filename);
		}
		struct stat info;
		std::string file_owner,file_group;
		if(stat(filename.c_str(), &info)==0){
			struct passwd *pw = getpwuid(info.st_uid);
			struct group  *gr = getgrgid(info.st_gid);
			if(pw!=0){file_owner=pw->pw_name;}
			if(gr!=0){file_group=gr->gr_name;}
			if(info.st_mode &  S_IWOTH)return true;
			std::string user=get_user_name();
			if(file_owner.compare(user)==0){
				if(info.st_mode &  S_IWUSR)return true;
			}
			//TODO get group of user and check group permissions
		}
		return false;
	}
	/** see if a string exists in a vector
	 * @param vector_to_check the vector to check
	 * @param item_to_find the item to find
	 */
	bool look_for_string_in_vector(std::vector<std::string> vector_to_check,std::string item_to_find){
		for( std::vector<std::string>::iterator it = vector_to_check.begin();
		it!=vector_to_check.end();
		++it){
			std::string tmp=*it;
			if(tmp.compare(item_to_find)==0){return true;}
		}
		return false;
	}
	/** works like the 'pkill' command
	 * @param programname the program name to look for
	 */
	bool pkill(std::string programname){
		/** get the pid (process ID)*/
		int pid=getProcIdByName(programname);
		if(pid<=0){
			echo_error("Invalid process ID for "+programname);
			return false;
		}
		int result=kill(pid,SIGKILL);
		if(result==0){return true;}
		else{
			/** check the errors and display them to stdout */
			switch (errno){
				case EINVAL:
					/**This should not happen normally, since we are sending SIGKILL hard-coded*/
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
	/** check to see if a program is already running
	 * @param program_line the program to check for
	 */
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
	/** save a string to a file
	 * @param MSG the message to save
	 * @param filename the filename to save it as
	 */
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
	/** change a gtk setting for org.gnome.desktop.interface *-theme
	 * @param item (icon or gtk)
	 * @param value the new value
	 */
	bool switch_gtk_setting(std::string item, std::string value){
		std::string GTK2=sed_i(item,"-","_");
		std::string tmpGTKconf="gtk-"+item;
		std::string gtkrc2_result, gtkrc3_result,gtk2;
		if(value.compare("")==0){return false;}
		if((item.compare("")==0)){return false;}
		int retval=0;
		std::string GSETTINGS=term_out("which gsettings");
		std::string GCONF2=term_out("which gconftool-2");
		if(GSETTINGS.find("gsettings")<GSETTINGS.length()){
			retval=run_a_program(GSETTINGS+" set org.gnome.desktop.interface "+item+ " \"" +value+"\"");
			if(retval!=0){echo_error("Error setting the GSETTINGS theme");}
		}
		if(GCONF2.find("gconftool-2")<GCONF2.length()){
			retval=run_a_program(GCONF2+" --set --type string /desktop/gnome/interface/"+GTK2+" \""+value+"\"");
			if(retval!=0){echo_error("Error setting the GCONF2 theme");}
		}
		const char* home = getenv("HOME");
		bool fileFix=true;
		if(home==NULL){fileFix=false;}
		else{
			std::string HOME=home;
		//CHECK/SET GTKRC FILES
			std::string GTKRC2=HOME + "/.gtkrc-2.0";
			const char* xdg_config_home=getenv("XDG_CONFIG_HOME");
			std::string XDG_CONFIG_HOME;
			if (xdg_config_home!=NULL){XDG_CONFIG_HOME=xdg_config_home;}
			else{XDG_CONFIG_HOME=HOME +"/.config";}
			std::string GTKRC3=XDG_CONFIG_HOME + "/gtk-3.0/settings.ini";
			if(test_file(GTKRC3.c_str())){
				gtkrc3_result=get_line_with_equal(GTKRC3,tmpGTKconf);
				gtkrc3_result=remove_cruft(gtkrc3_result,tmpGTKconf);
				gtkrc3_result=remove_cruft(gtkrc3_result,"\"");
				gtkrc3_result=remove_cruft(gtkrc3_result,"\"");
				if(value.compare(gtkrc3_result)!=0){
					fileFix=false;
					std::string command="sed -i \"s#"+gtkrc3_result+"#"+value+"#\" "+GTKRC3;
					//echo_error(command);
					retval=run_a_program(command);
					if(retval==0)fileFix=true;
					//TODO don't use sed... actually do it :P
				}
			}
			if(test_file(GTKRC2.c_str())){
				gtkrc2_result=get_line_with_equal(GTKRC2,tmpGTKconf);
				gtkrc2_result=remove_cruft(gtkrc2_result,tmpGTKconf);
				gtkrc2_result=remove_cruft(gtkrc2_result,"\"");
				gtkrc2_result=remove_cruft(gtkrc2_result,"\"");
				if(value.compare(gtkrc2_result)!=0){
				//TODO
					fileFix=false;
					///THIS
					std::string command="sed -i \"s#"+gtkrc2_result+"#"+value+"#\" "+GTKRC2;
					//echo_error(command);
					retval=run_a_program(command);
					if(retval==0)fileFix=true;
				}
			}
		}
		if((retval!=0)&&(!fileFix))return false;
		return true;
	}
	bool switch_gtk_item(std::string item, std::string value){
		std::string gtkrc2_result, gtkrc3_result,gtk2;
		if(value.compare("")==0){return false;}
		if((item.compare("icon")!=0)&&(item.compare("")!=0)){
			item="";
		}
		int retval=0;
		std::string GSETTINGS=term_out("which gsettings");
		std::string GCONF2=term_out("which gconftool-2");
		if(GSETTINGS.find("gsettings")<GSETTINGS.length()){
			std::string temp=item;
			if(temp.compare("")==0)temp="gtk";
			retval=run_a_program(GSETTINGS+" set org.gnome.desktop.interface "+temp+"-theme "+ value);
			if(retval!=0){echo_error("Error setting the theme");}
		}
		if(GCONF2.find("gconftool-2")<GCONF2.length()){
			std::string temp="gtk";
			if(item.compare("")!=0)temp=item;
			retval=run_a_program(GCONF2+" --set --type string /desktop/gnome/interface/"+temp+"_theme "+ value);
			if(retval!=0){echo_error("Error setting the theme");}
		}
		const char* home = getenv("HOME");
		bool fileFix=true;
		if(home==NULL){fileFix=false;}
		else{
			std::string HOME=home;
		//CHECK/SET GTKRC FILES
			std::string GTKRC2=HOME + "/.gtkrc-2.0";
			const char* xdg_config_home=getenv("XDG_CONFIG_HOME");
			std::string XDG_CONFIG_HOME;
			if (xdg_config_home!=NULL){XDG_CONFIG_HOME=xdg_config_home;}
			else{XDG_CONFIG_HOME=HOME +"/.config";}
			std::string GTKRC3=XDG_CONFIG_HOME + "/gtk-3.0/settings.ini";
			if(test_file(GTKRC3.c_str())){
				std::string temp;
				if(item.compare("")!=0)temp=item+"-";
				temp="gtk"+temp+"-theme-name=";
				gtkrc3_result=get_line_with_equal(GTKRC3,temp);
				gtkrc3_result=remove_cruft(gtkrc3_result,temp);
				gtkrc3_result=remove_cruft(gtkrc3_result,"\"");
				gtkrc3_result=remove_cruft(gtkrc3_result,"\"");
				if(value.compare(gtkrc3_result)!=0){
					fileFix=false;
				std::string command="sed -i \"s#"+gtkrc3_result+"#"+value+"#\" "+GTKRC3;
				retval=run_a_program(command);
				if(retval==0)fileFix=true;
				//TODO don't use sed... actually do it :P
				}
			}
			if(test_file(GTKRC2.c_str())){
				std::string temp;
				if(item.compare("")!=0)temp=item+"-";
				temp="gtk"+temp+"-theme-name=";
				gtkrc2_result=get_line_with_equal(GTKRC2,temp);
				gtkrc2_result=remove_cruft(gtkrc2_result,"\"");
				gtkrc2_result=remove_cruft(gtkrc2_result,"\"");
				if(value.compare(gtkrc2_result)!=0){
				//TODO
					fileFix=false;
				std::string command="sed -i \"s#"+gtkrc2_result+"#"+value+"#\" "+GTKRC2;
				retval=run_a_program(command);
				if(retval==0)fileFix=true;
				}
			}
		}
		if((retval!=0)&&(!fileFix))return false;
		return true;
	}
	/** switch a value out of a file in a Blank=thing setting.
	 * @param item  The ITEM=
	 * @param value what goes after the '=' (note... this can be blank and still succeed)
	 * @param filename the file to look in and overwrite
	 */
	bool switch_equal_line_item(std::string item, std::string value,std::string filename){
		if((item.compare("")==0) || (!test_file(filename)) || (!file_is_readable(filename)) || (!file_is_writable(filename)) ){return false;}
		std::vector<std::string> fVec = file_to_vector(filename);
		std::ifstream inputFileStream(filename.c_str(), std::ifstream::in);
		std::string OUT,thisLine;
		if(inputFileStream.is_open()){
			while (getline(inputFileStream,thisLine)){
				std::string LINE=thisLine;
				if(thisLine.find(item)<thisLine.length()){
					unsigned int found =thisLine.find("=");
					if(found < thisLine.length()){
						LINE=item+"="+value;
					}
				}
				if(OUT.compare("")!=0) OUT=OUT+"\n"+LINE;
				else OUT=LINE;
			}
		}
		if(OUT.compare("")!=0)return save_string_to_file(OUT,filename);
		return false;
	}
	/** test to see if a file exists
	 * @param fileWithFullPATH the full path and filename to test
	 */
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
			closedir(mydir);
		}
		else{echo_error("could not open directory to search for "+fileWithFullPATH);}
		return false;
	}
	/** check to see if an executable file exists
	 * @param execToTest the executable you want to check
	 */
	bool test_exec(std::string execToTest){
		if(execToTest.compare("")==0){return false;}
		/** the list of directories it might check*/
		/** /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games*/
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
	//DOUBLE FUNCTION///////////////////////////////////////////////////
	/** convert string number to a double
	 * @param num the string to convert
	 */
	double convert_string_to_double(std::string num){
		if(num.compare("")==0){return 0.0;}
		std::stringstream out;
		out << num;
		double integer;
		out >> integer;
		return integer;
	}
	//UNSIGNED INTEGER FUNCTIONS////////////////////////////////////////
	/** convert aa string number to an unsigned integer
	 * @param num the number to convert
	 */
	unsigned int convert_string_to_number(const char* num){
		unsigned int NUM=0;
		try{NUM=std::stoul(num);}
		catch(std::invalid_argument e){return 0;}
		catch(std::out_of_range e){return 0;}
		return NUM;
	}
	/** count the items in the PATH environment variable*/
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
	/** IF X11 is found, these functions will work */
	#ifdef LINUX_COMMON_HAS_X
	/** get the integer FLTK uses for colors from a string
	 * @param color the color to r=convert
	 */
	unsigned int get_fl_color(std::string color){
		unsigned int c=0;
		return get_fl_color(color,c);
	}
	/** get 2 integer colors from a string
	 * @param color the color string to check
	 * @param &color2 the dereferenced integer to hold the second color
	 */
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
			if(color.compare("")==0){return 0;}
			std::string value= x_color_from_name(input);
			return get_fl_color(value, color2);
		}
	}
	#endif
	unsigned int userUID(std::string user){
		unsigned int ERROR=99999;
		if(user.compare("")==0)return ERROR;
		struct passwd *pw;
		if(getpwnam(user.c_str())==NULL)return ERROR;
		unsigned int UID=pw->pw_uid;
		setpwent();
		endpwent();
		return UID;
	}
	unsigned int userGID(std::string user){
		unsigned int ERROR=99999;
		if(user.compare("")==0)return ERROR;
		struct passwd *pw;
		if(getpwnam(user.c_str())==NULL)return ERROR;
		unsigned int UID=pw->pw_gid;
		setpwent();
		endpwent();
		return UID;
	}
	unsigned int highest_user_UID(){
		std::vector <std::string> ALLusers = all_users();
		unsigned int TOTAL=0;
		for( std::vector<std::string>::iterator itr = ALLusers.begin();
			itr!=ALLusers.end();
			++itr){
			std::string tmpUser=*itr;
			unsigned int tmp=userUID(tmpUser);
			if(tmp>TOTAL)TOTAL=tmp;
		}
		return TOTAL;
	}
	//INTEGER FUNCTIONS/////////////////////////////////////////////////
	int convert_string_to_int(std::string num){
		unsigned int NUM=0;
		try{NUM=std::stoi(num);}
		catch(std::invalid_argument e){return 0;}
		catch(std::out_of_range e){return 0;}
		return NUM;
	}
	/** get a process ID from a name like 'pgrep'
	 * @param  procName the process name to look for
	 */
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
	/** recursivley make directories similar to 'mkdir -p' command
	 * @param dirToMake the directory to create
	 */
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
	/** run a program in a subshell
	 * @param program the program to run
	 */
	int run_a_program(std::string program){
		std::string shell=get_shell_for_C();
		if(shell.compare("")!=0){
			shell+=program;
			shell+="'";
		}
		else{shell=program;}
		return system(shell.c_str());
	}
	/** run a program and disown it
	 * @param program the program to run
	 */
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
	///VOID FUNCTIONS///////////////////////////////////////////////////
	/** use std::cout to pring a message
	 * if COMMON_XMLOUT is defined it will wrap in <!-- -->
	 * if QUIET_ERROR is defined it will not output
	 * @param msg The string to print
	 */
	void echo(std::string msg){
		#ifdef COMMON_XMLOUT
			std::cout<<"<!--"<<msg<<"-->"<<std::endl;
		#elif QUIET_ERROR
			/**do nothing if QUIET_ERROR is defined*/
		#else
			std::cout<<msg<<std::endl;
		#endif
	}
	/** use std::cerr to pring a message
	 * if COMMON_XMLOUT is defined it will wrap in <!-- -->
	 * if QUIET_ERROR is defined it will not output
	 * @param msg The string to print
	 */
	void echo_error(std::string msg){
		#ifdef COMMON_XMLOUT
			std::cerr<<"<!--"<<msg<<"-->"<<std::endl;
		#elif QUIET_ERROR
			/**do nothing if QUIET_ERROR is defined*/
		#else
			std::cerr<<msg<<std::endl;
		#endif
	}
	/** print a file to stdout using std::cout
	 * @param fileNameWithFullPath the file name with the full path
	 */
	void print_file_to_stdout(std::string fileNameWithFullPath){
		/** if nothing is sent in return*/
		if(fileNameWithFullPath.compare("")==0){return;}
		std::string line;
		std::ifstream inputFileStrem (fileNameWithFullPath.c_str(), std::ifstream::in);
		if(inputFileStrem.is_open()){
          while (getline(inputFileStrem,line)){
			  std::cout<<line<<std::endl;
          }
      }
	}
LINUX_COMMON__NS_END


#endif
