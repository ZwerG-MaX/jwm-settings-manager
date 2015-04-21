#include "../include/flKeyboard.h"

flKeyboard::flKeyboard()
{
    tinyxml2::XMLDocument doc;
}

flKeyboard::~flKeyboard()
{
    //dtor
}
void flKeyboard::getKeys(Fl_Browser *o){
    loadTemp();
    const char * output = NULL;
    std::string stringOutput;
    for(const tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("Key");node;node=node->NextSiblingElement("Key")){
        std::string action  = node->GetText();

        if(action.c_str() !=NULL){

            std::string key = node->Attribute("key");

            std::string keyMod ="  ";

            if(node->Attribute("mask")){
                keyMod = node->Attribute("mask");
            }

            if(key.c_str()!=NULL&&keyMod.c_str()!=NULL){
                stringOutput = keyMod + '\t' + key + '\t' + action;
                output = stringOutput.c_str();
                //std::cout<<output<<"\n";//Debug output
                o->add(output);
            }
        }
    }
}

void flKeyboard::addKey(const char * key, const char* shortcut){//setAttribute("Key","key",key,shortcut)
    tinyxml2::XMLElement* element=doc.FirstChildElement("JWM")->LastChildElement("Key");
    tinyxml2::XMLNode *keyboard = element;
    tinyxml2::XMLNode *node = doc.NewElement("Key");
    keyboard->InsertAfterChild(keyboard,node);
    tinyxml2::XMLText *action = doc.NewText(shortcut);
    node->LinkEndChild(action);
    tinyxml2::XMLElement* mod_element=node->ToElement();
    mod_element->SetAttribute("key",key);
    std::cerr<<"shortcut: "<<shortcut<<std::endl;
    saveChangesTemp();
}

///Overload addKey to accept a Modifier ('mask' in JWM terminology)
void flKeyboard::addKey(const char * keyMod, const char * key, const char* shortcut){
//    const char* functionName = "void flKeyboard::addKey(const char * keyMod, const char * key, const char* shortcut)";
    //std::cerr<<functionName<<std::endl;
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

void flKeyboard::deleteKey(const char * keyShortcut){
for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("Key");node;node=node->NextSiblingElement("Key")){
        std::string fromDoc = node->GetText();
        std::string fromProgram = keyShortcut;
        unsigned found = fromProgram.find_last_of("\t");
        fromProgram = fromProgram.erase(0,found+1);
        const char* value  = fromDoc.c_str();
        //std::cout<<"From Program: "<<fromProgram<<" From Document: " <<fromDoc<<'\n';
        if(fromProgram.compare(value) ==0){
            node->DeleteChild(node);
           //std::cout<<"deleted "<<keyShortcut<<std::endl;
        }

    }
    saveChangesTemp();
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
            read( fileno( stdin ), &c, 1 );
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
