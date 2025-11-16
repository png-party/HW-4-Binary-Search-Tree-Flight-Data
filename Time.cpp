#include "Time.h"
#include <iostream>
#include <ostream>
#include <string>
using namespace std;
Time::Time()
{
	minutes = 0;
	hours = 0;
	num = 0;
}
Time::Time(int landingTime)
{
	minutes = checkMinutes(landingTime);
	hours = checkHours(landingTime);
	num = hours * 100 + minutes;
}

int Time::verifyTime(int landingTime)
{
	landingTime = abs(landingTime);
	int checkedTime = checkHours(landingTime) * 100 + checkMinutes(landingTime);
	if (checkedTime != landingTime) cout << "==>Invalid time adjusted from " << landingTime << " to " << checkedTime << endl;
	return checkedTime;
}

std::string Time::getTimeString() const
{
	string padHours = (hours < 10) ? "0" : "";
	string padMinutes = (minutes < 10) ? "0" : "";
	return padHours + to_string(hours) + ":" + padMinutes + to_string(minutes);
}

int Time::getMinutes() const
{
	return minutes;
}

int Time::getHours() const
{
	return hours;
}

int Time::getTime() const
{
	return num;
}

void Time::setTime(int landingTime)
{
	minutes = checkMinutes(landingTime);
	hours = checkHours(landingTime);
	num = hours * 100 + minutes;
}

/* Gets the positive difference between two times
 * It subtracts the greatest time from the smaller time */
int Time::subtractTimes(int t1, Time& t2)
{
	int min1 = checkMinutes(t1);
	int h1 = checkHours(t1);

	/* Skip comparison if both times are equal */
	if (h1 * 100 + min1 == t2.getTime()) return 0;

	/* Subtract from requested time (t1) if greater,
	 * otherwise subtract from an existing time (t2) */
	int subMins = (h1 * 100 + min1 > t2.getTime()) ? min1 - t2.minutes : t2.minutes - min1;
	int subHours = (h1 * 100 + min1 > t2.getTime()) ? h1 - t2.hours : t2.hours - h1;

	/* Remove an hour if minutes are negative, then add the negative minutes to 60 */
	if (subMins < 0) return (subHours - 1 > 0) ? ((subHours - 1) * 100) + 60 + subMins : 0;
	return subHours * 100 + subMins;

}


int Time::addTimes(Time& t1, int t2)
{
	t2 = abs(t2);
	int min2 = checkMinutes(t2);
	int h2 = checkHours(t2);
	int addMins = t1.minutes + min2;
	int addHours = (t1.hours + h2 < 24) ? t1.hours + h2 : 0;
	if (addMins > 59)
	{
		if (addHours + 1 > 23) return 2359;
		//Add an extra hour if minutes overflow
		return (addHours + 1) * 100 + addMins - 60;
	}
	return addHours * 100 + addMins;
}

/* Helper methods for validating hours and minutes */

int Time::checkMinutes(int landingTime)
{
	//Get the first two digits
	int m = landingTime % 10;
	landingTime /= 10;
	m += (landingTime % 10) * 10;

	//Round down if minutes are over 59
	return (m <= 59) ? m : 59;
}

int Time::checkHours(int landingTime)
{
	//Get the 3rd digit
	landingTime /= 100;
	int h = landingTime % 10;
	landingTime /= 10;
	//Get the 4th digit if it exists
	if (landingTime > 0) h += landingTime % 10 * 10;
	//Round down if hours are over 23
	return (h <= 23) ? h : 23;
}