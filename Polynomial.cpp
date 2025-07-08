#include "Polynomial.h"


/****************************************************************************
 *                                                                          *
 *                 class Polynomial Constructors & Destructor               *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                 Polynomial Parametrized Constructor                      *
 * Rationale: This constructor operates by reading in a polynomial string,  *
 * storing # of terms in a variable, then iterating through the polynomial  *
 * using a for loop to read each term's coefficient and exponent into new   *
 * nodes. This loop is helpful because iterating from i = 0 to the number   *
 * of terms in the polynomial allows for the linked list to be initialized  *
 * to the correct size. Also, since inputs are all in greatest to least     *
 * exponent order, and only combined polynomials are inputted, the list is  *
 * initialized in the correct order!                                        *
 *                                                                          *
 * Runtime Analysis: O(n) because for loops have linear runtime and all     *
 * operations within this for loop have O(1) runtime, so the overall        *
 * runtime will remain O(n).                                                *
 ****************************************************************************/

Polynomial::Polynomial(const std::string& input) : head(nullptr) {
    istringstream iss(input);
    int numberOfTerms;
    iss >> numberOfTerms;

    Node* current = nullptr;

    //iterating through polynomial
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



/****************************************************************************
 *                       Polynomial Copy Constructor                        *
 * Rationale: This constructor operates by creating a new node for the new  *
 * polynomial and traversing through the remaining nodes of the source      *
 * polynomial, creating a new node in the current polynomial each time and  *
 * copying the coefficient and exponent from the corresponding node in the  *
 * source polynomial. Before ending the loop, I move the current and source *
 * pointers to point to the next term so that I can repeat the process      *
 * until the end of the source polynomial to make an accurate copy! This    *
 * constructor is useful because it allows for copying polynomials, and     *
 * therefore saving the original polynomial for restoration at the end of   *
 * a function when necessary.
 *                                                                          *
 * Runtime Analysis: O(n) because while loops have linear runtime and all   *
 * operations within the loop have O(1) runtime. This constructor is never  *
 * called within any loops throughout the rest of my program, so it does    *
 * impact the runtimes of the functions it is called within (the O(n) is    *
 * added and absorbed into runtimes).
 ****************************************************************************/

Polynomial::Polynomial(const Polynomial& other) : head(nullptr), tail(nullptr) {
    if (other.head == nullptr)
    {
        return;
    }

    //creating new node for head of current polynomial
    head = new Node(other.head->coefficient, other.head->exponent);
    Node* currentOther = other.head->next; //pointer for traversing source polynomial
    Node* currentThis = head; //pointer for traversing new polynomial

    //iterating through remaining nodes of source polynomial
    while (currentOther != nullptr)
    {
        //creating a new node in current polynomial, copying coeff and exp from source
        currentThis->next = new Node(currentOther->coefficient, currentOther->exponent);

        currentThis = currentThis->next; 
        currentOther = currentOther->next;
    }
}



/****************************************************************************
 *                         Polynomial Destructor                            *
 * Rationale: Calls clear helper function to delete a polynomial            *
 *                                                                          *
 * Runtime Analysis: clear() has a runtime of O(n) but the destructor is    *
 * never called in any loops within functions, and the O(n) is thus         *
 * absorbed into runtimes.                                                  *
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
 * Rationale: Beginning at head, this function iterates through the linked  *
 * list, setting next to the node after current, deleting current, and then *
 * setting current to next so that the process can repeat itself until      *
 * the end of the linked list. In order to avoid dangling pointers, I set   *
 * head and tail to nullptr at the end of the function.                     *
 *                                                                          *
 * Runtime Analysis: O(n) because while loops have linear runtime and the   *
 * procedures within the loop have O(1) runtime, so the overall function    *
 * runtime is O(n).                                                         *
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

    head = nullptr;  
    tail = nullptr;  
}



/****************************************************************************
 *                        Polynomial Insert Helper Function                 *
 * Rationale: This function creates a new node for the given coefficient    *
 * and exponent, and if the list is empty, sets both the head and tail to   *
 * the new node. If the list is not empty, tail is linked to the new node,  *
 * thus appending the new node to the end of the list. This function is     *
 * useful because it can be called without skewing runtimes!!               *
 *                                                                          *
 * Runtime Analysis: O(1) because no loops are used, so every operation     *
 * within the function will only run one time!                              *
 ****************************************************************************/
void Polynomial::insert(int coefficient, int exponent) 
{
    //creating a new node for the given coeff and exp
    Node* newNode = new Node(coefficient, exponent);
    
    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode; 
        tail = newNode; 
    }
}



