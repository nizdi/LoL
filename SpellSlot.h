#pragma once
#include <Windows.h>
#include "SpellInfo.h"
class SpellSlot {
public:
	int GetLevel() {
		return *(int*)((DWORD)this + 0x20);
	}

	float GetTime() {
		return *(float*)((DWORD)this + 0x28);
	}

	float GetCD() {
		return *(float*)((DWORD)this + 0x18);
	}

	SpellData* GetSpellData() {
		auto retaddr = *(DWORD*)(this + 0x124);
		if (retaddr == NULL)
			return NULL;
		auto ret = *(DWORD*)(retaddr + 0x38);
		if (ret == NULL)
			return NULL;
		return (SpellData*)(ret);
	}


};