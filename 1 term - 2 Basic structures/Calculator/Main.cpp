#include "Calculator.h"
#include <iostream>
#include <string>

int main() 
{
	std::string equation;
	std::cin >> equation;
	MyCalc calc( equation );
	calc.convertInfixToPostfix();
	calc.countValue();
	std::cout << calc.Value() << std::endl;
	system("pause");
	return 0;
}
