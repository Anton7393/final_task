#include "stdafx.h"
#include "StatementBuilder.h"

StatementBuilder::StatementBuilder(std::string path)
	: mStatementCounter(0)
	, mWrongStatement(false)
	, mOutOfNumberFlag(false)
	, mStatementSequnce()
	, mVariablesContainer()
{
	mFileStream.open(path);
	buildInitializer();
	buildStatementSequnce();
	validateStatementSequnce();
}

StatementBuilder::~StatementBuilder()
{
	mFileStream.close();
}

std::list<Statement> StatementBuilder::getStatementSequnce()
{
	return mStatementSequnce;
}

std::map<char, int> StatementBuilder::getVariablesContainer()
{
	return mVariablesContainer;
}

Initializer StatementBuilder::getInitializer()
{
	return mInitializer;
}

void StatementBuilder::validateStatementSequnce()
{
	bool mLockOpened(false);
	int mEndCounter(0);

	for (auto statement : mStatementSequnce)
	{
		if ((statement.command == StatementCommand::lock) && (mLockOpened == true))
		{
			throw std::runtime_error("Lock can not be called untill that open");
		}
		if ((statement.command == StatementCommand::unlock) && (mLockOpened == false))
		{
			throw std::runtime_error("Unlock statement can not call before lock statement");
		}
		if ((statement.command == StatementCommand::unlock) && (mLockOpened == true))
		{
			mLockOpened = false;
			continue;
		}
		if ((statement.command == StatementCommand::lock) && (mLockOpened == false))
		{
			mLockOpened = true;
			continue;
		}
		if (statement.command == StatementCommand::end)
		{
			mEndCounter++;
		}
	}

	if (mLockOpened == true)
	{
		throw std::runtime_error("Unlock must be follow the lock statement!");
	}

	if (mEndCounter > mInitializer.numberOfProgramms)
	{
		throw std::runtime_error("Incorrect end statements!");
	}
}

void StatementBuilder::buildInitializer()
{
	int mCounter(0);
	int mValue(0);
	std::string mSequence;
	std::stringstream mStreamSequence;

	std::getline(mFileStream, mSequence);
	mStreamSequence << mSequence;

	while (mStreamSequence >> mValue)
	{
		mCounter++;
		switch (mCounter)
		{
		case 1:
			mInitializer.numberOfProgramms = mValue;
			break;
		case 2:
			mInitializer.assignmentQTime = mValue;
			break;
		case 3:
			mInitializer.outputQTime = mValue;
			break;
		case 4:
			mInitializer.lockQTime = mValue;
			break;
		case 5:
			mInitializer.unlockQTime = mValue;
			break;
		case 6:
			mInitializer.endQTime = mValue;
			break;
		case 7:
			mInitializer.quantumTime = mValue;
			break;
		default:
			throw std::runtime_error("Programs count is too big");
			break;
		}
	}
}

void StatementBuilder::buildStatementSequnce()
{
	std::string mSubstring;
	std::string mSentence;

	while (std::getline(mFileStream, mSentence))
	{
		if (mSentence == "")
		{
			continue;
		}

		int mCounter(0);
		bool mCorrectStatement(false);
		std::stringstream mStreamSentence;
		std::vector<std::string> mStrVector;

		mStatementCounter++;
		mStreamSentence << mSentence;

		while (mStreamSentence >> mSubstring)
		{
			mCounter++;
			mStrVector.push_back(mSubstring);
		}

		switch (mCounter)
		{
		case 1:
			mCorrectStatement = isComand(mStrVector.at(0));
			break;
		case 2:
			mCorrectStatement = isPrint(mStrVector);
			break;
		case 3:
			mCorrectStatement = isAssignment(mStrVector);
			break;
		default:
			mCorrectStatement = false;
			break;
		}

		if (mStatementCounter > 25)
		{
			mCorrectStatement = false;
		}

		if (mCorrectStatement == false)
		{
			throw std::runtime_error("Statement is incorrect");
		}
	}
}

bool StatementBuilder::isComand(std::string command)
{
	bool mFlag(false);

	if (command == "end")
	{
		mFlag = true;
		createComandEnd();
	}
	else if (command == "lock")
	{
		mFlag = true;
		createComandLock();
	}
	else if (command == "unlock")
	{
		mFlag = true;
		createComandUnlock();
	}

	return mFlag;
}

bool StatementBuilder::isPrint(std::vector<std::string> command)
{
	bool mFlag(false);

	if ((command.at(0) == "print") && (command.at(1).length() == 1))
	{
		for (auto name : mVariablesNames)
		{
			if (name == command.at(1)[0])
			{
				mFlag = true;
				createComandPrint(name);
				break;
			}
		}
	}

	return mFlag;
}

bool StatementBuilder::isAssignment(std::vector<std::string> command)
{
	bool mFlag(false);

	if ((command.at(1) == "=") && (command.at(0).length() == 1) && (command.at(2).length() <= 2))
	{
		int value = stoi(command.at(2));
		for (auto name : mVariablesNames)
		{
			if ((name == command.at(0)[0]) && (value < 100))
			{
				mFlag = true;
				createComandAssignement(value, name);
				break;
			}
		}
	}

	return mFlag;
}

void StatementBuilder::createComandEnd()
{
	mStatementSequnce.push_back(Statement(StatementCommand::end));
}

void StatementBuilder::createComandLock()
{
	mStatementSequnce.push_back(Statement(StatementCommand::lock));
}

void StatementBuilder::createComandUnlock()
{
	mStatementSequnce.push_back(Statement(StatementCommand::unlock));
}

void StatementBuilder::createComandPrint(char _variableName)
{
	mStatementSequnce.push_back(Statement(StatementCommand::print, _variableName));
	mVariablesContainer.insert(std::pair<char, int>(_variableName, 0));
}

void StatementBuilder::createComandAssignement(int _variableValue, char _variableName)
{
	mStatementSequnce.push_back(Statement(StatementCommand::assignment, _variableValue, _variableName));
	mVariablesContainer.insert(std::pair<char, int>(_variableName, 0));
}