#include "Calculator.h"
#include <string>
#include <stack>
#include <cctype>
#include <cmath>
#include <vector>
#include <iostream>

MyCalc::MyCalc( const std::string& line ):
	value(0)
{
	infix = line;
}

double MyCalc::Value() const
{
	return value;
}

std::string MyCalc::Postfix() const
{
	return postfix;
}

void MyCalc::convertInfixToPostfix()
{
	std::stack<char> stack;
	stack.push( '(' );
	for( std::size_t i = 0; i < infix.length(); ++i ) {
		const char element = infix[i];
		if( element == ' ' ) {
			continue;
		}
		if( isalnum( element ) || element == '.' ) {
				   postfix += element;
				   continue;
		}	
		if ( element == '(' ) {
			stack.push( element );
			continue;
	    }
		if( isOperator(element) ) {
			char rightOperator = element;
			while( !stack.empty() && isOperator( stack.top() ) && sequence( stack.top(), rightOperator ) ) {
				postfix += ' ' + stack.top();
				stack.pop();
			}
			postfix += ' ';
			stack.push(rightOperator);
			continue;
		}
		if( element == ')' ) {
			while( !stack.empty() && stack.top() != '(' ) {
				postfix += ' ' + stack.top();
				stack.pop();
			}
			if( stack.empty() )
				throw std::runtime_error( "Error " );
			stack.pop();
			postfix += ' ';
			continue;
		}
	}
	while( !stack.empty() && stack.top() != '(' ) {
		postfix += ' ' +stack.top();
		stack.pop();
	}
	postfix += ' ';
	if( stack.empty() )
		throw std::runtime_error("Error ");
	stack.pop();
	modifyPostfix();
}

void MyCalc::countValue()
{
	std::stack<double> stack;
	std::string tmp;
	for( std::size_t i = 0; i < postfix.length(); ++i ) {
		char element = postfix[i];
		if( isalnum( element ) || element == '.' ) {
			tmp += element;
			continue;
		}
		if( isspace( element ) && ( isalnum( postfix[ i - 1 ] ) || postfix[ i - 1 ] == '.' ) ) {
			stack.push( std::stod(tmp) );
			tmp = "";
			continue;
		}
		if( isOperator( element ) ) {
			if( tmp != "" ) {
				stack.push( std::stod(tmp) );
				tmp = "";
			}
			double o1 = stack.top();
			stack.pop();
			double o2 = stack.top();
			stack.pop();
			stack.push( countOperation( element, o1, o2) );
			continue;
		}
	}
	value = stack.top();

}

bool MyCalc::isOperator( const char c )
{
	if( c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
		return true;
	return false;
}

bool MyCalc::sequence( const char& leftOperator, const char& rightOperator )
{
	if( rightOperator == '*' || rightOperator == '/' || rightOperator == '^' )
		return false;
	return true;
}

double MyCalc::countOperation( const char& operation, const double o1, const double o2 )
{
	double answer;
	switch (operation) {
        case'+': {
                answer = o1 + o2;
                break;
        }
        case'-': {
                answer = o2 - o1;
                break;
        }
        case'*': {
                answer = o1*o2;
                break;
        }
        case'/': {
                answer = o2 / o1;
                break;
        }
        case'^': {
                answer = pow(o2, o1);
                break;
        }
    }
        return answer;
}

void MyCalc::modifyPostfix()
{
        for (std::size_t i = 0; i < postfix.length(); ++i) {
                if (postfix[i] == 'K') postfix[i] = '+';
                if (postfix[i] == '~') postfix[i] = '^';
                if (postfix[i] == 'M') postfix[i] = '-';
                if (postfix[i] == 'J') postfix[i] = '*';
                if (postfix[i] == 'O') postfix[i] = '/';
        }
}