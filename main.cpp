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
        cout << "> "; 
        
        getline(cin, command);

        size_t start = command.find_first_not_of(" \t");
        if (start == string::npos) {
            command = "";  // case where the command is all spaces
        } else {
            size_t end = command.find_last_not_of(" \t");
            command = command.substr(start, end - start + 1);
        }
        
        if (command == "ZERO") {
            if (polynomial1)
            {
                delete polynomial1;
            }            
            
            polynomial1 = new Polynomial();
            cout << "Polynomial initialized to ZERO." << endl;
            polynomial1->print();



        } else if (command == "ARBITRARY") {
            if (polynomial1)
            {
                delete polynomial1;
            }
            
            cout << "Enter an arbitrary polynomial: " << endl;
            string input;
            getline(cin, input); //reading the rest of the line for polynomial input

            polynomial1 = new Polynomial(input);   
            cout << "This is your input" << endl;
            if (polynomial1) 
            {
                polynomial1->print();
                cout << endl;
            }
            else 
            {
                cout << "No arbitrary polynomial to print." << endl;
            }


        } else if (command == "PRINT") {
            if (polynomial1)
            {
                delete polynomial1;
            }

            cout << "Enter the polynomial you would like to print: " << endl;
            string input;
            getline(cin, input);

            polynomial1 = new Polynomial(input);
            cout << "Printed polynomial input: " << endl;
            if (polynomial1) 
            {
                polynomial1->print();
                cout << endl;
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
            cout << "Your polynomial evaluated at " << x << " is " << result <<  "\n" << endl;



        } else if (command == "ADD") {
            if (polynomial1)
            {
                polynomial1->reset();
            }
            if (polynomial2)
            {
                polynomial2->reset();
            }

            string input;
            cout << "Enter both polynomials you would like to add as a single string: " << endl;
            getline(cin, input);

            if (readPolynomials(input, polynomial1, polynomial2)) {
                cout << "You are asking to add ";
                if (polynomial1) 
                {
                    polynomial1->print();
                }
                cout << " and ";
                if (polynomial2) 
                {
                    polynomial2->print();
                }               
                *polynomial1 = *polynomial1 + *polynomial2; //using the overloaded operator+
                cout << "The result of polynomial addition is: ";
                if (polynomial1) 
                {
                    polynomial1->print();
                }
                cout << endl;
            } else {
                cout << "Invalid input format." << endl;
            }
        


        } else if (command == "SUB") {
            if (polynomial1)
            {
                polynomial1->reset();
            }
            if (polynomial2)
            {
                polynomial2->reset();
            }
            
            string input;
            cout << "Enter both polynomials you would like to subtract as a single string: " << endl;
            getline(cin, input);

            if (readPolynomials(input, polynomial1, polynomial2)) {
                cout << "You are asking to subtract ";
                if (polynomial2) 
                {
                    polynomial2->print();
                }           
                cout << " from ";
                if (polynomial1) 
                {
                    polynomial1->print();
                }           
                *polynomial1 = *polynomial1 - *polynomial2; //using the overloaded operator-
                cout << "The result of polynomial subtraction is: ";
                if (polynomial1) 
                {
                    polynomial1->print();
                }           
                cout << endl;
            } else {
                cout << "Invalid input format." << endl;
            }



        } else if (command == "MULT") {
            if (polynomial1)
            {
                polynomial1->reset();
            }
            if (polynomial2)
            {
                polynomial2->reset();
            }
            string input;
            cout << "Enter both polynomials you would like to multiply as a single string: " << endl;
            getline(cin, input);

            if (readPolynomials(input, polynomial1, polynomial2)) {
                cout << "You are asking to multiply ";
                if (polynomial1) 
                {
                    polynomial1->print();
                }           
                cout << " and ";
                if (polynomial2) 
                {
                    polynomial2->print();
                }           
                *polynomial1 = *polynomial1 * *polynomial2; //using the overloaded operator*
                cout << "The result of polynomial multiplication is: ";
                if (polynomial1) 
                {
                    polynomial1->print();
                }        
                cout << endl;
            } else {
                cout << "Invalid input format." << endl;
            }
            


        } else if (command == "EXP") {
            cout << "Enter the polynomial and the power you want to exponentiate to as a single string: " << endl;
            string input;
            getline(cin, input);

            //finding the position of the last space in the input
            size_t spacePos = input.find_last_of(' ');
            if (spacePos == string::npos) {
                cout << "Error: Invalid input format. Ensure you include both polynomial and exponent." << endl;
                continue;
            }

            //extracting polynomial part and exponent
            string polynomialPart = input.substr(0, spacePos);
            int exponent;
            try {
                exponent = std::stoi(input.substr(spacePos + 1));
            } catch (const std::invalid_argument&) {
                cout << "Error: Invalid exponent format. It must be an integer." << endl;
                continue;
            }

            //clearing previous contents of polynomial1 if needed
            if (polynomial1) 
            {
                polynomial1->reset();
            } 

            //initializing the polynomial with the polynomialPart
            *polynomial1 = Polynomial(polynomialPart);

            //performing exponentiation
            polynomial1->exponentiate(exponent);

            //printing the result
            cout << "Your polynomial raised to the power of " << exponent << " is: ";
            if (polynomial1) 
            {
                polynomial1->print();
            }        
            else 
            {
                cout << "Invalid input format." << endl;
            }
            cout << endl;



        } else if (command == "MOD") {
            if (polynomial1)
            {
                polynomial1->reset();
            }
            if (polynomial2)
            {
                polynomial2->reset();
            }
            string input;
            cout << "Enter both polynomials you would like to conduct modulus with as a single string: " << endl;
            getline(cin, input);

            if (readPolynomials(input, polynomial1, polynomial2)) {
                cout << "You are asking to calculate ";
                if (polynomial1) 
                {
                    polynomial1->print();
                }        
                cout << " mod ";
                if (polynomial2) 
                {
                    polynomial2->print();
                }        
                Polynomial px;
                Polynomial* returnPoly = &px;
                *returnPoly = (*polynomial1 %= *polynomial2); //using the overloaded operator%=
                cout << "The result of polynomial modulus calculation is: ";
                if (returnPoly)
                {
                    returnPoly->print();
                }
                cout << endl;
            } else {
                cout << "Invalid input format." << endl;
            }
            
            

        } else if (command == "QUIT") {
            delete polynomial1;
            delete polynomial2;
            return 0;



        } else{
            cout << "Error: Unknown Command:" << command << endl;
        }
    }

    // Clean up
    delete polynomial1;
    delete polynomial2;

    return 0;
}