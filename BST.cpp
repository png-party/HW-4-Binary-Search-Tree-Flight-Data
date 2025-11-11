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
	cout << "Total: " << noe << endl;
	cout << "============================" << endl;

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

Node* BST::remove(int landingTime)
{
	cout << "\nRemoving landing time \"" << landingTime <<"\"..." << endl;
	cout << removeNode(root, landingTime) << endl;
	return nullptr;
}

bool BST::search(int landingTime) const
{
	return true;
}

void BST::clearData()
{
	destroyTree(root);
	noe = 0;
}

int BST::nextAvailable(int requestedTime)
{
	return requestedTime;
}

Node* BST::getSmallest(Node* rootNode) const
{
	if (rootNode->left != nullptr) return getSmallest(rootNode->left);
	return rootNode;
}

Node* BST::printInOrder(Node* rootNode) const
{
	if (!rootNode) return nullptr;
	printInOrder(rootNode->left);
	cout << rootNode->time << endl; 
	rootNode->printTime();
	printInOrder(rootNode->right);
}

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
			cout << "==>Time added successfully, root created" << endl;
			return root;
		}
		cout << "==>Error: Memory could not be allocated!" << endl;
		return nullptr;
	}
	//Go left if addTime is smaller
	if (rootNode->time > addTime)
	{
		if (!rootNode->left)
		{
			if(Node* temp = new (nothrow) Node(addTime))
			{
				cout << "Root node: " << rootNode << endl;
				rootNode->left = temp;
				cout << rootNode << "'s left " << rootNode->left << endl;
				cout << "==>Time added successfully" << endl;
				noe++;
				return temp;
			}
			cout << "==>Error: Memory could not be allocated!" << endl;
			return nullptr;
			
		}
		addNode(rootNode->left, addTime);
	}
	//Go right if larger
	{
		if (!rootNode->right)
		{
			if (Node* temp = new (nothrow) Node(addTime)) {
				cout << "Root node: " << rootNode << endl;
				rootNode->right = temp;
				cout << rootNode << "'s right " << rootNode->right << endl;
				cout << "==>Time added successfully" << endl;
				noe++;
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
	/* Base Case */
	if (!current)
	{
		cout << "==>The specified time was not found!" << endl;
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

Node* BST::copyAll(const Node* otherRoot)
{
	if (!otherRoot) return nullptr;
	if (Node* copy = new (nothrow) Node(otherRoot->time))
	{
		copy->left = copyAll(otherRoot->left);
		copy->right = copyAll(otherRoot->right);
		return copy;
	}
}

void BST::destroyTree(Node* root)
{
	if (root == nullptr) return;
	destroyTree(root->left);
	destroyTree(root->right);

	delete root;
}

void BST::levelOrderRec(Node* root2, int level, vector<vector<string>>& res) {
	// Base case
	if (root2 == nullptr) return;

	// Add a new level to the result if needed
	if (res.size() <= level)
		res.push_back({});

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
						string s2((res[i-1].size()), ' ');
						cout << val << s2;
					}
					else cout << val << "  ";
				}
				cout << endl;
			
		}
		cout << "\n===========================" << endl;
}
