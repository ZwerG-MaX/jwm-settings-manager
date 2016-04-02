#include "../include/Config.h"

Config::Config(){
#ifdef DEBUG_TRACK
  std::cerr<<"[Config]->"<<std::endl;
#endif // DEBUG
    jwmrc = ".jwmrc";
    JSMfile = ".jsm";
    DEBUG_ME=isDebug();
    home = getenv ("HOME");
    homePathNoFiles = homePathNoFile();
    whichPanel = 1;
    path = getenv("PATH");
    stringPATH = path;
    pathPosition = stringPATH.find_first_of(':');
    numPATHS = howmanyPATHS();
    configEnvHOME = "$HOME/.config/";
    homeConfig = home;
    homeConfig+="/.config/";
    torimenu = "torimenu";
    placesmenu = "placesmenu";
    gnomemenu = "gnomeapps";
    sysmenu = "gnomesystem";
    xdg_paths = set_xdg_paths();
    stringXDG_PATH = xdg_paths;
    XDG_pathPosition = stringXDG_PATH.find_first_of(':');
    num_XDG_PATHS = numXDG_PATHS();
    defaultPath =getDefaultFilepath();
    defaultFilePath = defaultPath + "themes/Default/Default";
    defaultOLDFilePath = defaultPath + "themes/old/Default/Default";
    defaultFilePath230 = defaultPath + "themes/2.3.0/Default/Default";
    theMenuROOT = "root:m";

}

Config::~Config(){
#ifdef DEBUG_TRACK
  std::cerr<<"<-[Config]"<<std::endl;
#endif // DEBUG
}

//End construction/destruction

///****************************   ***********************************
std::string Config::set_xdg_paths(){
// for more info see:
// http://freedesktop.org/wiki/Specifications/basedir-spec/

    const char* datadirs=getenv("XDG_DATA_DIRS");
    std::string thisXDG;
    if (datadirs == NULL){
        thisXDG="/usr/local/share/:/usr/share/";
    }
    else{
        thisXDG =datadirs;
    }
    const char* datahome = getenv("XDG_DATA_HOME");
    if (datahome == NULL){
        thisXDG += ":";
        datahome = getenv("HOME");
        thisXDG += datahome;
        thisXDG += "/.local/share";

    }
    else{
        thisXDG += ":";
        thisXDG += datahome;
    }
    if(DEBUG_ME){
        std::cerr<<"full xdg data path list: "<<thisXDG<<std::endl;
    }
    return thisXDG;
}
std::string Config::getDefaultFilepath(){
    std::string testPATH,dirToOpen,fullpath;
    unsigned int found = 0;
    //initialize directory reading variables to NULL
    DIR *dir = NULL;
    struct dirent *entryPointer = NULL;

    // if we can't find the xdg paths... return without trying to read them
    if(num_XDG_PATHS==0){return "/usr/share/jwm-settings-manager/";}

    //lets loop through the xdg paths
    for (int i = 1; i <= num_XDG_PATHS; i++){

        //get the string equvalent for the integer representation if of the xdg path
        // something like
        /*
        1=/usr/share/
        2=/usr/local/share
        etc...
        */
        testPATH = thisXDG_PATH(i);

        //make sure this isn't blank
        if(testPATH.compare("")!=0){

            //look to see if we have a / at the end... remove it if we do...
            found = testPATH.find_last_of('/');
            if (found == testPATH.length()-1){testPATH=testPATH.substr(0,testPATH.length()-1);}

            //see if there is an icon directory
            dirToOpen = testPATH + "/jwm-settings-manager/";
            dir = opendir(dirToOpen.c_str());
            if (dir!=NULL){
                //std::cout << "Process directory: " << dirToOpen.c_str() << std::endl;
                while ((entryPointer=readdir(dir)) != NULL){
                    if ((entryPointer->d_type == DT_DIR)&&(entryPointer->d_name[0] != '.')){
                        if(DEBUG_ME){
                            std::cerr<<"Found XDG_DATA_DIR: "<<dirToOpen<<std::endl;
                        }
                        return dirToOpen;
                    }
                }
                closedir(dir);
            }
        }

    }
    return "/usr/share/jwm-settings-manager/";
}
unsigned int Config::numXDG_PATHS(){
    // use member variables in Constructor to count the paths listed in the xdg data dirs environment variable
    // in other words:
    //   howmany=($(echo "${XDG_DATA_DIRS//:/ }"));echo ${#howmany[@]}
    stringXDG_PATH=xdg_paths;
    XDG_pathPosition = stringXDG_PATH.find_first_of(':');
    if(XDG_pathPosition>stringXDG_PATH.length()){return 1;}
    unsigned int howmany;
    for(howmany=1;(XDG_pathPosition!=std::string::npos);howmany++){
        XDG_pathPosition=stringXDG_PATH.find(':', XDG_pathPosition+1);
    }
    return howmany;
}

const char* Config::thisXDG_PATH(int whichPath){
// use this to get the string of the path to test.
// basically in bash speak...
// whichpath=1;howmany=($(echo "${XDG_DATA_DIRS//:/ }"));echo ${howmany[$whichpath]}
    stringXDG_PATH=xdg_paths;

//I used and modified the Config paths code to do this... TODO: refactor to use 1 function
    unsigned int lastPath = 0;
    std::string result;
    if (whichPath >=1){lastPath = whichPath - 1;}
    else {lastPath = 0;}

    std::string::size_type firstPosition = stringXDG_PATH.find_first_of(':');
    std::string::size_type position = stringXDG_PATH.find(':');
    for (int i=1;i<=whichPath;i++){position = stringXDG_PATH.find(':',position+1);}
    for (unsigned int j=1;j<=lastPath;j++){firstPosition = stringXDG_PATH.find(':',firstPosition+1);}
    if((firstPosition+1)<stringXDG_PATH.length()){
        result = stringXDG_PATH.substr (firstPosition+1,((position-firstPosition)-1));
    }
    if(DEBUG_ME){
        std::cerr<<"XDG data path: "<<result<<std::endl;
    }
    return result.c_str();
}
void Config::setFileName(std::string &fileName){
jwmrc = fileName;
}
void Config::under_mouse(Fl_Window *o){
    if(DEBUG_ME){
        std::cerr<<"void Config::under_mouse(Fl_Window *o)"<<std::endl;
    }
    int screenHeight = Fl::h()/2;
    int screenWidth = Fl::w()/2;
    int window_w = o->decorated_w();
    int window_h = o->decorated_h();
    window_h = window_h/2;
    window_w = window_w/2;
    o->position((screenWidth-window_w),(screenHeight-window_h));
}
//End Member Variables
int Config::jwmVersion(){
    const char* jwmVers = "jwm -v | grep JWM |sed 's/ by.*//' |sed 's/JWM v//'";
	std::string version = returnTerminalOutput(jwmVers,"r");

    if(version.compare("2.3.0")==0){return 0;}
    if(version.compare("2.3.1")==0){return 1;}
    if(version.compare("2.3.2")==0){return 2;}
    if(version.compare("2.3.3")==0){return 3;}
    if(version.compare("2.3.4")==0){return 4;}
    return -1;
}
int Config::FULLjwmVersion(){
    const char* jwmVers = "jwm -v | grep JWM |sed 's/ by.*//' |sed 's/JWM v//'";
	std::string version = returnTerminalOutput(jwmVers, "r");
std::string major,minor,revno,temp,versionMASH;

	unsigned int finder = version.find_first_of('.');
	if(finder<version.length()){
		int retval=0;
		major=version;
		temp=version;
		major=major.erase(finder,std::string::npos);
		temp=temp.erase(0,finder+1);
		versionMASH=major;
		//int MAJOR=convert(major.c_str());
		finder = temp.find_first_of('.');
		if(finder<temp.length()){
			minor=temp;
			minor=minor.erase(finder,std::string::npos);
			temp=temp.erase(0,finder+1);
			//int MINOR=convert(minor.c_str());
			revno=temp;
			versionMASH+=minor;
			versionMASH+=revno;
			//int REVNO=convert(revno.c_str());
			//return REVNO;
			retval=convert(versionMASH.c_str() );
			return retval;
		}
	}
    return -1;
}

bool Config::newVersionJWM(){
    const char* jwmVersion = "jwm -v | grep JWM |sed 's/ by.*//' |sed 's/JWM v//'";
	std::string version = returnTerminalOutput(jwmVersion,"r");
	std::string newTagVersion = "2.3.0";
    if(version.compare(newTagVersion)==0){return true;}
    int newTagVersionMajor = 2, newTagVersionMinor = 3;
    int dot1 = version.find_first_of('.');
    int dot2 = version.find_last_of('.');
    std::string major = version.substr(0,dot1);
    std::string minor = version.substr(dot1+1,dot2);
    int majorVersion = convert(major.c_str());
    int minorVersion = convert(minor.c_str());
    if (majorVersion > newTagVersionMajor){return true;}
    if ((majorVersion == newTagVersionMajor)&&(minorVersion >= newTagVersionMinor)){return true;}
    return false;
}

