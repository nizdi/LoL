#pragma once
#include "Offsets.h"
#include <Windows.h>
#include "Vector.h"
#include <vector>
#include "Utils.h"
#include "guicon.h"
class AIManager
{
public:
	union {
		DEFINE_MEMBER_N(DWORD pStart, O_AIMGR_NAVBEGIN);
		DEFINE_MEMBER_N(DWORD pEnd, O_AIMGR_NAVEND);
	};

     Vector GetVelocity() {
		return *(Vector*)((DWORD)this + O_AIMGR_VELOCITY);
	}

	 bool HasNavPath() {
		 return *(BYTE*)((DWORD)this + O_AIMGR_HASNAVPATH) == 1;
	 }

	 bool IsMoving() {
		 return *(bool*)((DWORD)this + O_AIMGR_ISMOVING);
	 }

	std::vector<Vector*> getPathList() {
		std::vector<Vector*> test;
		for (DWORD pBuffPtr = this->pStart; pBuffPtr != this->pEnd; pBuffPtr += 0x8)
		{
			auto pBuff = *(Vector**)pBuffPtr;
			if (!pBuff) continue;
			if (pBuff) {
				Console.print("%f , %f , %f \,n", pBuff->X, pBuff->Y, pBuff->Z);
				test.push_back(pBuff);
			}

		}
		return test;
	}
};

