/*

AmISprinting, amIThrowingPrimaryGrenade, amIThrowingSecondaryGrenade, amIKnifing, ClActive, cg_s, CEntity, isSameTeamOffset, isFFA, viewAngles, baseAngles, originOffset, FPStextEnabled, FPStextX, FPStextY, FPStextSize, FPStextLength, FPStextPointer, Cbuf_Addtext 

"11409700 11409480 11409500 11409520 11442048 11099352 11099360 929580 11099356 158336 164 40 41213632 8865120 8865104 8865096 1936598 8865072 3316936 "

*/










#define DEVELOPER 0
#define TOC (0x897620)
struct opd_s
{
	int sub;
	int toc;
};
struct vec3 {
	float x,y,z;
};
opd_s snprintf_t = {0xCE268,TOC};
int(*snprintf)(char *buffer, size_t len, const char *fmt, ...) = (int(*)(char *buffer, size_t len, const char *fmt, ...))&snprintf_t;

bool DvarGetBool(char *dvar) {
	opd_s finddvar_t = {0x3BAF18,TOC};
	int(*finddvar)(char *var) = (int(*)(char*))&finddvar_t;
	opd_s dvargetbool_t = {0x3BE238,TOC};
	bool(*dvargetbool)(int var) = (bool(*)(int))&dvargetbool_t;
	return dvargetbool(finddvar(dvar));
}
#define BUTTONVALUE (*(short*)0x00002918EF2)
enum buttonslol {
	B_X = 0x1000,
	B_Triangle = 0x8000,
	B_Square = 0x4000,
	B_Circle = 0x2000,
	B_DpadUp = 0x0001,
	B_DpadDown = 0x0002,
	B_DpadLeft = 0x0004,
	B_DpadRight = 0x0008,
	B_R1 = 0x0200,
	B_R2 = 0x0800,
	B_R3 = 0x0080,
	B_L1 = 0x0100,
	B_L2 = 0x0400,
	B_L3 = 0x0040,
	B_Start = 0x0010,
	B_Select = 0x0020,
};
bool isButtonDown(int button) {
	return BUTTONVALUE & button;
}
int selectedMenu = 0;
int selectedOption = 0;
int currentOptionCount = 0;
int lastMenus[20];
int lastMenuCount = 0;
bool AimbotEnabled = false;//off by default
bool autoShoot = false;
namespace MENUS {
enum MENUS {
	Closed,
	Main,
	Self,
	Aimbot,
	IPs,
	Rank,
	Chat,
	Kick,
	PlayersList,
	PlayerMenu,
	Names,
	Infection,
	MapChooser,
	BindButtonList,
	Host,
	Invalid
};
}

namespace CALLBACK {
	enum CALLBACK {
		Infection,
		EnterDvar,
		CustomName
	};
}
int timeout = 0;

/*
COD WAW FPS TEXT:
*(char*)0x274DEC0 = on/off
*(float*)0x874560 = x (0x43D80000 is doable)
*(float*)0x874550 = y (0x43400000 is doable)
*(float*)0x8744DC = rotation
*(char*)0x1D8D27 = text length (set to 0xff)
*(float*)0x874548 = fps size (0x40000000 is doable)
*/
/*
#pragma pack(1)
struct dvar_s {//not right size
	char *name;//0x0
	char *description;//0x4
	short flags;//0x8
	char type;//0xA
	char modified;//0xB
	int current_firsthalf_cuz_its_actually_a_union;//0xC  but size of 0x8 so 0x10 for int
	int current;//0x10
};
#pragma pack(4)
#define sv_cheats ((dvar_s*)(*(int*)*(int*)0x876D78+0x0))
*/

void print(char *Text);
int getOption();
void cBuf_Addtext(int localclient, char *text) {
	opd_s Cbufaddtext = {0x00329CC8,TOC};
	void (*cBuf_Addtext2)(int localclient,char *text) = (void(*)(int,char*))&Cbufaddtext;
	timeout = -100;
	cBuf_Addtext2(localclient,text);
}
void setSV_Cheats(bool value);
void Cmd_ExecuteSingleCommand(int localclient, int unknown ,char *text) {
	//setSV_Cheats(1);//set enable cheats for this function, will be disabled in the loop later.
	opd_s Cmd_ExecuteSingleCommand_t = {0x00032B7F0,TOC};
	void (*Cmd_ExecuteSingleCommandd)(int localclient, int unknown ,char *text) = (void(*)(int,int,char*))&Cmd_ExecuteSingleCommand_t;
	//Cmd_ExecuteSingleCommandd(localclient,unknown,text);//doesn't work cuz threading stuff
	cBuf_Addtext(localclient,text);
}
void Cmd_ExecuteSingleCommand2(int localclient, int unknown ,char *text) {
	//setSV_Cheats(1);//set enable cheats for this function, will be disabled in the loop later.
	opd_s Cmd_ExecuteSingleCommand_t = {0x00032B7F0,TOC};
	void (*Cmd_ExecuteSingleCommandd)(int localclient, int unknown ,char *text) = (void(*)(int,int,char*))&Cmd_ExecuteSingleCommand_t;
	Cmd_ExecuteSingleCommandd(localclient,unknown,text);//doesn't work cuz threading stuff
	//cBuf_Addtext(localclient,text);
}
void CL_ForwardCommandToServer(int localClientNum, char *string) {
	opd_s _dup = {0x1CE4A8,TOC};
	void(*dup)(int r3, char *r4) = (void(*)(int,char*))&_dup;
	dup(localClientNum,string);
}
opd_s CG_BoldGameMessage_t = {0x00155D78,TOC};
void (*CG_BoldGameMessage)(int localclient, char *text) = (void(*)(int localclient, char *text))&CG_BoldGameMessage_t;

void setName(char *name) {
	strcpy((char*)0x02952934,name);
}

/*void openMenu() {
	lastMenuCount = 0;
	selectedMenu = MENUS::Main;
	selectedOption = 0;
}*/
void closeMenu() {
	lastMenuCount = 0;
	selectedMenu = MENUS::Closed;
	selectedOption = 0;
	//sleep(500);
}
void openSubmenu(int menu) {
	lastMenus[lastMenuCount] = selectedMenu;
	selectedMenu = menu;
	lastMenuCount++;
	selectedOption = 0;
}
void goBack() {
	selectedOption = 0;
	if (lastMenuCount == 0) {
		closeMenu();
	} else {
		lastMenuCount--;
		selectedMenu = lastMenus[lastMenuCount];
		selectedOption = 0;
	}
}
void openMenu() {
	lastMenuCount = 0;
	selectedMenu = MENUS::Main;
	selectedOption = 0;
	//sleep(500);
}
/*void resetOptions() {
	int len = strlen((char*)0x10070200);
	for (int i = 0; i < len+1; i++) {
		*(char*)(0x10070200+i) = 0;
	}
}*/
struct safeInfo {//had to make this because it liked to dellete variables I put not inside here
	int selectedPlayer;
	bool prestigeLoopBool;
	char debugMaterial[40];
	bool targetVisibility[20];
	vec3 positions[20];	
	vec3 AimAngles;
	bool aimbothit;
	vec3 baseAngleRet;
	int nearestClient;
	bool canChangeNearestClientAutoAim;
	int teleportClient;
	char infectionCode[0x4];//size does not matter. Just keep it last
};
safeInfo *menuInfo = (safeInfo*)0x10070200;
/*
faction_128_japan
faction_128_soviet
faction_128_american
faction_128_german
scoreboard_japaneese
scoreboard_usmc
*/
void resetOptionCount() {
	currentOptionCount = 0;
}
bool AimTarget_GetTagPos(int targEnt, unsigned int targIndex,float *outPos);
#include "Aimbot.h"
opd_s Material_RegisterHandle_t = {0x57C840,TOC};
void*(*Material_RegisterHandle)(const char *name, int imageTrack, bool errorIfMissing, int waitTime) = (void*(*)(const char*, int, bool, int))&Material_RegisterHandle_t;
opd_s R_AddCmdDrawStretchPicInternal_t ={0x00587A18/*0x397C78*//*0x1A7150*/,TOC};//maybe
void(*R_AddCmdDrawStretchPicInternal)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float * color, void *material) = (void(*)(float, float, float, float, float, float, float, float, float *, void*))&R_AddCmdDrawStretchPicInternal_t;
opd_s initFont_t = {0x569278,TOC};
void*(*R_RegisterFont)(const char * name, int imageTrack) = (void*(*)(const char*, int))&initFont_t;
//unsigned int (*R_RegisterFont)(char *font, int one) = (unsigned int(*)(char*,int))&initFont_t;
opd_s drawText_t = {0x587588,TOC};
void(*R_AddCmdDrawTextInternal)(const char* text, int maxChars, void* font, float x, float y, float yScale, float xScale, float rotation, float * colors, int Style) = (void(*)(const char*, int, void*, float, float, float, float, float, float *, int))&drawText_t;
//void(*R_AddCmdDrawTextInternal)(char *message,int messageLength, unsigned int font, unsigned int _0x3f800000, float x, float y, float xscale, float yscale) = (void(*)(char*,int,unsigned int, unsigned int, float, float, float, float))&drawText_t;

