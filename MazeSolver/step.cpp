#include "step.h"

Step::Step(State state, Cell* cell) {
    step.first = state;
    step.second = cell;
}

pair<State, Cell*> Step::getStep() {
    return step;
}
