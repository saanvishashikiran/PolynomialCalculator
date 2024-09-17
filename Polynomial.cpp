#include "Polynomial.h"
#include <iostream>
using namespace std;


//implementing constructors

//implementation for parametrized constructor
Polynomial::Polynomial(const std::string& input) : head(nullptr) {
    istringstream iss(input);
    int numberOfTerms;
    iss >> numberOfTerms;

    Node* current = nullptr;

    for (int i = 0; i < numberOfTerms; i++)
    {
        int coefficient, exponent;
        iss >> coefficient >> exponent;
        if (coefficient != 0)
        {
            Node* newNode = new Node(coefficient, exponent);
            if (head == nullptr)
            {
                head = newNode;
                current = head;
            }
            else
            {
                current->next = newNode;
                current = newNode;
            }
        }
    }
}



//copy constructor
Polynomial::Polynomial(const Polynomial& other) : head(nullptr) {
    // Node* current = other.head;

    // while (current != nullptr) {
    //     insert(current->coefficient, current->exponent);
    //     current = current->next;
    // }

    if (other.head == nullptr)
    {
        return;
    }

    head = new Node(other.head->coefficient, other.head->exponent);
    Node* currentOther = other.head->next;
    Node* currentThis = head;

    while (currentOther != nullptr)
    {
        currentThis->next = new Node(currentOther->coefficient, currentOther->exponent);
        currentThis = currentThis->next;
        currentOther = currentOther->next;
    }
}



//implementing destructor
Polynomial::~Polynomial()
{
    clear();
}



//implementing helper functions

//clear helper function
void Polynomial::clear() 
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    head = nullptr;
}



//inserting a term helper function
void Polynomial::insert(int coefficient, int exponent) 
{
    Node* newNode = new Node(coefficient, exponent);
    newNode->next = head;
    head = newNode;  // Insert at the front, no sorting
    // Node* newNode = new Node(coefficient, exponent);
    
    // //insert at front if list is empty or if exponent is greater than the first term (greatest 1st)
    // if (head == nullptr || head->exponent < exponent)
    // {
    //     newNode->next = head;
    //     head = newNode;
    //     return;
    // }

    // //creating pointers to linked list
    // Node* current = head;
    // Node* previous = nullptr;

    // //traversing to search for insertion point (this makes the function O(n))
    // while (current != nullptr && current->exponent > exponent)
    // {
    //     previous = current;
    //     current = current->next;
    // }

    // if (current != nullptr && current->exponent == exponent)
    // {
    //     current->coefficient += coefficient;
    //     delete newNode;
    //     if (current->coefficient == 0)
    //     {
    //         //removing node if coefficient changes to 0
    //         if (previous != nullptr)
    //         {
    //             previous->next = current->next; //if there is a previous node
    //         }
    //         else
    //         {
    //             head = current->next; //if the node is first
    //         }
    //         delete current;
    //     }
    // }
    // else //handles the case where the new term needs to be inserted into the list w/o replacing an existing term
    // {
    //     newNode->next = current;
    //     if (previous != nullptr)
    //     {
    //         previous->next = newNode;
    //     }
    //     else //if previous is nullptr
    //     {
    //         head = newNode;
    //     }
    // }
}


//helper function for cleaning up polynomials
void Polynomial::cleanup() {
    if (!head) return;

    Node* current = head;
    Node* prev = nullptr;

    // Bubble sort-like pass to sort by exponent
    bool sorted;
    do {
        sorted = true;
        current = head;
        prev = nullptr;

        while (current && current->next) {
            if (current->exponent < current->next->exponent) {
                // Swap nodes
                sorted = false;
                Node* temp = current->next;
                current->next = temp->next;
                temp->next = current;

                if (prev) {
                    prev->next = temp;
                } else {
                    head = temp;
                }
                prev = temp;
            } else {
                prev = current;
                current = current->next;
            }
        }
    } while (!sorted);

    // Pass to combine like terms and eliminate zero terms
    current = head;
    prev = nullptr;
    while (current) {
        if (current->next && current->exponent == current->next->exponent) {
            // Combine coefficients
            current->coefficient += current->next->coefficient;
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
        } else if (current->coefficient == 0) {
            // Remove zero coefficient terms
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
            current = prev ? prev->next : head;
        } else {
            prev = current;
            current = current->next;
        }
    }
}



