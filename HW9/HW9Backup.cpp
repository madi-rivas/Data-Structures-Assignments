#include <iostream>
#include <vector>
#include "Graph.hpp"
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

Graph::Graph()
{

}

Graph::~Graph()
{

}

void Graph::addEdge(string v1, string v2, int distance)
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name==v1)
        {
            for(int j = 0; j < vertices.size(); j ++)
            {
                if(vertices[j].name == v2 && i != j)
                {
                    Edge newEdge;
                    newEdge.distance = distance;
                    newEdge.v = &vertices[j];
                    vertices[i].Edges.push_back(newEdge);
                }
            }
        }
    }
}

void Graph::addVertex(string name)
{
    vertex newVertex;
    newVertex.name = name;
    newVertex.district = 0;
    newVertex.visited = false;

    vertices.push_back(newVertex);
}

void Graph::displayEdges()
{
    int j = 0;
    for(int i = 0; i < vertices.size(); i++)
    {
        cout<<vertices[i].district<<":"<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].Edges.size(); j++)
        {
            cout<<vertices[i].Edges[j].v->name;
            cout<<" ("<<vertices[i].Edges[j].distance<<" miles)";
            if(j != vertices[i].Edges.size()-1){
                cout<<"***";
            }
        }
        cout<<endl;
    }
}

void Graph::assignDistricts()
{
    int num = 1;
    setAllVerticesUnvisited();

    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].district < 1)
        {
            BFTraversalLabel(vertices[i].name, num);
            num++;
        }
    }

}

vertex* Graph::findVertex(std::string name)
{
    if(vertices[0].name == name)
        return &vertices[0];
    else
    {
        for(int i = 0; i < vertices.size(); i++)
        {
            if(vertices[i].name == name)
                return &vertices[i];
        }
    }
}

void Graph::BFTraversalLabel(string startingCity, int distID)
{
    queue<string> Queue;

    Queue.push(startingCity);

    while(!Queue.empty())
    {
        vertex* currentCity;
        currentCity = findVertex(Queue.front());
        currentCity->district = distID;
        currentCity->visited = true;

        Queue.pop();

        for(int i = 0; i < currentCity->Edges.size(); i++)
        {
            vertex* nextCity;
            nextCity = findVertex(currentCity->Edges[i].v->name);
            if(nextCity->visited==false)
            {
                currentCity->district = distID;
                Queue.push(nextCity->name);
            }
        }
        
    }
}


void Graph::setAllVerticesUnvisited()
{
    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
    }

}

void Graph::printDFS()
{
    setAllVerticesUnvisited();
     
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].visited == false)
        {
            DFTraversal(&vertices[i]);
        }
    }
}

void Graph::DFTraversal(vertex* v)
{
    vertex* currentVertex = v;
    stack<string> Stack;

    Stack.push(currentVertex->name);

    while(!Stack.empty())
    {
        string Name = Stack.top();
        Stack.pop();

        currentVertex = findVertex(Name);

        if(currentVertex->visited==false)
        {
            cout<<currentVertex->name<<endl;
            currentVertex->visited = true;
        }
    

        for(int i = currentVertex->Edges.size()-1; i >= 0; i--)
        {
            vertex* nextVertex = currentVertex->Edges[i].v;
            if(nextVertex->visited==false)
            {
                Stack.push(nextVertex->name);
            }
        }
    }

}


/*void Graph::printDFS()
{
    setAllVerticesUnvisited();
        DFTraversal(&vertices[0]);


}

void Graph::DFTraversal(vertex* v)
{
    vertex* nextVertex = v;
    if(!nextVertex->visited)
    {
        nextVertex->visited = true;
        cout<<nextVertex->name<<endl;
        for(int i = 0; i < nextVertex->Edges.size(); i++){
            nextVertex = nextVertex->Edges[i].v;
            if(!nextVertex->visited)
            {
                DFTraversal(nextVertex);
            }
        }
    }

}*/



int main(int argc, char** argv)
{
    Graph graph;
    std::vector<string> verts;

    char* fileName = argv[1];

    ifstream myFile(fileName);

    string line;

    getline(myFile, line);

    string trash;

    stringstream ss(line);

    getline(ss, trash, ',');
    
    string newCity;
    while(getline(ss, newCity, ','))
    {
        graph.addVertex(newCity);
        verts.push_back(newCity);
    }

    string city;
    string distance;
    //int intDist = stoi(distance);

    while(getline(myFile, line))
    {
        stringstream ss2(line);

        getline(ss2, city, ',');
        
        //cout << "HERE" << i << endl;
        int i = 0;
        while(getline(ss2, distance, ','))
        {
            //cout << "in here" << endl;
            int intDist = stoi(distance);
            if(intDist > 0)
            {
                graph.addEdge(city, verts[i], intDist);
                cout << " ... Reading in " << city << " -- " << verts[i] << " -- " << intDist << endl;
            
            }
            i++;
        }
    
    }

    graph.assignDistricts();

    graph.displayEdges();

    return 0;
}
