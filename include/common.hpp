#ifndef HEADER_LINUX_COMMON_HPP
#define HEADER_LINUX_COMMON_HPP
/**
 * common linux functions - version 0.1.0
 * --------------------------------------------------------
 * Copyright (C) 2016, by Israel Dahl (israeldahl@gmail.com)
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
#include <sys/stat.h>
#include <langinfo.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <errno.h>
#include <locale.h>
#include <unistd.h>
#include <signal.h>
#ifdef LINUX_COMMON_HAS_X
#include <X11/Xlib.h>
//#include <X11/xpm.h>
#endif

#ifndef LINUX_COMMON_VERSION
// Define version macro; evaluates to major * 100 + minor so that it's safe to use in less-than comparisons
#	define LINUX_COMMON_VERSION 010
#endif

// If no API is defined, assume default
#ifndef LINUX_COMMON_API
#	define LINUX_COMMON_API
#endif


namespace linuxcommon{
	//string functions
	std::string find_xdg_data_dir_subdir(std::string subdir);
	std::string grep(std::string args, std::string filename);
	std::string quote_xml(std::string input);
	std::string get_cache_dir();
	std::string get_symlinkpath(std::string symlink);
	std::string term_out(std::string terminal_Command_You_Want_Output_From);
	std::string sed_i(std::string input, std::string remove, std::string replace);
	std::string current_path(int whichPath);
	std::string current_directory();
	std::string get_gtk_theme();
	std::string remove_cruft(std::string StringInput, std::string CruftToRemove);
	std::string convert_num_to_string(int num);
	std::string get_line_with_equal(std::string filename, std::string line);
	std::string home_path();
	std::string fix_file_path_for_command_line(std::string filepath);
	std::string get_shell_for_C();
	const char* convert_num_to_string(double num);
	std::string look_for_file_in_subdirs(std::string fileWITHOUTpath,std::string dir);
	std::string look_for_first_file_in_subdirs(std::string fileWITHOUTpath,std::string dir);
	std::string look_for_icon_file(std::string fileWITHOUTpath);
	std::string file_to_string(std::string fileWithPath);
	///COLOR functions
	#ifdef LINUX_COMMON_HAS_X
	std::string x_color_from_name(const char *colorName);
	#endif
	std::string color_double_to_string(const double *rgb);
	std::string remove_percentage(std::string line);
	std::string test_file_in_vector_path(std::string fileWithNOPATH,std::vector<std::string> directories_to_check);
	std::string get_directory_from_filename(std::string filename);
	
	//vector functions
	std::vector<std::string> get_file_vector(std::string DIRECTORY,std::string file);
	std::vector<std::string> grep_lines(std::string args, std::string filename);
	std::vector<std::string> comma_vector(std::string LINE,std::vector<std::string> Vector);
	std::vector<std::string> desktop_dirs();
	std::vector<std::string> xdg_conf_dirs();
	std::string find_xdg_config_dir_subdir(std::string subdir);
	std::vector<std::string> desktop_paths();
	std::vector<std::string> split_paths(const char* envVar, const char* incasenothingexists);
	std::vector<std::string> file_to_vector(std::string filename);
	std::vector<std::string> sort_array(std::vector<std::string> thisPath);
	std::vector<std::string> join_string_vectors(std::vector<std::string> vectorA,std::vector<std::string> vectorB);
	//boolean
	bool look_for_string_in_vector(std::vector<std::string> vector_to_check,std::string item_to_find);
	bool test_file(std::string fileWithFullPATH);
	bool test_dir(std::string fullpath);
	bool test_exec(std::string stringEXEC);
	bool save_string_to_file(std::string MSG,std::string filename);/***This should make the directory recursively if it does not exist***/
	bool has_file_extention_at_end(std::string filename,std::string extention);
	bool program_is_running(std::string program_line);
	bool pkill(std::string programname);
	//int
	int mkdir_p(std::string dirToMake);
	int getProcIdByName(std::string procName);
	int run_a_program(std::string program);
	int run_a_program_in_background(std::string program);
	//unsigned int
	unsigned int convert_string_to_number(const char* num);
	unsigned int items_in_path();
	#ifdef LINUX_COMMON_HAS_X
	unsigned int get_fl_color(std::string color);
	unsigned int get_fl_color(std::string color, unsigned int &color2);
    #endif
	//void
	void print_file_to_stdout(std::string fileNameWithFullPath);
	void echo(std::string msg);
	void echo_error(std::string msg);
	void processDirEnt(struct dirent* ent);
}
#endif