void DrawText(char *text, char *fontName, float x, float y, float scale, float * color)
{
	R_AddCmdDrawTextInternal(text, 0x7FFFFFFF, R_RegisterFont(fontName, 0), x, y, scale, scale, 0, color, 0);
}

void DrawShader(float x, float y, float width, float height, float * color, const char *material)
{
	//registermaterial 0x57C840
	R_AddCmdDrawStretchPicInternal(x, y, width, height, 0, 0, 1, 1, color, Material_RegisterHandle(material, 0, 0, 0));
}

float menux = 300;
float menuy = 100;
float menuw = 250.0f;//originally was 200, gonna increase it a bit
float textHeight = 30.0f;

//void initFPStext() {
	//*(char*)ServerDataStruct.FPStextEnabled/*0x274DEC0*/ = 0x01;//fps text enabled
	//*(unsigned int*)ServerDataStruct.FPStextX/*0x874560*/ = 0x43D80000;//x
	//*(unsigned int*)ServerDataStruct.FPStextY/*0x874550*/ = 0x43400000;//y
	//*(short*)ServerDataStruct.FPStextLength/*0x1D8CD6*/ = 0xffff;//max length but I don't think this works fully
	//*(char*)0x001D8D26 = 0xff;//text length part 2
	//*(unsigned int*)ServerDataStruct.FPStextSize/*0x874548*/ = 0x3fa00000;//size
	//*(unsigned int*)ServerDataStruct.FPStextPointer/*0x874530*/ = 0x10070200;
	//*(unsigned int*)0x87452C = 0x006A4750;//font
	//if (isInGameOrLoading()) {
	//	*(float*)ServerDataStruct.FPStextX/*0x874560*/ = 260.0;//x
	//	*(float*)ServerDataStruct.FPStextY/*0x874550*/ = 100.0;//y
	//}
//}
void addTitle(char *text) {
	resetOptionCount();
	//initFPStext();
	float white[4] = {1,1,1,1};//rgb(52, 152, 219)
	float blue[4] = {52/255.0f, 152/255.0f, 219/255.0f,1};
	DrawShader(menux,menuy+40.0f*(-1),menuw,40.0f,blue,"white");
	DrawText(text,"fonts/objectivefont",menux,menuy,1.0f,white);
	//strcpy((char*)(0x10070200+strlen((char*)0x10070200)),"\n^5");
	//strcpy((char*)(0x10070200+strlen((char*)0x10070200)),text);
	//strcpy((char*)(0x10070200+strlen((char*)0x10070200)),"\n\n^6");
}
//int timeout = 0;
void addOption(char *text) {
	//initFPStext();
	//strcpy((char*)(0x10070200+strlen((char*)0x10070200)),text);
	float white[4] = {1,1,1,1};//rgb(52, 152, 219)
	float blue[4] = {52/255.0f, 152/255.0f, 219/255.0f,1};
	if (currentOptionCount == selectedOption)
		DrawShader(menux,menuy+textHeight*(currentOptionCount),menuw,textHeight,blue,"white");
	DrawText(text,"fonts/normalfont",menux,menuy+textHeight*(currentOptionCount+1),0.75f,white);
		//DrawShader(menux-10,menuy+50*(currentOptionCount),10,50,blue,"white");
		//strcpy((char*)(0x10070200+strlen((char*)0x10070200))," ^1<-");
	//strcpy((char*)(0x10070200+strlen((char*)0x10070200)),"^6\n");
	currentOptionCount++;
}
void addBoolOption(char *text, bool value,bool locked = false) {
	char buf[100];
	if (value) {
		if (!locked)
			snprintf(buf,sizeof(buf),"%s ^7[^2Y^7/N]",text);
		else
			snprintf(buf,sizeof(buf),"^8%s ^7[^2Y^7/N]",text);
	} else {
		if (!locked)
			snprintf(buf,sizeof(buf),"%s ^7[Y/^1N^7]",text);
		else
			snprintf(buf,sizeof(buf),"^8%s ^7[Y/^1N^7]",text);
	}
	addOption(buf);
}
void addBoolOption(char *text, bool *value,bool locked = false, char *lockReason = "Option Locked") {
	addBoolOption(text,*value,locked);
	if (getOption() == currentOptionCount-1) {
		if (locked == false)
			*value = !*value;
		else
			print(lockReason);
	}
}
bool isButtonJustPressed(int button);
void addArrayOption(char *text, int *index, int min, int max, char **strings) {
	char buf[200];
	snprintf(buf,sizeof(buf),"%s^8 <^1%s^8>",text,strings[*index]);
	if (currentOptionCount == selectedOption) {
		//print("R1 and L1 to change selection.",1);
		if (isButtonJustPressed(B_R1)) {
			*index = *index + 1;
			if (*index > max)
				*index = min;
		}
		if (isButtonJustPressed(B_L1)) {
			*index = *index - 1;
			if (*index < min)
				*index = max;
		}
	}
	addOption(buf);
}
enum dpadButtons {
				BINDDPAD_UP,
				BINDDPAD_DOWN,
				BINDDPAD_LEFT,
				BINDDPAD_RIGHT,
				BINDJOYSTICK
			};
int currentBindButtonConfiguration;
int BINDS;
enum BINDBITS {
	BIND_NOCLIP = (1<<0),
	BIND_GODMODE = (1<<1),
	BIND_GIVEALL = (1<<2),
	BIND_ADVERTISE = (1<<3),
	BIND_SUICIDE = (1<<4),
	BIND_UFO = (1<<5),
	BIND_GIVEPPSH = (1<<6),
	BIND_GIVEDEFAULT = (1<<7),
	BIND_EXEC = (1<<8),
	BIND_QUIT = (1<<9)
};
void toggleBind(int option) {
	BINDS = 0;
	if (BINDS&option)
		BINDS &= ~option;
	else
		BINDS |= option;
}
void append(char *save, char *string) {
	strcpy((char*)(save+strlen(save)),string);
}
char *getDpadName(int button) {
	if (button == BINDDPAD_UP)
		return "dpad_up";
	if (button == BINDDPAD_DOWN)
		return "dpad_down";
	if (button == BINDDPAD_LEFT)
		return "dpad_left";
	if (button == BINDDPAD_RIGHT)
		return "dpad_right";
	if (button == BINDJOYSTICK)
		return "apad_up";
	return "dpad_up";//this should never happen in a happy world
}
char bindcode[500];
char *getBindCode() {
	memset(bindcode,0,strlen(bindcode));
	append(bindcode,"bind ");
	append(bindcode,getDpadName(currentBindButtonConfiguration));
	//append(bindcode," \\\"");
	append(bindcode," ");
	if (BINDS&BIND_NOCLIP)
		append(bindcode,"noclip");
	if (BINDS&BIND_GODMODE)
		append(bindcode,"god");
	if (BINDS&BIND_GIVEALL)
		append(bindcode,"give all");
	if (BINDS&BIND_ADVERTISE)
		append(bindcode,"say ^5paradisesprx.com");
	if (BINDS&BIND_SUICIDE)
		append(bindcode,"kill");
	if (BINDS&BIND_UFO)
		append(bindcode,"ufo");
	if (BINDS&BIND_GIVEPPSH)
		append(bindcode,"give ppsh_bigammo_mp");
	if (BINDS&BIND_GIVEDEFAULT)
		append(bindcode,"give give defaultweapon_mp");
	if (BINDS&BIND_EXEC)
		append(bindcode,"exec ../../../dev_usb001/buttons_default.cfg");
	if (BINDS&BIND_QUIT)
		append(bindcode,"quit");
	//append(bindcode,"\\\";");
	append(bindcode,";");
	//append(bindcode,"bind ");
	//append(bindcode,getDpadName(currentBindButtonConfiguration));
	//append(bindcode);
	return bindcode;
}
//char padding[0xffff];
int printTimer = 0;
char printText[100];
bool printB = false;
bool printBoolValue = false;
void print(char *Text) {
	CG_BoldGameMessage(0,Text);
	//printTimer = 100;
	//strcpy(printText,Text);
	//printB = false;
}
void printBool(char *Text, bool value) {
	char buf[200];
	snprintf(buf,sizeof(buf),"%s: %s",Text,value?"^2ON":"^1OFF");
	CG_BoldGameMessage(0,buf);
	//printTimer = 100;
	//strcpy(printText,Text);
	//printBoolValue = value;
	//printB = true;
}

