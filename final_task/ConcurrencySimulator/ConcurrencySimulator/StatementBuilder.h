#pragma once
#include "Program.h"
#include "Data.h"

class StatementBuilder
{
public:
	StatementBuilder(const std::string & _path);
	std::list<Statement> & getStatementSequnce();
	std::map<char, int> & getVariablesContainer();
	StatementStack & getStatementStack();
	Initializer & getInitializer();

private:
	void validateStatementSequnce();
	void buildStatementStack();
	void buildInitializer();
	void buildStatementSequnce();
	bool isComand(const std::string & _command);
	bool isPrint(const std::vector<std::string> & _command);
	bool isAssignment(const std::vector<std::string> & _command);
	void createComandEnd();
	void createComandLock();
	void createComandUnlock();
	void createComandPrint(char _variableName);
	void createComandAssignement(int _variableValue, char _variableName);

	Initializer mInitializer;
	std::list<Statement> mStatementSequnce;
	std::map<char, int> mVariablesContainer;
	int mStatementCounter;
	bool mOutOfNumberFlag;
	bool mWrongStatement;
	StatementStack mStatementStack;
	std::ifstream mFileStream;
	const std::string mVariablesNames = "abcdefghijklmnopqrstuvwxyz";

	StatementBuilder(const StatementBuilder &);
	StatementBuilder & operator = (const StatementBuilder &);
};

