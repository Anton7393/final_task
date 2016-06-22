#include "stdafx.h"
#include "ProgramController.h"


ProgramController::ProgramController(Initializer _initializer, std::list<Statement> _statementSequnce, std::map<char, int> _variablesContainer)
	: mInitializer(_initializer)
	, mStatementSequnce(_statementSequnce)
	, mVariablesContainer(_variablesContainer)
	, mProgramSequnce()
{
	for (auto i = 0; i < mInitializer.numberOfProgramms; i++)
	{
		mProgramSequnce.push_back(Program());
	}
}

void ProgramController::start()
{
	readyProgrammsSetTime();

	for (auto statement : mStatementSequnce)
	{
		if (mProgramSequnce.size() == 0) break;
		programmsRunning();
		statementInterpretator(statement);
	}
}

void ProgramController::statementInterpretator(Statement _statement)
{
	switch (_statement.command)
	{
	case StatementCommand::end:
		implementEnd();
		break;
	case StatementCommand::lock:
		implementLock();
		break;
	case StatementCommand::unlock:
		implementUnlock();
		break;
	case StatementCommand::assignment:
		implementAssignment(&mVariablesContainer, _statement.variableName, _statement.variableValue);
		break;
	case StatementCommand::print:
		implementPrint(mVariablesContainer, _statement.variableName);
		break;
	}
}

void ProgramController::implementEnd()
{
	int implementationTime = mInitializer.endQTime;
	startImplementation();
	mProgramSequnce.begin()->spendTime(implementationTime);
	mProgramSequnce.begin()->end();
	mProgramSequnce.pop_front();
}

void ProgramController::implementLock()
{
	int implementationTime = mInitializer.lockQTime;
	startImplementation();
	mProgramSequnce.begin()->spendTime(implementationTime);
	mProgramSequnce.begin()->lock();
	overImplementation();
}

void ProgramController::implementUnlock()
{
	int implementationTime = mInitializer.unlockQTime;
	startImplementation();
	mProgramSequnce.begin()->spendTime(implementationTime);
	mProgramSequnce.begin()->unlock();
	overImplementation();
}

void ProgramController::implementPrint(std::map<char, int> _variablesContainer, char _variableName)
{
	int implementationTime = mInitializer.outputQTime;
	startImplementation();
	mProgramSequnce.begin()->spendTime(implementationTime);
	mProgramSequnce.begin()->print(_variablesContainer, _variableName);
	overImplementation();
}

void ProgramController::implementAssignment(std::map<char, int> * _variablesContainer, char _variableName, int _variableValue)
{
	int implementationTime = mInitializer.assignmentQTime;
	startImplementation();
	mProgramSequnce.begin()->spendTime(implementationTime);
	mProgramSequnce.begin()->assignment(_variablesContainer, _variableName, _variableValue);
	overImplementation();
}

void ProgramController::switchProgramms()
{
	auto bufferProgram = *(mProgramSequnce.begin());
	mProgramSequnce.pop_front();
	mProgramSequnce.push_back(bufferProgram);
}

void ProgramController::programmsRunning()
{
	for (auto program : mProgramSequnce)
	{
		if (program.getStatus() == Status::running)
		{
			program.addTime(mInitializer.quantumTime);
		}

		if (program.getTime() >= 0)
		{
			program.setStatus(Status::ready);
			program.setTime(mInitializer.quantumTime);
		}
	}
}

void ProgramController::readyProgrammsSetTime()
{
	for (auto program : mProgramSequnce)
	{
		if (program.getStatus() == Status::ready)
		{
			program.setTime(mInitializer.quantumTime);
		}
	}
}

void ProgramController::startImplementation()
{
	Status status = mProgramSequnce.begin()->getStatus();
	int currentTime = mProgramSequnce.begin()->getTime();

	if (status == Status::running)
	{
		switchProgramms();
		startImplementation();
	}

	if ((status == Status::ready) && (currentTime == 0))
	{
		mProgramSequnce.begin()->setTime(mInitializer.quantumTime);
	}
}

void ProgramController::overImplementation()
{
	Status status = mProgramSequnce.begin()->getStatus();
	int currentTime = mProgramSequnce.begin()->getTime();

	switch (status)
	{
	case Status::ready:
		if (currentTime < 0)
		{
			mProgramSequnce.begin()->setStatus(Status::running);
			switchProgramms();
		}
		if (currentTime == 0)
		{
			mProgramSequnce.begin()->setTime(mInitializer.quantumTime);
			switchProgramms();
		}
		break;
	case Status::running:
		throw std::runtime_error("Running program is can not be on active duty");
		break;
	case Status::blocked:
		mProgramSequnce.begin()->setTime(mInitializer.quantumTime);
		break;
	case Status::over:
		throw std::runtime_error("Cancelled program is can not be on active duty");
		break;
	default:
		throw std::runtime_error("Program status is undefined");
		break;
	}
}