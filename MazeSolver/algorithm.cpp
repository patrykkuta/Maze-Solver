#include "algorithm.h"

Algorithm::Algorithm() {}

Algorithm::~Algorithm() {}

queue<Step*> Algorithm::getSteps() {
    return steps;
}

vector<Cell*> Algorithm::getSolutionPath() {
    return solutionPath;
}