bool readPolynomials(const string& input, Polynomial*& polynomial1, Polynomial*& polynomial2) {
    istringstream iss(input);
    
    int termsInPolynomial1 = 0, termsInPolynomial2 = 0;
    
    //reading the number of terms in the first polynomial
    if (!(iss >> termsInPolynomial1)) {
        cout << "Error: Invalid input for terms in first polynomial." << endl;
        return false;
    }
    
    cout << termsInPolynomial1 << " terms in polynomial1\n" << endl;

    //reading coefficients and exponents for the first polynomial
    string polynomial1String = to_string(termsInPolynomial1) + " ";
    for (int i = 0; i < termsInPolynomial1; ++i) {
        int coefficient, exponent;
        if (!(iss >> coefficient >> exponent)) {
            cout << "Error: Invalid input for polynomial 1." << endl;
            return false;
        }
        polynomial1String += to_string(coefficient) + " " + to_string(exponent) + " ";
    }

    //debugging output for first polynomial
    cout << "Parsed polynomial 1: " << polynomial1String << endl;

    //initializing poly1 with the parsed string
    delete polynomial1;
    polynomial1 = new Polynomial(polynomial1String);

    //reading the number of terms in the second polynomial
    if (!(iss >> termsInPolynomial2)) {
        cout << "Error: Invalid input for terms in second polynomial." << endl;
        return false;
    }

    cout << termsInPolynomial2 << " terms in polynomial2\n" << endl;

    //reading coefficients and exponents for the second polynomial
    string polynomial2String = to_string(termsInPolynomial2) + " ";
    for (int i = 0; i < termsInPolynomial2; ++i) {
        int coefficient, exponent;
        if (!(iss >> coefficient >> exponent)) {
            cout << "Error: Invalid input for polynomial 2." << endl;
            return false;
        }
        polynomial2String += to_string(coefficient) + " " + to_string(exponent) + " ";
    }

    //debugging output for second polynomial
    cout << "Parsed polynomial 2: " << polynomial2String << endl;

    //initializing poly2 with the parsed string
    delete polynomial2;
    polynomial2 = new Polynomial(polynomial2String);

    return true;
}



//implementing public methods

//overloaded addition operator
Polynomial& Polynomial::operator+=(const Polynomial& other) 
{
    Node* current1 = head;
    Node* current2 = other.head;
    Node* prev = nullptr;

    while (current1 != nullptr && current2 != nullptr)
    {   
        if (current1->exponent > current2->exponent)
        {
            prev = current1;
            current1 = current1->next;
        }
        else if (current1->exponent < current2->exponent)
        {
            Node* newNode = new Node(current2->coefficient, current2->exponent);
            if (prev != nullptr)
            {
                prev->next = newNode;
            }
            else 
            {
                head = newNode;
            }
            newNode->next = current1;
            prev = newNode;
            current2 = current2->next;
        }
        else 
        {
            current1->coefficient += current2->coefficient;
            if (current1->coefficient == 0)
            {
                //skipping over this since the coefficient is now 0
                if (prev != nullptr)
                {
                    prev->next = current1->next;
                }
                else
                {
                    head = current1->next;
                }
                delete current1;
                if (prev != nullptr) 
                {
                    current1 = prev->next;
                } 
                else 
                {
                    current1 = head;
                }
            }
            else
            {
                prev = current1;
                current1 = current1->next;
            }
            current2 = current2->next;
        }
    }

    while (current2 != nullptr) 
    {
        Node* newNode = new Node(current2->coefficient, current2->exponent);
        if (prev != nullptr) 
        {
            prev->next = newNode;
        } 
        else 
        {
            head = newNode;
        }
        prev = newNode;
        current2 = current2->next;
    }

    return *this;
}



//overloaded subtraction operator
Polynomial& Polynomial::operator-=(const Polynomial& other) 
{
    // Node* current = other.head;

    // while (current != nullptr)
    // {
    //     insert(-current->coefficient, current->exponent);
    //     current = current->next;
    // }

    // return *this;
    Node* current1 = head;
    Node* current2 = other.head;
    Node* prev = nullptr;

    while (current1 != nullptr && current2 != nullptr)
    {   
        if (current1->exponent > current2->exponent)
        {
            prev = current1;
            current1 = current1->next;
        }
        else if (current1->exponent < current2->exponent)
        {
            Node* newNode = new Node(-current2->coefficient, current2->exponent);
            if (prev != nullptr)
            {
                prev->next = newNode;
            }
            else 
            {
                head = newNode;
            }
            newNode->next = current1;
            prev = newNode;
            current2 = current2->next;
        }
        else 
        {
            current1->coefficient -= current2->coefficient;
            if (current1->coefficient == 0)
            {
                //skipping over this since the coefficient is now 0
                if (prev != nullptr)
                {
                    prev->next = current1->next;
                }
                else
                {
                    head = current1->next;
                }
                delete current1;
                if (prev != nullptr) 
                {
                    current1 = prev->next;
                } 
                else 
                {
                    current1 = head;
                }
            }
            else
            {
                prev = current1;
                current1 = current1->next;
            }
            current2 = current2->next;
        }
    }

    while (current2 != nullptr) 
    {
        Node* newNode = new Node(-current2->coefficient, current2->exponent);
        if (prev != nullptr) 
        {
            prev->next = newNode;
        } 
        else 
        {
            head = newNode;
        }
        prev = newNode;
        current2 = current2->next;
    }

    return *this;
}



