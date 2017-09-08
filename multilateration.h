#ifndef MULTILATERATION_H
#define MULTILATERATION_H

#include "cyberglobal.h"


void referanceNode(const unsigned numberOfDevice, WAP *waps, lastDistance *lastDist);
void targetNode(const unsigned numberOfDevice, WAP *waps);
void gaussianElimination(float matirx[][4], float gaussianMatrix[][4]);

#endif // MULTILATERATION_H
