#include <iostream>

//#include "BST.h"
using namespace std;
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
static void displayInt(int landingTime)
{
	//int hours = getHours(landingTime);
	int time = getHours(landingTime) * 100 + getMinutes(landingTime);
	//int time = (hours > 9) ? hours * 100 : hours * 1000;
	//time += getMinutes(landingTime);
	cout << time << endl;
}
static void print(int landingTime)
{
	int h = getHours(landingTime);
	int m = getMinutes(landingTime);
	string s = (h < 10) ? "0" : "";
	string s2 = (m < 10) ? "0" : "";
	cout << s << h << ":" << s2 << m << endl;
}
int main()
{
	int mins = -1;
	while (mins != -2)
	{
		cin >> mins;
		displayInt(mins);
		print(mins);
	}
	//cin >> mins;
	return 0;
}