//overloaded multiplication operator 
Polynomial& Polynomial::operator*=(const Polynomial& other) 
{
    Polynomial polynomial1(*this); //copying original polynomial

    clear(); //clearing original polynomial

    Node* current1 = polynomial1.head; //pointer to original polyomial

    while (current1 != nullptr)
    {
        Node* current2 = other.head;
        while (current2 != nullptr) // moving through linked lists and multiplying terms
        {
            //insert(current1->coefficient * current2->coefficient, current1->exponent + current2->exponent); 
            int newCoefficient = current1->coefficient * current2->coefficient;
            int newExponent = current1->exponent + current2->exponent;

            insert(newCoefficient, newExponent);

            current2 = current2->next;
        }
       
        current1 = current1->next;
    }

    cleanup();
    return *this; //original has been modified!

    
    // Polynomial polynomial1(*this); //copying original polynomial
    // clear(); //clearing original polynomial
    // Node* current1 = polynomial1.head; //pointer to original polyomial

    // while (current1 != nullptr)
    // {
    //     Node* current2 = other.head;
    //     while (current2 != nullptr) // moving through linked lists and multiplying terms
    //     {
    //         insert(current1->coefficient * current2->coefficient, current1->exponent + current2->exponent); 
    //         current2 = current2->next;
    //     }
    //     current1 = current1->next;
    // }

    // return *this; //original has been modified!
    // // Polynomial temp;
    // // Node* current1 = head;


    // // while (current1 != nullptr)
    // // {
    // //     Node* current2 = other.head;
    // //     while (current2 != nullptr) // moving through linked lists and multiplying terms
    // //     {
    // //         temp.insert(current1->coefficient * current2->coefficient, current1->exponent + current2->exponent);
    // //         current2 = current2->next;
    // //     }
    // //     current1 = current1->next;
    // // }


    // // clear(); //clearing current polynomial
    // // head = temp.head; //assigning the result to the current polynomial
    // // temp.head = nullptr;


    // // return *this;
}



//overloaded assignment operator
Polynomial& Polynomial::operator=(const Polynomial& other)
{
    if (this != &other)
    {
        clear();
        Node* current = other.head;
        while (current != nullptr)
        {
            insert(current->coefficient, current->exponent);
            current = current->next;
        }
    }

    return *this;
}



//print function
void Polynomial::print() const 
{
    if (!head) {
        cout << "0" << endl; //printing "1 0 0" for polynomials initialized to zero
    }

    Node* current = head;
    while (current) //while current is not nullptr
    {
        //making sure all positive terms besides the first one are preceded by a plus sign
        if (current != head && current->coefficient > 0)
        {
            cout << " + ";
        }
        else if (current->coefficient < 0) //making sure all negative terms are preceded by a minus sign
        {
            cout << " - ";
        }
        if (current->coefficient != 0)
        {
            cout << abs(current->coefficient); //printing abs value since sign has been managed
            if (current->exponent > 0)
            {
                cout << "x";
                if (current->exponent > 1)
                {
                    cout << "^" << current->exponent;
                }
            }
        }
        current = current->next;
    }
    cout << endl;
}



void Polynomial::printInput(const std::string& input)
{
    istringstream iss(input);
    int numberOfTerms;
    iss >> numberOfTerms; //reading the number of terms

    Polynomial tempPoly; // Temporary polynomial to construct from input

    for (int i = 0; i < numberOfTerms; ++i) 
    {
        int coefficient, exponent;
        iss >> coefficient >> exponent; // Read coefficient and exponent
        tempPoly.insert(coefficient, exponent); // Use the insert function to add terms to the polynomial
    }

    // Now print the constructed polynomial
    tempPoly.cleanup();
    tempPoly.print(); // Call the existing print method
}


//evaluate function
int Polynomial::evaluate(const std::string& input) const 
{
    istringstream iss(input);
    int numberOfTerms, x;

    iss >> numberOfTerms;

    Polynomial tempPoly;

    int evaluatedPoly = 0;

    for (int i = 0; i < numberOfTerms; i++)
    {
        int coefficient, exponent;
        iss >> coefficient >> exponent;

        tempPoly.insert(coefficient, exponent);
        // tempPoly.cleanup();
        
        // int evaluatedTerm = coefficient * pow(x, exponent);
        // evaluatedPoly += evaluatedTerm;
    }

    iss >> x;

    tempPoly.cleanup();

    Node* current = tempPoly.head;

    while (current)
    {
        int evaluatedTerm = current->coefficient * pow(x, current->exponent);
        evaluatedPoly += evaluatedTerm; 
        current = current->next;
    }

    return evaluatedPoly;
}



