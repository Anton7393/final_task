#pragma once
#include "Program.h"
#include "Data.h"

class ProgramController
{
public:
	ProgramController(Initializer _initializer, std::list<Statement> _statementSequnce, std::map<char, int> _variablesContainer);
	void start();

private:
	void statementInterpretator(Statement _statement);
	void implementEnd();
	void implementLock();
	void implementUnlock();
	void implementPrint(std::map<char, int> _variablesContainer, char _variableName);
	void implementAssignment(std::map<char, int> * _variablesContainer, char _variableName, int _variableValue);
	void switchProgramms();
	void programmsRunning();
	void readyProgrammsSetTime();
	void startImplementation();
	void overImplementation();

	std::list<Program> mProgramSequnce;
	std::list<Statement> mStatementSequnce;
	std::map<char, int> mVariablesContainer;
	Initializer mInitializer;

	ProgramController(const ProgramController &);
	ProgramController & operator = (const ProgramController &);
};
