#include "mymath.h"

vec3 vectoangles(vec3 Angles)
{
	float angleseeeee[3];
	float forward;
	float yaw, pitch;
	//float PI = 3.1415926535897931;
	if (Angles.x == 0 && Angles.y == 0)
	{
		yaw = 0;
		if (Angles.z > 0) pitch = 90.00;
		else pitch = 270.00;
	}
	else
	{
		if (Angles.x != -1) yaw = (float)(myMath::atan2((double)Angles.y, (double)Angles.x) * 180.00 / PI);
		else if (Angles.y > 0) yaw = 90.00;
		else yaw = 270;
		if (yaw < 0) yaw += 360.00;

		forward = (float)sqrt((double)(Angles.x * Angles.x + Angles.y * Angles.y));
		pitch = (float)(myMath::atan2((double)Angles.z, (double)forward) * 180.00 / PI);
		if (pitch < 0) pitch += 360.00;
	}
	angleseeeee[0] = -pitch;
	angleseeeee[1] = yaw;
	angleseeeee[2] = 0;

	vec3 Angless = { angleseeeee[0], angleseeeee[1], angleseeeee[2] };
	return Angless;
}
bool visibleOnly = true;
bool autoAim = false;
long ClActive()
{
	return *(long*)0xAE9780;
}
vec3 *getViewAngles() {
	return (vec3*)(*(int*)0x00A95CD8+0x50000+0x35E0/*0x337E6020*/+0x434C);
}
vec3 *getViewOrigin() {
	//This is proper view origin, roughly at the location of my head
	//0x337E6020+0x4358
	return (vec3*)(*(int*)0x00A95CD8+0x50000+0x35E0+0x4358);
	//*(int*)0x00A95CD8+0x50000+0x360C this one overrites the one above
}
/*
Location infos:
the y value of master is overritten at address 0x000C6C9C
master = 0 + *(int*)0xA95CD8 + 0x50000 - 0x6CC + 0x20     THIS IS FROM PLAYERSTATE+0x20 WTH? BUT YEA IT IS. this one will make you flinch when changing but go back soon after. the 0 at the beginning is localclient*0xEACC0 I think
master overrites *(int*)0x00A95CD8+0x50000+0x360C
and that overrites *(int*)0x00A95CD8+0x50000+0x35E0+0x4358 which is used in getViewOrigin();

*/


bool RequireAiming = true;
void* read_process(uint64_t ea,uint32_t size)
{
	void* data;
	system_call_4(904, (uint64_t)sys_process_getpid(), ea, size, (uint64_t)data);
	return data;
}
unsigned int read_process_uint(uint64_t ea)
{
	unsigned int data;
	system_call_4(904, (uint64_t)sys_process_getpid(), ea, 4, (uint64_t)&data);
	return data;
}
int CEntity(int index) {//*(int*)0xA95CE0+0x2B0*
	return *(int*)0xA95CE0+0x2B0*index;
}//centity gun is offset 0x244
int GetIndex() {
	return *(int*)*(int*)0xA95CD8;//*(int*)*(int*)0xA95CD8
}
unsigned int cg_s() {
	return *(unsigned int*)0xA95CD8;
}
#define PLAYERSTATE (*(unsigned int*)*(unsigned int*)(0x8715B0))   /*0x87952C-0x7F7C*/
#define PLAYERSTATEPOINTER (*(unsigned int*)(0x8715B0))
#define CGARRAYPOINTER (*(int*)0x86EEE8)
#define CGARRAY (*(int*)(*(int*)0x86EEE8))
#define CLIENTVIEWROT ((vec3*)(CGARRAY+0x50000+0x792C))    /*derived from viewpos native thingy*/
#define CLIENTVIEWPOS ((vec3*)(CGARRAY+0x50000+0x792C+0x4*3))    /*((vec3*)((*(int*)(*(int*)0x86EEE8))+0x50000+0x792C+0x4*3)) same as playerstate viewpos*/
#define SERVERVIEWPOS ((vec3*)(*(int*)*(int*)0x871564/*0xA95CD8*/+0x58))
//cgArray is often paired with +0x50000 aka lis 5
//viewpos is at CGARRAY+0x50000+0x792C
unsigned int getWeaponDef(int weaponIndex) {
	return *(unsigned int*)(0x8CDADC+weaponIndex*4)+0x0;
}
float getAimValue() {
	//to make it not look like you are aiming do 0x11921C = nop otherwise 0xD19F0110 for normal function
	//0 when not aiming, 1 when aiming

	//printf("Be happy\n");
	//printf("Playerstate: 0x%X\n",PLAYERSTATE);
	//*(int*)*(int*)(0x87952C-0x7F7C)+0x4*0x7*0x9+0x5*0x4
	return *(float*)(PLAYERSTATE+0x110);
}