//exponentiation function
Polynomial* Polynomial::exponentiate(int n)  
{
    if (n < 0)
    {
        cout << "Error, exponent must be non-negative!" << endl;
        return this;
    }

    if (n == 0)
    {
        *this = Polynomial("1 1 0");
        return this;
    }    

    Polynomial polynomial(*this);
    Polynomial result("1 1 0");

    //binary exponentiation! follow textbook example exactly and use recursion
    if (n % 2 == 1) //if n is odd
    {
        Polynomial y = polynomial;
        y.exponentiate((n - 1)/2); //polynomial^((n-1)/2)
        result = y; 
        result *= y; //setting result to y * y
        result.cleanup();
        result *= polynomial; //setting result to y * y * base because n is an odd number
        result.cleanup();
    }
    else //if n is even
    {
        Polynomial y = polynomial;
        y.exponentiate(n/2);
        result = y;
        result *= y; //setting result to y * y
        result.cleanup();
    }


    // while (n > 0)
    // {
    //     //only odd exponents need the result to be multiplied by polynomial before moving on
    //     if (n % 2 == 1)
    //     {
    //         result *= polynomial;
    //     }
    //     polynomial *= polynomial;
    //     n /= 2;
    // }

    //result.cleanup();
    
    *this = result;
    return this;

    // //change this so that exp returns the original polynomial with modifications
    // Polynomial* result = new Polynomial();
    // return result;
}



// //addNode helper function for modulus function
// void Polynomial::addNode(int coeff, int exp)
// {
//     Node** curr = &head;
//     while (*curr && (*curr)->exponent > exp)
//     {
//         curr = &(*curr)->next;
//     }

//     if (*curr && (*curr)->exponent == exp)
//     {
//         (*curr)->coefficient += coeff;
//         if ((*curr)->coefficient == 0)
//         {
//             Node* mustDelete = *curr;
//             *curr = (*curr)->next;
//             delete mustDelete;
//         }
//     }
//     else
//     {
//         Node* newNode = new Node();
//         newNode->coefficient = coeff;
//         newNode->exponent = exp;
//         newNode->next = *curr;
//         *curr = newNode;
//     }

// }



// //modulus function
// Polynomial* Polynomial::modulus(Polynomial& other)  
// {
//     if (other.head == nullptr || other.head->coefficient != 1)
//     {
//         cout << "The leading coefficient of the divisor polynomial must be 1." << endl;
//         return this;
//     }

//     // int otherDegree = other.head->exponent;
//     Polynomial divisor(other);
//     Polynomial remainder(*this);
    
//     while (remainder.head != nullptr && remainder.head->exponent >= divisor.head->exponent)
//     {
//         int expDiff = remainder.head->exponent - divisor.head->exponent;
//         int coeff = remainder.head->coefficient;

//         Polynomial multiple;
        
//         Node* otherNode = divisor.head;

//         while (otherNode != nullptr)
//         {
//             multiple.insert(coeff * otherNode->coefficient, expDiff + otherNode->exponent); // go back and take this out when logic is working, write a simple addNode O(1) function that makes a new node w coeff and exp
//             otherNode = otherNode->next;
//         }

//         remainder -= multiple;
//     }
//     *this = remainder;
//     return this;
   
//     // //change this so that mod returns the original polynomial with modifications
//     // Polynomial* result = new Polynomial();
//     // return result;
// }

// #include "Polynomial.h"
// #include <iostream>
// using namespace std;


// //implementing constructors

// //implementation for parametrized constructor
// Polynomial::Polynomial(const std::string& input) : head(nullptr) {
//     istringstream iss(input);
//     int numberOfTerms;
//     iss >> numberOfTerms;

//     Node* current = nullptr;

//     for (int i = 0; i < numberOfTerms; i++)
//     {
//         int coefficient, exponent;
//         iss >> coefficient >> exponent;
//         if (coefficient != 0)
//         {
//             Node* newNode = new Node(coefficient, exponent);
//             if (head == nullptr)
//             {
//                 head = newNode;
//                 current = head;
//             }
//             else
//             {
//                 current->next = newNode;
//                 current = newNode;
//             }
//         }
//     }
// }



// //copy constructor
// Polynomial::Polynomial(const Polynomial& other) : head(nullptr) {
//     // Node* current = other.head;

//     // while (current != nullptr) {
//     //     insert(current->coefficient, current->exponent);
//     //     current = current->next;
//     // }

//     if (other.head == nullptr)
//     {
//         return;
//     }

//     head = new Node(other.head->coefficient, other.head->exponent);
//     Node* currentOther = other.head->next;
//     Node* currentThis = head;

//     while (currentOther != nullptr)
//     {
//         currentThis->next = new Node(currentOther->coefficient, currentOther->exponent);
//         currentThis = currentThis->next;
//         currentOther = currentOther->next;
//     }
// }



// //implementing destructor
// Polynomial::~Polynomial()
// {
//     clear();
// }



// //implementing helper functions

// //clear helper function
// void Polynomial::clear() 
// {
//     while (head != nullptr)
//     {
//         Node* temp = head;
//         head = head->next;
//         delete temp;
//     }

//     head = nullptr;
// }

// // //TEST INSERT FUNCTION:
// // void Polynomial::insert(int coefficient, int exponent) {
// //     //only appending non-zero terms
// //     if (coefficient == 0) {
// //         return;
// //     }

// //     Node* newNode = new Node(coefficient, exponent);

