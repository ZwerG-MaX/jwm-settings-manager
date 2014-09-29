#include "../include/flFont.h"

flFont::flFont()
{
    tinyxml2::XMLDocument doc;
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
    std::cout<<"The current Element doesn't have a font name or is missing a size.\n Recovering by rewriting default values\n";
    currentFont->SetText("ubuntu-12:antialias=true");
    getFontName(whichElement);//Is this a good Idea??  Is there a case that can make this loop endlessly?
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
        std:: string error = "no font\n";
        std::cout<<"This is an error, there is "<< error;
        return error;
    }
    std::cout<<"ERROR in getFontName(const char*), this shouldn't happen\n";
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
unsigned int flFont::getFontSize(const char* whichElement){
std::string font =fontTest(whichElement);
    if (font.c_str() != NULL){
        unsigned int fontSizeInt;
        std::string fontSize;
        std::string::size_type position = font.find(':');
        std::string::size_type size = font.find('-');
        if((font.find('-')!=std::string::npos)&&(font.find(':')!=std::string::npos)){
            fontSize = font.substr (size+1,(position-(size+1)));
            fontSizeInt = strtoul(fontSize.c_str(),0,10);
            //std::cout<<"FontSize = "<< fontSize<<"\n"<<fontSizeInt<<"\n";
            return fontSizeInt;
        }
    }
    else{
        missingFont(whichElement);
        getFontSize(whichElement);
    }
    std::cout<<"getFontSize had an Error.... abort... size 42\n";
    return 42;
}

///Everything below here needs ERROR CHECKING
void flFont::setSize(unsigned int &fontSize,const char* whichElement){
    tinyxml2::XMLElement * currentFont = doc.FirstChildElement("JWM")->FirstChildElement(whichElement)->FirstChildElement("Font");
    std::string font = currentFont->GetText();
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
	//std::cout<<result<<std::endl;//Debug
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


//AntiAlias
//This needs to be hooked into the UI eventually, as well as all the multitudes of options... I think I will apply advanced options to ALL fonts.
// I might also make a checkbox that sets all fonts the same if the user wants.
bool flFont::getAntialias(const char* whichElement){
    std::string font =fontTest(whichElement);
    if (font.c_str() != NULL){
        std::string A; //String antialias
        std::string::size_type antialias = font.find("antialias=");
        std::string::size_type position = font.find(':');
        if((font.find(':')!=std::string::npos)){
            if((font.find("antialias=")!=std::string::npos)){
            /*antialias +10 is 10 characters after the beginning of the string
			 * "antialias=" is 10 characters long
			 */
                A = font.substr (antialias+10,std::string::npos);
                if (A=="true"){return true;}else{return false;}
			//std::cout<<"Antialias = "<< A <<"\n";
            }
            else{return false;}
        }
        else{return false;}
    }
	return false;
}

/// Window STUFF

void flFont::setWindowFontColor(const double* rgb,const char* whichElement){
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" )->FirstChildElement("WindowStyle")->
                            FirstChildElement( whichElement )->
                            FirstChildElement( "Text" );
    std::string color1 = colorToString(rgb);
    colorElement->SetText(color1.c_str());
    saveChangesTemp();
}

unsigned int flFont::getWindowFontColor(const char *element){
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" )->FirstChildElement("WindowStyle")->
                            FirstChildElement( element )->
                            FirstChildElement( "Text" );
    std::string colorXML = colorElement->GetText();
    //this unsigned int isn't used here, because there is only 1 color...
    //TODO: overload the getColor function :)
    unsigned int u = 1;
    //this one is important
    unsigned int color;
    color = getColor(colorXML, u);
    return color;
}

///FONT CONFIG STUFF
void flFont::fontconfigLIST(Fl_Browser *o){
    FcObjectSet *object = FcObjectSetBuild(FC_FAMILY, (char *) 0);
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
            o->add(fontName);
    }
}
if (fontSet) FcFontSetDestroy(fontSet);
}
