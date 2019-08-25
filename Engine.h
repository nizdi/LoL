#pragma once
#include "Offsets.h"
#include "Utils.h"
#include "Vector.h"
#include "Hooks.h"
#include "CObjectManager.h"
#include <d3dx9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <stdio.h>
#include "Renderer.h"
#include <d3dx9math.h>
#include <d3dx9math.inl>
#define me Engine::GetLocalObject()

class Engine {
public:


	static Vector GetMouseWorldPosition() {
		DWORD MousePtr = (DWORD)GetModuleHandle(NULL) + oHudInstance;
		auto aux1 = *(DWORD*)MousePtr;
		aux1 += 0x14;
		auto aux2 = *(DWORD*)aux1;
		aux2 += 0x1C;

		float X = *(float*)(aux2 + 0x0);
		float Y = *(float*)(aux2 + 0x4);
		float Z = *(float*)(aux2 + 0x8);

		return Vector{ X, Y, Z };
	}

	static float GetGameTime() {
		return *(float*)(baseAddr + oGameTime);
	}

	static CObject* GetLocalObject() {
		auto retaddr = *(DWORD*)(baseAddr + oLocalPlayer);
		if (retaddr == NULL)
			return NULL;

		return (CObject*)retaddr;
	}

	static CObject* GetObjectByID(int ID)
	{
		if (ObjManager != NULL && ID >= 0 && ID <= 10000) {
			return ObjManager->objectArray[ID];
		}
		return NULL;
	}

	static void MoveTo(Vector* pos) {
		Vector poss = Vector(pos->X, pos->Y, pos->Z);
		if (GetLocalObject()->GetPos().DistTo(poss) < 150.0f) {
			Vector test = poss - (poss - me->GetPos()) * (150.0f / me->GetPos().DistTo(poss));
			Vector maxERange = Vector(-test.X, -test.Y, -test.Z);
			Functions.IssueOrder(GetLocalObject(), 2, &maxERange, NULL, false, false, false);
		}
		else {
			Functions.IssueOrder(GetLocalObject(), 2, pos, NULL, false, false, false);
		}
		
	}


	static void Attack(CObject* target, bool isMinion) {
		Vector* vec = new Vector(target->GetPos().X, target->GetPos().Y, target->GetPos().Z);
		Functions.IssueOrder(GetLocalObject(), 3, vec, target, 1, isMinion, 0);
	}

	static void Engine::CastSpellSelf(int SlotID) {
		if (me->IsAlive()) {
			auto spellbook = (DWORD)me + oObjSpellBook;
			auto spellslot = me->GetSpellBook()->GetSpellSlotByID(SlotID);
				Functions.CastSpell(spellbook, spellslot, SlotID, &me->GetPos(), &me->GetPos(), 0);
		}
	}

	static void Engine::CastSpellPos(int SlotID, Vector pos) {
		auto spellbook = (DWORD)me + oObjSpellBook;
		auto spellslot = me->GetSpellBook()->GetSpellSlotByID(SlotID);
		auto targetpos = &pos;

			Functions.CastSpell(spellbook, spellslot, SlotID, targetpos, new Vector(0,0,0), 0x0);
	}

	static void Engine::CastSpellPos(int SlotID, float x, float y, float z, CObject* obj) {
		auto spellbook = (DWORD)me + oObjSpellBook;
		auto spellslot = me->GetSpellBook()->GetSpellSlotByID(SlotID);
		Vector* pos = new Vector(x, y, z);
		Functions.CastSpell(spellbook, spellslot, SlotID, &obj->GetPos(), &me->GetPos(), obj->GetNetworkID());
	}

	static void Engine::CastSpellTargetted(int SlotID, CObject* obj) {
		auto spellbook = (DWORD)me + oObjSpellBook;
		auto spellslot = me->GetSpellBook()->GetSpellSlotByID(SlotID);

			Functions.CastSpell(spellbook, spellslot, SlotID, &obj->GetPos(), &me->GetPos(), obj->GetNetworkID());
	}

	static float Engine::getCD(int slot, CObject* obj) {

		//Console.print("CD : %f", obj->GetSpellBook()->GetSpellSlotByID(slot)->GetCD() - Engine::GetGameTime());
		return obj->GetSpellBook()->GetSpellSlotByID(slot)->GetCD();
	}

	static bool Engine::IsReady(int slot, CObject* obj) {
		//Console.print("LEVEL : %i", obj->GetSpellBook()->GetSpellSlotByID(slot)->GetLevel());
		return obj->GetSpellBook()->GetSpellSlotByID(slot)->GetLevel() >= 1 && getCD(slot, obj) == 0.0f;
	}