// //     //managing the special case of if the list is empty
// //     if (head == nullptr) {
// //         head = newNode;
// //         tail = newNode;
// //         return;
// //     }

// //     //append to the end of the list
// //     tail->next = newNode;
// //     tail = newNode;
    

//     //another test insert function
//     // if (coefficient == 0) {
//     //     return; // No need to insert zero coefficient terms
//     // }

//     // // Create the new node
//     // Node* newNode = new Node(coefficient, exponent);

//     // // If the list is empty or the new node should be at the beginning
//     // if (head == nullptr || head->exponent < exponent) {
//     //     newNode->next = head;
//     //     head = newNode;
//     //     if (tail == nullptr) {
//     //         tail = newNode; // Update tail if the list was empty
//     //     }
//     //     return;
//     // }

//     // // Traverse the list to find the correct insertion point
//     // Node* current = head;
//     // Node* prev = nullptr;

//     // while (current != nullptr && current->exponent > exponent) {
//     //     prev = current;
//     //     current = current->next;
//     // }

//     // // If we find a term with the same exponent, combine the coefficients
//     // if (current != nullptr && current->exponent == exponent) {
//     //     current->coefficient += coefficient;
//     //     if (current->coefficient == 0) {
//     //         // Remove the term if its coefficient becomes zero
//     //         if (prev != nullptr) {
//     //             prev->next = current->next;
//     //         } else {
//     //             head = current->next;
//     //         }
//     //         if (current == tail) {
//     //             tail = prev; // Update tail if the last node was removed
//     //         }
//     //         delete current;
//     //     }
//     //     delete newNode; // No need to keep the new node
//     // } else {
//     //     // Insert the new node in the correct position
//     //     if (prev != nullptr) {
//     //         prev->next = newNode;
//     //     }
//     //     newNode->next = current;
//     //     if (current == nullptr) {
//     //         tail = newNode; // Update tail if new node is the last node
//     //     }
//     // }
// // }


// //inserting a term helper function
// void Polynomial::insert(int coefficient, int exponent) 
// {   
//     //initializing a new node
//     Node* newNode = new Node(coefficient, exponent);
    
//     //insert at front if list is empty or if exponent is greater than the first term (greatest 1st)
//     if (head == nullptr || head->exponent < exponent)
//     {
//         newNode->next = head;
//         head = newNode;
//         if (tail == nullptr)
//         {
//             tail = newNode;
//         }
//         return;
//     }
    
//     //inserting at the end when the list is not empty
//     if (tail != nullptr)
//     {
//         tail->next = newNode;
//         tail = newNode;
//     }
//     else
//     {
//         head = tail = newNode; //if tail is nullptr both head and tail must point to newNode
//     }

// //     // //creating pointers to linked list
// //     // Node* current = head;
// //     // Node* previous = nullptr;

// //     // //traversing to search for insertion point (this makes the function O(n))
// //     // while (current != nullptr && current->exponent > exponent)
// //     // {
// //     //     previous = current;
// //     //     current = current->next;
// //     // }

// //     // if (current != nullptr && current->exponent == exponent)
// //     // {
// //     //     current->coefficient += coefficient;
// //     //     delete newNode;
// //     //     if (current->coefficient == 0)
// //     //     {
// //     //         //removing node if coefficient changes to 0
// //     //         if (previous != nullptr)
// //     //         {
// //     //             previous->next = current->next; //if there is a previous node
// //     //         }
// //     //         else
// //     //         {
// //     //             head = current->next; //if the node is first
// //     //         }
// //     //         delete current;
// //     //     }
// //     // }
// //     // else //handles the case where the new term needs to be inserted into the list w/o replacing an existing term
// //     // {
// //     //     newNode->next = current;
// //     //     if (previous != nullptr)
// //     //     {
// //     //         previous->next = newNode;
// //     //     }
// //     //     else //if previous is nullptr
// //     //     {
// //     //         head = newNode;
// //     //     }
// //     // }
// }



// // //clean-up helper function

// //this version is not working, re-wrote below
// // void Polynomial::cleanup()
// // {
// //     if (head == nullptr)
// //     {
// //         tail = nullptr;
// //         return;
// //     }

// //     Node* current = head;

// //     while (current != nullptr)
// //     {
// //         Node* comparisonNode = current->next;
// //         Node* prev = current;

// //         //traversing list in order to combine like terms
// //         while (comparisonNode != nullptr)
// //         {
// //             if (comparisonNode->exponent == current->exponent)
// //             {
// //                 //combining coefficients for like terms (same exponent degree!)
// //                 current->coefficient += comparisonNode->coefficient;
// //                 Node* temp = comparisonNode;
// //                 comparisonNode = comparisonNode->next;
// //                 delete temp;

// //                 //removing node if the coefficient has become 0
// //                 if (current->coefficient == 0)
// //                 {
// //                     if (prev == current) //removing the head node if the head's coefficient is 0
// //                     {
// //                         head = current->next;
// //                         delete current;
// //                         current = head;
// //                     }
// //                     else //removing a node that is not the head if its coefficient is 0
// //                     {
// //                         prev->next = current->next;
// //                         delete current;
// //                         current = prev->next;
// //                     }
                    