int Config::newStyle(){

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
        //std::cerr<<"Active"<<styles[i]<<" is "<<testActive<<std::endl;
    }
    i =0;
    for (bool testInactive =isElement(styles[0].c_str(),"Inactive"); i<=lengthofStyle;i++){
        testInactive=isElement(styles[i].c_str(),"Inactive");
        if(testInactive){inActive=true;}
        //std::cerr<<styles[i]<<" is "<<testInactive<<std::endl;
    }
    if(active && !inActive){
        if(!newVersion){
            //do something to let the user know || fix it...
            recover();
        }
        //std::cerr<<"New Version Support"<<std::endl;
        return two30;
    }
    //std::cerr<<"OLD Version Support"<<std::endl;
    return not23;
}
///++++++++++++++++++++++++++++++++++++++++++++++++++++++ Recovery ++++++++++++++++++++++++++++++++++++++++++++++++++++
void Config::write_out(std::string fileContents, std::string FILENAME){
  std::cout<<"Writing out the file: "<<FILENAME<<std::endl;
  const char* filename=FILENAME.c_str();
  std::ofstream outputFileStream(filename, std::ios::out);
  outputFileStream<<fileContents<<std::endl;
}
std::string Config::jwmrcOUT(){
	int version=FULLjwmVersion();
	unsigned int len=0;
	std::string brightUP,
				brightDown,
				MANUAL,
				STARTPAGE,
				TERM_PROG,
				SYS_MONITOR,
				MENU_WEB_PROG,
				SCREEN_SHOT,
				RUN_DIALOG,
				CALC_PROG,
				DESKTOP_PROG,
				VOL_PROG,
				STARTUP,
				OLD_CLOCK,
				BUTTONS,
				BG,
				addy,
				ABOUT_PROG;
	//Translatable strings
	std::string PLACES_NAME=gettext("Places");
	std::string ClockSettings=gettext("Clock Settings");
	std::string Calendarstring=gettext("Calendar");
	std::string TimezoneSettings=gettext("Timezone Settings");
	std::string EditPanel=gettext("Edit Panel");
	std::string EditMENU=gettext("Edit Menu");
	std::string updateMENU=gettext("Update Menu");
	std::string SHUTDOWN_NAME=gettext("Shutdown");
	std::string ReloadDesktop=gettext("Reload Desktop");
	std::string AboutToriOS=gettext("About ToriOS");
	std::string AboutUs=gettext("About Us");
	std::string Help=gettext("Help");
	std::string MENU_NAME=gettext("Apps");
	std::string Addnewitems=gettext("Add new items");

	len=4;
	const char *aBG[len];
	aBG[0]="/usr/share/backgrounds/default.jpg";
	aBG[1]="/usr/share/backgrounds/warty-final-ubuntu.png";
	aBG[2]="/usr/share/archlinux/wallpaper/archlinux-elation.jpg";
	aBG[3]="/usr/share/images/desktop-base/moreblue-orbit-wallpaper.png";
    for (unsigned int i=0;i<=len;i++){
		if(BG.compare("")==0){if(testFile(aBG[i])){BG=aBG[i];}}
	}
	std::string EXTENTION=".svg";
	std::string JSMsharePATH=getDefaultFilepath();
	std::string WHITE = "#ffffff";
	std::string GREY = "#383838";
	std::string RED = "#940000";
	std::string BLACK ="#000000";
	std::string OPACITY = "1.0";
	std::string LIGHT_GREY = "#808080";
	std::string DARK_GREY ="#232323";
	if (version<230){EXTENTION="";}
	std::string STARTPAGE_ICON="browser" + EXTENTION;
	std::string JSM="jwm-settings-manager";
	std::string EXECjwm="exec:";
	std::string TORIOSGAMMA="torios-gamma";
	std::string FACEB="https://www.facebook.com/ToriOS.Official";
	std::string GPLUS="https://plus.google.com/113578220061772446187/posts";
	std::string TWITTER="https://twitter.com/ToriOS_Official";
	std::string LP="https://launchpad.net/~torios";
	std::string TORIOSwebsite="http://torios.top";
	MANUAL="/usr/share/doc/torios/html/index.html";
	STARTPAGE="/usr/share/doc/torios/startpage.html";
	if(testExec(TORIOSGAMMA.c_str())){
		brightUP=TORIOSGAMMA+" up";
		brightDown=TORIOSGAMMA+" down";
	}
	/// MENU_WEB_PROG
	len=8;
	const char *aWEB[len];
	aWEB[0]="x-www-browser";
	aWEB[1]="firefox";
	aWEB[2]="chromium";
	aWEB[3]="google-chrome";
	aWEB[4]="qupzilla";
	aWEB[5]="opera";
	aWEB[6]="midori";
	aWEB[7]="links2";
    for (unsigned int i=0;i<=len;i++){
		if(MENU_WEB_PROG.compare("")==0){
            if(testExec(aWEB[i])){MENU_WEB_PROG=aWEB[i];}
        }
	}
	if(MENU_WEB_PROG.compare("")!=0){
		if(testFile(MANUAL.c_str())){MANUAL=MENU_WEB_PROG + " " + MANUAL;}
		else{MANUAL="";}
		if(testFile(STARTPAGE.c_str())){STARTPAGE=MENU_WEB_PROG + " " + STARTPAGE;}
		else{STARTPAGE=MENU_WEB_PROG;}
	}
	/// TERM_PROG
	len=8;
	const char *aterm[len];
	aterm[0]="x-terminal-emulator";
	aterm[1]="xterm";
	aterm[2]="sakura";
	aterm[3]="lxterminal";
	aterm[4]="rxvt";
	aterm[5]="roxterm";
	aterm[6]="xfce4-terminal";
	aterm[7]="terminator";
    for (unsigned int i=0;i<=len;i++){
		if(TERM_PROG.compare("")==0){if(testExec(aterm[i])){TERM_PROG=aterm[i];}}
	}
	if(TERM_PROG.compare("")!=0){SYS_MONITOR="htop";}
	if(!testExec(SYS_MONITOR.c_str())){
		SYS_MONITOR="lxtask";
		if(!testExec(SYS_MONITOR.c_str())){
			if(TERM_PROG.compare("")!=0){SYS_MONITOR="top";}
			if(!testExec(SYS_MONITOR.c_str())){
				SYS_MONITOR="";
			}
			else{SYS_MONITOR=TERM_PROG+" -e "+ SYS_MONITOR;}
		}
	}
	else{SYS_MONITOR=TERM_PROG+" -e "+ SYS_MONITOR;}
	///  SCREEN_SHOT
	len=6;
	const char *ascreen[len];
	ascreen[0]="screenie";
	ascreen[1]="gnome-screenshot";
	ascreen[2]="screengrab";
	ascreen[3]="shutter";
	ascreen[4]="xfce4-screenshooter";
	ascreen[5]="scrot";
    for (unsigned int i=0;i<=len;i++){
		if(SCREEN_SHOT.compare("")==0){if(testExec(ascreen[i])){SCREEN_SHOT=ascreen[i];}}
	}
	///  RUN_DIALOG
	len=2;
	const char *RUNa[len];
	RUNa[0]="zrun";
	RUNa[1]="grun";
    for (unsigned int i=0;i<=len;i++){
		if(RUN_DIALOG.compare("")==0){if(testExec(RUNa[i])){RUN_DIALOG=RUNa[i];}}
	}
	/// CALC_PROG="xcalc";
	len=7;
	const char *aCALC[len];
	aCALC[0]="xcalc";
	aCALC[1]="calcoo";
	aCALC[2]="galculator";
	aCALC[3]="gnome-calculator";
	aCALC[4]="kcalc";
	aCALC[5]="qalculate-gtk";
	aCALC[6]="wmcalc";
    for (unsigned int i=0;i<=len;i++){
		if(CALC_PROG.compare("CALC_PROG")==0){if(testExec(aCALC[i])){CALC_PROG=aCALC[i];}}
	}
	std::string VOL_UP="amixer-up";
	if(!testExec(VOL_UP.c_str())){VOL_UP="";}
	std::string VOL_DOWN="amixer-down";
	if(!testExec(VOL_DOWN.c_str())){VOL_DOWN="";}
	std::string VOL_MUTE="amixer-toggle";
	if(!testExec(VOL_MUTE.c_str())){VOL_MUTE="";}
	std::string HELP_PROG="xman";
	std::string LOGOUT_PROGRAM="torios-exit";
	if(!testExec(LOGOUT_PROGRAM.c_str())){LOGOUT_PROGRAM="jwm -exit";}
	std::string TZ_PROG="xterm -e 'sudo dpkg-reconfigure tzdata'";

	/// OLD_CLOCK
	len=15;
	const char *aCLOCK[len];
	aCLOCK[0]="torios-calendar";
	aCLOCK[1]="ccal";
	aCLOCK[2]="evolution";
	aCLOCK[3]="gdeskcal";
	aCLOCK[4]="gsimplecal";
	aCLOCK[5]="gnome-calendar";
	aCLOCK[6]="osmo";
	aCLOCK[7]="orage";
	aCLOCK[8]="python-goocalendar";
	aCLOCK[9]="remind";
	aCLOCK[10]="when";
	aCLOCK[11]="wmdate";
	aCLOCK[12]="xcal";
	aCLOCK[13]="yad";
	aCLOCK[14]="zenity";
    for (unsigned int i=0;i<=len;i++){
		if(OLD_CLOCK.compare("")==0){if(testExec(aCLOCK[i])){OLD_CLOCK=aCLOCK[i];}}
	}
	if(OLD_CLOCK.compare("zenity")==0){OLD_CLOCK+=" --calendar";}
	if(OLD_CLOCK.compare("yad")==0){OLD_CLOCK+=" --calendar";}
	std::string RESTART_PROGRAM="torios-reboot";

	std::string APPMENU_FILE="$HOME/.config/torimenu";
	std::string JWM_MENU,PLACES_INCLUDE;
	len=2;
	const char *aMENU[len];
	aMENU[0]="jwm-menu";
	aMENU[1]="jwm-desktopmenu";
    for (unsigned int i=0;i<=len;i++){
		if(JWM_MENU.compare("")==0){if(testExec(aMENU[i])){JWM_MENU=aMENU[i];}}
	}
	len=2;
	const char *aMENU2[len];
	aMENU2[0]="jwm-places";
	aMENU2[1]="jwm-placesmenu";
    for (unsigned int i=0;i<=len;i++){
		if(PLACES_INCLUDE.compare("")==0){if(testExec(aMENU2[i])){PLACES_INCLUDE=aMENU2[i];}}
	}
    if(testExec("torios-about")){ABOUT_PROG="torios-about";}
    else{
        if(testExec("starttorios")){ABOUT_PROG= MENU_WEB_PROG + " " + TORIOSwebsite;}
        else{ABOUT_PROG="";}
    }
    std::string baseFONT=getDefaultFONT();
    std::string FONT=baseFONT+"-12:antialias=true:encoding=utf8";
    std::cerr<<baseFONT<<">>"<<FONT<<std::endl;
    len=3;
	const char *aDESKTOP[len];
	aDESKTOP[0]="pcmanfm";
	aDESKTOP[1]="rox";
	aDESKTOP[2]="nautilus";
    for (unsigned int i=0;i<=len;i++){
		if(DESKTOP_PROG.compare("")==0){if(testExec(aDESKTOP[i])){DESKTOP_PROG=aDESKTOP[i];}}
	}
	if(DESKTOP_PROG.compare("pcmanfm")==0){DESKTOP_PROG+=" --desktop";}
	if(DESKTOP_PROG.compare("rox")==0){DESKTOP_PROG+=" -p";}
    if(DESKTOP_PROG.compare("")!=0){STARTUP="<StartupCommand>"+DESKTOP_PROG+"</StartupCommand>\n";}
    std::string JSMmouse=homePathNoFiles;
    JSMmouse+="/.config/jsm-mouse";
    if(testFile(JSMmouse.c_str())){STARTUP=STARTUP+"    <StartupCommand>"+JSMmouse+"</StartupCommand>\n";}
    len=2;
	const char *aVOL_PROG[len];
	aVOL_PROG[0]="torios-volume";
	aVOL_PROG[1]="volumeicon";
    for (unsigned int i=0;i<=len;i++){
		if(VOL_PROG.compare("")==0){if(testExec(aVOL_PROG[i])){VOL_PROG=aVOL_PROG[i];}}
	}
    if(testExec(VOL_PROG.c_str())){STARTUP=STARTUP+"    <StartupCommand>"+VOL_PROG+"</StartupCommand>\n";}
    if(testExec("nice-start")){STARTUP+="   <StartupCommand>nice-start</StartupCommand>\n";}
    if(testFile("/usr/lib/policykit-1-gnome/polkit-gnome-authentication-agent-1")){STARTUP+="   <StartupCommand>/usr/lib/policykit-1-gnome/polkit-gnome-authentication-agent-1</StartupCommand>";}
	///TODO: find this actually
	len=4;
	const char *buttonA[len];
	buttonA[0]="/Buttons/Default/close.png";
	buttonA[1]="/Buttons/Default/max.png";
	buttonA[2]="/Buttons/Default/max-toggle.png";
	buttonA[3]="/Buttons/Default/min.png";
	std::string tempbutton;
	for (unsigned int i=0;i<=len;i++){
		tempbutton=JSMsharePATH+buttonA[i];
		if(testFile(tempbutton.c_str())){
			switch(len){
				case 0:
					BUTTONS="<ButtonClose>" + tempbutton + "</ButtonClose>\n";
					break;
				case 1:
					BUTTONS=BUTTONS+"<ButtonMax>" + tempbutton + "</ButtonMax>\n";
					break;
				case 2:
					BUTTONS=BUTTONS+"<ButtonMaxActive>" + tempbutton + "</ButtonMaxActive>\n";
					break;
				case 3:
					BUTTONS=BUTTONS+"<ButtonMin>" + tempbutton + "</ButtonMin>\n";
					break;
				default:
					break;
			}
		}
	}

////////////////////////////////////// MENUS //////////////////////////////////////////////////////////////

//////MENUS
// 1 nothing
// 23 mouse menu
// 5 apps
// 7 places
// 8 gnome system
// 9 shutdown
// c clock
// p panel edit
// m menu edit

	///CLOCK
	std::string CLOCK_FORMAT="%a, %e %b %l:%M %p";
	std::string CLOCK="root:c";
	std::string OLD_CLOCK_TAG="    <Clock format=\"" + CLOCK_FORMAT + "\">" + OLD_CLOCK + "</Clock>";
	std::string CLOCK_TAG="    <Clock format=\"" + CLOCK_FORMAT + "\">" + CLOCK + "</Clock>";
	std::string CLOCK_MENU="<!-- Clock Menu-->\n\
    <RootMenu height=\"0\" onroot=\"c\">\n\
        <Program icon=\"time" + EXTENTION + "\" label=\""+ClockSettings+"\">" + JSM + " --clock-settings</Program>\n\
		<Separator/>\n\
        <Program icon=\"calendar" + EXTENTION + "\" label=\""+Calendarstring+"\">" + OLD_CLOCK + "</Program>\n\
        <Program icon=\"time" + EXTENTION + "\" label=\""+TimezoneSettings+"\">" + TZ_PROG + "</Program>\n\
    </RootMenu>";
//// Panel Edit
	std::string EDIT_PANEL_ROOT="root:p";
	std::string EDIT_PANEL="    <RootMenu onroot=\"p\">\n\
		<Program icon=\"jsm-panel" + EXTENTION + "\" label=\""+EditPanel+"\">" + JSM + " --panel</Program>\n\
		<Program icon=\"add" + EXTENTION + "\" label=\""+Addnewitems+"\">" + JSM + " --shortcuts</Program>\n\
    </RootMenu>";

//// Menu Edit
	std::string EDIT_MENU_ROOT="root:m";
	std::string EDIT_MENU="    <RootMenu onroot=\"m\">\n";
	if(testExec("update-menus")){EDIT_MENU=EDIT_MENU+"		<Program icon=\"reload" + EXTENTION + "\" label=\""+updateMENU+"\">update-menus</Program>\n";}
	EDIT_MENU=EDIT_MENU+"		<Program icon=\"jsm-panel" + EXTENTION + "\" label=\""+EditMENU+"\">" + JSM + " --menu</Program>\n\
		<Program icon=\"jsm-panel" + EXTENTION + "\" label=\""+EditPanel+"\">" + JSM + " --panel</Program>\n\
    </RootMenu>";
//// SHUTDOWN MENU
	std::string SHUTDOWN_ROOT="root:9";
	std::string SHUTDOWN_ICON="system-shutdown" + EXTENTION;
	std::string SHUTDOWN_PROGRAM=JSM + " --halt";
	std::string LOGOUT_ICON="system-logout" + EXTENTION;
	std::string RESTART_ICON="system-restart" + EXTENTION;
	std::string SHUTERDOWN="    <Separator/>\n\
		<Restart label=\""+ReloadDesktop+"\" icon=\"" + RESTART_ICON + "\"/>\n\
		<Program icon=\"" + SHUTDOWN_ICON + "\" label=\""+SHUTDOWN_NAME+"\">" + SHUTDOWN_PROGRAM + "</Program>";
//// MAIN MENU

	std::string JWM_ROOT_NUM="2";
	std::string JWM_ROOT="root:" + JWM_ROOT_NUM;
	std::string MENU_ICON="/usr/share/pixmaps/distributor-logo.png";
	if(!testFile(MENU_ICON.c_str())){MENU_ICON="distributor-logo";}
//MAIN MENU GENERATOR
	std::string JWM_ROOT_MENU="<RootMenu onroot=\"" + JWM_ROOT_NUM + "\">\n\
        <Include>" + EXECjwm + JWM_MENU + "</Include>\n";
    if(JWM_MENU.compare("")==0){JWM_ROOT_MENU="<RootMenu onroot=\"" + JWM_ROOT_NUM + "\">\n";}
    if(testExec("starttorios")){
        JWM_ROOT_MENU=JWM_ROOT_MENU+"        <Menu label=\""+AboutToriOS+"\" icon=\"help-about" + EXTENTION + "\" height=\"0\">\n";
        if(MANUAL.compare("")!=0){
            JWM_ROOT_MENU=JWM_ROOT_MENU+"       <Program label=\""+Help+"\" icon=\"help" + EXTENTION + "\">" + MANUAL + "</Program>\n";
        }
        if(MENU_WEB_PROG.compare("")!=0){JWM_ROOT_MENU=JWM_ROOT_MENU+"       <Program label=\"Launchpad\" icon=\"launchpad" + EXTENTION + "\">" + MENU_WEB_PROG + " " + LP + "</Program>\n\
        <Program label=\"G+\" icon=\"googleplus" + EXTENTION + "\">" + MENU_WEB_PROG + " " + GPLUS + "</Program>\n\
        <Program label=\"Facebook\" icon=\"facebook" + EXTENTION + "\">" + MENU_WEB_PROG + " " + FACEB + "</Program>\n\
        <Program label=\"Twitter\" icon=\"twitter" + EXTENTION + "\">" + MENU_WEB_PROG + " " + TWITTER + "</Program>\n";
        }
        if(ABOUT_PROG.compare("")!=0){
            JWM_ROOT_MENU=JWM_ROOT_MENU+"       <Program label=\""+AboutUs+"\" icon=\"" + MENU_ICON + "\">" + ABOUT_PROG + "</Program>\n";
        }
        JWM_ROOT_MENU=JWM_ROOT_MENU+"        </Menu>\n";
    }

        JWM_ROOT_MENU=JWM_ROOT_MENU+ SHUTERDOWN + "\n\
    </RootMenu>";
	std::string TORI_ROOT=JWM_ROOT;
//// PLACES MENU
	std::string PLACES_NUM="7";
	std::string PLACES_ROOT="root:" + PLACES_NUM;

	std::string PLACES_MENU_FILE="$HOME/.config/placesmenu";
	std::string PLACES_ICON="folder" + EXTENTION;
	std::string PLACES_MENU;
	if(PLACES_INCLUDE.compare("")!=0){
        PLACES_MENU="    <RootMenu onroot=\"" + PLACES_NUM + "\">\n\
        <Include>" + EXECjwm + PLACES_INCLUDE + "</Include>\n\
    </RootMenu>\n";
    }
    if(!testExec(PLACES_INCLUDE.c_str())){PLACES_MENU="";}
	std::string MENUS_LIST="    <Include>" + APPMENU_FILE + "</Include>\n\
<!--Places Menu-->\n\
    <Include>" + PLACES_MENU_FILE + "</Include>";
	std::string MENUS_LIST_NEW=JWM_ROOT_MENU + "\n\
" + PLACES_MENU+"    <RootMenu height=\"0\" onroot=\"z\">\n\
        <Exit label=\"Logout\" confirm=\"false\" icon=\"" + LOGOUT_ICON + "\"/>\n\
    </RootMenu>\n\
<!--Traybutton Edit Menu-->\n\
" + EDIT_PANEL+ "\n\
" + EDIT_MENU+ "\n"
 + CLOCK_MENU+ "\n";
	std::string ROOT_MENU="root:" + JWM_ROOT_NUM;
//// Mouse MENU
	std::string MOUSE_MENU="<RootMenu height=\"0\" onroot=\"3\">\n\
        <Program icon=\"folder-home" + EXTENTION + "\" label=\"Home\">xdg-open ~/</Program>\n\
        <Program icon=\"" + JSM + EXTENTION + "\" label=\"Settings\">" + JSM + "</Program>\n\
        <Program icon=\"preferences-desktop-wallpaper" + EXTENTION + "\" label=\"Change Desktop Background\">" + JSM + " --desktop</Program>\n\
    </RootMenu>";

//// window corners override in individual files
	std::string CORNER="4";
	std::string W_HEIGHT="20";
//// PANEL CONFIGURATIONS
//// THE NORMAL CONFIG used in Default, Ambiance and Live
	std::string TRAY="<Tray x=\"0\" y=\"-1\" height=\"34\" valign=\"top\" width=\"0\" halign=\"fixed\" layout=\"horizontal\">\n";
    if(JWM_MENU.compare("")!=0){
        TRAY=TRAY+"        <TrayButton label=\"" + MENU_NAME + "\" icon=\"" + MENU_ICON + "\" border=\"false\">\n\
            <Button mask=\"1\">" + JWM_ROOT + "</Button>\n\
            <Button mask=\"23\">" + EDIT_MENU_ROOT + "</Button>\n\
        </TrayButton>\n";
    }
    if(PLACES_INCLUDE.compare("")!=0){
        TRAY=TRAY+"        <TrayButton label=\"" + PLACES_NAME + "\" icon=\"" + PLACES_ICON + "\" border=\"false\">\n\
            <Button mask=\"1\">" + PLACES_ROOT + "</Button>\n\
            <Button mask=\"23\">" + EDIT_MENU_ROOT + "</Button>\n\
        </TrayButton>\n";
    }
    if(MENU_WEB_PROG.compare("")!=0){
        TRAY=TRAY+"        <TrayButton icon=\"" + STARTPAGE_ICON + "\" border=\"false\">\n\
            <Button mask=\"1\">" + EXECjwm + STARTPAGE + "</Button>\n\
            <Button mask=\"23\">" + EDIT_PANEL_ROOT + "</Button>\n\
        </TrayButton>\n";
    }
    TRAY=TRAY+"        <Pager labeled=\"true\"/>\n\
        <TaskList maxwidth=\"256\"/>\n\
        <Dock/>\n";
    if(testExec("xload")){TRAY +="    <Swallow name=\"xload\" width=\"64\">xload -nolabel -bg DimGrey -fg Grey -hl DarkGrey</Swallow>\n";}
    TRAY = TRAY + CLOCK_TAG + "\n\
    </Tray>";
////// OLD STYLE 2.2.2 configs
	std::string OLD_TRAY="<Tray x=\"0\" y=\"-1\" height=\"34\" valign=\"top\" width=\"0\" halign=\"fixed\" layout=\"horizontal\">\n";
    if(APPMENU_FILE.compare("")!=0){
        OLD_TRAY=OLD_TRAY+"        <TrayButton label=\"" + MENU_NAME + "\" icon=\"" + MENU_ICON + "\" border=\"false\">" + TORI_ROOT + "</TrayButton>\n";
    }
    if(PLACES_MENU_FILE.compare("")!=0){
        OLD_TRAY=OLD_TRAY+"        <TrayButton label=\"" + PLACES_NAME + "\" icon=\"" + PLACES_ICON + "\" border=\"false\">" + PLACES_ROOT + "</TrayButton>\n";
    }
    if(MENU_WEB_PROG.compare("")!=0){
        OLD_TRAY=OLD_TRAY+"        <TrayButton icon=\"" + STARTPAGE_ICON + "\" border=\"false\">" + STARTPAGE + "</TrayButton>\n";
    }
    OLD_TRAY=OLD_TRAY+"        <Pager labeled=\"true\"/>\n\
        <TaskList maxwidth=\"256\"/>\n\
        <Dock/>\n";
    if(testExec("xload")){
        OLD_TRAY +="    <Swallow name=\"xload\" width=\"64\">xload -nolabel -bg DimGrey -fg Grey -hl DarkGrey</Swallow>\n";
    }
        OLD_TRAY = OLD_TRAY + OLD_CLOCK_TAG + "\n\
        <TrayButton label=\"" + SHUTDOWN_NAME + "\" icon=\"" + SHUTDOWN_ICON + "\" border=\"false\">" + SHUTDOWN_ROOT + "</TrayButton>\n";

    //// see http://en.wikipedia.org/wiki/Table_of_keyboard_shortcuts
// I tried to implement everything from GNOME, Windows and OSX in here
    std::string KEYSHORTCUTS="<Key key=\"Up\">up</Key>\n\
    <Key key=\"Down\">down</Key>\n\
    <Key key=\"Right\">right</Key>\n\
    <Key key=\"Left\">left</Key>\n\
    <Key key=\"a\">left</Key>\n\
    <Key key=\"s\">down</Key>\n\
    <Key key=\"w\">up</Key>\n\
    <Key key=\"d\">right</Key>\n\
    <Key key=\"Return\">select</Key>\n\
    <Key key=\"Escape\">escape</Key>\n\
    <Key mask=\"A\" key=\"Tab\">next</Key>\n\
    <Key mask=\"4\" key=\"Tab\">next</Key>\n\
    <Key mask=\"AS\" key=\"Tab\">nextstacked</Key>\n\
    <Key mask=\"S4\" key=\"Tab\">nextstacked</Key>\n\
    <Key mask=\"SA\" key=\"Tab\">nextstacked</Key>\n\
    <Key mask=\"CA\" key=\"Tab\">nextstacked</Key>\n\
    <Key mask=\"C\" key=\"#\">desktop#</Key>\n\
    <Key mask=\"CA\" key=\"Right\">rdesktop</Key>\n\
    <Key mask=\"CA\" key=\"Left\">ldesktop</Key>\n\
    <Key mask=\"CA\" key=\"Up\">udesktop</Key>\n\
    <Key mask=\"CA\" key=\"Down\">ddesktop</Key>\n\
    <Key mask=\"A\" key=\"space\">window</Key>\n\
    <Key mask=\"A\" key=\"F3\">window</Key>\n\
    <Key key=\"F11\">fullscreen</Key>\n\
    <Key mask=\"C\" key=\"F11\">fullscreen</Key>\n\
    <Key mask=\"CS\" key=\"f\">fullscreen</Key>\n\
    <Key mask=\"4C\" key=\"f\">fullscreen</Key>\n\
    <Key mask=\"A\" key=\"F12\">shade</Key>\n\
    <Key mask=\"SC4\" key=\"Up\">maximize</Key>\n\
    <Key mask=\"4\" key=\"L\">maximize</Key>\n\
    <Key mask=\"A\" key=\"F10\">maximize</Key>\n\
    <Key mask=\"4\" key=\"Down\">minimize</Key>\n\
    <Key mask=\"4\" key=\"m\">minimize</Key>\n\
    <Key mask=\"A\" key=\"F9\">minimize</Key>\n\
    <Key mask=\"4\" key=\"w\">close</Key>\n\
    <Key mask=\"A\" key=\"F4\">close</Key>\n";
    if(JWM_ROOT_MENU.compare("")!=0){
		KEYSHORTCUTS + "    <Key mask=\"C\" key=\"Escape\">" + ROOT_MENU + "</Key>\n";
    }
	if(VOL_MUTE.compare("")!=0){
		KEYSHORTCUTS + "\n    <Key key=\"XF86AudioMute\">" + EXECjwm + VOL_MUTE + "</Key>\n";
	}
    if(VOL_UP.compare("")!=0){
		KEYSHORTCUTS + "\n<Key key=\"XF86AudioRaiseVolume\">" + EXECjwm + VOL_UP + "</Key>\n";
	}
    if(VOL_DOWN.compare("")!=0){
		KEYSHORTCUTS + "\n<Key key=\"XF86AudioLowerVolume\">" + EXECjwm + VOL_DOWN + "</Key>\n";
    }
	if(MENU_WEB_PROG.compare("")!=0){
		KEYSHORTCUTS + "\n    <Key key=\"XF86WWW\">" + EXECjwm + MENU_WEB_PROG + "</Key>\n";
	}
	if(CALC_PROG.compare("")!=0){
		KEYSHORTCUTS + "\n    <Key key=\"XF86Calculator\">" + EXECjwm + CALC_PROG + "</Key>\n";
	}
	if(TORIOSGAMMA.compare("")!=0){
		KEYSHORTCUTS + "\n    <Key key=\"XF86MonBrightnessUp\">" + EXECjwm + brightUP + "</Key>\n\
    <Key key=\"XF86MonBrightnessDown\">" + EXECjwm + brightDown + "</Key>\n";
	}

//CHECK for things to add to KEYS
	if(SCREEN_SHOT.compare("")!=0){
		KEYSHORTCUTS + "\n    <Key key=\"Print\">" + EXECjwm + SCREEN_SHOT + "</Key>\n\
    <Key mask=\"CA\" key=\"p\">" + EXECjwm + SCREEN_SHOT + "</Key>\n\
    <Key mask=\"S4\" key=\"3\">" + EXECjwm + SCREEN_SHOT + "</Key>\n";
	}
	if(TERM_PROG.compare("")!=0){
		KEYSHORTCUTS + "\n    <Key mask=\"CA\" key=\"t\">" + EXECjwm + TERM_PROG + "</Key>\n";
	}
	if(SYS_MONITOR.compare("")!=0){
		KEYSHORTCUTS + "\n    <Key mask=\"CS\" key=\"Escape\">" + EXECjwm + SYS_MONITOR + "</Key>\n\
    <Key mask=\"A4\" key=\"Escape\">" + EXECjwm + SYS_MONITOR + "</Key>\n\
    <Key mask=\"CA\" key=\"Delete\">" + EXECjwm + SYS_MONITOR + "</Key>\n\
    <Key mask=\"C\" key=\"Escape\">" + EXECjwm + SYS_MONITOR + "</Key>\n";
	}
	if(HELP_PROG.compare("")!=0){
		KEYSHORTCUTS + "\n    <Key mask=\"A\" key=\"F1\">" + EXECjwm + HELP_PROG + "</Key>\n";
	}
	if(RUN_DIALOG.compare("")!=0){
		KEYSHORTCUTS + "\n    <Key mask=\"A\" key=\"F2\">" + EXECjwm + RUN_DIALOG + "</Key>\n\
    <Key mask=\"4\" key=\"F2\">" + EXECjwm + RUN_DIALOG + "</Key>\n\
    <Key mask=\"4\" key=\"space\">" + EXECjwm + RUN_DIALOG + "</Key>\n";
	}

    std::string NEW_KEYSHORTCUTS=KEYSHORTCUTS + "\n\
    <Key mask=\"C4\" key=\"Up\">maxtop</Key>\n\
    <Key mask=\"C4\" key=\"Left\">maxleft</Key>\n\
    <Key mask=\"C4\" key=\"Right\">maxright</Key>\n\
    <Key mask=\"C4\" key=\"Down\">maxbottom</Key>\n\
    <Key mask=\"C4\" key=\"v\">maxv</Key>\n\
    <Key mask=\"4S\" key=\"Up\">maxv</Key>\n\
    <Key mask=\"C4\" key=\"h\">maxh</Key>\n\
    <Key mask=\"4\" key=\"Right\">sendr</Key>\n\
    <Key mask=\"4\" key=\"Left\">sendl</Key>\n\
    <Key mask=\"4\" key=\"Up\">sendu</Key>\n\
    <Key mask=\"4\" key=\"Down\">sendd</Key>\n\
    <Key mask=\"SCA\" key=\"Right\">sendr</Key>\n\
    <Key mask=\"SCA\" key=\"Left\">sendl</Key>\n\
    <Key mask=\"SCA\" key=\"Up\">sendu</Key>\n\
    <Key mask=\"SCA\" key=\"Down\">sendd</Key>";
    std::string theme=getGTKtheme();
    std::string ICONS_LIST=searchthemes(theme);
    ICONS_LIST+=homeIcons(theme);
    std::string MOUSE="<DoubleClickSpeed>400</DoubleClickSpeed>\n\
	<DoubleClickDelta>2</DoubleClickDelta>";

    std::string GROUPS="<Group>\n\
		<Option>noshade</Option>\n\
    </Group>\n\
    <Group>\n\
        <Class>Pidgin</Class>\n\
        <Option>sticky</Option>\n\
    </Group>\n\
    <Group>\n\
        <Name>gkrellm</Name>\n\
        <Option>nolist</Option>\n\
        <Option>sticky</Option>\n\
    </Group>\n\
    <Group>\n\
        <Name>conky</Name>\n\
        <Option>nolist</Option>\n\
        <Option>sticky</Option>\n\
    </Group>";


	std::string WINDOW_BACKGROUND = GREY+":"+DARK_GREY;

    std::string TrayStyle="    <TrayStyle>\n        <Active>\n\
            <Foreground>"+WHITE+"</Foreground>\n\
            <Background>"+RED+"</Background>\n\
        </Active>\n";
	std::string TaskListStyle="   <TaskListStyle>\n\
        <Font>" + FONT + "</Font>\n\
        <Active>\n\
		<Foreground>" + WHITE + "</Foreground>\n\
		<Background>" + RED + "</Background>\n\
        </Active>\n\
        <Foreground>" + WHITE + "</Foreground>\n\
        <Background>" + GREY + "</Background>\n\
    </TaskListStyle>\n";
    std::string PagerStyle="		<Active>\n\
		<Foreground>" + WHITE + "</Foreground>\n\
		<Background>" + RED + "</Background>\n\
        </Active>";
    std::string TrayButtonStyle="	<TrayButtonStyle>\n\
		<Font>" + FONT+"</Font>\n\
        <Foreground>" +WHITE+"</Foreground>\n\
        <Background>" + GREY+"</Background>\n\
    </TrayButtonStyle>\n";
    std::string MenuStyle="		<Active>\n\
	        <Foreground>" + WHITE + "</Foreground>\n\
			<Background>" + RED + "</Background>\n\
        </Active>\n";
    std::string WindowStyle= BUTTONS+"\n	<WindowStyle>\n\
        <Corner>" + CORNER + "</Corner>\n\
        <Active>\n\
            <Foreground>" + WHITE + "</Foreground>\n\
            <Background>" + WINDOW_BACKGROUND + "</Background>\n\
            <Outline>" + GREY + "</Outline>\n\
            <Opacity>" + OPACITY + "</Opacity>\n\
        </Active>\n\
		<Foreground>" + LIGHT_GREY + "</Foreground>\n\
		<Background>" + BLACK + "</Background>\n";
    std::string  KeysToUse=NEW_KEYSHORTCUTS;
	std::string TrayToUse=TRAY;
    std::string MenusToUse=MENUS_LIST_NEW;
	if (version<230){
		WindowStyle="<WindowStyle>\n\
		<Active>\n\
            <Text>" + WHITE + "</Text>\n\
            <Title>" + WINDOW_BACKGROUND + "</Title>\n\
            <Outline>" + GREY + "</Outline>\n\
            <Opacity>" + OPACITY + "</Opacity>\n\
        </Active>\n\
	<Text>" + LIGHT_GREY + "</Text>\n\
	<Title>" + BLACK + "</Title>\n";
		PagerStyle="		<Text>" + WHITE + "</Text>\n\
        <ActiveForeground>" + WHITE + "</ActiveForeground>\n\
        <ActiveBackground>" + RED + "</ActiveBackground>";
	  MenuStyle="<ActiveBackground>"+RED+"</ActiveBackground>";
	  addy="<!--less than 230-->\n";
	  addy+=TaskListStyle;
	  addy+=TrayButtonStyle;
	  KeysToUse=KEYSHORTCUTS;
	  MenusToUse=MENUS_LIST;
	  TrayToUse=OLD_TRAY;
	  TrayStyle="    <TrayStyle>\n";
	}
	else if( version==232){addy="<!-- 232-->\n";}
	else if(version>=232){
	  TrayStyle="    <TrayStyle group=\"true\">\n        <Active>\n\
            <Foreground>"+WHITE+"</Foreground>\n\
            <Background>"+RED+"</Background>\n\
        </Active>\n";

	}
	else{addy="<!-- 230 or 231 -->\n";}

	std::string JWMRCoutput="<?xml version=\"1.0\"?>\n\
<JWM>\n\
<!-- MENUS -->\n\
<!-- Main Menu -->\n\
   " +MenusToUse+"	<RootMenu onroot=\"1\"/>\n\
	<!-- Mouse Menu-->\n\
	"+ MOUSE_MENU+ "\n\
    <!--Shudown Menu-->\n\
	<RootMenu height=\"0\" onroot=\"9\">\n\
       " + SHUTERDOWN+ "\n\
	</RootMenu>\n\
<!-- END MENUS -->\n\
<!-- GROUP -->\n\
	" + GROUPS+ "\n\
<!-- PANEL -->\n\
	" + TrayToUse+ "\n\
<!-- Panel Style -->\n"
+TrayStyle+"		<Font>" + FONT + "</Font>\n\
		<Foreground>" + WHITE + "</Foreground>\n\
        <Background>" + GREY + "</Background>\n\
        <Opacity>" + OPACITY + "</Opacity>\n\
	</TrayStyle>\n\
    <PagerStyle>\n" + PagerStyle+ "\n\
        <Text>" + WHITE + "</Text>\n\
        <Outline>" + BLACK + "</Outline>\n\
        <Foreground>" + LIGHT_GREY + "</Foreground>\n\
        <Background>" + GREY + "</Background>\n\
    </PagerStyle>\n\
    <MenuStyle>\n\
        <Font>" + FONT + "</Font>\n"
        +MenuStyle+
"		<Foreground>" + WHITE + "</Foreground>\n\
        <Background>" + GREY + "</Background>\n\
        <Opacity>" + OPACITY + "</Opacity>\n\
    </MenuStyle>\n\
<!-- WINDOW -->\n	"
+WindowStyle+
"		<Font>" + FONT + "</Font>\n\
		<Width>4</Width>\n\
		<Height>" + W_HEIGHT + "</Height>\n\
		<Outline>" + BLACK + "</Outline>\n\
		<Opacity>" + OPACITY + "</Opacity>\n\
    </WindowStyle>\n\
    <FocusModel>click</FocusModel>\n\
    <SnapMode distance=\"10\">border</SnapMode>\n\
    <MoveMode>opaque</MoveMode>\n\
    <ResizeMode>opaque</ResizeMode>\n\
<!-- KEYSHORTCUTS -->\n\
	"+ KeysToUse + "\n\
<!-- MOUSE -->\n\
	" + MOUSE+ "\n\
<!-- ICONS -->\n\
   " + ICONS_LIST+ "\n\
<!-- DESKTOP -->\n\
    <Desktops width=\"2\" height=\"1\">\n";
if(BG.compare("")!=0){
    JWMRCoutput=JWMRCoutput+"        <Background type=\"image\">" + BG + "</Background>\n";
}
else{
    JWMRCoutput=JWMRCoutput+"        <Background type=\"solid\">" + BLACK + "</Background>\n";
    }
JWMRCoutput=JWMRCoutput+"    </Desktops>\n\
<!-- AUTOSTART -->\n\
	" + STARTUP+ "\n\
<!--POP UP -->\n\
    <PopupStyle>\n\
        <Font>" + FONT + "</Font>\n\
        <Outline>" + BLACK + "</Outline>\n\
        <Foreground>" + WHITE + "</Foreground>\n\
        <Background>" + GREY + "</Background>\n\
    </PopupStyle>\n\
</JWM>";
	return JWMRCoutput;
}
std::string Config::getFileName(std::string filename){
	std::string fileNAME;
	const char* home=getenv("HOME");
	if(home !=NULL){
		fileNAME=home;
		fileNAME+="/";
		if(filename.compare("")!=0){fileNAME+=filename;}
		else{fileNAME+=".jwmrc";}
	}
	else{fileNAME="/tmp/jwmrc";}
	return fileNAME;
}
int Config::recover(){
    std::string PATH = getFileName(".jwmrc~");
    std::string jwmRC=getFileName(".jwmrc");
	std::string contents=jwmrcOUT();
	write_out(contents,jwmRC);
	write_out(contents,PATH);
	return jwmVersion();
}
int Config::checkFiles(){
    #ifdef DEBUG_TRACK
    std::cerr<<"int Config::checkFiles()"<<std::endl;
    #endif // DEBUG
    std::string fileName = homePath();
    std::string fileName2 = homePathTemp();
    if(!testFile(fileName2.c_str())){
        if(testFile(fileName.c_str())){
            load();
            saveChangesTemp();
            testedFILE=true;
            return 0;
        }
        else{recover();testedFILE=true;}
        return 12;
    }
    if(!testedFILE){
    doc.LoadFile(fileName.c_str() );
    if (doc.ErrorID() !=0){
        errorJWM(jwmrc+" was not loaded properly...");
        if (loadTemp()!=0){
            doc.LoadFile(fileName2.c_str() );
            if (doc.ErrorID() !=0){
                errorJWM(jwmrc+" was not loaded properly...");
                recover();
                return 42;
            }
        }
    }
    }
    testedFILE=true;
    return 0;
}

