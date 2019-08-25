#pragma once
#include <time.h>
#include "stdafx.h"
#include "guicon.h"
#include "Engine.h"
#include "Hooks.h"
#include "detours.h"
#include "Missile.h"
#include <vector>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string>
#include <math.h>
#include "Prediction.h"
#include <d3d9.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
using namespace std;
class Orbwalker
{
public:
	// Function to convert hexadecimal to decimal 
	int hexadecimalToDecimal(char hexVal[])
	{
		int len = strlen(hexVal);

		// Initializing base value to 1, i.e 16^0 
int base = 1;

int dec_val = 0;

// Extracting characters as digits from last character 
for (int i = len - 1; i >= 0; i--)
{
	// if character lies in '0'-'9', converting  
	// it to integral 0-9 by subtracting 48 from 
	// ASCII value. 
	if (hexVal[i] >= '0' && hexVal[i] <= '9')
	{
		dec_val += (hexVal[i] - 48)*base;

		// incrementing base by power 
		base = base * 16;
	}

	// if character lies in 'A'-'F' , converting  
	// it to integral 10 - 15 by subtracting 55  
	// from ASCII value 
	else if (hexVal[i] >= 'A' && hexVal[i] <= 'F')
	{
		dec_val += (hexVal[i] - 55)*base;

		// incrementing base by power 
		base = base * 16;
	}
}

return dec_val;
	}

	bool ObjectAttacking(CObject* obj) {
		if (obj->GetSpellBook()->GetActiveSpellEntry()) {
			return obj->GetSpellBook()->GetActiveSpellEntry()->isAutoAttack();
		}
	}

	CObjectManager* ObjManager;


	bool InAutoAttackRange(CObject* target)
	{
		Engine* en = new Engine();
		float myRange = me->GetAttackRange() + me->GetBoundingRadius() + target->GetBoundingRadius();
		
		if (this->isPartOf("Caitlyn", me->GetChampionName()))
		{
			if (target->GetBuffMgr())
			{
				if (target->GetBuffMgr()->GetBuffEntryByName("caitlynyordletrapinternal"))
					myRange += 650;
			}
		}
		float dist = (me->GetPos().X - target->GetPos().X)*(me->GetPos().X - target->GetPos().X) + (me->GetPos().Z - target->GetPos().Z)*(me->GetPos().Z - target->GetPos().Z);
		return (dist <= myRange * myRange);
	}

	std::vector<CObject*> getAttackableUnitInRange() {
		std::vector<CObject*> objets;
		if (ObjManager) {
			for (int i = 0; i < 10000; i++) {

				CObject* obj = Engine::GetObjectByID(i);
				if (obj) {
					if (obj->IsHero() || obj->IsMinion() || obj->IsTurret()) {
						if (obj->IsAlive() && obj->GetTeam() != me->GetTeam() && obj->IsTargetable() && obj->GetMaxHealth() < 15000.0f) {
							if (InAutoAttackRange(obj)) {
								objets.push_back(obj);
							}
						}
					}

				}
			}
		}
		return objets;
	};

	std::vector<CObject*> getAttackableUnitInRange(float range) {
		std::vector<CObject*> objets;
		if (ObjManager) {
			for (int i = 0; i < 10000; i++) {

				CObject* obj = Engine::GetObjectByID(i);
				if (obj) {
					if (obj->IsHero() || obj->IsMinion() || obj->IsTurret()) {
						if (obj->IsAlive() && obj->GetTeam() != me->GetTeam() && obj->IsTargetable() && obj->GetMaxHealth() < 15000.0f) {
							float myRange = range + me->GetBoundingRadius() + obj->GetBoundingRadius();
							float dist = (me->GetPos().X - obj->GetPos().X)*(me->GetPos().X - obj->GetPos().X) + (me->GetPos().Z - obj->GetPos().Z)*(me->GetPos().Z - obj->GetPos().Z);
							if (dist <= myRange * myRange) {
								objets.push_back(obj);
							}
						}
					}

				}
			}
		}
		return objets;
	};
	float missileSpeed = 1800.0f;
	double ClickerDelay = 0.1;
	float movetimer = 0;
	float attacktimer = 0;

	void ResetMoveTimer()
	{
		movetimer = Engine::GetGameTime();
	};
	void ResetAttackTimer(float t)
	{
		attacktimer = Engine::GetGameTime() + t;
	};

	double CalcAttackDelay()
	{
		return (Engine::GetGameTime() - attacktimer);
	};
	double CalcAttackTime()
	{
		return Functions.GetAttackDelay(me);
	};
	double CalcAttackCast()
	{
		return Functions.GetAttackCastDelay(me);

	};