// //                     //updating tail if the list is now empty
// //                     if (head == nullptr)
// //                     {
// //                         tail = nullptr;
// //                     }

// //                     //continuing from previous node
// //                     break;
// //                 }
// //                 //moving onto next node
// //                 else 
// //                 {
// //                     comparisonNode = current->next;
// //                 }
// //             }
// //             else
// //             {
// //                 comparisonNode = comparisonNode->next;
// //             }
// //         }
        
// //         //moving onto next node
// //         if (current != nullptr)
// //         {
// //             prev = current;
// //             current = current->next;
// //         }
// //     }

// //     //updating the tail pointer so that it points to the last node
// //     if (head == nullptr)
// //     {
// //         tail = nullptr;
// //     }
// //     else
// //     {
// //         Node* temp = head;
// //         while (temp->next != nullptr)
// //         {
// //             temp = temp->next;
// //         }
// //         tail = temp;
// //     }

// // }



// // void Polynomial::cleanup() {
// //     if (head == nullptr) {
// //         tail = nullptr;
// //         return;
// //     }

// //     Node* current = head;
// //     Node* prev = nullptr;

// //     //traversing list in order to combine like terms
// //     while (current != nullptr) {
// //         prev = current;
// //         Node* inner = current->next;

// //         while (inner != nullptr) {
// //             if (inner->exponent == current->exponent) {
// //                 //combining like terms
// //                 current->coefficient += inner->coefficient;

// //                 //removing the redundant node
// //                 prev->next = inner->next;
// //                 delete inner;
// //                 inner = prev->next;
// //             } else {
// //                 prev = inner;
// //                 inner = inner->next;
// //             }
// //         }

// //         current = current->next;
// //     }

// //     //removing nodes with zero coefficient
// //     current = head;
// //     Node* prevNode = nullptr;
// //     while (current != nullptr) {
// //         if (current->coefficient == 0) {
// //             if (current == head) {
// //                 head = current->next;
// //                 delete current;
// //                 current = head;
// //             } else {
// //                 prevNode->next = current->next;
// //                 delete current;
// //                 current = prevNode->next;
// //             }
// //         } else {
// //             prevNode = current;
// //             current = current->next;
// //         }
// //     }

// //     //updating the tail pointer
// //     if (head == nullptr) {
// //         tail = nullptr;
// //     } else {
// //         Node* temp = head;
// //         while (temp->next != nullptr) {
// //             temp = temp->next;
// //         }
// //         tail = temp;
// //     }
// // }


// void Polynomial::cleanup() {
//     if (head == nullptr) {
//         tail = nullptr;
//         return;
//     }

//     //combining like terms
//     Node* current = head;
//     while (current != nullptr) {
//         Node* inner = current->next;
//         Node* prev = current;
        
//         while (inner != nullptr) {
//             if (inner->exponent == current->exponent) {
//                 current->coefficient += inner->coefficient;
//                 if (current->coefficient == 0) {
//                     //removing the term if coefficient becomes zero
//                     prev->next = inner->next;
//                     delete inner;
//                     inner = prev->next;
//                 } else {
//                     prev = inner;
//                     inner = inner->next;
//                 }
//             } else {
//                 prev = inner;
//                 inner = inner->next;
//             }
//         }

//         current = current->next;
//     }

//     //removing terms with zero coefficients
//     current = head;
//     Node* prevNode = nullptr;
//     while (current != nullptr) {
//         if (current->coefficient == 0) {
//             if (current == head) {
//                 head = current->next;
//                 delete current;
//                 current = head;
//             } else {
//                 prevNode->next = current->next;
//                 delete current;
//                 current = prevNode->next;
//             }
//         } else {
//             prevNode = current;
//             current = current->next;
//         }
//     }

//     //updating the tail pointer
//     if (head == nullptr) {
//         tail = nullptr;
//     } else {
//         Node* temp = head;
//         while (temp->next != nullptr) {
//             temp = temp->next;
//         }
//         tail = temp;
//     }
// }



// //implementing public methods

// //overloaded addition operator
// Polynomial& Polynomial::operator+=(const Polynomial& other) 
// {
//     // Node* current = other.head;

//     // while (current != nullptr)
//     // {
//     //     insert(current->coefficient, current->exponent);
//     //     current = current->next;
//     // }
    
//     // return *this;

//     Node* current1 = head;
//     Node* current2 = other.head;
//     Node* prev = nullptr;

