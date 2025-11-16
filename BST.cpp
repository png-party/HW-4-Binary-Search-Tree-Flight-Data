/*
 *	Nicole Sirbu
 *	CMPR-131
 *	2025-11-12
 *	Homework #4
 *  Collaboration:
 *https://www.geeksforgeeks.org/cpp/if-memory-allocation-using-new-is-failed-in-c-then-how-it-should-be-handled/
 */
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
	root = copyAll(other.root);
}

/* Overloaded assignment operator */
BST& BST::operator=(const BST& other)
{
	if (this != &other)
	{
		destroyTree(root);
		noe = other.noe;
		root = copyAll(other.root);
	}
	else cout << "Attempting self-assignment!" << endl;
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
	}
	else cout << "Attempting self-assignment!" << endl;
	return *this;
}

void BST::printSchedule() const
{
	cout << "\n===Scheduled Flight Times===" << endl;
	if (!root) cout << "No flights booked" << endl;
	else printInOrder(root);
	cout << "============================" << endl;
	cout << "Total Flights: " << noe << endl;
	cout << "============================" << endl;
}

/* The insert and remove methods will return true
 * if addNode() and removeNode() return a valid pointer
 * otherwise, they will return false if their private
 * methods return nullptr, meaning their operations
 * were unsuccessful */
bool BST::insert(int landingTime)
{
	cout << "\nAdding landing time \"" << landingTime << "\"..." << endl;
	int checkedTime = Time::verifyTime(landingTime);
	return addNode(root, checkedTime);
}

bool BST::remove(int landingTime)
{
	cout << "\nRemoving landing time \"" << landingTime << "\"..." << endl;
	return removeNode(root, landingTime);
}

bool BST::search(int landingTime) const
{
	cout << "\nSearching for landing time \"" << landingTime << "\"..." << endl;
	Node* found = getNode(root, landingTime);
	if (found) cout << "Time " << found << " was successfully found!" << endl;
	else cout << "Time << " << landingTime << " was not found" << endl;
	return found;
}

void BST::clearData()
{
	destroyTree(root);
	noe = 0;
	root = nullptr;
	cout << "Clearing all flights..." << endl;
}

/* Private helper method for printSchedule() */
Node* BST::printInOrder(Node* rootNode) const
{
	if (!rootNode) return nullptr;
	printInOrder(rootNode->left);
	rootNode->printTime();
	printInOrder(rootNode->right);
}

/* Private helper method for search() */
Node* BST::getNode(Node* rootNode, int toFind) const
{
	if (!rootNode) return nullptr;
	if (toFind == rootNode->time) return rootNode;
	if (toFind > rootNode->time) getNode(rootNode->right, toFind);
	if (toFind < rootNode->time) getNode(rootNode->left, toFind);
}

/* Private helper method for insert()
 * It is called when a collision is detected
 * It finds the minimum possible time from the collusion node */
int BST::nextAvailable(int requestedTime, Node* collisionTime) const
{
	int offset = Time::addTimes(collisionTime->date, 6);
	if (offset == 2359)
	{
		Time temp = Time(0);
		return Time::addTimes(temp, 6);
	}
	return offset;
}

/* Private helper method for insert() */
Node* BST::addNode(Node* rootNode, int addTime)
{
	//Check if adding the first node
	if (!root)
	{
		/* The nothrow argument with the new operator prevents
		 * an error from being thrown if memory allocation fails
		 * Instead, it sets the pointer to nullptr  */
		if (Node* temp = new(nothrow) Node(addTime))
		{
			root = temp;
			noe = 1;
			cout << "==>Flight booked successfully, root created" << endl;
			return root;
		}
		cout << "==>Error: Memory could not be allocated!" << endl;
		return nullptr;
	}
	if (!rootNode) return nullptr;

	/* Traverse the tree to find a suitable spot to add the node */
	while (rootNode)
	{
		/* Check each node visited for potential collisions */
		if (Time::subtractTimes(addTime, rootNode->date) <= 5)
		{
			cout << "==>Flight collision detected! " << addTime << " is within 5 minutes of another flight at " <<
				rootNode << endl;

			/* If there is a collision, select the closest time and start inserting from the root */
			int offset = nextAvailable(addTime, rootNode);
			rootNode = root;
			cout << "Attempting to book " << offset << " instead...\n" << endl;
			return addNode(rootNode, offset);
		}
		// Go left if addTime is smaller than current
		if (addTime < rootNode->time)
		{
			if (!rootNode->left) break;
			rootNode = rootNode->left;
		}
		// Go right if addTime is larger than current
		else if (addTime > rootNode->time)
		{
			if (!rootNode->right) break;
			rootNode = rootNode->right;
		}
	}

	/* Once a valid spot is found, add the node there */
	if (Time::subtractTimes(addTime, rootNode->date) > 5)
	{
		if (Node* temp = new(nothrow) Node(addTime))
		{
			if (rootNode->time > addTime) rootNode->left = temp;
			else rootNode->right = temp;
			cout << "==>Flight time " << temp << " booked successfully" << endl;
			noe++;
			return temp;
		}
		cout << "==>Error: Memory could not be allocated!" << endl;
	}
	return nullptr;
}

/* Private helper method for remove() */
Node* BST::getSmallest(Node* rootNode) const
{
	if (rootNode->left) return getSmallest(rootNode->left);
	return rootNode;
}

/* Private helper method for remove() */
Node* BST::removeNode(Node* current, int removeValue)
{
	/* Case 1: Tree is empty or value wasn't found */
	if (!current)
	{
		if (!root) cout << "==>The tree is empty, nothing to remove" << endl;
		else cout << "==>The specified time could not be found and removed" << endl;
		return nullptr;
	}
	/* Case 2: Current node contains removeValue */
	if (current->time == removeValue)
	{
		Node* toDelete = current;
		/* Case 2A: Contains right child (and maybe left) */
		if (Node* rightChild = toDelete->right)
		{
			if (Node* leftChild = toDelete->left)
			{
				Node* smallest = getSmallest(rightChild);
				smallest->left = leftChild;
			}
			current = rightChild;
		}
		/* Case 2B: Only contains a left child */
		else if (Node* leftChild = toDelete->left) current = leftChild;
			/* Case 2C: Current is a leaf so we set it to nullptr */
		else current = nullptr;
		/* Case 3D: Deleting the root */
		if (root->time == removeValue)
		{
			root = current;
			cout << "==>The specified time was successfully removed, root node updated" << endl;
		}
		else cout << "==>The specified time was found and removed" << endl;
		noe--;
		delete toDelete;
		return current;
	}

	//Go left if removeValue is smaller than current
	if (removeValue < current->time)
	{
		current->left = removeNode(current->left, removeValue);
		return current;
	}

	//Go right if removeValue is larger than current
	if (removeValue > current->time)
	{
		current->right = removeNode(current->right, removeValue);
		return current;
	}
}

/* Private helper method for the copy constructor and overloaded assignment operator */
Node* BST::copyAll(const Node* otherRoot)
{
	if (otherRoot)
	{
		if (Node* copy = new(nothrow) Node(otherRoot->date.getTime()))
		{
			copy->left = copyAll(otherRoot->left);
			copy->right = copyAll(otherRoot->right);
			return copy;
		}
		cout << "==>Error: Memory could not be initialized" << endl;
	}
	return nullptr;
}

/* Private helper method for clearData() */
void BST::destroyTree(Node* root)
{
	//Traverse in postOrder
	if (root == nullptr) return;
	destroyTree(root->left);
	destroyTree(root->right);

	delete root;
}
