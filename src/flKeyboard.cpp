#include "../include/flKeyboard.h"

flKeyboard::flKeyboard(){
#ifdef DEBUG_TRACK
    std::cerr<<"[flKeyboard]->"<<std::endl;
#endif // DEBUG
    tinyxml2::XMLDocument doc;
}

flKeyboard::~flKeyboard(){
#ifdef DEBUG_TRACK
    std::cerr<<"<-[flKeyboard]"<<std::endl;
#endif // DEBUG
}
void flKeyboard::getKeys(Fl_Browser *o){
    loadTemp();
    o->clear();
    const char * output = NULL;
    std::string stringOutput;
    if(!testElement("Key")){
      errorJWM("No Key elements found");
      return;
    }
    for(const tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("Key");node;node=node->NextSiblingElement("Key")){
        std::string action;
        std::string key;
        std::string keyMod ="  ";
        // get key attribute if it exists.. which it should
        if(node->Attribute("key")){key = node->Attribute("key");}
        // get mask attribute if it exists... which it MIGHT
        if(node->Attribute("mask")){keyMod = node->Attribute("mask");}
        if(node->GetText()){
            action  = node->GetText();
            if(DEBUG_ME)std::cout<<"key: "<<key<<" keyMod: "<<keyMod<<" action: "<<action<<std::endl;

            if( (key.compare("")!=0) &&
                (keyMod.compare("")!=0) ){
                stringOutput = keyMod + '\t' + key + '\t' + action;
                output = stringOutput.c_str();
                if(DEBUG_ME)std::cout<<"FOUND KEY: "<<output<<"\n";//Debug output
                o->add(output);
            }
        }
        else{
            if( (key.compare("")!=0) &&
                (keyMod.compare("")!=0) ){
                stringOutput = keyMod + '\t' + key + '\t' + "EMPTY";
                output = stringOutput.c_str();
                if(DEBUG_ME)std::cout<<"FOUND KEY: "<<output<<"\n";//Debug output
                o->add(output);
            }
            std::string msg="[Keyboard] node contains empty ACTION!";
            if(key.compare("")!=0){msg+="  This key is defined: ";msg+=key;}
            if(keyMod.compare("")!=0){msg+="  This key Modifier is defined: ";msg+=keyMod;}
            errorJWM(msg);
        }
    }
    o->redraw();
}

void flKeyboard::addKey(const char * key, const char* shortcut){
//setAttribute("Key","key",key,shortcut)
    if(!testElement("Key")){
        createElement("Key");
    }
    tinyxml2::XMLElement* element=doc.FirstChildElement("JWM")->LastChildElement("Key");
    tinyxml2::XMLNode *keyboard = element;
    tinyxml2::XMLNode *node = doc.NewElement("Key");
    keyboard->InsertAfterChild(keyboard,node);
    tinyxml2::XMLText *action = doc.NewText(shortcut);
    node->LinkEndChild(action);
    tinyxml2::XMLElement* mod_element=node->ToElement();
    mod_element->SetAttribute("key",key);
    if(DEBUG_ME)std::cerr<<"shortcut: "<<shortcut<<std::endl;
    saveChangesTemp();
}