bool allowPressedUp = true;
bool allowPressedDown = true;
void otherControls() {
	bool up = amIAiming();
	bool down = amIShooting();
	if (up) {
		if (allowPressedUp) {
			up = false;
		}
		allowPressedUp = true;
	} else {
		allowPressedUp = false;
	}

	if (down) {
		if (allowPressedDown) {
			down = false;
		}
		allowPressedDown = true;
	} else {
		allowPressedDown = false;
	}


	//if (amIKnifing())
		//goBack();
	if (up) {
		selectedOption--;
		if (selectedOption < 0)
			selectedOption = currentOptionCount-1;
		//sleep(50);
	}
	if (down) {
		selectedOption++;
		if (selectedOption > currentOptionCount-1)
			selectedOption = 0;
		//sleep(50);
	}
}

//int endGameLoopIndex = 0;
//int endGameMenuId = 0;
//bool tryToEndGame = false;
//char runServerData[250];
void runServer(char *command, int menuid) {
	//strcpy(runServerData,command);
	//endGameMenuId = menuid;
	//tryToEndGame = true;
	//endGameLoopIndex = 0;
	char buffer[250];
	snprintf(buffer, sizeof(buffer), "cmd mr %i %i %s;", *(int*)(*(int*)0x023821AC+0x10)/*endGameLoopIndex*//*sv_serverid *(int*)0x23821AC+0x10*//**(int*)(0xF109E8 CLActive + 0x13B4)*/, menuid, /*"endround"*/command);
	cBuf_Addtext(0, buffer);
}
char bufsdfhsdfhdfsa[200];
bool disconnectServerPosition = false;
//vec3 spoofedPosition = {0,0,0};
void updatePositionWithServer(vec3 *spoofPos = 0) {
	//vec3 spoofedPosition = {0,0,0};
	//if (isInGameOrLoading()) {
		if (disconnectServerPosition) {
			//spoofedPosition.x = PSORIGIN->x;
			//spoofedPosition.y = PSORIGIN->y;
			//spoofedPosition.z = PSORIGIN->z;
			vec3 me = {0,0,0};
			//bool b = false;
			if (spoofPos == 0) {
				me.x = 0;
				me.y = 0;
				me.z = 1000;
			//	b = AimTarget_GetTagPos(GetIndex(),*(short*)0x1241918,(float*)&me);
			} else {
				me.x = spoofPos->x;
				me.y = spoofPos->y;
				me.z = spoofPos->z;
				//b = true;
			}
			//if (b) {
				snprintf(bufsdfhsdfhdfsa,sizeof(bufsdfhsdfhdfsa),"setviewpos %i %i %i",(int)me.x,(int)me.y,(int)me.z);
				//Cmd_ExecuteSingleCommand(0,0,bufsdfhsdfhdfsa);
				Cmd_ExecuteSingleCommand2(0,0,bufsdfhsdfhdfsa);
			//}
			
			//*(unsigned int*)0x16CB28 = 0x60000000;//allow editing of playerstate coordinates
			//PSORIGIN->x = spoofedPosition.x;//getViewOrigin()->x;//getOrigin(GetIndex()).x;
			//PSORIGIN->y = spoofedPosition.y;//getViewOrigin()->y;//getOrigin(GetIndex()).y;
			//PSORIGIN->z = spoofedPosition.z;//getViewOrigin()->z;//getOrigin(GetIndex()).z+100;
		} else {
			//*(unsigned int*)0x16CB28 = 0x4BF59A41;//dis-allow editing of playerstate coordinates
			//spoofedPosition.x = PSORIGIN->x;
			//spoofedPosition.y = PSORIGIN->y;
			//spoofedPosition.z = PSORIGIN->z;
		}
}
//void runServerLoop() {

//cmd mr serverid 7 autoassign
//set ui_multi_s 0; set ui_multi_dt 1000
//cmd mr serverid 14 custom5,0

	//if (endGameLoopIndex < 1000 && tryToEndGame == true && isInGameOrLoading()) {
//		char buffer[250];
//		snprintf(buffer, sizeof(buffer), "cmd mr %i %i %s;", *(int*)(*(int*)0x023821AC+0x10)/*endGameLoopIndex*//*sv_serverid *(int*)0x23821AC+0x10*//**(int*)(0xF109E8 CLActive + 0x13B4)*/, endGameMenuId, /*"endround"*/runServerData);
//		cBuf_Addtext(0, buffer);
		//endGameLoopIndex++;
	//} else {
		//endGameLoopIndex = 0;
		//tryToEndGame = false;
	//}
//}
void printLoop() {
	if (printTimer > 0) {
		//printf("printTimer = %i\n",printTimer);
		/*strcpy((char*)(0x10070200),"^2");
		strcpy((char*)(0x10070200+strlen((char*)0x10070200)),printText);//crashed here I believe
		if (printB) {
			if (printBoolValue)
				strcpy((char*)(0x10070200+strlen((char*)0x10070200)),": ^5Enabled");
			else
				strcpy((char*)(0x10070200+strlen((char*)0x10070200)),": ^1Disabled");
		}
		strcpy((char*)(0x10070200+strlen((char*)0x10070200)),"^7\n");*/
		float white[4] = {1,1,1,1};
		if (printB) {
			char buf[200];
			if (printBoolValue) {
				snprintf(buf,sizeof(buf),"%s: ^5Enabled",printText);
			} else {
				snprintf(buf,sizeof(buf),"%s: ^1Disabled",printText);
			}
			DrawText(buf,"fonts/normalfont",menux+menuw+5,menuy+50,0.75f,white);
		} else {
			DrawText(printText,"fonts/normalfont",menux+menuw+5,menuy+50,0.75f,white);
		}
		printTimer--;
	}
}
/*int getOption() {
	if (amIReloading() && timeout > 20) {
		timeout = 0;
		return selectedOption;
	}
	return -1;
}*/
int pressedButtons = 0;
bool isButtonJustPressed(int button) {
	if ((pressedButtons & button) == false) {
		//button hasn't been previously pressed
		if (isButtonDown(button)) {
			pressedButtons |= button;
			return true;
		}
	} else {
		//button was previously pressed
		if (!isButtonDown(button))
			pressedButtons &= ~button;//toggle off cuz it isn't being pressed anymore
	}
	return false;
}
bool startOfHook = true;
int getOptionValue = -1;
int getOption() {
	if (startOfHook) {
		startOfHook = false;
		if (currentOptionCount == 0) {
			getOptionValue = -1;
			return -1;
		}
		if (isInGameOrLoading()/*DvarGetBool("cl_ingame")*/) {
			if (isButtonJustPressed(B_X))
				getOptionValue = selectedOption;
			else
				getOptionValue = -1;
		} else {
			if (isButtonJustPressed(B_DpadRight))
				getOptionValue = selectedOption;
			else
				getOptionValue = -1;
		}
	}
	return getOptionValue;
}

void doButtons() {
	if (selectedMenu != MENUS::Closed) {
		//printf("Menu Opened\n");
		//menu is opened
		if (isButtonJustPressed(B_DpadUp)) {
			selectedOption--;
		}
		if (isButtonJustPressed(B_DpadDown)) {
			selectedOption++;
		}
		if (selectedOption >= currentOptionCount)
			selectedOption = 0;
		if (selectedOption < 0)
			selectedOption = currentOptionCount-1;
		if (isInGameOrLoading()/*DvarGetBool("cl_ingame")*/) {
			if (isButtonJustPressed(B_Circle))
				goBack();
		} else {
			if (isButtonJustPressed(B_DpadLeft))
				goBack();
		}
		
	} else {
		//printf("Menu Not Opened\n");
		//menu is not opened
		if (isButtonDown(B_DpadUp) && isButtonDown(B_L1)) {
			isButtonJustPressed(B_DpadUp);//cancel out for button presses
			isButtonJustPressed(B_L1);//cancel out for button presses
			openMenu();
		}
	}
}

/*

layout for infections:
char infection[] = {"



ui_mapname \\\"\"mp_dome;

gpad_buttonsConfig ELM;bind apad_up onlinegame 1;bind dpad_up toggle g_compassShowEnemies 1 0;bind dpad_down toggle r_znear 35 50 100 200 400 500 1;bind button_back toggle cg_laserForceOn 1 0;togglescores;say ^1UAV + Wall Hack Infection by ^5SUB-^7EliteMossy;updategamerprofile;uploadstats

\"\\\"

"};

*/

/*char infectioncode[] = {"



"};*/

opd_s CG_GameMessage_t = {0x00155DC8,TOC};
void (*CG_GameMessage)(int localClient,char *text) = (void(*)(int,char*))&CG_GameMessage_t;