	bool AttackReady()
	{
		return Engine::GetGameTime() + 0.055 >= attacktimer + CalcAttackTime();
	};


	std::vector<Missile*> GetMissile() {
		std::vector<Missile*> objets;
		if (ObjManager) {
			for (int i = 0; i < 10000; i++) {
				CObject* obj = Engine::GetObjectByID(i);
				
				if (obj) {
					if (Functions.IsMissile(obj)) {
						//Console.print("%s", obj->GetName());
						objets.push_back((Missile*)obj);
					}
				}
			}
		}
		return objets;
	}

	bool isLastHittable(CObject* minion) {
		float adMultiplier = 0.0f;
		float armor = minion->GetArmor();

		if (armor > 0)
			adMultiplier = 100 / (100 + armor);
		else
			adMultiplier = 2 - (100 / (100 - armor));

		return (minion->GetHealth() - (adMultiplier*me->GetTotalAttackDamage()) <= 0);
	};

	bool KSable(CObject* minion, float damage, int type) {
		if (type == 1) {
			float adMultiplier = 0.0f;
			float armor = minion->GetArmor();

			if (armor > 0)
				adMultiplier = 100 / (100 + armor);
			else
				adMultiplier = 2 - (100 / (100 - armor));

			return (minion->GetHealth() - damage <= 0);
		}
		else {
			float adMultiplier = 0.0f;
			float armor = 100.0f;

			if (armor > 0)
				adMultiplier = 100 / (100 + armor);
			else
				adMultiplier = 2 - (100 / (100 - armor));

			return (minion->GetHealth() - damage <= 0);
		}
	}

	std::vector<CObject*> GetHeroes() {
		std::vector<CObject*> objets;
		for (CObject* obj : getAttackableUnitInRange()) {
			if (Functions.IsHero(obj)) {
				objets.push_back(obj);
			}
		}
		return objets;
	};

	std::vector<CObject*> GetHeroes(float range) {
		std::vector<CObject*> objets;
		for (CObject* obj : getAttackableUnitInRange(range)) {
			if (Functions.IsHero(obj)) {
				objets.push_back(obj);
			}
		}
		return objets;
	};

