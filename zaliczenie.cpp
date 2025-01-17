#include <iostream>

#include <string>
#include <stack>

#include "Help.h"
#include "Load.h"
#include "ShuntingYardAlgorithm.h"
#include "DrawFunction.h"
#include "Menu.h"
#include "Check.h"

using namespace std;

int main()
{
    setTextWhite();
    Setup(); //set all the orders of operations
    SetupMenu(); //set all settings

    bool running = true;
    while (running) {
        int input = -1;
        cout << "(0) Exit " << endl;
        cout << "(1) Draw a mathematical function " << endl;
        cout << "(2) Settings " << endl;

        input = getInt(NULL);

        if (input == 2) {
            OpenMenu();
        }
        else if (input == 1) {
            int i = 1; //records the decision whether to draw more charts
            
            while (i == 1) {
                system("cls");
                
                cout << "Mathematical function formula : ";
                cin.ignore(1000, '\n'); //doesn't work without it (total time spent on this : 2 days)
                string s;
                getline(cin, s);

                if (s == "")
                    continue;

                stack<string> st;
                loadAsStack(s, st);

                if(check(st)) //checks the correctness of the entered formula
                    drawFunction(st);

                cout << "(0) Return " << endl;
                cout << "(1) Next" << endl;

                i = getInt(NULL);

                system("cls");
            }
        }else {
            return 0;
        }

    }
}
