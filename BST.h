
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
		time = getHours(landingTime) * 100 + getMinutes(landingTime);
		left = nullptr;
		right = nullptr;
		if (time != landingTime) cout << "Time adjusted from " << landingTime << " to " << time << endl;
	}

	/* Prevent setting nodes with invalid times
	 * Ranges:
		 * 0 <= hours <= 23
		 * 0 <= minutes <= 59*/

	/* Hours and minutes are rounded up or down separately
	 * For example:
		 * 24:15 - > 23:15
		 * 9:99 - > 9:59 */
	void setTime(int landingTime)
	{
		time = getHours(landingTime) * 100 + getMinutes(landingTime);
	}

	/* Generates a new random time if there is a collision with other nodes */
	void randomizeTime()
	{
		cout << "==>Flight collision detected with requested time, " << time;
		time = randomValue(0, 23) * 100 + randomValue(0, 59);
		cout << ", generating new time: " << time << endl;
	}

	/* Helper method for generating random hours and minutes */
	int randomValue(int min, int max)
	{
		/* Create a new seed for the random number generator
		 * so the method generates new numbers each time
		 * it is called instead of returning the same ones */
		random_device seed;
		//Seed the random number generator
		mt19937 gen(seed());
		//Make a uniform distribution from which to select the numbers
		uniform_int_distribution<> distrib(min, max);

		//Generate random number within the range
		return distrib(gen);
	}

	/* Prints the node's time and pads numbers with zeroes
	 * It doesn't use getHours() or getMinutes() since it doesn't
	 * need to validate the time if the node was already created */
	string getTimeString() const
	{
		int hours = getHours(time);
		int minutes = getMinutes(time);

		string padHours = (hours < 10) ? "0" : "";
		string padMinutes = (minutes < 10) ? "0" : "";
		return padHours + to_string(hours) + ":" + padMinutes + to_string(minutes);
	}
	void printTime() const
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

		cout << "Landing Time: " << padHours << hours << ":" << padMinutes << minutes << endl;
	}
	void printBasicTime(ostream& out) const
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

		out << padHours << hours << ":" << padMinutes << minutes;
	}


	/*Helper methods for validating hours and minutes*/
	 static int getMinutes(int landingTime)
	{
		//Prevent negative values
		landingTime = abs(landingTime);

		//Get the first two digits
		int minutes = landingTime % 10;
		landingTime /= 10;
		minutes += (landingTime % 10) * 10;

		//Round down if minutes are over 59
		return (minutes > 59) ? 59 : minutes;
	}

	static int getHours(int landingTime)
	{
		//Prevent negative values
		landingTime = abs(landingTime);

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
/*Overloaded stream insertion operators for Node objects and pointers */

inline ostream& operator<<(ostream& out, const Node* other)
{
	other->printBasicTime(out);
	return out;
}

inline ostream& operator<<(ostream& out, const Node& other)
{
	other.printBasicTime(out);
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
	bool insert(int landingTime);
	Node* remove(int landingTime);
	bool search(int landingTime) const;
	void clearData();
	int nextAvailable(int requestedTime);

//private:
	Node* getSmallest(Node* rootNode) const;
	Node* printInOrder(Node* rootNode) const;
	Node* addNode(Node* root, int addTime);
	Node* removeNode(Node* current, int removeValue);
	Node* copyAll(const Node* otherRoot);
	void destroyTree(Node* rootNode);
	void levelOrderRec(Node* root2, int level, vector<vector<string>>& res);
	vector<vector<string>> levelOrder(Node* root2);
	void printLevel();
};

#endif