	float getReductedPriority(CObject* target) {
		std::map<string, int> Priorities;
		Priorities["Aatrox"] = 2;
		Priorities["Ahri"] = 4;
		Priorities["Akali"] = 3;
		Priorities["Alistar"] = 1;
		Priorities["Amumu"] = 1;
		Priorities["Anivia"] = 4;
		Priorities["Annie"] = 4;
		Priorities["Ashe"] = 4;
		Priorities["AurelionSol"] = 4;
		Priorities["Azir"] = 4;
		Priorities["Bard"] = 1;
		Priorities["Blitzcrank"] = 1;
		Priorities["Brand"] = 4;
		Priorities["Braum"] = 1;
		Priorities["Caitlyn"] = 4;
		Priorities["Cassiopeia"] = 4;
		Priorities["Chogath"] = 2;
		Priorities["Corki"] = 4;
		Priorities["Darius"] = 2;
		Priorities["Diana"] = 3;
		Priorities["Draven"] = 4;
		Priorities["DrMundo"] = 1;
		Priorities["Ekko"] = 4;
		Priorities["Elise"] = 2;
		Priorities["Evelynn"] = 2;
		Priorities["Ezreal"] = 4;
		Priorities["Fiddlesticks"] = 3;
		Priorities["Fiora"] = 3;
		Priorities["Fizz"] = 3;
		Priorities["Galio"] = 2;
		Priorities["Gangplank"] = 2;
		Priorities["Garen"] = 1;
		Priorities["Gnar"] = 1;
		Priorities["Gragas"] = 2;
		Priorities["Graves"] = 4;
		Priorities["Hecarim"] = 1;
		Priorities["Heimerdinger"] = 3;
		Priorities["Illaoi"] = 2;
		Priorities["Irelia"] = 2;
		Priorities["Ivern"] = 2;
		Priorities["Janna"] = 1;
		Priorities["JarvanIV"] = 1;
		Priorities["Jax"] = 2;
		Priorities["Jayce"] = 3;
		Priorities["Jhin"] = 4;
		Priorities["Jinx"] = 4;
		Priorities["Kalista"] = 4;
		Priorities["Karma"] = 4;
		Priorities["Karthus"] = 4;
		Priorities["Kassadin"] = 3;
		Priorities["Katarina"] = 4;
		Priorities["Kayle"] = 3;
		Priorities["Kennen"] = 4;
		Priorities["Khazix"] = 3;
		Priorities["Kindred"] = 4;
		Priorities["Kled"] = 2;
		Priorities["KogMaw"] = 4;
		Priorities["Leblanc"] = 4;
		Priorities["LeeSin"] = 2;
		Priorities["Leona"] = 1;
		Priorities["Lissandra"] = 3;
		Priorities["Lucian"] = 4;
		Priorities["Lulu"] = 1;
		Priorities["Lux"] = 4;
		Priorities["Malphite"] = 1;
		Priorities["Malzahar"] = 4;
		Priorities["Maokai"] = 2;
		Priorities["MasterYi"] = 4;
		Priorities["MissFortune"] = 4;
		Priorities["MonkeyKing"] = 1;
		Priorities["Mordekaiser"] = 3;
		Priorities["Morgana"] = 2;
		Priorities["Nami"] = 1;
		Priorities["Nasus"] = 1;
		Priorities["Nautilus"] = 1;
		Priorities["Nidalee"] = 3;
		Priorities["Nocturne"] = 2;
		Priorities["Nunu"] = 1;
		Priorities["Olaf"] = 1;
		Priorities["Orianna"] = 4;
		Priorities["Pantheon"] = 2;
		Priorities["Poppy"] = 2;
		Priorities["Quinn"] = 4;
		Priorities["Rammus"] = 1;
		Priorities["RekSai"] = 2;
		Priorities["Renekton"] = 1;
		Priorities["Rengar"] = 2;
		Priorities["Riven"] = 3;
		Priorities["Rumble"] = 2;
		Priorities["Ryze"] = 2;
		Priorities["Sejuani"] = 1;
		Priorities["Shaco"] = 3;
		Priorities["Shen"] = 1;
		Priorities["Shyvana"] = 1;
		Priorities["Singed"] = 1;
		Priorities["Sion"] = 1;
		Priorities["Sivir"] = 4;
		Priorities["Skarner"] = 1;
		Priorities["Sona"] = 1;
		Priorities["Soraka"] = 4;
		Priorities["Swain"] = 2;
		Priorities["Syndra"] = 4;
		Priorities["TahmKench"] = 1;
		Priorities["Taliyah"] = 3;
		Priorities["Talon"] = 4;
		Priorities["Taric"] = 1;
		Priorities["Teemo"] = 4;
		Priorities["Thresh"] = 1;
		Priorities["Tristana"] = 4;
		Priorities["Trundle"] = 2;
		Priorities["Tryndamere"] = 2;
		Priorities["TwistedFate"] = 4;
		Priorities["Twitch"] = 4;
		Priorities["Udyr"] = 2;
		Priorities["Urgot"] = 2;
		Priorities["Varus"] = 4;
		Priorities["Vayne"] = 4;
		Priorities["Veigar"] = 4;
		Priorities["Velkoz"] = 4;
		Priorities["Vi"] = 2;
		Priorities["Viktor"] = 4;
		Priorities["Vladimir"] = 3;
		Priorities["Volibear"] = 1;
		Priorities["Warwick"] = 1;
		Priorities["Xerath"] = 4;
		Priorities["XinZhao"] = 2;
		Priorities["Yasuo"] = 3;
		Priorities["Yorick"] = 1;
		Priorities["Zac"] = 1;
		Priorities["Zed"] = 4;
		Priorities["Ziggs"] = 4;
		Priorities["Zilean"] = 3;
		Priorities["Zyra"] = 3;
		Priorities["Sylas"] = 3;
		if (Priorities[target->GetChampionName()]) {
			if (Priorities[target->GetChampionName()] == 5)
				return 2.5;
			else if (Priorities[target->GetChampionName()] == 4)
				return 2;
			else if(Priorities[target->GetChampionName()] == 3)
				return 1.75;
			else if(Priorities[target->GetChampionName()] == 2)
				return 1.5;
			else if(Priorities[target->GetChampionName()] == 1)
				return 1;
		}
		else {
			return 1;
		}
	}

	float calculateDamage(CObject* from, CObject* to, float rawDamage) {
		float adMultiplier = 0.0f;
		float armor = to->GetArmor();

		if (armor > 0)
			adMultiplier = 100 / (100 + armor);
		else
			adMultiplier = 2 - (100 / (100 - armor));

		return ((adMultiplier*from->GetTotalAttackDamage()));

	}

	bool isUndying(CObject* target) {

	}

	CObject* GetTarget(std::vector<CObject*> targets) {
		CObject* selected = nullptr;
		float max = 0;
		if (targets.size() > 0) {
			for (CObject* target : targets) {
				if ((getReductedPriority(target)*calculateDamage(me, target, me->GetTotalAttackDamage()) / (target->GetHealth()*0.8f)) > max /*&& !isUndying(target)*/) {
					//Console.print("Nom: %s \n", target->GetName());
					max = (getReductedPriority(target)*calculateDamage(me, target, me->GetTotalAttackDamage()) / target->GetHealth());
					selected = target;
				}
			}

		}
		return selected;
	};

