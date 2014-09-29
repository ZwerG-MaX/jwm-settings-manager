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

void flKeyboard::addKey(const char * key, const char* shortcut){
    tinyxml2::XMLNode *keyboard = doc.FirstChildElement("JWM");

    tinyxml2::XMLNode *node = doc.NewElement("Key");
    keyboard->InsertAfterChild(node,node);

    tinyxml2::XMLText *action = doc.NewText(shortcut);
    node->LinkEndChild(action);

    tinyxml2::XMLElement* element=doc.FirstChildElement("JWM")->LastChildElement("Key");
    element->SetAttribute("key",key);
    saveChangesTemp();
}

///Overload addKey to accept a Modifier ('mask' in JWM terminology)
void flKeyboard::addKey(const char * keyMod, const char * key, const char* shortcut){
    addKey(key, shortcut);
    tinyxml2::XMLElement* element=doc.FirstChildElement("JWM")->LastChildElement("Key");
    element->SetAttribute("mask",keyMod);
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

