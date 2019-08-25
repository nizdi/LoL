#pragma once
#include "Utils.h"
#include <stdint.h>
/*class SpellData
{
public:
	char* GetMissileName() {
		return GetStr((DWORD)this + 0x0058);
	}; //0x0058
	char* GetSpellName() {
		return GetStr((DWORD)this + 0x007C);
	}; //0x0058
	char* GetDescription() {
		return GetStr((DWORD)this + 0x0088);
	}; //0x0058

	float GetEffectAmount() {
		return *(float*)((DWORD)this + 0xD0);
	}

	float GetIncreaseDamage() {
		return *(float*)((DWORD)this + 0xEC);
	}

	float GetSpellDuration() {
		return *(float*)((DWORD)this + 0x108);
	}

	float GetRootDuration() {
		return *(float*)((DWORD)this + 0x15C);
	}
	float GetIncreaseDamageBonus() {
		return *(float*)((DWORD)this + 0x178);
	}
	float GetCoefficient() {
		return *(float*)((DWORD)this + 0x200);
	}
	float GetCoefficient2() {
		return *(float*)((DWORD)this + 0x204);
	}
	int GetMaxHighlightTargets() {
		return *(int*)((DWORD)this + 0x208);
	}

	float GetCooldownTime() {
		return *(float*)((DWORD)this + 0x280);
	}

	float GetDelayCastOffsetPercent() {
		return *(float*)((DWORD)this + 0x29C);
	}

	float GetDelayTotalTimePercent() {
		return *(float*)((DWORD)this + 0x2A0);
	}

	int GetMaxAmmo() {
		return *(int*)((DWORD)this + 0x31C);
	}
	int GetAmmoUsed() {
		return *(int*)((DWORD)this + 0x338);
	}

	float GetAmmoRechargeTime() {
		return *(float*)((DWORD)this + 0x354);
	}

	float GetMissileSpeed() {
		return *(float*)((DWORD)this + 0x450);
	}
};*/

class SpellBooleans //
{
public:
	bool AmmoNotAffectedByCDR; //0x0000
	bool AmmoNotAffectedByCDR2; //0x0001
	bool CostAlwaysShownInUI; //0x0002
	bool CannotBeSuppressed; //0x0003
	bool CanCastWhileDisabled; //0x0004
	bool CanCastOrQueueWhileCasting; //0x0005
	bool CanOnlyCastWhileDisabled; //0x0006
	bool CantCancelWhileWindingUp; //0x0007
	bool CantCancelWhileChanneling; //0x0008
	bool CantCastWhileRooted; //0x0009
	bool ApplyAttackDamage; //0x000A
	bool ApplyAttackEffect; //0x000B
	bool ApplyMaterialOnHitSound; //0x000C
	bool DoesntBreakChannels; //0x000D
	bool BelongsToAvatar; //0x000E
	bool IsDisabledWhileDead; //0x000F
	bool CanOnlyCastWhileDead; //0x0010
	bool CursorChangesInGrass; //0x0011
	bool CursorChangesInTerrain; //0x0012
	bool LineMissileEndsAtTargetPoint; //0x0013
	bool SpellRevealsChampion; //0x0014
	bool LineMissileTrackUnitsAndContinues; //0x0015
	bool UseMinimapTargeting; //0x0016
	bool CastRangeUseBoundingBoxes; //0x0017
	bool MinimapIconRotation; //0x0018
	bool UseChargeChanneling; //0x0019
	bool UseChargeTargeting; //0x001A
	bool CanMoveWhileChanneling; //0x001B
	bool DisableCastBar; //0x001C
	bool ShowChannelBar; //0x001D
	bool AlwaysSnapFacing; //0x001E
	bool UseAnimatorFramerate; //0x001F
	bool HaveHitEffect; //0x0020
	bool HaveHitBone; //0x0021
	bool HaveAfterEffect; //0x0022
	bool HavePointEffect; //0x0023
	bool IsToggleSpell; //0x0024
	bool LineMissileBounces; //0x0025
	bool LineMissileUsesAccelerationForBounce; //0x0026
	bool MissileFollowsTerrainHeight; //0x0027
	bool DoNotNeedToFaceTarget; //0x0028
	bool NoWinddownIfCancelled; //0x0029
	bool IgnoreRangeCheck; //0x002A
	bool OrientRadiusTextureFromPlayer; //0x002B
	bool UseAutoattackCastTime; //0x002C
	bool IgnoreAnimContinueUntilCastFrame; //0x002D
	bool HideRangeIndicatorWhenCasting; //0x002E
	bool UpdateRotationWhenCasting; //0x002F
	bool ConsideredAsAutoAttack; //0x0030
	bool MinimapIconDisplayFlag; //0x0031
}; //Size: 0x0044

class SpellData
{
public:
	char pad_0000[88]; //0x0000
	char* MissileName; //0x0058
	char pad_005C[32]; //0x005C
	char* SpellName; //0x007C
	char pad_0080[8]; //0x0080
	char* Description; //0x0088
	char pad_008C[68]; //0x008C
	FLOAT EffectAmount[7]; //0x00D0
	FLOAT IncreaseDamage[7]; //0x00EC
	FLOAT SpellDuration[7]; //0x0108
	char pad_0124[56]; //0x0124
	FLOAT RootDuration[7]; //0x015C ex : Caitlyn trap root for 1.5 sec
	FLOAT IncreaseDamageBonus[7]; //0x0178
	char pad_0194[108]; //0x0194
	float Coefficient; //0x0200
	float Coefficient2; //0x0204
	int32_t MaxHighlightTargets; //0x0208
	char pad_020C[70]; //0x020C
	float castTime; // 0x027C
	FLOAT CooldownTime[7]; //0x0280
	float DelayCastOffsetPercent; //0x029C
	float DelayTotalTimePercent; //0x02A0
	char pad_02A4[120]; //0x02A4
	INT MaxAmmo[7]; //0x031C
	INT AmmoUsed[7]; //0x0338
	FLOAT AmmoRechargeTime[7]; //0x0354

	SpellBooleans spellBooleans; //0x0370

	FLOAT CastRange[7]; //0x03B4
	char pad_03D0[28]; //0x03D0
	FLOAT CastRadius[7]; //0x03EC
	FLOAT CastRadiusSecondary[1]; //0x0408
	float CastConeAngle; //0x040C
	float CastConeDistance; //0x0410
	float CastTargetAdditionalUnitsRadius; //0x0414
	float BounceRadius; //0x0418
	float MissileGravity; //0x041C
	float MissileTargetHeightAugment; //0x0420
	float LineMissileTargetHeightAugment; //0x0424
	float LineMissileDelayDestroyAtEndSeconds; //0x0428
	float LineMissileTimePulseBetweenCollisionSpellHits; //0x042C
	float LuaOnMissileUpdateDistanceInterval; //0x0430
	char pad_0434[28]; //0x0434
	float MissileSpeed; //0x0450
	float MissileAccel; //0x0454
	float MissileMaxSpeed; //0x0458
	float MissileMinSpeed; //0x045C
	char pad_0460[192]; //0x0460
	FLOAT ManaCost[7]; //0x0520
	char pad_053C[296]; //0x053C
	int32_t CastType; //0x0664
	char pad_0668[84]; //0x0668
}; //Size: 0x06BC

