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
	printInOrder(root);
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
	if (rootNode == nullptr) return nullptr;
	printInOrder(rootNode->left);
	rootNode->printTime();
	printInOrder(rootNode->right);
}

Node* BST::addNode(Node* rootNode, int addTime)
{
	//Check if adding the first node
	if (!root)
	{
		/*The nothrow argument with the new operator prevents
		 *an error from being thrown if memory allocation fails
		 *Instead, it sets the pointer to nullptr*/
		if (Node* temp = new (nothrow) Node(addTime)) root = temp;
		else cout << "Memory could not be allocated!" << endl;
		return nullptr;
	}
	//Go left if smaller
	if (rootNode->time > addTime)
	{
		if (!rootNode->left)
		{
			if(Node* temp = new (nothrow) Node(addTime))
			{
				rootNode->left = temp;
				return temp;
			}
			cout << "Memory could not be allocated!" << endl;
		}
		else addNode(rootNode->left, addTime);
	}
		
	//Go right if larger
	if (rootNode->time < addTime)
	{
		if (!rootNode->right)
		{
			if (Node* temp = new (nothrow) Node(addTime)) {
				rootNode->right = temp;
				return temp;
			}
			cout << "Memory could not be allocated!" << endl;
		}
		else addNode(rootNode->right, addTime);
	}
		

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
