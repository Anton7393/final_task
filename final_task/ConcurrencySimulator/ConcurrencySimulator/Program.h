#pragma once
#include "Data.h"

class Program
{
public:
	Program();
	void print(std::map<char, int> _variableContainer, char _name);
	void assignment(std::map<char, int> * _variableContainer, char _name, int _value);
	void lock();
	void unlock();
	void end();
	Status getStatus();
	void setStatus(Status _status);
	int getTime();
	void setTime(int _time);
	void addTime(int _time);
	void spendTime(int _time);

private:
	int mID;
	int mRemainigTime;
	Status mStatus;

	static int mNextId;
};


