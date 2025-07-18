#include "main.h"

int main() {
    string command = "";
    Polynomial* polynomial1 = nullptr;
    Polynomial* polynomial2 = nullptr;

    cout << "Welcome! To use this polynomial calculator, type a command along with your polynomial in the specified format in a single line (exact same format as listed in test data)." << endl;
    cout << "Please do NOT enter a command and enter without a numerical input in the same line." << endl;
    cout << "Example input: 'MOD 5 4 6 5 4 -3 3 6 2 -3 1 3 1 2 -3 1 2 0'" << endl;
    cout << "Enter one of the following commands: ZERO, ARBITRARY, PRINT, EVAL, ADD, SUB, MULT, EXP, MOD, QUIT followed by the necessary numerical inputs!" << endl;
    
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
        
        if (command.substr(0,4) == "ZERO") {
            if (polynomial1)
            {
                delete polynomial1;
            }            
            
            polynomial1 = new Polynomial();
            cout << "Polynomial initialized to ZERO." << endl;
            polynomial1->print();
            cout << endl;


        } else if (command.substr(0,9) == "ARBITRARY") {
            if (polynomial1)
            {
                delete polynomial1;
            }
            
            string input = command.substr(10);
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


        } else if (command.substr(0,5) == "PRINT") {
            if (polynomial1)
            {
                delete polynomial1;
            }

            string input = command.substr(6);
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



        } else if (command.substr(0,4) == "EVAL") {
            string input = command.substr(5);
            std::string polynomialPart = input.substr(0, input.find_last_of(' '));
            int x = std::stoi(input.substr(input.find_last_of(' ') + 1)); // Extract x from input

            Polynomial polynomial(polynomialPart); //initializing polynomial
            int result = polynomial.evaluate(x); //evaluating using the polynomial part
            cout << "Polynomial input: ";
            polynomial.print();
            cout << "Your polynomial evaluated at " << x << " is " << result <<  "\n" << endl;



        } else if (command.substr(0,3) == "ADD") {
            if (polynomial1)
            {
                polynomial1->reset();
            }
            if (polynomial2)
            {
                polynomial2->reset();
            }

            string input = command.substr(4);

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
        


        } else if (command.substr(0,3) == "SUB") {
            if (polynomial1)
            {
                polynomial1->reset();
            }
            if (polynomial2)
            {
                polynomial2->reset();
            }
            
            string input = command.substr(4);

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



        } else if (command.substr(0,4) == "MULT") {
            if (polynomial1)
            {
                polynomial1->reset();
            }
            if (polynomial2)
            {
                polynomial2->reset();
            }

            string input = command.substr(5);

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
            


        } else if (command.substr(0,3) == "EXP") {
            string input = command.substr(4);

            //trimming leading and trailing whitespace
            size_t start = input.find_first_not_of(" \t");
            size_t end = input.find_last_not_of(" \t");
            if (start == string::npos || end == string::npos) {
                cout << "Error: Invalid input format. Ensure you include both polynomial and exponent." << endl;
                continue;
            }
            
            input = input.substr(start, end - start + 1);

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
                exponent = stoi(input.substr(spacePos + 1));
            } catch (const invalid_argument&) {
                cout << "Error: Invalid exponent format. It must be an integer." << endl;
                continue;
            }

            //clearing previous contents of polynomial1 if needed
            if (polynomial1) 
            {
                polynomial1->reset();
            } 

            //ensuring polynomial1 is initialized correctly
            if (polynomial1 == nullptr) {
                polynomial1 = new Polynomial(polynomialPart); //initializing if null
            } else {
                *polynomial1 = Polynomial(polynomialPart); //reseting with new polynomial part
            }

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



        } else if (command.substr(0,3) == "MOD") {
            if (polynomial1)
            {
                polynomial1->reset();
            }
            if (polynomial2)
            {
                polynomial2->reset();
            }
            
            string input = command.substr(4);

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
            
            

        } else if (command.substr(0,4) == "QUIT") {
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