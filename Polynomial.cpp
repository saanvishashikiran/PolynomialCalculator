#include "Polynomial.h"
using namespace std;


/****************************************************************************
 *                                                                          *
 *                 class Polynomial Constructors & Destructor               *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                 Polynomial Parametrized Constructor                      *
 ****************************************************************************/

Polynomial::Polynomial(const std::string& input) : head(nullptr) {
    //reading in input
    istringstream iss(input);
    int numberOfTerms;
    iss >> numberOfTerms;

    //making a current pointer and initializing to nullptr
    Node* current = nullptr;

    //iterating through polynomial
    for (int i = 0; i < numberOfTerms; i++)
    {
        int coefficient, exponent;
        iss >> coefficient >> exponent; //reading into coefficient and exponent variables
        if (coefficient != 0)
        {
            Node* newNode = new Node(coefficient, exponent); //initializing node
            if (head == nullptr) //case where list is empty - adding in new node
            {
                head = newNode;
                current = head;
            }
            else //case where list is not empty - adding in new node
            {
                current->next = newNode;
                current = newNode;
            }
        } 
    }
}



/****************************************************************************
 *                       Polynomial Copy Constructor                        *
 ****************************************************************************/

Polynomial::Polynomial(const Polynomial& other) : head(nullptr), tail(nullptr) {
    //checking if list is empty
    if (other.head == nullptr)
    {
        return;
    }

    //creating new node for head of current polynomial
    head = new Node(other.head->coefficient, other.head->exponent);
    Node* currentOther = other.head->next;
    Node* currentThis = head;

    //iterating through remaining nodes of source polynomial
    while (currentOther != nullptr)
    {
        //creating a new node in current, copying coeff and exp from source
        currentThis->next = new Node(currentOther->coefficient, currentOther->exponent);
        currentThis = currentThis->next;
        currentOther = currentOther->next;
    }
}



/****************************************************************************
 *                         Polynomial Destructor                            *
 ****************************************************************************/
Polynomial::~Polynomial()
{
    clear(); //calling clear helper function
}



/****************************************************************************
 *                                                                          *
 *                  class Polynomial Private Helper Functions               *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                         Polynomial Clear Helper Function                 *
 ****************************************************************************/

void Polynomial::clear() 
{
    Node* current = head; //starting at head

    //iterating through linked list to delete each node
    while (current) {
        Node* next = current->next;
        delete current;  //freeing memory
        current = next; 
    }

    //avoiding dangling pointers by setting head and tail to nullptr to indicate an empty list
    head = nullptr;  
    tail = nullptr;  
}



/****************************************************************************
 *                        Polynomial Insert Helper Function                 *
 ****************************************************************************/
void Polynomial::insert(int coefficient, int exponent) 
{
    //creating a new node for the given coeff and exp
    Node* newNode = new Node(coefficient, exponent);
    
    if (!head) {
        //setting both head and tail to the new node if the list is empty
        head = newNode;
        tail = newNode;
    } else {
        //linking the new node to the current tail if the list is not empty
        tail->next = newNode; //setting next of current tail to the new node
        tail = newNode; //updating the tail to the new node
    }
}



/****************************************************************************
 *                       Polynomial Cleanup Helper Function                 *
 ****************************************************************************/

