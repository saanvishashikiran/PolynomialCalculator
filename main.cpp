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
            cout << "Enter the polynomial you would like to print: " << endl;
            string input;
            getline(cin, input);
            polynomial1 = new Polynomial(input);
            cout << "This is your input!" << endl;
            if (polynomial1) 
            {
                polynomial1->printInput(input);
            }
            else 
            {
                cout << "No polynomial to print." << endl;
            }
        } else if (command == "EVAL") {
            cout << "Enter the polynomial you would like to evaluate and the x value you want evaluate at." << endl;
            string input;
            getline(cin, input);
            std::string polynomialPart = input.substr(0, input.find_last_of(' '));
            int x = std::stoi(input.substr(input.find_last_of(' ') + 1)); // Extract x from input

            Polynomial polynomial(polynomialPart); // Initialize polynomial
            int result = polynomial.evaluate(polynomialPart); // Evaluate using the polynomial part
            cout << "Your polynomial evaluated at " << x << " is " << result << endl;
            // Polynomial polynomial(input);
            // if(polynomial)
            // {
            //     int result = polynomial1->evaluate(input);
            //     cout << "Your polynomial evaluated at " << input.substr(input.find_last_of(' ') + 1) << " is " << result << endl;
            // } 
            // else
            // {
            //     cout << "No polynomial to evaluate." << endl;
            // }
        } else if (command == "ADD") {
            string input;
            cout << "Enter both polynomials you would like to add as a single string: " << endl;
            getline(cin, input);
            Polynomial temp(input);
            Polynomial* polynomial1 = nullptr;
            Polynomial* polynomial2 = nullptr;
            if (readPolynomials(input, polynomial1, polynomial2)) {
                cout << "You are asking to add ";
                polynomial1->print();
                cout << " and ";
                polynomial2->print();
                *polynomial1 = *polynomial1 + *polynomial2; // Use the overloaded operator+
                cout << "The result of polynomial addition is: ";
                polynomial1->print();
                cout << endl;
            } else {
                cout << "Invalid input format." << endl;
            }
            
            delete polynomial1; // Clean up memory
            delete polynomial2;
            // if (polynomial1)
            // {
            //     *polynomial1 += temp;
            //     cout << "The result of polynomial addition is: ";
            //     polynomial1->print();
            //     cout << endl;
            // }
            // else
            // {
            //     cout << "There is no polynomial to add to.";
            // }
        } else if (command == "SUB") {
            string input;
            cout << "Enter both polynomials you would like to subtract as a single string: " << endl;
            getline(cin, input);
            Polynomial temp(input);
            Polynomial* polynomial1 = nullptr;
            Polynomial* polynomial2 = nullptr;

            if (readPolynomials(input, polynomial1, polynomial2)) {
                cout << "You are asking to subtract ";
                polynomial2->print();
                cout << " from ";
                polynomial1->print();
                *polynomial1 -= *polynomial2; // Use the overloaded operator+
                cout << "The result of polynomial subtraction is: ";
                polynomial1->print();
                cout << endl;
            } else {
                cout << "Invalid input format." << endl;
            }
            
            delete polynomial1; // Clean up memory
            delete polynomial2;
            // if (polynomial1)
            // {
            //     *polynomial1 -= temp;
            //     cout << "The result of polynomial subtraction is: ";
            //     polynomial1->print();
            //     cout << endl;
            // }
            // else
            // {
            //     cout << "There is no polynomial to subtract from.";
            // }
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