///Overload addKey to accept a Modifier ('mask' in JWM terminology)
void flKeyboard::addKey(const char * keyMod, const char * key, const char* shortcut){
//    const char* functionName = "void flKeyboard::addKey(const char * keyMod, const char * key, const char* shortcut)";
    //std::cerr<<functionName<<std::endl;
    if(!testElement("Key")){
        createElement("Key");
    }
    tinyxml2::XMLNode *base=doc.FirstChildElement("JWM");
    tinyxml2::XMLElement* element=doc.FirstChildElement("JWM")->LastChildElement("Key");
    tinyxml2::XMLNode *newNode = doc.NewElement("Key");
    base->InsertAfterChild(element,newNode);
    tinyxml2::XMLElement* keyboard=newNode->ToElement();
    keyboard->SetAttribute("key",key);
    keyboard->SetAttribute("mask",keyMod);
    keyboard->SetText(shortcut);
    saveChangesTemp();
}
void flKeyboard::configureKey(std::string keyShortcut, std::string newmod1, std::string newmod2, std::string newmod3, std::string newkey, std::string newaction){
    if(DEBUG_ME)std::cout<<"configureKey->"<<std::endl;
    if(DEBUG_ME)std::cout<<"line from program: "<<keyShortcut<<std::endl;
    //if there is nothing... get out quick!!
    if(!testElement("Key")){return;}
    //if the shortcut is null return!!
    if(keyShortcut.compare("")==0){return;}
    std::string mod1FromProg,mod2FromProg,mod3FromProg,keyFromProg,actionFromProg,totalMod,totalNewMod;
    totalNewMod=newmod1+newmod2+newmod3;
    mod1FromProg=getMod1(keyShortcut);
    mod2FromProg=getMod2(keyShortcut);
    mod3FromProg=getMod3(keyShortcut);
    totalMod= mod1FromProg+mod2FromProg+mod3FromProg;
    keyFromProg=getKey(keyShortcut);
    actionFromProg=getAction(keyShortcut);
    const char* modDoc=NULL;
    const char* keyDoc=NULL;
    const char* progDoc=NULL;
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("Key");node;node=node->NextSiblingElement("Key")){
        if(node->GetText()){
            progDoc = node->GetText();
            if(progDoc!=NULL){
                if(DEBUG_ME)std::cout<<"configureKey:: document text="<<progDoc<<std::endl;
                if((actionFromProg.compare(progDoc)==0)){
                    if(node->Attribute("mask")){modDoc=node->Attribute("mask");}
                    if(node->Attribute("key")){keyDoc=node->Attribute("key");}
                    if((modDoc!=NULL)&&(keyDoc!=NULL)){
                        if(DEBUG_ME)std::cout<<"configureKey:: mods="<<modDoc<<std::endl;
                        if((actionFromProg.compare(progDoc)==0)&&(keyFromProg.compare(keyDoc)==0)&&(totalMod.compare(modDoc)==0)){
                            if(DEBUG_ME)std::cout<<"configureKey:: using key:"<<newkey<<" and Action: "<<newaction<<" mods? "<<totalNewMod<<std::endl;
                            if(totalNewMod.compare("")!=0){node->SetAttribute("mask",totalNewMod.c_str());}
                            else{node->DeleteAttribute("mask");}
                            node->SetAttribute("key",newkey.c_str());
                            node->SetText(newaction.c_str());
                            saveChangesTemp();
                            return;
                        }
                    }
                    else if((modDoc==NULL)&&(keyDoc!=NULL)){
                        if(keyFromProg.compare(keyDoc)==0){
                            if(DEBUG_ME)std::cout<<"configureKey:: using key:"<<newkey<<" and Action: "<<newaction<<" mods? "<<totalNewMod<<std::endl;
                            if(totalNewMod.compare("")!=0){
                                node->SetAttribute("mask",totalNewMod.c_str());
                            }
                            node->SetAttribute("key",newkey.c_str());
                            node->SetText(newaction.c_str());
                            saveChangesTemp();
                            return;
                        }
                    }
                }
            }
        }
    }

}
std::string flKeyboard::getMod(std::string keyShortcut){
    if(!testElement("Key")){return "";}
    //if the shortcut is null return nothing!!
    if(keyShortcut.compare("")==0){return "";}
    std::string fromProgram = keyShortcut;
    std::string keymod =keyShortcut;
    //shortcut
    unsigned length =fromProgram.length();
    unsigned found = fromProgram.find_first_of("\t");
    if(found < length){
        keymod = keymod.erase(found,std::string::npos);
        return keymod;
    }
    return "";
}
std::string flKeyboard::getMod1(std::string keyShortcut){
    if(!testElement("Key")){return "";}
    //if the shortcut is null return nothing!!
    if(keyShortcut.compare("")==0){return "";}
    std::string result =getMod(keyShortcut);
    unsigned int len = result.length();
    if(len>1){result=result.erase(1,std::string::npos);}
    if(DEBUG_ME)std::cout<<"mod1:"<<result<<std::endl;
    return result;

}
std::string flKeyboard::getMod2(std::string keyShortcut){
    if(!testElement("Key")){return "";}
    //if the shortcut is null return nothing!!
    if(keyShortcut.compare("")==0){return "";}
    std::string result =getMod(keyShortcut);
    unsigned int len = result.length();
    if(len>1){result=result.erase(0,1);}
    len = result.length();
    if(len>2){result=result.erase(1,std::string::npos);}
    if(DEBUG_ME)std::cout<<"mod2:"<<result<<std::endl;
    return result;
}
std::string flKeyboard::getMod3(std::string keyShortcut){
    if(!testElement("Key")){return "";}
    //if the shortcut is null return nothing!!
    if(keyShortcut.compare("")==0){return "";}
    std::string result =getMod(keyShortcut);
    unsigned int len = result.length();
    if(len>2){result=result.erase(0,2);}
    else{result="";}
    if(DEBUG_ME)std::cout<<"mod3:"<<result<<std::endl;
    return result;
}
std::string flKeyboard::getKey(std::string keyShortcut){
    if(!testElement("Key")){return "";}
    //if the shortcut is null return nothing!!
    if(keyShortcut.compare("")==0){return "";}
    std::string fromProgram = keyShortcut;
    std::string keymod2 =keyShortcut;
    //shortcut
    unsigned length =fromProgram.length();
    unsigned found = fromProgram.find_last_of("\t");
    unsigned found1 = fromProgram.find_first_of("\t");
    unsigned found2 = fromProgram.find_first_of("\t",found1);
    if(found < length){
        fromProgram = fromProgram.erase(0,found+1);
        //keymod 2
        if(found2 < keymod2.length()){
            keymod2 = keymod2.erase(found,std::string::npos);
            keymod2 = keymod2.erase(0,found2+1);
            if(DEBUG_ME)std::cout<<"getKey: "<<keymod2<<std::endl;
            return keymod2;
        }
    }
    return "";
}
std::string flKeyboard::getAction(std::string keyShortcut){
    if(!testElement("Key")){return "";}
    //if the shortcut is null return nothing!!
    if(keyShortcut.compare("")==0){return "";}
    std::string fromProgram = keyShortcut;
    //shortcut
    unsigned length =fromProgram.length();
    unsigned found = fromProgram.find_last_of("\t");
    if(found < length){
        fromProgram = fromProgram.erase(0,found+1);
        if(DEBUG_ME)std::cout<<"getAction: "<<fromProgram<<std::endl;
        return fromProgram;
    }
    return "";
}
void flKeyboard::deleteKey(std::string keyShortcut){
    if(DEBUG_ME)std::cerr<<"deleteKey->"<<std::endl;
    //if there is nothing... get out quick!!
    if(!testElement("Key")){return;}
    //if the shortcut is null return!!
    if(keyShortcut.compare("")==0){return;}
    std::string mod1FromProg,mod2FromProg,mod3FromProg,keyFromProg,actionFromProg,totalMod;
    mod1FromProg=getMod1(keyShortcut);
    mod2FromProg=getMod2(keyShortcut);
    mod3FromProg=getMod3(keyShortcut);
    totalMod= mod1FromProg+mod2FromProg+mod3FromProg;
    keyFromProg=getKey(keyShortcut);
    actionFromProg=getAction(keyShortcut);
    const char* modDoc=NULL;
    const char* keyDoc=NULL;
    const char* progDoc=NULL;
    tinyxml2::XMLElement* base =doc.FirstChildElement("JWM");
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("Key");node;node=node->NextSiblingElement("Key")){
        if(DEBUG_ME)std::cout<<"deleteKey:: looping through elements"<<std::endl;
        if(node->GetText()){
            progDoc = node->GetText();
            if(DEBUG_ME)std::cout<<"deleteKey:: Node text: "<<progDoc<<std::endl;
            if(progDoc!=NULL){
                if(actionFromProg.compare(progDoc)==0){
                    if(node->Attribute("mask")){modDoc=node->Attribute("mask");}
                    if(node->Attribute("key")){keyDoc=node->Attribute("key");}
                    std::string fromProgram = keyShortcut;
                    if(DEBUG_ME)std::cout<<"deleteKey:: input: "<<keyShortcut<<std::endl;
                    if((keyDoc!=NULL)&&(modDoc!=NULL)){
                        if((keyFromProg.compare(keyDoc)==0)&&(totalMod.compare(modDoc)==0)){
                            if(DEBUG_ME)std::cerr<<"deleteKey:: REMOVING: "<<keyShortcut<<std::endl;
                            base->DeleteChild(node);
                            saveChangesTemp();
                            return;
                        }
                    }
                    else if( (keyDoc!=NULL) && (modDoc==NULL) ){
                        if(keyFromProg.compare(keyDoc)==0){
                            if(DEBUG_ME)std::cerr<<"deleteKey:: REMOVING: "<<keyShortcut<<std::endl;
                            base->DeleteChild(node);
                            saveChangesTemp();
                            return;
                        }
                    }
                }
            }
        }
        modDoc=NULL;
        keyDoc=NULL;
        progDoc=NULL;
    }
}

std::string flKeyboard::grabbedKey(){
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
            if(thisread !=0){std::cerr<< "read input command did not return 0"<<std::endl;}
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
