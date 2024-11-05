#pragma once

#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

template <typename T>
struct Stack {

private:

    struct Node {
        T person;
        Node* next;

        Node(T person) : person(person), next(nullptr) {}
    };

    Node* head;

public:

    Stack();
    ~Stack();

    bool is_empty();
    void push(T name);
    void pop();
    T top(); // return head without delete

    void print();
};

template <typename T>
Stack<T>::Stack() : head(nullptr) {}

template <typename T>
Stack<T>::~Stack() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
bool Stack<T>::is_empty() {
    return head == nullptr;
}

template <typename T>
void Stack<T>::push(T name) {
    Node* new_node = new Node(name);
    new_node->next = head;
    head = new_node;
}

template <typename T>
void Stack<T>::pop() {
    if (is_empty()) {
        throw runtime_error("Stack is empty");
    }
    else {
        Node* new_head = head->next;
        delete head;
        head = new_head;
    }
}


template <typename T>
T Stack<T>::top() {
    if (is_empty()) {
        throw runtime_error("Stack is empty");
    }
    return head->person;
}

template <typename T>
void Stack<T>::print() {
    Node* current = head;
    while (current != nullptr) {
        cout << current->person << " ";
        current = current->next;
    }
    cout << "\n";
}

