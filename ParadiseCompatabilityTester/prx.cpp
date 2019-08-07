//#define DEBUG 1
char unlockAll[] = {"set unlock \"statset 3000 4294967296; statset 3001 4294967296; statset 3002 4294967296; statset 3003 4294967296; statset 3004 4294967296; statset 3005 4294967296; statset 3006 4294967296; statset 3007 4294967296; statset 3008 4294967296; statset 3009 4294967296; statset 3010 4294967296; statset 3011 4294967296; statset 3012 4294967296; statset 3013 4294967296; statset 3014 4294967296; statset 3015 4294967296; statset 3016 4294967296; statset 3017 4294967296; statset 3018 4294967296; statset 3019 4294967296; statset 3020 4294967296; statset 3021 4294967296;cg_chatheight 2;say ^2Please wait 1;say ^5Unlocking all;wait 100;vstr upt2\"; set upt2 \"statset 3022 4294967296; statset 3023 4294967296; statset 3024 4294967296; statset 3025 4294967296; statset 3026 4294967296; statset 3027 4294967296; statset 3028 4294967296; statset 3029 4294967296; statset 3030 4294967296; statset 3031 4294967296; statset 3032 4294967296; statset 3033 4294967296; statset 3034 4294967296; statset 3035 4294967296; statset 3036 4294967296; statset 3037 4294967296; statset 3038 4294967296; statset 3039 4294967296; statset 3040 4294967296; statset 3041 4294967296; statset 3042 4294967296; statset 3043 4294967296;wait 100;say ^2Please wait 2;say ^5Unlocking all;vstr upt3\"; set upt3 \"statset 3044 4294967296; statset 3045 4294967296; statset 3046 4294967296; statset 3047 4294967296; statset 3048 4294967296; statset 3049 4294967296; statset 3050 4294967296; statset 3051 4294967296; statset 3052 4294967296; statset 3053 4294967296; statset 3054 4294967296; statset 3055 4294967296; statset 3056 4294967296; statset 3057 4294967296; statset 3058 4294967296; statset 3059 4294967296; statset 3060 4294967296; statset 3061 4294967296; statset 3062 4294967296; statset 3063 4294967296; statset 3064 4294967296; statset 3065 4294967296;wait 100;say ^2Please wait 3;say ^5Unlocking all;vstr upt4\"; set upt4 \"statset 3066 4294967296; statset 3067 4294967296; statset 3068 4294967296; statset 3069 4294967296; statset 3070 4294967296; statset 3071 4294967296; statset 3072 4294967296; statset 3073 4294967296; statset 3074 4294967296; statset 3075 4294967296; statset 3076 4294967296; statset 3077 4294967296; statset 3078 4294967296; statset 3079 4294967296; statset 3080 4294967296; statset 3081 4294967296; statset 3082 4294967296; statset 3083 4294967296; statset 3084 4294967296; statset 3085 4294967296; statset 3086 4294967296; statset 3087 4294967296;wait 100;say ^2Please wait 4;say ^5Unlocking all\";"};

#include "stdafx.h"

#include <cellstatus.h>
#include <sys/prx.h>

#include <ppu_asm_intrinsics.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h>
#include <cell/cell_fs.h>
#include <sys/stat.h>
#include <cellstatus.h>
#include <sys/prx.h>
#include <sys/ppu_thread.h>
#include <string.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/process.h>
#include <ppu_intrinsics.h>
#include <stdarg.h>
#include <stdio.h>
#include <sysutil\sysutil_msgdialog.h>
#include <sysutil\sysutil_oskdialog.h>
#include <sysutil\sysutil_oskdialog_ext.h>
#include <cstdlib>
#include <math.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h>
#include <cell/cell_fs.h>
#include <sys/stat.h>

