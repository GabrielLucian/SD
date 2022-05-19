#include <stdlib.h>
#include <stdio.h>
#include "graph_adj_matrix.h"

graphAdjMat_t *initGraph(size_t numNodes) 
{
    if (numNodes <= 0)
        return NULL;
    graphAdjMat_t *g = malloc(sizeof(graphAdjMat_t));

    g->numNodes = numNodes;
    g->mat = malloc(numNodes * sizeof(float *));

    for (int i = 0; i < numNodes; i++) 
        g->mat[i] = malloc(numNodes* sizeof(float));
    for (int i=0;i<numNodes;i++)
        for(int j=0;j<numNodes;j++)
            g->mat[i][j]=0;
    return g;
}

void insertEdge(graphAdjMat_t *g, size_t u, size_t v, float cost) 
{
    if (g == NULL)
        return;

    if (u >= g->numNodes || v >= g->numNodes)
        return;
    g->mat[u][v] = cost;
}

