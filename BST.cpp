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

/* Copy constructor */
BST::BST(const BST& other)
{
	noe = other.noe;
	if (other.root) root = copyAll(other.root);
	
}

/* Overloaded assignment operator */
BST& BST::operator=(const BST& other)
{
	if (this != &other)
	{
		destroyTree(root);
	}
	return *this;
}

/* Move constructor */
BST::BST(BST&& other) noexcept
{
	root = other.root;
	noe = other.noe;
	other.root = nullptr;
	other.noe = 0;
}

/* Move assignment operator */
BST& BST::operator=(BST&& other) noexcept
{
	if (this != &other)
	{
		destroyTree(root);
		root = other.root;
		noe = other.noe;

		other.root = nullptr;
		other.noe = 0;

	} else cout << "Attempting self-assignment!" << endl;
	return *this;
}

void BST::printSchedule()
{
	printInOrder(root);
}

/* The insert and remove methods will return true
 * if addNode() and removeNode() return a valid pointer
 * otherwise, they will return false if their private
 * methods return nullptr, meaning their operations
 * were unsuccessful */
bool BST::insert(int landingTime)
{
	cout << "\nAdding landing time..." << endl;
	return addNode(root, landingTime);
}

bool BST::remove(int landingTime)
{
	cout << "\nRemoving landing time..." << endl;
	return removeNode(root, landingTime);
}

bool BST::search(int landingTime) const
{
}

void BST::clearData()
{

}

int BST::nextAvailable(int requestedTime)
{
}

Node* BST::getSmallest(Node* rootNode) const
{
	if (rootNode->left) getSmallest(rootNode);
	return rootNode;
}

Node* BST::printInOrder(Node* rootNode)
{
	if (!rootNode) return nullptr;
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
		if (Node* temp = new (nothrow) Node(addTime)) {
			root = temp;
			cout << "==>Time added successfully, root created" << endl;
			return root;
		}
		cout << "==>Error: Memory could not be allocated!" << endl;
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
				cout << "==>Time added successfully" << endl;
				return temp;
			}
			cout << "==>Error: Memory could not be allocated!" << endl;
			return nullptr;
			
		}
		addNode(rootNode->left, addTime);
	}
		
	//Go right if larger
	if (rootNode->time < addTime)
	{
		if (!rootNode->right)
		{
			if (Node* temp = new (nothrow) Node(addTime)) {
				rootNode->right = temp;
				cout << "==>Time added successfully" << endl;
				return temp;
			}
			cout << "Memory could not be allocated!" << endl;
			return nullptr;
		}
		addNode(rootNode->right, addTime);
	}
}

Node* BST::removeNode(Node* current, int removeValue)
{
	/* Case 1: Tree is empty */
	if (!root)
	{
		cout << "==>The tree is empty, nothing to remove" << endl;
		return nullptr;
	}

	/* Case 2: RemoveValue is stored in the root */
	if (root->time == removeValue)
	{
		Node* toDelete = root;
		/* Case 2A: Root contains a right child (and maybe a left child) */
		if (Node* rightChild = toDelete->right)
		{
			//If there is also a left child, attach it to rightChild's leftmost node
			if (Node* leftChild = toDelete->left) getSmallest(rightChild)->left = leftChild;
			root = rightChild;
		}
		/* Case 2B: Root only contains a left child */
		if (!root->right && root->left)
		{
			root = root->left;
		}
		cout << "==>The specified time was successfully removed, root node updated" << endl;
		delete toDelete;
		return root;
	}

	/* Case 3: removeValue is stored in a left node
	 * Check the current node's left and right children for removeValue */
	if (current->left->time == removeValue)
	{
		Node* toDelete = current->left;
		/* Check if toDelete has children before destroying it
		 * Case 3A: Contains a right child (and maybe a left child) */
		if (Node* rightChild = toDelete->right)
		{
			//If there is also a left child, attach it to rightChild's leftmost node
			if (Node* leftChild = toDelete->left) getSmallest(rightChild)->left = leftChild;

			//Attach the subtree onto the left of the current node
			current->left = rightChild;
		}
		/* Case 3B: only contains a left child */
		else if (!toDelete->right && toDelete->left)
		{
			//Get the left child
			Node* leftChild = toDelete->left;
			//Attach the node/subtree onto the left of the current node
			current->left = leftChild;
		}
		delete toDelete;
		cout << "==>The specified time was successfully removed!" << endl;
		return current;
	}

	/* Case 4: removeValue is stored in a right node */
	if (current->right->time == removeValue) 
	{
		Node* toDelete = current->right;
		/* Check if toDelete has children before destroying it
		 * Case 4A: Contains a right child (and maybe a left child) */
		if (Node* rightChild = toDelete->right)
		{
			//If there is also a left child, attach below to rightChild's leftmost node
			if (Node* leftChild = toDelete->left) getSmallest(rightChild)->left = leftChild;

			//Attach toDelete's rightChild to current's right
			current->right = rightChild;
		}
		/* Case 4B: Only contains a left child*/
		else if (!toDelete->right && toDelete->left)
		{
			//toDelete's left child will now be used as current's right
			Node* leftChild = toDelete->left;
			//Attach toDelete's leftChild to current's right
			current->right = leftChild;
		}
		//Finally, remove the node
		delete toDelete;
		cout << "==>The specified time was successfully removed!" << endl;
		return current;
	}
	//Go left if current time is larger than target 
	if (current->time < removeValue) removeNode(current->left, removeValue);
	//Go right if current time is smaller than target
	if (current->time > removeValue) removeNode(current->right, removeValue);
	return nullptr;
}

Node* BST::copyAll(const Node* otherRoot)
{
	if (Node* copy = new (nothrow) Node(otherRoot->time))
	{
		copy->left = copyAll(otherRoot->left);
		copy->right = copyAll(otherRoot->right);
		return copy;
	}
	return nullptr;
}

void BST::destroyTree(Node* rootNode)
{
	if (rootNode)
	{
		destroyTree(rootNode->left);
		destroyTree(rootNode->right);
		delete rootNode;
	}
}
