/*https://www.geeksforgeeks.org/cpp/if-memory-allocation-using-new-is-failed-in-c-then-how-it-should-be-handled/
 * https://www.geeksforgeeks.org/cpp/how-to-generate-random-number-in-range-in-cpp/
 */
#include <iostream>
#include "BST.h"
using namespace std;

int main()
{

	BST x = BST();
	x.insert(500);
	x.insert(600);
	x.insert(300);
	x.insert(450);
	x.insert(520);
	x.insert(14);
	x.insert(555);
	x.insert(10);
	x.insert(0);
	x.insert(2);
	x.insert(3);
	x.insert(601);
	x.insert(602);
	x.insert(605);
	x.insert(0);
	x.insert(2359);
	x.insert(2355);
	x.insert(9999);
	x.insert(2566);
	x.insert(5409);
	x.printSchedule();
	x.printLevel();

	BST y = BST(x);

	BST h = BST();
	h.insert(10);
	h.insert(20);
	h.insert(30);
	h.insert(40);
	h.insert(50);
	h.printLevel();
		 //y.printSchedule();
	//cout << y.root << endl;
//	cout << "test" << endl;
	

	//x.printLevel();
	//cout << x.root->getTimeString() << endl;
	y.printLevel();
	cout << x.root->right->left << endl;
	cout << y.root->right->left << endl;
//	cout << y.root->right->right << endl;
	y.remove(500);
	y.printLevel();
	y.remove(3333);
	//x.printSchedule();
	//x.printLevel();
	cout << x.root << endl;
	cout << x.noe << endl;
	cout << "Test" << endl;
	return 0;
}