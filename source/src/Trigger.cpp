#include "Trigger.h"

#include "Unit.h"

Trigger* Trigger::copy(const Trigger *source)
{
    Trigger *t_copy = nullptr;

    switch (source->type)
    {
        case 0:
            t_copy = new Trigger_Always();
            break;

        case 1:
            t_copy = new Trigger_Life(source->value, source->relOperator);
            break;

        default:
            break;
    }

    return t_copy;
}


TacticTrigger::TacticTrigger(Trigger* A, Trigger* B, int oper)
    : tA(A), tB(B), operation(oper)
{
}

TacticTrigger::TacticTrigger(const TacticTrigger &source)
    : tA(0), tB(0)
{
    if (source.tA)
        tA = Trigger::copy(source.tA);

    if (source.tB)
        tB = Trigger::copy(source.tB);

    operation = source.operation;
}

bool TacticTrigger::testTrigger(Unit *unit)
{
    // Se nao houverem triggers - retorna 1
    if (!tA || !tB)   return 1;

    bool A = tA->testTrigger(unit);
    bool B = tB->testTrigger(unit);

    switch (operation)
    {
        case TRIGGER_LOGIC_AND:
            return (A && B);
        break;

        case TRIGGER_LOGIC_OR:
            return (A || B);
        break;
    }

    return 0;
}

TacticTrigger::~TacticTrigger()
{
    delete tA;
    delete tB;
}

Trigger_Always::Trigger_Always()
{
    type = TRIGGER_ALWAYS;
    value = 0;
    relOperator = 0;
}

Trigger_Always::~Trigger_Always()
{

}

bool Trigger_Always::testTrigger(Unit *unit)
{
    return 1;
}

//WHAT IS HAPPENING HERE? O.o
Trigger_Life::Trigger_Life(int lifeTrigger, int trigOP)
{
    type = TRIGGER_LIFE;
    value = lifeTrigger;
    relOperator = trigOP;
}

Trigger_Life::~Trigger_Life()
{

}

bool Trigger_Life::testTrigger(Unit *unit)
{
    // Endereco de trigger nao foi passado corretamente
    int sumHP = 0;
    for (unsigned int i = 0; i < unit->nShips(); ++i)
    {
        sumHP += unit->getShip(i)->getHP();
    }

    int maxHP = unit->getUnitInfo()->squadSize*unit->getUnitInfo()->stats.maxHP;

    // Considerar apenas o inteiro
    int percent = (sumHP/maxHP)*100;

    switch (relOperator)
    {
        case TRIGGER_OPERATION_EQUAL:
            if ( percent == value )   return 1;
        break;

        case TRIGGER_OPERATION_GREATER_EQUAL:
            if ( percent >= value )   return 1;
        break;

        case TRIGGER_OPERATION_LOWER_EQUAL:
            if ( percent <= value )   return 1;
        break;
    }

    return 0;
}

Trigger* TacticTrigger::getTriggerA()
{
	return tA;
}

Trigger* TacticTrigger::getTriggerB()
{
    return tB;
}

void TacticTrigger::setTriggerA(Trigger* t)
{
	if (tA)
        delete tA;

	tA = t;
}

void TacticTrigger::setTriggerB(Trigger* t)
{
	if (tB)
        delete tB;

    tB = t;
}