//End Recovery


///****************************  LOADING / SAVING  ***********************************
void Config::saveJWMRC(Fl_Double_Window *o){
    saveChanges();
    saveChangesTemp();
    o->hide();
}
void Config::saveJWMRC(){
    doc.LoadFile( homePathTemp().c_str() );
    if (doc.ErrorID() !=0){
        std::cerr<<"The file"<< (homePathTemp().c_str())<<"was not found.  Trying to fix it now"<<std::endl;
        if (recover() == 0){return;}
        else{
            errorJWM("Recovery function failed...");
        }
    }
    doc.SaveFile( homePath().c_str() );
    doc.SaveFile( homePathTemp().c_str() );
    if(std::system("jwm -restart")!=0){
        std::cerr<<"Error checking JWM... please fix errors in ~/.jwmrc"<<std::endl;;
    }
}
void Config::saveChanges(){
    if(DEBUG_ME)std::cout<<"File saved"<<std::endl;
    doc.SaveFile( homePath().c_str() );
    if(std::system("jwm -restart")!=0){
        std::cerr<<"couldn't restart JWM"<<std::endl;
    }
}
void Config::saveNoRestart(){
    //if(DEBUG_ME)
    loadTemp();
    std::cout<<"both Files saved no restart JWM"<<std::endl;
    saveChangesTemp();
    doc.SaveFile( homePath().c_str() );
}
void Config::saveChangesTemp(){
    std::string hp = homePathTemp();
    const char* filename = hp.c_str();
    if(filename==NULL){errorJWM("MISSING temporary filename"); return;}
    //if(DEBUG_ME)
    std::cout<<"saving Temporary jwmrc file to: "<<filename<<std::endl;
    doc.SaveFile( filename );
    //std::cout<<"Temporary File saved\n";
    if(std::system("jwm -p")!=0){
        std::cerr<<"Error checking JWM... please run jwm -p again"<<std::endl;
    }
}
int Config::loadTemp(){
    std::string fileName = homePathTemp();
    if(fileName.compare("")==0){errorJWM("jwmrc file does not exist");return -1;}
    if(DEBUG_ME)std::cout<<"Config::loadTemp()->Loading: "<<fileName<<std::endl;
    doc.LoadFile( fileName.c_str());
    if (doc.ErrorID() !=0){
        if(!testFile(fileName.c_str())){
            if(DEBUG_ME)std::cerr<<"The file: "<< fileName<<" was not found.  Trying to fix it now"<<std::endl;
            if(DEBUG_ME)errorJWM("[Function] Config::loadTemp()");
            load();saveChangesTemp();
        }
        return doc.ErrorID();
    }
    return 0;
}
int Config::load(){
    std::string fileName = homePath();
    if(fileName.compare("")==0){errorJWM("jwmrc file does not exist");return -1;}
    if(DEBUG_ME)std::cout<<"Config::load()->Loading: "<<fileName<<std::endl;
    doc.LoadFile(fileName.c_str());
    if (doc.ErrorID() !=0){
        if(!testFile(fileName.c_str())){
            if(DEBUG_ME)std::cerr<<"The file: "<< fileName<<" was not found.  Trying to fix it now"<<std::endl;
            if(DEBUG_ME)errorJWM("[Function] Config::load()");
            if(recover()==0){load();saveChanges();}
            else{
                std::cerr<<"An error occured loading "<<jwmrc<<" ErrorID: "<<doc.ErrorID()<<std::endl;
                return doc.ErrorID();
            }
        }
        else{return doc.ErrorID();}
    }
    else{
    #ifdef DEBUG_TRACK
    std::cerr<<"document loaded!"<<std::endl;
    #endif // DEBUG
    }
    return 0;
}
///This function cancels any temporary changes to the jwmrc file.
void Config::cancel(){
    load();
    saveChangesTemp();
    recoverJSM();
}
///This one also hides the window and shows the settings window
void Config::cancel(Fl_Double_Window *o){
    cancel();
    o->hide();
    //SettingsUI uiSettings;
    //uiSettings.make_window()->show();
}
//End LOADING/SAVING