vec3 getViewRot() {
	//x is up and down where 0 would be looking parallel to the ground. Looking all the way up is -70 and all the way down is 70; [70,-70] you have to be pressing on it to equal 70 otherwise it is (-70,70)
	//y is left and right; goes from 180 to -180 ie [180,-180]
	//z is the other one
	return *(vec3*)(PLAYERSTATE+0x124);
}
vec3 getPSOrigin() {
	//is this origin or VIEW origin? I cann't remember.
	//During tests, I think I confirmed this to be body origin, not view origin. Use getViewOrigin() for view origin
	return *(vec3*)(PLAYERSTATE+0x20);//this is local
}
#define PSORIGIN ((vec3*)(*(int*)0xA95CD8 + 0x50000 - 0x6CC + 0x20))
//nop 0x16CB28 to allow editing of PSORIGIN
bool isInGameOrLoading() {
	int cg_s = *(int*)(0xA95CD8);
	int centity = *(int*)(0xA95CE0);
	bool cl_ingame = *(char*)(*(int*)0x000873D24+0xf) == 1;
	bool playerstateready = PLAYERSTATE > 0x10000;
	return cg_s!=0 && centity!=0 && cl_ingame && playerstateready;
}
vec3 getOrigin(int client) {
	return *(vec3*)(CEntity(client)+0x28);
}
bool isAlive(int client) {
	//return (!(*(int*)(CEntity(client)+0xD0) & (1<<18))) && (*(int*)(CEntity(client)+0xD4) == 0x01);
	//0x80
	//0x408
	//char exists = *(char*)(cg_s()+ServerDataStruct.isSameTeamOffset+0x55C*client+0x408);//0x2c int is alive?      *(int*)0xA95CD8+0xE2F2C+0x55C*client
	return (bool)(*(int*)(CEntity(client)+0x2AC)&(1<<30));//(bool)(0x40000000&(1<<30))
	//return !(*(int*)(cg_s()+ServerDataStruct.isSameTeamOffset/**(int*)0xA95CD8+0xE2F2C*/+0x55C*client+0x3AC) & 1);//when the last bit is 1 they are dead
}
bool ClientExists(int client) {
	int exists = *(int*)(cg_s()+0xE2F2C+0x55C*client);
	return (exists != 0);
}
bool isSameTeam(int client1, int client2) {
	//0xE2F2C is isSameTeamOffset
	char team1 = *(char*)(cg_s()+0xE2F2C+0x55C*client1+0x2F);//*(unsigned int*)0xA95CD8+0xE2F2C+0x55C*0
	char team2 = *(char*)(cg_s()+0xE2F2C+0x55C*client2+0x2F);
	return (team1==team2);
}
/*
cg_s stuff:
0x5360C is x y and z coords for yourself
  nop 0x0019057C and 0x00190588 and 0x00190590    and 0x0018F3F0 and 0x0018F3F8 and 0x0018F400    and 0x0018F9B8 and 0x0018F9E4 for gravity      to disable it being overwritten
*/

//based on 0xAE16BC
bool amIAiming() {
	return getAimValue() == 1.0f;//*(char*)0x00AE1780;
}
bool amIShooting() {
	return *(char*)0x00AE1820;
}
bool amIJumping() {
	return *(char*)0x00AE1794;
}
bool amIReloading() {
	return *(char*)0x00AE18AC;
}
bool amIKnifing() {
	return *(char*)0x00AE1870;
}
bool amIThrowingSecondaryGrenade() {
	return *(char*)0x00AE185C;
}
bool amIThrowingPrimaryGrenade() {
	return *(char*)0x00AE1848;
}
bool amISprinting() {
	return *(char*)0x00AE1924;
}

