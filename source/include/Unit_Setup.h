/*
 *  Strategos - CREATE_ARMY.h
 *
 *  Este eh uma visualizacao do STATE CREATE_ARMY.
 *	O CREATE_ARMY sera a primeira tela a ser exibida e eh o retorno
 *  para quando os outros estados acabarem.
 *
 *	Last update: 06/07/2012
 */

#ifndef _UNIT_SETUP_H_
#define _UNIT_SETUP_H_

#include "StateMachine.h"
#include "GuiElements.h"
#include "GuiTactics.h"
#include "Dictionary.h"

class Unit_Setup : public StateMachine
{
private:
    Image *imgBackground;
    ImageBox *blueprint;
    Image *squad_selec;
    Button *btn_Back;
    Button *btn_Next;
    Button *btn_Del;
    Button *btn_Move;
    Unit *squad_focus;

    TacticList *list;

    Label *lbl_Geral;

    //TacticSet *tct_1,*tct_2,*tct_3,*tct_4,*tct_5;
    ImageBox *bx1,*bx2,*bx3,*bx4;

    Dictionary *dct;
    vector<Label*> squad_number;

    bool put_squad, move_squad;
    int squad_type;
public:
    Unit_Setup(STATE previous);
    ~Unit_Setup();

    void onInputEvent(cGuiElement* element, INPUT_EVENT action, SDL_Keysym key, Uint8 button);
    void Logic();
    void Render();
    void Clean();
};

#endif
