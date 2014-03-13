/*
 *  Strategos - Tactic.h
 *
 *  Esta classe apresenta diversos filhos que especificam uma certa regra
 *  a ser seguida no campo de batalha.
 *  Cada regra utiliza de parametros setados pelo jogador para que sejam
 *  ativadas. Uma vez ativada, uma regra liberara' uma action (atirar, tomar dano, etc.)
 *
 *	Last update: 06/07/2012
 */


#ifndef _TACTIC_H_
#define _TACTIC_H_

#include <vector>
#include <list>
#include <string>

#include "Action.h"
#include "Ship.h"
#include "Trigger.h"

#define TACTIC_ATTACK_NEAREST_ENEMY 0
#define TACTIC_ATTACK_WEAKEST_ENEMY 1
#define TACTIC_ATTACK_COLLAB        2
#define TACTIC_DEFENSE_COLAB        3
#define TACTIC_KAMIKASE             4
#define TACTIC_RETREAT              5
#define TACTIC_MOVE_RANDOM          100

class Unit;

struct TacticInfo
{
    TacticInfo(int unitID)
    {
        allyUnitID = unitID;
    }

    int allyUnitID; // Unidade aliada para interagir
};

class Tactic
{
    protected:
        TacticTrigger tacticTrigger;
        TacticInfo info;
        int type;

    public:
        static Tactic* copy(const Tactic *source);

        Tactic(TacticInfo info, const TacticTrigger& trigger, int type)
            : tacticTrigger(trigger), info(info), type(type)
        {}

//        Tactic() : info(0), type(-1)
//        {}

        virtual ~Tactic() {
        }

        bool testTrigger(Unit *unit)
        {
            return tacticTrigger.testTrigger(unit);
        }

        void setType(int newType)
        {
            type = newType;
        }

        int getType()
        {
            return type;
        }

        void setInfo(TacticInfo info_)
        {
            info.allyUnitID = info_.allyUnitID;
        }

        TacticInfo getInfo()
        {
            return info;
        }

        TacticTrigger& getTacticTrigger()
        {
            return tacticTrigger;
        }

        virtual void debugPrint() = 0;

        virtual string printTactic()
        {
            string str = "";

            //tipo da primeira trigger
            str.append(std::to_string(tacticTrigger.getTriggerA()->getType()));
            str.append(" ");
            //valor de comparacao
            str.append(std::to_string(tacticTrigger.getTriggerA()->getValue()));
            str.append(" ");
            //operador relacional
            str.append(std::to_string(tacticTrigger.getTriggerA()->getRelationalOperator()));
            str.append(" ");

            //operador logico
            str.append(std::to_string(tacticTrigger.getLogicOperator()));
            str.append(" ");

            //segunda trigger
            str.append(std::to_string(tacticTrigger.getTriggerB()->getType()));
            str.append(" ");
            str.append(std::to_string(tacticTrigger.getTriggerB()->getValue()));
            str.append(" ");
            str.append(std::to_string(tacticTrigger.getTriggerB()->getRelationalOperator()));
            str.append(" ");

            str.append(std::to_string(type));

            return str;
        }

        // Verifica se a tatica pode ser efetuada e nesse caso j� adiciona uma acao para a nave
        // @return: 1 se a tatica foi validada, 0 caso contrario.
        virtual int validateTactic(list<Action*> &newActions, Unit* squad, const vector<Unit*>& enemyUnits, const vector<Unit*>& alliedUnits ) = 0;
};

// Ataca o inimigo mais proximo dentro da RANGE da nave
// Nenhum parametro adicional
// TODOS os esquadroes possuem esta tatica como ultima alternativa
class AttackNearestEnemy : public Tactic
{
    private:

    public:
        AttackNearestEnemy(TacticInfo info, const TacticTrigger& trigger);
        ~AttackNearestEnemy() {}

        void debugPrint(){printf("AttackNearestEnemy");}

        int validateTactic(list<Action*> &newActions, Unit* squad, const vector<Unit*>& enemyUnits, const vector<Unit*>& alliedUnits);
};

// Ataca o inimigo mais fraco dentro da RANGE da nave
// Nenhum parametro adicional
class AttackWeakestEnemy : public Tactic
{
    private:

    public:
        AttackWeakestEnemy(TacticInfo info, const TacticTrigger& trigger);

        void debugPrint(){printf("AttackWeakestEnemy");}

        int validateTactic(list<Action*> &newActions, Unit* squad, const vector<Unit*>& enemyUnits, const vector<Unit*>& alliedUnits);
};

// Ataque colaborativo
// Ataca o mesmo alvo que a unidade aliada estiver atacando
// Se a unidade aliada estiver morta essa tatica eh desconsiderada.
class AttackCollab : public Tactic
{
    private:

    public:
        AttackCollab(TacticInfo info, const TacticTrigger& trigger);
        ~AttackCollab(){}

        string printTactic();

        void debugPrint(){printf("AttackCollab");}

        int validateTactic(list<Action*> &newActions, Unit* squad, const vector<Unit*>& enemyUnits, const vector<Unit*>& alliedUnits);
};

// Defende a unidade aliada
// Ataca quem estiver atacando a unidade aliada
class DefenseCollab : public Tactic
{
    private:

    public:
        DefenseCollab(TacticInfo info, const TacticTrigger& trigger);
        string printTactic();

        void debugPrint(){printf("DefenseCollab");}

        int validateTactic(list<Action*> &newActions, Unit* squad, const vector<Unit*>& enemyUnits, const vector<Unit*>& alliedUnits);
};

// Suicidar-se na nave inimiga mais proxima
// Cada nave do conjunto eh testada para os triggers
// Aquelas que ativarem iram se atirar na nave inimiga mais proxima
// OBS: A unidade Mae NAO pode ter esta tatica
class Kamikase : public Tactic
{
    private:

    public:
        Kamikase(TacticInfo info, const TacticTrigger& trigger);

        void debugPrint(){printf("Kamikase");}

        int validateTactic(list<Action*> &newActions, Unit* squad, const vector<Unit*>& enemyUnits, const vector<Unit*>& alliedUnits);
};

// Retornar para perto da unidade aliada
class Retreat : public Tactic
{
    private:
    public:
        Retreat(TacticInfo info, const TacticTrigger& trigger);

        string printTactic();

        void debugPrint(){printf("Retreat");}

        int validateTactic(list<Action*> &newActions, Unit* squad, const vector<Unit*>& enemyUnits, const vector<Unit*>& alliedUnits);
};

// Mover aleatoriamente
// TODOS os esquadroes possuem esta tatica como ultima alternativa
class MoveRandomly : public Tactic
{
    private:
        int cooldown; // Tempo para mudar de direcao

    public:
        MoveRandomly(TacticInfo info, const TacticTrigger& trigger);

        void debugPrint(){printf("MoveRandomly");}

        int validateTactic(list<Action*> &newActions, Unit* squad, const vector<Unit*>& enemyUnits, const vector<Unit*>& alliedUnits);
};

#endif