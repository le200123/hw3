#include "Polynomial.h"
#include <cmath> 


Polynomial::Polynomial() {
    head = new Node{0, 0, nullptr};
    head->next = head; 
}


Polynomial::Polynomial(const Polynomial& a) {
    head = new Node{0, 0, nullptr};
    head->next = head; 

    Node* current = a.head->next;
    while (current != a.head) {
        Node* newNode = createNode(current->coef, current->exp);
        newNode->next = head->next;
        head->next = newNode;
        current = current->next;
    }
}


Polynomial::~Polynomial() {
    Node* current = head->next;
    while (current != head) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    delete head;
}


const Polynomial& Polynomial::operator=(const Polynomial& a) {
    if (this != &a) {
        this->~Polynomial(); 
        head = new Node{0, 0, nullptr};
        head->next = head; 

        Node* current = a.head->next;
        while (current != a.head) {
            Node* newNode = createNode(current->coef, current->exp);
            newNode->next = head->next;
            head->next = newNode;
            current = current->next;
        }
    }
    return *this;
}


Polynomial Polynomial::operator+(const Polynomial& b) const {
    Polynomial result;
    Node* p1 = head->next;
    Node* p2 = b.head->next;

    while (p1 != head || p2 != b.head) {
        if (p1 != head && (p2 == b.head || p1->exp > p2->exp)) {
            result.head->next = createNode(p1->coef, p1->exp, result.head->next);
            p1 = p1->next;
        } else if (p2 != b.head && (p1 == head || p1->exp < p2->exp)) {
            result.head->next = createNode(p2->coef, p2->exp, result.head->next);
            p2 = p2->next;
        } else {
            int sumCoef = p1->coef + p2->coef;
            if (sumCoef != 0) {
                result.head->next = createNode(sumCoef, p1->exp, result.head->next);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    return result;
}


Polynomial Polynomial::operator-(const Polynomial& b) const {
    Polynomial result;
    Node* p1 = head->next;
    Node* p2 = b.head->next;

    while (p1 != head || p2 != b.head) {
        if (p1 != head && (p2 == b.head || p1->exp > p2->exp)) {
            result.head->next = createNode(p1->coef, p1->exp, result.head->next);
            p1 = p1->next;
        } else if (p2 != b.head && (p1 == head || p1->exp < p2->exp)) {
            result.head->next = createNode(-p2->coef, p2->exp, result.head->next);
            p2 = p2->next;
        } else {
            int diffCoef = p1->coef - p2->coef;
            if (diffCoef != 0) {
                result.head->next = createNode(diffCoef, p1->exp, result.head->next);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    return result;
}


Polynomial Polynomial::operator*(const Polynomial& b) const {
    Polynomial result;

    for (Node* p1 = head->next; p1 != head; p1 = p1->next) {
        Polynomial temp;
        for (Node* p2 = b.head->next; p2 != b.head; p2 = p2->next) {
            int newCoef = p1->coef * p2->coef;
            int newExp = p1->exp + p2->exp;
            temp.head->next = createNode(newCoef, newExp, temp.head->next);
        }
        result = result + temp;
    }
    return result;
}


float Polynomial::Evaluate(float x) const {
    float result = 0.0;
    for (Node* current = head->next; current != head; current = current->next) {
        result += current->coef * pow(x, current->exp);
    }
    return result;
}


Node* Polynomial::createNode(int coef, int exp, Node* next) {
    Node* newNode = new Node{coef, exp, next};
    return newNode;
}


istream& operator>>(istream& is, Polynomial& x) {
    int n;
    is >> n;
    for (int i = 0; i < n; ++i) {
        int coef, exp;
        is >> coef >> exp;
        x.head->next = x.createNode(coef, exp, x.head->next);
    }
    return is;
}


ostream& operator<<(ostream& os, const Polynomial& x) {
    for (Node* current = x.head->next; current != x.head; current = current->next) {
        os << current->coef << "x^" << current->exp;
        if (current->next != x.head) os << " + ";
    }
    return os;
}
int main() {
    Polynomial p1, p2, p3;
    cout << "?入多?式 p1: ";
    cin >> p1;
    cout << "?入多?式 p2: ";
    cin >> p2;

    p3 = p1 + p2;
    cout << "p1 + p2 = " << p3 << endl;

    p3 = p1 - p2;
    cout << "p1 - p2 = " << p3 << endl;

    p3 = p1 * p2;
    cout << "p1 * p2 = " << p3 << endl;

    float x;
    cout << "?入x的值: ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Evaluate(x) << endl;

    return 0;
}
