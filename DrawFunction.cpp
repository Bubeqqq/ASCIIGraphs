#include <string>
#include <stack>
#include <iostream>
#include <vector>
#include <limits>
#include <Windows.h>

#include "Help.h"
#include "ShuntingYardAlgorithm.h"

using namespace std;

int FunctionWidth = 100, FunctionHeight = 50;

int stepX = 5; //scale of the graph

string FunctionUnknown = "x";

bool autoSize = false;

bool whiteMode = true;

char Square = 219; //mark of which the chart makes up

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//getters setter
//needed for settings in the Menu.cpp file

void setWhiteMode(int a) {
    whiteMode = a == 1;
}

int getWhiteMode() {
    return whiteMode;
}

void setWidth(int a) {
    autoSize = false;
    if (a <= 0)
        FunctionWidth = 1;
    else
        FunctionWidth = a;
}

void setHeight(int a) {
    autoSize = false;
    if (a <= 0)
        FunctionHeight = 1;
    else
        FunctionHeight = a;
}

int getWidth() {
    return FunctionWidth;
}

int getHeight() {
    return FunctionHeight;
}

void setStepX(int a) {
    if (a <= 0)
        stepX = 1;
    else
        stepX = a;
}

int getStepX() {
    return stepX;
}

void setUnknown(int a) {
    FunctionUnknown = string(1, a);
}

int getUnknown() {
    return FunctionUnknown.at(0);
}

void setAutoSize(int a) { //Set the chart size to match the size of the console window
    if (a == 1) {
        int width, height;

        getConsoleSize(width, height);

        FunctionWidth = width / 2;
        FunctionHeight = height / 2 - 1;
        autoSize = true;
    }
    else {
        autoSize = false;
    }
}

int getAutoSize() {
    return autoSize;
}

//

void setTextWhite() {
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void setTextBlack() {
    SetConsoleTextAttribute(hConsole, 0 | 0 | 0 | 0);
}

void drawWhiteSpaces(string& s) {
    if (whiteMode)
        setTextWhite();
    else
        setTextBlack();
    cout << s;
    s = "";
}

void setGraphColor() {
    if (whiteMode) {
        SetConsoleTextAttribute(hConsole, 0 | 0 | FOREGROUND_BLUE | FOREGROUND_INTENSITY); //blue
    }
    else {
        setTextWhite();
    }
}

void drawFunction(stack<string> func) {
    if (getAutoSize()) {
        setAutoSize(1); //set automatic chart size
    }

    long double max = ULLONG_MAX;

    vector<long double> yValues;

    for (long double x = -FunctionWidth; x <= FunctionWidth; x++) { //calculate the y-values for each x
        string s = calculateWithVariable(func, FunctionUnknown, x / stepX);

        long double value = 0;

        if (s != "not") {
            value = stod(s); //value is defined
        }
        else {
            value = max; //value is undefined (e.g. 0 for x/0)
        }

        yValues.push_back(value);
    }

    string s = ""; //white characters are saved and later displayed at once

    cout << endl;
    for (long double y = FunctionHeight; y >= -FunctionHeight; y--) { //for each point in the system
        for (int x = -FunctionWidth + 1; x <= FunctionWidth; x++) {

            long double valueBefore = yValues.at(x + FunctionWidth - 1); //value for x - 1
            long double value = yValues.at(x + FunctionWidth); //current value
            long double ty = y / stepX; //y after taking into account the scale

            bool first = ty >= valueBefore && ty <= value;
            bool second = ty >= value && ty <= valueBefore;
            bool third = valueBefore != max && value != max;

            if (abs(ty - value) <= 0.5f / stepX) { //draw the calculated point
                drawWhiteSpaces(s); //draw white marks in front of

                setGraphColor();
                cout << Square;
            }
            else if ((first || second) && third) { //fill in between points
                /*
                    (ty >= valueBefore && ty <= value) -> if the function is increasing and the point is between the previously calculated points
                    (ty >= value && ty <= valueBefore) -> if the function is decreasing and the point is between the previously calculated points
                    (valueBefore != max && value != max) -> previously calculated values are defined
                */
  
                drawWhiteSpaces(s);//draw white marks in front of

                setGraphColor();
                cout << Square;
            }
            else if (x == 0 && y == 0) { //center of the graph
                drawWhiteSpaces(s);//draw white marks in front of
                
                SetConsoleTextAttribute(hConsole, 0 | 0 | 0 | FOREGROUND_INTENSITY); //draw the axis, as a gray point
                cout << Square;
            }
            else if (y == 0) { //x axis
                drawWhiteSpaces(s);//draw white marks in front of

                SetConsoleTextAttribute(hConsole, 0 | 0 | 0 | FOREGROUND_INTENSITY); //draw the axis, as a gray point
                cout << Square;
            }
            else if (x == 0) { //y axis
                drawWhiteSpaces(s);//draw white marks in front of

                SetConsoleTextAttribute(hConsole, 0 | 0 | 0 | FOREGROUND_INTENSITY);//draw the axis, as a gray point
                cout << Square;
            }
            else { //everything else
                s.append(string(1, Square)); //add white sign
            }
        }
        if(s != "")
            s.append("\n");
        else {
            cout << "\n";
        }
    }
    if (s != "") {
        drawWhiteSpaces(s);
    }
    setTextWhite();
}