/****************************************************************************
 *                       Polynomial Cleanup Helper Function                 *
 * Rationale: This function starts by checking if the list is empty. Then,  *
 * it declares current and prev pointers before declaring a bool to track   *
 * whether the list is sorted. Using a while loop within a do while loop    *
 * I used a bubble sort inspired technique to order the polynomial by       *
 * exponent. The outer loop runs as long as the list is not sorted. Since   *
 * sorted is updated to true before the inner loop, it will remain true if  *
 * the conditions for the inner loop are not met, allowing for the do while *
 * loop to be broken out of once the entire polynomial has been processed.  *
 * The inner loop swaps nodes when the next node has a higher degree        *
 * exponent, and moves on if the current node has the higher degree.        *
 * After sortinng terms according to order, the function has another while  *
 * loop that runs as through the entire list again, this time to combine    *
 * like terms and elimiate any 0 terms. It first combines terms when the    *
 * exponent degrees of current and next are equal. Then, it checks if the   *
 * coefficient is 0 and if it is, deletes the node and relinks the list.    *
 * This process repeats until the entire list has been checked, and our     *
 * reuslt is a fully sorted and combined polynomial. Breaking insert into   *
 * insert and cleanup allows for me to maintain the correct runtimes in my  *
 * operators!                                                               *
 *                                                                          *
 * Runtime Analysis: O(n^2) because of the nested while loops. Everything   *
 * within the innermost while loop is O(1). This gives us O(n^2+n) for the  *
 * nested loops and the non-nested loop, so our final runtime for cleanup   *
 * is O(n^2). I only call this function in operator* and exponentiation,    *
 * which are both supposed to be O(n^2), so the O(n^2) is absorbed into     *
 * their runtimes, as I am careful to not call it within loops!             *
 ****************************************************************************/

