#include "../include/keyboard.hpp"
//Void//////////////////////////////////////////////////////////////////
void addKey(std::string key, std::string shortcut){
	debug_out("void addKey(std::string "+ key+", std::string " +shortcut+ ")");
    if(!addElementWithTextAndAttribute("Key","key",key,shortcut)){debug_out("Add Key Failed");}
}
void addKey(std::string keyMod, std::string key, std::string shortcut){
	debug_out("void addKey(std::string "+keyMod+", std::string "+key+", std::string "+shortcut=")");
    if(!addElementWithTextAndAttribute("Key","key",key,"mask",keyMod,shortcut)){debug_out("Add Key Failed");}
}
void changemod(std::string mod,Fl_Output* Aout,Fl_Output* Bout){
	if(OutputIsEmpty(Aout)){Aout->value(mod.c_str());}
	else if(OutputIsEmpty(Bout)){Bout->value(mod.c_str());}
	else{debug_out("All Mods are filled");}
}
void changemod(std::string mod,Fl_Output* Aout,Fl_Output* Bout,Fl_Output* Cout){
	if(OutputIsEmpty(Aout)){Aout->value(mod.c_str());}
	else if(OutputIsEmpty(Bout)){Bout->value(mod.c_str());}
	else if(OutputIsEmpty(Cout)){Cout->value(mod.c_str());}
	else{debug_out("All Mods are filled");}
}
void configureKey(std::string keyShortcut, std::string newmod1, std::string newmod2, std::string newmod3, std::string newkey, std::string newaction){
	debug_out("void configureKey(std::string "+keyShortcut+", std::string "+newmod1+", std::string "+newmod2+", std::string "+newmod3+", std::string "+newkey+", std::string "+newaction+")");
    if(keyShortcut.compare("")==0){return;}
    std::string mod1FromProg,
				mod2FromProg,
				mod3FromProg,
				keyFromProg,
				actionFromProg,
				totalMod,
				totalNewMod;
    totalNewMod=newmod1+newmod2+newmod3;
    mod1FromProg=getMod1(keyShortcut);
    mod2FromProg=getMod2(keyShortcut);
    mod3FromProg=getMod3(keyShortcut);
    totalMod= mod1FromProg+mod2FromProg+mod3FromProg;
    keyFromProg=getKey(keyShortcut);
    actionFromProg=getAction(keyShortcut);
    pugi::xml_node node=compareNode("Key","key",keyFromProg,"mask",totalMod,actionFromProg);
    if(node){
		//found it!
		if(!node.attribute("mask")){node.append_attribute("mask");}
		node.attribute("mask").set_value(totalNewMod.c_str());
		if(!node.attribute("key")){node.append_attribute("key");} //This should NEVER happen..
		node.attribute("key").set_value(keyShortcut.c_str());
		node.set_value(newaction.c_str());
    }

}
bool Configure_CB(Fl_Output* mod1_output, Fl_Output* mod2_output,Fl_Output* mod3_output, Fl_Input * keyshortcut,Fl_Input * action_name1,std::string CURRENT){
	debug_out("void Configure_CB(Fl_Output* mod1_output, Fl_Output* mod2_output,Fl_Output* mod3_output, Fl_Input * keyshortcut,Fl_Input * action_name1,std::string "+CURRENT+")");
	std::string MOD1,MOD2,MOD3,KEY,ACTION;
	MOD1=getOUTPUT(mod1_output);
	MOD2=getOUTPUT(mod2_output);
	MOD3=getOUTPUT(mod3_output);
	KEY=getINPUT(keyshortcut);
	ACTION=getINPUT(action_name1);
	if(ACTION.compare("")==0){return false;}
	if(CURRENT.compare("")==0){return false;}
	configureKey(CURRENT,MOD1,MOD2,MOD3,KEY,ACTION);
	return true;
}
void Choose_Action(Fl_Input* action_name){
	debug_out("void Choose_Action(Fl_Input* action_name)");
	std::string result = choose_a_program();
	debug_out(result);
	std::string exec = "exec:";
	exec+=result;
	action_name->value(exec.c_str());
}
void deleteKey(std::string keyShortcut){
	debug_out("void deleteKey(std::string "+keyShortcut+")");
    if(keyShortcut.compare("")==0){return;}
    std::string mod1FromProg,mod2FromProg,mod3FromProg,keyFromProg,actionFromProg,totalMod;
    mod1FromProg=getMod1(keyShortcut);
    mod2FromProg=getMod2(keyShortcut);
    mod3FromProg=getMod3(keyShortcut);
    totalMod= mod1FromProg+mod2FromProg+mod3FromProg;
    keyFromProg=getKey(keyShortcut);
    actionFromProg=getAction(keyShortcut);
    removeElementCompare2Attr("Key","key",keyFromProg,"mask",totalMod,actionFromProg);
}
void key_event(Fl_Input* o, Fl_Output* out, Fl_Output* modder){
	debug_out("void key_event(Fl_Input* o, Fl_Output* out)");
	int k = Fl::event_key();
	std::string modifier_text =getINPUT(o);
	std::string key_display="";
	const char* event_text = Fl::event_text();
	int l_shift = Fl::event_key(FL_Shift_R);
	int r_shift = Fl::event_key(FL_Shift_L);
	int l_control = Fl::event_key(FL_Control_R);
	int r_control = Fl::event_key(FL_Control_L);
	int l_meta = Fl::event_key(FL_Meta_L);
	int r_meta = Fl::event_key(FL_Meta_R);
	int l_alt = Fl::event_key(FL_Alt_L);
	int r_alt = Fl::event_key(FL_Alt_R);
	bool alt = false;
	bool shift = false;
	bool meta = false;
	bool ctrl = false;
	if(r_alt||l_alt){alt=true;
		debug_out("MOD=Alt");
		key_display="Alt ";
		mod_cb("A",modder);
	}
	if(l_shift||r_shift){
		debug_out("MOD=Shift");
		mod_cb("S",modder);
		key_display="Shift +";
		shift=true;
	}
	if(l_control||r_control){
		debug_out("MOD=Control");
		key_display="Control +";
		mod_cb("C",modder);
		ctrl=true;
	}
	if(l_meta||r_meta){meta=true;
		debug_out("MOD=Meta/Super");
		key_display="Super ";
		mod_cb("4",modder);
	}
	if(event_text==NULL){
		debug_out("Key event is NULL");
		return;
	}
	key_display+=event_text;
	debug_out("Key display = "+key_display);
	if((key_display.compare("")!=0)&&(k<=256)){
		out->value(event_text);
		//out->show();
		o->value(key_display.c_str());
	}
}
void keyLayoutPopulate(Fl_Browser *o){keyPopulate(o,"layout");}
void keyModelPopulate(Fl_Browser *o){keyPopulate(o,"model");}
void keyOptionPopulate(Fl_Browser *o){keyPopulate(o,"option");}
void keyPopulate(Fl_Browser *o,std::string thingToGet){
	debug_out("void keyPopulate(Fl_Browser *o,std::string "+thingToGet+")");
	std::string list=linuxcommon::term_out("plocalectl list-x11-keymap-"+thingToGet+"s");
	if(list.compare("")==0){
		std::string file="/usr/share/X11/xkb/rules/base.lst";
		if(!linuxcommon::test_file(file)){
			errorOUT("Cannot create the list for "+thingToGet);
			return;
		}
		std::vector<std::string> vector_to_check=linuxcommon::file_to_vector(file);
		bool start=false;
		std::string fileItem="! "+thingToGet;
		for( std::vector<std::string>::iterator it = vector_to_check.begin();
		it!=vector_to_check.end();
		++it){
			std::string tmp=*it;
			unsigned int founder=tmp.find(fileItem);
			unsigned int flounder=tmp.find("! ");
			if(flounder<tmp.length()){start=false;}
			if(start){
				if(list.compare("")==0){if(tmp.compare("")!=0)list=tmp;}
				else{if(tmp.compare("")!=0)list=list+"\n"+tmp;}
			}
			if(founder<tmp.length()){start=true;}
		}
	}
	populateBrowserWithString(o,list);
}
void mod_cb(std::string mod, Fl_Output *o){
  if(mod.compare("")!=0){
    o->value(mod.c_str());
    o->redraw();
  }
}
void mod2_cb(std::string mod, Fl_Output *o){
	if(mod.compare("")==0){return;}
	o->value(mod.c_str());
}
void remove_key(Fl_Browser* o){
	debug_out("void remove_key(Fl_Browser* o)");
	const char* mykey = o->text(o->value());
	if(mykey==NULL){return;}
	std::string keyShortcut = mykey;
	if (keyShortcut.compare("")!=0){
		debug_out("Delete: "+keyShortcut);
		deleteKey(keyShortcut);
		o->clear();
		getKeys(o);
		o->redraw();
	}
	else{
		fl_message("Please click on an item to remove!");
	}
}
//String////////////////////////////////////////////////////////////////
std::string fixLayoutString(Fl_Browser *o){
	debug_out("std::string fixLayoutString(Fl_Browser *o)");
	std::string retval;
	if(checkFlBrowserItem(o)){
	  const char* val =o->text(o->value());
	  retval=val;
	  unsigned int exclaim=retval.find("!");
	  if(exclaim==0){return "";}
	  unsigned int finder=retval.find("  ");
	  if(finder<retval.length()){retval=retval.erase(finder,2);}
	  finder=retval.find(" ");
	  if(finder<retval.length()){retval=retval.erase(finder,std::string::npos);}
	}
	return retval;
}
std::string getAction(std::string keyShortcut){
	debug_out("std::string getAction(std::string "+keyShortcut+")");
    if(keyShortcut.compare("")==0){return "";}
    std::string fromProgram = keyShortcut;
    //shortcut
    unsigned length =fromProgram.length();
    unsigned found = fromProgram.find_last_of("\t");
    if(found < length){
        fromProgram = fromProgram.erase(0,found+1);
        debug_out("getAction: "+fromProgram);
        return fromProgram;
    }
    return "";
}
std::string getKey(std::string keyShortcut){
	debug_out("std::string getKey(std::string "+keyShortcut+")");
    if(keyShortcut.compare("")==0){return "";}
    std::string fromProgram = keyShortcut;
    std::string keymod2 =keyShortcut;
    //shortcut
    unsigned length =fromProgram.length();
    //recheck this code
    unsigned found = fromProgram.find_last_of("\t");
    unsigned found1 = fromProgram.find_first_of("\t");
    unsigned found2 = fromProgram.find_first_of("\t",found1);
    if(found < length){
        fromProgram = fromProgram.erase(0,found+1);
        //keymod 2
        if(found2 < keymod2.length()){
            keymod2 = keymod2.erase(found,std::string::npos);
            keymod2 = keymod2.erase(0,found2+1);
            debug_out("getKey: "+keymod2);
            return keymod2;
        }
    }
    return "";
}
std::string getLayout(){
	debug_out("std::string getLayout()");
	std::string test_command=linuxcommon::term_out("which localectl");
	std::string command="localectl";
	if(test_command.compare("")==0){
		test_command=linuxcommon::term_out("which setxkbmap");
		command="setxkbmap";
	}
	if(test_command.compare("")==0){return "";}
	std::string layout;
	if(command.compare("setxkbmap")==0){
		command+=" -query";
		layout=linuxcommon::term_out(command);
	}
	else{
		command+=" status";
		layout=linuxcommon::term_out(command);
		std::transform(layout.begin(),layout.end(),layout.begin(), ::tolower);
	}
	//std::vector<std::string> stringVec=linuxcommon::
	return layout;
}
std::string getMod(std::string keyShortcut){
	debug_out("std::string getMod(std::string "+keyShortcut+")");
    if(keyShortcut.compare("")==0){return "";}
    std::string keymod =keyShortcut;
    //shortcut
    unsigned length =keyShortcut.length();
    unsigned found = keyShortcut.find_first_of("\t");
    if(found < length){
        keymod = keymod.erase(found,std::string::npos);
        return keymod;
    }
    return "";
}
std::string getMod1(std::string keyShortcut){
	debug_out("std::string getMod1(std::string "+keyShortcut+")");
    if(keyShortcut.compare("")==0){return "";}
    std::string result =getMod(keyShortcut);
    unsigned int len = result.length();
    if(len>1){result=result.erase(1,std::string::npos);}
    debug_out("mod1:"+result);
    return result;

}
std::string getMod2(std::string keyShortcut){
	debug_out("std::string getMod2(std::string "+keyShortcut+")");
    if(keyShortcut.compare("")==0){return "";}
    std::string result =getMod(keyShortcut);
    unsigned int len = result.length();
    if(len>1){result=result.erase(0,1);}
    len = result.length();
    if(len>2){result=result.erase(1,std::string::npos);}
    debug_out("mod2:"+result);
    return result;
}
std::string getMod3(std::string keyShortcut){
	debug_out("std::string getMod3(std::string "+keyShortcut+")");
    if(keyShortcut.compare("")==0){return "";}
    std::string result =getMod(keyShortcut);
    unsigned int len = result.length();
    if(len>2){result=result.erase(0,2);}
    else{result="";}
    debug_out("mod3:"+result);
    return result;
}
std::string getINPUT(Fl_Input *o){
	debug_out("std::string getINPUT(Fl_Input *o)");
	if(o->visible()!=0){return "";}
	const char* out=o->value();
	if(out==NULL){return "";}
	std::string outer=out;
	debug_out("INPUT="+outer);
	return outer;
}
std::string getOUTPUT(Fl_Output *o){
	debug_out("std::string getOUTPUT(Fl_Output *o)");
	if(o->visible()!=0){return "";}
	const char* out=o->value();
	if(out==NULL){return "";}
	std::string outer=out;
	debug_out("OUTPUT="+outer);
	return outer;
}
std::string grabbedKey(){
    struct termios oldSettings, newSettings;
    tcgetattr( fileno( stdin ), &oldSettings );
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr( fileno( stdin ), TCSANOW, &newSettings );
    char c;
    while ( 1 ){
        fd_set set;
        struct timeval tv;

        tv.tv_sec = 10;
        tv.tv_usec = 0;

        FD_ZERO( &set );
        FD_SET( fileno( stdin ), &set );

        int res = select( fileno( stdin )+1, &set, NULL, NULL, &tv );

        if( res > 0 ){
            std::cout<<"Input available"<<std::endl;
            int thisread = read( fileno( stdin ), &c, 1 );
            if(thisread !=0){std::cerr<< gettext("read input command did not return 0")<<std::endl;}
        }
        else if( res < 0 )
        {
            perror( "select error" );
            break;
        }
        else
        {
            std::cout<<"Select timeout"<<std::endl;
        }
    }
    std::string result = "";
    result+= c;
    tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
    return result;

}
std::string oldvalue(Fl_Output* old_action, Fl_Output* current_key,Fl_Output* current_mod1,Fl_Output* current_mod2,Fl_Output* current_mod3){
	std::string temp;
	const char* mod1=current_mod1->value();
	if(mod1!=NULL){temp=mod1;}
	const char* mod2=current_mod2->value();
	if(mod2!=NULL){temp+=mod2;}
	const char* mod3=current_mod3->value();
	if(mod3!=NULL){temp+=mod3;}
	const char* keychar=current_key->value();
	if(keychar!=NULL){
		std::string keycurrent=keychar;
		if(temp.compare("")==0)temp="\t"+keycurrent;
		else{temp=temp+"\t"+keycurrent;}
	}
	const char* actionian=old_action->value();
	if(actionian!=NULL){temp=temp+"\t"+ actionian;}
	return temp;
}
//Boolean///////////////////////////////////////////////////////////////
bool add_cb(Fl_Input *action_name, Fl_Output *key_output, Fl_Output *mod_output, Fl_Output *mod2_output, Fl_Output * mod3_output, Fl_Browser *o){
	debug_out("void add_cb(Fl_Input *action_name,Fl_Output *key_output,Fl_Output *mod_output,Fl_Browser *o)");
	std::string action,keyInput,mod;
	const char* testAction=action_name->value();
	if(testAction!=NULL){action=testAction;}
	const char* this_keyInput = key_output->value();
	if(this_keyInput!=NULL){keyInput=this_keyInput;}
	const char* this_mod = mod_output->value();
	if(this_mod!=NULL){mod=this_mod;}
	const char* secondarymod=mod2_output->value();
	if(secondarymod!=NULL){mod+=secondarymod;}
	const char* tertiary=mod3_output->value();
	if(tertiary!=NULL){mod+=tertiary;}
	if(action.compare("")==0){
		debug_out("No action chosen...");
		return false;
	}
	if(keyInput.compare("")!=0){
		if(mod.compare("")!=0){addKey(mod,keyInput,action);}
		else{addKey(keyInput,action);}
		o->clear();
		getKeys(o);
		o->redraw();
		return true;
	}
	return false;
}
bool Configure(Fl_Browser *key_browser,
	Fl_Input *action_name1,
	Fl_Output *current_shortcut,
	Fl_Output *mod1_output,
	Fl_Output *mod2_output,
	Fl_Output *mod3_output,
	Fl_Output *old_value) {
	debug_out("bool Configure(Fl_Browser *key_browser,Fl_Input *action_name1,Fl_Output *current_shortcut,Fl_Output *mod1_output,Fl_Output *mod2_output,Fl_Output *mod3_output,Fl_Output *old_value)");
	if(!checkFlBrowserItem(key_browser)){
		debug_out("Browser didn't have anything nice selected");
		return false;
	}
	const char* mykey = key_browser->text(key_browser->value());
	std::string keyShortcut = mykey;
	if (keyShortcut.compare("")!=0){
		std::string mod1,mod2,mod3,key,program;
		mod1=getMod1(keyShortcut);
		if(mod1.compare("")!=0){mod1_output->value(mod1.c_str());}
		mod2=getMod2(keyShortcut);
		if(mod2.compare("")!=0){mod2_output->value(mod2.c_str());}
		mod3=getMod3(keyShortcut);
		if(mod3.compare("")!=0){mod3_output->value(mod3.c_str());}
		key=getKey(keyShortcut);
		program=getAction(keyShortcut);
		action_name1->value(program.c_str());
		current_shortcut->value(key.c_str());
		old_value->value(program.c_str());
		getKeys(key_browser);
		return true;
	}
	else{fl_message("Please click on an item to remove!");}
	return false;
}
bool newpanel(){
	debug_out("bool newpanel()");
	if(newStyle() == -1){return false;}
	return true;
}
bool getKeys(Fl_Browser* o){
	populateFLBrowser2Attr(o,"Key","key","mask");
	return false;
}
