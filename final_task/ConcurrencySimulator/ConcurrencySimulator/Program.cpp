#include "stdafx.h"
#include "Program.h"

int Program::mNextId = 1;

Program::Program()
	: mID(mNextId)
	, mStatus(Status::ready)
	, mRemainigTime(0)
{
	++mNextId;
}

void Program::print(std::map<char, int> _variableContainer, char _name)
{
	std::cout << mID << " : " << _variableContainer.at(_name) << std::endl;
}

void Program::assignment(std::map<char, int> * _variableContainer, char _name, int _value)
{
	_variableContainer->at(_name) = _value;
}

void Program::lock()
{
	mStatus = Status::blocked;
}

void Program::unlock()
{
	mStatus = Status::ready;
}

void Program::end()
{
	mStatus = Status::over;
}

Status Program::getStatus()
{
	return mStatus;
}

void Program::setStatus(Status _status)
{
	mStatus = _status;
}

int Program::getTime()
{
	return mRemainigTime;
}

void Program::setTime(int _time)
{
	mRemainigTime = _time;
}

void Program::addTime(int _time)
{
	mRemainigTime += _time;
}

void Program::spendTime(int _time)
{
	mRemainigTime -= _time;
}