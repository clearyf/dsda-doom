//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 1993-2008 Raven Software
// Copyright(C) 2005-2014 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//


#ifndef __H2DEF__
#define __H2DEF__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <values.h>

#include "st_start.h"
// haleyjd: removed WATCOMC

// ticcmd:

#include "d_ticcmd.h"

// events

#include "d_event.h"

// gamemode/mission

#include "d_mode.h"

// for fixed_t:

#include "m_fixed.h"

// angle definitions:

#include "tables.h"

#include "d_loop.h"
#include "net_defs.h"

// all exterior data is defined here
#include "xddefs.h"

// all important printed strings
#include "textdefs.h"

// header generated by multigen utility
#include "info.h"

/*
===============================================================================

						GLOBAL TYPES

===============================================================================
*/

/*
===============================================================================

							MAPOBJ DATA

===============================================================================
*/

struct player_s;

typedef union
{
    intptr_t i;
    struct mobj_s *m;
    struct player_s *p;
} specialval_t;

extern weaponinfo_t WeaponInfo[NUMWEAPONS][NUMCLASSES];

typedef enum
{
    arti_none,
    arti_invulnerability,
    arti_health,
    arti_superhealth,
    arti_healingradius,
    arti_summon,
    arti_torch,
    arti_egg,
    arti_fly,
    arti_blastradius,
    arti_poisonbag,
    arti_teleportother,
    arti_speed,
    arti_boostmana,
    arti_boostarmor,
    arti_teleport,
    // Puzzle artifacts
    arti_firstpuzzitem,
    arti_puzzskull = arti_firstpuzzitem,
    arti_puzzgembig,
    arti_puzzgemred,
    arti_puzzgemgreen1,
    arti_puzzgemgreen2,
    arti_puzzgemblue1,
    arti_puzzgemblue2,
    arti_puzzbook1,
    arti_puzzbook2,
    arti_puzzskull2,
    arti_puzzfweapon,
    arti_puzzcweapon,
    arti_puzzmweapon,
    arti_puzzgear1,
    arti_puzzgear2,
    arti_puzzgear3,
    arti_puzzgear4,
    NUMARTIFACTS
} artitype_t;

typedef enum
{
    pw_None,
    pw_invulnerability,
    pw_allmap,
    pw_infrared,
    pw_flight,
    pw_shield,
    pw_health2,
    pw_speed,
    pw_minotaur,
    NUMPOWERS
} powertype_t;

#define	INVULNTICS (30*35)
#define	INVISTICS (60*35)
#define	INFRATICS (120*35)
#define	IRONTICS (60*35)
#define WPNLEV2TICS (40*35)
#define FLIGHTTICS (60*35)
#define SPEEDTICS (45*35)
#define MORPHTICS (40*35)
#define MAULATORTICS (25*35)

#define MESSAGETICS (4*35)
#define BLINKTHRESHOLD (4*35)

#define NUMINVENTORYSLOTS	NUMARTIFACTS

typedef struct
{
    int type;
    int count;
} inventory_t;

/*
================
=
= player_t
=
================
*/

typedef struct player_s
{
    int pieces;                 // Fourth Weapon pieces
    short ultimateMessage;
    short yellowMessage;
    int poisoncount;            // screen flash for poison damage
    mobj_t *poisoner;           // NULL for non-player mobjs
    unsigned int jumpTics;      // delay the next jump for a moment
    unsigned int worldTimer;    // total time the player's been playing
} player_t;

#define CF_NOCLIP		1
#define	CF_GODMODE		2
#define	CF_NOMOMENTUM	4       // not really a cheat, just a debug aid

#define	SBARHEIGHT	(39 << crispy->hires)      // status bar height at bottom of screen

void NET_SendFrags(player_t * player);

/*
===============================================================================

					GLOBAL VARIABLES

===============================================================================
*/

#define TELEFOGHEIGHT (32*FRACUNIT)

extern GameMode_t gamemode;         // Always commercial

extern gameaction_t gameaction;

extern dboolean paused;

extern dboolean DevMaps;         // true = map development mode
extern char *DevMapsDir;        // development maps directory

extern dboolean nomonsters;      // checkparm of -nomonsters

extern dboolean respawnparm;     // checkparm of -respawn

extern dboolean randomclass;     // checkparm of -randclass

extern dboolean debugmode;       // checkparm of -debug

extern dboolean usergame;        // ok to save / end game

extern dboolean ravpic;          // checkparm of -ravpic

extern dboolean altpal;          // checkparm to use an alternate palette routine

