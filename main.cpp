/*https://www.geeksforgeeks.org/cpp/if-memory-allocation-using-new-is-failed-in-c-then-how-it-should-be-handled/*/
#include <iostream>
#include "BST.h"
using namespace std;




int main()
{
	/*TODO
	 * Node stream insertion operator helper method needs to return ostream obj
	 * make bst stuff private
	 * make node helpers private
	 */
	BST x = BST();
	x.insert(500);
	x.insert(600);
	x.insert(300);
	x.insert(450);
	x.insert(520);
	x.insert(14);
	x.insert(555);
	x.insert(10);
	//x.printSchedule();
	BST y = BST(x);
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
	//cout << x.root << endl;
	//cout << x.noe << endl;
	cout << "Test" << endl;
	return 0;
}