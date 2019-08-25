#pragma once
#include <Windows.h>
#include "Offsets.h"
#include "Vector.h"
#include "Utils.h"

class Missile {
public:
	Vector GetSpellStartPos() {
		return *(Vector*)((DWORD)this + missileStartPos);
	}

	Vector GetSpellEndPos() {
		return *(Vector*)((DWORD)this + missileEndPos);
	}
	char* GetName() {
		return GetStr((DWORD)this + oObjName);
	}
};