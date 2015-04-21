#include "../include/flFont.h"

flFont::flFont()
{
    tinyxml2::XMLDocument doc;
    antialias = "antialias";
    weight = "weight";
    slant = "slant";
    spacing = "spacing";
}

flFont::~flFont()
{
    //dtor
}
//Font NAME
std::string flFont::fontTest(const char* whichElement){
    tinyxml2::XMLElement * currentFont = doc.FirstChildElement("JWM")->FirstChildElement(whichElement)->FirstChildElement("Font");
    std::string font ="";
    const char* fontTester = currentFont->GetText();
    if(fontTester!=NULL){
        font=fontTester;
        return font;
    }
    else {
        missingFont(whichElement);
    }
    return NULL;
}
void flFont::missingFont(const char* whichElement){
    tinyxml2::XMLElement * currentFont = doc.FirstChildElement("JWM")->FirstChildElement(whichElement)->FirstChildElement("Font");
    std::cerr<<"The current Element doesn't have a font name or is missing a size.\n Recovering by rewriting default values\n";
    ///TODO member var for default font
    currentFont->SetText("ubuntu-12:antialias=true");
    //getFontName(whichElement);//Is this a good Idea??  Is there a case that can make this loop endlessly?
}
std::string flFont::getFontName(const char* whichElement){
    std::string font =fontTest(whichElement);
    if (font.c_str() != NULL){
        std::string fontName ="";
        std::string::size_type size = font.find_first_of('-');
        if((font.find_last_of('-')!=std::string::npos)){
            fontName = font.substr (0,size);
            //if (fontName !=NULL)
            return fontName;
        }
    }
    else{
        std:: string error = "no font";
        errorJWM("This is an error, there is no font");
        return error;
    }
    errorJWM("ERROR in getFontName(const char*), this shouldn't happen");
    return "?";
}

void flFont::setFontName(const char* name, const char* whichElement){
    if(name==NULL){return;}
    tinyxml2::XMLElement * currentFont = doc.FirstChildElement("JWM")->FirstChildElement(whichElement)->FirstChildElement("Font");
    std::string font =fontTest(whichElement);
    if (font.c_str() != NULL){
        std::string fontName ="";
        std::string fontOptions ="";
        std::string::size_type size = font.find_first_of('-');
        if((font.find('-')!=std::string::npos)){
            fontOptions = font.substr(size,std::string::npos);
            fontName = name + fontOptions;
            currentFont->SetText(fontName.c_str());
            //std::cout<<"FontName = "<< fontName<<"\n";
        }
	}
	else{
        missingFont(whichElement);
    }
    saveChangesTemp();
}


//Font SIZE
unsigned int flFont::getFontSize(std::string whichElement){
//    const char* functionName = "unsigned int flFont::getFontSize(std::string whichElement)";
    //std::cerr<<functionName<<std::endl;
    std::string font =fontTest(whichElement.c_str());
    if (font.compare("")!=0){
        unsigned int fontSizeInt;
        std::string fontSize;
        std::string::size_type position = font.find(':');
        std::string::size_type size = font.find('-');
        if((font.find('-')!=std::string::npos)&&(font.find(':')!=std::string::npos)){
            fontSize = font.substr (size+1,(position-(size+1)));
            fontSizeInt = convert(fontSize.c_str());
            //std::cout<<"FontSize = "<< fontSize<<"\n"<<fontSizeInt<<"\n";
            return fontSizeInt;
        }
    }
    else{
        missingFont(whichElement.c_str());
        return getFontSize(whichElement);
    }
    errorJWM("getFontSize had an Error.... abort... size 42");
    return 42;
}

///Everything below here needs ERROR CHECKING
void flFont::setSize(unsigned int &fontSize,std::string whichElement){
    tinyxml2::XMLElement * currentFont = doc.FirstChildElement("JWM")->FirstChildElement(whichElement.c_str())->FirstChildElement("Font");
    std::string font = currentFont->GetText();
    //std::cout<<"setSize input: "<<font<<std::endl;//Debug
    std::stringstream converter;
    converter<<fontSize;
    std::string fontSizeSTR =  converter.str();
    std::string::size_type position = font.find(':');
	std::string::size_type size = font.find('-');
	//create temporary variables and a result variable;
	std::string temp1,temp2,result;
	//get the text AFTER the ':' and save it to temp2
	temp2 = font.substr(position,std::string::npos);
	//get the text BEFORE the '-' and save it to temp1
	temp1 = font.substr(0,size+1);
	//add the stuff together, and...
	result = temp1+fontSizeSTR+temp2;
	currentFont->SetText(result.c_str());
	//std::cout<<"setSize result: "<<result<<std::endl;//Debug
    saveChangesTemp();
}

