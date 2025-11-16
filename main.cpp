/*
 *	Nicole Sirbu
 *	CMPR-131
 *	2025-11-12
 *	Homework #4
 *  Collaboration:
 *https://www.geeksforgeeks.org/cpp/if-memory-allocation-using-new-is-failed-in-c-then-how-it-should-be-handled/
 */
#include <iostream>
#include "BST.h"
using namespace std;

int main()
{
	BST x = BST();
	cout << "===Avoiding collision and inserting invalid values===" << endl;
	x.insert(1);
	x.insert(0);
	x.insert(1860);
	x.insert(1405);
	x.insert(1410);
	x.insert(9999);
	x.insert(2357);
	x.insert(1296);

	cout << "\n===Copying X with the assignment operator===" << endl;
	x.printSchedule();
	BST y = x;
	cout << "\n===Y after being assigned a copy of X===" << endl;
	y.printSchedule();

	cout << "\n===Removing values from Y===" << endl;
	y.remove(1859);
	y.remove(0);
	y.remove(233339);

	cout << "\n===Copying Y with the copy constructor==" << endl;
	y.printSchedule();
	BST h = BST(y);
	cout << "\n===H after using the copy constructor==" << endl;
	h.printSchedule();
	cout << "\n===Deleting all data in H===" << endl;
	h.clearData();
	h.printSchedule();
	cout << "\n===The original Y remains the same===" << endl;
	y.printSchedule();
	return 0;
}
