#ifndef TEMA3__GRAPH_ADJ_MATRIX_H
#define TEMA3__GRAPH_ADJ_MATRIX_H

#include "stddef.h"
#include "stack.h"

typedef struct graphAdjMat {
    size_t numNodes;      
    float **mat;             
} graphAdjMat_t;

typedef struct graphEdge {
    size_t u;     
    size_t v;      
    float cost;      
} graphEdge_t;

graphAdjMat_t *initGraph(size_t numNodes);
void insertEdge(graphAdjMat_t *g, size_t u, size_t v, float cost) ;
#endif //TEMA3__GRAPH_ADJ_MATRIX_H