extern dboolean cdrom;           // true if cd-rom mode active ("-cdrom")

extern dboolean deathmatch;      // only if started as net death

extern dboolean netgame;         // only true if >1 player

extern dboolean cmdfrag;         // true if a CMD_FRAG packet should be sent out every
                                                // kill

extern dboolean playeringame[MAXPLAYERS];
extern pclass_t PlayerClass[MAXPLAYERS];

extern int consoleplayer;       // player taking events and displaying

extern int displayplayer;

extern int viewangleoffset;     // ANG90 = left side, ANG270 = right

extern player_t players[MAXPLAYERS];

extern dboolean DebugSound;      // debug flag for displaying sound info

extern dboolean demoplayback;
extern dboolean demoextend;      // allow demos to persist through exit/respawn
extern int maxzone;             // Maximum chunk allocated for zone heap

// Truncate angleturn in ticcmds to nearest 256.
// Used when recording Vanilla demos in netgames.
extern dboolean lowres_turn;

extern int Sky1Texture;
extern int Sky2Texture;

extern gamestate_t gamestate;
extern skill_t gameskill;
//extern        dboolean         respawnmonsters;
extern int gameepisode;
extern int gamemap;
extern int prevmap;
extern int levelstarttic;       // gametic at level start
extern int leveltime;           // tics in game play for par

extern ticcmd_t *netcmds;

#define MAXDEATHMATCHSTARTS 16
extern mapthing_t *deathmatch_p;
extern mapthing_t deathmatchstarts[MAXDEATHMATCHSTARTS];

// Position indicator for cooperative net-play reborn
extern int RebornPosition;

#define MAX_PLAYER_STARTS 8
extern mapthing_t playerstarts[MAX_PLAYER_STARTS][MAXPLAYERS];
extern int maxplayers;

extern int mouseSensitivity;

extern dboolean precache;        // if true, load all graphics at level load

extern byte *screen;            // off screen work buffer, from V_video.c

extern dboolean singledemo;      // quit after playing a demo from cmdline

extern int bodyqueslot;
extern skill_t startskill;
extern int startepisode;
extern int startmap;
extern dboolean autostart;

extern dboolean testcontrols;
extern int testcontrols_mousespeed;

extern int vanilla_savegame_limit;
extern int vanilla_demo_limit;

/*
===============================================================================

					GLOBAL FUNCTIONS

===============================================================================
*/

#include "w_wad.h"
#include "z_zone.h"

//----------
//BASE LEVEL
//----------
void H2_Main(void);
// not a globally visible function, just included for source reference
// calls all startup code
// parses command line options
// if not overrided, calls N_AdvanceDemo

void H2_GameLoop(void);
// not a globally visible function, just included for source reference
// called by H2_Main, never exits
// manages timing and IO
// calls all ?_Responder, ?_Ticker, and ?_Drawer functions
// calls I_GetTime, I_StartFrame, and I_StartTic

//---------
//SYSTEM IO
//---------
byte *I_AllocLow(int length);
// allocates from low memory under dos, just mallocs under unix

// haleyjd: was WATCOMC, again preserved for historical interest as in Heretic
#if 0
extern dboolean useexterndriver;

#define EBT_FIRE			1
#define EBT_OPENDOOR 		2
#define EBT_SPEED			4
#define EBT_STRAFE			8
#define EBT_MAP				0x10
#define EBT_INVENTORYLEFT 	0x20
#define EBT_INVENTORYRIGHT 	0x40
#define EBT_USEARTIFACT		0x80
#define EBT_FLYDROP			0x100
#define EBT_CENTERVIEW		0x200
#define EBT_PAUSE			0x400
#define EBT_WEAPONCYCLE		0x800
#define EBT_JUMP			0x1000

typedef struct
{
    short vector;               // Interrupt vector

    signed char moveForward;    // forward/backward (maxes at 50)
    signed char moveSideways;   // strafe (maxes at 24)
    short angleTurn;            // turning speed (640 [slow] 1280 [fast])
    short angleHead;            // head angle (+2080 [left] : 0 [center] : -2048 [right])
    signed char pitch;          // look up/down (-110 : +90)
    signed char flyDirection;   // flyheight (+1/-1)
    unsigned short buttons;     // EBT_* flags
} externdata_t;
#endif

//----
//GAME
//----

void G_DeathMatchSpawnPlayer(int playernum);

void G_InitNew(skill_t skill, int episode, int map);

void G_DeferedInitNew(skill_t skill, int episode, int map);
// can be called by the startup code or M_Responder
// a normal game starts at map 1, but a warp test can start elsewhere