vec3 getBaseAngles() {
	//unsigned int data = read_process_uint(ClActive() + 0xa4 + 0x4);
	//float y = *(float*)(&data);
	menuInfo->baseAngleRet.x = *(float*)(ClActive() + 0xa4);
	menuInfo->baseAngleRet.y = *(float*)(ClActive() + 0xa4 + 0x4);
	menuInfo->baseAngleRet.z = *(float*)(ClActive() + 0xa4 + 0x8);
	//printf("X: 0x%X, Y: 0x%X, Z: 0x%X\n",*(unsigned int*)&baseAngleRet.x,*(unsigned int*)&baseAngleRet.y,*(unsigned int*)&baseAngleRet.z);
	return menuInfo->baseAngleRet;
}
void setViewAngles(float x, float y, float z) {//this works on the china map
	*(float*)(ClActive() + 0x26A80 + 0x00) = x;
	*(float*)(ClActive() + 0x26A80 + 0x04) = y;
	*(float*)(ClActive() + 0x26A80 + 0x08) = z;
}

bool isFFA() {
	bool p1 = *(char*)(*(int*)0xA95CDC+0x30) == 0x64;
	bool p2 = *(char*)(*(int*)0xA95CDC+0x31) == 0x6D;
	bool p3 = *(char*)(*(int*)0xA95CDC+0x32) == 0x00;
	return (p1 && p2 && p3);
}

float GetDistance(vec3 c1, vec3 c2)
{
	//float dx, dy, dz;
	float dx = c2.x - c1.x;
	float dy = c2.y - c1.y;
	float dz = c2.z - c1.z;

	return sqrt((float)((dx * dx) + (dy * dy) + (dz * dz)));
}
opd_s AimTarget_IsTargetVisible_t = {0x000EC610,TOC};
bool(*AimTarget_IsTargetVisible)(int localClientNum, unsigned int centity, unsigned int visBone) = (bool(*)(int,unsigned int,unsigned int))&AimTarget_IsTargetVisible_t;

int GetNearestPlayer(int client/*,bool checkingVisible = false*/)
{
    int nearestClient = -1;
    double nearestDistance = 1E+08f;

	//if (autoAim) {//teleport mode
			//nearestClient = menuInfo->nearestClient;
		
	//} else {

	//if (checkingVisible)
		//printf("Possibilities: ");
	for (int i = 0; i < /*12*/18; i++)
    {
		//if (checkingVisible) {
		//	while (!visibleTargetsTemp[i] && i < 11)
		//		i++;
		//}
		//visibleTargetsTemp[i] = false;
        if (i != client)
        {
            if (isAlive(i) && ClientExists(i))
            {
				if (!isSameTeam(client, i) || isFFA())
				{
					//if (checkingVisible)
						//printf("%i, ",i);
					float Distance = GetDistance(*SERVERVIEWPOS, getOrigin(i));//doesn't really matter cuz it's just distance check
					if (Distance < nearestDistance) {
						if ((menuInfo->targetVisibility[i]/* && menuInfo->targetVisibility2[i] && menuInfo->targetVisibility3[i]*/) || visibleOnly == false/* || autoAim == true*//*teleport mode is on*/    /*AimTarget_IsTargetVisible(0,CEntity(i),0x24000082)*/) {
							//visibleTargetsTemp[i] = true;
							nearestDistance = Distance;
							nearestClient = i;
						}
					}
				}
			}
        }
    }
	//printf("\n");
	//if (!checkingVisible)
		//return GetNearestPlayer(client,true);

	//}

	menuInfo->nearestClient = nearestClient;

	return nearestClient;
}






























