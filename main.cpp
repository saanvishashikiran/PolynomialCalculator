#include "Polynomial.h"
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    string command = "";
    Polynomial* polynomial1 = nullptr;
    Polynomial* polynomial2 = nullptr;

    cout << "Enter one of the following commands: ZERO, ARBITRARY, PRINT, EVAL, ADD, SUB, MULT, EXP, MOD, QUIT" << endl;
    
    while (true) {
        cout << "> ";  //promping for user input
        // cin >> command;
        // cin.ignore();  //ignoring any remaining newline characters in the input buffer
        
        getline(cin, command);

        size_t start = command.find_first_not_of(" \t");
        if (start == string::npos) {
            command = "";  // case where the command is all spaces
        } else {
            size_t end = command.find_last_not_of(" \t");
            command = command.substr(start, end - start + 1);
        }
        
        if (command == "ZERO") {
            delete polynomial1;
            polynomial1 = new Polynomial();
            cout << "Polynomial initialized to ZERO." << endl;
        } else if (command == "ARBITRARY") {
            cout << "Enter an arbitrary polynomial: " << endl;
            string input;
            getline(cin, input); // Read the rest of the line for polynomial input
            if (polynomial1) delete polynomial1; // Clean up previous polynomial if needed
            polynomial1 = new Polynomial(input);   
            cout << "This is your input" << endl;
            polynomial1->print();         
        } else if (command == "PRINT") {
            if (polynomial1) 
            {
                polynomial1->print();
            }
            else 
            {
                cout << "No polynomial to print." << endl;
            }
        } else if (command == "EVAL") {
           if(polynomial1)
           {
            int x; 
            cout << "Enter an x value: " << endl;
            cin >> x;
            cin.ignore();
            int result = polynomial1->evaluate(x);
            cout << "Your polynomial evaluated at " << x << " is " << result << endl;
           } 
        } else if (command == "ADD") {
            string input;
            cout << "Enter polynomial to add:" << endl;
            getline(cin, input);
            Polynomial temp(input);
            if (polynomial1)
            {
                *polynomial1 += temp;
                cout << "The result of polynomial addition is: ";
                polynomial1->print();
                cout << endl;
            }
            else
            {
                cout << "There is no polynomial to add to.";
            }
        } else if (command == "SUB") {
            string input;
            cout << "Enter polynomial to subtract:" << endl;
            getline(cin, input);
            Polynomial temp(input);
            if (polynomial1)
            {
                *polynomial1 -= temp;
                cout << "The result of polynomial subtraction is: ";
                polynomial1->print();
                cout << endl;
            }
            else
            {
                cout << "There is no polynomial to subtract from.";
            }
        } else if (command == "MULT") {
            string input;
            cout << "Enter the integer/polynomial you want to multiply: " << endl;
            getline(cin, input);
            Polynomial temp(input);
            if (polynomial1)
            {
                *polynomial1 *= temp;
                cout << "The result of integer/polynomial multiplication is: ";
                polynomial1->print();
                cout << endl;
            }
            else
            {
                cout << "There is no polynomial to multiply with.";
            }
        } else if (command == "EXP") {
            int exponent;
            cout << "Enter the power you want to exponentiate to:" << endl;
            cin >> exponent;
            cin.ignore();
            if (polynomial1)
            {
                polynomial1->exponentiate(exponent);
                cout << "The result of polynomial exponentiation is:";
                polynomial1->print();
                cout << endl;
            }
            else
            {
                cout << "There is no power to exponentiate to.";
            }

        } else if (command == "MOD") {
                if (polynomial1) {
                cout << "Enter polynomial for modulus operation:" << endl;
                string input;
                getline(cin, input);
                Polynomial other(input);
                cout << "Your input was ";
                other.print();
                cout << endl;
                // if (other.head == nullptr || other.head->coefficient != 1) {
                //     cout << "The leading coefficient of the divisor polynomial must be 1." << endl;
                // } else {
                    polynomial1->modulus(other);
                    cout << "The result of polynomial modulus is: ";
                    polynomial1->print();
                    cout << endl;
                // }
            } else {
                cout << "There is no polynomial to perform modulus with." << endl;
            }
        } else if (command == "QUIT") {
            break;
        } else{
            cout << "Error: Unknown Command:" << command << endl;
        }
    }

    // Clean up
    delete polynomial1;
    delete polynomial2;

    return 0;
}