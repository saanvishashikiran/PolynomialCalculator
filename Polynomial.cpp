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
    
    //insert at front if list is empty or if exponent is greater than the first term (greatest 1st)
    if (head == nullptr || head->exponent < exponent)
    {
        newNode->next = head;
        head = newNode;
        return;
    }

    //creating pointers to linked list
    Node* current = head;
    Node* previous = nullptr;

    //traversing to search for insertion point (this makes the function O(n))
    while (current != nullptr && current->exponent > exponent)
    {
        previous = current;
        current = current->next;
    }

    if (current != nullptr && current->exponent == exponent)
    {
        current->coefficient += coefficient;
        delete newNode;
        if (current->coefficient == 0)
        {
            //removing node if coefficient changes to 0
            if (previous != nullptr)
            {
                previous->next = current->next; //if there is a previous node
            }
            else
            {
                head = current->next; //if the node is first
            }
            delete current;
        }
    }
    else //handles the case where the new term needs to be inserted into the list w/o replacing an existing term
    {
        newNode->next = current;
        if (previous != nullptr)
        {
            previous->next = newNode;
        }
        else //if previous is nullptr
        {
            head = newNode;
        }
    }
}




//combining polynomials helper function

void Polynomial::combine(const Polynomial& other, int sign)
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
}



//implementing public methods

//overloaded addition operator
Polynomial& Polynomial::operator+=(const Polynomial& other) 
{
    combine(other, 1);
    return *this;
    
    // Node* current = other.head;

    // while (current != nullptr)
    // {
    //     insert(current->coefficient, current->exponent);
    //     current = current->next;
    // }
    
    // return *this;

    // Node* current1 = head;
    // Node* current2 = other.head;
    // Node* prev = nullptr;

    // while (current1 != nullptr && current2 != nullptr)
    // {   
    //     if (current1->exponent > current2->exponent)
    //     {
    //         prev = current1;
    //         current1 = current1->next;
    //     }
    //     else if (current1->exponent < current2->exponent)
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
    //         newNode->next = current1;
    //         prev = newNode;
    //         current2 = current2->next;
    //     }
    //     else 
    //     {
    //         current1->coefficient += current2->coefficient;
    //         if (current1->coefficient == 0)
    //         {
    //             //skipping over this since the coefficient is now 0
    //             if (prev != nullptr)
    //             {
    //                 prev->next = current1->next;
    //             }
    //             else
    //             {
    //                 head = current1->next;
    //             }
    //             delete current1;
    //             if (prev != nullptr) 
    //             {
    //                 current1 = prev->next;
    //             } 
    //             else 
    //             {
    //                 current1 = head;
    //             }
    //         }
    //         else
    //         {
    //             prev = current1;
    //             current1 = current1->next;
    //         }
    //         current2 = current2->next;
    //     }
    // }

    // while (current2 != nullptr) 
    // {
    //     Node* newNode = new Node(current2->coefficient, current2->exponent);
    //     if (prev != nullptr) 
    //     {
    //         prev->next = newNode;
    //     } 
    //     else 
    //     {
    //         head = newNode;
    //     }
    //     prev = newNode;
    //     current2 = current2->next;
    // }

    return *this;

    // if (current1 == nullptr)
    // {
    //     current1->next = current2;
    // }

    // //when we get to insertion point, we can call

    // return *this;

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
            insert(current1->coefficient * current2->coefficient, current1->exponent + current2->exponent); 
            current2 = current2->next;
        }
        current1 = current1->next;
    }

    return *this; //original has been modified!
    // Polynomial temp;
    // Node* current1 = head;


    // while (current1 != nullptr)
    // {
    //     Node* current2 = other.head;
    //     while (current2 != nullptr) // moving through linked lists and multiplying terms
    //     {
    //         temp.insert(current1->coefficient * current2->coefficient, current1->exponent + current2->exponent);
    //         current2 = current2->next;
    //     }
    //     current1 = current1->next;
    // }


    // clear(); //clearing current polynomial
    // head = temp.head; //assigning the result to the current polynomial
    // temp.head = nullptr;


    // return *this;
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
        cout << "1 0 0" << endl; //printing "1 0 0" for polynomials initialized to zero
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



//evaluate function
int Polynomial::evaluate(int x) const 
{
    int evaluatedPoly = 0;
    Node* current = head;

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
        result *= polynomial; //setting result to y * y * base because n is an odd number
    }
    else //if n is even
    {
        Polynomial y = polynomial;
        y.exponentiate(n/2);
        result = y;
        result *= y; //setting result to y * y
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



//modulus function
Polynomial* Polynomial::modulus(Polynomial& other)  
{
    if (other.head == nullptr || other.head->coefficient != 1)
    {
        cout << "The leading coefficient of the divisor polynomial must be 1." << endl;
        return this;
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
    }
    *this = remainder;
    return this;
   
    // //change this so that mod returns the original polynomial with modifications
    // Polynomial* result = new Polynomial();
    // return result;
}