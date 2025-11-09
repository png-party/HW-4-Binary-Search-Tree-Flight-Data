#include "BST.h"
#include <iostream>
using namespace std;
BST::BST()
{
	root = nullptr;
	noe = 0;
}

BST::~BST()
{
	destroyTree(root);
}

BST::BST(const BST& other)
{
}

BST& BST::operator=(const BST& other)
{
}

BST::BST(BST&& other) noexcept
{
}

BST& BST::operator=(BST&& other) noexcept
{
}

void BST::printSchedule()
{
}

void BST::insert(int landingTime)
{
	addNode(root, landingTime);
}

bool BST::remove(int landingTime)
{
}

bool BST::search(int landingTime) const
{
}

int BST::nextAvailable(int requestedTime)
{
}

Node* BST::printInOrder(Node* rootNode)
{
	printInOrder(rootNode->left);
	cout << rootNode << endl;
	printInOrder(rootNode->right);
}

Node* BST::addNode(Node* rootNode, int addTime)
{
	//Check if adding the first node
	if (!root)
	{
		if (Node* temp = new Node(addTime)) root = temp;
		else cout << "Memory could not be allocated!" << endl;
		return nullptr;
	} 
	//Go left if smaller
	//Go right if larger
}

Node* BST::removeNode(Node* root, int removeTime)
{
}

Node* BST::destroyTree(Node* rootNode)
{
	destroyTree(rootNode->left);
	destroyTree(rootNode->right);
	delete rootNode;
}