/// JSM <></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></>
void Config::saveJSM(){
    //std::cout<<"File saved\n";
    jsm.SaveFile(jsmPath().c_str());
}
int Config::loadJSM(){
    std::string fileName = jsmPath();
    jsm.LoadFile( fileName.c_str() );
    if (jsm.ErrorID() !=0){
        if(!testFile(fileName.c_str())){
            std::cerr<<"An error occured loading: "<< fileName<<std::endl;
            if(recoverJSM()==0){return 0;}
        }
    }
    return jsm.ErrorID();
}
int Config::recoverJSM(){
    recoverJSM(1);
    return 0;
}
void Config::recoverJSM(int panel){
    std::string path = jsmPath();
    //std::cout<<path<<std::endl;
    std::string clock = "xclock";
    ///TODO: make this pick a good default for other systems..
    std::string clocktz = "xterm -e 'sudo dpkg-reconfigure tzdata'";
    int places = 7;
    int root = 5;
    int gsys = 8;
    const char* fname = path.c_str();
    std::string p = convert(panel);
    std::ofstream jsmSTREAM(fname, std::ios::out);
    jsmSTREAM<<"<?xml version=\"1.0\"?>\n\
<num>"<<p<<"</num>\n\
<clock>"<<clock<<"</clock>\n\
<clocktz>"<<clocktz<<"</clocktz>\n\
<places root=\""<<places<<"\">"<<configEnvHOME<<placesmenu<<"</places>\n\
<apps root=\""<<root<<"\">"<<configEnvHOME<<torimenu<<"</apps>\n\
<gnapps root=\""<<root<<"\">"<<configEnvHOME<<sysmenu<<"</gnapps>\n\
<gnsys root=\""<<gsys<<"\">"<<configEnvHOME<<gnomemenu<<"</gnsys>\n\
<debug>false</debug>\n\
<ext>"<<"svg"<<"</ext>";
}
const char* Config::getJSMelement(const char* element){
    loadJSM();
    if(!jsm.FirstChildElement(element)){recoverJSM(1);}
    loadJSM();
    tinyxml2::XMLElement* node;
    node = jsm.FirstChildElement(element);
    const char* result = node->GetText();
    return result;
}
void Config::setJSMelement(const char* element, const char* value){
    loadJSM();
    if(!jsm.FirstChildElement(element)){
        std::cerr<<element<<" does not exist in the config file... creating it"<<std::endl;
        jsm.NewElement(element);
        saveJSM();
    }
    tinyxml2::XMLElement* node;
    node=jsm.FirstChildElement(element);
    node->SetText(value);
    saveJSM();
}
std::string Config::jsmPath(){
    if (getenv ("HOME") !=NULL){
        //printf ("The current Home Directory is: %s\n",home); //you can turn this on to debug if you like :)
        std::string fileName = getenv ("HOME");
        fileName += "/";
        fileName+=JSMfile;
        return fileName;
	}
	else{errorJWM("ERROR not valid path"); return "HomePath Error 2\n";}
}

//End JSM <></><></><></><></><></><></><></>

///ENVIROMENT VARIABLES //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// $HOME ~/~/~/~/

std::string Config::homePathTemp(){
//this returns $HOME/.jwmrc~
    const char* home_env_var=getenv("HOME");
    if (home_env_var!=NULL){
        std::string fileName = home_env_var;
        fileName += "/.jwmrc~";
        if(DEBUG_ME)std::cout<<"std::string Config::homePathTemp()="<<fileName<<std::endl;
        return fileName;
	}
	else{errorJWM("ERROR not valid path"); return "HomePathTemp Error";}
	return "~/.jwmrc";
}
std::string Config::homePath(){
//this returns $HOME/.jwmrc
    const char* home_env_var=getenv ("HOME");
    if (home_env_var!=NULL){
        std::string fileName = home_env_var;
        fileName += ("/"+jwmrc);
        //std::cout<<"Here is the Path: "<<fileName<<std::endl;//DEBUG
        return fileName;
	}
	else{errorJWM("ERROR not valid path"); return "HomePath Error";}
}
std::string Config::homePathNoFile(){
//this returns $HOME/
    if (getenv ("HOME")!=NULL){
        std::string fileName = getenv ("HOME");
        fileName += "/";
        return fileName;
	}
	else{errorJWM("ERROR not valid path"); return "HomePath NO FILE Error 3";}
}
//End $HOME ~/~/~/

                    /// $PATH /:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:

// /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
unsigned int Config::howmanyPATHS(){
    unsigned int howmany;
    for(howmany=1;(pathPosition!=std::string::npos);howmany++){
        pathPosition=stringPATH.find(':', pathPosition+1);
    }
    return howmany;
}
const char* Config::thisPATH(int whichPath){
    unsigned int lastPath = 0;
    std::string result;
    if (whichPath >=1){lastPath = whichPath - 1;}
    else {lastPath = 0;}
//std::cout<<"last path: "<<lastPath<<std::endl;
    std::string stringPATH = path;
    std::string::size_type firstPosition = stringPATH.find(':');
    std::string::size_type position = stringPATH.find(':');
    for (int i=1;i<=whichPath;i++){position = stringPATH.find(':',position+1);}
    for (unsigned int j=1;j<=lastPath;j++){firstPosition = stringPATH.find(':',firstPosition+1);}
    result = stringPATH.substr (firstPosition+1,((position-firstPosition)-1));
    return result.c_str();
}

//End $PATH /:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:

//End ENVIROMENT VARIABLES


/// Utility Functions ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Config::errorJWM(std::string message){
 errorJWM(message.c_str());
}
void Config::errorJWM(const char* message){
    ///TODO: make this an flmessage that shows up also...
    //And logs to a file
    //fl_message(message);
   std::cerr<< message << "\n "<<gettext("Please Report this bug")<<std::endl;
}
std::string Config::convert(int num){
    std::string number;
    std::stringstream out;
    out << num;
    number = out.str();
    return number;
}
const char* Config::convert(double num){
    std::string number;
    std::stringstream out;
    out << num;
    number = out.str();
    return number.c_str();
}
unsigned int Config::convert(const char* num){
    std::stringstream out;
    out << num;
    unsigned int integer;
    out >> integer;
    return integer;
}
std::string Config::fixName(const char* filename){
    //std::cout<<"fixName:\n";
    std::string Filename = filename;
    std::string escape = "\\ ";
    size_t start_pos = 0;
    while((start_pos = Filename.find(' ', start_pos)) != std::string::npos) {
        Filename.replace(start_pos, 1, escape);
        start_pos += escape.length(); // Handles case where 'to' is a substring of 'from'
        //std::cout<<Filename<<std::endl;
    }
    return Filename;
}

//End Utility

