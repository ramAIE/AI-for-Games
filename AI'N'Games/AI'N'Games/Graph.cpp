#include "Graph.h"
#include <Renderer2D.h>
#include <stack>

Graph::Graph()
{
}

void Graph::AddNode(Node * node)
{
	nodes.push_back(node);
}

void Graph::ConnectNode(Node * a, Node * b)
{
	a->SetConnection(a, b, 10.0f);
}

void Graph::draw(aie::Renderer2D * renderer)
{
	for (auto node : nodes)
	{
		for (auto it : node->GetConnections())
		{
			Edge* edge = it;
			renderer->setRenderColour(1, 1, 1, 1);
			renderer->drawLine(node->GetPosition().m_x, node->GetPosition().m_y,
								edge->GetNodeB()->GetPosition().m_x, edge->GetNodeB()->GetPosition().m_y);
		}
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

	return std::vector<Node*>();
}


Graph::~Graph()
{
	for (auto& node : nodes)
	{
		delete node;
		node = nullptr;
	}

}
