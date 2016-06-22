#pragma once
#include "Program.h"
#include "Data.h"

class StatementBuilder
{
public:
	StatementBuilder(std::string path);
	~StatementBuilder();
	std::list<Statement> getStatementSequnce();
	std::map<char, int> getVariablesContainer();
	Initializer getInitializer();

private:
	void validateStatementSequnce();
	void buildInitializer();
	void buildStatementSequnce();
	bool isComand(std::string command);
	bool isPrint(std::vector<std::string> command);
	bool isAssignment(std::vector<std::string> command);
	void createComandEnd();
	void createComandLock();
	void createComandUnlock();
	void createComandPrint(char _variableName);
	void createComandAssignement(int _variableValue, char _variableName);

	Initializer mInitializer;
	std::ifstream mFileStream;
	std::list<Statement> mStatementSequnce;
	std::map<char, int> mVariablesContainer;
	int mStatementCounter;
	bool mOutOfNumberFlag;
	bool mWrongStatement;
	const std::string mVariablesNames = "abcdefghijklmnopqrstuvwxyz";

	StatementBuilder(const StatementBuilder &);
	StatementBuilder & operator = (const StatementBuilder &);
};

