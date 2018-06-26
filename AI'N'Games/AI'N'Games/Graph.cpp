#include "Graph.h"
#include <Renderer2D.h>

Graph::Graph()
{
}

void Graph::AddNode(Node * node)
{
	nodes.push_back(node);
}

void Graph::ConnectNode(Node * a, Node * b)
{
	Edge* edge = new Edge();
	edge->SetNodeA(a);
	edge->SetNodeB(b);
	a->SetConnection(edge);
}

void Graph::draw(aie::Renderer2D * renderer)
{
	for (auto node : nodes)
	{
		for (std::vector<Edge*>::iterator it = node->GetConnections().begin(); it != node->GetConnections().end(); ++it)
		{
			Edge* edge = *it;
			renderer->setRenderColour(1, 1, 1, 1);
			renderer->drawLine(edge->GetNodeA()->GetPosition().m_x, edge->GetNodeA()->GetPosition().m_y,
								edge->GetNodeB()->GetPosition().m_y, edge->GetNodeB()->GetPosition().m_y);
		}
		renderer->drawBox(node->GetPosition().m_x, node->GetPosition().m_y, 10, 10);
	}
}


Graph::~Graph()
{
	for (auto node : nodes)
		delete node;
}