	D3DXMATRIX * D3DXMatrixMultiply(D3DXMATRIX * pOut, const D3DXMATRIX * pM1, const D3DXMATRIX * pM2)
	{
		if (pOut == NULL) {
			pOut = D3DXMatrixIdentity(pOut);
		}

		pOut->_11 = pM1->_11 * pM2->_11 + pM1->_12 * pM2->_21 + pM1->_13 * pM2->_31 + pM1->_14 * pM2->_41;
		pOut->_12 = pM1->_11 * pM2->_12 + pM1->_12 * pM2->_22 + pM1->_13 * pM2->_32 + pM1->_14 * pM2->_42;
		pOut->_13 = pM1->_11 * pM2->_13 + pM1->_12 * pM2->_23 + pM1->_13 * pM2->_33 + pM1->_14 * pM2->_43;
		pOut->_14 = pM1->_11 * pM2->_14 + pM1->_12 * pM2->_24 + pM1->_13 * pM2->_34 + pM1->_14 * pM2->_44;
		pOut->_21 = pM1->_21 * pM2->_11 + pM1->_22 * pM2->_21 + pM1->_23 * pM2->_31 + pM1->_24 * pM2->_41;
		pOut->_22 = pM1->_21 * pM2->_12 + pM1->_22 * pM2->_22 + pM1->_23 * pM2->_32 + pM1->_24 * pM2->_42;
		pOut->_23 = pM1->_21 * pM2->_13 + pM1->_22 * pM2->_23 + pM1->_23 * pM2->_33 + pM1->_24 * pM2->_43;
		pOut->_24 = pM1->_21 * pM2->_14 + pM1->_22 * pM2->_24 + pM1->_23 * pM2->_34 + pM1->_24 * pM2->_44;
		pOut->_31 = pM1->_31 * pM2->_11 + pM1->_32 * pM2->_21 + pM1->_33 * pM2->_31 + pM1->_34 * pM2->_41;
		pOut->_32 = pM1->_31 * pM2->_12 + pM1->_32 * pM2->_22 + pM1->_33 * pM2->_32 + pM1->_34 * pM2->_42;
		pOut->_33 = pM1->_31 * pM2->_13 + pM1->_32 * pM2->_23 + pM1->_33 * pM2->_33 + pM1->_34 * pM2->_43;
		pOut->_34 = pM1->_31 * pM2->_14 + pM1->_32 * pM2->_24 + pM1->_33 * pM2->_34 + pM1->_34 * pM2->_44;
		pOut->_41 = pM1->_41 * pM2->_11 + pM1->_42 * pM2->_21 + pM1->_43 * pM2->_31 + pM1->_44 * pM2->_41;
		pOut->_42 = pM1->_41 * pM2->_12 + pM1->_42 * pM2->_22 + pM1->_43 * pM2->_32 + pM1->_44 * pM2->_42;
		pOut->_43 = pM1->_41 * pM2->_13 + pM1->_42 * pM2->_23 + pM1->_43 * pM2->_33 + pM1->_44 * pM2->_43;
		pOut->_44 = pM1->_41 * pM2->_14 + pM1->_42 * pM2->_24 + pM1->_43 * pM2->_34 + pM1->_44 * pM2->_44;

		return pOut;
	}


	D3DXVECTOR2 WorldToScreen(D3DXVECTOR3 pos)
	{
		Renderer * ritorender = (Renderer*)*(DWORD*)(baseAddr + oRenderer);
		D3DXMATRIX viewMatrix = ritorender->viewMatrix(); //1
		D3DXMATRIX projMatrix = ritorender->projMatrix(); //2

		D3DXVECTOR2 returnVec = D3DXVECTOR2();
		D3DXVECTOR2 screen = D3DXVECTOR2(1600, 900);

		D3DXMATRIX* matrix = new D3DXMATRIX();
		D3DXMatrixMultiply(matrix, &viewMatrix, &projMatrix);


		D3DXVECTOR4 clipCoords = D3DXVECTOR4();

		clipCoords.x = pos.x * matrix->_11 + pos.y * matrix->_21 + pos.z * matrix->_31 + matrix->_41;
		clipCoords.y = pos.x * matrix->_12 + pos.y * matrix->_22 + pos.z * matrix->_32 + matrix->_42;
		clipCoords.z = pos.x * matrix->_13 + pos.y * matrix->_23 + pos.z * matrix->_33 + matrix->_43;
		clipCoords.w = pos.x * matrix->_14 + pos.y * matrix->_24 + pos.z * matrix->_34 + matrix->_44;


		if (clipCoords[3] < 0.1f)
			return returnVec;

		D3DXVECTOR3 M = D3DXVECTOR3();
		M.x = clipCoords.x / clipCoords.w;
		M.y = clipCoords.y / clipCoords.w;
		M.z = clipCoords.z / clipCoords.w;

		returnVec.x = (screen.x / 2 * M.x) + (M.x + screen.x / 2);
		returnVec.y = -(screen.y / 2 * M.y) + (M.y + screen.y / 2);
		return returnVec;
	}

	static bool IsWall(Vector vec) {
		return !Functions.IsNotWall(&vec, 0);
	}

};