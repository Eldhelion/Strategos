/*
 *  Strategos - Play.h
 *
 *  Este eh uma visualizacao do STATE Menu.
 *	O Menu sera a primeira tela a ser exibida e eh o retorno
 *  para quando os outros estados acabarem.
 *
 *	Last update: October 17th 2012
 */

#ifndef _PLAY_H_
#define _PLAY_H_

#include "StateMachine.h"
#include "GuiElements.h"

class Play : public StateMachine
{
private:
    Image *imgBackground;
    Label *lbTitle;
    Button *btSimulate;
    ComboBox *cbSelect1;
    ComboBox *cbSelect2;
    ComboBox *cbPlayer1;
    ComboBox *cbCPU1;
    ComboBox *cbPlayer2;
    ComboBox *cbCPU2;

    TextField *tfPlayer1;
    TextField *tfPlayer2;

public:
    Play(STATE previous);
    ~Play();

    void onInputEvent(cGuiElement* element, INPUT_EVENT action, SDL_Keysym key, Uint8 button);
    void onKeyDownEvent(SDL_Keysym key);
    void onKeyUpEvent(SDL_Keysym key);
    void onMouseDownEvent(Uint8 button);
    void onMouseUpEvent(Uint8 button);
    void Logic();
    void Render();
    void Clean();
};

bool previewArmy(const char *armyName);

#endif