#include "Dialog.h"
void sleep(usecond_t time) {sys_timer_usleep(time * 1000);}//1 second = 1000
/*
enum uiMenuCommand_t
{
    UIMENU_NONE = 0x0,
    UIMENU_MAIN = 0x1,
    UIMENU_MAINLOBBY = 0x2,
    UIMENU_INGAME = 0x3,
    UIMENU_PREGAME = 0x4,
    UIMENU_POSTGAME = 0x5,
    UIMENU_WM_QUICKMESSAGE = 0x6,
    UIMENU_SCRIPT_POPUP = 0x7,
    UIMENU_SCOREBOARD = 0x8,
    UIMENU_GAMERCARD = 0x9,
    UIMENU_MUTEERROR = 0xA,
    UIMENU_SPLITSCREENGAMESETUP = 0xB,
    UIMENU_SYSTEMLINKJOINGAME = 0xC,
    UIMENU_PARTY = 0xD,
    UIMENU_WAGER_PARTY = 0xE,
    UIMENU_LEAGUE_PARTY = 0xF,
    UIMENU_GAMELOBBY = 0x10,
    UIMENU_WAGERLOBBY = 0x11,
    UIMENU_PRIVATELOBBY = 0x12,
    UIMENU_LEAGUELOBBY = 0x13,
    UIMENU_THEATERLOBBY = 0x14,
    UIMENU_MIGRATION = 0x15,
    UIMENU_CONTROLLERREMOVED = 0x16,
    UIMENU_ENDOFGAME = 0x17,
    UIMENU_INGAME_NOUNPAUSE = 0x18,
};
#define sv_serverId *(int*)0xF11D9C
Cbuf_AddText(va("cmd mr %i %i %s", sv_serverId, UIMENU_INGAME, "endround"));
*/

namespace keyboardRunner {
	enum TextMode {
		Closed,Open,JustClosed
	};
	int textMode = Closed;
	int saveID = 0;
	wchar_t* INIT_TEXT, *TITLE;
	char retText[500];
	void openKeyboard(int saveID, wchar_t* title, wchar_t* sampleText) {
		memset(retText,0,sizeof(retText));
		TITLE = title;
		INIT_TEXT = sampleText;
		keyboardRunner::saveID = saveID;
		Keyboard::oskdialog_mode = Keyboard::MODE_OPEN;
	}
	bool isKeyboardOpen() {
		return (Keyboard::oskdialog_mode == Keyboard::MODE_OPEN) || (Keyboard::oskdialog_mode == Keyboard::MODE_RUNNING);
	}
	int getSaveID() {
		return saveID;
	}
	char *getResult() {
		if (textMode == JustClosed) {
			textMode = Closed;
			return retText;
		} else {
			return 0;
		}
	}
	
	sys_ppu_thread_t ThreadModuleID;
	void thread(uint64_t nothing) {
		for (;;) {
			textMode = Closed;
			while(isKeyboardOpen()) {
				textMode = Open;
				Keyboard::keyboard(retText, INIT_TEXT,TITLE);
			}
			if (textMode == Open && Keyboard::oskdialog_mode == Keyboard::MODE_EXIT/* && Keyboard::oskdialog_mode == Keyboard::MODE_CANCELED*/) {
				printf("Done!\n");
				textMode = JustClosed;
				sleep(1000);//give code enough time to realize it was just closed
			}
			sleep(100);
		}
		//wait for the keyboard to end and run it meanwhile

		//end thread
		sys_ppu_thread_exit(nothing);
	}
};

#include<cell/pad.h>
#include <cell/sysmodule.h>
void PatchInJump(int Address, int Destination, bool Linked);
#define MAX_PAD (1)
void PadRead(uint32_t* pbutton1, uint32_t* pbutton2)
{
	int			i;
	int			ret;
	CellPadInfo2 pad_info;
	static uint32_t old_pad_info=0;
	CellPadData pad_data;
	uint32_t	button1 = 0;
	uint32_t	button2 = 0;

	ret = cellPadGetInfo2(&pad_info);
	if (ret != CELL_OK){
		//printf("cellPadGetInfo2() error (0x%x).\n", ret);
		return;
	}

     /*E Check info field for monitoring the INTERCEPTED state. */
    if((pad_info.system_info & CELL_PAD_INFO_INTERCEPTED) && 
       (!(old_pad_info & CELL_PAD_INFO_INTERCEPTED))) 
    {
        //printf ("This program lost the ownership of the game pad data\n");
        old_pad_info = pad_info.system_info;
    }
    else if((!(pad_info.system_info & CELL_PAD_INFO_INTERCEPTED)) &&
            (old_pad_info & CELL_PAD_INFO_INTERCEPTED))
    {
       // printf ("This program got the ownership of the game pad data\n");
        old_pad_info = pad_info.system_info;
    }

	for (i = 0; i < MAX_PAD; i ++)
	{
		if (pad_info.port_status[i] & CELL_PAD_STATUS_CONNECTED == 0)
			continue;

		ret = cellPadGetData(i, &pad_data);
		if (ret != CELL_PAD_OK || pad_data.len == 0)
			continue;

		button1 = pad_data.button [CELL_PAD_BTN_OFFSET_DIGITAL1];
		button2 = pad_data.button [CELL_PAD_BTN_OFFSET_DIGITAL2];
	}
	*pbutton1 = button1;
	*pbutton2 = button2;
	return;
}

