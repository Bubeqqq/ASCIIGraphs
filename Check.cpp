#include <iostream>
#include <string>
#include <stack>
#include <vector>

#include "Help.h"
#include "ShuntingYardAlgorithm.h"
#include "DrawFunction.h"

using namespace std;

void printError(vector<string> list, string before, string error, int index, int highlight) {
	cout << endl;
	cout << before << " \"" << list.at(index) << "\" " << error << endl; //display error information

	if (highlight >= list.size()) { //backlighting goes out of range
		highlight = list.size() - 1;
	}
	else if (highlight < 0) {
		highlight = 0;
	}

	for (int i = 0; i < list.size(); i++) {
		if (i == highlight) {
			cout << "\033[7m" << list.at(i) << "\033[0m"; //display the part of the code that causes the problem with the highlight
		}
		else
			cout << list.at(i); //display the correct parts of the code
	}

	cout << endl << endl;
}

bool isWord(string s) {
	return isLetter(s.at(0));
}

bool isOpenBracket(string s) {
	return (s.at(0) == '(' || s.at(0) == '[' || s.at(0) == '{');
}

bool isClosedBracket(string s) {
	return (s.at(0) == ')' || s.at(0) == ']' || s.at(0) == '}');
}

bool isUnknown(string s) {
	if (string(1, getUnknown()) == s) //traditional unknown
		return true;

	if (s.size() == 2 && s.at(0) == '-' && s.at(1) == getUnknown()) { //unknown with minus (-x)
		return true;
	}

	return false;
}

bool check(stack<string> stack) {
	vector<string> list;

	reverseStack(stack);
	while (!stack.empty()) { //replace stack with vector
		list.push_back(stack.top());
		stack.pop();
	}


	for (int i = 0; i < list.size(); i++) {
		string word = list.at(i);

		if (isUnknown(word) || isNumber(word)) //number and unknown does not display error
			continue;

		if (isWord(word)) { //funkcjê (sin, cos, arcsin)
			if (!isOperation(word) && !isUnknown(word)) { //misspelling (sim, cosz)
				printError(list, "", "is not a known function", i, i);
				return false;
			}

			if (i == list.size() - 1 || !isOpenBracket(list.at(i + 1))) { // no parenthesis after the function ( sinx), cos2 )
				printError(list, "after", "the bracket was expected to open", i, i + 1);
				return false;
			}
		}else if (isOpenBracket(word)) { //otwarty nawias
			int brackets = 0;

			if (i == list.size() - 1 || isClosedBracket(list.at(i + 1))) { //There is no number ( (), (())) after the parenthesis )
				printError(list, "after", "the number expected", i, i + 1);
				return false;
			}

			for (int j = i; j < list.size(); j++) { //look for the end of the parenthesis ( sin(x + 3, ((x+2)+3 ))
				if (isOpenBracket(list.at(j))) //open parenthesis found
					brackets++;
				else if (isClosedBracket(list.at(j))) //closed parenthesis found
					brackets--;

				if (brackets == 0) //end of parenthesis found
					break;
			}

			if (brackets != 0) { //no end found
				printError(list, "", "bracket closure not found", i, i);
				return false;
			}
		}else if (isClosedBracket(word)) { //end of bracket
			int brackets = 0;

			for (int j = i; j >= 0; j--) { //look for the start of the parenthesis ( )(x+3) )
				if (isOpenBracket(list.at(j)))
					brackets++;
				else if (isClosedBracket(list.at(j)))
					brackets--;

				if (brackets == 0)
					break;
			}

			if (brackets != 0) {
				printError(list, "", "bracket opening not found", i, i);
				return false;
			}
		}else { //operations such as +, -, *
			if (!isOperation(word)) { //no such operation found (+-, &, $)
				printError(list, "", "is not a valid arithmetic operation", i, i);
				return false;
			}
			
			if (word.at(0) != '-') { //before - does not have to be a number
				if (i == 0) { //operation is in the early stages
					printError(list, "before", "the number expected", i, i - 1); //errors such as +3, *5+8
					return false;
				}
			}

			if (i == list.size() - 1) { //operation is at the end of the action 5+, 7*8*
				printError(list, "after", "the number expected", i, i + 1);
				return false;
			}

			if (word.at(0) != '-') {
				if (!isClosedBracket(list.at(i - 1)) && !isNumber(list.at(i - 1)) && !isUnknown(list.at(i - 1))) { //before the operation, there is no number
					printError(list, "before", "the number expected", i, i - 1);
					return false;
				}
			}

			if (!isOpenBracket(list.at(i + 1)) && !isNumber(list.at(i + 1)) && !isUnknown(list.at(i + 1)) && !isWord(list.at(i + 1))) { //after the operation there is no number
				printError(list, "after", "the number expected", i, i + 1);
				return false;
			}
		}
	}

	return true;
}