#pragma once

enum class StatementCommand
{
	end,
	lock,
	unlock,
	print,
	assignment,
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
	Statement(StatementCommand _command);
	Statement(StatementCommand _command, char _variableName);
	Statement(StatementCommand _command, int _variableValue, char _variableName);

	StatementCommand command;
	int variableValue;
	char variableName;
};

struct StatementStack
{
	StatementStack();
	void initializeStatementStack(int _countOfProgramms);
	void addStatement(Statement _statement, int _sequnceNumber);
	Statement getStatement(int _id);
	int getSizeOfSequnce(int _id);
	int getSizeOfStack();

private:
	typedef std::list<Statement> StatementSequnce;
	std::vector<StatementSequnce> mStatementStack;
};

struct Initializer
{
	Initializer();

	int numberOfProgramms;
	int assignmentQTime;
	int outputQTime;
	int lockQTime;
	int unlockQTime;
	int endQTime;
	int quantumTime;
};