/*
float radian(float ang) 
{ 
    return ang * (M_PI/180); 
}
 
void AngleVectors(float *angles, float *forward, float *right, float *up)
{
    float            angle;
    static float    sr, sp, sy, cr, cp, cy;
    
    angle = radian(angles[0]);//pitch
    sp= sin(angle);
    cp= cos(angle);
    
    angle = radian(angles[1]);//yaw
    sy = sin(angle);
    cy = cos(angle);
    
    angle = radian(angles[2]);//roll
    sr = sin(angle);
    cr = cos(angle);
    
    if (forward)
    {
        forward[0] = cp*cy;
        forward[1] = cp*sy;
        forward[2] = -sp;
    }
    if (right)
    {
        right[0] = (-1*sr*sp*cy+-1*cr*-sy);
        right[1] = (-1*sr*sp*sy+-1*cr*cy);
        right[2] = -1*sr*cp;
    }
    if (up)
    {
        up[0] = (cr*sp*cy+-sr*-sy);
        up[1] = (cr*sp*sy+-sr*cy);
        up[2] = cr*cp;
    }
}
 
void VectorAngles(const vec3 forward, vec3 angles)
{
    float tmp, yaw, pitch;
    
    if (forward.y == 0 && forward.x == 0) 
    {
        yaw = 0;
        if (forward.z > 0)
        {
            pitch = 90;
        }
        else
        {
            pitch = 270;
        }
    }
    else
    {
        yaw = (atan2(forward.y, forward.x) * 180 / M_PI);
        
        if (yaw < 0)
        {
            yaw += 360;
        }
        
        tmp = sqrt(forward.x * forward.x + forward.y * forward.y);
        pitch = (atan2(forward.z, tmp) * 180 / M_PI);
        
        if (pitch < 0)
        {
            pitch += 360;
        }
    }
    
    angles.x = pitch;
    angles.y = yaw;
    angles.z = 0;
}
 
void AnglesToAxis( const vec3 angles, vec3 axis[3] )
{
    vec3    right;
    
    AngleVectors( (float *)&angles, (float *)&axis[0], (float *)&right, (float *)&axis[2] );
    VectorSubtract( vec3_origin, right, axis[1] );
}
 
void VectorToViewangles(float *fEntTarg, float &fAngleX, float &fAngleY)
{
    vec3 vecEntity, vecAngle;
    VectorSubtract(fEntTarg, refdef->viewOrg, vecEntity);
    VectorAngles(vecEntity, vecAngle);
    vecAngle[PITCH] = -vecAngle[PITCH];
    if(vecAngle[YAW] > 180.0f)
        vecAngle[YAW] -= 360.0f;
    else if(vecAngle[YAW] < -180.0f)
        vecAngle[YAW] += 360.0f;
    if(vecAngle[PITCH] > 180.0f)
        vecAngle[PITCH] -= 360.0f;
    else if(vecAngle[PITCH] < -180.0f)
        vecAngle[PITCH] += 360.0f;
    //AnglesToAxis(vecAngle, refdef->viewAxis);
    vecAngle[YAW] -= cg->refdefViewAngles[YAW];
    if(vecAngle[YAW] > 180.0f)
        vecAngle[YAW] -= 360.0f;
    else if(vecAngle[YAW] < -180.0f)
        vecAngle[YAW] += 360.0f;
    vecAngle[PITCH] -= cg->refdefViewAngles[PITCH];
    if(vecAngle[PITCH] > 180.0f)
        vecAngle[PITCH] -= 360.0f;
    else if(vecAngle[PITCH] < -180.0f)
        vecAngle[PITCH] -= 360.0f;
    fAngleX = vecAngle[YAW];
    fAngleY = vecAngle[PITCH];
}
*/

































/*
#define	CMD_BACKUP	128
 
class CUserCmd
{
public:
	int iServerTime; 
	int iButtons;
    int iAngles[3];
	int iWeaponIndex;
	char unknown24[20];
};
 
class CClientActive
{
public:
    CUserCmd UserCmds[CMD_BACKUP]; 
    int iCurrentCmdNumber; 
 
    CUserCmd* GetUserCmd( int CmdNumber )
    {
        int id = CmdNumber & 0x7F;
 
        return &UserCmds[id];
    }
};*/

