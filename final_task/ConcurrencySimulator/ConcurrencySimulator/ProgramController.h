#pragma once
#include "Program.h"
#include "Data.h"

class ProgramController
{
public:
	ProgramController(const Initializer & _initializer, StatementStack _statementStack, std::map<char, int> & _variablesContainer);
	void start();

private:
	void statementInterpretator(const Statement & _statement);
	int getReadyId();
	Statement getCurrentStatement();
	void implementEnd();
	void implementLock();
	void implementUnlock();
	void implementPrint(const std::map<char, int> & _variablesContainer, char _variableName);
	void implementAssignment(std::map<char, int> & _variablesContainer, char _variableName, int _variableValue);
	void switchProgramms();
	void programmsRunning();
	void readyProgrammsSetTime();
	void startImplementation();
	void overImplementation();

	Initializer mInitializer;
	StatementStack mStatementStack;
	std::map<char, int> mVariablesContainer;
	std::list<Program> mProgramSequnce;
	
	ProgramController(const ProgramController &);
	ProgramController & operator = (const ProgramController &);
};
