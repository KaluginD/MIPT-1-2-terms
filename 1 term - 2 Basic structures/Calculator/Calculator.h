#pragma once
#include <string>
#include <stack>

class MyCalc {
public:
	MyCalc() {};
	MyCalc( const std::string& line );
	~MyCalc() {};

	void convertInfixToPostfix();
	void countValue();

	std::string Postfix() const;
	double Value() const;

	std::string postfix;
private:
	std::string infix;
	
	double value;

	bool isOperator( const char c );
	bool sequence( const char& leftOperator, const char& rightOperator );
	double countOperation( const char& operation, const double o1, const double o2 );
	void modifyPostfix();
};