	bool isPartOf(char* w1, char* w2)
	{
		int i = 0;
		int j = 0;


		while (w1[i] != '\0') {
			if (w1[i] == w2[j])
			{
				int init = i;
				while (w1[i] == w2[j] && w2[j] != '\0')
				{
					j++;
					i++;
				}
				if (w2[j] == '\0') {
					return true;
				}
				j = 0;
			}
			i++;
		}
		return false;
	}

	float LaneClearPred(CObject* minion, float time) {
		float hpPred = 0;
		if (ObjManager) {
			for (int i = 0; i < 10000; i++) {

				CObject* obj = Engine::GetObjectByID(i);
				if (obj) {
					if (obj->IsMinion()) {
						if (obj->GetSpellBook()) {
							if (obj->GetSpellBook()->GetActiveSpellEntry()) {
								if (obj->GetSpellBook()->GetActiveSpellEntry()->targetID() == minion->GetNetworkID() && obj->GetSpellBook()->GetActiveSpellEntry()->isAutoAttack()) {
									int n = 0;
									float startAttack = Engine::GetGameTime();
									float endAttack = Engine::GetGameTime() + time;
									while (startAttack < endAttack) {
										float MissileSpeed = obj->GetSpellBook()->GetActiveSpellEntry()->GetSpellData()->MissileSpeed;
										if (startAttack >= Engine::GetGameTime() && (startAttack + MAX((obj->GetSpellBook()->GetActiveSpellEntry()->GetStartPos().DistTo(obj->GetSpellBook()->GetActiveSpellEntry()->GetEndPos()) - obj->GetBoundingRadius()), 0) / MissileSpeed + Functions.GetAttackCastDelay(obj) < endAttack)){

											n++;
									}
										startAttack += Functions.GetAttackCastDelay(obj);
		

								}
									hpPred += n* obj->GetTotalAttackDamage();
							}
						}

					}
				}

			}
		}
		return hpPred;
	}
	}

	float GetPredictedDamages(CObject* minion, float time){
		float hpPred = 0;
		if (ObjManager) {
			for (int i = 0; i < 10000; i++) {

				CObject* obj = Engine::GetObjectByID(i);
				if (obj) {
					if (obj->IsMinion()) {
						if (obj->GetSpellBook()) {
							if (obj->GetSpellBook()->GetActiveSpellEntry()) {
								if (obj->GetSpellBook()->GetActiveSpellEntry()->targetID() == minion->GetNetworkID() && obj->GetSpellBook()->GetActiveSpellEntry()->isAutoAttack()) {

										float MissileSpeed = obj->GetSpellBook()->GetActiveSpellEntry()->GetSpellData()->MissileSpeed;
										float timeImpact = MAX((obj->GetSpellBook()->GetActiveSpellEntry()->GetStartPos().DistTo(obj->GetSpellBook()->GetActiveSpellEntry()->GetEndPos()) - obj->GetBoundingRadius()), 0) / MissileSpeed + Functions.GetAttackCastDelay(obj);
										if (timeImpact < time) {
											hpPred += obj->GetTotalAttackDamage();
										
									}


								}
							}
						}

				}
					}

				}
			}
			return hpPred;
		}

	CObject* GetLastHittableMinion() {		
		
		std::vector<CObject*> objectsInRange = this->getAttackableUnitInRange();
		for (CObject* minion : objectsInRange) {
			if (minion->IsMinion()) {
				float hPred = minion->GetHealth();

				float lasthittime = MAX((me->GetPos().DistTo(minion->GetPos()) - me->GetBoundingRadius()), 0) / this->missileSpeed + CalcAttackCast() - 0.1f;
				hPred -= KSable(minion, GetPredictedDamages(minion, lasthittime), 1);


				if (hPred <= 0 || isLastHittable(minion)) {
					return minion;
				}
			}

		}
		return nullptr;
	}

	bool ShouldWait() {
		std::vector<CObject*> objectsInRange = this->getAttackableUnitInRange();
		for (CObject* minion : objectsInRange) {
			if (minion->IsMinion()) {
				float hPred = minion->GetHealth();

				float time = Functions.GetAttackDelay(me);
				hPred -= KSable(minion, this->LaneClearPred(minion, time), 1);


				if (hPred <= KSable(minion, me->GetTotalAttackDamage(), 1)) {
					return true;
				}
			}

		}
		return false;
	}

