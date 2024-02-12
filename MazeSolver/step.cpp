#include "step.h"

Step::Step(State state, Cell* cell) {
    step.first = state;
    step.second = cell;
}

State Step::state() {
    return step.first;
}

Cell* Step::cell() {
    return step.second;
}

bool Step::operator==(const Step& other) const {
    return (other.step.first == step.first) && (other.step.second == step.second);
}