//****************************  Font Color  ***********************************
///@param whichElement is something like TaskListStyle or TrayStyle or MenuStyle, etc..
void flFont::setFontColor(const double* rgb,const char* whichElement){
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( whichElement )->
                            FirstChildElement( "Foreground" );
    std::string color1 = colorToString(rgb);
    colorElement->SetText(color1.c_str());
    saveChangesTemp();
}

unsigned int flFont::getFontColor(const char *element){
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( element )->
                            FirstChildElement( "Foreground" );
    std::string colorXML = colorElement->GetText();
    //this unsigned int isn't used here, because there is only 1 color...
    //TODO: overload the getColor function :)
    unsigned int u = 1;
    //this one is important
    unsigned int color;
    color = getColor(colorXML, u);
    return color;
}

//######################################### END Font Color ##############################################
bool flFont::isValue(const char* whichElement, const char* name, const char* value){
    std::string n = name, v = value;
    std::string love = isValue(whichElement,n,v);
    if (love.compare("LOVE")!=0){return true;}
	return false;

}
bool flFont::isValue(const char* whichElement, std::string name){
    std::string font =fontTest(whichElement);
    std::cout<<font<<std::endl;
    if (font.c_str() != NULL){if((font.find(name)!=std::string::npos)){return true;}}
    return false;
}
const char* flFont::isValue(const char* whichElement, std::string name, std::string value){
    std::string font =fontTest(whichElement);
    if (font.c_str() != NULL){
        name+="=";
        int sizeOfName = name.length();
        //NAME+= value;
        //std::cout<<name<<std::endl;
        std::string N;
        int sizeOfValue =value.length();
        std::string::size_type namePosition = font.find(name);
        std::string::size_type position = (namePosition);
        if((font.find(':')!=std::string::npos)){
            if((font.find(name)!=std::string::npos)){
                N = font.substr ((position+sizeOfName),sizeOfValue);
                if (N==value){return N.c_str();}
            }
        }
    }
    return "LOVE";
}
void flFont::changeValue(const char* whichElement, std::string name, std::string value){
    if (isValue(whichElement, name)){
        std::string font =fontTest(whichElement);
        if (font.c_str() != NULL){
            name+="=";
            int sizeOfName = name.length();
            std::cout<<name<<std::endl;
            std::string Begin, End;
            int sizeOfValue =value.length();
            std::string::size_type namePosition = font.find(name);
            std::string::size_type position = (namePosition);
           // std::cout<<"namePosition: "<<namePosition<<" position: "<<position<<std::endl;
            if((font.find(':')!=std::string::npos)){
                if((font.find(name)!=std::string::npos)){
                    Begin = font.substr (0,position);
                    ///TODO:::: Find ':' after atrribute and value??
                    End = font.substr((position+sizeOfName+sizeOfValue),std::string::npos);
                    Begin +=value;
                    Begin += End;
                    //std::cout<<"Value: "<< Begin <<"\n";

                }
            }
        }
    }
}
//AntiAlias
//This needs to be hooked into the UI eventually, as well as all the multitudes of options... I think I will apply advanced options to ALL fonts.
// I might also make a checkbox that sets all fonts the same if the user wants.
bool flFont::getAntialias(const char* whichElement){return isValue(whichElement, antialias, "true");}
#if 0
///FONT CONFIG STUFF just here if I ever need the info...
void flFont::fontconfigLIST(Fl_Browser *o){
    std::list<std::string> fontList;
    std::string cast;// = new std::string;
    std::string n;
    //int fontIterator= 0;
    Fl_Font fontie = 0;
    FcObjectSet *object = FcObjectSetBuild(FC_FAMILY, FC_STYLE, (char *) 0);
    FcPattern *pattern = FcPatternCreate();
    FcConfig *config = FcInitLoadConfigAndFonts();
    FcFontSet *fontSet = FcFontList(config, pattern, object);
    //FcFontSetPrint(fontSet);
    for (int i=0; fontSet && i < fontSet->nfont; ++i) {
    FcPattern* font = fontSet->fonts[i];
    FcChar8 *family;
    if (FcPatternGetString(font, FC_FAMILY, 0, &family) == FcResultMatch){
            //printf("Font: %s\n", family);
            const char * fontName = reinterpret_cast<const char*>(family);
            fontList.push_back(fontName);
            //o->add(fontName);
    }
    }
    fontList.sort();
    fontList.unique();
    std::list<std::string>::iterator it = std::unique (fontList.begin(), fontList.end());
    fontList.resize(std::distance(fontList.begin(),it));
    for(it = fontList.begin(); it != fontList.end(); ++it){
        std::cout << *it << std::endl;
        cast = *it;
        //Fl::set_font(fontie, cast.c_str());
        std::cout << "--------------------" << std::endl;
        o->add(cast.c_str());
        fontie++;
    }

if (fontSet) FcFontSetDestroy(fontSet);
}
#endif
