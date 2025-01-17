#include <string>
#include <stack>
#include <iostream>
#include <Windows.h>
#include <vector>

#include "DrawFunction.h"

using namespace std;

typedef void (*refresh)();

bool isNumber(char& c) {
    return ((c >= 48 && c <= 57) || c == 46 || c == 44); //true if c is in the 0-9 range or is '.' or ','
}

bool isLetter(char& c) {
    return (c >= 97 && c <= 122); //true if c is in the a-z range
}

bool isNumber(string s) {
    if (isNumber(s.at(0)))
        return true;

    if (s.size() > 1 && s.at(0) == '-' && isNumber(s.at(1))) {
        return true;
    }

    return false;
}

void reverseStack(stack<string>& stackToReverse) { // reverses the order
    stack<string> reversedStack;

    while (!stackToReverse.empty()) {
        reversedStack.push(stackToReverse.top());
        stackToReverse.pop();
    }

    stackToReverse = reversedStack;
}

void printStack(stack<string>& stackToPrint) {
    stack<string> toPrint = stackToPrint;

    cout << endl << endl;

    while (!toPrint.empty()) {
        cout << "\"" << toPrint.top() << "\" ";
        toPrint.pop();
    }
    cout << endl << endl;
}

void reverseStack(stack<string>& stackToReverse, string n, string value) { //reverses the order and converts the unknown to the given value
    stack<string> reversedStack;

    while (!stackToReverse.empty()) {
        string top = stackToReverse.top();

        if (top == n) { //conversion of an unknown into a value
            top = value;
        }
        else if (top.size() == 2 && top.at(0) == '-' && top.at(1) == getUnknown()) { //an unknown with a minus
            if (value.at(0) == '-') {
                top = value.substr(1, value.size()); //remove the minus
            }
            else {
                string minus = "-"; //add a minus
                minus.append(value);
                top = minus;
            }
        }

        reversedStack.push(top);
        stackToReverse.pop();
    }

    stackToReverse = reversedStack;
}

void getConsoleSize(int& width, int& height) { //Sets width, height to the dimensions of the console. This allows the chart to be automatically sized
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

int getInt(refresh refr){ //repeats until the user enters a number
    int value;
    if (cin >> value) return value;

    cin.clear();
    cin.ignore(1000000, '\n');

    cout << "\033[A"; //deletes last line
    cout << "\33[2K";
    cout.flush();

    if (refr != NULL) //Calling the complement function (when you remove something you were not supposed to remove)
        refr();

    return getInt(refr);
}

int getChar(refresh refr) { //repeats until the user types the character
    char value;
    if (cin >> value) return value;

    cin.clear();
    cin.ignore(1000000, '\n');

    cout << "\033[A"; //deletes last line
    cout << "\33[2K";
    cout.flush();

    if (refr != NULL) //Calling the complement function (when you remove something you were not supposed to remove)
        refr();

    return getInt(refr);
}