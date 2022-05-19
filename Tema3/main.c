#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph_adj_matrix.h"
#include "stack.h"
#include "queue.h"
void printPath(int *incoming, int j, int final)
{
    if (incoming[j] == -1)
        return;
    printPath(incoming, incoming[j],final);
    printf("%d", j);
    if(j!=final)
        printf(" ");
}
int minDist(float *dist,int *visit, int size)
{
    float min=9999;
    int minindex;
    for(int i=0;i<size;i++)
        if(visit[i]==0 && dist[i] <= min)
        {
            min=dist[i];
            minindex=i;
        }
    return minindex;
}
float *dijkstraPRO(graphAdjMat_t *graph, int s, int *incoming)
{
    float *dist=malloc(graph->numNodes*sizeof(float));
    int *visit=malloc(graph->numNodes*sizeof(int));
    for(int i=0;i<graph->numNodes;i++)
    {
        dist[i]=9999;
        visit[i]=0;
        incoming[i]=-1;
    }
    dist[s]=0;
    for(int i=0;i<graph->numNodes-1;i++)
    {
        int u=minDist(dist,visit,graph->numNodes);
        visit[u]=1;
        for(int j=0;j<graph->numNodes;j++)
            if(visit[j]==0 && graph->mat[u][j]!=0 && dist[u]!= 9999 && dist[u] + graph->mat[u][j] < dist[j])
            {
                dist[j] = dist[u] + graph->mat[u][j];
                incoming[j]=u;
            }
    }
    free(visit);
    return dist;
}

void e1(graphAdjMat_t *graph)
{
    int s,k,x;
    float totalcost=0;
    scanf("%d%d",&s,&k);
    for(int i=0;i<k;i++)
    {
        scanf("%d", &x);
        float *dist1,*dist2;
        int *path1,*path2;
        path1=malloc(graph->numNodes*sizeof(int));
        path2=malloc(graph->numNodes*sizeof(int));
        dist1=dijkstraPRO(graph,s,path1);
        dist2=dijkstraPRO(graph,x,path2);
        totalcost=totalcost+dist1[x]+dist2[s];
        printf("%d\n", x);
        printf("%.1f %.1f\n", dist1[x],dist2[s]);
        printf("%d ", s);
        printPath(path1,x,-1);
        printPath(path2,s,s);
        printf("\n");

        free(dist1);
        free(dist2);
        free(path1);
        free(path2);
    }
    printf("%.1f", totalcost);
    
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

float *dijkstra(graphAdjMat_t *graph, int s)
{
    float *dist=malloc(graph->numNodes*sizeof(float));
    int *visit=malloc(graph->numNodes*sizeof(int));
    for(int i=0;i<graph->numNodes;i++)
    {
        dist[i]=9999;
        visit[i]=0;
    }
    dist[s]=0;
    for(int i=0;i<graph->numNodes-1;i++)
    {
        int u=minDist(dist,visit,graph->numNodes);
        visit[u]=1;
        for(int j=0;j<graph->numNodes;j++)
            if(visit[j]==0 && graph->mat[u][j]!=0 && dist[u]!= 9999 && dist[u] + graph->mat[u][j] < dist[j])
            {
                dist[j] = dist[u] + graph->mat[u][j];
            }
    }
    free(visit);
    return dist;
}

void swap(int *zona, int i, int j)
{
    int aux;
    aux=zona[i];
    zona[i]=zona[j];
    zona[j]=aux;
}

void checkDistance(int *zona, int size, float *mincost, graphAdjMat_t *graph, float **distances)
{
    float cost=0;
    for(int i=0;i<size-1;i++)
    {
        cost += distances[zona[i]][zona[i + 1]];
        if (cost > *mincost)
            return;
    }
    if(cost<*mincost)
        *mincost=cost;
}
void permutari(int *zona,int size, int start, int end, float *mincost, graphAdjMat_t *graph, float **distances)
{
    if(end==start)
    {    
        checkDistance(zona,size,mincost,graph,distances);
        return;
    }
    for(int i=start;i<end+1;i++)
    {
        swap(zona,start,i);
        permutari(zona,size,start+1,end,mincost,graph,distances);
        swap(zona,start,i);
    }
}
void e3(graphAdjMat_t *graph)
{
    int r;
    scanf("%d", &r);
    int k,x;
    float **distances;
    distances = malloc(graph->numNodes * sizeof(float *));
    for (int i = 0; i < graph->numNodes; i++)
        distances[i] = dijkstra(graph, i);
    for (int i = 0; i < r; i++)
    {
        scanf("%d",&k);
        int *zona=malloc((k+2)*sizeof(int));
        for(int j=0;j<k;j++)
            scanf("%d",&zona[j+1]);
        float mincost=9999;
        for(int j=0;j<graph->numNodes;j++)
        {
            if(graph->mat[j][j]==1)
            {
                zona[0]=j;
                zona[k+1]=j;
                permutari(zona,k+2,1,k,&mincost,graph,distances);
            }
        }
        free(zona);
        printf("%.1f",mincost);
        if(i!=r-1)
            printf("\n");
    }
}
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
        if(strcmp(cerinta,"e1\n")==0 || strcmp(cerinta,"e1")==0 )
            e1(graph);
        else if(strcmp(cerinta,"e2")==0)
            e2(graph);
        else if(strcmp(cerinta,"e3")==0 || strcmp(cerinta,"e3\n")==0)
            e3(graph);
        fgets(cerinta,5,stdin);
        if(i!=cer-1)
            printf("\n");
    }
    for (int i = 0; i < graph->numNodes; i++) {
        free(graph->mat[i]);
    }
    free(graph->mat);
    free(graph);
    return 0;
}
