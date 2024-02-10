#ifndef PRIMSALGORITHM_H
#define PRIMSALGORITHM_H

#include "generatingalgorithm.h"
#include <random>
#include <algorithm>

class PrimsAlgorithm : public GeneratingAlgorithm
{
private:
    random_device rd;

    unsigned short randomFrontierPosition();
    void addUnvisitedNeighbours(Cell* cell);

protected:
    Cell* getGenerationStartCell() override;

public:
    PrimsAlgorithm(unsigned short width, unsigned short height);

    vector<vector<Cell*>> generate() override;
};

#endif // PRIMSALGORITHM_H