/*namespace buttonssss {
	int triangle = CELL_PAD_CTRL_TRIANGLE;
	int square = CELL_PAD_CTRL_SQUARE;
	int circle = CELL_PAD_CTRL_CIRCLE;
	int cross = CELL_PAD_CTRL_CROSS;
	int dpadUp = CELL_PAD_CTRL_UP;//digital 1
	int dpadDown = CELL_PAD_CTRL_DOWN;//digital 1
	int dpadLeft = CELL_PAD_CTRL_LEFT;//digital 1
	int dpadRight = CELL_PAD_CTRL_RIGHT;//digital 1
	int r1 = CELL_PAD_CTRL_R1;
	int r2 = CELL_PAD_CTRL_R2;
	int r3 = CELL_PAD_CTRL_R3;//digital 1
	int l1 = CELL_PAD_CTRL_L1;
	int l2 = CELL_PAD_CTRL_L2;
	int l3 = CELL_PAD_CTRL_L3;//digital 1
	int start = CELL_PAD_CTRL_START;//digital 1
	int select = CELL_PAD_CTRL_SELECT;//digital 1
}*/
enum btns {
	BTriangle,
	BSquare,
	BCirlce,
	BCross,
	BDpadUp,
	BDpadDown,
	BDpadLeft,
	BDpadRight,
	BR1,
	BR2,
	BR3,
	BL1,
	BL2,
	BL3,
	BStart,
	BSelect
};
int buttons[] = {CELL_PAD_CTRL_TRIANGLE,CELL_PAD_CTRL_SQUARE,CELL_PAD_CTRL_CIRCLE,CELL_PAD_CTRL_CROSS,CELL_PAD_CTRL_UP,CELL_PAD_CTRL_DOWN,CELL_PAD_CTRL_LEFT,CELL_PAD_CTRL_RIGHT,CELL_PAD_CTRL_R1,CELL_PAD_CTRL_R2,CELL_PAD_CTRL_R3,CELL_PAD_CTRL_L1,CELL_PAD_CTRL_L2,CELL_PAD_CTRL_L3,CELL_PAD_CTRL_START,CELL_PAD_CTRL_SELECT};
bool buttonsType[]/*0 means digital 2, 1 means digital 1*/ = {0,0,0,0,1,1,1,1,0,0,1,0,0,1,1,1};
unsigned int button1,button2;
bool isButtonPressed(int button) {
	if (buttonsType[button] == 0) {
		//digital 2
		if(button2 & buttons[button])
		{
			return true;
		}
	} else {
		//digital 1
		if(button1 & buttons[button])
		{
			return true;
		}
	}
	return false;
}




