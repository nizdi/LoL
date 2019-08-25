#pragma once
#include <Windows.h>
#include "SpellInfo.h"
#include <vector>
#include "Vector.h"
class CSpellEntry {
public:
	SpellData* GetSpellData() {
		auto retaddr = *(DWORD*)(this + 0x8);
		if (retaddr == NULL)
			return NULL;
		auto ret = *(DWORD*)(retaddr + 0x38);
		if (ret == NULL)
			return NULL;
		return (SpellData*)(ret);
	}

	bool isAutoAttack() {
			return *(bool*)((DWORD)this + 0xAC);
	
	}
	int targetID() {
		return *(int*)((DWORD)this + 0xAC);
	}
		Vector GetStartPos() {
			return *(Vector*)((DWORD)this + 0x78);
		}

		Vector GetEndPos() {
			return *(Vector*)((DWORD)this + 0x84);
		}

};