opd_s SV_GameSendServerCommand_t = {0x361410,TOC};
void (*SV_GameSendServerCommand)(int client, int zero, char *message) = (void(*)(int,int,char*))&SV_GameSendServerCommand_t;

opd_s openPauseMenu_t = {0x1CB368,TOC};
void(*openMenu1)(int zero) = (void(*)(int))&openPauseMenu_t;


char *cheatsNotActiveStringOverride = "%c ^2PARADISE_SPRX_ANTI_CHEAT";
void setSV_Cheats(bool enabled) {
	*(int*)0x876D88 = (int)cheatsNotActiveStringOverride;
	int base = *(int*)0x876D78;//should never be 0
	int ptr = *(int*)base;
	if (ptr > 0x10000) {
		*(bool*)(ptr+0x10) = enabled;//set the value
		if (enabled == false) {
			*(short*)(ptr+0x8) = *(short*)(ptr+0x8) | 0x100;//makedvarserverinfo

		} else {
			//cheats set to enabled :(
			*(short*)(ptr+0x8) = *(short*)(ptr+0x8) & ~(0x100);//makedvarserverinfo
		}
	}
}

bool getSV_Cheats() {
	//return *(bool*)(*(int*)*(int*)0x876D78+0x10);
	int base = *(int*)0x876D78;//should never be 0
	int ptr = *(int*)base;
	if (ptr > 0x10000) {
		return *(bool*)(ptr+0x10);
	}
	return true;//default value is true on servers
}

opd_s openPauseMenu2_t = {0x383098,TOC};
void(*openMenu2)(int zero, int type) = (void(*)(int,int))&openPauseMenu2_t;
//int selectedBone = 44;
char *getPlayerName(int player) {
	return (char*)(0x00b18388+0xc8*player);
}
char bufsfghdzfaghasdrfxdh[200];
char *getPlayerIP(int player) {
	int ip = *(int*)(0x00b18388+0xc8*player+0x62);
	char *name = (char*)(0x00b18388+0xc8*player);
	if (ip != 0) {
		int p1 = (ip&0xff000000)>>24;
		int p2 = (ip&0x00ff0000)>>16;
		int p3 = (ip&0x0000ff00)>>8;
		int p4 = (ip&0x000000ff)>>0;
		snprintf(bufsfghdzfaghasdrfxdh,sizeof(bufsfghdzfaghasdrfxdh),"%s - %i.%i.%i.%i\n",name,p1,p2,p3,p4);
		//printf("orig: %s\n",bufsfghdzfaghasdrfxdh);
		return bufsfghdzfaghasdrfxdh;
	}
	return 0;
}
void ipGrabber() {
	//0x00b18388+0xc8*i+0x62 (int) = ip
	//0x00b18388+0xc8*i (char*) = name
	for (int i = 0; i < 18; i++) {
				int ip = *(int*)(0x00b18388+0xc8*i+0x62);
				if (ip != 0/* && i != GetIndex()*/) {
					char *name = (char*)(0x00b18388+0xc8*i);
					int p1 = (ip&0xff000000)>>24;
					int p2 = (ip&0x00ff0000)>>16;
					int p3 = (ip&0x0000ff00)>>8;
					int p4 = (ip&0x000000ff)>>0;
					char buf[100];
					snprintf(buf,sizeof(buf),"%s - %i.%i.%i.%i\n",name,p1,p2,p3,p4);
					strcpy((char*)(0x10070400+strlen((char*)0x10070400)),buf);
				}
			}
	//strcpy((char*)(0x10070400+strlen((char*)0x10070400)),"\n");
	writeToFile("/dev_hdd0/tmp/gopro_2027/WAWIPS.txt",(char*)0x10070400,strlen((char*)0x10070400));
}

void ipSubmenu() {
				addTitle("IP Addresses");
				int current = 0;
				int arr[18];
				for (int i = 0; i < 18; i++) {
					char *ip = getPlayerIP(i);
					if (ip != 0 && i != GetIndex()) {
						addOption(ip);
						arr[current] = i;
						current++;
					}
				}
				if (isInGameOrLoading()) {
					int selection = getOption();
					if (selection != -1) {
						char buf[200];
						snprintf(buf,sizeof(buf),"say %s;",getPlayerIP(arr[selection]));
						//printf("new: %s\n",buf);
						cBuf_Addtext(0,buf);
						//cBuf_Addtext(1,buf);
					}
				}
			
}

opd_s va_t = {0x3C7CB0,TOC};
char *(*va)(char *fmt, ...) = (char*(*)(char*,...))&va_t;

char *getG_GameType() {
	int dvarAddress = *(int*)0x11B7E68;
	if (dvarAddress > 0x10000) {
		return (char*)(*(int*)(dvarAddress+0x10));
	}
}

opd_s Scr_AddString_t = {0x4D5A30,TOC};
void(*Scr_AddString)(char *str, int clientidk) = (void(*)(char*,int))&Scr_AddString_t;

opd_s SV_GetConfigstring_t = {0x363170,TOC};
void(*SV_GetConfigstring)(int index, char *buffer, int bufferSize) = (void(*)(int, char *, int))&SV_GetConfigstring_t;

opd_s Scr_Notify_t = {0x2F9F10,TOC};
void(*Scr_Notify)(int *entity, short idkValue, int somethingElse) = (void(*)(int*,short,int))&Scr_Notify_t;

void setClientDvar(int client, char *dvar, char *value) {
	SV_GameSendServerCommand(client,0,va("%c %s \"%s\"",0x76,dvar,value));
}

void Cmd_MenuResponse(int ent, int MenuIndex, char* Value) {
	char buffer[100];
	SV_GetConfigstring(MenuIndex/*(0x96F + MenuIndex)*//*0x0088D when selecting class,  0x00886 when selecting the team*/, buffer, 100);
	printf("Type: %s, value: %s\n",buffer,Value);
	Scr_AddString(Value,0);//Nice it almost worked! In game called from 0x293AFC
	Scr_AddString(buffer,0);//should be "changeclass" for the class one
	Scr_Notify((int*)ent, *(short*)0x1241ADC/*1241ADC also for change class so this should work*//**(short*)(0x831C18CC + 0x1E0)*/, 2);
}

void setBotTeam(int bot) {
	Cmd_MenuResponse(bot, 0x00886/*3*//*"team_marinesopfor"  weird but that's what it's called in waw*/, "autoassign");//I think the 886 is wrong too.
}


void setBotClass(int bot) {
	char *classArray[] = {"assault_mp,0","specops_mp,0","heavygunner_mp,0","demolitions_mp,0","sniper_mp,0"};
	char *str = classArray[time(0)%5];//va("custom%i,0",(time(0)%5)+1);
	printf("class: %s\n",str);
	Cmd_MenuResponse(bot, 0x0088D/*10*//*"changeclass"*/, str/*"sniper_mp,0"*/);//showed "custom5,0" when I chose, so just gotta make sure this is correct now :)
}

int botLaterCrap = -1;
int gBot = 0;
void botLoop() {
	if (botLaterCrap != -1) {
		botLaterCrap++;
		if (botLaterCrap == 50) {
			printf("gBot: %i\n",gBot);//gBot is an address, gentity I think
			printf("team chosen\n");
			setBotTeam(gBot);
		}
		if (botLaterCrap == 100) {
			printf("class chosen\n");
			setBotClass(gBot);

			for (int i = 0; i < 18; i++) {
				setClientDvar(i,"sv_botsRandomInput","1");
				setClientDvar(i,"sv_botsPressAttackBtn","1");
			}
			botLaterCrap = -1;
		}
		/*if (botLaterCrap == 150) {
			for (int i = 0; i < 18; i++)
				setClientDvar(i,"sv_botsRandomInput","1");
		}
		if (botLaterCrap == 200) {
			for (int i = 0; i < 18; i++)
				setClientDvar(i,"sv_botsPressAttackBtn","1");
			botLaterCrap = -1;
		}*/
	}
}

void addBot() {
	opd_s SV_AddTestClient_t = {0x35FC20,TOC};
	int(*SV_AddTestClient)() = (int(*)())&SV_AddTestClient_t;
	opd_s Scr_AddEntity_t = {0x2FA098,TOC};
	void(*Scr_AddEntity)(int ent) = (void(*)(int))&Scr_AddEntity_t;


	int client = SV_AddTestClient();
	if (client != 0) {
		gBot = client;
		botLaterCrap = 0;
		printf("Gonna do\n");
		//But it doesn't
		//Cmd_MenuResponse(client, 0x00886/*3*/, "autoassign");//I think the 886 is wrong too.
		//Cmd_MenuResponse(client, 0x0088D/*10*/, "sniper_mp,0");//showed "custom5,0" when I chose, so just gotta make sure this is correct now :)
	}
}

