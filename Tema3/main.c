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
        //if(i!=k-1)
            printf("\n");

        free(vizit);
        delete_stack(ret1->path);
        delete_stack(ret2->path);
        free(ret1);
        free(ret2);
    }
}
graphAdjMat_t *transpose(graphAdjMat_t *graph){
    graphAdjMat_t *tr=malloc(sizeof(graphAdjMat_t));
    tr->numNodes=graph->numNodes;
    tr->mat=malloc(graph->numNodes*sizeof(float*));
    for(int i=0;i<graph->numNodes;i++)
        tr->mat[i]=malloc(graph->numNodes*sizeof(float));
    for(int i=0;i< tr->numNodes;i++)
        for(int j=0;j<tr->numNodes;j++)
            tr->mat[i][j]=graph->mat[j][i];
    return tr;
}
void DFS(graphAdjMat_t *graph, int s, int *vizit, stack *path)
{
    vizit[s] = 1;
    for (int i = 0; i < graph->numNodes; i++) {
        if (graph->mat[s][i] != 0 && vizit[i] == 0 && graph->mat[i][i]!=1) {
            add_stack(path,i);
            DFS(graph,i,vizit,path);
        }
    }
}

void e2(graphAdjMat_t *graph)
{
    graphAdjMat_t *graphtr=transpose(graph);
    stack *path1=init_stack();
    int *vizit1=calloc(graph->numNodes, sizeof(int));
    int *vizit2=calloc(graph->numNodes, sizeof(int));
    int len=1;
    for(int i=0;i<graph->numNodes;i++)
    {
        if(vizit1[i]==0 && graph->mat[i][i]!=1)
        {
            add_stack(path1,i);
            DFS(graph,i,vizit1,path1);
            
        }
    }
    free(vizit1);

    node_t *aux;
    int count=0;
    stack **groups=malloc(1*sizeof(stack*));
    while(path1->len>0)
    {
        aux=remove_stack(path1);
        int i=aux->val;
        if(vizit2[i]==0 && graphtr->mat[i][i]!=1)
        {
            count++;
            groups=realloc(groups,count*sizeof(stack*));
            groups[count-1]=init_stack();
            add_stack(groups[count-1],i);
            DFS(graphtr,i,vizit2,groups[count-1]);
            groups[count-1]=sort(groups[count-1]);
        }
        free(aux);
    }
    free(path1);
    free(vizit2);

    stack *aux2;
    for(int i=0; i<count;i++)
        for(int j=0;j<count-i-1;j++)
            if(groups[j]->top->val>groups[j+1]->top->val)
            {
                aux2=groups[j];
                groups[j]=groups[j+1];
                groups[j+1]=aux2;
            }

    printf("%d\n", count);
    for(int i=0;i<count;i++)
    {
        print_stack(groups[i]);
        if(i!=count-1)
            printf("\n");
        delete_stack(groups[i]);
    }

    for (int i = 0; i < graphtr->numNodes; i++) {
        free(graphtr->mat[i]);
    }
    free(graphtr->mat);
    free(graphtr);
    free(groups);
}
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
        //printf("%s\n", cerinta);
        if(strcmp(cerinta,"e1\n")==0)
            e1(graph);
        else if(strcmp(cerinta,"e2")==0)
            e2(graph);
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
