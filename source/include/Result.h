/*
 * Result.h
 *
 *  Created on: 21/09/2013
 *      Author: Eldhelion
 */

#ifndef RESULT_H_
#define RESULT_H_
#include "StateMachine.h"
#include "GuiElements.h"
using namespace std;
class Result : public StateMachine
{
private:
    Image *imgBackground;
    Button *btn_Next;

    Label *alive,*dead;

public:
    Result(STATE previous);
    ~Result();

    void onInputEvent(cGuiElement* element, INPUT_EVENT action, SDL_Keysym key, Uint8 button);
    void Logic();
    void Render();
    void Clean();
};
#endif /* RESULT_H_ */