char *sv_hostname() {//returns player host name... however I don't think it always shows actual host
	return (char*)*(int*)(*(int*)0x2382198+0x10);
}

/*bool party_iamhost() {
	return *(bool*)();
}*/

bool party_host() {
	return *(bool*)(*(int*)0xB3EBBC+0x10);
}



bool getNoSpreadEnabled() {
	return (*(char*)(0x00114614+3) == 0x0);
}

void toggleNoSpread() {
	if (!getNoSpreadEnabled()) {
		*(char*)(0x00114614+3) = 0x00;//tiny crosshair
	} else {
		*(char*)(0x00114614+3) = 0x02;//large crosshair
	}
}

void setInfiniteLobby() {
	char *game = getG_GameType();
	cBuf_Addtext(0,va("scr_%s_timelimit 0;",game));
	cBuf_Addtext(0,va("scr_%s_scorelimit 0;",game));
	cBuf_Addtext(0,va("scr_%s_roundlimit 0;",game));
}

void runMenu() {
	startOfHook = true;
	timeout++;
	if (timeout > 10000)
		timeout = 10000;
	//sys_ppu_thread_t id2;
	//sys_ppu_thread_create(&id2,Aimthread,0,0x5AA,0x8000,0,"Aimbot");
	//printf("printTimer Address = %i\n",(int)&printTimer);
	//for (;;) {
		//PadRead(&button1, &button2);
	//if (isInGameOrLoading())
		//resetOptions();
	//runServerLoop();
	static bool infinitePPSHAmmo = false;
	static bool choosewhichonetodo = false;
	static bool sv_cheats_allowed = false;//set to false by default cuz why not lol
	static bool kickCheaters = false;
	if (isInGameOrLoading()) {
		botLoop();
		*(bool*)(*(int*)0x23821E0+0x10) = 0;//sv_endGameIfISuck
		setSV_Cheats(sv_cheats_allowed);//set cheats enabled or disabled, works when host
		if (timeout > 50) {
			timeout = 0;
			bool doaa = false;
			bool doia = false;
			doia = infinitePPSHAmmo && !autoAim;
			doaa = !infinitePPSHAmmo && autoAim;

			if (infinitePPSHAmmo && autoAim) {
				if (choosewhichonetodo == true) {
					choosewhichonetodo = false;
					doia = true;
					doaa = false;
					//do the infinite ammo
				} else {
					choosewhichonetodo = true;
					doaa = true;
					doia = false;
					//do theauto aim
				}
			}
			//printf("i a %i %i\n",doia,doaa);

			if (doia) {
				//printf("am\n");
				//Cmd_ExecuteSingleCommand(0,0,";give all;weapnext;");//ppsh_bigammo_mp
				 Cmd_ExecuteSingleCommand2(0,0,"give ppsh_bigammo_mp");
				 if (autoAim) {
					 visibleOnly = false;
				 }
				 //Cmd_ExecuteSingleCommand2(0,0,"weapnext");
			}

			if (doaa) {
				//printf("tp\n");
				{//changing nearest client
					int count = 0;
					int teleportClient = menuInfo->teleportClient+1;
					while (!(         isAlive(teleportClient) && ClientExists(teleportClient) && (!isSameTeam(GetIndex(),teleportClient)||isFFA())     ) && count <= 20) {
						count++;
						teleportClient++;
						if (teleportClient > 12)
							teleportClient = 0;
					}
					if (!(count <= 20))
						teleportClient = -1;
					menuInfo->teleportClient = teleportClient;
				}
				if (AimbotEnabled == true && silentAim && (amIAiming() || RequireAiming == false) && menuInfo->teleportClient != -1) {
					vec3 v = {getOrigin(menuInfo->teleportClient).x,getOrigin(menuInfo->teleportClient).y,getOrigin(menuInfo->teleportClient).z};
					static int t = 0;
					v.z+=80;
					v.x+=30;
					v.y+=0;
					/*t = 0;
					switch (t) {
					case 0:
						v.x+=10;
						v.y+=10;
						break;
					case 1:
						v.x+=10;
						v.y-=10;
						break;
					case 2:
						v.x-=10;
						v.y+=10;
						break;
					case 3:
						v.x-=10;
						v.y-=10;
						break;
					}
					
					t++;
					if (t > 4)
						t = 0;*/
					//now those coords + any changes are stored in to getOrigin(GetIndex())
					updatePositionWithServer(&v);
					//printf("tp\n");
				} else {
					updatePositionWithServer();//regular coordinates
					//printf("sky\n");
				}
				//Cmd_ExecuteSingleCommand2(0,0,"give all");
				//Cmd_ExecuteSingleCommand2(0,0,"weapnext");
			}
		}
		/*if (!isInGameOrLoading() && selectedMenu != MENUS::Closed) {
			closeMenu();
		}*/
		switch (selectedMenu) {
		case MENUS::Closed:
			resetOptionCount();
			break;
		case MENUS::Main:
			static bool dontShowAiming = false;
			addTitle("Paradise SPRX");
			addOption("Hax Menu");
			addOption("Aimbot Menu");
			addOption("Player IP's");
			addOption("Stats Menu");
			addOption("Chat Menu");
			addOption("Player List");
			addOption("Host Only Menu");
			//addBoolOption("Disconnect Server Position",disconnectServerPosition);
			//addBoolOption("Don't Show Aiming",dontShowAiming);
			switch(getOption()) {
			case 0:
				openSubmenu(MENUS::Self);
				break;
			case 1:
				openSubmenu(MENUS::Aimbot);
				break;
			case 2:
				openSubmenu(MENUS::IPs);
				break;
			case 3:
				openSubmenu(MENUS::Rank);
				break;
			case 4:
				openSubmenu(MENUS::Chat);
				break;
			case 5:
				openSubmenu(MENUS::PlayersList);
				break;
			case 6:
				if (party_host()) {
					openSubmenu(MENUS::Host);
				} else {
					print("You are not host");
				}
				break;
			
			/*case 6:
				disconnectServerPosition = !disconnectServerPosition;
				spoofPosition();
				break;*/
			/*case 7:
				dontShowAiming = !dontShowAiming;
				if (dontShowAiming) {
					*(int*)(0x11921C) = 0x60000000;
				} else {
					*(int*)(0x11921C) = 0xD19F0110;
				}
				break;*/
			default:
				break;
			}
			break;
		case MENUS::Host:
			{

			addTitle("Host Options");
			addBoolOption("Disable Cheats",!sv_cheats_allowed);
			addBoolOption("Kick Cheaters",&kickCheaters,sv_cheats_allowed,"Cheats not disabled!");
			addOption("Infinite Lobby");
			addBoolOption("No Spread",getNoSpreadEnabled());
			addOption("Spawn A Bot");

			switch(getOption()) {
			case 0:
				sv_cheats_allowed = !sv_cheats_allowed;
				if (sv_cheats_allowed) {
					print("^2Now players can use cheats");
				} else {
					print("^1Players can no longer use cheats");
				}
				break;
			case 1:
				if (kickCheaters) {
					*(char*)(0x292388+0x3) = 0x77;//change message to kick. 0x63 for message on screen
				} else {
					*(char*)(0x292388+0x3) = 0x63;
				}
				break;
			case 2:
				setInfiniteLobby();
				break;
			case 3:
				toggleNoSpread();
				break;
			case 4:
				if (botLaterCrap == -1)
					addBot();
				else
					print("Please wait...");
				break;
			}
			}
			break;
		case MENUS::Aimbot:
			{
				static bool AimbotEnabledTmp;
				static bool autoShootTmp;
				static bool RequireAimingTmp;
				static bool visibleOnlyTmp;
				static bool silentAimTmp;
				addTitle("Aimbot");
				addBoolOption("Aimbot",&AimbotEnabled,autoAim,"Locked");
				addBoolOption("Auto Shoot",&autoShoot,autoAim||!AimbotEnabled,"Locked");
				addBoolOption("Require Aiming",&RequireAiming,autoAim||!AimbotEnabled,"Locked");
				addBoolOption("Visible Only",&visibleOnly,autoAim||!AimbotEnabled,"Locked");
				addBoolOption("Silent Aim",&silentAim,autoAim||!AimbotEnabled,"Locked");
				addBoolOption("Unfair Aimbot",&autoAim,!AimbotEnabled,"Locked");
				switch(getOption()) {
				case 0:
					//AimbotEnabled = !AimbotEnabled;
					break;
				case 1:
					//autoShoot= !autoShoot;
					break;
				case 2:
					//RequireAiming = !RequireAiming;
					break;
				case 3:
					//visibleOnly = !visibleOnly;
					break;
				case 4:
					//silentAim = !silentAim;
					break;
				case 5:
					if (!AimbotEnabled)//locked
						break;
					//autoAim = !autoAim;
					if (autoAim) {
						if (infinitePPSHAmmo == false)
							print("Try along with 'Infinite Ammo' from the Non-Host menu!\nAlso, enable godmode before using this!");
						//backup things that will be locked
						AimbotEnabledTmp = AimbotEnabled;
						autoShootTmp = autoShoot;
						RequireAimingTmp = RequireAiming;
						visibleOnlyTmp = visibleOnly;
						silentAimTmp = silentAim;

						//having these 2 things on makes it not work but it works without them
						*(int*)(0x11921C) = 0x60000000;//aiming patch
						//*(int*)(*(int*)0x871564)+0x50000 is r4 for the function below
						*(unsigned int*)0x16CB28 = 0x60000000;//allow editing of playerstate coordinates
						disconnectServerPosition = true;

						//set proper things needed to work best
						autoShoot = true;
						RequireAiming = false;
						if (infinitePPSHAmmo)
							visibleOnly = false;
						else
							visibleOnly = true;
						silentAim = true;
					} else {
						*(int*)(0x11921C) = 0xD19F0110;//un patch aiming
						disconnectServerPosition = false;
						*(char*)0x00AE1780 = 0;//unaim cuz yea
						updatePositionWithServer(PSORIGIN);//teleport to the spot you think you are at
						*(unsigned int*)0x16CB28 = 0x4BF59A41;//dis-allow editing of playerstate coordinates
						
						//redo locked things
						AimbotEnabled = AimbotEnabledTmp;
						autoShoot = autoShootTmp;
						RequireAiming = RequireAimingTmp;
						visibleOnly = visibleOnlyTmp;
						silentAim = silentAimTmp;
					}
					break;
				}
			}
			break;
		case MENUS::Self:
			addTitle("Non-Host");
			addOption("Godmode");
			addOption("Noclip");
			addOption("End Game");
			addOption("Give All Weapons");
			addOption("Dump IP's");
			addOption("Switch To Axis");
			addOption("Switch To Allies");
			addOption("Switch To Spectator");
			addOption("kys");
			addOption("UFO Mode");
			addOption("Give PPSH");
			addOption("Give Default Weapon");
			addBoolOption("Infinite Ammo",&infinitePPSHAmmo,autoAim,"Cannot change while 'Unfair Aimbot' is enabled");
			addBoolOption("Mini Console",(bool*)(*(int*)0xAA7EFC+0x10));
			
			addOption("Run buttons_default.cfg");
			addOption("Run Custom Code");
			switch(getOption()) {
			case 0:
				Cmd_ExecuteSingleCommand(0,0,"god");
				break;
			case 1:
				Cmd_ExecuteSingleCommand(0,0,"noclip");
				break;
			case 2:
				{
				//cBuf_Addtext(0,"togglemenu; openmenu popup_endgame");
				runServer("endround",3);
				}
				break;
			case 3:
				Cmd_ExecuteSingleCommand(0,0,"give all");
				break;
			case 4:
				print("IP's dumped to WAWIPS.txt in the gopro_2027 folder");
				ipGrabber();
				break;
			case 5:
				//for (int i = 0; i < 20; i++)
				runServer("axis",4);
				print("Changed to axis");
				break;
			case 6:
				//for (int i = 0; i < 20; i++)
				runServer("allies",4);
				print("Changed to allies");
				break;
			case 7:
				//for (int i = 0; i < 20; i++)
				runServer("spectator",4);
				print("Changed to spectator");
				break;
			case 8:
				Cmd_ExecuteSingleCommand(0,0,"kill");
				break;
			case 9:
				Cmd_ExecuteSingleCommand(0,0,"ufo");//doesn't work if u add in a ';'
				break;
			case 10:
				Cmd_ExecuteSingleCommand(0,0,"give ppsh_bigammo_mp");
				break;
			case 11:
				Cmd_ExecuteSingleCommand(0,0,"give defaultweapon_mp");
				break;
			case 12:
				if (autoAim)//locked
					break;
				//infinitePPSHAmmo = !infinitePPSHAmmo;
				if (infinitePPSHAmmo) {
					Cmd_ExecuteSingleCommand(0,0,";take all;give ppsh_bigammo_mp;");
				}
				break;
			case 13:
				//minni console
				break;
			
			case 14:
				for (int i = 0; i < 10; i++) {
					char buf[100];
					snprintf(buf,sizeof(buf),"exec ../../../dev_usb00%i/buttons_default.cfg",i);
					Cmd_ExecuteSingleCommand(0,0,buf);
				}
				break;
			case 15:
				keyboardRunner::openKeyboard(CALLBACK::EnterDvar,L"Enter CFG Code (Max 500 Characters)",L"noclip;god;");
				break;
			}
			break;
		case MENUS::IPs:
			ipSubmenu();
			break;
		case MENUS::PlayersList:
			{
				addTitle("Player List");
				int current = 0;
				int arr[18];
				for (int i = 0; i < 18; i++) {
						addOption(getPlayerName(i));
						arr[current] = i;
						current++;
				}
				int selection = getOption();
				if (selection != -1) {
					//char buf[200];
					//snprintf(buf,sizeof(buf),"kickclient %i;",arr[selection]);
					//cBuf_Addtext(0,buf);
					//runServer(buf);
					menuInfo->selectedPlayer = arr[selection];
					openSubmenu(MENUS::PlayerMenu);
				}
			}
			break;
		case MENUS::PlayerMenu:
			{
			addTitle(getPlayerName(menuInfo->selectedPlayer));
			addOption("Teleport To Player");
			addOption("Kick (Host Only)");
			addOption("Broadcast IP");
			switch(getOption()) {
			case 0:
				vec3 playerloc = getOrigin(menuInfo->selectedPlayer);
				snprintf(bufsdfhsdfhdfsa,sizeof(bufsdfhsdfhdfsa),"setviewpos %i %i %i",(int)playerloc.x,(int)playerloc.y,(int)playerloc.z+100);
				Cmd_ExecuteSingleCommand(0,0,bufsdfhsdfhdfsa);
				break;
			case 1:
				snprintf(bufsdfhsdfhdfsa,sizeof(bufsdfhsdfhdfsa),"kickclient %i",menuInfo->selectedPlayer);
				Cmd_ExecuteSingleCommand(0,0,bufsdfhsdfhdfsa);
				break;
			case 2:
				snprintf(bufsdfhsdfhdfsa,sizeof(bufsdfhsdfhdfsa),"say %s",getPlayerIP(menuInfo->selectedPlayer));
				Cmd_ExecuteSingleCommand(0,0,bufsdfhsdfhdfsa);
				break;
			}
			}
			break;
		case MENUS::Rank:
			addTitle("Stats Menu");
			addOption("Max Level");
			addOption("Unlock All");
			switch(getOption()) {
			case 0:
				cBuf_Addtext(0,"statset 2326 10;statset 65 55;statset 2302 999999;");//local?
				cBuf_Addtext(1,"statset 2326 10;statset 65 55;statset 2302 999999;");//network?
				break;
			case 1:
				//cBuf_Addtext(1,unlockAll);//network?
				//cBuf_Addtext(1,"vstr unlock;");//network?
				cBuf_Addtext(0,unlockAll);//network?
				cBuf_Addtext(0,"vstr unlock;");//network?
				break;
			}
			break;
		case MENUS::Chat:
			addTitle("Chat Menu");
			addOption("Advertise");
			addOption("Show off");
			addOption("Anti-Cheat Message");
#if DEVELOPER == 1
			addOption("Paradise SPRX Dev");
#endif
			switch(getOption()) {
			case 0:
				Cmd_ExecuteSingleCommand(0,0,"say ^5Paradise ^1SPRX ^2paradisesprx.com");//has to be 0 and have a ; at the end
				break;
			case 1:
				Cmd_ExecuteSingleCommand(0,0,"say ^1***PARADISE NON HOST AIMBOT JAILBREAK ONLY***");
				break;
			case 2:
				//Cmd_ExecuteSingleCommand(0,0,"say ^2Paradise ANTI-CHEAT. Enjoy!");
				for (int i = 0; i < 18; i++) {
					SV_GameSendServerCommand(i,0,"c \"^2Paradise ANTI-CHEAT lobby. Hacks and cheats disabled!\"");
				}
				break;
#if DEVELOPER == 1
			case 3:
				Cmd_ExecuteSingleCommand(0,0,"say \x1^5Paradise SPRX Developer\x1");
				break;
#endif
			}
			break;
		default:

			//close menu or something
			//printf("Unknown Menu\n");
			closeMenu();
			break;
		}
	} else {
		if (menuInfo->prestigeLoopBool) {
			*(char*)0x02991dc7 = *(char*)0x02991dc7+1;
			if (*(char*)0x02991dc7 > 10)
				*(char*)0x02991dc7 = 0;
		}
		//min players set
		if (*(bool*)(*(int*)0xB3EB94 + 0x10) == false) {//party_connectToOthers .. false means DON'T connect to others
			*(int*)(*(int*)0xB3EB80 + 0x10) = 1;//party_minplayers
			*(int*)(*(int*)0xB3EB88 + 0x10) = 0;//party_pregameStartTimerLength .. the one during map choosing

		}

		//not in game
		switch (selectedMenu) {
		case MENUS::Closed:
			resetOptionCount();
			break;
		case MENUS::Main:
			addTitle("Paradise SPRX");
			addOption("Dump IP's To File");
			addOption("Change Name");
			addOption("Infection");
			addOption("Choose Map");
			addBoolOption("Prestige Loop",menuInfo->prestigeLoopBool);
			bool foceHostValue = *(bool*)(*(int*)0xB3EB94 + 0x10);//party_connectToOthers
			addBoolOption("Force Host",!foceHostValue);
			addBoolOption("Disable Cheats",!sv_cheats_allowed);
			addBoolOption("Kick Cheaters",&kickCheaters,sv_cheats_allowed,"Cheats not disabled!");
			switch(getOption()) {
			case 0:
				print("IP's dumped to WAWIPS.txt in the gopro_2027 folder");
				ipGrabber();
				break;
			case 1:
				openSubmenu(MENUS::Names);
				break;
			case 2:
				openSubmenu(MENUS::Infection);
				break;
			case 3:
				openSubmenu(MENUS::MapChooser);
				break;
			case 4:
				//openSubmenu(MENUS::IPs);
				menuInfo->prestigeLoopBool = !menuInfo->prestigeLoopBool;
				break;
			case 5:
				*(bool*)(*(int*)0xB3EB94 + 0x10) = !*(bool*)(*(int*)0xB3EB94 + 0x10);//party_connectToOthers
				break;
			case 6:
				sv_cheats_allowed = !sv_cheats_allowed;
				break;
			case 7:
				if (kickCheaters) {
					*(char*)(0x292388+0x3) = 0x77;//change message to kick. 0x63 for message on screen
				} else {
					*(char*)(0x292388+0x3) = 0x63;
				}
				break;
			/*case 6:
				{
				cBuf_Addtext(0,"ui_mapname \"mp_dome\";");
				}
				break;*/
			}
			break;
		case MENUS::MapChooser:
			addTitle("Choose Map (Host Only)");
			char *mapArray[] = {"mp_airfield","mp_asylum","mp_castle","mp_courtyard","mp_dome","mp_downfall","mp_hangar","mp_makin","mp_outskirts","mp_roundhouse","mp_seelow","mp_shrine","mp_suburban"};
			for (int i = 0; i < sizeof(mapArray)/sizeof(char*); i++) {
				addOption(mapArray[i]);
			}
			{
				int chosenOption = getOption();
				if (chosenOption != -1) {
					char buf[100];
					snprintf(buf,sizeof(buf),"ui_mapname \"%s\";",mapArray[chosenOption]);
					cBuf_Addtext(0,buf);
				}
			}
			break;
		case MENUS::IPs:
			ipSubmenu();
			break;
		case MENUS::Names:
			addTitle("Change Name");
			addOption("Custom Input");
			addOption("Real Looking Name");
			addOption("Youtuber");
			addOption("Cheater");
			addOption("Paradise SPRX");
			addOption("Jailbroken");
			addOption("Funny");
			addOption("Advertise <3");
			addOption("Anti-Cheat");
#if DEVELOPER == 1
			addOption("Paradise SPRX Dev");
#endif
			switch(getOption()) {
			case 0:
				keyboardRunner::openKeyboard(CALLBACK::CustomName,L"Enter Name",L"");
				break;
			case 1:
				setName("AverageJoe2012");
				break;
			case 2:
				setName("Whiteboy7thst");
				break;
			case 3:
				setName("^1HAX");
				break;
			case 4:
				setName("\x1^5Paradise ^1SPRX\x1");
				break;
			case 5:
				setName("^1\x2JAILBREAK\x2");
				break;
			case 6:
				setName("^1LOL");
				break;
			case 7:
				setName("^5Paradise^1SPRX^5.com");
				break;
			case 8:
				setName("Anti-Cheat Lobby");
				break;
#if DEVELOPER == 1
			case 9:
				setName("\x1^5Paradise SPRX Dev\x1");
				break;
#endif
			}
			break;
		case MENUS::Infection:
			//menuInfo->infectionCode
			addTitle("Infection Menu");
			addOption("Add Custom Code");
			addOption("Binds");
			addOption("Clear Code");
			addOption("Set Infection");
			addOption("");
			addOption("Current code:");
			addOption(menuInfo->infectionCode);
			switch(getOption()) {
			case 0:
				keyboardRunner::openKeyboard(CALLBACK::Infection,L"Enter CFG Code (Max 500 Characters)",L"bind dpad_left noclip;");
				break;
			case 1:
				openSubmenu(MENUS::BindButtonList);
				break;
			case 2:
				memset(menuInfo->infectionCode,0,strlen(menuInfo->infectionCode)+4);
				break;
			case 3:
				{
				char buf[1000];
				snprintf(buf,sizeof(buf),"ui_mapname \"mp_dome;%s\";",menuInfo->infectionCode);
				cBuf_Addtext(0,buf);
				print("Infection Set");
				}
				break;
			}
			break;
		case MENUS::BindButtonList:
			addTitle("Button Binds");
			char *dpadbuttonnames[5] = {"Dpad Up","Dpad Down","Dpad Left","Dpad Right","Walk"};
			addArrayOption("Button",&currentBindButtonConfiguration,0,4,dpadbuttonnames);
			addBoolOption("Noclip",BINDS&BIND_NOCLIP);
			addBoolOption("Godmode",BINDS&BIND_GODMODE);
			addBoolOption("Give All",BINDS&BIND_GIVEALL);
			addBoolOption("Advertise",BINDS&BIND_ADVERTISE);
			addBoolOption("Suicide",BINDS&BIND_SUICIDE);
			addBoolOption("UFO Mode",BINDS&BIND_UFO);
			addBoolOption("Give PPSH",BINDS&BIND_GIVEPPSH);
			addBoolOption("Give Finger Guns",BINDS&BIND_GIVEDEFAULT);
			addBoolOption("Run USB Code",BINDS&BIND_EXEC);
			addBoolOption("Quit To XMB",BINDS&BIND_QUIT);
			addOption("Save Binds");//getBindCode()
			switch(getOption()) {
			case 0:
				//button chooser
				break;
			case 1:
				toggleBind(BIND_NOCLIP);
				break;
			case 2:
				toggleBind(BIND_GODMODE);
				break;
			case 3:
				toggleBind(BIND_GIVEALL);
				break;
			case 4:
				toggleBind(BIND_ADVERTISE);
				break;
			case 5:
				toggleBind(BIND_SUICIDE);
				break;
			case 6:
				toggleBind(BIND_UFO);
				break;
			case 7:
				toggleBind(BIND_GIVEPPSH);
				break;
			case 8:
				toggleBind(BIND_GIVEDEFAULT);
				break;
			case 9:
				toggleBind(BIND_EXEC);
				break;
			case 10:
				toggleBind(BIND_QUIT);
				break;
			case 11:
				append(menuInfo->infectionCode,getBindCode());
				cellMsgDialogOpen(1,"Code Set!",my_dialog2,(void*) 0x0000aaab, NULL);
				break;
			}
			break;
		default:
			closeMenu();
			break;
		}
	}

	printLoop();
		//otherControls();
	doButtons();
		//sleep(100);
	//}
	//currentOptionCount = 0;
}