	float resetAAtimer = 0.0f;
	float castTimeAAreset = 0.0f;
	bool ResetAutoAttackReady() {
		if (Engine::GetGameTime() >= resetAAtimer + castTimeAAreset) {
			return true;
		}
		return false;
	}

	void Orbwalk(CObject* Target, bool hasTarget)
	{

		if (isPartOf("Vayne", me->GetChampionName())) {
			if (me->GetSpellBook()->GetActiveSpellEntry()) {
				if (isPartOf(me->GetSpellBook()->GetActiveSpellEntry()->GetSpellData()->SpellName, "VayneTumble")) {
					this->ResetAttackTimer(0.0f);
				}
			}
		}
		if (isPartOf("Lucian", me->GetChampionName())) {
			if (me->GetSpellBook()->GetActiveSpellEntry()) {
				if (isPartOf(me->GetSpellBook()->GetActiveSpellEntry()->GetSpellData()->SpellName, "LucianQ")) {
					this->ResetAttackTimer(0.0f);
				}
			}
		}
		if (isPartOf("Sivir", me->GetChampionName())) {
			if (Engine::GetGameTime()-me->GetSpellBook()->GetSpellSlotByID(1)->GetTime()==0.0f) {
					this->ResetAttackTimer(0.0f);
			}
		}

		/*

		Console.print("AttackTimer : %f, AttackReady : %i\n", this->attacktimer, this->AttackReady());
		if (isPartOf("Lucian", me->GetChampionName())) {
			if (me->GetSpellBook()->GetSpellSlotByID(2)->GetTime() - Engine::GetGameTime() == 0.0f) {
				resetAAtimer = Engine::GetGameTime();
			}
		}*/

		if (!hasTarget) {
			Engine::MoveTo(new Vector(Engine::GetMouseWorldPosition()));

		}
		else {

			if (AttackReady() && getAttackableUnitInRange().size() > 0)
			{
					
					Engine::Attack(Target, 1);
					if (me->GetSpellBook()->GetActiveSpellEntry()) {
						if (me->GetSpellBook()->GetActiveSpellEntry()->isAutoAttack()) {
							this->missileSpeed = me->GetSpellBook()->GetActiveSpellEntry()->GetSpellData()->MissileSpeed;
							this->ResetAttackTimer(0.0f);
						}

					}
					
		
					
			}
		    if (!AttackReady() && getAttackableUnitInRange().size() > 0)
			{
				if (CalcAttackCast() < CalcAttackDelay() + 0.015)
				{
					//Console.print("AttackDelay: %f |AttackCastDelay: %f | Engine::GetGameTime(): %f\n", CalcAttackCast(), CalcAttackDelay(), CalcAttackCast() + 0.2f);
					Engine::MoveTo(new Vector(Engine::GetMouseWorldPosition()));
					ResetMoveTimer();
				}
			}
			if (getAttackableUnitInRange().size() < 1)
			{
				Engine::MoveTo(new Vector(Engine::GetMouseWorldPosition()));
				ResetMoveTimer();
			}
		}
	};



	CObject* getLaneClearMinion() {
		std::vector<CObject*> objectsInRange = this->getAttackableUnitInRange();
		for (CObject* minion : objectsInRange) {
			if (minion->IsMinion()) {
				float hPred = minion->GetHealth();

				float time = Functions.GetAttackDelay(me);
				hPred -= KSable(minion, this->LaneClearPred(minion, time), 1);


				if (hPred >= 2 * KSable(minion, me->GetTotalAttackDamage(), 1)) {
					return minion;
				}
			}

		}
		return nullptr;
	}
	void LaneClear() {
		if (this->GetLastHittableMinion()) {
			Orbwalk(this->GetLastHittableMinion(), 1);
		}
		else if (this->getLaneClearMinion()) {
			Orbwalk(this->getLaneClearMinion(), 1);
		}

		
		else if (GetTarget(GetHeroes()) && !this->ShouldWait()) {
			Orbwalk(GetTarget(GetHeroes()), 1);
		}
		else {
		Orbwalk(me, 0);
		}

	}

	void LastHit() {
		if (GetLastHittableMinion()) {
			Orbwalk(GetLastHittableMinion(), 1);
		}
		else if (GetTarget(GetHeroes())) {
			this->Harass();
			Orbwalk(GetTarget(GetHeroes()), 1);
		}
		else {
			Orbwalk(me, 0);
		}

	}