void Polynomial::cleanup() {
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
                //no swap is needed because the current node has the higher exponent degree!
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
                current = prev->next;  
            } else {
                current = head;        
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
 * Rationale: This function allows for me to read input strings of 2        *
 * polynomials and store each polynomial in polynomial1 and polynomial2     *
 * before I call my methods to perform operations on the two polynomials in *
 * main. It operates by reading in number of terms in each polynomial and   *
 * then reading through the string to essentially separate the input string *
 * into a polynomial1 string and a polynomial2 string, and then converting  *
 * each string to a new polynomial1 & polynomial2. The logic is the same    *
 * for reading each polynomial in, and this function returns a bool rather  *
 * than an output so that it just allows for polynomial creation to prepare *
 * for function calls in main.                                              *
 *                                                                          *
 * Runtime Analysis: O(n) because for loops have linear runtime and the     *
 * contents of these for loops have O(1) runtime.                           *
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

    //printing first polynomial
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

    //printing second polynomial
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
 * Rationale: This operator works by traversing both polynomials and        *
 * stopping when one of them ends. The first loop moves onto the next node  *
 * if the current1 polynomial has the higher exponent, and if not, a new    *
 * node for current2 is created. As nodes are added in, they are linked to  *
 * the rest of the list. If the coefficient of a node in current1 is equal  *
 * to the coefficient of the corresponding node in current2, the            *
 * coefficients are added. If the new coefficient is 0, the node is skipped.*
 * If not, prev is updated and we move onto the rest of the list.           *
 * Finally, I have another while loop to iterate through the remaining      *
 * nodes in larger polynomial, which adds the nodes to the end of the       *
 * result polynomial.                                                       *
 *                                                                          *
 * Runtime Analysis: O(n+m) where n and m are the highest powers of the two *
 * polynomials because the first loop has runtime O(n) from iterating       *
 * through both polynomials until the shorter polynomial ends, and the      *
 * second loop runs through the remaining nodes in the longer polynomial,   *
 * which will be O(m).                                                      *
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
        //moving to the next term if current1 has a higher exponent
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
            prev->next = newNode; 
        } 
        else 
        {
            head = newNode; 
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
 * Rationale: This operator works by traversing both polynomials and        *
 * stopping when one of them ends. The first loop moves onto the next node  *
 * if the current1 polynomial has the higher exponent, and if not, a new    *
 * node for current2 is created, which negates the coefficient to account   *
 * for subtraction. As nodes are added in, they are linked to               *
 * the rest of the list. If the coefficient of a node in current1 is equal  *
 * to the coefficient of the corresponding node in current2, the            *
 * coefficients are subtracted. If the new coefficient is 0, the node is    *
 * skipped. If not, prev is updated and we move onto the rest of the list.  *
 * Finally, I have another while loop to iterate through the remaining      *
 * nodes in larger polynomial, which adds the nodes to the end of the       *
 * result polynomial, negating the coefficients to account for subtraction. *
 *                                                                          *
 * Runtime Analysis: O(n+m) where n and m are the highest powers of the two *
 * polynomials because the first loop has runtime O(n) from iterating       *
 * through both polynomials until the shorter polynomial ends, and the      *
 * second loop runs through the remaining nodes in the longer polynomial,   *
 * which will be O(m).                                                      *
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
            prev->next = newNode; 
        } 
        else 
        {
            head = newNode;
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
 * Rationale: This function copies the original polynomial into             *
 * polynomial1 before clearing the original polynomial. I declare a pointer *
 * to the original polynomial and then use nested while loops to iterate    *
 * through both linked lists. In the innermost while loop that iterates     *
 * through the second polynomial, I multiply coefficients and add exponents *
 * before adding these new coefficient and exponent values to the list with *
 * my insert function. Outside of the loops, I call cleanup to sort the     *
 * list, combine like terms, and eliminate 0s before returning.             *
 *                                                                          *
 * Runtime Analysis: O(n^2) because while loops have linear runtime and     *
 * nesting them gives me O(n^2). All operations within innermost while loop *
 * have O(1) runtime. Outside of the loops, I call cleanup() which has      *
 * O(n^2) runtime, but the runtimes would be added O(n^2+n^2) = O(2n^2)     *
 * and simplified back to O(n^2) so this function runs in the proper time!  *
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
 * Rationale: This operator operates by looping through the nodes of the    *
 * other polynomial after checking for self assignment, and calling insert  *
 * to insert the other polynomial's coefficients and exponents after        *
 * clearing the existing list. This operator is useful because it allows me *
 * to set one polynomial equal to another.                                  *
 * 
 * Runtime Analysis: O(n) because of while loop with O(1) contents as while *
 * loops have linear runtime. This operator is only called in instances     *
 * where the O(n) runtime will be dominated by or absorbed into the runtime *
 * of the function it is called in!                                         *
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
 * Rationale: This function prints 0 for polynomials initialized to zero.   *
 * If the list is not empty, it loops through the list with a while loop to *
 * ensure that all positive terms after the first term are preceded by a    *
 * plus sign, and all negative terms are preceded by a negative sign.       *
 * Since signs have been taken care of, I then print the abs value of       *
 * non-zero coefficients before printing x to the degree of the             *
 * corresponding coeffiicent if the exponent degree is greater than 0.      *
 *                                                                          *
 * Runtime Analysis: O(n) because while loops have linear runtime and all   *
 * procedures inside of the while loop have O(1) runtime.                   *
 ****************************************************************************/

void Polynomial::print() const 
{
    if (!head) {
        cout << "0" << endl; //printing "1 0 0" for polynomials initialized to zero
        return;
    }

    Node* current = head;
    while (current) //while current is not nullptr
    {
        //making sure all positive terms besides the first one are preceded by a plus sign
        if (current != head && current->coefficient > 0)
        {
            cout << " + ";
        }
        else if (current->coefficient < 0) //making sure all negative terms are preceded by a negative sign
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
 * Rationale: After checking if the list is empty, this function uses a     *
 * while loop to loop through the inputted polynomial list and find the     *
 * highest degree exponent in the list. Then, I initialize a vector to      *
 * store coefficients that is one larger than the size of the highest deg   *
 * exponent to account for a trailing constant term. The vector is          *
 * initialized to 0 so that there are placeholder 0s for missing terms.     *
 * This allows for my eval method to work as intended. Next, I fill the     *
 * coefficients array with polynomial terms (place in the array corresponds)*
 * with exponent degree, allowing for this loop to correctly match          *
 * coefficients with their correpsonding exponenents. I fill in the array   *
 * for the terms that exist, leaving 0 coefficients for the missing terms.  *
 * Then, I use the "linear" method that begins with the last term and adds  *
 * coefficient[i] * the current x power to the evaluatedPoly variable       *
 * before updating the current x power to the next degree and then moving   *
 * onto the next coefficient. For example, if I know the value of x,        *
 * I calculate x*x=x^2, right before restarting the loop, and repeat this.  *
 *                                                                          *
 * Runtime Analysis: O(n) because this function has three separate loops    *
 * (not nested) and everything within each loop is O(1). For loops and      *
 * while loops have linear runtime.                                         *
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
    vector<int> coefficients(highestDegreeExp + 1, 0);

    //filling the coefficients array with polynomial terms
    //rationale: placeholder 0s for missing terms allows for method to function as intended
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
 * Rationale: I checked to see if exponent is non-negative, then checked    *
 * if the input n is 0 (returned 1 in this case). After these checks, I     *
 * copied my original polynomial into polynomial and intialized a result to *
 * "1 1 0". My approach to exponentiation implements recursion. I declare a *
 * polynomial y that is equal to the original polynomial and then check if  *
 * the inputted n value is odd or even. If it is odd, I call                *
 * exponentiate, feeding in ((n-1)/2) before setting result to y*y,         *
 * cleaning up, and then multiplying result by polyomial and cleaning up.   *
 * If it is even, I call exponentiate with n/2 and then set result to y*y   *
 * before cleaning up. This rationale is rooted in the idea that when a     *
 * term is odd, it needs an extra multiplication by the base (remainder of  * 
 * dividing n by 2, which we are doing to make expontiation efficient).     *    
 *                                                                          *
 * Runtime Analysis: O(n^2log(m)) where n is the highest power of the       *
 * polynomial and m is the exponent. My overloaded multiplication           *
 * operator, which I call in this function, has a runtime of O(n^2), and    *
 * there are log(m) recursive calls. I call cleanup() in this function,     * 
 * but cleanup()'s O(n^2) runtime is absorbed into the runtime because      *
 * O(n^2+n^2)=O(2n^2) which simplifies to O(n^2) for runtime purposes. The  *
 * O(n) copy constructor runtime is dominated by the O(n^2) overall runtime!*                                                   
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
        y.exponentiate(n/2); //polynomial^(n/2)
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
 * Rationale: First, I checked to make sure that the leading coefficient    *
 * is not empty and has a leading coefficient of 1. I then called my copy   *
 * constructor to make a copy of the current polynomial called remainder,   *
 * and also made a copy of the current polynomial called original (for      *
 * later restoration). Then, I use nested while loops to reverse through    *
 * the polynomials. The outer loop continues as long as remainder head is   *
 * not nullptr and the head exponent is greater than that of the divisor.   *
 * In the loop, I find exponent difference and coefficient of remainder     *
 * before declaring a multiple polynomial and traversing the divisor.       *
 * My strategy is inserting the multiplied terms into the multiple poly,    *
 * and subtracting that multiple from remainder outside the inner loop, to  *
 * mock the structure of polynomial long division. I then store the         *
 * remainder in a return polynomial and then restore *this to the original. *
 * The result is the remainder of polynomial division!!                     *
 *                                                                          *
 * Runtime Analysis: O(n^2) because while loops have linear runtime and     *
 * nesting them results in O(n^2) runtime. Everything in the innermost loop *
 * has a runtime of O(1). I call the copy constructor, which has O(n)       *
 * runtime, but this call is outside of the loops so this O(n) runtime is   *
 * dominated by the O(n^2) of the overall function!                         *
 ****************************************************************************/

Polynomial Polynomial::operator%=(const Polynomial& other)
{
    //checking if the divisor is in the valid format (not empty and leading coefficient of 1)
    if (other.head == nullptr || other.head->coefficient != 1)
    {   
        
        cout << "The leading coefficient of the divisor polynomial must be 1 and the divisor polynomial must not be empty." << endl;
        return *this;
    }

    //creating a copy of current polynomial for remainder
    Polynomial remainder(*this);

    //creating a copy of current polynomial for later use (setting *this back to original poly)
    Polynomial original(*this);
    
    //polynomial long division!!
    while (remainder.head != nullptr && (remainder.head->exponent >= other.head->exponent))
    {
        //finding exponent difference and coefficient to know what to multiply by during long division
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
    Polynomial returnPoly = remainder; //using move to avoid copying

    //restoring original polynomia;
    *this = original;

    //returning remainder result!!!
    return returnPoly;
}





