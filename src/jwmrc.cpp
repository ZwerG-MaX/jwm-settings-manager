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
#include "../include/jwmrc.h"
pugi::xml_document doc;
//Boolean///////////////////////////////////////////////////////////////
//A
bool addButtonToLastTray(std::string attribute, std::string value, std::string text){
	debug_out("bool addButtonToLastTray(std::string "+attribute+", std::string "+value+",std::string "+text+")");
	if(text.compare("")==0){return false;}
	unsigned int whichElement=currentPanel();
	pugi::xml_node node;
	std::string element="Tray";
	std::string subelement="TrayButton";
	node=parseNodes(whichElement,element);
	if(!node.child(subelement.c_str())){
		debug_out("No subelement "+subelement+" found");
		return false;
	}
    node=node.child(subelement.c_str());
    while(node.next_sibling(subelement.c_str())){
		std::string noder=node.name();
		debug_out("getting next "+noder);
		node=node.next_sibling(subelement.c_str());
	}
	if(!node){
		std::string nodie=node.name();
		debug_out(nodie+" node does not exist");
		return false;
	}
	std::string button="Button";
	node=node.append_child(button.c_str());
	node.text().set(text.c_str());
	node.append_attribute(attribute.c_str())=value.c_str();
	return saveChangesTemp();
}
bool addElement(std::string element){
//	if(!loadTemp()){return false;}
	debug_out("addElementAndSub(std::string "+element+")");
	if(element.compare("")==0){return false;}
	pugi::xml_node node =doc.child("JWM").append_child(element.c_str());
	if(!node){return false;}
    return saveChangesTemp();
}
bool addElementAndSub(std::string element, std::string subelement){
//	if(!loadTemp()){return false;}
	debug_out("addElementAndSub(std::string "+element+", std::string "+ subelement+ ")");
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	pugi::xml_node node =doc.child("JWM").append_child(element.c_str()).append_child(subelement.c_str());
	if(!node){return false;}
    return saveChangesTemp();
}
bool addElementWithText(std::string element, std::string text){
	debug_out("addElementWithText(std::string "+ element+", std::string "+ text+")");
	if(!loadTemp()){return false;}
	if(element.compare("")==0){return false;}
	if(text.compare("")==0){return false;}
	pugi::xml_node node =  doc.child("JWM");
    pugi::xml_node testnode =  doc.child("JWM").child(element.c_str());
    if(testnode){
		node=node.insert_child_before(element.c_str(),testnode);
	}
	else{
		node=node.append_child(element.c_str());
	}
	node.text().set(text.c_str());
    return saveChangesTemp();
}
bool addElementWithTextAfter(std::string element, std::string text){
	debug_out("addElementWithText(std::string "+ element+", std::string "+ text+")");
	if(!loadTemp()){return false;}
	if(element.compare("")==0){return false;}
	if(text.compare("")==0){return false;}
	pugi::xml_node node =  doc.child("JWM");
    pugi::xml_node testnode =  doc.child("JWM").child(element.c_str());
    if(testnode){
		node=node.insert_child_after(element.c_str(),testnode);
	}
	else{
		node=node.append_child(element.c_str());
	}
	node.text().set(text.c_str());
    return saveChangesTemp();
}
bool addMenuElement(unsigned int whichMenu,std::string element){
	debug_out("bool addMenuElement(unsigned int whichMenu,std::string "+element+")");
	if(element.compare("")==0){return false;}
	pugi::xml_node node =parseNodes(whichMenu,"RootMenu");
	if(!node){
		errorOUT("The root menu does not exist!!");
		return false;
	}
	node.append_child(element.c_str());
	return saveChangesTemp();	
}
bool addSubElement(unsigned int whichElement,std::string element, std::string subelement){
//	if(!loadTemp()){return false;}
	debug_out("addSubElementWithText(unsigned int whichElement,std::string "+ element+", std::string "+ subelement+ ")");
	unsigned int i=1;
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	pugi::xml_node node =doc.child("JWM").child(element.c_str());
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    if(!node){doc.child("JWM").append_child(element.c_str());}
    node.append_child(subelement.c_str());
    return saveChangesTemp();
}
bool addSubElementWithText(unsigned int whichElement,std::string element, std::string subelement, std::string text){
//	if(!loadTemp()){return false;}
	debug_out("addSubElementWithText(unsigned int whichElement,std::string "+ element+", std::string "+ subelement+ ", std::string " + text+ ")");
	unsigned int i=1;
	if(element.compare("")==0){errorOUT("Empty element");return false;}
	if(subelement.compare("")==0){errorOUT("Empty sub-element");return false;}
	if(text.compare("")==0){errorOUT("Empty text");return false;}
	pugi::xml_node node =doc.child("JWM").child(element.c_str());
	if(!node){
		node=checkIncludes(whichElement,element);
		if(!node){
			errorOUT("COULD NOT FIND "+element);
			return false;
		}
		whichElement=i;
	}
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    if(!node){errorOUT("Empty Node");return false;}
    node.append_child(subelement.c_str());
    node=node.last_child();
    node.text().set(text.c_str());
    return saveChangesTemp();
}
bool addSubElementWithTextandAttribute(unsigned int whichElement,std::string element, std::string subelement, std::string text,std::string attribute, std::string value){
	unsigned int i=1;
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	if(attribute.compare("")==0){return false;}
	if(value.compare("")==0){return false;}
	if(text.compare("")==0){return false;}
	pugi::xml_node node =doc.child("JWM").child(element.c_str());
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    node.append_child(subelement.c_str());
    node=node.last_child();
    node.text().set(text.c_str());
    node.append_attribute(attribute.c_str())=value.c_str();
    return saveChangesTemp();

}
bool addSubElementWithAttribute(unsigned int whichElement,std::string element, std::string subelement, std::string attribute, std::string value){
	unsigned int i=1;
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	if(attribute.compare("")==0){return false;}
	if(value.compare("")==0){return false;}
	pugi::xml_node node =doc.child("JWM").child(element.c_str());
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    node.append_child(subelement.c_str());
    node=node.last_child();
    node.append_attribute(attribute.c_str())=value.c_str();
    return saveChangesTemp();

}
bool addElementWithAttribute(std::string element, std::string attribute, std::string value){
	debug_out("addElementWithAttribute(std::string "+ element+ ", std::string " +attribute + ", std::string " + value+  ")");
	if(element.compare("")==0){
		debug_out("Empty Element sent in");
		return false;
	}
	if(attribute.compare("")==0){
		debug_out("Empty attribute sent in");
		return false;
	}
	if(value.compare("")==0){
		debug_out("Empty Attribute Value sent in");
		return false;
	}
	pugi::xml_node node =  doc.child("JWM").append_child(element.c_str());
    node=node.last_child();
    node.append_attribute(attribute.c_str())=value.c_str();
    return saveChangesTemp();
}
bool addElementWithTextAndAttribute(std::string element, std::string attribute, std::string value,std::string text){
	debug_out("addElementWithTextAndAttribute(std::string "+ element+ ", std::string " +attribute + ", std::string " + value+  ", std::string " + text+ ")");
	if(element.compare("")==0){return false;}
	if(attribute.compare("")==0){return false;}
	if(value.compare("")==0){return false;}
	if(text.compare("")==0){return false;}
	pugi::xml_node node =  doc.child("JWM").append_child(element.c_str());
    //node=node.last_child();
    node.text().set(text.c_str());
    node.append_attribute(attribute.c_str())=value.c_str();
    return saveChangesTemp();
}
bool addElementWithTextAndAttribute(std::string element, std::string attribute, std::string value, std::string attribute2, std::string value2,std::string text){
	debug_out("addElementWithTextAndAttribute(std::string "+ element+ ", std::string " +attribute + ", std::string " + value+ ", std::string " +attribute2 + ", std::string " + value2+  ", std::string " + text+ ")");
	if(element.compare("")==0){return false;}
	if(attribute.compare("")==0){return false;}
	if(value.compare("")==0){return false;}
	if(text.compare("")==0){return false;}
	pugi::xml_node node =  doc.child("JWM").append_child(element.c_str());
    node.text().set(text.c_str());
    node.append_attribute(attribute.c_str())=value.c_str();
    node.append_attribute(attribute2.c_str())=value2.c_str();
    return saveChangesTemp();
}
bool addElementWithSubAndText(std::string element, std::string subelement, std::string text){
//	if(!loadTemp()){return false;}
	debug_out("addElementWithSubAndText(std::string "+ element+ ", std::string " +subelement + ", std::string " + text+ ")");
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	if(text.compare("")==0){return false;}
    pugi::xml_node node =  doc.child("JWM").append_child(element.c_str()).append_child(subelement.c_str());
    node.text().set(text.c_str());
    return saveChangesTemp();
}
bool addSubNodewithText(pugi::xml_node node,std::string element,std::string text){
	if(!node){return false;}
	std::string name=node.name();
	if(name.compare("")==0){name="node";}
	debug_out("bool addSubNodewithText(pugi::xml_node "+name+",std::string "+element+",std::string "+text+")");
	if(!node){return false;}
	if(element.compare("")==0){return false;}
	if(text.compare("")==0){return false;}
	node=node.append_child(element.c_str());
	node.text().set(text.c_str());
	return saveChangesTemp();
}
bool addSubNodewithAttributeAndText(pugi::xml_node node,std::string element,std::string attribute, std::string value, std::string text){
	if(!node){return false;}
	std::string name=node.name();
	if(name.compare("")==0){name="node";}
	debug_out("bool addSubNodewithAttributeAndText(pugi::xml_node "+name+",std::string "+element+",std::string "+attribute+", std::string "+value+",std::string "+text+")");
	if(!node){
		std::string nodie=node.name();
		debug_out(nodie+" node does not exist");
		return false;
	}
	if(element.compare("")==0){return false;}
	if(text.compare("")==0){return false;}
	node=node.append_child(element.c_str());
	node.text().set(text.c_str());
	node.attribute(attribute.c_str())=value.c_str();
	return saveChangesTemp();
}
//C
bool changeCursorTheme(Fl_Browser *o){
	debug_out("bool changeCursorTheme(Fl_Browser *o)");
	if(!checkFlBrowserItem(o)){return false;}
	std::string ThemeName=o->text(o->value());
	unsigned int finder=ThemeName.rfind("/");
	if(finder < ThemeName.length()){ThemeName=ThemeName.substr(finder+1,std::string::npos);}
	std::string IconFileName=linuxcommon::home_path();
	if(IconFileName.compare("")==0){return false;}
	IconFileName+=".icons/";
	if(!linuxcommon::test_dir(IconFileName)){linuxcommon::mkdir_p(IconFileName);}
	IconFileName+="default/index.theme";
	std::string gsetLine="gsettings set org.gnome.desktop.interface cursor-theme "+ThemeName;
	int retval = linuxcommon::run_a_program(gsetLine);
	if(retval!=0){debug_out("Didn't run the command correctly");}
	std::string FileOutput="# written by jwm-settings-manager\n\
[Icon Theme]\n\
Name=Default\n\
Comment=Default mouse cursor\n\
Inherits="+ThemeName;
	return linuxcommon::save_string_to_file(FileOutput,IconFileName);
}
bool checkDE(std::string file){
	debug_out("bool checkDE(std::string "+file+")");
	const char* DE=getenv("DESKTOP_SESSION");
	const char* xdgDE=getenv("XDG_SESSION_DESKTOP");
	const char* xdgCurrentDE=getenv("XDG_CURRENT_DESKTOP");
	std::string JWM="JWM";
	std::string ONLY=linuxcommon::get_line_with_equal(file,"OnlyShowIn=");
	std::string NOT=linuxcommon::get_line_with_equal(file,"NotShowIn=");
	debug_out("File="+file+"\nOnlyShowIn="+ONLY+"\nNotShowIn="+NOT);
	if(DE!=NULL){
		if(ONLY.find(DE)<ONLY.length()){return true;}
		else{if(ONLY.compare("")!=0){return false;}}
		if(NOT.find(DE)<NOT.length()){return false;}
	}
	if(xdgDE!=NULL){
		if(ONLY.find(xdgDE)<ONLY.length()){return true;}
		else{if(ONLY.compare("")!=0){return false;}}
		if(NOT.find(xdgDE)<NOT.length()){return false;}
	}
	if(xdgCurrentDE!=NULL){
		if(ONLY.find(xdgCurrentDE)<ONLY.length()){return true;}
		else{if(ONLY.compare("")!=0){return false;}}
		if(NOT.find(xdgCurrentDE)<NOT.length()){return false;}
	}
	if(ONLY.find(JWM)<ONLY.length()){return true;}
	else{if(ONLY.compare("")!=0){return false;}}
	if(NOT.find(JWM)<NOT.length()){return false;}
	return true;
}
bool checkExec(std::string exec){
	debug_out("bool checkExec(std::string "+exec+")");
	if(isExec(exec)){
		debug_out(exec+" is a program");
		if(linuxcommon::program_is_running(exec)){return true;}
		else if (!linuxcommon::term_out("pgrep "+exec).empty()){return true;}
		else{debug_out(exec+" is not running");}
	}
	return false;
}
bool checkFlBrowserItem(Fl_Browser* o){
	/// Simple check to see if the Fl_Browser has something selected
	int line=o->value();
	if(line>o->size()){return false;}
	const char* one=o->text(line);
	if(one==NULL){return false;}
	return true;
}
bool checkVector(std::vector<std::string> myVec,std::string item){
	return linuxcommon::look_for_string_in_vector(myVec,item);
}
//D
bool deleteElements(std::string element){
	debug_out("bool deleteElements(std::string "+element+")");
	pugi::xml_node baseNode=doc.child("JWM");
	pugi::xml_node node=doc.child("JWM").child(element.c_str());
	if(!node){
		debug_out("NO "+element+" nodes found!");
		return true;
	}
	pugi::xml_node testnode=node;
	while(testnode){
		std::string tmp=node.text().as_string();
		baseNode.remove_child(element.c_str());
		testnode=baseNode.child(element.c_str());
	}
	return saveChangesTemp();
}
bool deleteSubElement(std::string element, int whichElement){
	pugi::xml_node baseNode=doc.child("JWM");
	pugi::xml_node node=doc.child("JWM").child(element.c_str());
	if(!node){
		debug_out("NO "+element+" nodes found!");
		return true;
	}
	int i=1;
	if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    baseNode.remove_child(node);
    return saveChangesTemp();
}
//E
bool editMenuItem(int menu, int item, std::string text){
	debug_out("bool editMenuItem(int menu, int item, std::string "+text+")");
	pugi::xml_node node = getNode(menu,"RootMenu",item);
	return setNodeText(node, text);
}
bool editMenuItem(int menu, int item, std::string attribute,std::string value){
	debug_out("bool editMenuItem(int menu, int item, std::string "+attribute+",std::string "+value+")");
	pugi::xml_node node = getNode(menu,"RootMenu",item);
	return setAttribute(node, attribute,value);
}
//G
bool getIcons(Fl_Browser *o){return populateFLBrowser(o,"IconPath");}
bool getMenuItems(Fl_Browser* menuElement,std::string menu,Fl_Browser* menuElementText){
	//TODO includes
	debug_out("void getMenuItems(Fl_Browser*  menuElement,std::string "+menu+", Fl_Browser* menuElementText)");
	if(menu.compare("")==0){
		debug_out("The menu text sent in was empty");
		return false;
	}
	std::string element="RootMenu";
	pugi::xml_node node;
	std::string attributevalue;
	for(node=doc.child("JWM").child(element.c_str());node;node=node.next_sibling(element.c_str())){
		if(node.attribute("onroot")){
			attributevalue=node.attribute("onroot").as_string();
			if (attributevalue.compare(menu)==0){
				for(pugi::xml_node subnode=node.first_child();subnode;subnode=subnode.next_sibling()){
					std::string NODEname=subnode.name();
					std::string text=subnode.text().as_string();
					if(text.compare("")!=0){
						menuElementText->add(text.c_str());
					}
					else{
						std::string itemNAME;
						if(NODEname.compare("Menu")==0){
							itemNAME=gettext("Sub Menu");
							menuElementText->add(itemNAME.c_str());
						}
						else if(NODEname.compare("Separator")==0){
							itemNAME=gettext("Separator");
							menuElementText->add(itemNAME.c_str());
						}
						else if(NODEname.compare("Restart")==0){
							itemNAME=gettext("Restart");
							menuElementText->add(itemNAME.c_str());
						}
						else if(NODEname.compare("Desktops")==0){
							itemNAME=gettext("Desktop List");
							menuElementText->add(itemNAME.c_str());
						}
						else if(NODEname.compare("SendTo")==0){
							itemNAME=gettext("Send To Desktop Menu");
							menuElementText->add(itemNAME.c_str());
						}
						else if(NODEname.compare("Stick")==0){
							itemNAME=gettext("Sticky state of Window");
							menuElementText->add(itemNAME.c_str());
						}
						else if(NODEname.compare("Maximize")==0){
							itemNAME=gettext("Maximize window");
							menuElementText->add(itemNAME.c_str());
						}
						else if(NODEname.compare("Minimize")==0){
							itemNAME=gettext("Minimize window");
							menuElementText->add(itemNAME.c_str());
						}
						else if(NODEname.compare("Shade")==0){
							itemNAME=gettext("Shade window");
							menuElementText->add(itemNAME.c_str());
						}
						else if(NODEname.compare("Move")==0){
							itemNAME=gettext("Move window");
							menuElementText->add(itemNAME.c_str());
						}
						else if(NODEname.compare("Resize")==0){
							itemNAME=gettext("Resize window");
							menuElementText->add(itemNAME.c_str());
						}
						else if(NODEname.compare("Kill")==0){
							itemNAME=gettext("Kill window");
							menuElementText->add(itemNAME.c_str());
						}
						else if(NODEname.compare("Close")==0){
							itemNAME=gettext("Close window");
							menuElementText->add(itemNAME.c_str());
						}
						else if(NODEname.compare("Exit")==0){
							itemNAME=gettext("Exit");
							menuElementText->add(itemNAME.c_str());
						}
						else{
							menuElementText->add(NODEname.c_str());
						}
					}
					menuElement->add(NODEname.c_str());
				}
			}
		}
     
     }
	menuElement->redraw();
	menuElementText->redraw();
	return true;
}
bool getMenus(Fl_Browser* rootnode){
	//TODO Includes
	debug_out("bool getMenus(Fl_Browser* rootnode)");
	std::string element="RootMenu";
	std::string attributevalue;
	bool retval=false;
	for(pugi::xml_node node=doc.child("JWM").child(element.c_str());node;node=node.next_sibling(element.c_str())){
		if(node.attribute("onroot")){
			attributevalue=node.attribute("onroot").as_string();
			if (attributevalue.compare("")!=0){
				retval=true;
				debug_out("adding: "+attributevalue);
				rootnode->add(attributevalue.c_str());
			}
		}
     
     }
     rootnode->redraw();
	return retval;
}
//I
bool isColor(std::string text){
	debug_out("bool isColor(std::string "+text+")");
	std::string HTMLcolor=text.substr(0,1);
	if(isImage(text)){return false;}
	if(HTMLcolor.compare("#")==0){return true;}
	//TODO make this smarter eventually..
	return false;
}
bool isElement(std::string element){
	debug_out("bool isElement(std::string "+ element+")");
	if(element.compare("")==0){return false;}
	pugi::xml_node node = doc.child("JWM").child(element.c_str());
	if(!node){node=checkIncludes(element);}
	if(node){return true;}
	setJSMItem("file",homePath());
	return false;
}
bool isElement(std::string element, std::string subelement){
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	debug_out("bool isElement(std::string "+ element+ ", std::string "+ subelement+")");
	pugi::xml_node node = doc.child("JWM").child(element.c_str()).child(subelement.c_str());
	if(!node){node=checkIncludes(element,subelement);}
	if(node){return true;}
	setJSMItem("file",homePath());
	return false;
}
bool isElement(std::string element, std::string subelement, std::string SUBsubelement){
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	debug_out("bool isElement(std::string "+ element+ ", std::string "+ subelement+ ", std::string "+ SUBsubelement+")");
	pugi::xml_node node = doc.child("JWM").child(element.c_str()).child(subelement.c_str()).child(SUBsubelement.c_str());
	if(!node){node=checkIncludes(element,subelement,SUBsubelement);}
	if(node){return true;}
	setJSMItem("file",homePath());
	return false;
}
bool isExec(std::string exec){
	std::string tmp=linuxcommon::term_out("which "+exec);
	if(tmp.compare("")!=0){return true;}
	return false;
}
bool isImage(std::string filename){
	debug_out("bool isImage(std::string "+filename+")");
	if(linuxcommon::has_file_extention_at_end(filename,".png")){return true;}
	if(linuxcommon::has_file_extention_at_end(filename,".jpg")){return true;}
	if(linuxcommon::has_file_extention_at_end(filename,".jpeg")){return true;}
	if(linuxcommon::has_file_extention_at_end(filename,".svg")){return true;}
	return false;
}
bool isMenu(std::string rootNumber){
	//TODO check includes (more)
    debug_out("bool isMenu(std::string "+rootNumber+")");
	unsigned int numOFpanels = numPanels();
	if (numOFpanels == 0 ){return false;}
	std::string root = "root:";
	root += rootNumber;
	std::string num = root;
	std::string compNum;
	int i = 1;
	int panel = currentPanel();
	pugi::xml_node panelElement = doc.child("JWM").child("Tray");
	if (panel != i){
		while(panelElement.next_sibling("Tray") && i!=panel){
			panelElement=panelElement.next_sibling("Tray");
			i++;
		}
	}
	if(!panelElement){panelElement=checkIncludes(panel,"Tray");}
	panelElement=panelElement.child( "TrayButton" );
	if(panelElement.child( "TrayButton" )){
        for(panelElement=panelElement.child("TrayButton");panelElement;panelElement = panelElement.next_sibling("TrayButton")){
			if(panelElement.child("Button")){
				pugi::xml_node button;
				for(button=panelElement.child("Button");button;button=button.next_sibling("Button")){
					compNum = button.text().as_string();
					if(compNum.compare("")==0){debug_out("can't compare... there is nothing found yet.");}
					else{debug_out("comparing: "+compNum+" to: "+num);}
					if(compNum.compare(num)==0){return true;}
				}
			}
			compNum=panelElement.text().as_string();
			if(compNum.compare("")==0){debug_out("can't compare... there is nothing found yet.");}
			else{debug_out("comparing: "+compNum+"to: "+num);}
			if(compNum.compare(num)==0){return true;}
		}
	}
	return false;
}
bool isRootMenu(std::string rootmenu){
    std::string thisRoot;
    pugi::xml_node menuElement = doc.child("JWM");
    if(!menuElement.child("RootMenu")){
		menuElement=checkIncludes("RootMenu");
		if(!menuElement){return false;}
	}
	else{menuElement=menuElement.child("RootMenu");}
    for(menuElement=menuElement;
        menuElement;
        menuElement=menuElement.next_sibling("RootMenu")){
        thisRoot=menuElement.attribute("onroot").as_string();
        debug_out("This root: "+thisRoot+" the one we want: "+rootmenu);
        if(thisRoot.compare(rootmenu)==0){
            debug_out("Found: "+thisRoot);
            return true;
        }
    }
    debug_out("Didn't find the menu");
    return false;
}
bool isSVG(std::string filename){
	debug_out("bool isSVG(std::string "+filename+")");
    return linuxcommon::has_file_extention_at_end(filename,".svg");
}
bool isTrayElement(std::string element){
	pugi::xml_node node = checkIncludes("Tray",element);
	if(node){return true;}
	return false;
}
//L
bool load(){
	std::string fileName = homePath();
	if(fileName.compare("")==0){return false;}
	return load(fileName);
}
bool loadTemp(){
	std::string fileName = homePath();
	if(fileName.compare("")==0){return false;}
	fileName+="~";
	return load(fileName);
}
bool load(std::string filename){return load(filename,true);}
bool load(std::string fileName, bool saveTemp){
	debug_out("bool load(std::string "+fileName+")");
    if(fileName.compare("")==0){linuxcommon::echo_error("file does not exist and cannot be loaded");return false;}
   // debug_out("load(): "+fileName);
    if(!doc.load_file( fileName.c_str() )){
        if(!linuxcommon::test_file(fileName.c_str())){
            debug_out("The file: "+fileName+" was not found.");
            return false;
        }
    }
    else{
		//debug_out("document loaded!");
		setJSMItem("file",fileName);
		if(saveTemp){return saveChangesTempOverwrite(fileName);} //save the current file as the temp file
    }
    return true;
}
//N
bool newVersionJWM(){
	debug_out("bool newVersionJWM()");
    const char* jwmVersion = "jwm -v | grep JWM |sed 's/ by.*//' |sed 's/JWM v//'";
	std::string version = terminal(jwmVersion);
	std::string newTagVersion = "2.3.0";
    if(version.compare(newTagVersion)==0){return true;}
    int newTagVersionMajor = 2, newTagVersionMinor = 3;
    int dot1 = version.find_first_of('.');
    int dot2 = version.rfind('.');
    std::string major = version.substr(0,dot1);
    std::string minor = version.substr(dot1+1,dot2);
    int majorVersion = convert(major.c_str());
    int minorVersion = convert(minor.c_str());
    if (majorVersion > newTagVersionMajor){return true;}
    if ((majorVersion == newTagVersionMajor)&&(minorVersion >= newTagVersionMinor)){return true;}
    return false;
}
//P
bool populateFLBrowser(Fl_Browser *o,std::string element){
//	if(!loadTemp()){return false;}
	debug_out("bool populateFLBrowser(Fl_Browser *o,std::string "+element+")");
	if(element.compare("")==0){return false;}
	pugi::xml_node node=doc.child("JWM").child(element.c_str());
	if(!node){node=checkIncludes(element);}
	if(!node){return false;}
    for (node=doc.child("JWM").child(element.c_str());node;node=node.next_sibling(element.c_str())){
        std::string value  = node.text().as_string();
        if(value.compare("")!=0){
            const char * v = value.c_str();
            o->add(v);
        }
        else{return false;}
        debug_out("Value:"+value);
    }
    return true;
}
bool populateFLBrowser(Fl_Browser *o,std::string element,std::string subelement,unsigned int whichMainElement){
//	if(!loadTemp()){return false;}
	debug_out("bool populateFLBrowser(Fl_Browser *o,std::string "+element+",std::string "+subelement+",unsigned int whichMainElement)");
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
    pugi::xml_node node=doc.child("JWM").child(element.c_str());
    if(!node){node=checkIncludes(element);}
    if(!node){return false;}
    unsigned int i=1;
    if(whichMainElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichMainElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
	for (pugi::xml_node node2=node.child(subelement.c_str());node2;node2=node2.next_sibling(subelement.c_str())){
		std::string value  = node2.text().as_string();
		if(value.compare("")!=0){
			const char * v = value.c_str();
			o->add(v);
		}
		else{errorOUT("BLANK Text in:"+element);}
		debug_out("Value:"+value);
    }
    return true;
}
bool populateFLBrowser2Attr(Fl_Browser *o,std::string element,std::string attribute1, std::string attribute2){
debug_out("bool populateFLBrowser2Attr(Fl_Browser *o,std::string "+element+",std::string "+attribute1+",std::string " + attribute2+")");
	if(element.compare("")==0){
		debug_out("Element NOT specified");
		return false;
	}
	if(attribute1.compare("")==0){
		debug_out("1st Attribute NOT specified");
		return false;
	}
	if(attribute2.compare("")==0){
		debug_out("2nd Attribute NOT specified");
		return false;
	}
    pugi::xml_node node=doc.child("JWM").child(element.c_str());
    if(!node){node=checkIncludes(element);}
    if(!node){
		debug_out(element+" NOT found in document");
		return false;
	}
	for (pugi::xml_node node2=doc.child("JWM").child(element.c_str());node2;node2=node2.next_sibling(element.c_str())){
		std::string value=node2.text().as_string();
		std::string attr1,attr2;
		if(value.compare("")!=0){
			attr1=node2.attribute(attribute1.c_str()).as_string();
			attr2=node2.attribute(attribute2.c_str()).as_string();
			debug_out(attribute1+"="+attr1+"\n"+attribute2+"="+attr2+"\n"+element+" text="+value);
			std::string browser_line=attr1+'\t'+attr2+ '\t'+value;
			const char * v = browser_line.c_str();
			o->add(v);
		}
		else{
			errorOUT("BLANK Text in:"+element);
		}
    }
    return true;
}
//R
bool removeMenu(std::string value){
	debug_out("bool removeMenu(std::string "+value+")");
	return false;
}
//S
bool saveChanges(){
	std::string myhomie=getJSMItem("file");
	if(myhomie.compare("")==0){return false;}
	myhomie=makeNOTtemp(myhomie);
	return saveChanges(myhomie,true,true);
}
bool saveChanges(std::string filename, bool restart, bool reload){
	debug_out("bool saveChanges(std::string "+filename+", bool restart, bool reload)");
	if(filename.compare("")==0){return false;}
    if(!doc.save_file( filename.c_str() )){
		debug_out("saveChanges failed for: "+filename);
		return false;
	}
	if(restart){
		if(std::system("jwm -restart")!=0){errorOUT("couldn't restart JWM");}
    }
    else{
		if(reload){return load(filename);}
		return true;
	}
    return false;
}
bool saveNoRestart(){
	loadTemp();
	std::string myhomie=getJSMItem("file");
	if(myhomie.compare("")==0){return false;}
	myhomie=makeNOTtemp(myhomie);
	return saveChanges(myhomie,false,false);
}
bool saveChangesTemp(){
	std::string myhomie=getJSMItem("file");
	if(myhomie.compare("")==0){return false;}
	myhomie=makeTempName(myhomie);
	return saveChanges(myhomie,false,true);
}
bool saveChangesTempOverwrite(){
	std::string myhomie=getJSMItem("file");
	if(myhomie.compare("")==0){return false;}
	myhomie=makeTempName(myhomie);
	return saveChanges(myhomie,false,false);
}
bool saveChangesTempOverwrite(std::string myhomie){
	if(myhomie.compare("")==0){return false;}
	myhomie=makeTempName(myhomie);
	return saveChanges(myhomie,false,false);
}
bool setAttribute(pugi::xml_node node,std::string attribute,std::string value){
	if(!node){
		std::string texter=node.name();
		debug_out("setAttribute::"+texter+" node doesn't exist");
		return false;
	}
	std::string name=node.name();
	if(name.compare("")==0){name="node";}
	debug_out("bool setAttribute(pugi::xml_node "+name+",std::string "+attribute+",std::string "+value+")");
	if(attribute.compare("")==0){return false;}
	if(value.compare("")==0){return false;}
	if(!node.attribute(attribute.c_str())){
		node.append_attribute(attribute.c_str())=value.c_str();
	}
	else{
		node.attribute(attribute.c_str()).set_value(value.c_str());
	}
	std::string nodename;
	nodename = node.attribute(attribute.c_str()).as_string();
	debug_out("Attribute name:"+nodename);
	return saveChangesTemp();
}
bool setElementAttribute(std::string element, std::string attribute, std::string value){
	debug_out("bool setElementAttribute(std::string "+ element+ ", std::string " + attribute+ ", std::string "+ value+")");
	if(element.compare("")==0){return false;}
	if(attribute.compare("")==0){return false;}
	if(value.compare("")==0){return false;}
    pugi::xml_node node = doc.child("JWM").child(element.c_str());
    if(!node){node=checkIncludes(element);}
    if(!node){node = doc.child("JWM").append_child(element.c_str());}
    if(node){return setAttribute(node,attribute,value);}
    return false;
}
bool setElementAttribute(unsigned int whichElement, std::string element, std::string attribute, std::string value){
	debug_out("bool setElementAttribute(std::string "+ element+ ", std::string " + attribute+ ", std::string "+ value+")");
	if(element.compare("")==0){return false;}
	if(attribute.compare("")==0){return false;}
	if(value.compare("")==0){return false;}
    unsigned int i=1;
    pugi::xml_node node = doc.child("JWM").child(element.c_str());
    if(!node){node=checkIncludes(element);}
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    if(!node){node=checkIncludes(whichElement,element);}
    if(!node){node = doc.child("JWM").append_child(element.c_str());}
    if(node){return setAttribute(node,attribute,value);}
    return false;
}
bool setElementAttribute(unsigned int whichElement, std::string element, std::string subelement, std::string attribute, std::string value){
	debug_out("bool setElementAttribute(std::string "+ element+ ", std::string " + attribute+ ", std::string "+ value+")");
//	if(!loadTemp()){return false;}
	if(element.compare("")==0){return false;}
	if(attribute.compare("")==0){return false;}
	if(value.compare("")==0){return false;}
    unsigned int i=1;
    pugi::xml_node node = doc.child("JWM").child(element.c_str());
    if(!node){node=checkIncludes(element);}
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    if(!node){node=checkIncludes(whichElement,element);}
    if(!node){node = doc.child("JWM").append_child(element.c_str());}
    node=node.child(subelement.c_str());
    if(!node){node = doc.child("JWM").child(element.c_str()).append_child(subelement.c_str());}
    if(node){return setAttribute(node,attribute,value);}
    return false;
}
bool setElementAttribute(std::string element, std::string subelement, std::string attribute, std::string value){
	debug_out("bool setElementAttribute(std::string "+ element+ ", std::string "+ subelement+", std::string " + attribute+ ", std::string "+ value+")");
//	if(!loadTemp()){return false;}
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	if(attribute.compare("")==0){return false;}
	if(value.compare("")==0){return false;}
    pugi::xml_node node = doc.child("JWM").child(element.c_str());
    if(!node){node=checkIncludes(element);}
    if(!node){node = doc.child("JWM").append_child(element.c_str());}
    node=node.child(subelement.c_str());
    if(!node){node=checkIncludes(element,subelement);}
    if(!node){node = doc.child("JWM").child(element.c_str()).append_child(subelement.c_str());}
    if(node){return setAttribute(node,attribute,value);}
    return false;
}
bool setElementAttribute(std::string element, std::string subelement, std::string SUBsubsubelement, std::string attribute, std::string value){
//	if(!loadTemp()){return false;}
	debug_out("bool setElementAttribute(std::string "+ element+ ", std::string "+ subelement+ ", std::string "+ SUBsubsubelement+", std::string " + attribute+ ", std::string "+ value+")");
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	if(SUBsubsubelement.compare("")==0){return false;}
	if(attribute.compare("")==0){return false;}
	if(value.compare("")==0){return false;}
	pugi::xml_node node = doc.child("JWM").child(element.c_str()).child(subelement.c_str()).child(SUBsubsubelement.c_str());
    if(!node){node=checkIncludes(element,subelement,SUBsubsubelement);}
    if(!node){node = doc.child("JWM").child(element.c_str()).child(subelement.c_str()).append_child(SUBsubsubelement.c_str());}
    if(node){return setAttribute(node,attribute,value);}
    return false;
}
bool setElementAttributeANDtext(std::string element, std::string attribute, std::string value,std::string text){
	debug_out("bool setElementAttributeANDtext(std::string "+ element+", std::string " + attribute+ ", std::string "+ value+", std::string "+text+")");
	if(element.compare("")==0){return false;}
	if(attribute.compare("")==0){return false;}
	if(value.compare("")==0){return false;}
	if(text.compare("")==0){return false;}
	pugi::xml_node node = doc.child("JWM").child(element.c_str());
	if(!node){node=checkIncludes(element);}
    if(!node){node = doc.child("JWM").append_child(element.c_str());}
    node.attribute(attribute.c_str()).set_value(value.c_str());
    node.text().set(text.c_str());
    return saveChangesTemp();
}
bool setElementAttributeANDtext(std::string element, std::string subelement, std::string attribute, std::string value,std::string text){
	debug_out("bool setElementAttributeANDtext(std::string "+ element+ ", std::string "+ subelement+", std::string " + attribute+ ", std::string "+ value+", std::string "+text+")");
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	if(attribute.compare("")==0){return false;}
	if(value.compare("")==0){return false;}
	if(text.compare("")==0){return false;}
	pugi::xml_node node = doc.child("JWM").child(element.c_str()).child(subelement.c_str());
	if(!node){node=checkIncludes(element,subelement);}
    if(!node){node = doc.child("JWM").child(element.c_str()).append_child(subelement.c_str());}
    node.attribute(attribute.c_str()).set_value(value.c_str());
    node.text().set(text.c_str());
    return saveChangesTemp();
}
bool setElementAttributeANDtext(std::string element, std::string subelement, std::string SUBsubsubelement, std::string attribute, std::string value,std::string text){
	debug_out("bool setElementAttributeANDtext(std::string "+ element+ ", std::string "+ subelement+ ", std::string "+ SUBsubsubelement+", std::string " + attribute+ ", std::string "+ value+", std::string "+text+")");
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	if(SUBsubsubelement.compare("")==0){return false;}
	if(attribute.compare("")==0){return false;}
	if(value.compare("")==0){return false;}
	if(text.compare("")==0){return false;}
	pugi::xml_node node = doc.child("JWM").child(element.c_str()).child(subelement.c_str()).child(SUBsubsubelement.c_str());
    if(!node){node=checkIncludes(element,subelement,SUBsubsubelement);}
    if(!node){node = doc.child("JWM").child(element.c_str()).child(subelement.c_str()).append_child(SUBsubsubelement.c_str());}
    node.attribute(attribute.c_str()).set_value(value.c_str());
    node.text().set(text.c_str());
    return saveChangesTemp();
}
bool setElementColor(std::string element, const double* rgb){
//	if(!loadTemp()){return false;}
	debug_out("bool setElementColor(std::string "+ element+", const double* rgb)");
	if(element.compare("")==0){return false;}
	std::string c=colorToString(rgb);
	return setElementText(element,c);
}
bool setElementColor(std::string element, std::string subelement, const double* rgb){
//	if(!loadTemp()){return false;}
	debug_out("bool setElementColor(std::string "+ element+ ", std::string " + subelement+", const double* rgb)");
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	std::string c=colorToString(rgb);
	return setElementText(element,subelement,c);
}
bool setElementColor(std::string element, std::string subelement, std::string SUBsubsubelement, const double* rgb){
//	if(!loadTemp()){return false;}
	debug_out("bool setElementColor(std::string "+ element+ ", std::string " + subelement+ ", std::string " + SUBsubsubelement+", const double* rgb)");
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	if(SUBsubsubelement.compare("")==0){return false;}
	std::string c=colorToString(rgb);
	return setElementText(element,subelement,SUBsubsubelement,c);
}
bool setElementInt(std::string element, unsigned int text){
	debug_out("setElementInt(std::string "+ element+ "unsigned int text)");
	std::string textr=linuxcommon::convert_unsigned_to_string(text);
	return setElementText(element,textr);
}
bool setElementInt(std::string element, std::string subelement, unsigned int text){
	debug_out("setElementInt(std::string "+ element+", std::string " +subelement +"unsigned int text)");
	std::string textr=linuxcommon::convert_unsigned_to_string(text);
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	return setElementText(element,subelement,textr);
}
bool setElementInt(std::string element, std::string subelement, std::string SUBsubsubelement, unsigned int text){
	debug_out("setElementInt(std::string "+ element+", std::string " +subelement + ", std::string "+ SUBsubsubelement+"unsigned int text)");
	std::string textr=linuxcommon::convert_unsigned_to_string(text);
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	if(SUBsubsubelement.compare("")==0){return false;}
	return setElementText(element,subelement,SUBsubsubelement,textr);
}
bool setElementFloat(std::string element, double* text){
	debug_out("setElementFloat(std::string "+element + ", float text)");
	std::string textr=colorToString(text);
	return setElementText(element,textr);
}
bool setElementFloat(std::string element, std::string subelement, double* text){
	debug_out("setElementFloat(std::string "+element +", std::string "+ subelement+", float text)");
	std::string textr=colorToString(text);
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	return setElementText(element,subelement,textr);
}
bool setElementFloat(std::string element, std::string subelement, std::string SUBsubsubelement, double* text){
	debug_out("setElementFloat(std::string "+element +", std::string "+ subelement+", std::string "+ SUBsubsubelement+", float text)");
	std::string textr=colorToString(text);
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	if(SUBsubsubelement.compare("")==0){return false;}
	return setElementText(element,subelement,SUBsubsubelement,textr);
}
bool setElementText(std::string element, std::string text){
	debug_out("setElementText(std::string "+ element+ ", std::string " +text + ")");
//	if(!loadTemp()){return false;}
	if(element.compare("")==0){return false;}
	if(text.compare("")==0){return false;}
    pugi::xml_node node = doc.child("JWM").child(element.c_str());
    if(!node){node=checkIncludes(element);}
    if(!node){node = doc.child("JWM").append_child(element.c_str());}
    node.text().set(text.c_str());
    return saveChangesTemp();
}
bool setElementText(unsigned int whichElement, std::string element, std::string subelement, std::string text){
	pugi::xml_node node = doc.child("JWM").child(element.c_str());
	unsigned int i=1;
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    if(!node){node=checkIncludes(whichElement,element);}
    if(!node){node = doc.child("JWM").append_child(element.c_str());}
    node=node.child(subelement.c_str());
    node.text().set(text.c_str());
    return saveChangesTemp();
}
bool setElementText(std::string element, std::string subelement, std::string text){
	debug_out("setElementText(std::string "+ element+ ", std::string "+ subelement+", std::string " +text + ")");
//	if(!loadTemp()){return false;}
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	if(text.compare("")==0){return false;}
    pugi::xml_node node = doc.child("JWM").child(element.c_str()).child(subelement.c_str());
    if(!node){node=checkIncludes(element,subelement);}
    if(!node){
		node = doc.child("JWM").child(element.c_str());
		if(!node){node=doc.child("JWM").append_child(element.c_str());}
		node=node.child(subelement.c_str());
		if(!node){node=doc.child("JWM").child(element.c_str()).append_child(subelement.c_str());}
	}
    node.text().set(text.c_str());
    return saveChangesTemp();
}
bool setElementText(std::string element, std::string subelement, std::string SUBsubsubelement, std::string text){
	debug_out("setElementText(std::string "+ element+ ", std::string "+ subelement+ ", std::string "+ SUBsubsubelement+", std::string " +text + ")");
//	if(!loadTemp()){return false;}
	if(element.compare("")==0){return false;}
	if(subelement.compare("")==0){return false;}
	if(SUBsubsubelement.compare("")==0){return false;}
	if(text.compare("")==0){return false;}
    pugi::xml_node node = doc.child("JWM").child(element.c_str()).child(subelement.c_str()).child(SUBsubsubelement.c_str());
    if(!node){node=checkIncludes(element,subelement,SUBsubsubelement);}
    if(!node){
		debug_out("Didn't find "+element+"->"+subelement+"->"+SUBsubsubelement+" in check Includes");
		node = doc.child("JWM").child(element.c_str());
		if(!node){node=doc.child("JWM").append_child(element.c_str());}
		node=node.child(subelement.c_str());
		if(!node){node=doc.child("JWM").child(element.c_str()).append_child(subelement.c_str());}
		node=node.child(SUBsubsubelement.c_str());
		if(!node){node=doc.child("JWM").child(element.c_str()).child(subelement.c_str()).append_child(SUBsubsubelement.c_str());}
	}
    node.text().set(text.c_str());
    return saveChangesTemp();
}
bool setJSMItem(std::string item, std::string value){
	debug_out("bool setJSMItem(std::string "+item+", std::string "+value+")");
	if(item.compare("")==0){return false;}
	std::string filename=linuxcommon::home_path();
	if(filename.compare("")==0){return false;}
	filename+=".jsm";
	std::string stringfile,p,d,f;
	if(!linuxcommon::test_file(filename)){
		debug_out(filename+" NOT found");
		p="1";
		d="false";
		f=homePath();
	}
	else{
		d=getJSMItem("debug");
		p=getJSMItem("panel");
		f=getJSMItem("file");
	}
	if(item.compare("panel")==0){p=value;}
	else if(item.compare("debug")==0){d=value;}
	else if(item.compare("file")==0){f=value;}
	stringfile="panel="+p+"\ndebug="+d+"\nfile="+f+"\n";
	return linuxcommon::save_string_to_file(stringfile,filename);
}
bool setLastTrayButtonAttribute(std::string attribute,std::string value){
	debug_out("bool setLastTrayButtonAttribute(std::string "+attribute+",std::string "+value+")");
	if(attribute.compare("")==0){return false;}
	if(value.compare("")==0){return false;}
	unsigned int whichElement=currentPanel();
	pugi::xml_node node;
	std::string element="Tray";
	std::string subelement="TrayButton";
	node=parseNodes(whichElement,element);
	if(!node.child(subelement.c_str())){
		debug_out("No subelement "+subelement+" found");
		return false;
	}
    node=node.child(subelement.c_str());
    while(node.next_sibling(subelement.c_str())){
		std::string noder=node.name();
		debug_out("getting next "+noder);
		node=node.next_sibling(subelement.c_str());
	}
	node.append_attribute(attribute.c_str())=value.c_str();
	std::string nodename=doc.child(node.name()).name();
	debug_out("Node name:"+nodename);
	return saveChangesTemp();
}
bool setNodeText(pugi::xml_node node,std::string text){
	if(!node){return false;}
	std::string name=node.name();
	if(name.compare("")==0){name="node";}
	debug_out("bool setNodeText(pugi::xml_node "+name+",std::string "+text+")");
	if(text.compare("")==0){return false;}
	node.text().set(text.c_str());
	return saveChangesTemp();
}
bool setNodeButtonTextByMask(pugi::xml_node node,std::string text,std::string attribute){
	if(!node){return false;}
	std::string name=node.name();
	if(name.compare("")==0){name="node";}
	debug_out("bool setNodeText(pugi::xml_node "+name+",std::string "+text+")");
	if(text.compare("")==0){return false;}
	//TODO figure out how to either add a button node, or add just the text..
	if(!node.child("Button")){return false;}
	node=node.find_child_by_attribute("Button","mask",attribute.c_str());
	if(!node)node=node.child("Button");
	node.text().set(text.c_str());
	return saveChangesTemp();
}
bool setRootMenuAttribute(int MENU, std::string attribute,std::string value){
	debug_out("bool setRootMenuAttribute(int MENU, std::string "+attribute+",std::string "+value+")");
	if(value.compare("")==0){return false;}
	pugi::xml_node node=getMenu(MENU);
	return setAttribute(node,attribute,value);
}
bool setRootMenuHeight(std::string val, int height){
	debug_out("bool setRootMenuHeight(std::string "+val+", int height)");
	if(val.compare("")==0){return false;}
	std::string thing = linuxcommon::convert_num_to_string(height);
	setRootMenuAttribute(val,"height",thing);
	return true;
}
//T
bool testExec(std::string command){return linuxcommon::test_exec(command);}
//String////////////////////////////////////////////////////////////////
//C
std::string checkListofExec(std::vector<std::string> list){
	return linuxcommon::check_list_of_exec(list);
}
std::string colorToString(const double *rgb){
	return linuxcommon::color_double_to_string(rgb);
}
//F
std::string fixHomieInclude(std::string includeLine){
	std::string result=linuxcommon::sed_i(includeLine,"$HOME/",linuxcommon::home_path());
	result=linuxcommon::sed_i(result,"~/",linuxcommon::home_path());
	return result;
}
//G
std::string getAttribute(pugi::xml_node node,std::string attribute){
	debug_out("std::string getAttribute(pugi::xml_node node,std::string "+attribute+")");
	if(!node){return "";}
	if(attribute.compare("")==0){return "";}
	std::string res=node.attribute(attribute.c_str()).as_string();
	return res;
}
std::string getElementText(std::string element){
	if(element.compare("")==0){return "";}
	debug_out("std::string getElementText(std::string "+element +")");
    pugi::xml_node node = doc.child("JWM").child(element.c_str());
    std::string stringie="";
    if(!node){node=checkIncludes(element);}
    if(node){stringie = node.text().as_string();}
    debug_out("result="+stringie);
    return stringie;
}
std::string getElementText(std::string element, std::string subelement){
	debug_out("std::string getElementText(std::string "+element +", std::string  "+subelement+")");
	if(element.compare("")==0){return "";}
	if(subelement.compare("")==0){return "";}
    pugi::xml_node node = doc.child("JWM").child(element.c_str()).child(subelement.c_str());
    std::string stringie="";
    if(!node){node=checkIncludes(element,subelement);}
    if(node){stringie = node.text().as_string();}
    debug_out("result="+stringie);
    return stringie;
}
std::string getElementText(unsigned int whichElement, std::string element, std::string subelement){
	unsigned int i=1;
    pugi::xml_node node = doc.child("JWM").child(element.c_str());
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    node=node.child(subelement.c_str());
    if(!node){return "";}
    return node.text().as_string();
}
std::string getElementText(std::string element, std::string subelement, std::string SUBsubsubelement){

	debug_out("std::string getElementText(std::string "+element +", std::string  "+subelement+ ", std::string  "+ SUBsubsubelement+")");
	if(element.compare("")==0){return "";}
	if(subelement.compare("")==0){return "";}
	if(SUBsubsubelement.compare("")==0){return "";}
    pugi::xml_node node = doc.child("JWM").child(element.c_str()).child(subelement.c_str()).child(SUBsubsubelement.c_str());
    std::string stringie="";
    if(!node){node=checkIncludes(element,subelement,SUBsubsubelement);}
    if(node){stringie = node.text().as_string();}
    debug_out("result="+stringie);
    return stringie;
}
std::string getElementAttribute(std::string element, std::string attribute){
	debug_out("std::string getElementAttribute(std::string "+element +", std::string  "+attribute+")");
	if(element.compare("")==0){return "";}
	if(attribute.compare("")==0){return "";}
    pugi::xml_node node = doc.child("JWM").child(element.c_str());
    std::string stringie="";
    if(!node){node=checkIncludes(element);}
    if(node){stringie = node.attribute(attribute.c_str()).as_string();}
    debug_out("result="+stringie);
    return stringie;
}
std::string getElementAttribute(std::string element, std::string subelement, std::string attribute){
	debug_out("std::string getElementAttribute(std::string "+element +", std::string  "+  subelement+ ", std::string  "+attribute+")");
	if(element.compare("")==0){return "";}
	if(subelement.compare("")==0){return "";}
	if(attribute.compare("")==0){return "";}
    pugi::xml_node node = doc.child("JWM").child(element.c_str()).child(subelement.c_str());
    std::string stringie="";
    if(!node){node=checkIncludes(element,subelement);}
    if(node){stringie = node.attribute(attribute.c_str()).as_string();}
    debug_out("result="+stringie);
    return stringie;
}
std::string getElementAttributeFromElementWithAttributeAndValue(std::string element, std::string attribOfEle, std::string value, std::string subelement, std::string attribute){
	debug_out("std::string getElementAttributeFromElementWithAttributeAndValue(std::string "+element +", std::string  "+attribOfEle+", std::string  "+value +", std::string  "+  subelement+ ", std::string  "+attribute+")");
	if(element.compare("")==0){return "";}
	if(subelement.compare("")==0){return "";}
	if(attribute.compare("")==0){return "";}
    pugi::xml_node node = doc.child("JWM").find_child_by_attribute(element.c_str(),attribOfEle.c_str(),value.c_str());
    debug_out(node.name());
    //.child(subelement.c_str());
    std::string stringie="";
    if(!node){//TODO
		debug_out("TODO: fix this");
		//node=checkIncludes(element,subelement);}
	}
    if(node){stringie = node.child(subelement.c_str()).attribute(attribute.c_str()).as_string();}
    debug_out("result="+stringie);
    return stringie;
}
std::string getElementAttributeFromElementWithAttributeAndValueAndText(std::string element, std::string attribOfEle, std::string value, std::string subelement, std::string attribute,std::string text){
	debug_out("std::string getElementAttributeFromElementWithAttributeAndValueAndText(std::string "+element +", std::string  "+attribOfEle+", std::string  "+value +", std::string  "+  subelement+ ", std::string  "+attribute+ ", std::string  "+text+")");
	if(element.compare("")==0){return "";}
	if(subelement.compare("")==0){return "";}
	if(attribute.compare("")==0){return "";}
    pugi::xml_node node = doc.child("JWM").find_child_by_attribute(element.c_str(),attribOfEle.c_str(),value.c_str());
    debug_out(node.name());
    //.child(subelement.c_str());
    std::string stringie="";
    if(!node){//TODO
		debug_out("TODO: fix this");
		//node=checkIncludes(element,subelement);}
	}
	for(node=node.child(subelement.c_str());node;node=node.next_sibling(subelement.c_str())){
		std::string tmpTXT=node.text().as_string();
		if(tmpTXT.compare(text)==0){stringie = node.attribute(attribute.c_str()).as_string();}
	}
    debug_out("result="+stringie);
    return stringie;
}
std::string getElementAttribute(std::string element, std::string subelement, std::string SUBsubsubelement, std::string attribute){
	debug_out("std::string getElementAttribute(std::string "+element +", std::string  "+  subelement+ ", std::string  "+ SUBsubsubelement+", std::string  " +attribute+")");
	if(element.compare("")==0){return "";}
	if(subelement.compare("")==0){return "";}
	if(SUBsubsubelement.compare("")==0){return "";}
	if(attribute.compare("")==0){return "";}
    pugi::xml_node node = doc.child("JWM").child(element.c_str()).child(subelement.c_str()).child(SUBsubsubelement.c_str());
    std::string stringie="";
    if(!node){node=checkIncludes(element,subelement,SUBsubsubelement);}
    if(node){stringie = node.attribute(attribute.c_str()).as_string();}
    debug_out("result="+stringie);
    return stringie;
}
std::string getElementAttribute(unsigned int whichElement,std::string element, std::string subelement, std::string attribute){
	unsigned int i=1;
    pugi::xml_node node = doc.child("JWM").child(element.c_str());
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    if(!node){node=checkIncludes(whichElement,element);}
    node=node.child(subelement.c_str());
	if(!node){return "";}
    return node.attribute(attribute.c_str()).as_string();
}
std::string getElementAttribute(unsigned int whichElement,std::string element, std::string attribute){
unsigned int i=1;
    pugi::xml_node node = doc.child("JWM").child(element.c_str());
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    if(!node){node=checkIncludes(whichElement,element);}
    return node.attribute(attribute.c_str()).as_string();
}
std::string getElementAttribute(unsigned int whichElement,std::string element,unsigned int whichItem, std::string subelement, std::string attribute){
	unsigned int i=1;
    pugi::xml_node node = doc.child("JWM").child(element.c_str());
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    if(!node){node=checkIncludes(whichElement,element);}
    node=node.child(subelement.c_str());
    i=1;
    if(whichItem!=i){
		while(node.next_sibling(subelement.c_str()) && i!=whichItem){
            node=node.next_sibling(subelement.c_str());
            i++;
        }
    }
    if(!node){return "";}
    return node.attribute(attribute.c_str()).as_string();
}
std::string getEQUALvalue(std::string INTERNAL_LINE){
	std::string subString;
	unsigned int found =INTERNAL_LINE.find("=");
	if(found < INTERNAL_LINE.length()){
		subString=INTERNAL_LINE.substr(found+1,std::string::npos);
		return subString;
	}
	return "";
}
std::string getFirstColor(std::string element, std::string subelement){
	std::string val=getElementText(element,subelement);
	return splitColor(1,val);
}
std::string getItemText(pugi::xml_node node){return node.text().as_string();}
std::string getJSMItem(std::string item){
	//debug_out("std::string getJSMItem(std::string "+item+")");
	if(item.compare("")==0){return "";}
	std::string filename=linuxcommon::home_path();
	if(filename.compare("")==0){return "";}
	filename+=".jsm";
	//debug_out("Filename="+filename);
	if(!linuxcommon::test_file(filename)){
		std::string defaultFile="panel=1\ndebug=false\nfile="+homePath()+"\n";
		//debug_out(filename+" does not seem to be a file");
		if(!linuxcommon::save_string_to_file(defaultFile,filename)){
			//debug_out("could not write default config file:"+filename);
			return "";
		}
	}
	//debug_out("item="+item);
	item+="=";
	std::string result = linuxcommon::get_line_with_equal(filename,item);
	if(result.compare("")==0){
		errorOUT("Could not get "+item+" from "+filename);
		return "";
	}
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}
std::string getLayoutThing(std::string attribute,std::string value1,std::string value2,std::string value3,std::string layout){
	debug_out("std::string getLayoutThing(std::string "+attribute+",std::string "+value1+",std::string "+value2+",std::string "+value3+",std::string "+layout+")");
	std::string subelement="Tray";
	pugi::xml_node node=doc.child("JWM").child(subelement.c_str());
	if(!node){node=checkIncludes(subelement.c_str());}
	std::list<std::string> layouts;
	int Iter=0;
	for(node=node;node;node=node.next_sibling(subelement.c_str())){
		if(node.attribute(attribute.c_str())){
			layouts.push_back(node.attribute(attribute.c_str()).as_string());
			Iter++;
		}
	}
	int fixed = 0, left = 0, right = 0, center = 0;
	for (std::list<std::string>::iterator it = layouts.begin(); it != layouts.end(); ++it){
		std::string layout=*it;
		if(layout.compare(value1)==0)fixed++;
		else if(layout.compare(value2)==0)left++;
		else if(layout.compare(value3)==0)right++;
		else center++;
	}
	std::string smartieAlign;
	//HORIZONTAL
	if(attribute.compare("halign")==0){
		if(layout.compare("horizontal")==0){
			if (((left+right+center)<=1)&&(fixed<=1)){smartieAlign =value1;}
			else if (((left+right)<=1)&&(fixed<1)){smartieAlign =value1;}
			else if (((left+center)<=1)&&(fixed<1)){smartieAlign =value1;}
			else if (((right+center)<=1)&&(fixed<1)){smartieAlign =value1;}
			else{smartieAlign ="center";}
		}
		else{
			if (left==0){smartieAlign =value2;}
			else if ((left==1)&&(fixed+right==0)){smartieAlign =value3;}
			else{smartieAlign =value1;}
		}
    }
    else{
		//VERTICAL
		if(layout.compare("horizontal")==0){
			if ((left==1)&&((right+fixed)==0)){smartieAlign ="bottom";}
			else if ((left==0)&&((right+fixed)==1)){smartieAlign ="top";}
			else{smartieAlign ="fixed";}
		}
		else if(layout.compare("vertical")==0){
			//this is our vertical Tray, since it can only be vertical or horizontal
			//so we pretty much only want fixed....
			if (fixed>=3){smartieAlign ="center";}
			else{smartieAlign ="fixed";}
		}
		else{
			debug_out("Not vertical or horizontal??");
			smartieAlign="fixed";
		}
    }
	return smartieAlign;
}
std::string getMenuAttribute(std::string MENU, std::string attribute){
	pugi::xml_node thisNODE=getMenu(MENU);
	std::string thisATTRIB=thisNODE.attribute(attribute.c_str()).as_string();
	return thisATTRIB;
}
std::string getMenuAttribute(int MENU, int subitem, std::string element, std::string attribute){
	pugi::xml_node node=getNode(MENU,"RootMenu",subitem,element);
	std::string thisATTRIB=node.attribute(attribute.c_str()).as_string();
	return thisATTRIB;
}
std::string getPanelButtonIcon(){
	//TODO make this look at ALL of them.
	debug_out("std::string getPanelButtonIcon()");
	std::string result=getElementAttribute("Tray","TrayButton","icon");
	debug_out("Icon="+result);
	if(!linuxcommon::test_file(result)){
		std::vector<std::string> iconity=IconPaths();
		result=linuxcommon::test_file_in_vector_path(result,iconity);
	}
	return result;
}
std::string getRootMenuAttribute(int MENU, std::string attribute){
	debug_out("std::string getRootMenuAttribute(int MENU, std::string "+attribute+")");
	pugi::xml_node node=getMenu(MENU);
	return getAttribute(node,attribute);
}
std::string getSecondColor(std::string element, std::string subelement){
	std::string val=getElementText(element,subelement);
	return splitColor(2,val);
}
std::string getSmartHoriz(std::string layout){return getLayoutThing("halign","fixed","left","right",layout);}
std::string getSmartVert(std::string layout){return getLayoutThing("valign","fixed","top","bottom",layout);}
std::string getSmartLayout(){
	debug_out("std::string getSmartLayout()");
    std::string smartiePosition ="";
    std::string layout;
    std::string subelement="Tray";
	pugi::xml_node node=doc.child("JWM").child(subelement.c_str());
	if(!node){node=checkIncludes(subelement.c_str());}
	std::list<std::string> layouts;
	int Iter=0;
	std::string attribute="layout";
	for(node=node;node;node=node.next_sibling(subelement.c_str())){
		if(node.attribute(attribute.c_str())){
			layouts.push_back(node.attribute(attribute.c_str()).as_string());
			Iter++;
		}
	}
	int v1 = 0, v2 = 0, v3 = 0;
	for (std::list<std::string>::iterator it = layouts.begin(); it != layouts.end(); ++it){
		std::string layout=*it;
		if(layout.compare("horizontal")==0)v1++;
		else if(layout.compare("vertical")==0)v2++;
		else{v3++;}
	}
    //call horizontalORvertical to figure out which one to pick.
    smartiePosition = horizontalORvertical(v1,v2);
    return smartiePosition;
}
//H
std::string homePath(){
	std::string filename = linuxcommon::home_path();
	if(filename.compare("")==0){return filename;}
	else{
		filename+=".jwmrc";
	}
	//debug_out("std::string homePath() RETURNS "+filename );
	return filename;
}
std::string horizontalORvertical(int horizontalValue, int verticalValue){
	debug_out("std::string horizontalORvertical(int horizontalValue, int verticalValue)");
    std::string horizontal = "horizontal";
    std::string vertical= "vertical";
    /*
    if there are:

    0 horiz                     make the next horizontal
    1 horiz 0 vert              make the next horizontal
    1 vert 1 horiz              make the next horizontal
    2 vert 1 horiz              make the next horizontal

    2 horiz 0 vert              make the next vertical
    1 vert 2 horiz              make the next vertical
    anything else... just center it

    Basically I want to preferr Horizontal, because people are used to it.
    */
    if((horizontalValue == 0)){return horizontal;}
    else if((horizontalValue ==1)&&(verticalValue == 0)){return horizontal;}
    else if((horizontalValue==2) && (verticalValue == 0)){return vertical;}
    else if((verticalValue==1) && (horizontalValue == 1)){return horizontal;}
    else if((verticalValue==2) && (horizontalValue == 1)){return horizontal;}
    else if((verticalValue==1) && (horizontalValue == 2)){return vertical;}
    else {return "center";}
}
//J
std::string joinColors(const double* rgb, const double* rgb2){
	std::string color1=colorToString(rgb);
	std::string color;
	if(rgb2!=NULL){
        std::string color2 = colorToString(rgb2);
        color = color1 + ":" + color2;
        debug_out("std::string joinColors(const double* rgb, const double* rgb2) RETURNS "+color);
        return color;
    }
    else{
		debug_out("std::string joinColors(const double* rgb, const double* rgb2) RETURNS "+color1);
		return color1;
	}
    debug_out("std::string joinColors(const double* rgb, const double* rgb2) RETURNS the default... #000000");
    //just return black, because 'Good guys wear Black' right???
    return "#000000";
}
//M
std::string makeTempName(std::string filename){
	if(filename.find("~")<filename.length()){return filename;}
	filename+="~";
	return filename;
}
std::string makeNOTtemp(std::string filename){
	unsigned int find=filename.find("~");
	std::string tmp=filename;
	if(find==filename.length()-1){tmp=tmp.erase(find,std::string::npos);}
	return tmp;
}
std::string menuButtonText(pugi::xml_node node){
	debug_out("std::string menuButtonText(pugi::xml_node node)");
	if(!node){errorOUT("Button node was not found");return "";}
	return node.text().as_string();
}
//S
std::string splitColor(unsigned int first_or_second, std::string HTMLcolor){
	debug_out("std::string splitColor(unsigned int first_or_second, std::string "+HTMLcolor+")");
	std::string color=HTMLcolor;
	unsigned int found=color.find(":");
	if(found>color.length()){
		if((first_or_second==1)&&(HTMLcolor.compare("")!=0)){
			debug_out("String does not contain 2 Colors.. returning it to you, hopefully you only wanted one color, and this is a color");
			return HTMLcolor;
		}
		if(HTMLcolor.compare("")==0){
			debug_out("The string you sent in  is blank");
			return "";
		}
		else{
			debug_out("There is No second color.... :(");
			return "";
		}
	}
	if(first_or_second==1){
		color=color.erase(found,std::string::npos);
		debug_out("First Color="+color);
	}
	else{
		color=color.erase(0,found+1);
		debug_out("Second Color="+color);
	}
	return color;
}
//T
std::string terminal(std::string terminal){return linuxcommon::term_out(terminal);}
//Const char*
const char* convert(double num){
	return linuxcommon::convert_num_to_string(num);
}
//unsigned int//////////////////////////////////////////////////////////
//c
unsigned int convert(const char* num){
	if(num==NULL){return 0;}
	return linuxcommon::convert_string_to_number(num);
}
unsigned int currentPanel(){
	debug_out("unsigned int currentPanel()");
    std::string panel=getJSMItem("panel");
    if(panel.compare("")==0)panel="1";
    debug_out("unsigned int currentPanel()->"+panel);
    return linuxcommon::convert_string_to_number(panel.c_str());
}
//e
unsigned int elementCounter(std::string element){
	pugi::xml_node node=doc.child("JWM").child(element.c_str());
	//TODO count includes
    if(!node){return 0;}
    unsigned int i=1;
	while(node.next_sibling(element.c_str())){
            node=node.next_sibling(element.c_str());
            i++;
    }
    return i;
}
//f
unsigned int flCOLOR(std::string color){
	debug_out("unsigned int flCOLOR(std::string "+color + ")");
	return linuxcommon::get_fl_color(color);
}
unsigned int flCOLOR(std::string color, unsigned int &c){
debug_out("unsigned int flCOLOR(std::string "+color + ", unsigned int &c)");
	return linuxcommon::get_fl_color(color, c);
}
//g
unsigned int getActiveBackground(unsigned int c,std::string element){
	debug_out("unsigned int getActiveBackground(unsigned int c,std::string "+element+")");
	std::string color=getElementText(element,"Active","Background");
	unsigned int retval=flCOLOR(color,c);
	return retval;
}
unsigned int getActiveForeground(unsigned int c,std::string element){
	debug_out("unsigned int getActiveBackground(unsigned int c,std::string "+element+")");
	std::string color=getElementText(element,"Active","Foreground");
	unsigned int retval=flCOLOR(color,c);
	return retval;
}
unsigned int getBackground(unsigned int c,std::string element){
	debug_out("unsigned int getBackground(unsigned int c,std::string "+element+")");
	std::string color=getElementText(element,"Background");
	unsigned int retval=flCOLOR(color,c);
	return retval;
}
unsigned int getElementInt(std::string element){
	debug_out("unsigned int getElementInt(std::string "+element + ")");
	//if(!loadTemp()){return false;}
	if(element.compare("")==0){return 0;}
    pugi::xml_node node = doc.child("JWM").child(element.c_str());
    unsigned int stringie=0;
    if(!node){node=checkIncludes(element);}
    if(node){stringie = node.text().as_uint();}
    return stringie;
}
unsigned int getElementInt(std::string element, std::string subelement){
	debug_out("unsigned int getElementInt(std::string "+element + ", std::string " + subelement+ ")");
	//if(!loadTemp()){return false;}
	if(element.compare("")==0){return 0;}
	if(subelement.compare("")==0){return 0;}
    pugi::xml_node node = doc.child("JWM").child(element.c_str()).child(subelement.c_str());
    unsigned int stringie=0;
    if(!node){node=checkIncludes(element,subelement);}
    if(node){stringie = node.text().as_uint();}
    return stringie;
}
unsigned int getElementInt(std::string element, std::string subelement, std::string SUBsubsubelement){
	//if(!loadTemp()){return false;}
	debug_out("unsigned int getElementInt(std::string "+element + ", std::string " + subelement+ ", std::string " + SUBsubsubelement+")");
	if(element.compare("")==0){return 0;}
	if(subelement.compare("")==0){return 0;}
	if(SUBsubsubelement.compare("")==0){return 0;}
    pugi::xml_node node = doc.child("JWM").child(element.c_str()).child(subelement.c_str()).child(SUBsubsubelement.c_str());
    unsigned int stringie=0;
    if(!node){node=checkIncludes(element,subelement,SUBsubsubelement);}
    if(node){stringie = node.text().as_uint();}
    return stringie;
}
unsigned int getFontColor(unsigned int c,std::string element){
	debug_out("unsigned int getFontColor(unsigned int c,std::string "+element+")");
	std::string color=getElementText(element,"Foreground");
	unsigned int retval=flCOLOR(color,c);
	return retval;
}
//n
unsigned int numPanels(){return elementCounter("Tray");}
//s
unsigned int splitColor(std::string color, int one_or_two){
	debug_out("unsigned int splitColor(std::string "+ color+ ", int one_or_two)");
	std::string choice ="";
	if(color.compare("")==0){return flCOLOR("#000000");}
	unsigned int found=color.find(":");
	if(found>color.length()){return flCOLOR(color);}
	if(one_or_two==1){choice=color.erase(found,std::string::npos);}
	else{choice=color.erase(0,found+1);}
	return flCOLOR(choice);
}
unsigned int switch_panel(Fl_Menu_Item *o){
	debug_out("unsigned int switch_panel(Fl_Menu_Item *o)");
	unsigned int whichPanel = o->value();
	return whichPanel;
}
//int///////////////////////////////////////////////////////////////////
int addMenuItem(Fl_Browser* root_menu, Fl_Input* add_label, Fl_Input* add_icon, Fl_Input* add_input, Fl_Input* add_tooltip, Fl_Check_Button* add_button, std::string result){
	debug_out("int addMenuItem(Fl_Browser* root_menu, Fl_Input* add_label, Fl_Input* add_icon, Fl_Input* add_input, Fl_Input* add_tooltip, Fl_Check_Button* add_button, std::string "+result+")");
	if(result.compare("")==0){
		errorOUT("Nothing to add..");
		return -1;
	}
	int whichMenu=root_menu->value();
	if((whichMenu>root_menu->size())||whichMenu<0){
		errorOUT("No root menu item chosen");
		return -1;
	}
	if(result.compare("Separator")==0){
		if(!addMenuElement(whichMenu,result)){return 1;}
		return 0;
	}
	const char* lbl = add_label->value();
	const char* icon = add_icon->value();
	const char* input = add_input->value();
	const char* tooltip = add_tooltip->value();
	if(!addMenuElement(whichMenu,result)){return 1;}
	if(result.compare("Include")==0){
		if(input!=NULL){
			if(!setNodeText(getLastSubNode(whichMenu,"RootMenu",result),input)){
				errorOUT("Could not set the text");
			}
			else{return 0;}
		}
		return -1;		
	}
	int retval = addMenuAttrib(whichMenu,result,"label",lbl);
	if(retval==-1){errorOUT("Couldn't set label");}
	retval = addMenuAttrib(whichMenu,result,"icon",icon);
	if(retval==-1){errorOUT("Couldn't set icon");}
	retval = addMenuAttrib(whichMenu,result,"tooltip",tooltip);
	if(retval==-1){errorOUT("Couldn't set tooltip");}
	int button = add_button->value();
	std::string labled="false";
	if(button==1){labled="true";}
	std::string attrib;
	if(result.compare("Exit")==0){attrib="confirm";}
	if((result.compare("Menu")==0)||(result.compare("Dynamic")==0)){attrib="labeled";}
	if(attrib.compare("")!=0){
		retval = addMenuAttrib(whichMenu,result,attrib,labled.c_str());
	}
	return -1;
}
int addMenuAttrib(int whichMenu,std::string element,std::string attribute,const char *value){
	debug_out("int addMenuAttrib(int whichMenu,std::string "+element+",std::string "+attribute+",const char *value)");
	if(value==NULL){
		debug_out("attribute value was non existant");
		return 1;
	}
	if(!setAttribute(getLastSubNode(whichMenu,"RootMenu",element),attribute,value)){
		return -1;
	}
	return 0;
}
int getIntAttribute(std::string element, std::string attribute){
	if(element.compare("")==0){return 0;}
	if(attribute.compare("")==0){return 0;}
    pugi::xml_node node = doc.child("JWM").child(element.c_str());
    if(!node){node=checkIncludes(element);}
    unsigned int stringie=0;
    if(node){stringie = node.attribute(attribute.c_str()).as_uint();}
    return stringie;
}
int getIntAttribute(std::string element, std::string subelement, std::string attribute){
	if(element.compare("")==0){return 0;}
	if(attribute.compare("")==0){return 0;}
    pugi::xml_node node = doc.child("JWM").child(element.c_str()).child(subelement.c_str());
    if(!node){node=checkIncludes(element,subelement);}
    unsigned int stringie=0;
    if(node){stringie = node.attribute(attribute.c_str()).as_uint();}
    return stringie;
  }
int newStyle(){
	debug_out("int newStyle()");
    const char* tray = "TrayButtonStyle";
    const char* task = "TaskListStyle";
    const char* pager = "PagerStyle";
    const char* win = "WindowStyle";
    const char* menu = "MenuStyle";
    std::vector<std::string> styles;
    styles.push_back(task);//0
    styles.push_back(tray);//1
    styles.push_back(menu);//2
    styles.push_back(win);//3
    styles.push_back(pager);//4
    int lengthofStyle = 4;//# of entries above from 0
    int i =0; //o is the starting point
    loadTemp();
    //check current if JWM version is >=2.3.0
    bool newVersion = newVersionJWM();
    int not23 = -1; //OLD
    int two30 = 0; // version before removing traybutton/tasklist styles
    int two3later = 1; //2.3.2 ++
    bool testActive = false;
    int totaltester =0;
    for (testActive =isElement(styles[0].c_str()); i<=2;i++){
       testActive =isElement(styles[i].c_str()); //if these exist it is 0 or -1
       if(!testActive){
         totaltester = 1;
       }
    }
    if (totaltester == 1){return two3later;}

    bool active = false;
    bool inActive =false;
    for (testActive =isElement(styles[0].c_str(),"Active"); i<=lengthofStyle;i++){
        testActive=isElement(styles[i].c_str(),"Active");
        if(testActive){active=true;}
        //debug_out("Active "+styles[i]+" is "+testActive);
    }
    i =0;
    for (bool testInactive =isElement(styles[0].c_str(),"Inactive"); i<=lengthofStyle;i++){
        testInactive=isElement(styles[i].c_str(),"Inactive");
        if(testInactive){inActive=true;}
        //debug_out("Active "+styles[i]+" is "+testInactive);
    }
    if(active && !inActive){
        if(!newVersion){
            //do something to let the user know || fix it...
            errorOUT("Something went wrong trying to find your version of JWM");
        }
        debug_out("New Version Support");
        return two30;
    }
    debug_out("OLD Version Support");
    return not23;
}
int JWMversion(){
	std::string command="jwm -v |grep v[0-9] | sed 's/.* v//'|sed 's/ .*//'";
	std::string result=linuxcommon::term_out(command);
	if(result.compare("")==0){result="2.2.0";}
	result=linuxcommon::sed_i(result,".","");
	debug_out("RESULT="+result);
	unsigned int retval =linuxcommon::convert_string_to_number(result.c_str());
	int tmpret=retval;
	return tmpret;
}
int whichAlign(std::string align){
    if(align.compare("top")==0 || align.compare("bottom")==0){return 1;}
    else if(align.compare("left")==0 || align.compare("right")==0){return 2;}
    else {return 3;}
}
//float//////////////////////////////////////////////////////////////////
float getElementFloat(std::string element){
	//if(!loadTemp()){return false;}
	debug_out("(std::string "+element + ")");
	if(element.compare("")==0){return 0.0;}
    pugi::xml_node node = doc.child("JWM").child(element.c_str());
    float stringie=0.0;
    if(!node){node=checkIncludes(element);}
    if(node){stringie = node.text().as_float();}
    return stringie;
}
float getElementFloat(std::string element, std::string subelement){
	debug_out("(std::string "+element + ", std::string " + subelement+ ")");
	//if(!loadTemp()){return false;}
	if(element.compare("")==0){return 0.0;}
	if(subelement.compare("")==0){return 0.0;}
    pugi::xml_node node = doc.child("JWM").child(element.c_str()).child(subelement.c_str());
    float stringie=0.0;
    if(!node){node=checkIncludes(element,subelement);}
    if(node){stringie = node.text().as_float();}
    return stringie;
}
float getElementFloat(std::string element, std::string subelement, std::string SUBsubsubelement){
	debug_out("(std::string "+element + ", std::string " + subelement+ ", std::string "+SUBsubsubelement + ")");
	//if(!loadTemp()){return false;}
	if(element.compare("")==0){return 0.0;}
	if(subelement.compare("")==0){return 0.0;}
	if(SUBsubsubelement.compare("")==0){return 0.0;}
    pugi::xml_node node = doc.child("JWM").child(element.c_str()).child(subelement.c_str()).child(SUBsubsubelement.c_str());
    float stringie=0.0;
    if(!node){node=checkIncludes(element,subelement,SUBsubsubelement);}
    if(node){stringie = node.text().as_float();}
    return stringie;
}
float getOpacity(std::string element){return getElementFloat(element);}
#if 0
const double* getBoxColor(Fl_Box*o){
    //unsigned int thisColor = Fl::get_color(o->color());
    //double intermediary=static_cast<double>(thisColor);
    const double* thisdub = 0.0;//const_cast<const double*>(intermediary);
    return thisdub;
}
#endif
//vector//////////////////////////////////////////////////////////////////
std::vector<std::string> AnythingVector(std::string element){
	debug_out("std::vector<std::string> Includes()");
	std::vector<std::string> includeVec;
	for (pugi::xml_node node=doc.child("JWM").child(element.c_str());node;node=node.next_sibling(element.c_str())){
        std::string value  = node.text().as_string();
        if(value.compare("")!=0){
            includeVec.push_back(value);
        }
    }
	return includeVec;
}
std::vector<std::string> IconPaths(){return AnythingVector("IconPath");}
std::vector<std::string> Includes(){return AnythingVector("Include");}
std::vector<std::string> XDGautostart(){
	debug_out("std::vector<std::string> XDGautostart()");
	std::string thisDIR=linuxcommon::find_xdg_config_dir_subdir("autostart");
	debug_out("system XDG config dir:"+thisDIR);
	std::string currentInclude;
	std::vector<std::string> totalVector;
	if(linuxcommon::test_dir(thisDIR)){
		std::vector<std::string> dirs=linuxcommon::get_file_vector(thisDIR,".desktop");
		for(std::vector<std::string>::iterator it = dirs.begin();it!=dirs.end();++it){
			currentInclude=*it;
			if(checkDE(currentInclude)){totalVector.push_back(currentInclude);}
		}
	}
	const char* xdgconf=getenv("XDG_CONFIG_HOME");
	std::string thisXDG;
	if(xdgconf==NULL){
		xdgconf = getenv("HOME");
		std::string thisXDG;
		if (xdgconf != NULL){
			thisXDG = xdgconf;
			thisXDG += "/.config";
		}
	}
	else{thisXDG=xdgconf;}
	thisXDG=thisXDG+"/autostart/";
	debug_out("User XDG config dir: "+thisXDG);
	if(linuxcommon::test_dir(thisXDG)){
		std::vector<std::string> dirs=linuxcommon::get_file_vector(thisXDG,".desktop");
		for(std::vector<std::string>::iterator it = dirs.begin();it!=dirs.end();++it){
			currentInclude=*it;
			if(checkDE(currentInclude)){totalVector.push_back(currentInclude);}
		}
	}
	return totalVector;
}
std::vector<std::string> zoneSubdir(std::string thisDIR){
	debug_out("std::vector<std::string> zoneSubdir(std::string "+thisDIR+")");
	DIR *dir = NULL;
    struct dirent *entryPointer = NULL;
    std::vector<std::string> returnVec;
	dir = opendir(thisDIR.c_str());
	std::string SUBDIRNAME=thisDIR;
	unsigned int finder =SUBDIRNAME.rfind("/");
	if(finder<SUBDIRNAME.length()){SUBDIRNAME=SUBDIRNAME.erase(0,finder+1);}
	SUBDIRNAME+="\\/";
	if (dir!=NULL){
		while ((entryPointer=readdir(dir)) != NULL){
			if ((entryPointer->d_type == DT_DIR)
			&&(entryPointer->d_name[0] != '.')){
				std::string msg="found subdir.. in subdir:";
				msg+=entryPointer->d_name;
				debug_out(msg);
			}//if DIR
			else if((entryPointer->d_type == DT_REG)
			&&(entryPointer->d_name[0] != '.')){
				std::string tmp=SUBDIRNAME;
				tmp+=entryPointer->d_name;
				returnVec.push_back(tmp);
			}
		}
		closedir(dir);
	}
	else{errorOUT("Could not open time zone sub-directory:"+thisDIR);}
	return returnVec;
}
std::vector<std::string> zoneVector(){
	debug_out("std::vector<std::string> zoneVector()");
	DIR *dir = NULL;
	std::vector<std::string> returnVec;
    struct dirent *entryPointer = NULL;
	std::string dirToOpen="/usr/share/zoneinfo/";
	dir = opendir(dirToOpen.c_str());
	if (dir!=NULL){
		while ((entryPointer=readdir(dir)) != NULL){
			if ((entryPointer->d_type == DT_DIR)
			&&(entryPointer->d_name[0] != '.')){
				std::string tmp=dirToOpen;
				tmp+=entryPointer->d_name;
				std::vector<std::string> tmpVec=zoneSubdir(tmp);
				returnVec=linuxcommon::join_string_vectors(returnVec,tmpVec);
			}//if DIR
			else if((entryPointer->d_type == DT_REG)
			&&(entryPointer->d_name[0] != '.')){
				std::string tmp=entryPointer->d_name;
				returnVec.push_back(tmp);
			}
		}
		closedir(dir);
	}
	else{errorOUT("Could not open time zone directory");}
	returnVec=linuxcommon::sort_array(returnVec);
	return returnVec;
}
//void//////////////////////////////////////////////////////////////////
//A
void addCursorsToBrowser(Fl_Browser *o){
	debug_out("void addCursorsToBrowser(Fl_Browser *o)");
	o->clear();
    std::vector<std::string> cursors;
	std::vector<std::string> mypaths=linuxcommon::split_paths("XDG_DATA_DIRS","/usr/share");
	std::string home=linuxcommon::home_path();
	if(linuxcommon::test_dir(home)){
		home+=".";
		mypaths.push_back(home);
	}
	for(std::vector<std::string>::iterator it=mypaths.begin();it!=mypaths.end();++it){
		std::string thisDIR=*it;
		debug_out("Checking: "+thisDIR);
		thisDIR+="icons/";
		std::string temp=linuxcommon::look_for_file_in_subdirs("cursor.theme", thisDIR);
		if(temp.compare("")!=0){
			debug_out("found cursor.theme in: "+temp);
			cursors=linuxcommon::comma_vector(temp,cursors);
		}
	}
	std::string temp=linuxcommon::look_for_file_in_subdirs(".theme", "/etc/X11");
	if(temp.compare("")!=0){
		debug_out("Found theme file in: "+temp);
		cursors=linuxcommon::comma_vector(temp,cursors);
	}
	for(std::vector<std::string>::iterator it=cursors.begin();it!=cursors.end();++it){
		std::string thisDIR=*it;
		thisDIR=linuxcommon::remove_cruft(thisDIR,"cursor.theme");
		thisDIR=linuxcommon::remove_cruft(thisDIR,".theme");
		if(thisDIR.rfind("/")==thisDIR.length()-1){thisDIR.erase(thisDIR.length()-1,std::string::npos);}
		std::cout<<thisDIR<<std::endl;
		o->add(thisDIR.c_str());
	}	
}
//C
void cancel(){
  debug_out("Cancel");
  load();
  saveChangesTempOverwrite();
  quit();
}
void changeElementText(std::string element,std::string text,std::string NEWTEXT){
	if(element.compare("")==0){return;}
	pugi::xml_node node =doc.child("JWM").child(element.c_str());
	if(!node){node=checkIncludes(element);}
	if(!node){return;}
	for (pugi::xml_node node2=node.child(element.c_str());node2;node2=node.next_sibling(element.c_str())){
		std::string value  = node2.text().as_string();
		if(value.compare(text)==0){
			node2.text().set(NEWTEXT.c_str());
		}
    }
    if(!saveChangesTemp()){debug_out("void changeElementText(std::string "+element+",std::string "+text+",std::string "+NEWTEXT+") failed to save");}
}
//D
void debug_out(std::string msg){
	#ifdef DEBUG
	linuxcommon::echo_error(msg);
	#else
	if(getJSMItem("debug").compare("true")==0){linuxcommon::echo_error(msg);}
	#endif
}
void deletePanelItem(int whichElement){
	debug_out("void deletePanelItem(int whichElement)");
	pugi::xml_node node=getCurrentTrayNode();
	if(!node){debug_out("Tray does not exist");}
	node=node.first_child();
	
	int i=1;
	if(whichElement!=i){
		while(node.next_sibling() && i!=whichElement){
            i++;
            node=node.next_sibling();
        }
    }
    else{
		debug_out("The selected node is at the top, and cannot be moved up");
		return;
	}
	if(node){
		pugi::xml_node basenode=node.parent();
		std::string msg="Remove Node=";
		msg+=node.name();
		debug_out(msg);
		basenode.remove_child(node);
	}
	else{debug_out("Node not found...");}
	saveChangesTemp();
}
void deleteShortcut(std::string program){
	debug_out("void deleteShortcut(std::string "+program+")");
	std::string element="Tray";
	pugi::xml_node node =doc.child("JWM").child(element.c_str());
	if(!node){node=checkIncludes(element);}
	unsigned int whichElement=currentPanel();
	unsigned int i=1;
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    std::string button="Button";
    if(!node){node=checkIncludes(whichElement,element);}
    for (node=node.child("TrayButton");node;node=node.next_sibling("TrayButton")){
		std::string add_text=node.text().as_string();
		pugi::xml_node buttonnode=node.child(button.c_str());
		if(buttonnode){
			for(buttonnode=node.child(button.c_str());buttonnode;buttonnode=buttonnode.next_sibling(button.c_str())){
				std::string temp2=buttonnode.text().as_string();
				if(temp2.compare(program)==0){
					doc.remove_child(node);
					saveChangesTemp();
					return;
				}
			}
		}
		else{
			if(add_text.compare(program)==0){
				doc.remove_child(node);
				saveChangesTemp();
				return;
			}
		}	
	}
}
//E
void errorOUT(std::string msg){
	std::string lines="\n";
	#ifdef DEBUG
	lines+="----------------\n";
	#endif
	linuxcommon::echo_error(lines+msg+lines);
}
void getShortcuts(Fl_Browser*o){
	debug_out("void getShortcuts(Fl_Browser*o)");
	o->clear();
	std::string element="Tray";
	pugi::xml_node node =doc.child("JWM").child(element.c_str());
	if(!node){node=checkIncludes(element);}
	unsigned int whichElement=currentPanel();
	unsigned int i=1;
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    std::string button="Button";
    if(!node){node=checkIncludes(whichElement,element);}
    for (node=node.child("TrayButton");node;node=node.next_sibling("TrayButton")){
		std::string add_text=node.text().as_string();
		pugi::xml_node buttonnode=node.child(button.c_str());
		if(buttonnode){
			for(buttonnode=node.child(button.c_str());buttonnode;buttonnode=buttonnode.next_sibling(button.c_str())){
				std::string temp2=buttonnode.text().as_string();
				if((temp2.compare("")!=0)&&(temp2.find("exec:")<temp2.length())){o->add(temp2.c_str());}
			}
		}
		else{
			if((add_text.compare("")!=0)&&(add_text.find("exec:")<add_text.length())){o->add(add_text.c_str());}
		}	
	}
	o->redraw();
}
//L
void listAutostartXDG(Fl_Browser *o){
	debug_out("void listAutostartXDG(Fl_Browser *o)");
	std::vector<std::string> myVec=XDGautostart();
	std::string currentInclude;
	o->clear();
	for(std::vector<std::string>::iterator it = myVec.begin();it!=myVec.end();++it){
		currentInclude=*it;
		o->add(currentInclude.c_str());
	}
	o->redraw();
}
//M
void moveDown(int whichElement){
	debug_out("void moveDown( int whichone)");
	pugi::xml_node node=getCurrentTrayNode();
	if(!node){debug_out("Tray does not exist");}
	pugi::xml_node basenode=getCurrentTrayNode();
	node=node.first_child();
	int i=1;
	if(whichElement!=i){
		while(node.next_sibling() && i!=whichElement){
            i++;
            node=node.next_sibling();
        }
    }
	pugi::xml_node nodeparser=node.next_sibling();
	basenode.insert_move_after(node,nodeparser);
	saveChangesTemp();
}
void moveUp(int whichElement){
	debug_out("void moveUp( int whichone)");
	pugi::xml_node node=getCurrentTrayNode();
	if(!node){debug_out("Tray does not exist");}
	pugi::xml_node basenode=getCurrentTrayNode();
	node=node.first_child();
	int i=1;
	if(whichElement!=i){
		while(node.next_sibling() && i!=whichElement){
            i++;
            node=node.next_sibling();
        }
    }
    else{
		debug_out("The selected node is at the top, and cannot be moved up");
		return;
	}
	pugi::xml_node nodeparser=node.previous_sibling();
	basenode.insert_move_before(node,nodeparser);
	saveChangesTemp();
}
//P
void populateApps(Fl_Browser*o){
	debug_out("void populateApps(Fl_Browser*o)");
	o->clear();
	std::string element="Tray";
	pugi::xml_node node =doc.child("JWM").child(element.c_str());
	unsigned int whichElement=currentPanel();
	unsigned int i=1;
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    if(!node){checkIncludes(whichElement,element);}
    std::string RUNNINGAPPLIST=gettext("Running App List");
	std::string INDICATORS=gettext("Indicators");
	std::string CLOCK=gettext("Clock");
	std::string SWALLOW=gettext("Swallow");
	std::string MENU=gettext("Menu");
	std::string DESKSWITCH=gettext("Desktop Switcher");
	std::string LAUNCHER=gettext("Launcher");
	std::string SPACER=gettext("Spacer");
    for (node=node.first_child();node;node=node.next_sibling()){
		std::string text=node.name();
		std::string add_text;
		std::string temp=node.text().as_string();
		if(text.compare("TrayButton")==0){
			std::string button="Button";
			pugi::xml_node buttonnode=node.child(button.c_str());
			if(buttonnode){
				for(buttonnode=node.child(button.c_str());buttonnode;buttonnode=buttonnode.next_sibling(button.c_str())){
					std::string temp2=buttonnode.text().as_string();
					debug_out("button node text="+temp2);
					if((temp2.find("root:")<temp2.length())&&(add_text.compare("")==0)){
						add_text=MENU;
						add_text+=" ";
						add_text+=temp2;
					}
					else if(add_text.compare("")==0){
						add_text=LAUNCHER;
						add_text+=" ";
						add_text+=temp2;
					}
				}
			}
			else{
				debug_out("node text="+temp);
				if((temp.find("root:")<temp.length())&&(add_text.compare("")==0)){
					add_text=MENU;
					add_text+=" ";
					add_text+=temp;
				}
				else if(add_text.compare("")==0){
					add_text=LAUNCHER;
					add_text+=" ";
					add_text+=temp;
				}
			}
		}
		else if(text.compare("Pager")==0){add_text=DESKSWITCH;}
		else if(text.compare("TaskList")==0){add_text=RUNNINGAPPLIST;}
		else if(text.compare("Dock")==0){add_text=INDICATORS;}
		else if(text.compare("Swallow")==0){
			add_text=SWALLOW;
			add_text+=" ";
			add_text+=temp;
		}
		else if(text.compare("Clock")==0){add_text=CLOCK;}
		else if (text.compare("Spacer")==0){add_text=SPACER;}
		else{add_text=text;}
		if(add_text.compare("")!=0){o->add(add_text.c_str());}
		add_text="";
	}
	o->redraw();
}
void populateDesc(Fl_Browser *b){
  //see BELOW function to see how I generated this code
    //these are all the descriptions of the options above
    int vernum=JWMversion();
    if(vernum>=236){
    	b->add("Enable auto-maximization. New in v2.3.6.");
	}
    b->add("Enables the border on windows in this group.");
    b->add("Center windows in this group upon initial placement instead of using cascaded placement.");
    b->add("Prevent clients in this group from moving off-screen.");
    b->add("The desktop on which windows in this group will be started.");
    if(vernum>=234){
    	b->add("Do not pass mouse events to the window. Instead, use the mouse to move/resize the window. New in v2.3.4.");
    }
    if(vernum>=235){
        b->add("Fix the windows in this group to the current desktop. This will cause the desktop to change when the window is raised rather than the default behavior of moving the window to the current desktop. New in v2.3.5.");
    }
	b->add("Make windows in this group maximize horizontally by default.");
    b->add("The icon to be used for windows in this group.");
    b->add("Ignore the increment size hint when maximizing windows in this group.");
    b->add("The layer on which windows in this group will be started. Valid ooptions are below, normal, and above.");
    b->add("Make windows in this group maximized.");
    b->add("Make windows in this group minimized.");
    b->add("Disables the border for windows in this group.");
    b->add("Hides the close button for windows in this group.");
    if(vernum>=236){
    	b->add("Disable mod1+drag for moving/resizing windows in this group. New in v2.3.6.");
	}
    b->add("Prevents windows in this group from grabbing the focus when mapped.");
    b->add("Prevents windows in this group from being fullscreen.");
    b->add("Causes the tray to ignore windows in this group.");
    b->add("Disallows maximization for windows in this group.");
    b->add("Disallows minimization for windows in this group.");
    b->add("Prevents windows in this group from being moved.");
    b->add("Causes the pager to ignore windows in this group.");
    b->add("Prevents windows in this group from being resized.");
    b->add("Disallows shading for windows in this group.");
    b->add("Disables the title bar for windows in this group.");
    b->add("Ignore the urgent hint for windows in this group. Without this option set, JWM will flash the border of urgent windows.");
    b->add("Set the opacity for windows in this group. The value is a number between 0.0 and 1.0 inclusive.");
    b->add("Ignore program-specified initial position.");
    b->add("Make windows in this group shaded.");
    b->add("Make windows in this group sticky.");
    b->add("Attempt to tile windows in this group upon initial placement. If tiled placement fails, windows will fall back to cascaded (the default) or centered if specified.");
    b->add("Enables the title bar for windows in this group.");
    b->add("Make windows in this group maximize vertically by default.");
}
void populateOptions(Fl_Browser *o){
      /*I generated this using
    the chart here:
    http://www.joewing.net/projects/jwm/config.shtml#groups

    programming to write a program :P
    there is NO way I'd type this all out, Joe already spent the effort :D

    saving it as a file and running:

    sed -i 's/^/o->add("/' filename
    sed -i 's/$/");/' filename
    sed -i 's# * #");\nb->add("#' filename
    sed  -i s'/\t//' filename
    */
    //this moves b->add to the end of the file for easy copy and paste
    //  sed -i '/^b->add/{H;$!d;s/.*//};$G;s/\n*//' filename

    // I DID delete things after : manually
    // I also added the vernum>=23X portions where the description says New in 2.3.X
    //these are all the options
    int vernum=JWMversion();
    if(vernum>=236){
    	o->add("aerosnap");
    }
	o->add("border");
    o->add("centered");
    o->add("constrain");
    o->add("desktop:");
    if(vernum>=234){
    	o->add("drag");
    }
    if(vernum>=235){
    	o->add("fixed");
	}
    o->add("hmax");
    o->add("icon:");
    o->add("iignore");
    o->add("layer:");
    o->add("maximized");
    o->add("minimized");
    o->add("noborder");
    o->add("noclose");
    if(vernum>=236){
    	o->add("nodrag");
    }
	o->add("nofocus");
    o->add("nofullscreen");
    o->add("nolist");
    o->add("nomax");
    o->add("nomin");
    o->add("nomove");
    o->add("nopager");
    o->add("noresize");
    o->add("noshade");
    o->add("notitle");
    o->add("noturgent");
    o->add("opacity:");
    o->add("pignore");
    o->add("shaded");
    o->add("sticky");
    o->add("tiled");
    o->add("title");
    o->add("vmax");

}
//Q
void quit(){exit(0);}
//R
void removeElement(unsigned int whichMainElement, std::string element,std::string subelement,std::string text){
	debug_out("void removeElement(unsigned int whichMainElement, std::string "+element+",std::string "+subelement+",std::string "+text+")");
	unsigned int i=1;
	if(element.compare("")==0){
		debug_out("Empty variable sent in");
		return;
	}
	if(subelement.compare("")==0){
		debug_out("Empty variable sent in");
		return;
	}
	if(text.compare("")==0){
		debug_out("Empty variable sent in");
		return;
	}
	pugi::xml_node node =doc.child("JWM").child(element.c_str());
	if(!node){node=checkIncludes(element);}
	if(!node){return;}
    if(whichMainElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichMainElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
	for (pugi::xml_node node2=node.child(subelement.c_str());node2;node2=node.next_sibling(subelement.c_str())){
		std::string value  = node2.text().as_string();
		if(value.compare(text)==0){
			node.remove_child(node2);
		}
    }
    if(!saveChangesTemp()){debug_out("Could not save the file");}
}
void removeElement(unsigned int whichMainElement, std::string element){
	unsigned int i=1;
	if(element.compare("")==0){return;}
	pugi::xml_node node =doc.child("JWM").child(element.c_str());
	if(!node){node=checkIncludes(element);}
    if(whichMainElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichMainElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    if(!node){node=checkIncludes(whichMainElement,element);}
    pugi::xml_node main =doc.child("JWM");
    main.remove_child(node);
	if(!saveChangesTemp()){debug_out("Could not save the file");}
}
void removeElement(unsigned int whichMainElement, std::string element,std::string subelement){
	unsigned int i=1;
	if(element.compare("")==0){return;}
	pugi::xml_node node =doc.child("JWM").child(element.c_str()).child(subelement.c_str());
	if(!node){node=checkIncludes(element,subelement);}
    if(whichMainElement!=i){
		while(node.next_sibling(subelement.c_str()) && i!=whichMainElement){
            node=node.next_sibling(subelement.c_str());
            i++;
        }
    }
    pugi::xml_node main =doc.child("JWM").child(element.c_str());
    main.remove_child(node);
	if(!saveChangesTemp()){debug_out("Could not save the file");}
}
void removeElement(std::string subelement,std::string text){
	debug_out("void removeElement(std::string "+subelement+",std::string "+text+")");
	if(subelement.compare("")==0){return;}
	pugi::xml_node node =doc.child("JWM").child(subelement.c_str());
	if(!node){node=checkIncludes(subelement);}
	if(!node){return;}
	node=doc.child("JWM");
	for (pugi::xml_node node2=node.child(subelement.c_str());node2;node2=node.next_sibling(subelement.c_str())){
		std::string value  = node2.text().as_string();
		if(value.compare(text)==0){
			node.remove_child(node2);
		}
    }
    if(!saveChangesTemp()){debug_out("void removeElement(std::string "+subelement+",std::string "+text+") failed to save");}
}
void removeElementCompare2Attr(std::string element, std::string attribute, std::string value, std::string attribute2, std::string value2,std::string text){
	if(element.compare("")==0){return;}
	if(text.compare("")==0){return;}
	pugi::xml_node basenode =doc.child("JWM");
	pugi::xml_node node;
	pugi::xml_node node2;
	//TODO check includes
	if(!basenode){return;}
	std::string Text1,Text2;
	if(
	((attribute.compare("")==0)&&(value.compare("")==0))
	&&((attribute2.compare("")!=0)&&(value2.compare("")!=0))
	){
		node=basenode.find_child_by_attribute(element.c_str(),attribute.c_str(),value.c_str());
		if(node){
			Text1=node.text().as_string();
			node2=basenode.find_child_by_attribute(element.c_str(),attribute2.c_str(),value2.c_str());
			if((Text1.compare(text)==0)&&(node2==node)){
				basenode.remove_child(node);
				if(!saveChangesTemp()){debug_out("Couldn't save the changes..");}
				return;
			}
		}
		
	}
	if((attribute2.compare("")!=0)&&(value2.compare("")!=0)){
		node=node.find_child_by_attribute(element.c_str(),attribute2.c_str(),value2.c_str());
		Text1=node.text().as_string();
		if((node)&&(Text1.compare(text)==0)){
			basenode.remove_child(node);
			if(!saveChangesTemp()){
				debug_out("Couldn't save the changes..");
				return;
			}
		}
	}
	if((attribute.compare("")!=0)&&(value.compare("")!=0)){
		node=node.find_child_by_attribute(element.c_str(),attribute.c_str(),value.c_str());
		Text1=node.text().as_string();
		if((node)&&(Text1.compare(text)==0)){
			basenode.remove_child(node);
			if(!saveChangesTemp()){
				debug_out("Couldn't save the changes..");
				return;
			}
		}

	}
}
void removeXDGautostart(bool NOT, bool ONLY, bool DE, std::string filename, std::string env){
	//TODO
	if(!NOT){
		debug_out("Not NOT");
	}
	if(ONLY){
		debug_out("ONLY");
	}
	
}
//S
void setRootMenuAttribute(std::string menustring ,std::string attribute,std::string value){
	debug_out("void setRootMenuAttribute(std::string "+menustring+", std::string "+attribute+", std::string "+value+")");
	if((menustring.compare("")==0)||(attribute.compare("")==0)||(value.compare("")==0)){
		debug_out("Missing a value");
		return;
	}
	pugi::xml_node node=getRootMenu(menustring);
	if(!node){
		errorOUT("Could not find the menu");
		return;
	}
	pugi::xml_attribute attri=node.attribute(attribute.c_str());
	if(!attri){node.append_attribute(attribute.c_str()).set_value(value.c_str());}
	else{attri.set_value(value.c_str());}
	if(!saveChangesTemp()){errorOUT("Could not save the changes properly");}
}
//U
void under_mouse(Fl_Window *o){
    debug_out("void under_mouse(Fl_Window *o)");
    int screenHeight = Fl::h()/2;
    int screenWidth = Fl::w()/2;
    int window_w = o->decorated_w();
    int window_h = o->decorated_h();
    window_h = window_h/2;
    window_w = window_w/2;
    o->position((screenWidth-window_w),(screenHeight-window_h));
}
//PUGI XML//////////////////////////////////////////////////////////////
//a
pugi::xml_node addNextSubelement(std::string element){
	debug_out("pugi::xml_node addNextSubelement(std::string "+element+")");
	pugi::xml_node node = parseNodes(currentPanel(),element.c_str());
	pugi::xml_node basenode = doc.child("JWM");
	pugi::xml_node newnode;
	if(!node){
		node=checkIncludes(currentPanel(),element.c_str());
		if(node){
			basenode=node.parent();
			newnode=node.insert_child_after(element.c_str(),basenode);
		}
	}
	else{
		basenode=node.parent();
		newnode=node.insert_child_after(element.c_str(),basenode);
	}
	if(!node){
		node=doc.child("JWM");
		newnode=doc.append_child(element.c_str());
	}
	if(!saveChangesTemp()){errorOUT("Did not save the changes to the temporary file");}
	if(!newnode)newnode=parseNodes(currentPanel(),element.c_str());
	return newnode;
}
pugi::xml_node addNode(unsigned int whichElement,std::string element, std::string subelement){
	debug_out("pugi::xml_node addNode(unsigned int whichElement,std::string "+element+", std::string "+subelement+")");
	pugi::xml_node node;
	if(element.compare("")==0){return node;}
	if(subelement.compare("")==0){return node;}
	node=parseNodes(whichElement,element);
    if(!node){
		debug_out("Node not found!");
		return node;
	}
    node.append_child(subelement.c_str());
    node=node.last_child();
    std::string tmpnoder=node.name();
    debug_out("added "+tmpnoder);
    if(node.next_sibling(subelement.c_str())){
		while(node.next_sibling(subelement.c_str())){
			std::string tmpnoder=node.name();
			debug_out("found next "+tmpnoder);
			node=node.next_sibling(subelement.c_str());
		}
    }
    saveChangesTemp();
    return node;
}
//c
pugi::xml_node checkIncludes(unsigned int whichElement,std::string element){
	debug_out("std::string checkIncludes(std::string "+element+")");
	pugi::xml_node node;
	unsigned int i=1;
	if(element.compare("")==0){return node;}
	std::vector<std::string> includeVec=Includes();
	std::string currentInclude ="";
	for(std::vector<std::string>::iterator it = includeVec.begin();it!=includeVec.end();++it){
		currentInclude=*it;
		currentInclude=linuxcommon::sed_i(currentInclude,"$HOME/",linuxcommon::home_path());
		currentInclude=linuxcommon::sed_i(currentInclude,"~/",linuxcommon::home_path());
		unsigned int finder=0;
		finder=currentInclude.find("exec:");
		if(finder<currentInclude.length()){
			std::string command=currentInclude.erase(0,finder+5);//???
			//executable
			if(!linuxcommon::test_exec(command)){debug_out(command+"doesn't exist?");}
			else{
				std::string INCLUDEcontents=linuxcommon::term_out(command);
				if(!doc.load_string(INCLUDEcontents.c_str())){
					debug_out("Error loading contents of "+command);
				}
				else{
					node= doc.child("JWM").child(element.c_str());
					if(whichElement!=i){
						while(node.next_sibling(element.c_str()) && i!=whichElement){
							node=node.next_sibling(element.c_str());
							i++;
						}
					}
				}
			}
		}
		else{
			//load it
			debug_out(currentInclude);
			if(!linuxcommon::test_file(currentInclude)){debug_out(currentInclude+" is neither executable NOR a file???");}
			else{
				load(currentInclude);
				node = doc.child("JWM").child(element.c_str());
				if(whichElement!=i){
					while(node.next_sibling(element.c_str()) && i!=whichElement){
						node=node.next_sibling(element.c_str());
						i++;
					}
				}
			}
		}
	}
	if((node)&&(linuxcommon::test_file(currentInclude))){setJSMItem("file",currentInclude);}
	else{
		loadTemp();
		setJSMItem("file",homePath());
	}
	return node;
}
pugi::xml_node checkIncludes(std::string element){
	debug_out("std::string checkIncludes(std::string "+element+")");
	pugi::xml_node node;
	if(element.compare("")==0){return node;}
	std::vector<std::string> includeVec=Includes();
	std::string currentInclude ="";
	for(std::vector<std::string>::iterator it = includeVec.begin();it!=includeVec.end();++it){
		currentInclude=*it;
		currentInclude=fixHomieInclude(currentInclude);
		unsigned int finder=0;
		finder=currentInclude.find("exec:");
		if(finder<currentInclude.length()){
			std::string command=currentInclude.erase(0,finder+5);//???
			//executable
			if(!linuxcommon::test_exec(command)){debug_out(command+"doesn't exist?");}
			else{
				std::string INCLUDEcontents=linuxcommon::term_out(command);
				if(!doc.load_string(INCLUDEcontents.c_str())){
					debug_out("Error loading contents of "+command);
				}
			}//TODO: pugi load string and look for element.c_str();
		}
		else{
			//load it
			debug_out(currentInclude);
			if(!linuxcommon::test_file(currentInclude)){debug_out(currentInclude+" is neither executable NOR a file???");}
			else{
				if(load(currentInclude)){
					node = doc.child("JWM").child(element.c_str());
				}
			}//TODO: pugi load file and look for element.c_str();
		}
	}
	if((node)&&(linuxcommon::test_file(currentInclude))){setJSMItem("file",currentInclude);}
	else{
		debug_out("checkIncludes didn't find:"+element);

		loadTemp();
		setJSMItem("file",homePath());
	}
	return node;
}
pugi::xml_node checkIncludes(std::string element,std::string subelement){
	debug_out("std::string checkIncludes(std::string "+element+","+subelement+")");
	pugi::xml_node node;
	if(element.compare("")==0){return node;}
	if(subelement.compare("")==0){return node;}
	std::vector<std::string> includeVec=Includes();
	std::string currentInclude ="";
	for(std::vector<std::string>::iterator it = includeVec.begin();it!=includeVec.end();++it){
		currentInclude=*it;
		currentInclude=fixHomieInclude(currentInclude);
		unsigned int finder=0;
		finder=currentInclude.find("exec:");
		if(finder<currentInclude.length()){
			std::string command=currentInclude.erase(0,finder+5);//???
			//executable
			if(!linuxcommon::test_exec(command)){debug_out(command+"doesn't exist?");}
			else{
				std::string INCLUDEcontents=linuxcommon::term_out(command);
				if(!doc.load_string(INCLUDEcontents.c_str())){
					debug_out("Error loading contents of "+command);
				}
				else{node= doc.child("JWM").child(element.c_str()).child(subelement.c_str());}
			}//TODO: pugi load string and look for element.c_str();
		}
		else{
			//load it
			debug_out(currentInclude);
			if(!linuxcommon::test_file(currentInclude)){debug_out(currentInclude+" is neither executable NOR a file???");}
			else{
				if(load(currentInclude)){
					node = doc.child("JWM").child(element.c_str()).child(subelement.c_str());
				}
			}//TODO: pugi load file and look for element.c_str();
		}
	}
	if((node)&&(linuxcommon::test_file(currentInclude))){setJSMItem("file",currentInclude);}
	else{
		loadTemp();
		setJSMItem("file",homePath());
		debug_out("checkIncludes didn't find:"+element+"->"+subelement);

	}
	return node;
}
pugi::xml_node checkIncludes(std::string element,std::string subelement,std::string SUBsubelement){
debug_out("std::string checkIncludes(std::string "+element+","+subelement+","+SUBsubelement+")");
	pugi::xml_node node;
	pugi::xml_node nodeEmpty;
	if(element.compare("")==0){return nodeEmpty;}
	if(subelement.compare("")==0){return nodeEmpty;}
	std::vector<std::string> includeVec=Includes();
	std::string currentInclude ="";
	for(std::vector<std::string>::iterator it = includeVec.begin();it!=includeVec.end();++it){
		currentInclude=*it;
		currentInclude=fixHomieInclude(currentInclude);
		unsigned int finder=0;
		finder=currentInclude.find("exec:");
		if(finder<currentInclude.length()){
			std::string command=currentInclude.erase(0,finder+5);//???
			//executable
			if(!linuxcommon::test_exec(command)){debug_out(command+"doesn't exist?");}
			else{
				std::string INCLUDEcontents=linuxcommon::term_out(command);
				if(!doc.load_string(INCLUDEcontents.c_str())){
					debug_out("Error loading contents of "+command);
				}
				else{node= doc.child("JWM").child(element.c_str()).child(subelement.c_str()).child(SUBsubelement.c_str());}
			}//TODO: pugi load string and look for element.c_str();
		}
		else{
			//load it
			debug_out(currentInclude);
			if(!linuxcommon::test_file(currentInclude)){debug_out(currentInclude+" is neither executable NOR a file???");}
			else{
				if(load(currentInclude)){
					node = doc.child("JWM").child(element.c_str()).child(subelement.c_str()).child(SUBsubelement.c_str());
				}
			}//TODO: pugi load file and look for element.c_str();
		}
	}
	if((node)&&(linuxcommon::test_file(currentInclude))){setJSMItem("file",currentInclude);}
	else{
		debug_out("checkIncludes didn't find:"+element+"->"+subelement+"->"+SUBsubelement);
		loadTemp();
		setJSMItem("file",homePath());
	}
	return node;
}
pugi::xml_node compareNode(std::string element, std::string attribute, std::string value, std::string attribute2, std::string value2,std::string text){
	debug_out("");
	//TODO fix for check includes
	pugi::xml_node basenode =doc.child("JWM");
	pugi::xml_node node;
	pugi::xml_node node2;
	if(element.compare("")==0){return node;}
	if(text.compare("")==0){return node;}
	if(!node){node=checkIncludes(element);}
	if(!node){return node;}
	std::string Text1,Text2;
	if(
	((attribute.compare("")==0)&&(value.compare("")==0))
	&&((attribute2.compare("")!=0)&&(value2.compare("")!=0))
	){
		node=basenode.find_child_by_attribute(element.c_str(),attribute.c_str(),value.c_str());
		if(node){
			Text1=node.text().as_string();
			node2=basenode.find_child_by_attribute(element.c_str(),attribute2.c_str(),value2.c_str());
			if((Text1.compare(text)==0)&&(node2==node)){return node;}
		}
		
	}
	if((attribute2.compare("")!=0)&&(value2.compare("")!=0)){
		node=node.find_child_by_attribute(element.c_str(),attribute2.c_str(),value2.c_str());
		Text1=node.text().as_string();
		if((node)&&(Text1.compare(text)==0)){return node;}
	}
	if((attribute.compare("")!=0)&&(value.compare("")!=0)){
		node=node.find_child_by_attribute(element.c_str(),attribute.c_str(),value.c_str());
		Text1=node.text().as_string();
		if((node)&&(Text1.compare(text)==0)){
			return node;
		}

	}
	return node;
}
//g
pugi::xml_node getCurrentTrayNode(){
	debug_out("pugi::xml_node getCurrentTrayNode()");
	unsigned int whichElement=currentPanel();
	std::string element="Tray";
	pugi::xml_node node=parseNodes(whichElement,element);
    if(!node){node=checkIncludes(whichElement,element);}
    return node;
}
pugi::xml_node getLastSubNode(unsigned int whichElement,std::string element, std::string subelement){
	debug_out("pugi::xml_node getLastSubNode(unsigned int whichElement,std::string "+element+", std::string "+subelement+")");
	pugi::xml_node node;
	if(element.compare("")==0){return node;}
	if(subelement.compare("")==0){return node;}
	node=parseNodes(whichElement,element);
	if(!node.child(subelement.c_str())){
		debug_out("No subelement "+subelement+" found");
		return node;
	}
    node=node.child(subelement.c_str());
    while(node.next_sibling(subelement.c_str())){
		std::string noder=node.name();
		debug_out("getting next "+noder);
		node=node.next_sibling(subelement.c_str());
	}
    return node;
}
pugi::xml_node getMenu(int menu){
	debug_out("pugi::xml_node getMenu(int menu)");
	return parseNodes(menu, "RootMenu");
}
pugi::xml_node getMenu(std::string text){
	debug_out("pugi::xml_node getMenu(std::string "+text+")");
	unsigned int whichElement=currentPanel();
	pugi::xml_node node;
	std::string element="Tray";
	std::string subelement="TrayButton";
	std::string button="Button";
	if(element.compare("")==0){return node;}
	if(subelement.compare("")==0){return node;}
	node =parseNodes(whichElement,element);
	if(!node){return node;}
    if(!node.child(subelement.c_str())){node.append_child(subelement.c_str());}
    node=node.child(subelement.c_str());
    while(node.next_sibling(subelement.c_str())){
		std::string temp=node.text().as_string();
		pugi::xml_node buttonnode=node.child(button.c_str());
		if(buttonnode){
			for(buttonnode=node.child(button.c_str());buttonnode;buttonnode=buttonnode.next_sibling(button.c_str())){
				std::string temp2=buttonnode.text().as_string();
				if(temp2.find(text)<temp2.length()){return node;}
			}
		}
		else{
			if(temp.find(text)<temp.length()){return node;}
		}
		node=node.next_sibling(subelement.c_str());
	}
    return node;
}
pugi::xml_node getMenuButtonByMask(std::string text,int item){
	debug_out("pugi::xml_node getMenuButton(std::string "+text+")");
	std::string button="Button";
	pugi::xml_node node=getTraySubElement(item);
	pugi::xml_node buttonnode=node.child(button.c_str());
	if(buttonnode){
		for(buttonnode=node.child(button.c_str());buttonnode;buttonnode=buttonnode.next_sibling(button.c_str())){
			std::string temp2=buttonnode.attribute("mask").as_string();
			if(temp2.find(text)<temp2.length()){return buttonnode;}
		}
	}
	return node;
}
pugi::xml_node getNode(unsigned int whichElement,std::string element,unsigned int whichNODE){
	unsigned int i=1;
	pugi::xml_node node;
	if(element.compare("")==0){return node;}
	node =doc.child("JWM").child(element.c_str());
	if(!node){node=checkIncludes(element);}
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    node=node.first_child();
    i=1;
    if(whichNODE!=i){
		while(node.next_sibling() && i!=whichNODE){
            node=node.next_sibling();
            i++;
        }
    }
    return node;
}
pugi::xml_node getNode(unsigned int whichElement,std::string element,unsigned int whichNODE, std::string subelement){
	unsigned int i=1;
	pugi::xml_node node;
	if(element.compare("")==0){return node;}
	if(subelement.compare("")==0){return node;}
	node =doc.child("JWM").child(element.c_str());
	if(!node){node=checkIncludes(element);}
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    node=node.child(subelement.c_str());
    if(!node){node=checkIncludes(whichElement,element);}
    i=1;
    if(whichNODE!=i){
		while(node.next_sibling(subelement.c_str()) && i!=whichNODE){
            node=node.next_sibling(subelement.c_str());
            i++;
        }
    }
    return node;
}
pugi::xml_node getRootMenu(std::string text){
	debug_out("pugi::xml_node getRootMenu(std::string "+text+")");
	pugi::xml_node node;
	std::string element="RootMenu";
	if(element.compare("")==0){return node;}
	node=doc.child("JWM").child(element.c_str());
	if(!node)node=checkIncludes(element.c_str());
	std::string docroot=node.attribute(text.c_str()).as_string();
	if(docroot.compare(text)==0){return node;}
    while(node.next_sibling(element.c_str())){
		node=node.next_sibling(element.c_str());
		std::string temp=node.attribute(text.c_str()).as_string();
		if(temp.compare(text)==0)return node;
	}
	pugi::xml_node empty;
    return empty;
}
pugi::xml_node getSubNode(unsigned int whichElement,std::string element,unsigned int whichSubElement, std::string subelement){
	debug_out("pugi::xml_node getSubNode(unsigned int whichElement,std::string "+element+",unsigned int whichSubElement, std::string "+subelement+")");
	unsigned int i=1;
	pugi::xml_node node;
	if(element.compare("")==0){return node;}
	if(subelement.compare("")==0){return node;}
	node=parseNodes(whichElement,element);
    i=1;
    node=node.child(subelement.c_str());
    if(whichSubElement!=i){
		while(node.next_sibling(subelement.c_str()) && i!=whichElement){
			std::string noder=node.name();
			debug_out("getting next "+noder);
            node=node.next_sibling(subelement.c_str());
            i++;
        }
    }
    return node;
}
pugi::xml_node getTraySubElement(unsigned int whichNODE){
	unsigned int i=1;
	pugi::xml_node node=getCurrentTrayNode();
    node=node.first_child();
    i=1;
    if(whichNODE!=i){
		while(node.next_sibling() && i!=whichNODE){
            node=node.next_sibling();
            i++;
        }
    }
    return node;
}
//p
pugi::xml_node parseNodes(unsigned int whichElement,std::string element){
	debug_out("pugi::xml_node parseNodes(unsigned int whichElement,std::string "+element+")");
	unsigned int i=1;
	pugi::xml_node node;
	if(element.compare("")==0){return node;}
	node =doc.child("JWM").child(element.c_str());
	if(!node){node=checkIncludes(element);}
    if(whichElement!=i){
		while(node.next_sibling(element.c_str()) && i!=whichElement){
            node=node.next_sibling(element.c_str());
            i++;
        }
    }
    if(!node){node=checkIncludes(whichElement,element);}
    return node;
}