	void Combo() {
		Engine* engine = new Engine();
		if (me->GetBuffMgr()) {
			if (me->GetBuffMgr()->GetBuffEntryByName("kalistaexpungemarker")) {
				CObject* p = me;
			}
		}
	if (GetTarget(GetHeroes())) {

			/*if (me->GetSpellBook().GetSpellSlotByID(0)->GetTime() == 0) {
				me->CastSpellTarget(GetTarget(GetHeroes()), 0);
			}*/
			//Console.print("%s", me->GetChampionName());
			//TRISTANA COMBO

				if (isPartOf("Tristana", me->GetChampionName())) {
					if (Engine::IsReady(0, me))
						Engine::CastSpellSelf(0);

					if (Engine::IsReady(2, me) && !AttackReady())
						Engine::CastSpellTargetted(2, GetTarget(GetHeroes()));

					if (GetTarget(GetHeroes())->GetHealth() / GetTarget(GetHeroes())->GetMaxHealth() < 0.1f && (Engine::IsReady(3, me))) {
						if (me->GetSpellBook()->GetSpellSlotByID(3)->GetLevel() == 1 && KSable(GetTarget(GetHeroes()), 300, 0)) {
							Engine::CastSpellTargetted(3, GetTarget(GetHeroes()));
						}
						else if (me->GetSpellBook()->GetSpellSlotByID(3)->GetLevel() == 2 && KSable(GetTarget(GetHeroes()), 400, 0)) {
							Engine::CastSpellTargetted(3, GetTarget(GetHeroes()));
						}
						else if (me->GetSpellBook()->GetSpellSlotByID(3)->GetLevel() == 3 && KSable(GetTarget(GetHeroes()), 500, 0)) {
							Engine::CastSpellTargetted(3, GetTarget(GetHeroes()));
						}
					}

				}
				else if (isPartOf("Twitch", me->GetChampionName())) {

				}
				else if (isPartOf("Ashe", me->GetChampionName())) {
					if (Engine::IsReady(1, me))
						Engine::CastSpellPos(1, GetTarget(GetHeroes())->GetPos());
				}
				else if (isPartOf("Kayle", me->GetChampionName())) {
					if (Engine::IsReady(0, me) &&!this->AttackReady())
						Engine::CastSpellTargetted(0, GetTarget(GetHeroes()));
					if (Engine::IsReady(2, me))
						Engine::CastSpellSelf(2);
				}
				else if (isPartOf("Quinn", me->GetChampionName()) && !this->AttackReady()) {
					if (Engine::IsReady(2, me))
						Engine::CastSpellTargetted(2, GetTarget(GetHeroes()));
				}
				else if (isPartOf("MissFortune", me->GetChampionName())) {
					if (Engine::IsReady(0, me))
						Engine::CastSpellTargetted(0, GetTarget(GetHeroes()));
					if (Engine::IsReady(1, me))
						Engine::CastSpellSelf(1);
				}
				else if (isPartOf("Ezreal", me->GetChampionName())) {

					auto pred = new Prediction(new LinePrediction());
					if (!pred->IsCollisioned(Prediction::CollisionType::Minion, GetTarget(GetHeroes())->GetPos(), 70))
					{
						Vector Predict = pred->LinePred->Predict(GetTarget(GetHeroes()), 1150, 2200, 0.1f);
						if (Predict.X != 0 && Predict.Y != 0 && Predict.Z != 0) {
							if (Engine::IsReady(0, me))
								Engine::CastSpellPos(0, Predict);
						}

					}



				}
				else if (isPartOf("Kalista", me->GetChampionName())) {

					auto pred = new Prediction(new LinePrediction());
					if (!pred->IsCollisioned(Prediction::CollisionType::Minion, GetTarget(GetHeroes())->GetPos(), 70))
					{
						Vector Predict = pred->LinePred->Predict(GetTarget(GetHeroes()), 1150, 2100, 0.1f);
						if (Predict.X != 0 && Predict.Y != 0 && Predict.Z != 0) {
							if (Engine::IsReady(0, me))
								Engine::CastSpellPos(0, Predict);
						}

					}



				}
				else if (isPartOf("Caitlyn", me->GetChampionName())) {


				}
				else if (isPartOf("Xayah", me->GetChampionName())) {

					auto pred = new Prediction(new LinePrediction());


					Vector Predict = pred->LinePred->Predict(GetTarget(GetHeroes()), 1200 + me->GetBoundingRadius(), 2200, 0.1f);
					if (Predict.X != 0 && Predict.Y != 0 && Predict.Z != 0) {
						if (Engine::IsReady(0, me) && !this->AttackReady())
							Engine::CastSpellPos(0, Predict);
					}
					if (Engine::IsReady(1, me))
						Engine::CastSpellSelf(1);
				}
				else if (isPartOf("Vayne", me->GetChampionName())) {

					this->castTimeAAreset = 0.225f;
					if (Engine::IsReady(2, me)) {

						CObject* target = GetTarget(GetHeroes());
						float bRange = me->GetAttackRange() / 3;
						Vector test = target->GetPos() - (target->GetPos() - me->GetPos()) * (500.0f/me->GetPos().DistTo(target->GetPos()));
						Vector maxERange = Vector(-test.X, -test.Y, -test.Z);
						/*if (Engine::IsWall(maxERange)) {
							Engine::CastSpellTargetted(2, target);

						}*/
					}
				}
				else if (isPartOf("Lucian", me->GetChampionName())) {
					if (me->GetBuffMgr()) {
						if (!me->GetBuffMgr()->GetBuffEntryByName("lucianpassivebuff")) {
							this->castTimeAAreset = 0.1f;
							if (Engine::IsReady(0, me))
								Engine::CastSpellTargetted(0, GetTarget(GetHeroes()));
							auto pred = new Prediction(new LinePrediction());
							if (!pred->IsCollisioned(Prediction::CollisionType::Minion, GetTarget(GetHeroes())->GetPos(), 70))
							{
								Vector Predict = pred->LinePred->Predict(GetTarget(GetHeroes()), 900, me->GetSpellBook()->GetSpellSlotByID(1)->GetSpellData()->MissileSpeed, 0.25f);
								if (Predict.X != 0 && Predict.Y != 0 && Predict.Z != 0) {
									if (Engine::IsReady(1, me))
										Engine::CastSpellPos(1, Predict);
								}

							}
						}
					}

				}
				else if (isPartOf("Teemo", me->GetChampionName())) {
				if (Engine::IsReady(0, me))
					Engine::CastSpellTargetted(0, GetTarget(GetHeroes()));
				}
				else if (isPartOf("Sivir", me->GetChampionName())) {
				if (Engine::IsReady(1, me) && !this->AttackReady())
					Engine::CastSpellSelf(1);
				}
				else if (isPartOf("Cassiopeia", me->GetChampionName())) {
					auto pred = new Prediction(new LinePrediction());
					CObject* o = (GetTarget(GetHeroes(850.0f)));
					if (o->GetBuffMgr()) {
						if (o->GetBuffMgr()->GetBuffEntryByName("cassiopeiaqdebuff") || o->GetBuffMgr()->GetBuffEntryByName("cassiopeiawpoison")) {
							if (Engine::IsReady(2, me)) {
								Engine::CastSpellTargetted(2, o);
							}
						}
						else {
							if (Engine::IsReady(0, me)) {
								Vector Predict = pred->LinePred->Calculate(GetTarget(GetHeroes()), 850 + GetTarget(GetHeroes())->GetBoundingRadius(), 10000000000000.0f, 0.55f);
								Engine::CastSpellPos(0, Predict);
							}
						}

					}
				}
			Orbwalk(GetTarget(GetHeroes()), 1);
		}
		else {
			Orbwalk(me, 0);
		}
		
	}