/*
typedef struct 
{
    __int32 ServerTime; //0000 - Only Exist in the first Struct
    __int32 PacketCount; //0004
    vec3 Origin; //0008
                char unknown2[20];
    vec3 viewAngle ; //0028
                char unknown5[12];
}c_usercmd_t;

typedef struct
{
    __int32 TimeOfLastPacketSent; //0000
        char unknown0[4];
    __int32 viewAngles[3];; //0008
    __int32 WeaponIndex; //0014
        char unknown3[16];
}usercmd_t;

typedef struct 
{
    int ServerTime;   //0004
    vec3 ViewAngles;//0016
    usercmd_t   usercmd  [128]; //size 1400
    c_usercmd_t c_usercmd[256]; //size 4000
    char unknown1[4];
    int CMDNum;// 256 Max

    usercmd_t *GetUserCommand    ( int CmdNum )
    {
        if( CmdNum >= 128 )
        {
            int Cmd = (CmdNum - 128);
            return &usercmd[Cmd];
        }
        return &usercmd[CmdNum];
    }

    c_usercmd_t *GetUserCamCommand( int CmdNum )
    {
        return &c_usercmd[CmdNum];
    }
}clientActive_t;*/


#define	CMD_BACKUP	128
 
class usercmd_t
{
public:
	int iServerTime; 
	int iButtons;
    float viewAngles[3];
	int iWeaponIndex;
	char unknown24[20];
};
 
class clientActive_t
{
public:
    usercmd_t UserCmds[CMD_BACKUP]; 
    int iCurrentCmdNumber; 
 
    usercmd_t* GetUserCmd( int CmdNumber )
    {
        int id = CmdNumber & 0x7F;
 
        return &UserCmds[id];
    }
};


bool silentAim = false;


opd_s CL_WritePacket_t = {0x001B6198,TOC};
int(*CL_WritePacket)(int localClient) = (int(*)(int))&CL_WritePacket_t;
opd_s CL_CreateNewCommands_t = {0x001B9478,TOC};
int(*CL_CreateNewCommands)(int localClient) = (int(*)(int))&CL_CreateNewCommands_t;

//cmdnum*0x2c+0x66AA0+*(int*)0x00AE9780
int getCurrentCmd(int add) {
	//0x3462BD58 works too
	return (*(int*)(128*0x2c+0x66AA0+*(int*)0x00AE9780)+add) & 0x7f;
	//return *(int*)(0x6A4A4+*(int*)0x00AE9780);
}
int getCmdAddr(int cmdnum) {
	return cmdnum*0x2c+0x66AA0+*(int*)0x00AE9780;
}
int getCCmdAddr(int cmdnum) {
	return cmdnum*0x24+0x680A4+*(int*)0x00AE9780;
}
#define ANGLE2SHORT(x)   ((int)((x)*65536/360) & 65535)
struct vec3i {
	int x,y,z;
};
float normalize180(float num) {
	while (num < -180)
		num+=360;
	while (num > 180)
		num-=360;
	return num;
}
float normalize90(float num) {
	while (num < -90)
		num+=180;
	while (num > 90)
		num-=180;
	if (num > 89)
		num = 88;
	if (num < -89)
		num = -88;
	return num;
}

void calcViewAngles() {
	int targindex = GetNearestPlayer(GetIndex());
	if (targindex != -1) {
		vec3 Aim = {menuInfo->positions[targindex].x,menuInfo->positions[targindex].y,menuInfo->positions[targindex].z/*-20*/};
		vec3 me = {menuInfo->positions[GetIndex()].x,menuInfo->positions[GetIndex()].y,menuInfo->positions[GetIndex()].z};
		/*if (autoAim) {
			//server sided, desynced so use server view pos
			me.x = SERVERVIEWPOS->x;//getViewOrigin()->x;//&getOrigin(GetIndex());
			me.y = SERVERVIEWPOS->y;//getViewOrigin()->y;
			me.z = SERVERVIEWPOS->z;//getViewOrigin()->z;
		} else {
			me.x = getViewRot().x;
			me.y = getViewRot().y;
			me.z = getViewRot().z;
		}*/
		//printf("VIEWPOS: 0x%X %i PLAYERSTATE: 0x%X %i\n",*(unsigned int*)&(SERVERVIEWPOS->x),(int)SERVERVIEWPOS->x,*(unsigned int*)&(PSORIGIN->x),(int)PSORIGIN->x);
		/*if (autoAim) {
			//position is not the same boi
			me.x = getOrigin(GetIndex()).x;
			me.y = getOrigin(GetIndex()).y;
			me.z = getOrigin(GetIndex()).z;
			Aim.x = getOrigin(targindex).x;
			Aim.y = getOrigin(targindex).y;
			Aim.z = getOrigin(targindex).z;
		}*/
		vec3 angles = {Aim.x - me.x,Aim.y - me.y,Aim.z - me.z};
		getBaseAngles();
		vec3 cangle = vectoangles(angles);
		vec3 fin = {cangle.x - menuInfo->baseAngleRet.x,cangle.y - menuInfo->baseAngleRet.y,0};
		menuInfo->AimAngles.x = fin.x;
		menuInfo->AimAngles.y = fin.y;
		menuInfo->AimAngles.z = 0;
		menuInfo->aimbothit = true;
	} else {
		menuInfo->aimbothit = false;
	}
}

