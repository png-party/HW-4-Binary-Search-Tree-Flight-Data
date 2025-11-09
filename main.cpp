/*https://www.geeksforgeeks.org/cpp/if-memory-allocation-using-new-is-failed-in-c-then-how-it-should-be-handled/*/
#include <iostream>
#include "BST.h"
using namespace std;

int main()
{
	/*TODO
	 * Node stream insertion operator helper method needs to return ostream obj
	 * Destroy tree function needs base case
	 */
	BST x = BST();
	x.insert(500);
	x.insert(600);
	x.insert(300);
	x.insert(450);
	x.insert(520);
	x.insert(14);
	x.insert(555);
	x.printSchedule();
	return 0;
}