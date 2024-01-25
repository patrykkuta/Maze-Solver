#ifndef STEP_H
#define STEP_H

#include "state.h"
#include "Cell.h"

class Step
{
public:
    Step(State state, Cell* cell);
    pair<State, Cell*> getStep();
private:
    pair<State, Cell*> step;
};

#endif // STEP_H
