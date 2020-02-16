#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <list>
#include <vector>
using namespace std;

class Node
{
	friend class Graph;
	friend class Edge;
public:
	bool operator== (const Node& input);
private:
	Node(string A)
	{
		name = A;
	}
	int distance = 999999999; //"infinity" expressed in a finite amount.
	string name;
	list<Edge> destinations;
};

class Edge
{
	friend class Graph;
	friend class Node;
public:
	Edge(Node* l, int d)
	{
		link = l;
		distance = d;
	}
private:
	Node* link;
	int distance;
};

class Graph
{
public:
	Graph(); // It Begins...
	void addLink(string A, string B, string C); //Adds a link between airport A and B, and adds the airport if it does not exist.
	string testConnection(string A, string B); //Tests if you can get from one airport to another using backtracking.
	
private:
	list<Node> airports;
	Node* findAirport(string A); //Find the airport requested and returns a pointer to it.
	vector<string> beenTo; //Vector to prevent going back on our path (AER to X to AER to X to AER to X...)
	list<Node*> unvisited; //Unvisited nodes.
	list<Node*> visited; // Visited nodes, for recovery.
	vector<string> path; // Shortest path to destination.
};



#endif