/// Autostart ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Config::addAutostart(std::string program){
    loadTemp();
    ///Check to see if it is already there...
    if(isAutostart(program)){return;}
    //bool tester = false;
    //base XML element
    tinyxml2::XMLNode *baseNODE = doc.FirstChildElement( "JWM" );
    tinyxml2::XMLNode *node = doc.NewElement("StartupCommand");
    //Base startup Node
    //does it even exist???
    tinyxml2::XMLNode *startNode = doc.FirstChildElement( "JWM" );
    if(isElement("StartupCommand")){
        startNode = startNode->LastChildElement("StartupCommand");
        baseNODE->InsertAfterChild(startNode,node);
    }
    else{baseNODE->InsertEndChild(node);}
    //add the text to our new node
    tinyxml2::XMLText *startup = doc.NewText(program.c_str());
    node->LinkEndChild(startup);

    ///These are used to check for running instances
    //use the pidof command to check if the program is running
    std::string PID = "pgrep ";
    int sys = 0;
    std::string baseprogram = program;
    unsigned int found_space=baseprogram.find_first_of(' ');
    if(found_space<baseprogram.length()){
        baseprogram=baseprogram.erase(found_space,std::string::npos);
    }
    ///Check if the program is running.  If not start it!
    PID += baseprogram;
    //if(DEBUG_ME)
    std::cout<<PID<<std::endl;
    std::string pidOF = returnTerminalOutput(PID,"r");



    if(pidOF.compare("")==0){
        if(DEBUG_ME)std::cerr<<baseprogram<<" is not running"<<std::endl;
        sys= run(program.c_str());
        if (sys !=0){
            std::string errorMSG = gettext("system call did not return 0 for ");
            errorMSG +=program;
            errorJWM(errorMSG);
        }
    }
    if(DEBUG_ME)std::cerr<<"added autostart"<<std::endl;
    saveChangesTemp();
}
bool Config::isAutostart(std::string program){
    loadTemp();
    std::string autostart = program;
    std::string trim = program;
    if(!isElement("StartupCommand")){return false;}
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");node;node=node->NextSiblingElement("StartupCommand")){
        std::string fromDoc = node->GetText();
        const char* value  = fromDoc.c_str();
        if(DEBUG_ME)std::cout<<"isAutostart "<<value<<":"<<autostart<<std::endl;
        if(autostart.compare(value) ==0){return true;}
    }
    return false;
}
void Config::removeAutostart(std::string program){
    loadTemp();
    if(!isElement("StartupCommand")){return;}
    tinyxml2::XMLNode* baseNODE=doc.FirstChildElement("JWM");
    tinyxml2::XMLNode* deleter;
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");node;node=node->NextSiblingElement("StartupCommand")){
        if(node->GetText()){
            std::string fromDoc = node->GetText();
            std::cout<<fromDoc<<":"<<program<<std::endl;
            ///TODO: test exec to kill process?
            //const char* value  = fromDoc.c_str();
            //std::string fromProgram = program;
            deleter=node;
            if(program.compare(fromDoc) ==0){
                baseNODE->DeleteChild(deleter);
                if(DEBUG_ME)std::cout<<"deleted "<<program<<std::endl;
                saveChangesTemp();
                return;
            }
        }
    }
    saveChangesTemp();
}
//End Autostart

/// Color Functions //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int Config::getColor(std::string color, unsigned int &color2){
#ifdef DEBUG_TRACK
    std::cerr<<"unsigned int Config::getColor("<<color<<","<<color2<<")--->"<<std::endl;
#endif // DEBUG
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
				std::cerr<< "not a valid color"<<std::endl;
				return 42;
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
        std::string value= xColor(input);
        return getColor(value, color2);
    }
}
std::string Config::colorToString(const double *rgb){
    char tmp[8];
    std::snprintf(tmp, sizeof(tmp), "#%02x%02x%02x", int(rgb[0]), int(rgb[1]), int(rgb[2]));
        //return
    //std::cout<<tmp<<"\n tmp\n";
    return tmp;
}
bool Config::testElement(tinyxml2::XMLElement* element){
    loadTemp();
    if(element){return true;}
    return false;
}
bool Config::testElement(const char* whichElement){
    loadTemp();
    if(!doc.FirstChildElement( "JWM" )){return false;}
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    if (element->FirstChildElement( whichElement )){return true;}
    return false;

}
bool Config::testElement(const char* whichElement, const char* whichSubElement){
    loadTemp();
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    if (element->FirstChildElement( whichElement )){
        if (element->FirstChildElement( whichElement )->FirstChildElement( whichSubElement )){return true;}
    }
    return false;
}
bool Config::testElement(const char* whichElement,const char* whichSubElement, const char* whichSUBsubElement){
    loadTemp();
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    if (element->FirstChildElement( whichElement )){
        if (element->FirstChildElement( whichElement )->FirstChildElement( whichSubElement )){
            if (element->FirstChildElement( whichElement )->FirstChildElement( whichSubElement )->FirstChildElement( whichSUBsubElement ) ){return true;}
        }
    }
    return false;
}
std::string Config::xColor(const char *colorName){
/* Paul Sladen, 2014-08-13, Public Domain
 * XLookupColor() -> RGB colour value example, per request on
 * http://irclogs.ubuntu.com/2014/08/13/%23ubuntu-devel.html#t19:52
 * grep MistyRose /usr/share/X11/rgb.txt | awk '{printf("%02x%02x%02x\n",$1,$2,$3);}'
 * http://manpages.ubuntu.com/manpages/man3/XQueryColor.3.html
 * gcc xlookupcolour.c -o xlookupcolour -lX11 && ./xlookupcolour red yellow blue

modified for use in this program by Israel <israel@torios.org>
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
std::string Config::returnXColor(unsigned int color){
    #if 0
    Display *dpy;
    Colormap map;
    int scr;
    XColor rgb, nearest_rgb;
    int red = (int)rgb.red>>8;
    int green = (int)rgb.green>>8;
    int blue = (int)rgb.blue>>8;
    const char* colorName;
//    const char *fallback_colours[] = {"red", "white", "blue", "pink", NULL};
    dpy = XOpenDisplay(NULL);
    scr = XDefaultScreen(dpy);
    map = DefaultColormap(dpy, scr);
    XLookupColor(dpy, map, &colorName, rgb, &nearest_rgb);
    //printf("%3d %3d %3d %s\n", rgb.red>>8, rgb.green>>8, rgb.blue>>8, colorName);
    //std::cout<< "r= "<<red<<"  g= "<<green<<"  b= "<<blue<<'\n';
    char tmp[8];
    std::snprintf(tmp, sizeof(tmp), "#%02x%02x%02x", red, green, blue);
    #endif // 0
    color++;
    std::string output = "tmp";
    return output;
}
//End Color



///MENU ///&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
std::string Config::getLabelMenu(const char* menu){
    loadTemp();
    //make sure we have a Tray element first
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){
        createPanel();
        errorJWM("No panels existed... created one for you");
        return "";
    }
    if (!isMenu(menu)){
        errorJWM("The menu specified does not exist as a menu");
        return "";
    }
    const char * label = NULL;
    std::string labelString , labeled;
    labelString = "";
    std::string root ="root:";
    root +=menu;

    if(DEBUG_ME){
      std::cerr<<"Root menu string created: "<<root<<std::endl;
    }

    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    //does this have a traybutton??
     if(panelElement->FirstChildElement( "TrayButton" )){
        //lopp through them
        for(panelElement = panelElement->FirstChildElement( "TrayButton" );
            panelElement;
            panelElement = panelElement->NextSiblingElement("TrayButton" )){
                //check if it is new school style Button thingie
                if(panelElement->FirstChildElement("Button")->GetText()){labeled = panelElement->FirstChildElement("Button")->GetText();}
                //Is there even text here at all???
                if(panelElement->GetText()){labeled = panelElement->GetText();}
                if (labeled.compare(root)==0){
                    label = panelElement->Attribute("label");
                    if(label!=NULL){
                        labelString = label;
                    }
                }
        }

    }
    if(DEBUG_ME){
      std::cerr<<"Returning this Label for the menu: "<<labelString<<std::endl;
    }
    return labelString;
}
std::string Config::getImageMenu(const char* menu){
    loadTemp();
    int i = 1;

    //make sure we have a Tray element first
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){
        createPanel();
        return "";
    }
    if (!isMenu(menu)){return "";}
    std::string root ="root:";
    std::string labeled;
    root +=menu;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    //does this have a traybutton??
     if(panelElement->FirstChildElement( "TrayButton" )){
        //lopp through them
        for(panelElement = panelElement->FirstChildElement( "TrayButton" );
            panelElement;
            panelElement = panelElement->NextSiblingElement("TrayButton" )){
                //check if it is new school style Button thingie
                if(panelElement->FirstChildElement("Button")->GetText()){labeled = panelElement->FirstChildElement("Button")->GetText();}
                //Is there even text here at all???
                if(panelElement->GetText()){labeled = panelElement->GetText();}
                //does the GetText() from the Traybutton match??
                if (labeled.compare(root)==0){
                    //is there an icon??
                    if (panelElement->Attribute("icon")){
                        std::string icon = panelElement->Attribute("icon");
                        //well ok then, let's return it!!
                        return icon;
                    }
                }
        }
    }
    return "";
 }
bool Config::comparedColon(const char* something, const char* text){
    std::string stringText = text;
    unsigned found = stringText.find_first_of(":");
    if(found < stringText.length()){stringText=stringText.erase(found+1,std::string::npos);}
    std::string stringSomething = something;
    if(stringText.compare(stringSomething)==0){return true;}
    return false;
}
void Config::trayButtonAttribute(const char* text,const char* attribute,const char* attributeValue){
    if(text==NULL){return;}
    if(attribute==NULL){return;}
    if(attributeValue==NULL){return;}
    if(DEBUG_ME)std::cout<<"TrayButton text: "<<text<<"\nattribute to set: "<<attribute<<"\nvalue: "<<attributeValue<<std::endl;
    int i = 1;
    //make sure we have a Tray element first
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){createPanel();}
    std::string docText;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    if(panelElement->FirstChildElement( "TrayButton" )){
        for(panelElement = panelElement->FirstChildElement( "TrayButton" );
            panelElement;
            panelElement = panelElement->NextSiblingElement("TrayButton" )){

            tinyxml2::XMLElement * buttonElement = panelElement;
            //Is this the Newer style that can have a  Button in it??
            if(buttonElement->FirstChildElement("Button")){
                if(DEBUG_ME)std::cout<<"Button found"<<std::endl;
                for(buttonElement=buttonElement->FirstChildElement("Button");
                    buttonElement;
                    buttonElement=buttonElement->NextSiblingElement("Button")){

                    if(buttonElement->GetText()){
                        docText = buttonElement->GetText();
                        if(DEBUG_ME)std::cout<<"compare: "<<docText<<":"<<text<<std::endl;
                        if (docText.compare(text)==0){
                            if(DEBUG_ME)std::cout<<"Attribute: "<<attribute<<" set to:"<<attributeValue<<std::endl;
                            panelElement->SetAttribute(attribute,attributeValue);
                            saveChanges();
                            saveChangesTemp();
                            return;
                        }
                    }
                }
            }
            //Is there even text here??
            if(panelElement->GetText()){
                docText = panelElement->GetText();
                if(DEBUG_ME)std::cout<<"compare: "<<docText<<":"<<text<<std::endl;
                if (docText.compare(text)==0){
                if(DEBUG_ME)std::cout<<"Attribute: "<<attribute<<" set to:"<<attributeValue<<std::endl;
                    panelElement->SetAttribute(attribute,attributeValue);
                    saveChanges();
                    saveChangesTemp();
                    return;
                }
            }
        }
        errorJWM("Tray Buttons found, but couldn't find the one you were looking for");
    }
    errorJWM("No Tray Buttons found");
}
void Config::setImageMenu(const char* menu, const char* icon){
    if(menu==NULL){errorJWM("NULL variable sent into Config::setImageMenu");return;}
    if(icon==NULL){errorJWM("NULL variable sent into Config::setImageMenu");return;}
    if(DEBUG_ME)std::cout<<"Set Menu "<<menu<<" icon to: "<<icon<<std::endl;
    std::string root ="root:";
    root +=menu;
    trayButtonAttribute(root.c_str(),"icon",icon);
}
void Config::labelMenu(const char* menu,const char* label){
    if(menu==NULL){errorJWM("NULL variable sent into Config::labelMenu");return;}
    if(label==NULL){errorJWM("NULL variable sent into Config::labelMenu");return;}
    if(DEBUG_ME)std::cout<<"Set Menu "<<menu<<" label to: "<<label<<std::endl;
    std::string root ="root:";
    root +=menu;
    trayButtonAttribute(root.c_str(),"label",label);
}
void Config::labelMenu(const char * icon, const char* num,const char* label){
    if(icon==NULL){errorJWM("NULL variable sent into Config::labelMenu");return;}
    if(num==NULL){errorJWM("NULL variable sent into Config::labelMenu");return;}
    if(label==NULL){errorJWM("NULL variable sent into Config::labelMenu");return;}
    if(DEBUG_ME)std::cout<<"Set Menu "<<num<<" label to: "<<label<<" and icon to: "<<icon<<std::endl;
    std::string root ="root:";
    root +=num;
    trayButtonAttribute(root.c_str(),"icon",icon);
    trayButtonAttribute(root.c_str(),"label",label);
}

///          isMenu

bool Config::isMenu(std::string includeLine){  // called below
    return isElementText("Include",includeLine);
}
bool Config::isRootMenu(std::string rootmenu){
    loadTemp();
    std::string thisRoot;
    tinyxml2::XMLElement* menuElement = doc.FirstChildElement( "JWM" );
    if(!menuElement->FirstChildElement("RootMenu")){return false;}
    for(menuElement=menuElement->FirstChildElement("RootMenu");
        menuElement;
        menuElement=menuElement->NextSiblingElement("RootMenu")){
        thisRoot=menuElement->Attribute("onroot");
        if(DEBUG_ME){
        std::cerr<<"This root: "<<thisRoot<<" the one we want: "<<rootmenu<<std::endl;
        }
        if(thisRoot.compare(rootmenu)==0){
            if(DEBUG_ME){
            std::cerr<<"Found: "<<thisRoot<<std::endl;
            }
            return true;
        }
    }
    if(DEBUG_ME){
    std::cerr<<"Didn't find the menu..."<<std::endl;
    }
    return false;
}
bool Config::isMenu(const char* rootNumber){
    loadTemp();
    std::cout<< rootNumber<< "::rootnumber"<<std::endl;
    //make sure we have a Tray element first
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){
        createPanel();
        return false;
    }

    std::string root = "root:";
    root += rootNumber;
    const char* num = root.c_str();
    std::string compNum;
    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    if(panelElement->FirstChildElement( "TrayButton" )){
        for(panelElement = panelElement->FirstChildElement( "TrayButton" );
            panelElement;
            panelElement = panelElement->NextSiblingElement("TrayButton" )){

                if(panelElement->FirstChildElement("Button")){
                    tinyxml2::XMLElement* button;
                    for(button = panelElement->FirstChildElement("Button");
                        button;
                        button = button->NextSiblingElement("Button" )){
                            if(button->GetText()){
                                compNum = button->GetText();
                                if(DEBUG_ME){
                                if(compNum.compare("")==0){std::cerr<<"can't compare... there is nothing found yet.";}
                                else{std::cerr<<"comparing: "<<compNum<<" to: "<<num<<std::endl;}
                                }
                                if(compNum.compare(num)==0){return true;}
                            }
                    }
                }
            if(panelElement->GetText()){compNum = panelElement->GetText();}
            if(DEBUG_ME){
                if(compNum.compare("")==0){std::cerr<<"can't compare... there is nothing found yet.";}
                else{std::cerr<<"comparing: "<<compNum<<" to: "<<num<<std::endl;}
            }
            if(compNum.compare(num)==0){return true;}
        }
    }
return false;
}
void Config::addRoot(std::string rootmenu){
    std::string attribute = "onroot";
    createElement("RootMenu",attribute,rootmenu);
}
void Config::setRootMenuHeight(const char* menu, int height){
    if(menu==NULL){return;}
    setRootMenuAttribute(menu,"height",convert(height).c_str());
}
void Config::setRootMenuAttribute(const char* menu, const char* attribute, const char* attributeValue){
const char* root ="RootMenu";
    std::string docAttributeValue; //holder for comparing
    for(tinyxml2::XMLElement * menuElement = doc.FirstChildElement("JWM")->FirstChildElement(root);menuElement;menuElement = menuElement->NextSiblingElement()){
        if(menuElement->Attribute("onroot")){
            //if it exists put it in our string to compare
            docAttributeValue=menuElement->Attribute("onroot");
            //std::cout<<attributeValue<<" "<<rootmenu<<std::endl;
            // see if it matches the one in the hidden label
            if (docAttributeValue.compare(menu)==0){
                menuElement->Attribute(attribute,attributeValue);
                saveChangesTemp();
                return;
            }
        }
    }
}
void Config::addMenu(const char* rootnumber, const char* label, const char* icon){
    loadTemp();
    std::string r = "root:";
    std::string stringICON = icon;
    stringICON += getExtention();
    r += rootnumber;
    const char* root = r.c_str();
    int i = 1;

    //make sure we have a Tray element first
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){createPanel();}

    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    tinyxml2::XMLNode *node = doc.NewElement("TrayButton");
    panelElement->InsertEndChild(node);
    tinyxml2::XMLElement *newNode = node->ToElement();
    panelElement = panelElement->LastChildElement( "TrayButton" );
    panelElement->SetAttribute("label",label);
    panelElement->SetAttribute("border","false");
    panelElement->SetAttribute("icon",stringICON.c_str());
    if(newStyle()<1){
        newNode->SetText(root);
    }
    else{
        tinyxml2::XMLNode* trayNode = panelElement;
        tinyxml2::XMLNode *buttonNode= doc.NewElement("Button");
        trayNode->InsertEndChild(buttonNode);
        tinyxml2::XMLElement *BUTTON = buttonNode->ToElement();
        BUTTON->SetAttribute("mask",1);
        BUTTON->SetText(root);
        BUTTON->SetAttribute("mask",23);
        BUTTON->SetText(theMenuROOT);
    }
    saveChangesTemp();
}
void Config::deleteMenu(const char* menu){
    std::string menuString = "root:";
    menuString +=menu;
    int i = 1;

    //check to see if the tray exists
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return;
    }

    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    tinyxml2::XMLElement* node = panelElement;
    std::string root;
    for(node=node->FirstChildElement( "TrayButton" );node;node=node->NextSiblingElement("TrayButton")){
        if((newStyle()>=1)&&(panelElement->FirstChildElement("Button"))){root = node->FirstChildElement("Button")->GetText();}
        else{root = node->GetText();}
        if(root.compare(menuString)==0){
                panelElement->DeleteChild(node);
                //TODO delete entire RootMenu as well
                saveChangesTemp();
            }
    }
}
//End Menus



///  MULTIPLE PANELS  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Config::createPanel(){
    //make a node(needed for InsertEndChild) version of our Sibling Tray
    tinyxml2::XMLNode *tray = doc.FirstChildElement("JWM");
    //create the new Tray we want to add
    tinyxml2::XMLNode *newTray = doc.NewElement("Tray");
    //add the new tray
    tray->InsertEndChild(newTray);

    //save it so we can modify it more
    saveChangesTemp();
    saveChanges();

    //make a spacer so there is at least something there
    tinyxml2::XMLNode *spacer = doc.NewElement("Spacer");
    newTray->InsertEndChild(spacer);

    //turn the newTray node back into an element so we can modify the attributes
    tinyxml2::XMLElement *thisone = newTray->ToElement();

    //basic default panel setup
    thisone->SetAttribute("layout","horizontal");
    thisone->SetAttribute("valign","top");
    thisone->SetAttribute("halign","fixed");
    thisone->SetAttribute("height","34");
    thisone->SetAttribute("width","0");
    thisone->SetAttribute("x","0");
    thisone->SetAttribute("y","-1");

    //save it fully
    saveChanges();
    saveChangesTemp();
    //update the .jsm file
    updatePanels(1);
}
const char* Config::getAttribute(const char* attribute, unsigned int panel){
    loadTemp();
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return "";
    }
    unsigned int i = 1;
    //std::cout<<panel<<std::endl;
    const char* result ="";
    loadTemp();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        //std::cout<<attribute<<std::endl;
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    if(panelElement->Attribute(attribute)){result = panelElement->Attribute(attribute);}
    else{
        panelElement->SetAttribute(attribute,0);
        saveChangesTemp();
        result = "0";
    }
    return result;
}
//simply check if there are multiple panels
bool Config::multipanel(){
    loadTemp();
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return false;
    }
    bool test = false;
    load();
    int counter2 = 0;
    tinyxml2::XMLElement* node;
    for(node=doc.FirstChildElement("JWM")->FirstChildElement("Tray");node;node=node->NextSiblingElement("Tray")){counter2++;}
    if (counter2>1){test = true;}
    return test;
}
int Config::numPanels(){
    loadTemp();
    int counter2 = 0;
    tinyxml2::XMLElement* node=doc.FirstChildElement("JWM");
    if(!node->FirstChildElement("Tray")){return -1;}
    for(node=node->FirstChildElement("Tray");node;node=node->NextSiblingElement("Tray")){counter2++;}
    //std::cout<<"Found "<<counter2<< " panel(s)"<<std::endl;
    return counter2;
}
void Config::changePanel(int panel){
    std::string p = convert(panel);
    loadJSM();
    tinyxml2::XMLElement* num = jsm.FirstChildElement("num");
    num->SetText(p.c_str());
    saveJSM();

}

                            ///->->->->->->->->->->->->->->->->->-> current
int Config::currentPanel(){
    loadJSM();
    int value =1;
    tinyxml2::XMLElement* num = jsm.FirstChildElement("num");
    bool exists = testElement(num);
    if (exists){
        const char* number = num->GetText();
        value = convert(number);
    }
    else{
    recoverJSM(1);
    }
    return value;
}


                            ///->->->->->->->->->->->->->->->->->-> layout
const char* Config::checkLayout(){
    int layout = currentPanel();
    return checkLayout(layout);
}
const char* Config::checkLayout(unsigned int panel){
    loadTemp();
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return "horizontal";
    }
    tinyxml2::XMLElement* tray=doc.FirstChildElement("JWM")->FirstChildElement("Tray");
    bool test = multipanel();
    unsigned int i=1;
    if(test && panel != i ){
        while(tray->NextSiblingElement("Tray") && i!=panel){
            tray=tray->NextSiblingElement("Tray");
            i++;
        }
    }
    else{
        tray=doc.FirstChildElement("JWM")->FirstChildElement("Tray");
    }
    const char* layout = tray->Attribute("layout");
    return layout;
}
const char* Config::getPanelLayout(){
    int layout = currentPanel();
    return getPanelLayout(layout);
}
const char* Config::getPanelLayout(unsigned int panel){
    loadTemp();
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        //not sure what I need to return here...
        return "top";
    }
    tinyxml2::XMLElement* tray=doc.FirstChildElement("JWM")->FirstChildElement("Tray");
    bool test = multipanel();
    std::string layout;
    unsigned int i=1;
    //std::cout<<"panel: "<<panel<<std::endl;
    if((panel != i) && (test)){
        while(tray->NextSiblingElement("Tray") && i!=panel){
            tray=tray->NextSiblingElement("Tray");
            ++i;
            layout = tray->Attribute("layout");
        }
    }
    ///Why does this crash everything??

    ///if horizontal check valign
    ///should be left or right
    if(layout.compare("horizontal")==0){
        const char* valign = tray->Attribute("valign");
        //std::cout<<valign<<std::endl;
        return valign;
    }
    ///if vertical check halign
    ///should be top or bottom
    else if(layout.compare("vertical")==0){
        const char* halign = tray->Attribute("halign");
        //std::cout<<halign<<std::endl;
        return halign;
    }
    const char* error = "This shouldn't happen... no layout in getPanelLayout(unsigned int panel)";
    errorJWM(error);
    return error;
}
//End MultiPanels


///  EXECUTABLES AND PATHS  /././././././././././././././././././../././.././././././././././././././././..././././././././.././.././././/..././././././

bool Config::testExec(const char* exec){
    if(exec==NULL){return false;}
    struct stat sb;
    std::string stringEXEC = exec;
 /// my cheat sheet
 // /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
    std:: string testPATH, testEXEC;
    for (int i = 1; i <= numPATHS; i++){
		stringEXEC = exec;
		//std::cout<<"exec: "<<exec<<std::endl;
        testPATH = thisPATH(i);
        stringEXEC = testPATH + "/" + stringEXEC;
        testEXEC = stringEXEC.c_str();
        if (stat(testEXEC.c_str(), &sb) == 0){return true;}//else{std::cerr<<"Couldn't find "<<exec<<"\n";}
    }
    return false;
}
bool Config::testFile(const char* fileWithFullPATH){
  if(fileWithFullPATH==NULL){return false;}
  struct stat buffer;
  return (stat (fileWithFullPATH, &buffer) == 0);
}
//End Executables && $PATH

///########################################### ICONS ###########################################//////////////...............................................

std::vector<std::string> Config::iconList(){
    std::string value;
    std::vector<std::string> thisList;
    loadTemp();
    for(const tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("IconPath");node;node=node->NextSiblingElement("IconPath")){
        value  = node->GetText();
        if(value.c_str() !=NULL){
            if (value.compare("/usr/share/pixmaps")!=0 && value.compare("/usr/share/icons")!=0 ){
                thisList.push_back(value);
            }
        }
    }
    return thisList;
}
int Config::EXTENTION(std::string filename){
 ///represent the image extention in integer numerals
    const char* svg = "svg";
    const char* png = "png";
    const char* xpm = "xpm";
    std::string extentionReturn = ".";
    unsigned int found = filename.find_last_of(".");
    if((found+1)>filename.length()){return 42;}
    filename = filename.erase(0,found+1);
    if(filename.compare(svg)==0){
        return 0;//0 means svg
    }
    else if(filename.compare(png)==0){
        return 1;//1 means png
    }
    else if(filename.compare(xpm)==0){
        return 2;//2 means xpm
    }
    else return 42;//42 means you'll have to go fish
}
std::string Config::getExtention(){
///This function returns the most used image extention from <IconPath> tags

    //counters for image format as well as a gofishcounter for non images...
    int svgCounter = 0, pngCounter = 0, xpmCounter = 0, gofishcounter = 0;

    //make an unsigned int to store the vector size
    unsigned int listCounter= 0;
    //get a list of the IconPath directory entries as a vector
    std::vector<std::string> IconList = iconList();

    std::string value, filename, tempDir;

    // make our filename extentions to compare with
    const char* SVG = "svg";
    const char* PNG = "png";
    const char* XPM = "xpm";

    //initialize our extention as a dot
    //we add the extention to it later
    std::string extentionReturn = ".";

    // this is used as a temporary container for the result of EXTENTION function above
    int tracker;
    /* 0 means svg
     * 1 means png
     * 2 means xpm
     * 42 means you'll have to go fish... it is not what we want
     */

    // get the size of our list of directories
    listCounter = IconList.size();

    //if there is nothing use pixmaps because we ignored it
    if (listCounter<=1){IconList.push_back("/usr/share/pixmaps");}

    //make our pointer to the directory
    DIR *dirPointer = NULL;

    //make our pointer to our entry in the directory (stuff like files and folders)
    struct dirent *dirEntryPointer = NULL;

    // loop through the whole list starting at 0 and ending at the vector length
    for (unsigned int i = 0; i < listCounter; i++){

        // this will be our directory to open
        // the i-th directory in our list
        tempDir = (IconList[i]).c_str();

        //if it is empty... don't do anything.
        if (tempDir.compare("")!=0){

            // make the directory pointer the tempDir string (i.e. /usr/share/pixmaps)
            dirPointer=opendir(tempDir.c_str());

            // read it until it returns NULL
            // (this would be an error, or the end of the directory)
            while ((dirEntryPointer=readdir(dirPointer)) != NULL){

                // the filename will be whatever the directory entry's name is
                filename = dirEntryPointer->d_name;
                // use the EXTENTION function to get the numerical representation of
                // the file's extention
                tracker = EXTENTION(filename);
                /// see EXTENTION function above
                    /* 0 means svg
                     * 1 means png
                     * 2 means xpm
                     * 42(else) means it is not what we want
                     */
                if(tracker == 0){svgCounter++;}
                else if(tracker == 1){pngCounter++;}
                else if(tracker == 2){xpmCounter++;}
                else{gofishcounter++;}
            }
            // close the directory
            if(dirPointer!=NULL){closedir(dirPointer);}
        }
    }
    // if png has more than svg and xpm extentionReturn = .png
    // we want to preferr this, as PNG looks nice and works
    // on most compiled JWM setups
    if (pngCounter>svgCounter && pngCounter > xpmCounter){extentionReturn += PNG;}

    // this is very lightweight, so it will be our second check
    // if xpm has more than svg and png extentionReturn = .xpm
    else if (xpmCounter>svgCounter && xpmCounter > pngCounter){extentionReturn += XPM;}

    // if svg has more than png and xpm extentionReturn = .svg
    // svg looks the best, but some versions of JWM are compiled without support for it..
    else if (svgCounter>pngCounter && svgCounter > xpmCounter){extentionReturn += SVG;}
    // I like SVG a lot... so just return it
    else{extentionReturn+="svg";}
    // this can be uncommented to see what you are getting
    //std::cerr<<extentionReturn<<std::endl;

    // return the extention
    return extentionReturn.c_str();
}

