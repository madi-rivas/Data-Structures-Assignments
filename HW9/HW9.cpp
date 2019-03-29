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


int main(int argc, char** argv)
{
	std::vector<string> vertices_;
	Graph graph;

	char* fileName = argv[1];
	ifstream myFile(fileName);
	string line;
	getline(myFile, line);

	string first;

	stringstream ss(line);
	getline(ss, first, ',');

	string newVert;

	while(getline(ss, newVert, ','))
	{
		graph.addVertex(newVert);
		vertices_.push_back(newVert);
	}

	string city;
	string dist;

	while(getline(myFile, line))
	{
		stringstream ss_(line);

		getline(ss_, city, ',');
		int i = 0;
		while(getline(ss_, dist, ','))
		{
			int distI = stoi(dist);
			if(distI >= 1)
			{
				graph.addEdge(city, vertices_[i], distI);
				cout<<" ... Reading in "<<city<<" -- "<<vertices_[i]<<" -- "<<distI<<endl;
			}
			i++;
		}
	}
	graph.assignDistricts();
	graph.displayEdges();

	return 0;
}