void G_DeferredNewGame(skill_t skill);

void G_DeferedPlayDemo(const char *demo);

void G_LoadGame(int slot);
// can be called by the startup code or M_Responder
// calls P_SetupLevel or W_EnterWorld
void G_DoLoadGame(void);

void G_SaveGame(int slot, char *description);
// called by M_Responder

void G_RecordDemo(skill_t skill, int numplayers, int episode, int map,
                  const char *name);
// only called by startup code

void G_PlayDemo(char *name);
void G_TimeDemo(char *name);

void G_TeleportNewMap(int map, int position);

void G_Completed(int map, int position);
//void G_ExitLevel (void);
//void G_SecretExitLevel (void);

void G_StartNewGame(skill_t skill);
void G_StartNewInit(void);

void G_WorldDone(void);

void G_Ticker(void);
dboolean G_Responder(event_t * ev);

void G_ScreenShot(void);

//-------
//SV_SAVE
//-------

#define HXS_VERSION_TEXT "HXS Ver 2.37"
#define HXS_VERSION_TEXT_LENGTH 16
#define HXS_DESCRIPTION_LENGTH 24

extern char *SavePath;

void SV_SaveGame(int slot, const char *description);
void SV_SaveMap(dboolean savePlayers);
void SV_LoadGame(int slot);
void SV_MapTeleport(int map, int position);
void SV_LoadMap(void);
void SV_InitBaseSlot(void);
void SV_UpdateRebornSlot(void);
void SV_ClearRebornSlot(void);
dboolean SV_RebornSlotAvailable(void);
int SV_GetRebornSlot(void);

//-----
//PLAY
//-----

void P_Ticker(void);
// called by C_Ticker
// can call G_PlayerExited
// carries out all thinking of monsters and players

void P_SetupLevel(int episode, int map, int playermask, skill_t skill);
// called by W_Ticker

void P_Init(void);
// called by startup code

int P_GetMapCluster(int map);
int P_TranslateMap(int map);
int P_GetMapCDTrack(int map);
int P_GetMapWarpTrans(int map);
int P_GetMapNextMap(int map);
int P_GetMapSky1Texture(int map);
int P_GetMapSky2Texture(int map);
char *P_GetMapName(int map);
fixed_t P_GetMapSky1ScrollDelta(int map);
fixed_t P_GetMapSky2ScrollDelta(int map);
dboolean P_GetMapDoubleSky(int map);
dboolean P_GetMapLightning(int map);
dboolean P_GetMapFadeTable(int map);
char *P_GetMapSongLump(int map);
void P_PutMapSongLump(int map, char *lumpName);
int P_GetCDStartTrack(void);
int P_GetCDEnd1Track(void);
int P_GetCDEnd2Track(void);
int P_GetCDEnd3Track(void);
int P_GetCDIntermissionTrack(void);
int P_GetCDTitleTrack(void);

//-------
//REFRESH
//-------

extern dboolean setsizeneeded;

extern dboolean BorderNeedRefresh;
extern dboolean BorderTopRefresh;

extern int UpdateState;
// define the different areas for the dirty map
#define I_NOUPDATE	0
#define I_FULLVIEW	1
#define I_STATBAR	2
#define I_MESSAGES	4
#define I_FULLSCRN	8

void R_RenderPlayerView(player_t * player);
// called by G_Drawer

void R_Init(void);
// called by startup code

void R_DrawViewBorder(void);
void R_DrawTopBorder(void);
// if the view size is not full screen, draws a border around it

void R_SetViewSize(int blocks, int detail);
// called by M_Responder

int R_FlatNumForName(const char *name);

int R_TextureNumForName(const char *name);
int R_CheckTextureNumForName(const char *name);
// called by P_Ticker for switches and animations
// returns the texture number for the texture name


//----
//MISC
//----
extern int localQuakeHappening[MAXPLAYERS];

int M_DrawText(int x, int y, dboolean direct, char *string);

//------------------------------
// SC_man.c
//------------------------------

void SC_Open(const char *name);
void SC_OpenLump(const char *name);
void SC_OpenFile(const char *name);
void SC_Close(void);
dboolean SC_GetString(void);
void SC_MustGetString(void);
void SC_MustGetStringName(char *name);
dboolean SC_GetNumber(void);
void SC_MustGetNumber(void);
void SC_UnGet(void);
//dboolean SC_Check(void);
dboolean SC_Compare(const char *text);
int SC_MatchString(const char **strings);
int SC_MustMatchString(const char **strings);
void SC_ScriptError(const char *message);