//     while (current1 != nullptr && current2 != nullptr)
//     {   
//         if (current1->exponent > current2->exponent)
//         {
//             prev = current1;
//             current1 = current1->next;
//         }
//         else if (current1->exponent < current2->exponent)
//         {
//             Node* newNode = new Node(current2->coefficient, current2->exponent);
//             if (prev != nullptr)
//             {
//                 prev->next = newNode;
//             }
//             else 
//             {
//                 head = newNode;
//             }
//             newNode->next = current1;
//             prev = newNode;
//             current2 = current2->next;
//         }
//         else 
//         {
//             current1->coefficient += current2->coefficient;
//             if (current1->coefficient == 0)
//             {
//                 //skipping over this since the coefficient is now 0
//                 if (prev != nullptr)
//                 {
//                     prev->next = current1->next;
//                 }
//                 else
//                 {
//                     head = current1->next;
//                 }
//                 delete current1;
//                 if (prev != nullptr) 
//                 {
//                     current1 = prev->next;
//                 } 
//                 else 
//                 {
//                     current1 = head;
//                 }
//             }
//             else
//             {
//                 prev = current1;
//                 current1 = current1->next;
//             }
//             current2 = current2->next;
//         }
//     }

//     while (current2 != nullptr) 
//     {
//         Node* newNode = new Node(current2->coefficient, current2->exponent);
//         if (prev != nullptr) 
//         {
//             prev->next = newNode;
//         } 
//         else 
//         {
//             head = newNode;
//         }
//         prev = newNode;
//         current2 = current2->next;
//     }

//     return *this;

//     // if (current1 == nullptr)
//     // {
//     //     current1->next = current2;
//     // }

//     // //when we get to insertion point, we can call

//     // return *this;

// }



// //overloaded subtraction operator
// Polynomial& Polynomial::operator-=(const Polynomial& other) 
// {
//     // Node* current = other.head;

//     // while (current != nullptr)
//     // {
//     //     insert(-current->coefficient, current->exponent);
//     //     current = current->next;
//     // }

//     // return *this;
//     Node* current1 = head;
//     Node* current2 = other.head;
//     Node* prev = nullptr;

//     while (current1 != nullptr && current2 != nullptr)
//     {   
//         if (current1->exponent > current2->exponent)
//         {
//             prev = current1;
//             current1 = current1->next;
//         }
//         else if (current1->exponent < current2->exponent)
//         {
//             Node* newNode = new Node(-current2->coefficient, current2->exponent);
//             if (prev != nullptr)
//             {
//                 prev->next = newNode;
//             }
//             else 
//             {
//                 head = newNode;
//             }
//             newNode->next = current1;
//             prev = newNode;
//             current2 = current2->next;
//         }
//         else 
//         {
//             current1->coefficient -= current2->coefficient;
//             if (current1->coefficient == 0)
//             {
//                 //skipping over this since the coefficient is now 0
//                 if (prev != nullptr)
//                 {
//                     prev->next = current1->next;
//                 }
//                 else
//                 {
//                     head = current1->next;
//                 }
//                 delete current1;
//                 if (prev != nullptr) 
//                 {
//                     current1 = prev->next;
//                 } 
//                 else 
//                 {
//                     current1 = head;
//                 }
//             }
//             else
//             {
//                 prev = current1;
//                 current1 = current1->next;
//             }
//             current2 = current2->next;
//         }
//     }

//     while (current2 != nullptr) 
//     {
//         Node* newNode = new Node(-current2->coefficient, current2->exponent);
//         if (prev != nullptr) 
//         {
//             prev->next = newNode;
//         } 
//         else 
//         {
//             head = newNode;
//         }
//         prev = newNode;
//         current2 = current2->next;
//     }

//     return *this;
// }



// //overloaded multiplication operator 
// Polynomial& Polynomial::operator*=(const Polynomial& other) 
// {
//     Polynomial polynomial1(*this); //copying original polynomial

//     clear(); //clearing original polynomial

//     Node* current1 = polynomial1.head; //pointer to original polyomial

//     while (current1 != nullptr)
//     {
//         Node* current2 = other.head;
//         while (current2 != nullptr) // moving through linked lists and multiplying terms
//         {
//             //insert(current1->coefficient * current2->coefficient, current1->exponent + current2->exponent); 
//             int newCoefficient = current1->coefficient * current2->coefficient;
//             int newExponent = current1->exponent + current2->exponent;

//             insert(newCoefficient, newExponent);

//             current2 = current2->next;
//         }
       
//         current1 = current1->next;
//     }

//     cleanup();
//     return *this; //original has been modified!
//     // Polynomial temp;
//     // Node* current1 = head;


//     // while (current1 != nullptr)
//     // {
//     //     Node* current2 = other.head;
//     //     while (current2 != nullptr) // moving through linked lists and multiplying terms
//     //     {
//     //         temp.insert(current1->coefficient * current2->coefficient, current1->exponent + current2->exponent);
//     //         current2 = current2->next;
//     //     }
//     //     current1 = current1->next;
//     // }


//     // clear(); //clearing current polynomial
//     // head = temp.head; //assigning the result to the current polynomial
//     // temp.head = nullptr;


//     // return *this;
// }



// //overloaded assignment operator
// Polynomial& Polynomial::operator=(const Polynomial& other)
// {
//     if (this != &other)
//     {
//         clear();