void readFile(char *file, char buf[], int size) {
	int fd;
	int ret;
	uint64_t pos;
	uint64_t nread;
	ret = cellFsOpen(file, 0, &fd, NULL, 0);
	if (!ret)
	{
		cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
		ret = cellFsRead(fd, buf, size, &nread);
		if (!ret)
		{
			cellFsClose(fd);
		}
	}
}
void writeToFile(char *file, char buf[] = NULL, int size = 0) {
	int err;
 int fd;
 uint64_t nrw;
 int ret;
 /* Open file */
 err = cellFsOpen(file,CELL_FS_O_RDWR|CELL_FS_O_CREAT, &fd, NULL, 0);
 /* Clear file */
 cellFsTruncate(file,0);
 /* Write to file */
 if (size != 0)
 err = cellFsWrite(fd, (const void *)buf, (uint64_t)size, &nrw);
 /* Close file */
 err = cellFsClose(fd);
}
void createFile(char *loc) {
	int fd;
	int ret;
	ret = cellFsOpen(loc,CELL_FS_O_CREAT|CELL_FS_O_RDWR|CELL_FS_O_TRUNC, &fd, NULL, 0);
    cellFsClose(fd);
	if (!ret)
	{
		cellFsClose(fd);
	}
}
int doesFolderExist(const char *Path)
{
	int i, err;	CellFsStat status;
	for (i = 0; i < 15; i++) 
	{
		err = cellFsStat(Path, &status);
		if (err == CELL_FS_SUCCEEDED) 
		{
			return 1;
		}
	}
	return 0;
}
void my_dialog2(int button, void *userdata)
{
    switch(button) {
        case CELL_MSGDIALOG_BUTTON_OK:

        case CELL_MSGDIALOG_BUTTON_NONE:

		case CELL_MSGDIALOG_BUTTON_ESCAPE:
            //dialog_action = 1;
            break;
        default:
		    break;
    }
}





int write_process(void* destination, const void* source, size_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);//dex only
	return_to_user_prog(int);
}
bool isNumericChar(char x) {
	return (x >= '0' && x <= '9') ? true : false;
}
int StoI2( const char *c ) {
	int value = 0;
    int sign = 1;
    if( *c == '+' || *c == '-' ) {
       if( *c == '-' ) sign = -1;
       c++;
    }
    while ( isNumericChar( *c ) ) {
        value *= 10;
        value += (int) (*c-'0');
        c++;
    }
    return value * sign;
}

void reverse(char arr[], int count)
{
   char temp;
   for (int i = 0; i < count/2; ++i)
   {
      temp = arr[i];
      arr[i] = arr[count-i-1];
      arr[count-i-1] = temp;
   }
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}
char *ItoS(int num)
{
	char buf[30];
	return itoa(num,buf,10);
}


int StoI( const char *c ) {
    int value = 0;
    int sign = 1;
    if( *c == '+' || *c == '-' ) {
       if( *c == '-' ) sign = -1;
       c++;
    }
    while ( isNumericChar( *c ) ) {
        value *= 10;
        value += (int) (*c-'0');
        c++;
    }
    return value * sign;
}


#include "Base.h";

void PatchInJump(int Address, int Destination, bool Linked) 
{
	// use this data to copy over the address
	int FuncBytes[4];

	// Get the actual destination address
	Destination = *(int *)Destination;

	FuncBytes[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF); // lis     %r11, dest>>16
	if (Destination & 0x8000) // If bit 16 is 1
		FuncBytes[0] += 1;

		FuncBytes[1] = 0x396B0000 + (Destination & 0xFFFF); // addi    %r11, %r11, dest&0xFFFF
		FuncBytes[2] = 0x7D6903A6; // mtctr    %r11

		FuncBytes[3] = 0x4E800420; // bctr

		if (Linked)
			FuncBytes[3] += 1; // bctrl

		write_process((void*)Address, FuncBytes, 4 * 4);
}

int Memcpy2(void* destination, const void* source, size_t size)
{
 system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);
 __dcbst(destination);
 __sync();
 __isync();
 return_to_user_prog(int);
}





