#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <utility>
#include <iostream>
#include <sstream>

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

    // Node(int coeff, int exp); //constructor
    //NOTE: Not sure if it is the line above or this...
    Node(int coeff, int exp) : coefficient(coeff), exponent(exp), next(nullptr) {}
    // ~Node(); //destructor
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
    void insert(int coefficient, int exponent);
    void cleanup();
    friend bool readPolynomials(const std::string& input, Polynomial*& polynomial1, Polynomial*& polynomial2);
    //int evaluationCalc(int x) const;
    //probably dont need these
    // Polynomial* addOrSubtract(Polynomial* other, bool addition);
    // Polynomial* multiply(Polynomial* other);

public:
    //constructors
    Polynomial() : head(nullptr) {}; //default constructor (for zero polynomial?)
    Polynomial(const std::string& input); //parametrized constructor
    Polynomial(const Polynomial& other); //copy constructor

    //destructor
    ~Polynomial(); //destructor

    //overloaded operators
    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator-=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);
    Polynomial& operator%=(const Polynomial& other);
    Polynomial& operator=(const Polynomial& other);

    //methods
    void print() const;
    int evaluate(int x) const;
    Polynomial* exponentiate(int n);
    // Polynomial* modulus(Polynomial& other);
    void addNode(int coeff, int exp);
};

#endif