
#pragma once
#ifndef BST_H
#define BST_H
#include <iostream>
#include <ostream>
#include <random>
#include <string>
#include <vector>
using namespace std;
struct Node
{
	int time;
	Node* left; //Less than parent
	Node* right; //Greater than parent

	Node(int landingTime)
	{
		time = landingTime;
		left = nullptr;
		right = nullptr;
	}

	/* Prevent setting nodes with invalid times
	 * and will adjust the time as needed 
	 * Ranges:
		 * 0 <= hours <= 23
		 * 0 <= minutes <= 59*/

	/* Hours and minutes are rounded up or down separately
	 * For example:
		 * 24:15 - > 23:15
		 * 9:99 - > 9:59
	 * This is static because it will be used in the BST class
	 * before creating nodes while checking for collisions */
	static int verifyTime(int landingTime)
	{
		//Prevent negative values
		landingTime = abs(landingTime);
		return getHours(landingTime) * 100 + getMinutes(landingTime);
	}
	/* Returns the node's time as a string and pads numbers with zeroes
	 * It doesn't use getHours() or getMinutes() since it doesn't
	 * need to round/validate the time if the node was already created */
	string getTimeString() const
	{
		int temp = time;

		int minutes = temp % 10;
		temp /= 10;
		minutes += (temp % 10) * 10;
		temp /= 10;


		int hours = temp % 10;
		temp /= 10;
		if (temp > 0) hours += temp % 10 * 10;

		string padHours = (hours < 10) ? "0" : "";
		string padMinutes = (minutes < 10) ? "0" : "";
		return padHours + to_string(hours) + ":" + padMinutes + to_string(minutes);
	}

	void printTime() const
	{
		cout << "Landing Time: " << getTimeString() << endl;
	}

	/* Helper methods for validating hours and minutes */
	 static int getMinutes(int landingTime)
	{
		//Get the first two digits
		int minutes = landingTime % 10;
		landingTime /= 10;
		minutes += (landingTime % 10) * 10;

		//Round down if minutes are over 59
		return (minutes > 59) ? 59 : minutes;
	}

	static int getHours(int landingTime)
	{
		//Get the 3rd digit
		landingTime /= 100;
		int hours = landingTime % 10;
		landingTime /= 10;
		//Get the 4th digit if it exists
		if (landingTime > 0) hours += landingTime % 10 * 10;
		//Round down if hours are over 23
		return (hours > 23) ? 23 : hours;
	}
};

/* Overloaded stream insertion operators for Node objects and pointers */
inline ostream& operator<<(ostream& out, const Node* other)
{
	if (!other) out << "Null value" << endl;
	else out << other->getTimeString();
	return out;
}

inline ostream& operator<<(ostream& out, const Node& other)
{
	out << other.getTimeString();
	return out;
}

class BST
{


public:
	Node* root;
	int noe;
	BST();
	/*==The Big 5==*/
	//Destructor
	~BST();
	//Copy constructor
	BST(const BST& other);
	//Overloaded assignment operator
	BST& operator=(const BST& other);
	//Move constructor
	BST(BST&& other) noexcept;
	//Move operator
	BST& operator=(BST&& other) noexcept;

	void printSchedule() const;
	bool search(int landingTime) const;
	bool insert(int landingTime);
	bool remove(int landingTime);
	void clearData();

//private:
	Node* printInOrder(Node* rootNode) const;
	Node* getNode(Node* rootNode, int toFind) const;
	int nextAvailable(int requestedTime, int collisionTime) const;
	Node* addNode(Node* rootNode, int addTime);
	Node* getSmallest(Node* rootNode) const;
	Node* removeNode(Node* current, int removeValue);
	Node* copyAll(const Node* otherRoot);
	void destroyTree(Node* rootNode);
	void levelOrderRec(Node* root2, int level, vector<vector<string>>& res);
	vector<vector<string>> levelOrder(Node* root2);
	void printLevel();
};

#endif