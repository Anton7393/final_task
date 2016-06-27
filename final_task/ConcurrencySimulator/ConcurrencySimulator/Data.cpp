#include "stdafx.h"
#include "Data.h"

Statement::Statement(StatementCommand _command)
	: command(_command)
	, variableValue(NULL)
	, variableName(NULL)
{
}

Statement::Statement(StatementCommand _command, char _variableName)
	: command(_command)
	, variableValue(NULL)
	, variableName(_variableName)
{
}

Statement::Statement(StatementCommand _command, int _variableValue, char _variableName)
	: command(_command)
	, variableValue(_variableValue)
	, variableName(_variableName)
{
}

StatementStack::StatementStack()
	: mStatementStack()
{
}

void StatementStack::initializeStatementStack(int _countOfProgramms)
{
	StatementSequnce emptyStatementSequnce;

	for (auto i = 0; i < _countOfProgramms; i++)
	{
		mStatementStack.push_back(emptyStatementSequnce);
	}
}

void StatementStack::addStatement(Statement _statement, int _sequnceNumber)
{
	mStatementStack.at(_sequnceNumber - 1).push_back(_statement);
}

Statement StatementStack::getStatement(int _id)
{
	auto temporarySequnce = *(mStatementStack.at(_id - 1).cbegin());
	mStatementStack.at(_id - 1).pop_front();
	return temporarySequnce;
}

int StatementStack::getSizeOfSequnce(int _id)
{
	return mStatementStack.at(_id - 1).size();
}

int StatementStack::getSizeOfStack()
{
	return mStatementStack.size();
}

Initializer::Initializer()
	: numberOfProgramms(0)
	, assignmentQTime(0)
	, outputQTime(0)
	, lockQTime(0)
	, unlockQTime(0)
	, endQTime(0)
	, quantumTime(0)
{
}