//End Icons

///  BASH-LIKE  /!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#

const char* Config::grep(const char* args, const char* filename){
///Return the FIRST match of the 'args' from a file
// this is like  line=`grep $args $filename` that only returns one line
    std::string line;
//    const char* result;
    std::string lengthTEST = args;
    int lengthofARGS = lengthTEST.length();
    std::string subString;
    std::ifstream inputFileStrem (filename, std::ifstream::in);
    if(inputFileStrem.is_open()){
        while (getline(inputFileStrem,line)){
            unsigned int found =line.find(args);
            if(found<line.length()){
                if(DEBUG_ME){
                std::cerr<<"grepped "<<args<<" from: "<<filename<<" returning: "<<line<<std::endl;
                }
                return line.c_str();
            }
/* TODO: test this to see if it works better:
            result=strstr(line.c_str(),args);
            if(result!=NULL){
                return line.c_str();
            }
*/
        }
    }
    return "";
}
std::string Config::grep(const char* args, std::string filename){
    std::string line;
    std::string subString;
    std::ifstream inputFileStrem (filename.c_str(), std::ifstream::in);
    if(inputFileStrem.is_open()){
        while (getline(inputFileStrem,line)){
            unsigned int found =line.find(args);
            if(found<line.length()){
                if(DEBUG_ME){
                std::cerr<<"grepped "<<args<<" from: "<<filename<<" returning: "<<line<<std::endl;
                }
                return line.c_str();
            }
        }
    }
    return "";
}
///Array for grep
std::vector<std::string> Config::egrep(const char* args, const char* filename){
    std::vector<std::string> result;
    std::string line;
    std::string stringARGS = args;
    std::string sub;
    std::ifstream ifs (filename, std::ifstream::in);
    if(ifs.is_open()){
        while (getline(ifs,line)){
            if(line.find(stringARGS)<line.length()){
                result.push_back(line);
            }
        }
    }
    return result;
}
std::string Config::term_out(std::string terminal_Command_You_Want_Output_From) {
  std::string result="";
  const int max_buffer = 1024;
  char buffer[max_buffer];
  FILE *command_p = popen(terminal_Command_You_Want_Output_From.c_str(), "r");
  if (command_p){
    while(!feof(command_p)){
      if( fgets(buffer, sizeof(buffer), command_p) !=NULL){
        result.append(buffer);
      }
    }
    pclose(command_p);
  }
  else{ return "<!--[returnTerminalOutput] Error from command run-->";}
  int end = result.length();
  if((end-1) == 0){return "";}
  return result.erase(end-1,end);
}
std::string Config::returnTerminalOutput(std::string terminal_Command_You_Want_Output_From, const char* type){
    std::string result="";
    const int max_buffer = 1024;
    char buffer[max_buffer];
    /*
    Thanks to Jeremy Morgan's article!
    my original code was not using feof, this works now :)
    */
    FILE *command_p = popen(terminal_Command_You_Want_Output_From.c_str(), type);
	if (command_p){
        while(!feof(command_p)){
            if( fgets(buffer, sizeof(buffer), command_p) !=NULL){
                result.append(buffer);
            }
        }
        pclose(command_p);
    }
    else{ return "[returnTerminalOutput] Error from command run";}
	return result;
}
int Config::run(const char* command){
    std::string exec = "/bin/bash -c '";
    exec+=command;
    exec+=" &disown'";
    return system(exec.c_str());
}
//End BASH

