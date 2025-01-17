#include <string>
#include <stack>
#include <iostream>

#include "Help.h"
#include "DrawFunction.h"

using namespace std;

const short LETTER = 0, NUMBER = 1, ARYTH = 2, BRACKET = 3;

void addMultiplyBetweenWordAndNumber(stack<string>& st) { //allows you to enter, for example, 2sin(x) instead of 2*sin(x)
    stack<string> result;

    short last = -1;
    while (!st.empty()) {
        short state = -1;

        if (isNumber(st.top().at(0))) //determine the type of the current expression
            state = NUMBER;
        else if (isLetter(st.top().at(0)))
            state = LETTER;

        if ((last == NUMBER && state == LETTER) || (last == LETTER && state == NUMBER)) { //if there is a number and word next to each other, add a '*' between them
            result.push("*");
        }
        last = state;
        result.push(st.top());
        st.pop();
    }

    reverseStack(result);
    st = result;
}

void sortMinuses(stack<string>& st) { //Assigns minuses to numbers, e.g. “2”, “+”, “-”, “x” -> “2”, “+”, “-x”
    stack<string> result;

    reverseStack(st);

    short last = -1; //status of the last word
    int index = 0; //current word number
    while (!st.empty()) {
        short state = -1;

        char token = st.top().at(0);

        if (isNumber(token)) //determine the type of the current expression
            state = NUMBER;
        else if (isLetter(token))
            state = LETTER;
        else if (token == '(' || token == '[' || token == '{') {
            state = BRACKET;
        }

        if (token == '-' && st.top().size() == 1) {
            if (last == BRACKET || index == 0) { // - is after the parenthesis or at the beginning of the expression
                st.pop(); //remove the minus

                if (!st.empty()) { //after the minus is something else
                    if (isNumber(st.top().at(0)) || isLetter(st.top().at(0)) || (st.top().at(0) == getUnknown() && st.top().size() == 1)) { //after the minus is a number or unknown or a word
                        string s = "-"; //add a minus to a number, or unknown
                        s.append(st.top());
                        st.pop();
                        result.push(s);

                        index++;
                        continue;
                    }
                    else { //after the minus is something else, such as a parenthesis
                        result.push("-");
                    }
                }
                else { //the minus is at the end
                    result.push("-");
                }
            }
        }

        last = state;
        result.push(st.top());
        st.pop();
        index++;
    }

    st = result;
}

void loadAsStack(string op, stack<string>& loadedStack) { //separates the individual expressions (2sin(x) -> “2”, “sin”, “(”, “x”, “)”)
    short state = -1;

    string currentWord = "";

    stack<string> operation;

    for (int i = 0; i < op.length(); i++) {
        char token = op.at(i);

        if (token == ' ') //ignore spaces
            continue;

        if (isNumber(token)) { //number
            if (state == NUMBER || currentWord == "") { //previous tokens are numbers
                currentWord.append(string(1, token)); //add to the number
                state = NUMBER;
            }
            else { //earlier tokens are something else
                operation.push(currentWord); //write down the current word and start a new number
                currentWord = string(1, token);
                state = NUMBER;
            }
        }
        else if (isLetter(token)) { //litera
            if (state == LETTER || currentWord == "") {//previous tokens are letters
                currentWord.append(string(1, token));//add to letters
                state = LETTER;
            }
            else {//earlier tokens are something else
                operation.push(currentWord);//write down the current number and start a new word
                currentWord = string(1, token);
                state = LETTER;
            }
        }
        else if (token == '(' || token == '[' || token == '{' || token == ')' || token == ']' || token == '}') { //bracket
            if(currentWord != "") //if the current expression is not empty then save it
                operation.push(currentWord);

            currentWord = string(1, token);

            state = BRACKET;
        }
        else { //arithmetic operation
            if (state == ARYTH || currentWord == "") {//previous tokens are operations
                currentWord.append(string(1, token));//add to operation
                state = ARYTH;
            }
            else {//earlier tokens are something else
                operation.push(currentWord);//save the current tokens and start a new arithmetic operation
                currentWord = string(1, token);
                state = ARYTH;
            }
        }
    }

    if (currentWord != "") { //if there is an expression left, save it
        operation.push(currentWord);
    }

    addMultiplyBetweenWordAndNumber(operation);

    sortMinuses(operation);

    loadedStack = operation;
}