//         Node* current = other.head;
//         while (current != nullptr)
//         {
//             insert(current->coefficient, current->exponent);
//             current = current->next;
//         }

//         //cleanup();
//     }

//     return *this;
// }



// //print function
// void Polynomial::print() const 
// {
//     if (!head) {
//         cout << "0" << endl; //printing "1 0 0" for polynomials initialized to zero
//     }

//     Node* current = head;
//     while (current) //while current is not nullptr
//     {
//         //making sure all positive terms besides the first one are preceded by a plus sign
//         if (current != head && current->coefficient > 0)
//         {
//             cout << " + ";
//         }
//         else if (current->coefficient < 0) //making sure all negative terms are preceded by a minus sign
//         {
//             cout << " - ";
//         }
//         if (current->coefficient != 0)
//         {
//             cout << abs(current->coefficient); //printing abs value since sign has been managed
//             if (current->exponent > 0)
//             {
//                 cout << "x";
//                 if (current->exponent > 1)
//                 {
//                     cout << "^" << current->exponent;
//                 }
//             }
//         }
//         current = current->next;
//     }
//     cout << endl;
// }



// //evaluate function
// int Polynomial::evaluate(int x) const 
// {
//     int evaluatedPoly = 0;
//     Node* current = head;

//     while (current)
//     {
//         int evaluatedTerm = current->coefficient * pow(x, current->exponent);
//         evaluatedPoly += evaluatedTerm;
//         current = current->next;
//     }

//     return evaluatedPoly;
// }



// //exponentiation function
// Polynomial* Polynomial::exponentiate(int n)  
// {
//     if (n < 0)
//     {
//         cout << "Error, exponent must be non-negative!" << endl;
//         return this;
//     }

//     if (n == 0)
//     {
//         *this = Polynomial("1 1 0");
//         return this;
//     }    

//     Polynomial polynomial(*this);
//     Polynomial result("1 1 0");

//     //binary exponentiation! follow textbook example exactly and use recursion
//     if (n % 2 == 1) //if n is odd
//     {
//         Polynomial y = polynomial;
//         y.exponentiate((n - 1)/2); //polynomial^((n-1)/2)
//         result = y; 
//         result *= y; //setting result to y * y
//         result *= polynomial; //setting result to y * y * base because n is an odd number
//     }
//     else //if n is even
//     {
//         Polynomial y = polynomial;
//         y.exponentiate(n/2);
//         result = y;
//         result *= y; //setting result to y * y
//     }


//     // while (n > 0)
//     // {
//     //     //only odd exponents need the result to be multiplied by polynomial before moving on
//     //     if (n % 2 == 1)
//     //     {
//     //         result *= polynomial;
//     //     }
//     //     polynomial *= polynomial;
//     //     n /= 2;
//     // }
    
//     *this = result;
//     return this;

//     // //change this so that exp returns the original polynomial with modifications
//     // Polynomial* result = new Polynomial();
//     // return result;
// }



// // //addNode helper function for modulus function
// // void Polynomial::addNode(int coeff, int exp)
// // {
// //     Node** curr = &head;
// //     while (*curr && (*curr)->exponent > exp)
// //     {
// //         curr = &(*curr)->next;
// //     }

// //     if (*curr && (*curr)->exponent == exp)
// //     {
// //         (*curr)->coefficient += coeff;
// //         if ((*curr)->coefficient == 0)
// //         {
// //             Node* mustDelete = *curr;
// //             *curr = (*curr)->next;
// //             delete mustDelete;
// //         }
// //     }
// //     else
// //     {
// //         Node* newNode = new Node();
// //         newNode->coefficient = coeff;
// //         newNode->exponent = exp;
// //         newNode->next = *curr;
// //         *curr = newNode;
// //     }

// // }



//modulus function
// Polynomial* Polynomial::modulus(Polynomial& other)  
Polynomial& Polynomial::operator%=(const Polynomial& other)
{
    if (other.head == nullptr || other.head->coefficient != 1)
    {
        cout << "The leading coefficient of the divisor polynomial must be 1." << endl;
        return *this;
    }

    // int otherDegree = other.head->exponent;
    Polynomial divisor(other);
    Polynomial remainder(*this);
    
    while (remainder.head != nullptr && remainder.head->exponent >= divisor.head->exponent)
    {
        int expDiff = remainder.head->exponent - divisor.head->exponent;
        int coeff = remainder.head->coefficient;

        Polynomial multiple;
        
        Node* otherNode = divisor.head;

        while (otherNode != nullptr)
        {
            multiple.insert(coeff * otherNode->coefficient, expDiff + otherNode->exponent); // go back and take this out when logic is working, write a simple addNode O(1) function that makes a new node w coeff and exp
            otherNode = otherNode->next;
        }

        remainder -= multiple;
        remainder.cleanup();
    }
    *this = remainder;
    return *this;
   
    // //change this so that mod returns the original polynomial with modifications
    // Polynomial* result = new Polynomial();
    // return result;
}