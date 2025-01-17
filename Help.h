#pragma once

#include <string>
#include <stack>
#include <vector>

using namespace std;

typedef void (*refresh)();

bool isNumber(char& c);

bool isLetter(char& c);

void reverseStack(stack<string>& stackToReverse);

void printStack(stack<string>& stackToPrint);

void reverseStack(stack<string>& stackToReverse, string n, string value);

void getConsoleSize(int& width, int& height);

int getInt(refresh refr);

int getChar(refresh refr);

bool isNumber(string s);