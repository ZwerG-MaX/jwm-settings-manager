/*                 Joe's Window Manager Configuration
 *
 * This program configures JWM using pugixml and FLTK
 *
 *         Copyright (C) 2016  Israel <israeldahl@gmail.com>
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
 *
 *
 * You may redistribute this, but you must keep this comment in place
 * Jesus is my Lord, and if you don't like it feel free to ignore it.
 */

#include "../include/icons.hpp"
//BOOL//////////////////////////////////////////////////////////////////
bool JSM_Icon::edit_value(Fl_Browser* iconsBrowser,Fl_Input* dir_edit_input){
	const char* line=iconsBrowser->text(iconsBrowser->value());
	if(line==NULL){return false;}
	dir_edit_input->value(line);
	dir_edit_input->redraw();
	return true;
}
bool JSM_Icon::save_edit_value(Fl_Browser* iconsBrowser,Fl_Input* dir_edit_input){
	const char* line=dir_edit_input->value();
	if(line==NULL){return false;}
	
	return true;
}
bool JSM_Icon::switchTheme(Fl_Browser* o,int size){
	debug_out("bool switchTheme(Fl_Browser* o,int size)");
	const char* theme_selection=o->text(o->value());
	if(theme_selection==NULL){
		debug_out("Browser selection is NULL");
		return false;
	}
	std::string SELECTION=theme_selection;
	std::vector<std::string> THESEthemesVector=icon_themefiles_vector();
	std::string themefileResult;
	for( std::vector<std::string>::iterator it = THESEthemesVector.begin();
		it!=THESEthemesVector.end();
		++it){
		std::string themefile=*it;
		debug_out("File="+themefile);
		if(themefile.compare("")!=0){
			std::string themeNAME=linuxcommon::get_line_with_equal(themefile,"Name=");
			debug_out("Name="+themeNAME);
			if(SELECTION.compare(themeNAME)==0){
				debug_out("Found the correct one:"+themeNAME+" as "+themefile);
				themefileResult=themefile;
			}
		}
	}
	if(themefileResult.compare("")==0){return false;}
	std::string SelectedTheme=themefileResult;
	std::string DIRECTORY=linuxcommon::find_xdg_data_dir_subdir("icons");
	if(DIRECTORY.compare("")==0){
		errorOUT("Icon directory NOT found");
		return false;
	}
	//std::string themefile=DIRECTORY+SelectedTheme+"/index.theme";
	//linuxcommon::look_for_file_in_subdirs(DIRECTORY+SelectedTheme,"index.theme");
	debug_out("File="+SelectedTheme);
	if(SelectedTheme.compare("")!=0){
		std::string themeStyle=linuxcommon::get_line_with_equal(SelectedTheme,"Name=");
		if(SelectedTheme.compare("")!=0){
			debug_out("Name="+SelectedTheme);
			if((SelectedTheme.compare(SelectedTheme)==0)){
				debug_out("Found the Selected one:"+SelectedTheme);
				return populateIncludes(SelectedTheme,size);
			}
		}
		else{debug_out("Couldn't find the Name in the themefile:"+SelectedTheme);}
	}
	return false;
}
bool JSM_Icon::populateIncludes(std::string themefile,int size_to_use){
	debug_out("bool populateIncludes(std::string "+themefile+",int size_to_use)");
	bool non_empty=false;
	std::string icPATH="IconPath";
	std::vector<std::string> IconFileVector=list_icon_dirs_in_themefile( themefile, size_to_use);
	if(!deleteElements(icPATH)){
		debug_out("Could not delete IconPath items");
		return false;
	}
	for( std::vector<std::string>::iterator it = IconFileVector.begin();
	it!=IconFileVector.end();
	++it){
		std::string item=*it;
		if(item.compare("")!=0){
			non_empty=true;
			if(!addElementWithTextAfter(icPATH,item)) debug_out("Couldn't add Icon path="+item);
		}
	}
	return non_empty;
}
//VECTOR////////////////////////////////////////////////////////////////
std::vector<std::string> JSM_Icon::icon_themefiles_vector(){
	debug_out("std::vector<std::string> icon_themefiles_vector()");
	std::string DIRECTORY=linuxcommon::find_xdg_data_dir_subdir("icons");
	std::vector<std::string> thisISmyVector;
	if(DIRECTORY.compare("")==0){errorOUT("Icon directory NOT found");}
	else{thisISmyVector=linuxcommon::get_file_vector(DIRECTORY,"index.theme");}
	if(thisISmyVector.empty()){errorOUT("Didn't find and Icon themes");}
	return thisISmyVector;
}
std::vector<std::string> JSM_Icon::list_icon_dirs_in_themefile(std::string themefile,int size_to_use){
	debug_out("std::vector<std::string> list_icon_dirs_in_themefile(std::string "+themefile+",int size_to_use)");
	std::vector<std::string> ListOfIconDirs;
	std::string SIZE_TO_USE=linuxcommon::convert_num_to_string(size_to_use);
	std::string INTERNAL_LINE;
	std::string subString;
	std::string basedir=linuxcommon::get_directory_from_filename(themefile);
	std::string THEME_DIR=basedir;
	std::ifstream inputFileStrem (themefile.c_str(), std::ifstream::in);
	std::string INHERITS;
	if(inputFileStrem.is_open()){
		std::string DIRS,MIN,MAX,SIZE,TYPE,THRESH,CONTEXT,HEADER;
		int size=0;
		int tresh=0;
		int max=0;
		int min=0;
		std::string LINE=getEQUALvalue(INTERNAL_LINE);
		while (getline(inputFileStrem,INTERNAL_LINE)){
			if(INTERNAL_LINE.find('[')<INTERNAL_LINE.length()){
				HEADER=INTERNAL_LINE;
				HEADER=linuxcommon::remove_cruft(HEADER,"[");
				HEADER=linuxcommon::remove_cruft(HEADER,"]");
				HEADER="/"+HEADER;
			}
			else if(INTERNAL_LINE.find("Inherits=")<INTERNAL_LINE.length()){
				INHERITS=LINE;
			}
			else if(INTERNAL_LINE.find("Directories=")<INTERNAL_LINE.length()){
				DIRS=LINE;
			}
			else if(INTERNAL_LINE.find("MinSize=")<INTERNAL_LINE.length()){
				MIN=LINE;
				min=linuxcommon::convert_string_to_number(MIN.c_str());
			}
			else if(INTERNAL_LINE.find("MaxSize=")<INTERNAL_LINE.length()){
				MAX=LINE;
				max=linuxcommon::convert_string_to_number(MAX.c_str());
			}
			else if(INTERNAL_LINE.find("Size=")<INTERNAL_LINE.length()){
				SIZE=LINE;
				size=linuxcommon::convert_string_to_number(SIZE.c_str());
			}
			else if(INTERNAL_LINE.find("Type=")<INTERNAL_LINE.length()){
				TYPE=LINE;
			}
			else if(INTERNAL_LINE.find("Threshold=")<INTERNAL_LINE.length()){
				THRESH=LINE;
				tresh=linuxcommon::convert_string_to_number(THRESH.c_str());
			}
			else if(INTERNAL_LINE.find("Context=")<INTERNAL_LINE.length()){
				CONTEXT=LINE;
			}
			if((CONTEXT.compare("Animations")!=0)
			&&(CONTEXT.compare("Stock")!=0)
			&&(CONTEXT.compare("Status")!=0)
			&&(CONTEXT.compare("Emblems")!=0)
			&&(CONTEXT.compare("Emotes")!=0)
			&&(CONTEXT.compare("International")!=0) ){
				if((SIZE.compare(SIZE_TO_USE))||
				((tresh-size)==(size_to_use))||
				((tresh+size)==(size_to_use)) ){
					if(HEADER.find(SIZE)<HEADER.length()){
						std::string testDIR=THEME_DIR+HEADER;
						debug_out("Sized: Checking if "+testDIR+" is a directory");
						if(linuxcommon::test_dir(testDIR)){
							//TODO check Vector for entry prior to adding it
							ListOfIconDirs.push_back(testDIR);
						}
					}
				}
				else{
					if(TYPE.compare("Scalable")==0){
						if((max>=size)&&(min<=size)){
							std::string testDIR=THEME_DIR+HEADER;
							debug_out("Scalable: Checking if "+testDIR+" is a directory");
							if(linuxcommon::test_dir(testDIR)){
								//TODO check Vector for entry prior to adding it
								ListOfIconDirs.push_back(testDIR);
							}
						}
					}
				}
			}
		}
	}
	debug_out("Done parsing themefile "+themefile);
	if(INHERITS.compare("")!=0){
		std::string inheritThemeFileDIR=linuxcommon::find_xdg_data_dir_subdir("icons");
		std::string inheritThemeFile=inheritThemeFileDIR;
		if(INHERITS.find(",")<INHERITS.length()){
			std::vector<std::string> InheritFileVector=linuxcommon::comma_vector(INHERITS,InheritFileVector);
			std::vector<std::string> IconFileVector=list_icon_dirs_in_themefile( themefile, size_to_use);
			for( std::vector<std::string>::iterator it = InheritFileVector.begin();
			it!=InheritFileVector.end();
			++it){
				std::string thisTheme=*it;
				inheritThemeFile+=thisTheme;
				std::string temp=linuxcommon::look_for_file_in_subdirs("index.theme",inheritThemeFile);
				if(temp.compare("")==0){
					debug_out("Couldn't find theme file in:"+inheritThemeFile);
				}
				else{
					std::vector<std::string> ListOfInheritIconDirs=list_icon_dirs_in_themefile(temp,size_to_use);
					if(!ListOfInheritIconDirs.empty()){
						ListOfIconDirs=linuxcommon::join_string_vectors(ListOfInheritIconDirs,ListOfIconDirs);
					}
				}
			}
		}
		else{
			inheritThemeFile+=INHERITS;
			std::string temp=linuxcommon::look_for_file_in_subdirs("index.theme",inheritThemeFile);
			if(temp.compare("")==0){debug_out("Couldn't find theme file in:"+inheritThemeFile);}
			else{
				std::vector<std::string> ListOfInheritIconDirs=list_icon_dirs_in_themefile(temp,size_to_use);
				if(!ListOfInheritIconDirs.empty()){
					ListOfIconDirs=linuxcommon::join_string_vectors(ListOfInheritIconDirs,ListOfIconDirs);
				}
			}
		}
	}
	return ListOfIconDirs;
}
//VOID//////////////////////////////////////////////////////////////////
void JSM_Icon::populateIconThemes(Fl_Browser* o){
	debug_out("void populateIconThemes(Fl_Browser* o)");
	o->clear();
	int chosen=1;
	std::vector<std::string> themesVector=icon_themefiles_vector();
	std::string gtk_theme=linuxcommon::get_gtk_icon_theme();
	if(themesVector.empty()){
		errorOUT("Didn't find any Icon themes");
		return;
	}
	for( std::vector<std::string>::iterator it = themesVector.begin();
		it!=themesVector.end();
		++it){
		std::string themefile=*it;
		debug_out("File="+themefile);
		if(themefile.compare("")!=0){
			std::string themeStyle=linuxcommon::get_line_with_equal(themefile,"Name=");
			if(themeStyle.compare("")!=0){o->add(themeStyle.c_str());
				debug_out("Name="+themeStyle);
				if((themefile.find(gtk_theme)<themefile.length())||(gtk_theme.compare(themeStyle)==0)){
					debug_out("Found the current one:"+themeStyle);
					chosen=o->size();
					o->select(chosen);
				}
			}
		}
	}
	o->redraw();
	themesVector.clear();
}
