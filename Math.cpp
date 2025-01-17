#define _USE_MATH_DEFINES

#include <string>
#include <stack>
#include <iostream>
#include <cmath>

using namespace std;

//functions return a result via queue.push(to_string(RESULT));
//if the function returns false, it means that the value is undefined, e.g. log(-3)
//functions like 2+5 give 2 numbers, but functions like abs(x) give only 1 number
//if 2 number does not exist, then b will be set to “buf”
//if the function uses only 1 value, and the second value is given it should be returned to the queue before adding the result

bool sum(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);
    long double num2 = stod(b);

    queue.push(to_string(num2 + num1));
    return true;
}

bool substracion(string a, string b, string op, stack<string>& queue) {
    if (b != "buf") { //2 figures (2-3) are given
        long double num1 = stod(a);
        long double num2 = stod(b);

        queue.push(to_string(num2 - num1));
    }
    else { //only 1 number (-3) is given
        long double num1 = stod(a);
        queue.push(to_string(-num1));
    }
    return true;
}

bool multiply(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);
    long double num2 = stod(b);

    queue.push(to_string(num1 * num2));

    return true;
}

bool powC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);
    long double num2 = stod(b);

    long double ans = pow(num2, num1);

    queue.push(to_string(ans));

    return true;
}

bool divide(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);
    long double num2 = stod(b);

    if (num1 == 0) { //cannot be divided by 0
        return false;
    }

    queue.push(to_string(num2 / num1));

    return true;
}

bool sinC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    queue.push(to_string(sin(num1)));

    return true;
}

bool cosC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    queue.push(to_string(cos(num1)));

    return true;
}

bool tgC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);


    queue.push(to_string(tan(num1)));

    return true;
}

bool cotC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    queue.push(to_string(1 / tan(num1)));

    return true;
}

bool arcsinC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    if (num1 > 1 || num1 < -1) {
        return false;
    }

    queue.push(to_string(asin(num1)));

    return true;
}

bool arccosC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    if (num1 > 1 || num1 < -1) {
        return false;
    }

    queue.push(to_string(acos(num1)));

    return true;
}

bool arctgC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    queue.push(to_string(atan(num1)));

    return true;
}

bool arccotC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    queue.push(to_string(M_PI_2 - atan(num1)));

    return true;
}

bool LogarithmLN(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    if (num1 <= 0)
        return false;

    queue.push(to_string(log(num1)));

    return true;
}

bool Logarithm(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    if (num1 <= 0)
        return false;

    queue.push(to_string(log10(log(num1))));

    return true;
}

bool absC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    queue.push(to_string(abs(num1)));

    return true;
}

bool squareRoot(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    if (num1 < 0) {
        return false;
    }

    queue.push(to_string(sqrt(num1)));

    return true;
}

bool cubeRoot(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    if (num1 < 0) {
        queue.push(to_string(-pow(-num1, 1/3.f)));
    }
    else {
        queue.push(to_string(pow(num1, 1 / 3.f)));
    }

    return true;
}

bool MsinC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    queue.push(to_string(-sin(num1)));

    return true;
}

bool McosC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    queue.push(to_string(-cos(num1)));

    return true;
}

bool MtgC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);


    queue.push(to_string(-tan(num1)));

    return true;
}

bool McotC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    queue.push(to_string(-1 / tan(num1)));

    return true;
}

bool MarcsinC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    if (num1 > 1 || num1 < -1) {
        return false;
    }

    queue.push(to_string(-asin(num1)));

    return true;
}

bool MarccosC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    if (num1 > 1 || num1 < -1) {
        return false;
    }

    queue.push(to_string(-acos(num1)));

    return true;
}

bool MarctgC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    queue.push(to_string(-atan(num1)));

    return true;
}

bool MarccotC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    queue.push(to_string(-M_PI_2 + atan(num1)));

    return true;
}

bool MLogarithmLN(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    if (num1 <= 0)
        return false;

    queue.push(to_string(-log(num1)));

    return true;
}

bool MLogarithm(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    if (num1 <= 0)
        return false;

    queue.push(to_string(-log10(log(num1))));

    return true;
}

bool MabsC(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    queue.push(to_string(-abs(num1))); //pierwiastek bez parametru

    return true;
}

bool MsquareRoot(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    if (num1 < 0) {
        return false;
    }

    queue.push(to_string(-sqrt(num1)));

    return true;
}

bool McubeRoot(string a, string b, string op, stack<string>& queue) {
    long double num1 = stod(a);

    if (b != "buff") //if there is a second number, return it to the queue
        queue.push(b);

    if (num1 < 0) {
        queue.push(to_string(pow(-num1, 1 / 3.f)));
    }
    else {
        queue.push(to_string(-pow(num1, 1 / 3.f)));
    }

    return true;
}