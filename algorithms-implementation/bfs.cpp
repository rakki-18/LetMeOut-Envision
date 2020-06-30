#include <iostream>
#include <list>

using namespace std;

class Graph
{
    int numVertices;
    list *adjLists;
    bool* visited;
public:
    Graph(int vertices);
    void addEdge(int src, int dest);
    void BFS(int startVertex);
};

Graph::Graph(int vertices) // function of graph
{
    numVertices = vertices;
    adjLists = new list[vertices];
}

void Graph::addEdge(int src, int dest) // function to add an edge between vertices
{
    adjLists[src].push_back(dest);
    adjLists[dest].push_back(src);
}

void Graph::BFS(int startVertex)
{
    visited = new bool[numVertices];
    // making all other points as not visited
    for(int i = 0; i < numVertices; i++)
        visited[i] = false;

    list queue;

    visited[startVertex] = true;
    queue.push_back(startVertex);// pushing start vertex into the queue

    list::iterator i;

    while(!queue.empty())   // loop runs until there is no point left in queue
    {
        int currVertex = queue.front();
        cout << "Visited " << currVertex << " ";  // printing the first element in the queue
        queue.pop_front();  // removing that element from the queue

        for(i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); ++i)  // running a loop on all the adjacent points from the current vertex
        {
            int adjVertex = *i;
            if(!visited[adjVertex])
            {
                visited[adjVertex] = true;   // if the adjacent vertex is not visited, we are marking it as visited
                queue.push_back(adjVertex);  // we are pushing the adjacent vertex to the queue
            }
        }
    }
}

int main()
{
    Graph g(5);  // declaring the graph
     // adding all the edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.BFS(0);   // doing bfs from vertex 0

    return 0;
}