typedef struct
{
    vec3 surfaceDirection;
    float unknown;
    float fraction;
    unsigned long surfaceType;
    unsigned long surfaceFlags;
    unsigned long hitType;
    unsigned short entityNum;
    unsigned char _0x0022[0x0028 - 0x0022];
    unsigned short index;
    unsigned char startsolid;
    unsigned char allsolid;
    unsigned char _0x002C[0x003C - 0x002C];
    vec3 endpos;
    unsigned char indexHit;
    unsigned char _0x0049[0x004C - 0x0049];
    unsigned long materialType;
}trace_t;

opd_s glt = {0x001A3B38,TOC};
void (*CG_LocationalTrace)(trace_t* trace, float *start, float *end, int passEntityNum, int contentmask, int zero) = (void(*)(trace_t*, float*, float*, int, int, int))&glt;
//opd_s atgtp = {0x000EBE88,TOC};
//void (*AimTarget_GetTagPos)(int centity, int bodyPart, float *storeLoc) = (void(*)(int,int,float*))&atgtp;
trace_t trace;
bool Trace(int clientNum, vec3 start, vec3 end){
    CG_LocationalTrace(&trace, (float*)&start, (float*)&end, clientNum, 0x803003 /*0x0280E833 mask of shooting*/  /*0x0280B001 mask of something*/,0);
	//if (trace.fraction > 0.95)
		//printf("Trace: %i percent    addr: %i\n",(int)(trace.fraction*100),&trace);
	return (trace.fraction >= 0.95);
}
int getBoneID(int bone) {
	return (int)*(short*)(*(int*)0x86C73C+bone);
}

