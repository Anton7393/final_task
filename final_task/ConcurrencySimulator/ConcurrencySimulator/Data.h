#pragma once

enum class StatementCommand
{
	end,
	lock,
	unlock,
	print,
	assignment
};

enum class Status
{
	ready,
	running,
	blocked,
	over
};

struct Statement
{
	Statement(StatementCommand _command)
		: command(_command)
		, variableValue(NULL)
		, variableName(NULL)
	{
	}

	Statement(StatementCommand _command, char _variableName)
		: command(_command)
		, variableValue(NULL)
		, variableName(_variableName)
	{
	}

	Statement(StatementCommand _command, int _variableValue, char _variableName)
		: command(_command)
		, variableValue(_variableValue)
		, variableName(_variableName)
	{
	}

	StatementCommand command;
	int variableValue;
	char variableName;
};

struct Initializer
{
	int numberOfProgramms;
	int assignmentQTime;
	int outputQTime;
	int lockQTime;
	int unlockQTime;
	int endQTime;
	int quantumTime;
};

