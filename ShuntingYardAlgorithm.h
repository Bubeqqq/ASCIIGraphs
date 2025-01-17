#pragma once

#include <string>
#include <stack>

using namespace std;

void ShuntingYardAlgorithm(stack<string>& operation);

void Setup();

string calculateAnswer(stack<string>& postfix);

string calculateWithVariable(stack<string> func, string variable, long double i);

bool isOperation(string s);