opd_s GCDObJ = {0x00334A78,TOC};
int (*Com_GetClientDObj)(unsigned int handle, int localClientNum) = (int(*)(unsigned int,int))&GCDObJ;
opd_s DObjGWTP = {0x00142B48,TOC};
bool (*CG_DObjGetWorldTagPos)(unsigned int targ_centity, unsigned int dobj, unsigned int tagIndex, float *pos) = (bool(*)(unsigned int,unsigned int,unsigned int,float*))&DObjGWTP;


bool AimTarget_GetTagPos(int targEnt, unsigned int targIndex,float *outPos)
{
	unsigned int handle = *(unsigned int*)(CEntity(targEnt) + 0x15C);
	unsigned int DObj = Com_GetClientDObj(handle , *(char*)(CEntity(targEnt)+0x4));
	if (DObj == 0)
		return false;
	return CG_DObjGetWorldTagPos(CEntity(targEnt), DObj, targIndex, outPos);
}

/*
0x879D38-0x7F2C


vote string
announcement message
game message
bold game message
chat message
%s
team chat message

from cod4:
hudelem string
announcement message
game message
bold game message
*/
int hook() {
	//drawText("^1Hey there pal",0xffff,initFont("fonts/smallDevFont",1),0x3f800000,200.0f,200.0f,1.0f,1.0f);
	if (isInGameOrLoading()) {
		vec3 me;
		if (ClientExists(GetIndex())) {
			if (isAlive(GetIndex())) {
				//THIS WILL NOT WORK IF DOING THE TELEPORT TO OTHER PLAYERS WHILE VIEW IS SOMEWHERE ELSE CUZ THIS GRABS THE VIEW NOT THE SERVER POS
				//bool b = AimTarget_GetTagPos(GetIndex(),*(short*)0x1241918/*35*//*getBoneID(*//*selectedBone*//*)*//*0x31*/,(float*)&me);//0x86C740 is my centity???
				//printf("Me: %i, 0x%X 0x%X 0x%X\n",(int)b,*(unsigned int*)&(me.x),*(unsigned int*)&(me.y),*(unsigned int*)&(me.z));
				//if (b) {
				bool unfairAimbot = autoAim;//I call it auto aim for some reason lmao idk why
				if (unfairAimbot) {
					//using server view pos (origin actually I think) when desynced
					menuInfo->positions[GetIndex()].x = SERVERVIEWPOS->x;//getOrigin(GetIndex()).x;//me.x;
					menuInfo->positions[GetIndex()].y = SERVERVIEWPOS->y;//getOrigin(GetIndex()).y;//me.y;
					menuInfo->positions[GetIndex()].z = SERVERVIEWPOS->z;//getOrigin(GetIndex()).z;//me.z;
					me.x = SERVERVIEWPOS->x;
					me.y = SERVERVIEWPOS->y;
					me.z = SERVERVIEWPOS->z;
				} else {
					//using playerstate view position when it's not desynced
					menuInfo->positions[GetIndex()].x = getViewOrigin()->x;
					menuInfo->positions[GetIndex()].y = getViewOrigin()->y;
					menuInfo->positions[GetIndex()].z = getViewOrigin()->z;
					me.x = menuInfo->positions[GetIndex()].x;
					me.y = menuInfo->positions[GetIndex()].y;
					me.z = menuInfo->positions[GetIndex()].z;
				}
				//}
			}
		}
		for (int i = 0; i < /*12*/18; i++) {
			if (i != GetIndex()) {
				if (ClientExists(i)) {
					if (!isSameTeam(GetIndex(), i) || isFFA()) {
						vec3 them;
						bool b = AimTarget_GetTagPos(i,silentAim?0x31:*(short*)0x1241918/*35*//*getBoneID(*//*selectedBone*//*)*//*0x31*/,(float*)&them);
						if (b) {
							if (autoAim) {//unfair aimbot
								menuInfo->positions[i].x = getOrigin(i).x;//them.x;
								menuInfo->positions[i].y = getOrigin(i).y;//them.y;
								menuInfo->positions[i].z = getOrigin(i).z;//them.z;
								menuInfo->targetVisibility[i] = Trace(0,me,them/*getOrigin(GetIndex())*//*,getOrigin(i)*/);//!AimTarget_IsTargetVisible(0,CEntity(i),0/*0x0BE3*//*0x24000082*/);
							} else {
								//not unfair aimbot
								menuInfo->positions[i].x = them.x;//getOrigin(i).x;
								menuInfo->positions[i].y = them.y;//getOrigin(i).y;
								menuInfo->positions[i].z = them.z;//getOrigin(i).z;
								menuInfo->targetVisibility[i] = Trace(0,me,them/*getOrigin(GetIndex())*//*,getOrigin(i)*/);//!AimTarget_IsTargetVisible(0,CEntity(i),0/*0x0BE3*//*0x24000082*/);
							
							}
						} else {
							menuInfo->targetVisibility[i] = false;
						}
					} else {
						menuInfo->targetVisibility[i] = false;
					}
				} else {
					menuInfo->targetVisibility[i] = false;
				}
			} else {
				menuInfo->targetVisibility[i] = false;
			}
		}
	} else {
		//selectedBone = 44;
	}
	//spoofPosition();
	return 0;
}
/*void renderHook();
void render_redo() {
	opd_s r_t = {0x1D9430,TOC};
	void(*r)() = (void(*)())&r_t;
	char bytes[16] = {0xF8, 0x21, 0xFF, 0x41, 0x7C, 0x68, 0x02, 0xA6, 0xFB, 0xC1, 0x00, 0xB0, 0x83, 0xC2, 0x81, 0xA0};
	write_process((void*)0x1D9430,bytes,16);
	r();
	PatchInJump(0x1D9430,(int)renderHook,false);
}*/

