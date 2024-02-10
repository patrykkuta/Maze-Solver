#ifndef GENERATINGALGORITHM_H
#define GENERATINGALGORITHM_H

#include "Cell.h"
#include "Step.h"
#include <set>

class GeneratingAlgorithm
{
protected:
    unsigned short mazeWidth;
    unsigned short mazeHeight;
    vector<vector<Cell*>> maze;
    set<Cell*> frontier;
    vector<Step> generationSteps;

    virtual Cell* getGenerationStartCell() = 0;
    bool connect(Cell* cell);

public:
    GeneratingAlgorithm(unsigned short width, unsigned short height);
    virtual vector<vector<Cell*>> generate() = 0;
    vector<Step> getGenerationSteps();

};

#endif // GENERATINGALGORITHM_H
