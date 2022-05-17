#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph_adj_matrix.h"
#include "stack.h"

drumret *drum(int s, int d, int *vizit,graphAdjMat_t *graph)
{
    if(s==d)
    {
        drumret *ret= malloc(sizeof(drumret));
        ret->path=init_stack();
        ret->cost=1;
        return ret;
    }
    else
    {
        int ok = 0, minnode;
        float mincost = 10000;
        drumret *ret;
        stack *path;
        int *newvizit = calloc(graph->numNodes, sizeof(int));
        for (int i = 0; i < graph->numNodes; i++)
            newvizit[i] = vizit[i];
        newvizit[s] = 1;

        for (int i = 0; i < graph->numNodes; i++) {
            if (graph->mat[s][i] != 0 && newvizit[i] == 0) {
                ret = drum(i, d, newvizit, graph);
                if (ret != NULL) {
                    add_stack(ret->path, i);
                    ret->cost += graph->mat[s][i];
                    if (ret->cost < mincost) {
                        mincost = ret->cost;
                        path=ret->path;
                        //delete_stack(path);
                        //path=copy(ret->path);
                        //free(ret);
                    }
                    else
                    {
                        delete_stack(ret->path);
                        free(ret);
                    }
                }
            }
        }
        free(newvizit);
        if (mincost != 10000) {
            drumret *ret1 = malloc(sizeof(drumret));
            ret1->path=path;
            ret1->cost=mincost;
            return ret1;
        }
        return 0;
    }
}
void e1(graphAdjMat_t *graph)
{
    int s,k,x;
    float totalcost=0;
    scanf("%d%d",&s,&k);
    for(int i=0;i<k;i++)
    {
        scanf("%d",&x);
        printf("%d\n",x);
        int *vizit=calloc(graph->numNodes, sizeof(int));


        drumret *ret1=drum(s,x,vizit,graph);
        drumret *ret2=drum(x,s,vizit,graph);
        add_stack(ret1->path,s);
        printf("%.1f %.1f\n",ret1->cost-1,ret2->cost-1);
        print_stack(ret1->path);
        print_stack(ret2->path);
        if(i!=k-1)
            printf("\n");

        free(vizit);
        delete_stack(ret1->path);
        delete_stack(ret2->path);
        free(ret1);
        free(ret2);
    }
}
void e2();
void e3();
int main() {
    int n,m,d,u,v,dep,cer;
    float w;
    char cerinta[5];
    graphAdjMat_t *graph;
    scanf("%d%d%d",&n,&m,&d);
    graph=initGraph(n);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d%f", &u,&v,&w);
        insertEdge(graph,u,v,w);
    }
    for(int i=0;i<d;i++)
    {
        scanf("%d",&dep);
        graph->mat[dep][dep]=1;
    }
    scanf("%d",&cer);
    fgets(cerinta,5,stdin);
    for(int i=0;i<cer;i++)
    {
        fgets(cerinta,5,stdin);
        if(strcmp(cerinta,"e1\n")==0)
            e1(graph);
        else if(strcmp(cerinta,"e2\n")==0)
            e2;
        else if(strcmp(cerinta,"e3\n")==0)
            e3;
    }
    for (int i = 0; i < graph->numNodes; i++) {
        free(graph->mat[i]);
    }
    free(graph->mat);
    free(graph);
    //printf("\b");
    return 0;
}
