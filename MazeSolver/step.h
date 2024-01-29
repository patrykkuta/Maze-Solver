#ifndef STEP_H
#define STEP_H

#include "state.h"
#include "Cell.h"

class Step
{
public:
    Step(State state, Cell* cell);
    State state();
    Cell* cell();
    bool operator==(const Step& other) const;
private:
    pair<State, Cell*> step;
};

#endif // STEP_H
