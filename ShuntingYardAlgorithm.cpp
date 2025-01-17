#pragma once

#include <string>
#include <stack>
#include <unordered_map>

#include "math.h"
#include "Load.h"
#include "Help.h"

using namespace std;

typedef bool (*Operation)(string a, string b, string op, stack<string>& queue);

unordered_map<string, int> OperationPriority;
unordered_map<string, Operation> OperationFunctions;

void addFunction(string sign, int priority, bool (*func)(string a, string b, string op, stack<string>& queue)) {
    OperationPriority[sign] = priority;
    OperationFunctions[sign] = func;
}

void Setup() {
    OperationPriority["("] = 0;
    OperationPriority[")"] = 0;
    OperationPriority["["] = 0;
    OperationPriority["]"] = 0;
    OperationPriority["{"] = 0;
    OperationPriority["}"] = 0;
    addFunction("+", 2, sum);
    addFunction("-", 2, substracion);
    addFunction("*", 3, multiply);
    addFunction("/", 3, divide);
    addFunction("^", 4, powC);
    addFunction("sin", 5, sinC);
    addFunction("cos", 5, cosC);
    addFunction("tan", 5, tgC);
    addFunction("cot", 5, cotC);
    addFunction("arcsin", 5, arcsinC);
    addFunction("arccos", 5, arccosC);
    addFunction("arctan", 5, arctgC);
    addFunction("arccot", 5, arccotC);
    addFunction("ln", 5, LogarithmLN);
    addFunction("log", 5, Logarithm);
    addFunction("abs", 5, absC);
    addFunction("sqrt", 5, squareRoot);
    addFunction("cbrt", 5, cubeRoot);
    addFunction("-sin", 5, MsinC);
    addFunction("-cos", 5, McosC);
    addFunction("-tan", 5, MtgC);
    addFunction("-cot", 5, McotC);
    addFunction("-arcsin", 5, MarcsinC);
    addFunction("-arccos", 5, MarccosC);
    addFunction("-arctan", 5, MarctgC);
    addFunction("-arccot", 5, MarccotC);
    addFunction("-ln", 5, MLogarithmLN);
    addFunction("-log", 5, MLogarithm);
    addFunction("-abs", 5, MabsC);
    addFunction("-sqrt", 5, MsquareRoot);
    addFunction("-cbrt", 5, McubeRoot);
}

bool isOperation(string s) {
    return OperationPriority.count(s);
}

void checkForDoubleMinus(stack<string>& operation) {
    stack<string> checked;

    string last = "";

    while (!operation.empty()) {
        if (last == "-" && operation.top() == "-") { //if there are 2 minuses next to each other
            checked.pop(); //delete last minus
            checked.push("+"); //add + instead of 2 minuses
            last = "+";
            operation.pop();
        }
        else {
            last = operation.top(); //update the last word
            checked.push(operation.top()); //port to new
            operation.pop();
        }
    }

    operation = checked;
}

void ShuntingYardAlgorithm(stack<string>& operation) {
    stack<string> queue, result; //shunting yard algorithm

    while (!operation.empty()) { //for each expression in action
        string token = operation.top(); //expression currently in process

        if (token == "(" || token == "[" || token == "{") { //token is the beginning of the parenthesis
            queue.push(token); //add to queue
        }
        else if (token == ")" || token == "]" || token == "}") { //token is the end of the parenthesis
            string topOfQueue = queue.top();

            while (topOfQueue != "(" && topOfQueue != "[" && topOfQueue != "{") { //move expressions from the queue until it encounters the beginning of the parenthesis
                result.push(topOfQueue);
                queue.pop();

                topOfQueue = queue.top();
            }

            queue.pop(); //remove the beginning of the parenthesis from the queue
        }
        else if (isOperation(token)) { //if the token is a mathematical operation
            if (queue.empty() || OperationPriority[token] > OperationPriority[queue.top()]) { //je¿eli stack pomocniczy jest pusty, lub priorytet ostatniego wyrazu w kolejce jest ni¿szy
                queue.push(token); //dodaj token do kolejki
            }
            else {
                while (!queue.empty()) { //move all tokens from the queue that have a lower priority to the result
                    if (OperationPriority[queue.top()] < OperationPriority[token])
                        break;

                    result.push(queue.top());
                    queue.pop();
                }

                queue.push(token);//add the token to the queue
            }
        }
        else { //token is a number
            result.push(token); //add to the result
        }

        operation.pop();
    }

    while (!queue.empty()) { //when finished, add the queue to the result
        result.push(queue.top());
        queue.pop();
    }

    checkForDoubleMinus(result);

    operation = result;
}

bool doMath(string a, string b, string op, stack<string>& queue) {
    return OperationFunctions[op](a, b, op, queue);
}

string calculateAnswer(stack<string>& postfix) {
    stack<string> queue, operation = postfix;

    while (!operation.empty()) {
        string token = operation.top();

        if (isOperation(token)) { //if token is an arithmetic operation
            string a = queue.top(); //get 2 numbers from the queue
            queue.pop();

            string b = queue.empty() ? "buf" : queue.top(); //if the stack is empty, it means that the action requires only 1 number, so the 2nd number is replaced by a temporary “buf”

            if (b != "buf") { //if there is only 1 number at the action, replace the 2nd number with a temporary “buf”
                queue.pop();
            }

            if (!doMath(a, b, token, queue)) {
                return "not";
            }
        }
        else { //token is a number
            queue.push(token); //add to queue
        }

        operation.pop();
    }

    return queue.top(); //the only number in the queue is the result
}

string calculateWithVariable(stack<string> func, string variable, long double i) {
    stack<string> operation = func;

    reverseStack(operation, variable, to_string(i)); //replace unknown with value

    ShuntingYardAlgorithm(operation);

    return calculateAnswer(operation); //return the calculated value
}
