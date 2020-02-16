#include "Graph.h"
#include <list>
#include <string>
#include <vector>
using namespace std;

Graph::Graph() { }

void Graph::addLink(string A, string B, string C)
{
	//local variables
	int edgeValue = stoi(C);
	Node* Aptr = nullptr;
	Node* Bptr = nullptr;
	Node airport(A);
	Node airport2(B);
	Node* link = nullptr;
	Edge edge(link, edgeValue);

	//base case, after initialization.
	if (airports.size() == 0)
	{
		airports.push_back(airport);
		link = &airports.back();
		unvisited.push_back(link);
		airports.push_back(airport2);
		link = &airports.back();
		unvisited.push_back(link);
		edge.link = link;
		airports.front().destinations.push_back(edge);
		return;
	}
	
	//Adding past base case.
	auto it = find(airports.begin(), airports.end(), airport2); //Local variable declaration

	//If it doesn't exist
	if (it == airports.end())
	{
		airports.push_back(airport2);
		link = &airports.back();
		unvisited.push_back(link);
	}
	else
	{
		link = &(*it);
	}

	it = find(airports.begin(), airports.end(), airport);
	
	//If it doesn't exist
	if (it == airports.end())
	{
		edge.link = link;
		airport.destinations.push_back(edge);
		airports.push_back(airport);
		link = &airports.back();
		unvisited.push_back(link);
	}
	else
	{
		edge.link = link;
		it->destinations.push_back(edge);
	}
}

string Graph::testConnection(string A, string B)
{
	//Local Variables
	string returnVal = "Shortest path to destination is ";
	Node* currentNode = findAirport(A);
	Node* startNode = currentNode;
	Node* nextNode = nullptr;
	int lowestCount = 999999999;
	bool finished = false;
	Node* destinationNode = findAirport(B);

	//same beginning and ending.
	if (A == B)
	{
		return "... You're already there. ";
	}

	if (currentNode == nullptr || destinationNode == nullptr)
	{
		return "Something is incorrect, one of the two airports do not exist.";
	}

	currentNode->distance = 0;

	while (!finished)
	{
		path.push_back(currentNode->name);
		//consider all of its  unvisited neighbors and calculate their tentative distances through the current node
		lowestCount = 999999999;
		for (Edge i : currentNode->destinations)
		{
			if (i.link->distance > currentNode->distance + i.distance)
			{
				i.link->distance = currentNode->distance + i.distance;
			}
			else if (i.link == destinationNode)
			{
				path.pop_back();
			}
		}

		visited.push_back(currentNode);
		unvisited.remove(currentNode);

		//if smallest tentative distance between unvisited nodes is infinity, we are done.
		finished = true;
		for (Node* i : unvisited)
		{
			if (i->distance != 999999999)
			{
				finished = false;
				break;
			}
		}

		//If destination node has been visited, algorithmn is done.
		for (Node* i : visited)
		{
			if (i == destinationNode)
			{
				finished = true;
			}
		}

		//choose next node to be next unvisited node.
		if (!finished)
		{
			lowestCount = 999999999;
			for (Node* i : unvisited)
			{
				if (i->distance < lowestCount)
				{
					lowestCount = i->distance;
					nextNode = i;
				}
			}
			if (nextNode == nullptr)
			{
				finished = true;
			}

			//old, not sure if implementing this right.
			/*for (Edge i : currentNode->destinations)
			{
				auto it = find(unvisited.begin(), unvisited.end(), i.link);
				if (it != unvisited.end() && i.distance < lowestCount)
				{
					lowestCount = i.distance;
					nextNode = i.link;
				}
			}
			if (nextNode == nullptr)
			{
				finished = true;
			}*/

		//set nextnode to currentnode so we move there.
			currentNode = nextNode;
		}
	}

	//Old code to attempt to return path.
	/*for (string i : path)
	{
		returnVal.append(i + " -> ");
	}
	//delete spare ->
	returnVal.erase(returnVal.size() - 2);
	returnVal.erase(returnVal.size() - 1);
	return returnVal;*/

	return to_string(destinationNode->distance);
}

Node* Graph::findAirport(string A)
{
	Node findNode(A);
	auto it = find(airports.begin(), airports.end(), findNode);
	if (it == airports.end())
	{
		return nullptr;
	}
	Node* ptr = &(*it);
	return ptr;
}

bool Node::operator==(const Node& input)
{
	if (input.name == name)
	{
		return true;
	}
	return false;
}