void keyboardCallback() {
	char *text = keyboardRunner::getResult();
	if (text!=0){
		switch(keyboardRunner::getSaveID()) {
		case CALLBACK::Infection:
			strcpy((char*)(menuInfo->infectionCode+strlen(menuInfo->infectionCode)),text);
			print("Code Added");
			break;
		case CALLBACK::EnterDvar:
			cBuf_Addtext(0,text);
			print("Code Ran");
			break;
		case CALLBACK::CustomName:
			setName(text);
			break;
		}
	}
}

void onRun() {
	//printf("Ran\n");
	cBuf_Addtext(0,"bind dpad_up lol;");
}

bool justStartedGame = false;
void renderHook() {
	//render_redo();
	//printf("hi\n");
	//printf("In game: %i\n",DvarGetBool("cl_ingame"));
	if(isInGameOrLoading()/* && DvarGetBool("cl_ingame")*/) {
		if (justStartedGame == true) {
			justStartedGame = false;
			onRun();
		}
		//printf("You are in the game\n");
	} else {
		justStartedGame = true;
	}


	if (selectedMenu != MENUS::Closed) {
		float black[4] = {0,0,0,0.5f};
		float blue[4] = {0,0,1,0.5f};
		float white[4] = {1,1,1,1};
		//DrawShader(0,0,2000,2000,blue,"white"/*menuInfo->debugMaterial*/);
		DrawShader(menux,menuy,menuw,/*600*/currentOptionCount*textHeight,black,"white");
	}
	runMenu();
	keyboardCallback();
	//spoofPosition();
	//printf("past\n");
	//float color[4] = {0,0,1,1};
	//DrawText("Hey there pal","fonts/objectivefont",menux,menuy,1.0f,color);
	//drawText("^1Hey there pal",0xffff,initFont("fonts/consoleFont",1),0x3f800000,*(float*)0x874560/*200.0f*/,*(float*)0x874550/*200.0f*/,1.0f,1.0f);
	
}



void fastLoopThread(uint64_t nothing) {
	for (;;) {
		if (isInGameOrLoading()) {
			/*if (testtp) {
				PSORIGIN->x = getViewOrigin()->x;//getOrigin(GetIndex()).x;
				PSORIGIN->y = getViewOrigin()->y;//getOrigin(GetIndex()).y;
				PSORIGIN->z = getViewOrigin()->z;//getOrigin(GetIndex()).z+100;
			}*/
			//spoofPosition();

		}
		sleep(1);
	}
	sys_ppu_thread_exit(nothing);
}