void init() {

	/*
	for (;;) {
		int party_connectToOthers = *(int*)0xB3EB94;
		if (party_connectToOthers > 0x10000) {
			if (*(char*)(*(int*)0x000873D24+0xf) == false) {//cl_ingame
				*(bool*)(party_connectToOthers + 0x10) = false;//set not to connect to others when in lobby
			} else {
				*(bool*)(party_connectToOthers + 0x10) = true;//set to connect to others once in game
			}

		}

		int minp = *(int*)0xB3EB80;//party_minplayers
		if (minp > 0x10000) {
			*(int*)(minp + 0x10) = 1;//party_minplayers
		}

		sleep(1000);
	}
	return;*/

	
	//*(int*)0x002EE6C4 = 
	//unsigned char sa1[4] = {0x2F, 0x80, 0x00, 0x00};
	//write_process((void*)0x00114614,sa1,4);//part of weapon spread
	
	
	//unsigned char sa[12] = {0xD0, 0x05, 0x00, 0x00, 0xD0, 0x06, 0x00, 0x00, 0x4E, 0x80, 0x00, 0x20};//kinda worked
	//write_process((void*)0x00114608,sa,12);
	*(int*)0x0019D0D8 = 0x60000000;//steady aim
	*(int*)0x0019FFE0 = 0x60000000;//no recoil
	//*(int*)0x0019AF40 = 0x60000000;//no sway  (only visual, doesn't actually work)
	*(int*)0x001D9768 = 0x48000240;//jump to fps patch
	*(char*)(0x292388+0x3) = 0x63;//anti-cheat message change to big text
	//printf("Chitter\n");

	//NEED TO CHANGE THE HOOK TO A RELIABLE ONE
	PatchInJump(0x001A71E0/*CL_SetFOVSensitivityScale found from within CL_DrawActive*//*hook from rpc 0x5C6168*//*0x144898 hook I was using but doesn't work on that one map for some reason*//*some random address I found*/,(int)hook,false);
	//1D8B88
	//printf("Execution\n");

	//trying to hook instead of of original way
	PatchInJump(/*0x1D9430*/0x1D8B88,(int)renderHook,false);
	//Hook renderingHook = Hook(0x1D8B88,(unsigned int)renderHook);
	//printf("hook: 0x%X, func: 0x%X, dif: 0x%X\n",0x1D8B88,(unsigned int)renderHook,0x1D8B88-(unsigned int)renderHook);
	//renderingHook.detour();
	//end of new hook code

	//printf("kek\n");
	//PatchInJump(0x001B9478,(int)hkCL,false);//create commands

	
	PatchInJump(0x001B6198,(int)hkCL,false);//write packet
	
	
	//HookFunctionStart(0x001B6198,(int)saveStub,(int)hkCL);
	//printf("khhh\n");
	//for (int i = 0; i < 0xffff; i++)
		//padding[i]  = 0;
	sys_ppu_thread_t id2;
	//sys_ppu_thread_t id3;
	sys_ppu_thread_create(&id2,Aimthread,0,0x5AA,0xff,0,"Aimbot");//3071
	sys_ppu_thread_create(&keyboardRunner::ThreadModuleID, keyboardRunner::thread, 0, 0x6AA, 0x3000, 0, "Keyboard Runner");
	//sys_ppu_thread_create(&id3,fastLoopThread, 0, 0x7AA, 0xff, 0, "Fast Loop Thread");
	strcpy(menuInfo->debugMaterial,"white");
	//threadLoop();//stops the whole process
	//sustain ammo: *(char*)(*(int*)0x008C9758+0x10) = 1; or *(int*)0x0011B8E4 = 0x38600001;
}



void start() {
	menuInfo->nearestClient = -1;
	
	cellMsgDialogOpen(1,"Welcome to Paradise!\nMade by gopro_2027",my_dialog2,(void*) 0x0000aaab, NULL);
	init();
}
void Thread(uint64_t nothing) {
	sleep(5000);
	start();
	sys_ppu_thread_exit(nothing);
}


SYS_MODULE_INFO("Paradise SPRX", 0, 1, 1);
SYS_MODULE_START( _ParadiseCompatabilityTester_prx_entry );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _ParadiseCompatabilityTester_export_function, LIBNAME );

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _ParadiseCompatabilityTester_export_function(void)
{
    return CELL_OK;
}

sys_ppu_thread_t ThreadModuleID;
extern "C" int _ParadiseCompatabilityTester_prx_entry(void)
{
	sys_ppu_thread_create(&ThreadModuleID, Thread, 0, 0x4AA, 0x7000, 0, "Paradise SPRX");
	
	//cellPadInit(MAX_PAD);
    return SYS_PRX_RESIDENT;
}
