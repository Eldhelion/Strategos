#include "CombatLog.h"
CombatLogItem::CombatLogItem(int squad, int ship)
{
	this->squadNum=squad;
	this->shipNum = ship;
}

CombatLogItem::~CombatLogItem()
{
}

/// Combat Log

CombatLog::CombatLog()
{
	this->damageDealt=0;
	this->damageTaken=0;
}

CombatLog::~CombatLog()
{
    for (unsigned int i = 0; i < combatline.size(); ++i)
        delete combatline[i];
	this->combatline.clear();
}

void CombatLog::addLog(int squad, int ship)
{
	this->combatline.push_back(new CombatLogItem(squad,ship));
}

std::vector<CombatLogItem*> CombatLog::getLog()
{
	return this->combatline;
}