int hkCL(int r3);
int wp_redo(int r3) {
	char bytes[16] = {0x7D, 0x80, 0x00, 0x26, 0xF8, 0x21, 0xF6, 0xA1, 0xFA, 0x01, 0x08, 0xE0, 0x3A, 0x01, 0x00, 0x70};
	write_process((void*)0x001B6198,bytes,16);
	int j = CL_WritePacket(r3);
	PatchInJump(0x001B6198,(int)hkCL,false);
	return j;
}
int clcnc_redo(int r3) {
	char bytes[16] = {0xF8, 0x21, 0xFF, 0x41, 0x7C, 0xC8, 0x02, 0xA6, 0x54, 0x64, 0x10, 0x3A, 0x54, 0x65, 0x28, 0x34};
	write_process((void*)0x001B9478,bytes,16);
	int j = CL_CreateNewCommands(r3);
	PatchInJump(0x001B9478,(int)hkCL,false);
	return j;
}



int oviewangles[3];
int cviewangles[3];

vec3i viewangles[128];

opd_s wepspread_t = {0x00114608,TOC};
bool(*BG_GetSpreadForWeapon)(unsigned int playerstate, unsigned int weapDef, float *minSpread, float *maxSpread) = (bool(*)(unsigned int,unsigned int,float*,float*))&wepspread_t;

void correctSpread(int cmd) {
    float minSpread, maxSpread, spreadX, spreadY;
 
    BG_GetSpreadForWeapon(PLAYERSTATE, getWeaponDef(CEntity(GetIndex())+0x244), &minSpread, &maxSpread);
 
    //RandomBulletDir(cmd->time, &spreadX, &spreadY);
 
    float aimSpreadScale = getAimValue() / 255.0f;
    float aimSpreadAmount = minSpread + ((maxSpread - minSpread) * aimSpreadScale);
    spreadX *= aimSpreadAmount;
    spreadY *= aimSpreadAmount;
	//printf("%s");
 
	vec3i *cmdangles = (vec3i*)(cmd+0x8);
    cmdangles->x += ANGLE2SHORT(spreadX);
    cmdangles->y += ANGLE2SHORT(spreadX);
}