	void Poppy() {
					if (!strcmp(me->GetChampionName(), "Poppy")) {
						if (GetTarget(GetHeroes(475.0f))) {
							if (Engine::IsReady(2, me)) {

								CObject* target = GetTarget(GetHeroes(475.0f));
									Vector test = target->GetPos() - (target->GetPos() - me->GetPos()) * (525.0f / me->GetPos().DistTo(target->GetPos()));
									Vector maxERange = Vector(-test.X, -test.Y, -test.Z);
									/*if (Engine::IsWall(maxERange)) {
										Engine::CastSpellTargetted(2, target);

									}*/
							}
						}


				}
	}

	void Harass() {
		if (isPartOf("Cassiopeia", me->GetChampionName()) && me->GetMana()/me->GetMaxMana()>0.25f) {
			CObject* o = GetTarget(GetHeroes(850.0f));
			if (o->GetAIManager()) {
				if (!o->GetAIManager()->IsMoving()) {
					if (Engine::IsReady(0, me)) {
						Engine::CastSpellPos(0, o->GetPos());
					}
				}
			}
		}
	};

	float damageKalistaE(int buffCount) {
		float damageE = 0.0f;
		switch (me->GetSpellBook()->GetSpellSlotByID(2)->GetLevel()) {
		case 1:
			damageE = 20 + 0.6f* me->GetTotalAttackDamage() + (buffCount - 1) * (10 + 0.2f*me->GetTotalAttackDamage());
			break;
		case 2:
			damageE = 30 + 0.6f* me->GetTotalAttackDamage() + (buffCount - 1) * (14 + 0.2375f*me->GetTotalAttackDamage());
			break;
		case 3:
			damageE = 40 + 0.6f* me->GetTotalAttackDamage() + (buffCount - 1) * (19 + 0.275f*me->GetTotalAttackDamage());
			break;
		case 4:
			damageE = 50 + 0.6f* me->GetTotalAttackDamage() + (buffCount - 1) * (25 + 0.3125f*me->GetTotalAttackDamage());
			break;
		case 5:
			damageE = 60 + 0.6f* me->GetTotalAttackDamage() + (buffCount - 1) * (32 + 0.35f*me->GetTotalAttackDamage());
			break;
		}
		return damageE;
	}

