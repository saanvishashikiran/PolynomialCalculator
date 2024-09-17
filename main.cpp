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

            Polynomial polynomial(polynomialPart); //initializing polynomial
            int result = polynomial.evaluate(x); //evaluating using the polynomial part
            cout << "Polynomial input: ";
            polynomial.print();
            cout << "Your polynomial evaluated at " << x << " is " << result << endl;
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
                *polynomial1 += *polynomial2; //using the overloaded operator+=
                cout << "The result of polynomial addition is: ";
                polynomial1->print();
                cout << endl;
            } else {
                cout << "Invalid input format." << endl;
            }
            
            delete polynomial1; //cleaning up memory
            delete polynomial2;
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
                *polynomial1 -= *polynomial2; //using the overloaded operator-=
                cout << "The result of polynomial subtraction is: ";
                polynomial1->print();
                cout << endl;
            } else {
                cout << "Invalid input format." << endl;
            }
            
            delete polynomial1; //cleaning up memory
            delete polynomial2;
        } else if (command == "MULT") {
            string input;
            cout << "Enter both polynomials you would like to multiply as a single string: " << endl;
            getline(cin, input);
            Polynomial temp(input);
            Polynomial* polynomial1 = nullptr;
            Polynomial* polynomial2 = nullptr;

            if (readPolynomials(input, polynomial1, polynomial2)) {
                cout << "You are asking to multiply ";
                polynomial1->print();
                cout << " and ";
                polynomial2->print();
                *polynomial1 *= *polynomial2; //using the overloaded operator*=
                cout << "The result of polynomial multiplication is: ";
                polynomial1->print();
                cout << endl;
            } else {
                cout << "Invalid input format." << endl;
            }
            
            delete polynomial1; //cleaning up memory
            delete polynomial2;

        } else if (command == "EXP") {
            cout << "Enter the polynomial and the power you want to exponentiate to as a single string: " << endl;
            string input;
            getline(cin, input);

            // Find the position of the last space in the input
            size_t spacePos = input.find_last_of(' ');
            if (spacePos == string::npos) {
                cout << "Error: Invalid input format. Ensure you include both polynomial and exponent." << endl;
                continue;
            }

            // Extract polynomial part and exponent
            string polynomialPart = input.substr(0, spacePos);
            int exponent;
            try {
                exponent = std::stoi(input.substr(spacePos + 1));
            } catch (const std::invalid_argument&) {
                cout << "Error: Invalid exponent format. It must be an integer." << endl;
                continue;
            }

            // Initialize the polynomial
            delete polynomial1;
            polynomial1 = new Polynomial(polynomialPart);

            // Perform exponentiation
            polynomial1->exponentiate(exponent);

            // Print the result
            cout << "Polynomial input: ";
            polynomial1->print(); // Print the polynomial after exponentiation
            cout << "Your polynomial raised to the power of " << exponent << " is: ";
            polynomial1->print(); // Print the final polynomial after exponentiation
            cout << endl;
            // cout << "Enter the polynomial and the power you want to exponentiate to as a single string: " << endl;
            // string input;
            // getline(cin, input);
            // std::string polynomialPart = input.substr(0, input.find_last_of(' '));
            // int n = std::stoi(input.substr(input.find_last_of(' ') + 1)); // Extract x from input

            // Polynomial polynomial(polynomialPart); //initializing polynomial
            // int result = polynomial.exponentiate(n); //exponentiating using the polynomial part
            // cout << "Polynomial input: ";
            // polynomial.print();
            // cout << "Your polynomial raised to the power of " << n << " is " << result << endl;
            
            // // string input;
            // // cout << "Enter the polynomial and the power you want to exponentiate to as a single string: " << endl;
            // // getline(cin, input);
            // // istringstream iss(input);
            // // int termsInPolynomial1 = 0;

            // // if (!iss >> termsInPolynomial1)
            // // {
            // //     cout << "ERROR: Invalid input for terms in first polynomial." << endl;
            // // }

            // //     cout << termsInPolynomial1 << " terms in polynomial1\n" << endl;

            // // //reading coefficients and exponents for the first polynomial
            // // string polynomial1String = to_string(termsInPolynomial1) + " ";
            // // for (int i = 0; i < termsInPolynomial1; ++i) {
            // //     int coefficient, exponent;
            // //     if (!(iss >> coefficient >> exponent)) {
            // //         cout << "Error: Invalid input for polynomial 1." << endl;
            // //     }
            // //     polynomial1String += to_string(coefficient) + " " + to_string(exponent) + " ";
            // // }

            // // //debugging output for first polynomial
            // // cout << "Parsed polynomial 1: " << polynomial1String << endl;

            // // //initializing poly1 with the parsed string
            // // delete polynomial1;
            // // polynomial1 = new Polynomial(polynomial1String);

            // // int exponent;

            // // if (!(iss >> exponent)) {
            // //     cout << "Error: Invalid input for exponent." << endl;
            // // }

            // // if (polynomial1)
            // // {
            // //     polynomial1->exponentiate(exponent);
            // //     cout << "The result of polynomial exponentiation is:";
            // //     polynomial1->print();
            // //     cout << endl;
            // // }
            // // else
            // // {
            // //     cout << "There is no power to exponentiate to.";
            // // }

        } else if (command == "MOD") {
            string input;
            cout << "Enter both polynomials you would like to conduct modulus with as a single string: " << endl;
            getline(cin, input);
            Polynomial temp(input);
            Polynomial* polynomial1 = nullptr;
            Polynomial* polynomial2 = nullptr;

            if (readPolynomials(input, polynomial1, polynomial2)) {
                cout << "You are asking to calculate ";
                polynomial1->print();
                cout << " mod ";
                polynomial2->print();
                *polynomial1 %= *polynomial2; //using the overloaded operator*=
                cout << "The result of polynomial modulus calculation is: ";
                polynomial1->print();
                cout << endl;
            } else {
                cout << "Invalid input format." << endl;
            }
            
            delete polynomial1; //cleaning up memory
            delete polynomial2;
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