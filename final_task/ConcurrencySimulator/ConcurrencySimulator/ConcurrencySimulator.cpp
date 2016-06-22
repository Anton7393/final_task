// ConcurrencySimulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Program.h"
#include "Data.h"
#include "StatementBuilder.h"
#include "ProgramController.h"

int main()
{
	std::list<Statement> statementSequnce;
	std::map<char, int> variablesContainer;
	Initializer initializer;

	try
	{
		StatementBuilder builder("Program.txt");
		initializer = builder.getInitializer();
		statementSequnce = builder.getStatementSequnce();
		variablesContainer = builder.getVariablesContainer();
	}
	catch (std::runtime_error & ex)
	{
		std::cout << ex.what() << std::endl;
	}

	ProgramController controller(initializer, statementSequnce, variablesContainer);
	controller.start();

	system("pause");
	return 0;
}

