#include "Graph.h"
#include <Renderer2D.h>
#include <stack>
#include <list>

Graph::Graph()
{
}

void Graph::AddNode(Node * node)
{
	nodes.push_back(node);
}

void Graph::ConnectNode(Node * a, Node * b, float cost)
{
	a->SetConnection(a, b, cost);
}

void Graph::draw(aie::Renderer2D * renderer)
{
	for (auto node : nodes)
	{
		renderer->setRenderColour(1, 1, 1, 1);
		for (auto it : node->GetConnections())
		{
			Edge* edge = it;
			renderer->setRenderColour(1, 1, 1, 1);
			renderer->drawLine(node->GetPosition().m_x, node->GetPosition().m_y,
								edge->GetNodeB()->GetPosition().m_x, edge->GetNodeB()->GetPosition().m_y);
		}
		if (node->highlighted == true)
			renderer->setRenderColour(0, 1, 0, 1);

		renderer->drawBox(node->GetPosition().m_x, node->GetPosition().m_y, 10, 10);
	}
}

std::vector<Node*> Graph::GetNodes()
{
	return nodes;
}

std::vector<Node*> Graph::DFS(Node * startNode, Node * endNode)
{
	// create a stack to store the nodes
	std::stack<Node*> nodeStack;
	// push the first node on to the stack
	nodeStack.push(startNode);
	// while the stack is not empty
	while (!nodeStack.empty())
	{
		// get the top node off the stack and remove it
		Node* currentNode = nodeStack.top();
		nodeStack.pop();
		currentNode->Visited(true);
		for (auto c : currentNode->GetConnections())
		{
			if (!c->GetNodeB()->CheckVisited())
			{
				nodeStack.push(c->GetNodeB());
				c->GetNodeB()->SetParent(currentNode);
			}
		}
	}

	std::vector<Node*> path;
	Node* currentPathNode = endNode;
	while (currentPathNode != NULL)
	{
		path.push_back(currentPathNode);
		currentPathNode = currentPathNode->GetParent();
	}

	return path;
}

std::vector<Node*> Graph::DjikstraSearch(Node * startNode, Node * endNode)
{
	// set all parent to null and all the gscore to infinity
	for (auto n : nodes)
	{
		// all the gscore to infinity
		n->SetGScore(INFINITY);
		// set all parent to null
		n->SetParent(nullptr);
	}
	// set up the priority queue
	std::list<Node*> nodePrQueue;
	// set the parent to itself <- don't do this, set it to nullptr
	startNode->SetParent(nullptr);
	// set the gscore to 0
	startNode->SetGScore(0);
	// push the first node on to the priority queue
	nodePrQueue.push_back(startNode);
	// check if the priority queue is not empty
	while (!nodePrQueue.empty())
	{
		// sorts the node based on the gscore
		nodePrQueue.sort(Node::CompareGScore);
		// Get the current node at the end of the queue
		Node* currentNode = nodePrQueue.front();

		if (currentNode == endNode)
			break;

		// remove it from the queue
		nodePrQueue.remove(currentNode);
		// set the currentNode to be traversed
		currentNode->Visited(true);
		// loop through its connection
		for (auto c : currentNode->GetConnections())
		{
			if (!c->GetNodeB()->CheckVisited())
			{
				// add the currentnode Gscore to the edge cost
				float cost = currentNode->GetGScore() + c->GetCost();
				// if the cost is less than the existing g cost in the end node
				if (cost < c->GetNodeB()->GetGScore())
				{
					// set the end node parent to the current node
					c->GetNodeB()->SetParent(currentNode);
					// set the end node g-score to the currentnode g-score + edge cost
					c->GetNodeB()->SetGScore(currentNode->GetGScore() + c->GetCost());
				}
				// push the end node on to the queue
				nodePrQueue.push_back(c->GetNodeB());
			}
		}
	}
	// path of the node
	std::vector<Node*> path;
	// setting the final node to the the current path node
	Node* currentPathNode = endNode;
	// loop backwards to find the path 
	while (currentPathNode != nullptr)
	{
		// push the current node into the path
		path.push_back(currentPathNode);
		currentPathNode = currentPathNode->GetParent();
	}
	return path;
}

std::vector<Node*> Graph::AStarSearch(Node * startNode, Node * endNode)
{
	// set the parent node of all the nodes to null and set all the g-score to infinity
	for (auto n : nodes)
	{
		n->SetParent(nullptr);
		n->SetGScore(NULL);
		n->SetFScore(INFINITY);
	}
	// set up the priority queue
	std::list<Node*> priorityQueue;
	// set the start node parent to nullptr
	startNode->SetParent(nullptr);
	// set the start node gscore to 0
	startNode->SetGScore(0);
	// push start node on to the priority queue
	priorityQueue.push_back(startNode);
	// while queue is not empty
	while (!priorityQueue.empty())
	{
		// sort the priority queue based on the f-score
		priorityQueue.sort(Node::CompareFScore);
		// Get the current Node off the end of the queue
		Node* currentNode = priorityQueue.front();
		// remove the current node from the queue
		priorityQueue.remove(currentNode);
		// mark it traversed
		currentNode->Visited(true);
		// loop through the current node edges
		for (auto e : currentNode->GetConnections())
		{
			// if end node is not traversed
			if (!e->GetNodeB()->CheckVisited())
			{
				// heuristic score of current node to end node
				Vector2 dist = e->GetNodeB()->GetPosition() - endNode->GetPosition();
				float hScore = sqrtf(dist.m_x * dist.m_x + dist.m_y * dist.m_y);
				// Calculate current node’s g-score + the edge cost + heuristic of end node
				float cost = currentNode->GetGScore() + e->GetCost() + hScore;
				// if cost is less than the node connected to the edge
				if (cost < e->GetNodeB()->GetFScore())
				{
					// set the parent connected to the edge to current node
					e->GetNodeB()->SetParent(currentNode);
					// set the f-score connected to the edge to current node g-score + edge cost + heuristic score
					e->GetNodeB()->SetFScore(cost);
					// push the target node to the queue
					priorityQueue.push_back(e->GetNodeB());
				}
			}
		}
	}

	std::vector<Node*> path;
	// setting the final node to the the current path node
	Node* currentPathNode = endNode;
	// loop backwards to find the path 
	while (currentPathNode != nullptr)
	{
		// push the current node into the path
		path.push_back(currentPathNode);
		currentPathNode = currentPathNode->GetParent();
	}
	return path;
}


Graph::~Graph()
{
	for (auto& node : nodes)
	{
		delete node;
		node = nullptr;
	}

}