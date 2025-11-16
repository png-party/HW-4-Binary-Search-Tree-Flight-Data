#pragma once
#ifndef TIME_H
#define TIME_H
#include <string>
class Time
{
	int num;
	int minutes;
	int hours;

public:
	Time();
	Time(int landingTime);
	static int verifyTime(int landingTime);
	std::string getTimeString() const;
	int getMinutes() const;
	int getHours() const;
	int getTime() const;
	void setTime(int landingTime);
	static int subtractTimes(int t1, Time& t2);
	static int addTimes(Time& t1, int t2);

private:
	static int checkMinutes(int landingTime);
	static int checkHours(int landingTime);
};
#endif