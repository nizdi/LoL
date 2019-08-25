// dllmain.cpp : Define o ponto de entrada para da aplicação DLL.
#include <time.h>
#include "stdafx.h"
#include "guicon.h"
#include "Engine.h"
#include "Hooks.h"
#include "detours.h"
#include "Orbwalker.h"
#pragma comment(lib, "detours.lib")

CObjectManager* ObjManager;
CConsole Console;
CFunctions Functions;
Orbwalker* orb = new Orbwalker();
clock_t lastmove = NULL;
bool bInit = false;
typedef HRESULT(WINAPI *Prototype_Present)(DWORD, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
Prototype_Present Original_Present;

HRESULT WINAPI Hooked_Present(DWORD Device, CONST RECT *pSrcRect, CONST RECT *pDestRect, HWND hDestWindow, CONST RGNDATA *pDirtyRegion) {
	/*if (me->GetSpellBook()->GetActiveSpellEntry()) {
		Console.print("Missile speed : %f", me->GetSpellBook()->GetActiveSpellEntry()->GetSpellData()->GetMissileSpeed());
	}*/
	if (me) {
		if (me->IsAlive()) {
			orb->Poppy();
			//orb->Kalista();
			orb->autoWCaitlyn();
			orb->autoQSivir();
		}
	}

		

		if (GetAsyncKeyState(VK_SPACE) < 0)
		{
			//Console.print("Missile speed : %f, %f , %f", me->GetAIManager()->GetVelocity().X, me->GetAIManager()->GetVelocity().Y, me->GetAIManager()->GetVelocity().Z);
			if (me) {
				if (!bInit) {
					bInit = true;
				}
				if (me->IsAlive()) {
					orb->Combo();
					//Console.print("%f \n", me->GetBoundingRadius());
				}
			}




		}
		if (GetAsyncKeyState(0x56) < 0) { // 0x56 = V Key

			orb->LaneClear();
		}
		if (GetAsyncKeyState(0x43) < 0) { // 0x43 = C Key

			orb->LastHit();
		}

	

	return Original_Present(Device, pSrcRect, pDestRect, hDestWindow, pDirtyRegion);
}

DWORD FindDevice(DWORD Len)
{
	DWORD dwObjBase = 0;

	dwObjBase = (DWORD)LoadLibrary("d3d9.dll");
	while (dwObjBase++ < dwObjBase + Len)
	{
		if ((*(WORD*)(dwObjBase + 0x00)) == 0x06C7
			&& (*(WORD*)(dwObjBase + 0x06)) == 0x8689
			&& (*(WORD*)(dwObjBase + 0x0C)) == 0x8689
			) {
			dwObjBase += 2; break;
		}
	}
	return(dwObjBase);
}

DWORD GetDeviceAddress(int VTableIndex)
{
	PDWORD VTable;
	*(DWORD*)&VTable = *(DWORD*)FindDevice(0x128000);
	return VTable[VTableIndex];
}

void __stdcall Start() {
	//Console.startConsoleWin(80, 25, NULL);

	while (Engine::GetGameTime() < 1.0f || !me)
		Sleep(1);

	ObjManager = (CObjectManager*)(baseAddr + oObjManager);
	if (ObjManager) {
		orb->ObjManager = ObjManager;
	}
	Functions.PrintChat = (Typedefs::fnPrintChat)(baseAddr + oPrintChat);
	Functions.IsTargetable = (Typedefs::fnIsTargetable)(baseAddr + oIsTargetable);
	Functions.IsAlive = (Typedefs::fnIsAlive)(baseAddr + oIsAlive);

	Functions.IsMinion = (Typedefs::fnIsMinion)(baseAddr + oIsMinion);
	Functions.IsTurret = (Typedefs::fnIsTurret)(baseAddr + oIsTurret);
	Functions.IsHero = (Typedefs::fnIsHero)(baseAddr + oIsHero);
	Functions.IsMissile = (Typedefs::fnIsMissile)(baseAddr + oIsMissile);
	Functions.IsNexus = (Typedefs::fnIsNexus)(baseAddr + oIsNexus);
	Functions.IsInhibitor = (Typedefs::fnIsInhibitor)(baseAddr + oIsInhib);
	Functions.IsTroyEnt = (Typedefs::fnIsTroyEnt)(baseAddr + oIsTroy);

	Functions.CastSpell = (Typedefs::fnCastSpell)((DWORD)GetModuleHandle(NULL) + oCastSpell);
	Functions.IssueOrder = (Typedefs::fnIssueOrder)((DWORD)GetModuleHandle(NULL) + oIssueOrder);
	Functions.DrawCircle = (Typedefs::fnDrawCircle)((DWORD)GetModuleHandle(NULL) + oDrawCircle);
	//Functions.IsNotWall = (Typedefs::fnIsNotWall)((DWORD)GetModuleHandle(NULL) + oIsNotWall); 
	Functions.GetAttackCastDelay = (Typedefs::fnGetAttackCastDelay)((DWORD)GetModuleHandle(NULL) + oGetAttackCastDelay);
	Functions.GetAttackDelay = (Typedefs::fnGetAttackDelay)((DWORD)GetModuleHandle(NULL) + oGetAttackDelay);

	Original_Present = (Prototype_Present)DetourFunction((PBYTE)GetDeviceAddress(17), (PBYTE)Hooked_Present);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Start, 0, 0, 0);
		return TRUE;
	}

	else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
		return TRUE;
	}
	return FALSE;
}
