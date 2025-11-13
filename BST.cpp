#include "BST.h"
#include <iostream>
#include <ios>
#include <vector>
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
	else root = nullptr;
}

/* Overloaded assignment operator */
BST& BST::operator=(const BST& other)
{
	if (this != &other)
	{
		destroyTree(root);
		noe = other.noe;
		if (other.root) root = copyAll(other.root);
		else root = nullptr;
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

void BST::printSchedule() const
{
	cout << "\n===Scheduled Flight Times===" << endl;
	printInOrder(root);
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
	int checkedTime = Node::verifyTime(landingTime);
	if (checkedTime != landingTime) cout << "==>Invalid time adjusted from " << landingTime << " to " << checkedTime << endl;
	return addNode(root, checkedTime);
}

bool BST::remove(int landingTime)
{
	cout << "\nRemoving landing time \"" << landingTime <<"\"..." << endl;
	return removeNode(root, landingTime);
}

bool BST::search(int landingTime) const
{
	cout << "\nSearching for landing time \"" << landingTime << "\"..." << endl;
	Node* found = getNode(root, landingTime);
	if (found) cout << "Time "<< found << " was successfully found!" << endl;
	else cout << "Time << " << landingTime << " was not found" << endl;
	return found;
}

void BST::clearData()
{
	destroyTree(root);
	noe = 0;
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
 * It finds the minimum possible time from the collusion node
 * If the time is before noon, it looks for later time slots
 * If the time is after noon, it looks for earlier time slots */
int BST::nextAvailable(int requestedTime, int collisionTime) const
{
	if (requestedTime == 0) requestedTime = 2359;
	int difference = 6 - abs(requestedTime - collisionTime);
	if (requestedTime <= 2359 / 2) return Node::verifyTime(requestedTime + difference);
	if (requestedTime >= 2359 / 2) return Node::verifyTime(requestedTime - difference);
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
		if (Node* temp = new (nothrow) Node(addTime)) {
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
	int count = noe;
	while (count >= 0)
	{
		/* Check each node visited for potential collisions */
		if (std::abs(addTime - rootNode->time) <= 5)
		{
			cout << "==>Flight collision detected! " << addTime << " is within 5 minutes of another flight at " << rootNode << endl;
			/* Select the closest time and start inserting from the root */
			int offset = nextAvailable(addTime, rootNode->time);
			rootNode = root;
			cout << "Attempting to book " << offset << " instead...\n" << endl;
			return addNode(rootNode, offset);
		}
		// Go left if addTime is smaller than current
		if (addTime < rootNode->time) {
			if (!rootNode->left) break;
			rootNode = rootNode->left;
		}
		// Go right if addTime is larger than current
		else if (addTime > rootNode->time) {
			if (!rootNode->right) break;
			rootNode = rootNode->right;
		}
		count--;
	}
	/* Once a valid spot is found, add the node there */
	if (std::abs(addTime - rootNode->time) > 5)
	{
		if (Node* temp = new (nothrow) Node(addTime))
		{
			cout << "Root node: " << rootNode << endl;
			if (rootNode->time > addTime) rootNode->left = temp;
			else rootNode->right = temp;
			cout << "==>Flight time " << temp << " booked successfully" << endl;
			noe++;
			return temp;
		}
		cout << "==>Error: Memory could not be allocated!" << endl;
		return nullptr;
	}
	return nullptr;
}

/* Private helper method for remove() */
Node* BST::getSmallest(Node* rootNode) const
{
	if (rootNode->left != nullptr) return getSmallest(rootNode->left);
	return rootNode;
}

/* Private helper method for remove() */
Node* BST::removeNode(Node* current, int removeValue)
{
	/* Base Case */
	if (!current)
	{
		cout << "==>The specified time could not be found and removed" << endl;
		return nullptr;
	}

	/* Case 1: Tree is empty */
	if (!root)
	{
		cout << "==>The tree is empty, nothing to remove" << endl;
		return nullptr;
	}

	/* Case 2: RemoveValue is stored in the root */
	if (root->time == removeValue)
	{
		cout << "RemoveValue is stored in the root" << endl;
		Node* toDelete = root;

		/* Case 2A: Root contains a right child (and maybe a left child) */
		if (Node* rightChild = toDelete->right)
		{
			//If there is also a left child, attach it to rightChild's leftmost node
			if (Node* leftChild = toDelete->left) {
				
				Node* smallest = getSmallest(rightChild);
				smallest->left = leftChild;
			}
			//Make right the new root
			root = rightChild;
		}

		/* Case 2B: Root only contains a left child */
		else if (root->left)
		{
			//Make left the new root
			root = root->left;
		}
		cout << "==>The specified time was successfully removed, root node updated" << endl;
		noe--;
		delete toDelete;
		return root;
	}

	/* Case 3: Current node contains removeValue */
	if (current->time == removeValue)
	{
		Node* toDelete = current;
		/* Case 3A: Contains right child (and maybe left) */
		if (Node* rightChild = toDelete->right)
		{
			if (Node* leftChild = toDelete->left)
			{
				Node* smallest = getSmallest(rightChild);
				cout << "Smallest node on the right is " << smallest << endl;
				smallest->left = leftChild;
				cout << smallest << "'s left is now " << leftChild << endl;
			}
			current = rightChild;
		}
		/* Case 3B: Only contains a left child */
		else if (Node* leftChild = toDelete->left) current = leftChild;
		/* Case 3C: Current is a leaf so we set it to nullptr */
		else current = nullptr;

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
	if (removeValue > current->time) {
		current->right = removeNode(current->right, removeValue);
		return current;
	}
}

/* Private helper method for the copy constructor and overloaded assignment operator */
Node* BST::copyAll(const Node* otherRoot)
{
	if (!otherRoot) return nullptr;
	if (Node* copy = new (nothrow) Node(otherRoot->time))
	{
		copy->left = copyAll(otherRoot->left);
		copy->right = copyAll(otherRoot->right);
		return copy;
	}
	cout << "==>Error: Memory could not be initialized" << endl;
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

void BST::levelOrderRec(Node* root2, int level, vector<vector<string>>& res) {
	// Base case

	// Add a new level to the result if needed
	if (res.size() <= level)
		res.push_back({});
	if (root2 == nullptr)
	{
		res[level].push_back("Xx:xX");
		return;
	}

	// Add current node's data to its corresponding level
	res[level].push_back(root2->getTimeString());

	// Recur for left and right children
	levelOrderRec(root2->left, level + 1, res);
	levelOrderRec(root2->right, level + 1, res);
}

// Function to perform level order traversal
vector<vector<string>> BST::levelOrder(Node* root2) {

	// Stores the result level by level
	vector<vector<string>> res;

	levelOrderRec(root2, 0, res);
	return res;
}

void BST::printLevel()
{
	cout << "\n===========================" << endl;
	vector<vector<string>> res = levelOrder(root);
		for (int i = 0; i < (int)res.size(); i++)
		{
			string s((res.size() - i)*2 , ' ');
			cout << s;
				for (string val : res[i]) {
					if (i !=0)
					{
						//string s2((res[i-1].size()), ' ');
						cout << val << "  ";
					}
					else cout << val << "";
				}
				cout << endl;
			
		}
		cout << "\n===========================" << endl;
}