///MULTIUSE///////////////////////////////////////////////////////////////////////////
/*
 * These are all Multiuse general functions for the FirstChild Element of 'JWM'
 *
 *
 We are looking for whichElement... this is whatever element you want to find
 I use it for IconPath sepcifically in

 <JWM>
    <whichElement>
    </whichElement>
 </JWM>
 *
 * XML attributes are
 *
 <JWM>
    <whichElement attribute="value">
    </whichElement>
 </JWM>
 *
 */

void Config::setAttribute(const char* whichElement, const char* attribute, const char* value){
    loadTemp();
    //make sure element exists first
    if (!isElement(whichElement)){createElement(whichElement);}
    //point to it
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichElement);
    //set the attribute
    element->SetAttribute(attribute,value);
    //save :)
    saveChangesTemp();
}
void Config::setAttribute(const char* whichElement, const char* attribute, const char* value, const char* text){
    loadTemp();
    //make sure the element exists
    if (!isElement(whichElement)){createElement(whichElement);}
    //create a pointer to the base element <JWM>
    tinyxml2::XMLElement* base = doc.FirstChildElement( "JWM" );
    //
    tinyxml2::XMLNode *node = doc.NewElement(whichElement);
    base->InsertAfterChild(node,node);
    tinyxml2::XMLText *action = doc.NewText(text);
    node->LinkEndChild(action);
    tinyxml2::XMLElement* element=doc.FirstChildElement("JWM")->LastChildElement(whichElement);
    element->SetAttribute(attribute,value);
    saveChangesTemp();
}
void Config::setAttribute(const char* whichElement, const char* attribute, double &value){
    loadTemp();
    // this overloads to take a double.. it simply converts to a const char* to run the base function
    const char* result = convert(value);
    setAttribute(whichElement,attribute,result);
}
void Config::setAttribute(const char* whichElement, const char* attribute, int &value){
    loadTemp();
    // this overloads to take an int.. it simply converts to a const char* to run the base function
    std::string result = convert(value);
    setAttribute(whichElement,attribute,result.c_str());
}
void Config::newMenu(const char* menu){
    loadTemp();
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    tinyxml2::XMLNode *node = doc.NewElement("RootMenu");
    element->InsertEndChild(node);
    tinyxml2::XMLElement* rootmenu = node->ToElement();
    rootmenu->SetAttribute("onroot",menu);
    saveChangesTemp();
    saveChanges();
}
void Config::createElement(const char* whichElement){
    /* simply creates a Child element of <JWM>
    <JWM>
       <whichElementToCreate/>
    </JWM>
    * since there is no text, it will make the single element rather than the pair
    */
    loadTemp();
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    tinyxml2::XMLNode *node = doc.NewElement(whichElement);
    element->InsertEndChild(node);
    saveChangesTemp();
    saveChanges();
}
void Config::createElement(const char* whichElement,std::string attribute, std::string attributeValue){
    if(whichElement==NULL){return;}
    /* simply creates a Child element of <JWM>
    <JWM>
       <whichElementToCreate/>
    </JWM>
    * since there is no text, it will make the single element rather than the pair
    */
    loadTemp();
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    tinyxml2::XMLNode *node = doc.NewElement(whichElement);
    element->InsertFirstChild(node);
    element=element->FirstChildElement(whichElement);
    element->Attribute(attribute.c_str(),attributeValue.c_str());

    saveChangesTemp();
    saveChanges();
}
void Config::createElement(const char* whichMainElement, const char* whichElementToCreate){
    if(whichMainElement==NULL){return;}
    if(whichElementToCreate==NULL){return;}
    loadTemp();
    /*this over-loaded version will make a sub-element of whichMainElement
    <JWM>
        <whichMainElement>
            <whichElementToCreate/>
        </whichMainElement>
    </JWM>
    * since there is no text, it will make the single element rather than the pair
    */

    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    //make sure whichMainElement exists before we go further
    if (!element->FirstChildElement(whichMainElement)){
      tinyxml2::XMLNode *node = doc.NewElement(whichMainElement);
    element->InsertEndChild(node);
    }
    //make it!
    element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichMainElement);
    tinyxml2::XMLNode *node = doc.NewElement(whichElementToCreate);
    //put it at the very end
    element->InsertEndChild(node);
    //save
    saveChangesTemp();
    saveChanges();
}
void Config::createElement(const char* whichMainElement, const char* whichSubElement, const char* whichElementToCreate){
  if(whichMainElement==NULL){return;}
  if(whichSubElement==NULL){return;}
  if(whichElementToCreate==NULL){return;}
  /*this over-loaded version will make a sub-element of the sub element whichSubElement
    <JWM>
        <whichMainElement>
            <whichSubElement>
                <whichElementToCreate/>
            </whichSubElement>
        </whichMainElement>
    </JWM>
    * since there is no text, it will make the single element rather than the pair
    */
    loadTemp();
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    //make sure the first element exists
    if (!element->FirstChildElement(whichMainElement)){
        createElement(whichMainElement);
        //loadTemp();
    }
    //point to the first one
    element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichMainElement);
//make sure the second exists
    if (!element->FirstChildElement(whichMainElement)->FirstChildElement(whichSubElement)){
        createElement(whichMainElement,whichSubElement);
        //loadTemp();
    }
//point to the second
    element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichMainElement)->FirstChildElement(whichSubElement);
    //make it!
    tinyxml2::XMLNode *node = doc.NewElement(whichElementToCreate);
    element->InsertEndChild(node);
    //save it!!
    saveChangesTemp();
    saveChanges();
}
bool Config::isElement(const char* whichElement){
    if(whichElement==NULL){return false;}
    loadTemp();
    //check if it is an element or not
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    if ((element)->FirstChildElement(whichElement)){return true;}
    return false;
}
bool Config::isElement(const char* whichElement, const char* whichSUBElement){
    if(whichElement==NULL){return false;}
    if(whichSUBElement==NULL){return false;}
    loadTemp();
    //check sub elements
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    if (element->FirstChildElement(whichElement)){
        if(doc.FirstChildElement( "JWM" )->FirstChildElement(whichElement)->FirstChildElement(whichSUBElement)){return true;}
    }
    return false;
}
bool Config::isElementText(const char* whichElement, std::string textTOcompare){
    if(whichElement==NULL){return false;}
    loadTemp();
    //this is to compare text in an element with std::string text
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    std::string testText;
    //does it exist
    if ((element)->FirstChildElement(whichElement)){
        for (element = element->FirstChildElement(whichElement);element;element = element->NextSiblingElement(whichElement)){
            testText = element->GetText();
            //std::cerr<<testText<<std::endl;
            if (textTOcompare.compare(testText.c_str())==0){return true;}
        }
    }
    //if it never gets to return true then we always return false
    return false;
}
int Config::getIntAttribute(const char* whichElement,const char* attribute){
    if(whichElement==NULL){return 0;}
    if(attribute==NULL){return 0;}
    loadTemp();
    //use the function below
    const char* result = getElementAttribute(whichElement, attribute);
    //convert string to unsigned long int
    // str   to ul
    //oh... and use 10... we want a base 10 number not something else
    int value = strtoul(result,0,10);
    return value;
}
const char* Config::getElementAttribute(const char* whichElement,const char* attribute){
    if(whichElement==NULL){return "";}
    if(attribute==NULL){return "";}
    loadTemp();
    if (!isElement(whichElement)){return "0";}
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichElement);
    return element->Attribute(attribute);
}
const char* Config::getElementAttribute(const char* whichElement,const char* whichSubElement,const char* attribute){
    if(whichElement==NULL){return "";}
    if(attribute==NULL){return "";}
    if(whichSubElement==NULL){return "";}
    loadTemp();
    if (!isElement(whichElement)){return "0";}
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichElement);
    //make sure sub element exists... if not then return 0
    if(!element->FirstChildElement(whichSubElement)){return 0;}
    element=element->FirstChildElement(whichSubElement);
    return element->Attribute(attribute);
}
unsigned int Config::getELEMENTColor(const char* whichStyle, const char* ActiveORinactive, unsigned int &color2, const char* FGorBG){
    if(whichStyle==NULL){return 0;}
    if(ActiveORinactive==NULL){return 0;}
    if(FGorBG==NULL){return 0;}
    loadTemp();
    unsigned int bg = 0;
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" );
    //make sure the base element exists
    if (!colorElement->FirstChildElement( whichStyle )){
        createElement(whichStyle);
    }
    colorElement = doc.FirstChildElement( "JWM" )->FirstChildElement( whichStyle );
    std::string style = whichStyle;
    if(newStyle() !=-1){
        std::string check = ActiveORinactive;
        if (check.compare("Active")==0){
            //Active so we have 3 deep we need to check for existence more
            if (!colorElement->FirstChildElement( ActiveORinactive )){createElement(whichStyle,ActiveORinactive);}
            //make sure the sub element exists first
            if (!colorElement->FirstChildElement( ActiveORinactive )->FirstChildElement( FGorBG )){createElement(whichStyle,ActiveORinactive,FGorBG);}

            //point to it
            colorElement  = colorElement->FirstChildElement( ActiveORinactive )->FirstChildElement( FGorBG );
        }
        else{
            //make sure it exists first
            if (!colorElement->FirstChildElement( FGorBG )){createElement(whichStyle,FGorBG);}

            //point to it
            colorElement  = colorElement->FirstChildElement( FGorBG );
        }
    }
    else{
        //make sure it exists first
        if (!colorElement->FirstChildElement( ActiveORinactive )){createElement(whichStyle,ActiveORinactive);}

        //point to it
        colorElement  = colorElement->FirstChildElement( ActiveORinactive );
    }
    //get the text
    std::string colour = colorElement->GetText();
    bg = getColor(colour, color2);
    return bg;
}
unsigned int Config::getFGColor(const char* whichStyle, const char* ActiveORinactive, unsigned int &color2){
    return getELEMENTColor(whichStyle, ActiveORinactive, color2, "Foreground");
}
void Config::setELEMENTColor(const char* whichStyle, const char* ActiveORinactive, const double* rgb, const char* FGorBG){
    loadTemp();
        tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" );
    //make sure the base element exists
    if (!colorElement->FirstChildElement( whichStyle )){
        createElement(whichStyle);
    }
    colorElement = doc.FirstChildElement( "JWM" )->FirstChildElement( whichStyle );
    std::string style = whichStyle;
    if(newStyle() !=-1){
        std::string check = ActiveORinactive;
        if (check.compare("Active")==0){
            //Active so we have 3 deep we need to check for existence more
            if (!colorElement->FirstChildElement( ActiveORinactive )){createElement(whichStyle,ActiveORinactive);}
            //make sure the sub element exists first
            if (!colorElement->FirstChildElement( ActiveORinactive )->FirstChildElement( FGorBG )){createElement(whichStyle,ActiveORinactive,FGorBG);}

            //point to it
            colorElement  = colorElement->FirstChildElement( ActiveORinactive )->FirstChildElement( FGorBG );
        }
        else{
            //make sure it exists first
            if (!colorElement->FirstChildElement( FGorBG )){createElement(whichStyle,FGorBG);}

            //point to it
            colorElement  = colorElement->FirstChildElement( FGorBG );
        }
    }
    else{
        //make sure it exists first
        if (!colorElement->FirstChildElement( ActiveORinactive )){createElement(whichStyle,ActiveORinactive);}

        //point to it
        colorElement  = colorElement->FirstChildElement( ActiveORinactive );
    }
    //convert the double rgb to a string
    std::string color1 = colorToString(rgb);
    //set it!
    colorElement->SetText(color1.c_str());
    saveChangesTemp();
}
void Config::setFGColor(const char* whichStyle, const char* ActiveORinactive, const double* rgb){
    setELEMENTColor(whichStyle, ActiveORinactive, rgb, "Foreground");
}
std::string Config::desktopFILE(){
    const char * f = "/usr/share/applications";
    const char * m="Choose a program";
    const char *p="*";
    int r = 0;
    std::string result = fl_file_chooser(m,p,f,r);
    std::string returnable = result;
    std::string base = result;
    unsigned period = result.find_last_of(".");
    bool isDESKTOP = false;
    if(result.compare("")!=0){
        if(period<result.length()){
            std::string testDesktop = result.substr(period+1,std::string::npos);
            if(testDesktop.compare("desktop")==0){isDESKTOP = true;}
        }
        unsigned found = result.find_last_of("//");
        if((found+1)<result.length()){returnable=result.erase(0,found+1);}
        unsigned found2 = returnable.find_last_of(".");
        if(found2<result.length()){returnable=returnable.erase(found2,std::string::npos);}
        if(isDESKTOP){
            std::string desktop = desktopExec(base);
            return desktop;
        }
    }
    return returnable;
}
std::string Config::desktopExec(std::string filename){
    if (filename.compare("")==0){std::cerr<<"No filename specified"<<std::endl;return "";}
    const char* ExecLine = grep("TryExec=",filename.c_str());
    std::string EXEC = ExecLine;
    if((ExecLine == NULL)||(EXEC.compare("")==0)){
        ExecLine = grep("Exec=",filename.c_str());
        EXEC = ExecLine;
    }
    if((ExecLine == NULL)||(EXEC.compare("")==0)){std::cerr<<"There is no TryExec/Exec line in: "<<filename<<std::endl;return " ";}
    unsigned int args = 0, equals = 0;
    args = EXEC.find("%");
    if (args < EXEC.length())EXEC = EXEC.erase(args,std::string::npos);
    equals = EXEC.find("=");
    if (equals < EXEC.length())EXEC= EXEC.erase(0,equals+1);
    std::cerr<<EXEC<<std::endl;
    return EXEC;
}
char* Config::Get_Fl_Icon(const char** pIcon){
    if(DEBUG_ME){
        std::cerr<<"char* Config::Get_Fl_Icon(const char** "<<pIcon<<")"<<std::endl;
    }
    /* Set icon for Linux:
     * This function must be initialised once by assigning an icon with parameter pIcon.
     * For sequential setting of icon to subwindows, this function can be called several
     * times without assigning an icon every time.
     *
     * Code from Vincent on FLTK forums 2015 Feb 10
     */
     //std::cout<< "sent in: "<<pIcon<<" to Get_Fl_Icon"<<std::endl;
   // Set icon for Linux:
    // This function must be initialised once by assigning an icon with parameter pIcon.
    // For sequential setting of icon to subwindows, this function can be called several
    // times without assigning an icon every time.
        static Pixmap p= 0;                // static store of assigned icon
        static Pixmap mask;
    if (!p && pIcon){
        // assign icon once
        fl_open_display();
        XpmCreatePixmapFromData(fl_display, DefaultRootWindow(fl_display),
(char**) pIcon, &p, &mask, 0);
    }
    return (char*) p;
}
void Config::setDebug(){
    std::string filename =homePathNoFile();
    filename+=".jwm-settings-manager.log";
    freopen( filename.c_str(), "w", stderr );
    setJSMelement("debug","true");
}
void Config::setDebugOff(){setJSMelement("debug","false");}
bool Config::isDebug(){
    std::string debugger= getJSMelement("debug");
    if(debugger.compare("true")==0){return true;}
    return false;
}