void Polynomial::cleanup() {
    //checking if list is empty
    if (!head) return;

    Node* current = head;
    Node* prev = nullptr;

    //using a bubble sort inspired technique in order to sort polynomial by exponent 
    //compares two terms at a time and swapping them if the next node has a greater exponent degree
    bool sorted;
    do {
        sorted = true;
        current = head;
        prev = nullptr;

        while (current && current->next) {
            if (current->exponent < current->next->exponent) {
                //swapping nodes if the next node has a higher exponent degree!
                sorted = false; //using a bool to track sorting status
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

    //passing through list again to combine like terms and eliminate zero terms
    current = head;
    prev = nullptr;
    while (current) {
        //will run as long as there is a next node and the exponent of current and next are equal
        if (current->next && (current->exponent == current->next->exponent)) {
            //combining coefficients
            current->coefficient = current->coefficient + current->next->coefficient;
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
        } else if (current->coefficient == 0) {
            //removing zero coefficient terms
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
            if (prev != nullptr) {
                current = prev->next;  //setting current to the next node if prev isn't null
            } else {
                current = head;        //setting current to head if prev is null
            }
        } else {
            //if there are no terms to combine or remove, keep reading through linked list!!
            prev = current;
            current = current->next;
        }
    }
}



/****************************************************************************
 *              Polynomial Reading Polynomials Helper Function              *
 ****************************************************************************/

bool readPolynomials(const string& input, Polynomial*& polynomial1, Polynomial*& polynomial2) {
    istringstream iss(input);
    
    int termsInPolynomial1 = 0, termsInPolynomial2 = 0;
    
    //reading the # of terms in the first polynomial
    if (!(iss >> termsInPolynomial1)) {
        cout << "Error: Invalid input for terms in first polynomial." << endl;
        return false;
    }
    
    cout << "\n" << termsInPolynomial1 << " terms in polynomial1" << endl;

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

    //initializing polymomial1 with the parsed string
    delete polynomial1;
    polynomial1 = new Polynomial(polynomial1String);

    //reading the # of terms in the second polynomial
    if (!(iss >> termsInPolynomial2)) {
        cout << "Error: Invalid input for terms in second polynomial." << endl;
        return false;
    }

    cout << "\n" << termsInPolynomial2 << " terms in polynomial2" << endl;

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
    cout << "Parsed polynomial 2: " << polynomial2String << "\n" << endl;

    //initializing polynomial2 with the parsed string
    delete polynomial2;
    polynomial2 = new Polynomial(polynomial2String);

    return true;
}



/****************************************************************************
 *                                                                          *
 *                          class Polynomial Methods                        *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                  Polynomial Overloaded Addition Operator                 *
 ****************************************************************************/

Polynomial& Polynomial::operator+(const Polynomial& other) 
{
    //declaring pointers
    Node* current1 = head;
    Node* current2 = other.head;
    Node* prev = nullptr;

    //traversing both polynomials, stopping when either one ends
    while (current1 != nullptr && current2 != nullptr)
    {   
        //moving to the next term in current1 has a higher exponent
        if (current1->exponent > current2->exponent)
        {
            prev = current1;
            current1 = current1->next;
        }
        //creating a new node for current 2 if current2 has a higher exponent
        else if (current1->exponent < current2->exponent)
        {
            Node* newNode = new Node(current2->coefficient, current2->exponent);
            if (prev != nullptr)
            {
                //linking to previous node if there is one
                prev->next = newNode;
            }
            else 
            {
                //case where there is no prev
                head = newNode;
            }
            //linking nodes and moving on
            newNode->next = current1;
            prev = newNode;
            current2 = current2->next;
        }
        else 
        {
            //adding coefficients if exponents are equal
            current1->coefficient = current1->coefficient + current2->coefficient;
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
                delete current1; //freeing memory
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
                //updating previous and moving on if coefficient is not 0
                prev = current1;
                current1 = current1->next;
            }
            current2 = current2->next;
        }
    }

    //adding remaining current2 terms to the result
    while (current2 != nullptr) 
    {
        Node* newNode = new Node(current2->coefficient, current2->exponent);
        if (prev != nullptr) 
        {
            prev->next = newNode; //linking to previous
        } 
        else 
        {
            head = newNode; //setting to head if there is no previous
        }

        //updating previous to new node and moving on
        prev = newNode;
        current2 = current2->next;
    }

    //returning modified polynomial!
    return *this;
}



/****************************************************************************
 *                  Polynomial Overloaded Subtraction Operator              *
 ****************************************************************************/

Polynomial& Polynomial::operator-(const Polynomial& other) 
{
    //declaring pointers
    Node* current1 = head;
    Node* current2 = other.head;
    Node* prev = nullptr;

    //traversing both polynomials, stopping when either one ends
    while (current1 != nullptr && current2 != nullptr)
    {   
        //moving to the next term in current1 has a higher exponent
        if (current1->exponent > current2->exponent)
        {
            prev = current1;
            current1 = current1->next;
        }
        //creating a new node for current 2 if current2 has a higher exponent
        else if (current1->exponent < current2->exponent)
        {
            //negating coefficient for subtraction!
            Node* newNode = new Node(-current2->coefficient, current2->exponent);
            if (prev != nullptr)
            {
                //linking to previous node if there is one
                prev->next = newNode;
            }
            else 
            {
                //case where there is no prev
                head = newNode;
            }
            //linking nodes and moving on
            newNode->next = current1;
            prev = newNode;
            current2 = current2->next;
        }
        else 
        {
            //subtracting coefficients if exponents are equal
            current1->coefficient = current1->coefficient - current2->coefficient;
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
                delete current1; //freeing memory
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
                //updating previous and moving on if coefficient is not 0
                prev = current1;
                current1 = current1->next;
            }
            current2 = current2->next;
        }
    }

    //adding remaining current2 terms to the result
    while (current2 != nullptr) 
    {
        Node* newNode = new Node(-current2->coefficient, current2->exponent);
        if (prev != nullptr) 
        {
            prev->next = newNode; //linking to previous
        } 
        else 
        {
            head = newNode; //setting to head if there is no previous
        }

        //updating previous to new node and moving on
        prev = newNode;
        current2 = current2->next;
    }

    //returning modified polynomial!
    return *this;
}



/****************************************************************************
 *               Polynomial Overloaded Multiplication Operator              *
 ****************************************************************************/

Polynomial& Polynomial::operator*(const Polynomial& other) 
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

    //calling cleanup to organize and combine terms
    cleanup();

    return *this; //original has been modified!
}