extern char *sc_String;
extern int sc_Number;
extern int sc_Line;
extern dboolean sc_End;
extern dboolean sc_Crossed;
extern dboolean sc_FileScripts;
extern const char *sc_ScriptsDir;

//------------------------------
// SN_sonix.c
//------------------------------

enum
{
    SEQ_PLATFORM,
    SEQ_PLATFORM_HEAVY,         // same script as a normal platform
    SEQ_PLATFORM_METAL,
    SEQ_PLATFORM_CREAK,         // same script as a normal platform
    SEQ_PLATFORM_SILENCE,
    SEQ_PLATFORM_LAVA,
    SEQ_PLATFORM_WATER,
    SEQ_PLATFORM_ICE,
    SEQ_PLATFORM_EARTH,
    SEQ_PLATFORM_METAL2,
    SEQ_DOOR_STONE,
    SEQ_DOOR_HEAVY,
    SEQ_DOOR_METAL,
    SEQ_DOOR_CREAK,
    SEQ_DOOR_SILENCE,
    SEQ_DOOR_LAVA,
    SEQ_DOOR_WATER,
    SEQ_DOOR_ICE,
    SEQ_DOOR_EARTH,
    SEQ_DOOR_METAL2,
    SEQ_ESOUND_WIND,
    SEQ_NUMSEQ
};

typedef enum
{
    SEQTYPE_STONE,
    SEQTYPE_HEAVY,
    SEQTYPE_METAL,
    SEQTYPE_CREAK,
    SEQTYPE_SILENCE,
    SEQTYPE_LAVA,
    SEQTYPE_WATER,
    SEQTYPE_ICE,
    SEQTYPE_EARTH,
    SEQTYPE_METAL2,
    SEQTYPE_NUMSEQ
} seqtype_t;

void SN_InitSequenceScript(void);
void SN_StartSequence(mobj_t * mobj, int sequence);
void SN_StartSequenceName(mobj_t * mobj, char *name);
void SN_StopSequence(mobj_t * mobj);
void SN_UpdateActiveSequences(void);
void SN_StopAllSequences(void);
int SN_GetSequenceOffset(int sequence, int *sequencePtr);
void SN_ChangeNodeData(int nodeNum, int seqOffset, int delayTics, int volume,
                       int currentSoundID);


typedef struct seqnode_s seqnode_t;
struct seqnode_s
{
    int *sequencePtr;
    int sequence;
    mobj_t *mobj;
    int currentSoundID;
    int delayTics;
    int volume;
    int stopSound;
    seqnode_t *prev;
    seqnode_t *next;
};

extern int ActiveSequences;
extern seqnode_t *SequenceListHead;

//----------------------
// Interlude (IN_lude.c)
//----------------------

#define MAX_INTRMSN_MESSAGE_SIZE 1024

extern dboolean intermission;
extern char ClusterMessage[MAX_INTRMSN_MESSAGE_SIZE];

void IN_Start(void);
void IN_Ticker(void);
void IN_Drawer(void);

//----------------------
// Chat mode (CT_chat.c)
//----------------------

void CT_Init(void);
void CT_Drawer(void);
dboolean CT_Responder(event_t * ev);
void CT_Ticker(void);
char CT_dequeueChatChar(void);

extern dboolean chatmodeon;

//--------------------
// Finale (F_finale.c)
//--------------------

void F_Drawer(void);
void F_Ticker(void);
void F_StartFinale(void);

//----------------------
// STATUS BAR (SB_bar.c)
//----------------------

extern int inv_ptr;
extern int curpos;
void SB_Init(void);
void SB_SetClassData(void);
dboolean SB_Responder(event_t * event);
void SB_Ticker(void);
void SB_Drawer(void);
void Draw_TeleportIcon(void);
void Draw_SaveIcon(void);
void Draw_LoadIcon(void);

//-----------------
// MENU (MN_menu.c)
//-----------------

void MN_Init(void);
void MN_ActivateMenu(void);
void MN_DeactivateMenu(void);
dboolean MN_Responder(event_t * event);
void MN_Ticker(void);
void MN_Drawer(void);
void MN_DrTextA(const char *text, int x, int y);
void MN_DrTextAYellow(const char *text, int x, int y);
int MN_TextAWidth(const char *text);
void MN_DrTextB(const char *text, int x, int y);
int MN_TextBWidth(const char *text);

extern int messageson;

#include "sounds.h"

#endif // __H2DEF__
