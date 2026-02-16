
#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;



//Declarations of Additional Functions: 
int getPrec(char character);
bool checkSyntax(string &infix);
bool InToPost(string infix, string& postfix); 
bool evaluatePostfix(string postfix); 





//Evaluate Funciton//
int evaluate(string infix, string& postfix, bool& result)
{
	if (InToPost(infix, postfix) == false)
	{
		return 1; 
	}
	result = evaluatePostfix(postfix); 
	return 0; 
}





//return a precendce rank for each symbol 
int getPrec(char character)
{
	switch (character)
	{
	case '^':
		return 1; 
	case '&':
		return 2; 
	case '!':
		return 3; 
	//won't happen 
	default:         
		return 4; 
	}
	return 4; 
}







//Check syntax 
bool checkSyntax(string& infix)
{
	

	//Remove spaces 
	string spacesRemovedInfix = "";
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] != ' ')
		{
			spacesRemovedInfix += infix[i];
		}
	}
	infix = spacesRemovedInfix;

	//Check for empty infix string 
	if (infix == "")
	{
		return false;
	}


	//Check Beginning -- can't start with ^ || & opperator 
	switch (infix[0])
	{
	case '^':
	case '&':
		return false;
	default:
		break;
	}

	//Check End -- can't end with certian symbols 
	switch (infix[infix.size()] - 1)
	{
	case '^':
	case '&':
	case '!':
	case '(':
		return false;
	default:
		break;
	}

	//check for additional improper characters 
	//certian characters cannot come directly after other characters 
	for (int i = 0; i < infix.size(); i++)
	{
		char character = infix[i];
		switch (character)
		{
		
	

		//( and ! cannot be followed by ), &, ^
		case '(':
		case '!':
			if (i + 1 < infix.size())
			{
				switch (infix[i + 1])
				{
				case '&':
				case '^':
				case ')':
					return false;
				default:
					break;
				}
			}
			else
			{
				return false; 
			}
			break; 

		//T or F cannot be followed by (, !, T, F 
		case 'F':
		case 'T':
			if ((i + 1) < infix.size())
			{
				switch (infix[i + 1])
				{
				case 'T':
				case 'F':
				case '(':
				case '!':
					return false;
				default: 
					break; 
				}
			}
			break; 

		//) cannot be followed by T, F, (
		case ')':
			if (i + 1 < infix.size())
			{
				switch (infix[i + 1])
				{
				case '(':
				case 'T':
				case 'F':
					return false; 
				default:
					break; 
				}
			}
			break; 

		case '^': 
		case '&':
			if (i + 1 < infix.size())
			{
				switch (infix[i + 1])
				{
				case '&':
				case '^':
				case ')':
					return false;
				default:
					break;
				}
			}
			else
			{
				return false; 
			}
			break;

		}
	}

	//if you get to the end, syntax is okay 
	return true; 
}








//Infix to Postfix 
bool InToPost(string infix, string& postfix)
{
	//check/correct syntax 
	if (checkSyntax(infix) == false)
	{
		return false; 
	}


	//Initialize postfix to empty
	postfix = ""; 

	//Initialize the operator stack to empty 
	stack<char>  operatorStack; 




	//Covert to Postfix and check for impropper characters 
	for (int i = 0; i < infix.size(); i++)
	{
		char currentChar = infix[i]; 
		switch (currentChar)
		{
			//T F -- append to end of postfix
			case 'T':
			case 'F':
				postfix += currentChar;
				break;
			
			//push ( onto opperator stack 
			case '(':
			case '!':     
                                        //might be wrong 
				operatorStack.push(currentChar); 
				break; 

			case ')':
				//pop stack until matching '('
				//while stack top is not '('
				while (operatorStack.empty() == false && operatorStack.top() != '(')
				{
					postfix += operatorStack.top(); //append the stack top to postfix 
					operatorStack.pop();            //pop the stack 
				}
				if (operatorStack.empty() == true)  //paren is the wrong way 
				{
					return false; 
				}
				operatorStack.pop(); //pop the stack to remove the '('
			    break; 

			case '&':
			case '^':
				//While the stack is not empty and the stack top is not '('
				//and precedence of ch <= precedence of stack top
				while (operatorStack.empty() == false   &&   operatorStack.top() != '('    &&    getPrec(currentChar) <= getPrec(operatorStack.top()))
				{
					postfix += operatorStack.top();   //append the stack top to postfix
					operatorStack.pop();              //pop the stack
				}
				operatorStack.push(currentChar); //push ch onto the stack
				break;                           //break 

			//there is an improper symbol 
			default: 
				return false; 
		}
	}

	//while stack is not empty 
	while (operatorStack.empty() == false)
	{
		//if there is still ( ) then there were too many paren used 
		if (operatorStack.top() == '(' || operatorStack.top() == ')')
		{
			return false; 
		}

		postfix += operatorStack.top(); 
		operatorStack.pop(); 
	}

	//if you get this far, then all the syntax checks out 
	return true; 
}








//Evaluate Postfix 
bool evaluatePostfix(string postfix)
{

	//Initialize the operand stack to empty
	stack<bool> operandStack; 

	//For each character ch in the postfix string
	for (int i = 0; i < postfix.size(); i++)
	{
		char currentChar = postfix[i]; 
		//if ch is an operand
		if (currentChar == 'T' || currentChar == 'F')
		{
			//push the value that ch represents onto the operand stack
			if (currentChar == 'T')
			{
				operandStack.push(true); 
			}
			else
			{
				operandStack.push(false); 
			}
		}
		else if (currentChar == '&' || currentChar == '^')   // ch is a binary operator
		{
			bool operand2 = operandStack.top();  //set operand2 to the top of the operand stack
			operandStack.pop();                  //pop the stack
			bool operand1 = operandStack.top();  //set operand1 to the top of the operand stack
			operandStack.pop();                  //pop the stack

			//apply the operation that ch represents to operand1and
			//operand2, and push the result onto the stack
			if (currentChar == '&')
			{
				operandStack.push(operand1 & operand2);          //CHECK THIS
			}
			if (currentChar == '^')
			{
				operandStack.push(operand1 ^ operand2); 
			}
		}
		else    //Then operator is ! 
		{
			bool operand1 = operandStack.top(); 
			operandStack.pop(); 
			operandStack.push(!operand1); 
		}
	}
	
	//When the loop is finished, the operand stack will contain one item,
	//the result of evaluating the expression
	return operandStack.top(); 

}



int main()
{
	string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^" && answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
	cout << "Passed all tests" << endl;
}