/****************************************************************************
 *                 Polynomial Overloaded Assignment Operator                *
 ****************************************************************************/

Polynomial& Polynomial::operator=(const Polynomial& other)
{
    //checking for self-assignment
    if (this != &other) {
        clear();  //cleaning up existing list
        Node* temp = other.head; //temporary pointer

        //iterating through nodes of other
        while (temp != nullptr) { 
            //inserting and moving on!
            insert(temp->coefficient, temp->exponent);
            temp = temp->next;
        }
    }

    //returning current object
    return *this;
}



/****************************************************************************
 *                          Polynomial Print Function                       *
 ****************************************************************************/

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



/****************************************************************************
 *                       Polynomial Evaluate Function                       *
 ****************************************************************************/

int Polynomial::evaluate(int x) const 
{
    //checking if the list is empty
    if (head == nullptr)
    {
        return 0; 
    }

    //finding the highest exponent in the polynomial
    int highestDegreeExp = 0;
    Node* current = head;
    while (current != nullptr)
    {
        if (current->exponent > highestDegreeExp)
        {
            highestDegreeExp = current->exponent;
        }
        current = current->next;
    }

    //creating an array to store coefficients and initializing to 0 (allowing for placeholder 0s)
    std::vector<int> coefficients(highestDegreeExp + 1, 0);

    //filling the coefficients array with polynomial terms
    //rationale: placeholder 0s for missing terms allows for horner's method to function as intended
    current = head;
    while (current != nullptr)
    {
        if (current->exponent <= highestDegreeExp) 
        {
            coefficients[current->exponent] = current->coefficient;
        }
        current = current->next;
    }

    //evaluating the polynomial using the coefficients array
    int evaluatedPoly = 0;
    int currentPowerOfX = 1;  

    //iterating through array
    for (int i = 0; i <= highestDegreeExp; i++)
    {
        evaluatedPoly += coefficients[i] * currentPowerOfX; //updating final answer
        currentPowerOfX *= x;  //updating x^i for the next term
    }

    return evaluatedPoly;
}



/****************************************************************************
 *                       Polynomial Exponentiate Function                   *
 ****************************************************************************/

Polynomial* Polynomial::exponentiate(int n)  
{
    if (n < 0)
    {
        cout << "Error, exponent must be non-negative!" << endl;
        return this;
    }

    //returning 1
    if (n == 0)
    {
        *this = Polynomial("1 1 0");
        return this;
    }    

    Polynomial polynomial(*this);
    Polynomial result("1 1 0");

    //binary exponentiation! 
    if (n % 2 == 1) //if n is odd
    {
        Polynomial y = polynomial;
        y.exponentiate((n - 1)/2); //polynomial^((n-1)/2)
        result = y; 
        result = result * y; //setting result to y * y
        result.cleanup();
        result = result * polynomial; //setting result to y * y * base because n is an odd number
        result.cleanup();
    }
    else //if n is even
    {
        Polynomial y = polynomial;
        y.exponentiate(n/2);
        result = y;
        result = result * y; //setting result to y * y
        result.cleanup();
    }
    
    *this = result;
    cleanup();
    return this;
}



/****************************************************************************
 *              Polynomial Overloaded Modulus Assignment Operator           *
 ****************************************************************************/

Polynomial Polynomial::operator%=(const Polynomial& other)
{
    //checking if the divisor is in the valid format (not empty and leading coefficient of 1)
    if (other.head == nullptr || other.head->coefficient != 1)
    {
        cout << "The leading coefficient of the divisor polynomial must be 1." << endl;
        return *this;
    }

    //creating a copy of current polynomial for remainder
    Polynomial remainder(*this);

    //creating a copy of current polynomial for later use (setting *this back to original poly)
    Polynomial original(*this);
    
    //polynomial long division!!
    while (remainder.head != nullptr && (remainder.head->exponent >= other.head->exponent))
    {
        //finding exponent difference to know what to multiply by during long division
        int expDiff = remainder.head->exponent - other.head->exponent;
        int coeff = remainder.head->coefficient;

        //polynomial for storing divisor's multiple
        Polynomial multiple;
        
        //polynomial for traversing the divisor
        Node* otherNode = other.head; 

        //building multiple based on current coefficient and the exponent difference
        while (otherNode != nullptr)
        {
            //calling insert and multiplying coefficients + adding exponents
            multiple.insert(coeff * otherNode->coefficient, expDiff + otherNode->exponent);
            otherNode = otherNode->next;
        }

        //subtracting multiple from remainder
        remainder = (remainder - multiple);
    }

    //moving remainder polynomial
    Polynomial returnPoly = std::move(remainder); //using move to avoid copying

    //restoring original polynomia;
    *this = original;

    //returning remainder result!!!
    return returnPoly;
}