void DoSilentAim(bool bAdjust)
{
    int cmd = getCmdAddr(getCurrentCmd(0));
	int oldcmd = getCmdAddr(getCurrentCmd(-1));

	vec3i *oldcmdangles = (vec3i*)(oldcmd+0x8);
	//vec3i *cmdangles = (vec3i*)(cmd+0x8);

    if (bAdjust) // Do adjustment
    {
        /* Backup servertime */
        //int stime = *(int*)oldcmd;

        /* Copy current command data to old command */
        //memcpy((void*)oldcmd, (void*)cmd, 0x2c);

        /* Restore old servertime but add 1 to activate l33t h4x */
        //*(int*)oldcmd = stime-1;
		*(int*)oldcmd = *(int*)oldcmd+2;
		//*(int*)cmd++;

        /* Backup old viewangles */
        //memcpy(oldcmdangles, oviewangles,4*3);
		//memcpy(cmdangles, cviewangles,4*3);


		int x = ANGLE2SHORT(normalize90(menuInfo->AimAngles.x));
		int y = ANGLE2SHORT(normalize180(menuInfo->AimAngles.y));

        /* Not ideal (see below) */
        oldcmdangles->x = /*cmdangles->x + */x;
        oldcmdangles->y = /*cmdangles->y + */y;
		//correctSpread(oldcmd);
		//cmdangles->x = /*cmdangles->x + */x;
        //cmdangles->y = /*cmdangles->y + */y;

		//*(int*)(oldcmd+0x4) &= ~(1<<0);//unshoot old cmd
		*(int*)(cmd+0x4) |= (1<<0);//shoot    oldcmd does not work
		if (autoAim) {
			//*(int*)(cmd+0x4) |= (1<<11);//aim
			//*(int*)(0x11921C) = 0x60000000;
			//*(char*)0x00AE1780 = 1;
		} else {
			//*(int*)(0x11921C) = 0xD19F0110;
		}

		/*for (int i = 0; i < 128; i++) {
			int cmd = getCmdAddr(getCurrentCmd(i));
			vec3i *angles = (vec3i*)(cmd+0x8);
			memcpy(angles,&(viewangles[i]),4*3);
			angles->x = x;
			angles->y = y;
		}*/
    }
    else // Fix angles
    {
        /* Restore old viewangles */
        //memcpy(oviewangles, oldcmdangles, 4*3);
		//memcpy(cviewangles, cmdangles, 4*3);
		//*(int*)(cmd+0x4) &= ~(1<<0);//unshoot
		//*(int*)(cmd+0x4) &= ~(1<<11);//unaim
		/*for (int i = 0; i < 128; i++) {
			int cmd = getCmdAddr(getCurrentCmd(i));
			vec3i *angles = (vec3i*)(cmd+0x8);
			memcpy(&(viewangles[i]),angles,4*3);
		}*/
    }
} 

bool justUnaimed = false;
int hkCL(int r3)
{
	//int ret;
	//int ret = clcnc_redo(r3);
	if (isInGameOrLoading()) {
	if (menuInfo->aimbothit && silentAim && (amIAiming() || RequireAiming == false)) {

		DoSilentAim(1); // Adjust angles
		if (autoAim) {
			justUnaimed = true;
			*(char*)0x00AE1780 = 1;
		}
		//ret = wp_redo(r3);

		//DoSilentAim(0); // Fix angles

		/*
		int curcmd = getCmdAddr(getCurrentCmd(0));
		int oldcmd = getCmdAddr(getCurrentCmd(-1));
		memcpy((void*)oldcmd,(void*)curcmd,0x2c);
		*(int*)oldcmd--;
		//*(int*)curcmd+=1;//makes it not work in private match even
		int x = ANGLE2SHORT(normalize90(menuInfo->AimAngles.x))-((vec3i*)(curcmd+0x8))->x;
		int y = ANGLE2SHORT(normalize180(menuInfo->AimAngles.y))-((vec3i*)(curcmd+0x8))->y;
		//printf("Angles: %i, %i  cmdnum: %i  time: %i\n",(int)silentmenuInfo->AimAngles.x,(int)silentmenuInfo->AimAngles.y,getCurrentCmd(0),*(int*)curcmd);
		vec3i *curangles;// = (vec3i*)(curcmd+0x8);
		curangles->x = x;
		curangles->y = y;
		curangles->z = 0;
		
		curangles = (vec3i*)(oldcmd+0x8);//eeh
		curangles->x = x;
		curangles->y = y;
		curangles->z = 0;

		//*(int*)(curcmd+0x4) &= ~(1<<0);//make me shoot
		*(int*)(curcmd+0x4) |= (1<<0);//make me shoot
		*/

		/*
		int x = ANGLE2SHORT(normalize90(menuInfo->AimAngles.x));
		int y = ANGLE2SHORT(normalize180(menuInfo->AimAngles.y));
		for (int i = 0; i < 128; i++) {
			int cmd = getCmdAddr(i);
			vec3i *angles = (vec3i*)(cmd+0x8);//eeh
			angles->x = x;
			angles->y = y;
			angles->z = 0;

			*(int*)(cmd+0x4) &= ~(1<<0);//make me shoot
			*(int*)(cmd+0x4) |= (1<<0);//make me shoot
		}*/
		
		/*
		int oldcmd = getCmdAddr(getCurrentCmd(-1));
		//int curcmd = getCmdAddr(getCurrentCmd(0));
		//int nextcmd = getCmdAddr(getCurrentCmd(1));
		//memcpy((void*)oldcmd,(void*)curcmd,0x2c);
		//*(int*)(128*0x2c+0x66AA0+*(int*)0x00AE9780) = *(int*)(128*0x2c+0x66AA0+*(int*)0x00AE9780)+1;//0x3462BD58
		//(*(int*)0x3462BD58)++;
		//*(int*)curcmd+=1;//makes it not work in private match even
		int x = ANGLE2SHORT(normalize90(menuInfo->AimAngles.x));
		int y = ANGLE2SHORT(normalize180(menuInfo->AimAngles.y));
		//printf("Angles: %i, %i  cmdnum: %i  time: %i\n",(int)silentmenuInfo->AimAngles.x,(int)silentmenuInfo->AimAngles.y,getCurrentCmd(0),*(int*)curcmd);
		//vec3i *ac = (vec3i*)(curcmd+0x8);

		vec3i *angles = (vec3i*)(oldcmd+0x8);
		angles->x = x;
		angles->y = y;
		angles->z = 0;

		*(int*)oldcmd+=1;

		//*(int*)(curcmd+0x4) |= (1<<0);//make me shoot
		*/
	} else {
		//ret = wp_redo(r3);
		if (autoAim) {
			if (justUnaimed == true) {
				justUnaimed = false;
				*(char*)0x00AE1780 = 0;
			}
		}
	}
	}
	//return ret;
	return wp_redo(r3);
} 

