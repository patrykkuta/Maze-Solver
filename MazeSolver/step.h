#ifndef STEP_H
#define STEP_H

#include "state.h"
#include "cell.h"

class Step
{
public:
    Step(State state, Cell* cell);
    pair<State, Cell*> getStep();
private:
    pair<State, Cell*> step;
};

#endif // STEP_H
