/*
 *	Nicole Sirbu
 *	CMPR-131
 *	2025-11-12
 *	Homework #4
 *  Collaboration:
 *https://www.geeksforgeeks.org/cpp/if-memory-allocation-using-new-is-failed-in-c-then-how-it-should-be-handled/
 */
#pragma once
#ifndef BST_H
#define BST_H
#include <iostream>
#include <ostream>
#include <string>
#include "Time.h"
using namespace std;
class Time;

struct Node
{
	Time date;
	int time;
	Node* left; //Less than parent
	Node* right; //Greater than parent

	Node(int landingTime)
	{
		date = Time(landingTime);
		time = date.getTime();
		left = nullptr;
		right = nullptr;
	}

	/* Returns the node's time as a string and pads numbers with zeroes
	 * and uses the getTimeString method from the Time class */
	string getTimeString() const
	{
		return date.getTimeString();
	}

	void printTime() const
	{
		cout << "Landing Time: " << date.getTimeString() << endl;
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
	Node* root;
	int noe;

public:
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

private:
	Node* printInOrder(Node* rootNode) const;
	Node* getNode(Node* rootNode, int toFind) const;
	int nextAvailable(int requestedTime, Node* collisionTime) const;
	Node* addNode(Node* rootNode, int addTime);
	Node* getSmallest(Node* rootNode) const;
	Node* removeNode(Node* current, int removeValue);
	Node* copyAll(const Node* otherRoot);
	void destroyTree(Node* rootNode);
};

#endif