///ICON FUNCTIONS
bool Config::writeToFile(std::string fileContents){
	const char* home = getenv("HOME");
	if(home==NULL){return false;}
	std::string HOME=home;
	std::string JWM_FILE=HOME + "/.jwmrc";
	std::string JWM_FILE_BACKUP=HOME + "/.jwmrc~";
	std::string line,result;
	std::vector<std::string> VectorBuff;
	const char* FILENAME =JWM_FILE.c_str();
	const char* FILENAME2 =JWM_FILE_BACKUP.c_str();
	std::ifstream inputFileStrem (FILENAME, std::ifstream::in);
	if(inputFileStrem.is_open()){
		while (getline(inputFileStrem,line)){
			if((line.find("<IconPath>")== std::string::npos)&&(line.find("</JWM>")== std::string::npos)){
				VectorBuff.push_back(line);
				result+=line+"\n";
			}
		}
	}
	std::ofstream outputFileStream(FILENAME, std::ios::out);
    outputFileStream<<result<<fileContents<<"\n</JWM>"<<std::endl;
    std::ofstream outputFileStreamBAK(FILENAME2, std::ios::out);
    outputFileStreamBAK<<result<<fileContents<<"\n</JWM>"<<std::endl;
    return true;
}
bool Config::isDir(std::string FullPathToDir){
	if(DEBUG_ME)errorJWM(FullPathToDir);
	if(FullPathToDir.compare("")==0){return false;}
	DIR *dir = NULL;
	dir = opendir(FullPathToDir.c_str());
	if(dir!=NULL){closedir(dir);return true;}
	closedir(dir);
	return false;
}
std::string Config::homeIcons(std::string THEME_TO_USE){
	const char* home = getenv("HOME");
	if(home==NULL){std::cerr<<"HOME variable is not set"<<std::endl;return "";}
	std::string HOME=home;
	std::string HOME_THEME_DIR=HOME + "/.icons";
	std::string USER_ICONS;
	if (isDir(HOME_THEME_DIR)){USER_ICONS=getUserIcons(HOME_THEME_DIR);}
	std::string LOCALICONS=HOME+"/.local/share/icons/";
	if (isDir(LOCALICONS)){USER_ICONS+=getUserIcons(LOCALICONS);}

	std::string BASE_THEME_DIR="\n\t<IconPath>/usr/share/pixmaps</IconPath>\n\
\t<IconPath>/usr/share/icons</IconPath>\n\
\t<IconPath>/usr/share/app-install/icons</IconPath>";
	return BASE_THEME_DIR+USER_ICONS;
}
std::string Config::searchthemes(std::string THEME_TO_INHERIT){
	unsigned int SIZE_TO_USE=24;
	std::string HEADER,INHERITS,DIRS,MIN,MAX,SIZE,TYPE,THRESH,CONTEXT,ICON_PATH,THEME_DIR,THEME_TO_USE,ThemeFile,tempStr,tempPathString,INHERIT_ICON_WRITE,tempInherits;
	std::vector<std::string> THEME_DIR_XDG=iconThemeDirectories();
	std::vector<std::string> filesInDir;
	std::vector<std::string> INHERIT_ARRAY,ICONDIR_ARRAY;
   	for( std::vector<std::string>::iterator it = THEME_DIR_XDG.begin();
		it!=THEME_DIR_XDG.end();
		++it){

		THEME_DIR=*it;
		//unsigned int found = directory.find_last_of('/');
		//if (found != directory.length()-1){directory+="/";}
		THEME_DIR=THEME_DIR+THEME_TO_INHERIT;
		if(isDir(THEME_DIR)){
			filesInDir=GetThemeFiles(THEME_DIR);
			for(std::vector<std::string>::iterator iter = filesInDir.begin();
			iter!=filesInDir.end();
			++iter){
				unsigned int thresh,size,min,max;
				ThemeFile=*iter;
				//echo("Searching"+THEME_DIR+" Theme File:"+ThemeFile);
				std::string line;
				std::string subString;
				//reset variables
				HEADER="";INHERITS="";DIRS="";MIN="";MAX="";SIZE="";TYPE="";THRESH="";CONTEXT="";
				std::ifstream inputFileStrem (ThemeFile.c_str(), std::ifstream::in);
				if(inputFileStrem.is_open()){
					while (getline(inputFileStrem,line)){

				HEADER=PickOut(line,"[",HEADER);
				tempInherits=PickOut(line,"Inherits=",INHERITS);
				if(tempInherits.compare("")!=0){INHERITS=tempInherits;}
				DIRS=PickOut(line,"Directories=",DIRS);
				MIN=PickOut(line,"MinSize=",MIN);
				MAX=PickOut(line,"MaxSize=",MAX);
				SIZE=PickOut(line,"Size=",SIZE);
				TYPE=PickOut(line,"Type=",TYPE);
				THRESH=PickOut(line,"Threshold=",THRESH);
				CONTEXT=PickOut(line,"Context=",CONTEXT);
				thresh=convert(THRESH.c_str());
				size=convert(SIZE.c_str());
				min=convert(MIN.c_str());
				max=convert(MAX.c_str());
				HEADER=removeCruft(HEADER,"]");
				if( (HEADER.compare("Icon Theme")!=0)&&(HEADER.compare("")!=0)){
					ICON_PATH=HEADER;
					tempPathString=THEME_DIR+"/"+ICON_PATH;
				}
				//echo("H:"+HEADER+" IN:"+INHERITS+" DR:"+DIRS+" MN:"+MIN+" MX:"+MAX+" SZ:"+SIZE+" TY:"+TYPE+" TH:"+THRESH+" C:"+CONTEXT);
				//echo(tempPathString);
				if ( (CONTEXT.compare("Animations")!=0)
				&& (CONTEXT.compare("Stock")!=0)
				&&(CONTEXT.compare("Status")!=0)
				&& (CONTEXT.compare("Emblems")!=0)
				&& (CONTEXT.compare("Emotes")!=0)
				&& (CONTEXT.compare("International")!=0)){
							if ( (size==SIZE_TO_USE)
							||((thresh+size)==SIZE_TO_USE)
							||((thresh-size)==SIZE_TO_USE ) ){
								tempStr="<IconPath>"+tempPathString+"</IconPath>";
								if (ICON_PATH.find(SIZE)<=ICON_PATH.length()&&(isDir(tempPathString))){
									if(ICON_PATH.find(tempPathString)>ICON_PATH.length()) INHERIT_ICON_WRITE+="\n\t"+tempStr;
								}
							}
							else{
								tempStr="<IconPath>"+tempPathString+"</IconPath>";
								if ((TYPE.compare("Scalable")==0)&&( max >= size )&&( min <= size )&&(isDir(tempPathString))){if(ICON_PATH.find(tempPathString)>ICON_PATH.length()) INHERIT_ICON_WRITE+="\n\t"+tempStr;}
							}
						}
					}
				}
				if(INHERITS.compare("")!=0){
					unsigned int comma = INHERITS.find(',');
					if (comma<INHERITS.length()){INHERIT_ARRAY=commaVector(INHERITS,INHERIT_ARRAY);}
					else{INHERIT_ARRAY.push_back(INHERITS);}
				}
			}
		}
	}
	for( std::vector<std::string>::iterator i = INHERIT_ARRAY.begin();
	i!=INHERIT_ARRAY.end();
	++i){
		THEME_TO_INHERIT=*i;
		//echo("Inheriting: "+THEME_TO_INHERIT);
		INHERIT_ICON_WRITE+=searchthemes(THEME_TO_INHERIT);
	}
	return INHERIT_ICON_WRITE;
} // searchthemes()
std::string Config::getUserIcons(std::string directory){
	std::string result,fullpath;
	DIR *dir = NULL;
	struct dirent *entryPointer = NULL;
	unsigned int found = directory.find_last_of("/");
	if (found != directory.length()-1){directory+="/";}

	dir = opendir(directory.c_str());
	if(dir!=NULL){
		while ((entryPointer=readdir(dir)) != NULL){
			if ((entryPointer->d_type == DT_DIR)&&(entryPointer->d_name[0] != '.')){
				fullpath = entryPointer->d_name;
				//echo ("getUserIcons("+fullpath+")");
				result+= "\n\t<IconPath>"+directory+fullpath+"</IconPath>";
				result+=getUserIcons(directory+fullpath);
			}
		}
	}
	closedir(dir);
	return result;
}
std::string Config::get_line(std::string filename, std::string line) {
    std::string INTERNAL_LINE;
    std::string subString;
    std::ifstream inputFileStrem (filename.c_str(), std::ifstream::in);
    if(inputFileStrem.is_open()){
        while (getline(inputFileStrem,INTERNAL_LINE)){
            if(INTERNAL_LINE.find(line)<INTERNAL_LINE.length()){
                unsigned int found =INTERNAL_LINE.find("=");
                if(found < INTERNAL_LINE.length()){
                    subString=INTERNAL_LINE.substr(found+1,std::string::npos);
                   return subString;
                }
            }
        }
    }
    return "";
}
std::string Config::getGTKtheme(){
	std::string gtkrc2_result, gtkrc3_result,gtk2;
	std::string GSETTINGS=term_out("which gsettings");
	std::string GCONF2=term_out("which gconftool-2");
	if(GSETTINGS.find("gsettings")<GSETTINGS.length()){
		gtkrc3_result=term_out(GSETTINGS+" get org.gnome.desktop.interface icon-theme");
		//gtkrc3_result=removeCruft(gtkrc3_result,"gtk-icon-theme-name=");
		gtkrc3_result=removeCruft(gtkrc3_result,"\'");
		gtkrc3_result=removeCruft(gtkrc3_result,"\'");
		return gtkrc3_result;
	}
	if(GCONF2.find("gconftool-2")<GCONF2.length()){
		gtk2=term_out(GCONF2+" --get /desktop/gnome/interface/icon_theme");
		return gtk2;
	}
	const char* home = getenv("HOME");
	if(home==NULL){return "hicolor";}
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
	if(testFile(GTKRC3.c_str())){
		gtkrc3_result=get_line(GTKRC3,"gtk-icon-theme-name=");
		gtkrc3_result=removeCruft(gtkrc3_result,"gtk-icon-theme-name=");
		gtkrc3_result=removeCruft(gtkrc3_result,"\"");
		gtkrc3_result=removeCruft(gtkrc3_result,"\"");
		return gtkrc3_result;
	}
	if(testFile(GTKRC2.c_str())){
		gtkrc2_result=get_line(GTKRC2,"gtk-icon-theme-name=");
		gtkrc2_result=removeCruft(gtkrc2_result,"\"");
		gtkrc2_result=removeCruft(gtkrc2_result,"\"");
		return gtkrc2_result;
	}
	return "hicolor";
}
std::string Config::PickOut(std::string line, std::string findThis, std::string OriginalVar){
	//if(OriginalVar.compare("")!=0){return Original/Var;}
	std::string result=removeCruft(line,findThis);
	if(result.compare(line)==0){return "";}
	if(findThis.find(result)<findThis.length()){return "";}
	return result;
}
std::string Config::removeCruft(std::string StringInput, std::string CruftToRemove){
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
	errorJWM("There was a problem removing the cruft.... Giving you back your string");
	return StringInput;

}
std::vector<std::string> Config::iconThemeDirectories(){
	std::vector<std::string> THEME_DIR_XDG;
	std::string dirToOpen = "/usr/share/icons/";
	std::string pathToGet = "/icons/";
	std::string testPATH,tester,result,fullpath;
    std::vector<std::string> uniqueDirs = split_paths("XDG_DATA_DIRS","/usr/share/:/usr/local/share/");
	unsigned int found = 0;
   	for( std::vector<std::string>::iterator it = uniqueDirs.begin();
		it!=uniqueDirs.end();
		++it){
        //get the string equvalent for the integer representation if of the xdg path
        // something like
        /*
        1=/usr/share/
        2=/usr/local/share
        etc...
        */
		testPATH = *it;
		//make sure this isn't blank
		if(testPATH.compare("")!=0){
			//look to see if we have a / at the end... remove it if we do...
			found = testPATH.find_last_of('/');
			if (found == testPATH.length()-1){testPATH=testPATH.substr(0,testPATH.length()-1);}
			//see if there is a pathToGet directory
			dirToOpen = testPATH + pathToGet;
			if(isDir(dirToOpen)){THEME_DIR_XDG.push_back(dirToOpen);		}
		}//testPath is not ""
	}//directory looper
	return THEME_DIR_XDG;
}
std::vector<std::string> Config::GetThemeFiles(std::string directory){
	std::vector<std::string> THEME_DIR_XDG;
	std::string result,fullpath;
    DIR *dir = NULL;
	struct dirent *entryPointer = NULL;
	unsigned int found = directory.find_last_of("/");
	if (found != directory.length()-1){directory+="/";}
	//echo ("GetThemeFiles("+directory+")");
	dir = opendir(directory.c_str());
	if(dir!=NULL){
		while ((entryPointer=readdir(dir)) != NULL){
			if ((entryPointer->d_type == DT_REG)&&(entryPointer->d_name[0] != '.')){
				fullpath = entryPointer->d_name;
				result=directory+fullpath;
				unsigned period = result.find_last_of(".");
				bool isTheme = false;
				if(result.compare("")!=0){
					if(period<result.length()){
						std::string testTheme = result.substr(period+1,std::string::npos);
						if(testTheme.compare("theme")==0){isTheme = true;}
					}
					if(isTheme){THEME_DIR_XDG.push_back(result);} //isTheme
				}//result !empty
			}//it is a file
		}//readdir is not NULL
	}//dir!=NULL
	closedir(dir);
	return THEME_DIR_XDG;
}
std::vector<std::string> Config::commaVector(std::string LINE,std::vector<std::string> Vector){
	//std::vector<std::string> itemsVector;
	std::string original,preComma,postComma;
	original=LINE;
	unsigned int found,finder;
	finder=original.length();
	for(found=original.find_first_of(",");found<finder;found=original.find(",")){
		preComma=original;
		postComma=original;
		preComma=preComma.erase(found,std::string::npos);
		Vector.push_back(preComma);
		postComma=postComma.erase(0,found+1);
		//echo(preComma+"  "+postComma);
		original=postComma;
		finder=original.length();
	}
	if(postComma.compare("")!=0){Vector.push_back(postComma);}
	return Vector;
}
std::vector<std::string> Config::sortArray(std::vector<std::string> thisPath){
    std::vector<std::string>::iterator it;
    std::sort (thisPath.begin(), thisPath.end());
	it = std::unique (thisPath.begin(), thisPath.end());
	thisPath.resize( std::distance(thisPath.begin(),it) );
    return thisPath;
}
std::vector<std::string> Config::split_paths(const char* envVar, const char* incasenothingexists){
	std::vector<std::string> thisPath;
	std::vector<std::string>::iterator it;
	std::string thisXDG;
	const char* datadirs=getenv(envVar);
    if (datadirs == NULL){thisXDG=incasenothingexists;}
    else{thisXDG=datadirs;}
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
	//for(it=thisPath.begin();it<=thisPath.end();it++){outXML(*it);}
	return thisPath;
}
bool Config::isFONT(std::string FONTNAME){
    Fl_Font a;a = Fl::set_fonts("-*");
    std::string v;
    Fl_Font i;
    for (i=1;i!=a;++i){
        v = Fl::get_font_name(i,0);
        if(v.compare(FONTNAME)==0){return true;}
    }
    return false;
}
std::string Config::getDefaultFONT(){
    unsigned int len=4;
    std::string DEFAULT;
	const char *a[len];
	a[0]="sans";
	a[1]="droid";
	a[2]="serif";
	a[3]="arial";
    for (unsigned int i=0;i<=len;i++){
		if(DEFAULT.compare("")==0){
            if(isFONT(a[i])){
                DEFAULT=a[i];
                return DEFAULT;
            }
		}
	}
	return DEFAULT;
}
