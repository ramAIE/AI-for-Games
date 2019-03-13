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
		// check the current node to true
		currentNode->Visited(true);
		// go through all the connections of the current node
		for (auto c : currentNode->GetConnections())
		{
			// if the target node is not visited
			if (!c->GetNodeB()->CheckVisited())
			{
				// push it into the stack
				nodeStack.push(c->GetNodeB());
				// set the parent of the node to be the current node
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
	startNode->SetFScore(0);
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

std::vector<Node*> Graph::AStarThetaStarSearch(Node * startNode, Node * endNode) {
	// reset the properties of all the nodes
	for (auto n : nodes) {
		// set the node g-score to null
		n->SetGScore(NULL);
		// set the node f-score to INF
		n->SetFScore(INFINITY);
		// set the parent of the node to nullptr
		n->SetParent(nullptr);
	}

	// create a open list to store the list of nodes that has not been traversed
	std::list<Node*> openList;
	// create a closed list to store the list of nodes that has been traversed
	std::list<Node*> closedList;

	// create a container to store the path
	std::vector<Node*> path;

	// Set the g-score of startnode to 0
	startNode->SetGScore(0);
	// set the f-score of startnode to 0
	startNode->SetFScore(0);
	startNode->SetParent(nullptr);
	// add startnode to the openlist
	openList.push_back(startNode);

	// while the openlist is not empty
	while (!openList.empty()) {
		// sort the priority queue based on the f-score
		openList.sort(Node::CompareFScore);

		// Let currentnode be the firstnode from the openlist
		Node* currentNode = openList.front();
		
		// if currentnode is same as the endnode
		if (currentNode == endNode) {
			// exit the loop
			break;
		}
		openList.remove(currentNode);
		// add currentNode to the closedlist
		closedList.push_back(currentNode);
		
		// for all the edges 'e' in currentnode connections
		for (auto e : currentNode->GetConnections()) {
			// check if the targetnode of the connection is not in the closedlist
			std::list<Node*>::iterator citer = std::find(closedList.begin(), closedList.end(), e->GetNodeB());
			if (citer == closedList.end()) {
				
				// check if the targetnode of the connection is not in the openlist
				std::list<Node*>::iterator oiter = std::find(openList.begin(), openList.end(), e->GetNodeB());
				if (oiter == openList.end()) {
					// set g-score of targetnode to infinity
					e->GetNodeB()->SetGScore(INFINITY);
					// set parent of targetnode to nullptr
					e->GetNodeB()->SetParent(nullptr);
				}
				
				/*** update vertex ***/

				// let gcost be the gscore of targetnode
				float gTargetNodeCost = e->GetNodeB()->GetGScore();
				
				/*** compute cost ***/

				// any-angle paths, theta*
				// if the target node is in the line of sight of the current node's parent
				if (currentNode->GetParent() && LineOfSight(currentNode->GetParent(), e->GetNodeB())) {
					// find the distance between the current node's parent and the target node
					Vector2 targetDistance = e->GetNodeB()->GetPosition() - currentNode->GetParent()->GetPosition();
					float length = targetDistance.magnitude();
					// check if the current node's parent g-score combined with above distance is less than g-score of targetnode
					if ((currentNode->GetParent()->GetGScore() + length) < gTargetNodeCost) {
						// let parent of the current node be the parent of the targetnode
						e->GetNodeB()->SetParent(currentNode->GetParent());
						// set the g-score of the target node to g-score of the current node's parent combined with the distance between the length
						e->GetNodeB()->SetGScore(currentNode->GetParent()->GetGScore() + length);
					}
				}
				// otherwise,
				else {
					// check if g-score of currentnode combined with the cost of the currentedge connection is less than g-score of targetnode
					if (currentNode->GetGScore() + e->GetCost() < gTargetNodeCost) {
						// let currentnode be the parent of the targetnode
						e->GetNodeB()->SetParent(currentNode);
						// set the g-score of the targetnode to g-score of currentnode combined with other cost
						e->GetNodeB()->SetGScore(currentNode->GetGScore() + e->GetCost());
					}
				}

				/*** compute cost ***/

				// check if g-score of the targetnode is less than gCost
				if (e->GetNodeB()->GetGScore() < gTargetNodeCost) {
					if (oiter != openList.end()) {
						openList.remove(e->GetNodeB());
					}
					// calculate h-score
					Vector2 hDistance = e->GetNodeB()->GetPosition() - endNode->GetPosition();
					float hScore = hDistance.magnitude();
					float cost = e->GetNodeB()->GetGScore() + hScore * 1.075f;
					// set the gscore of the targetnode
					e->GetNodeB()->SetFScore(cost);
					// add the targetnode to the openlist
					openList.push_back(e->GetNodeB());
				}

				/*** update vertex ***/
			}
		}
	}

	// let the currentpathnode be the endnode/goalnode
	Node* currentPathNode = endNode;
	// while currentpathnode is not empty
	while (currentPathNode != nullptr) {
		// push the currentpathnode to the path list
		path.push_back(currentPathNode);
		// get the parent of the current pathnode and assign it to the currentpathnode
		currentPathNode = currentPathNode->GetParent();
	}
	// return the path
	return path;
}

bool Graph::LineOfSight(Node * parentNode, Node * targetNode) {
	// get the position of the parent node
	float x0 = parentNode->GetPosition().m_x;
	float y0 = parentNode->GetPosition().m_y;
	// get the position of the target node
	float x1 = targetNode->GetPosition().m_x;
	float y1 = targetNode->GetPosition().m_y;
	// x distance between the parent node and the target node
	float dx = x1 - x0;
	// y distance between the parent node and the target node
	float dy = y1 - y0;

	float sx = 0.0f;
	float sy = 0.0f;

	float f = 0;

	// if the y-distance is negative
	if (dy < 0.0f) {
		// change y-distance to positive value
		dy = -dy;
		// move down in the negative direction
		sy = -1.0f;
	}
	else {
		// move up in the positive direction
		sy = 1.0f;
	}

	// if the x-distance is negative
	if (dx < 0.0f) {
		// change the x-distance to negative value
		dx = -dx;
		// move left in the negative direction
		sx = -1.0f;
	}
	else {
		// move right in the positive direction
		sx = 1.0f;
	}

	// x-distance is greater than or equal to y-distance
	if (dx >= dy) {
		// loop through to check if the target node is in sight
		while (x0 != x1) {
			f += dy;
			if (f >= dx) {
				y0 += sy;
				f -= dx;
			}
			// the dy is zero, the target node is not in line of sight
			if (dy == 0)
				return false;

			x0 += sx;
		}
	}
	// x-distance is less than y-distance
	else {
		while (y0 != y1) {
			f += dx;
			if (f >= dy) {
				x0 += sx;
				f -= dy;
			}
			// the dx is zero, the target node is not in line of sight
			if (dx == 0)
				return false;

			y0 += sy;
		 }
	}

	return true;
}

Graph::~Graph()
{
	// Release all the nodes on the graph 
	for (auto& node : nodes)
	{
		delete node;
		node = nullptr;
	}

}
