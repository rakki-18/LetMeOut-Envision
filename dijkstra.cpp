#include <bits/stdc++.h>
int i;
int minindex;
const int V=4;


using namespace std;
int mindistance(int dist[], bool sptset[])
{
    int min=INT_MAX;
    for(i=0;i<V;i++)
    {
        if(sptset[i]==false&&dist[i]<min)
            min=dist[i],minindex=i;
    }
    return minindex;
}
void dijkstra(int graph[V][V] , int start)
{
    int dist[V],count;
    bool sptset[V];
    for(i=0;i<V;i++)
        sptset[i]=false,dist[i]=INT_MAX;
    dist[start]=0;
    for(count=0;count<V-1;count++)
    {
       int u=mindistance(dist,sptset);
        sptset[u]=true;
        for(int v=0;v<V;v++)
        {
            if(graph[u][v]&&dist[u]+graph[u][v]<dist[v]&&!sptset[v])
                dist[v]=dist[u]+graph[u][v];
        }
    }
    for(i=0;i<V;i++)
        cout<<"distance of "<<i<<"from "<<start<<"is "<<dist[i]<<endl;

}

int main()
{
    int graph[4][4]={0,10,1,6,10,0,5,0,1,5,0,10,6,0,10,0};
    dijkstra(graph,2);

    return 0;
}
