#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <utility>
#include <iostream>
#include <sstream>
#include <cmath>
#include <math.h>

using namespace std;


/****************************************************************************
 *                                                                          *
 *                       class Node declaration                             *
 *                                                                          *
 ****************************************************************************/

class Node {
public:
    int coefficient;
    int exponent;
    Node* next;

    //constructor
    Node(int coeff, int exp) : coefficient(coeff), exponent(exp), next(nullptr) {}
};



/****************************************************************************
 *                                                                          *
 *                       class Polynomial declaration                       *
 *                                                                          *
 ****************************************************************************/

class Polynomial {
private:
    Node* head;
    Node* tail;

    void clear(); //function to delete all nodes
    void insert(int coefficient, int exponent); //insertion function
    void cleanup(); //cleanup function to combine like terms and eliminate 0 coefficient terms

    //helper function to read polynomials when there are two inputted (used in ADD, SUB, MULT, MOD)
    friend bool readPolynomials(const std::string& input, Polynomial*& polynomial1, Polynomial*& polynomial2);


public:
    //constructors
    Polynomial() : head(nullptr) {}; //default constructor (for zero polynomial)
    Polynomial(const std::string& input); //parametrized constructor
    Polynomial(const Polynomial& other); //copy constructor

    //destructor
    ~Polynomial(); //destructor

    //overloaded operators
    Polynomial& operator+(const Polynomial& other); //overloaded addition operator
    Polynomial& operator-(const Polynomial& other); //overloaded subtraction operator
    Polynomial& operator*(const Polynomial& other); //overloaded multiplication operator
    Polynomial operator%=(const Polynomial& other); //overloaded modulus operator
    Polynomial& operator=(const Polynomial& other); //overloaded assignment operator

    //methods
    void print() const; //print polynomials function
    int evaluate(int x) const; //polynomial evaluation function
    Polynomial* exponentiate(int n); //polynomial exponentiation function
    
    //helper function to call clear in main
    void reset() {
        clear();
    }
};

#endif