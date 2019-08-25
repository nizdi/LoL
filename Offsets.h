#pragma once
#define TARGET_GAMEVERSION "Version 9.16.284.8446 [PUBLIC]"
#define oCastSpell 0x5AF790 //0xF9F790
#define oIsTroy 0x219C60 //0xC16860
#define oIsMissile 0x229D60 //0xC16600
#define oIsNotWall 0x7576A0 //0x11476A0
#define oIsTargetable 0x222C20 //0xC0F600
#define oIsNexus 0x226520 //0xC16520
#define oIsHero 0x229D00 //0xC165A0
#define oDrawCircle 0x40FAF0 //0xF97940
#define oIsDragon 0x215080 //0xC05080
#define oUpdateChargeableSpell 0x5B1F60 //0xFA1F60
#define oIsMinion 0x229D40 //0xC165E0
#define oIsBaron 0x215C50 //0xC05C50
#define oIsAlive 0x1E6980 //0xBD2560
#define oIsInhib 0x226420 //0xC16420
#define oPrintChat 0x5EA6E0 //0xFDA6E0
#define oGetBasicAttack 0x1B3960 //0xBA3960
#define oIssueOrder 0x1BE3D0 //0xBAE3D0
#define oIsTurret 0x226770 //0xC16770
#define oGetAttackDelay 0x2F6760 //0xFA8030
#define oGetAttackCastDelay 0x16F0270 //0xB6B8D0
#define oGetSpellState 0x40BBD0 //0xF95440

#define oRenderer 0x2F5D88C //0x394D88C
#define oChatClientPtr 0x1692E0C //0x2082E0C
#define oGameVersion 0x2F9B000 //0x393AB50
#define oObjManager 0x16AE9A8 //0x392FF78
#define oLocalPlayer 0x2F8F7D4 //0x39307EC
#define oGameTime 0x2F8AA88 //0x392C6E8
#define oZoomClass 0x2F3C4F8 //0x392C4F8
#define oHudInstance 0x16F0270 //0x2085410

#define oScreenWidth 0x18
#define oScreenHeight 0x1C
#define oViewMatrix 0x64
#define oProjection 0xA4

#define oObjBuffMgr 0x20E8
#define oObjSpellBook 0x2898
#define oObjChampionName 0x3168
#define XorKey 0xEFEE81C4
#define oObjIndex 0x1E
#define oObjTeam 0x44
#define oObjName 0x60
#define oObjNetworkID 0x110
#define oObjSourceIndex 0x250
#define oObjPos 0x1A0
#define oObjTargetID 0x320 //not sure, didn't test.
#define oObjVisibility 0x428
#define oObjHealth 0xDD4
#define oObjArmor 0x1278
#define oObjBaseAtk 0x1250
#define oObjBonusAtk 0x11D0
#define oObjMoveSpeed 0x1290
#define oObjAtkRange 0x1298
#define oObjCombatType 0x21D0
#define oObjLevel 0x4BAC
#define oObjMaxHealth 0xDE4
#define oObjMana 0x454
#define oObjMaxMana 0x464

#define oObjSpellStartPos 0x2E4
#define oObjSpellEndPos 0x2F0

//Missile

#define missileStartPos 0x2E4
#define missileEndPos 0x2F0

//Buff

#define O_BUFFMGR_BUFFNAME 0x08
#define O_BUFFMGR_STARTTIME 0xC
#define O_BUFFMGR_ENDTIME 0x10
#define O_BUFFMGR_flBUFFCOUNT 0x2C
#define O_BUFFMGR_iBUFFCOUNT 0x70

//AI MGR

#define O_AIMGR_TARGETPOS 0x10
#define O_AIMGR_ISMOVING 0x198
#define O_AIMGR_ISDASHING 0x1E8
#define O_AIMGR_NAVBEGIN 0x1BC //NOT VERIFIED
#define O_AIMGR_NAVEND 0x1C0 //NOT VERIFIED
#define O_AIMGR_HASNAVPATH 0x19C //NOT VERIFIED
#define O_AIMGR_CURRENTPOS 0x2BC //NOT VERIFIED
#define O_AIMGR_VELOCITY 0x2C0 //NOT VERIFIED
#define oWorldToScreen 0x815060
#define oNetClient 0x2F95DF4
#define oGetPing 0x35DE00
#define oUnderMouseObject 0x2340A3C  