bool tmpautoshoot = false;
void Aimthread(uint64_t)
{
	for(;;) {
		//if (!silentAim) {
		if(AimbotEnabled && isInGameOrLoading()) {
			if (amIAiming() || RequireAiming == false) {
				/*if (autoAim) {
					vec3 v = {getOrigin(menuInfo->nearestClient).x,getOrigin(menuInfo->nearestClient).y,getOrigin(menuInfo->nearestClient).z};
					v.z+=50;
					v.x+=20;
					calcViewAngles(&v);
				} else {*/
					calcViewAngles();
				//}
				if (menuInfo->aimbothit && !silentAim) {
					setViewAngles(menuInfo->AimAngles.x,menuInfo->AimAngles.y,menuInfo->AimAngles.z);
					if(autoShoot) {
						tmpautoshoot = true;
						*(char*)0x00AE1820 = 1;
					}
				} else {
					if(autoShoot && tmpautoshoot) {
						tmpautoshoot = false;
						*(char*)0x00AE1820 = 0;
					}
				}

				
                /*int targindex = GetNearestPlayer(GetIndex());
				if (targindex != -1) {
						vec3 Aim;// = getOrigin(targindex);
						Aim.x = menuInfo->positions[targindex].x;
						Aim.y = menuInfo->positions[targindex].y;
						Aim.z = menuInfo->positions[targindex].z;
						vec3 *me=getViewOrigin();
						vec3 angles = {Aim.x - me->x,Aim.y - me->y,Aim.z - me->z};
						getBaseAngles();
						vec3 cangle = vectoangles(angles);
						vec3 fin = {cangle.x - baseAngleRet.x,cangle.y - baseAngleRet.y,0};
						//silentmenuInfo->AimAngles.x = fin.x;
						//silentmenuInfo->AimAngles.y = fin.y;
						//silentmenuInfo->AimAngles.z = fin.z;
						//if (!silentAim) {
							setViewAngles(fin.x,fin.y,fin.z);
							//menuInfo->aimbothit = false;
						//}
						*/
				/*} else {
					//menuInfo->aimbothit = false;
					if(autoShoot && tmpautoshoot) {
						tmpautoshoot = false;
						*(char*)0x00AE1820 = 0;
					}
				}*/
			} else {
				//menuInfo->aimbothit = false;
				if(autoShoot && tmpautoshoot) {
					tmpautoshoot = false;
					*(char*)0x00AE1820 = 0;
				}
			}
		} else {
			//menuInfo->aimbothit = false;
		}
		//}
		sleep(1);
	}
}