	void Kalista() {
		if (!strcmp(me->GetChampionName(), "Kalista")) {
			if (Engine::IsReady(2, me)) {
				std::vector<CObject*> obj = this->getAttackableUnitInRange(1150.0f);
				for (CObject* o : obj) {
					if (o->GetBuffMgr()) {
						if (o->GetBuffMgr()->GetBuffEntryByName("kalistaexpungemarker")) {
							BuffEntry* buff = o->GetBuffMgr()->GetBuffEntryByName("kalistaexpungemarker");
							float damageE = this->damageKalistaE(buff->GetBuffCountInt());

							Console.print("dmg : %f\n", damageE);
							if (this->KSable(o, damageE, 1)) {
								Engine::CastSpellTargetted(2, o);
							}
						}
					}
				}

			}
		}
	}

	void autoQSivir() {
		if (isPartOf("Sivir", me->GetChampionName())) {


			if (Engine::IsReady(0, me)) {
				for (CObject* target : this->GetHeroes(1250.0f)) {

					if (target->GetBuffMgr()) {

						if (target->GetBuffMgr()->IsImmobile(29)) {
							if (Engine::IsReady(0, me))
								Engine::CastSpellPos(1, target->GetPos());
							break;
						}
						else if (target->GetBuffMgr()->IsImmobile(5)) {
							if (Engine::IsReady(0, me))
								Engine::CastSpellPos(1, target->GetPos());
							break;
						}
						else if (target->GetBuffMgr()->IsImmobile(11)) {
							if (Engine::IsReady(0, me))
								Engine::CastSpellPos(1, target->GetPos());
							break;
						}
					}
				}
			}

		}
		if (isPartOf("Jinx", me->GetChampionName())) {
			if (Engine::IsReady(1, me) && !this->AttackReady()) {
				for (CObject* target : this->GetHeroes(1250.0f)) {

					if (target->GetBuffMgr()) {

						if (target->GetBuffMgr()->IsImmobile(29)) {
							if (Engine::IsReady(1, me))
								Engine::CastSpellPos(1, target->GetPos());
							break;
						}
						else if (target->GetBuffMgr()->IsImmobile(5)) {
							if (Engine::IsReady(1, me))
								Engine::CastSpellPos(1, target->GetPos());
							break;
						}
						else if (target->GetBuffMgr()->IsImmobile(11)) {
							if (Engine::IsReady(1, me))
								Engine::CastSpellPos(1, target->GetPos());
							break;
						}
					}
				}
			}
		}
	}
		void autoWCaitlyn() {
			if (isPartOf("Caitlyn", me->GetChampionName())) {


				if (Engine::IsReady(1, me)) {
					for (CObject* target : this->GetHeroes(800.0f)) {

						if (target->GetBuffMgr()) {

							if (target->GetBuffMgr()->IsImmobile(29)) {
								if (Engine::IsReady(1, me))
									Engine::CastSpellPos(1, target->GetPos());
								break;
							}
							else if (target->GetBuffMgr()->IsImmobile(5)) {
								if (Engine::IsReady(1, me))
									Engine::CastSpellPos(1, target->GetPos());
								break;
							}
							else if (target->GetBuffMgr()->IsImmobile(11)) {
								if (Engine::IsReady(1, me)) 
									Engine::CastSpellPos(1, target->GetPos());
									break;
							}
						}
					}
				}

				if (Engine::IsReady(0, me) && !this->AttackReady()) {
					for (CObject* target : this->GetHeroes(1250.0f)) {

						if (target->GetBuffMgr()) {
							if (target->GetBuffMgr()->IsImmobile(29)) {
								if (Engine::IsReady(0, me))
									Engine::CastSpellPos(0, target->GetPos());
							}
							else if (target->GetBuffMgr()->IsImmobile(5)) {
								if (Engine::IsReady(0, me))
									Engine::CastSpellPos(0, target->GetPos());
							}
							else if (target->GetBuffMgr()->IsImmobile(11)) {
								if (Engine::IsReady(0, me))
									Engine::CastSpellPos(0, target->GetPos());
							}
						}

					}
				}

			}
		}
};

