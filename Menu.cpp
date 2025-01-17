#include <iostream>
#include <string>
#include <vector>

#include "DrawFunction.h"
#include "Help.h"

using namespace std;

typedef void (*Operation)(int a); //returns true if the variable is of type char
typedef int (*getValue)();

int getZero() { //it works, perfectly, no problems here. You can smoothly skip it, and go to the remaining of the program
	return 0;
}

class Setting {
public:
	Operation op;
	getValue getV;
	string name;
	bool valueIsChar;

	Setting(Operation op, string name, getValue getV, char valueIsChar) {
		this->op = op;
		this->name = name;
		this->valueIsChar = valueIsChar;
		this->getV = getV;
	}
};

vector<Setting> settings;

void SetupMenu() {
	Setting s(NULL, "Return", getZero, false);
	settings.push_back(s);
	Setting s1(setWidth, "Graph Width", getWidth, false);
	settings.push_back(s1);
	Setting s2(setHeight, "Graph Height", getHeight, false);
	settings.push_back(s2);
	Setting s3(setStepX, "Graph Scale", getStepX, false);
	settings.push_back(s3);
	Setting s4(setUnknown, "Unknown Symbol", getUnknown, true);
	settings.push_back(s4);
	Setting s5(setAutoSize, "Automatic Sizing", getAutoSize, false);
	settings.push_back(s5);
	Setting s6(setWhiteMode, "White Mode", getWhiteMode, false);
	settings.push_back(s6);

	setAutoSize(1);
}

int option = 0;
void say() { //after clearing the screen it continues to display
	cout << "(" << option << ") " << settings.at(option).name << " -> ";
}

void OpenMenu() {
	do {
		if (getAutoSize()) {
			setAutoSize(1); //set the size of the chart to display correctly in the settings 
		}

		system("cls");

		for (int i = 0; i < settings.size(); i++) { //display all settings
			cout << "(" << i << ") " << settings.at(i).name << " -> ";

			if (settings.at(i).valueIsChar) {
				cout << (char) settings.at(i).getV() << endl; //setting with chars
			}
			else {
				cout << settings.at(i).getV() << endl; //other settings
			}

		}

		option = getInt(NULL);

		if (option < 0 || option >= settings.size() || option == 0) { //return to menu
			system("cls");
			break;
		}

		system("cls");
		cout << "(" << option << ") " << settings.at(option).name << " -> "; //change setting values
		if (!settings.at(option).valueIsChar) {
			int value = 0; //for numerical settings
			value = getInt(say);

			settings.at(option).op(value);
		}
		else {
			char value = 0; //for settings with variable char (unknown)
			value = getChar(say);
			settings.at(option).op(value);
		}

	} while (true);
}