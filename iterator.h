#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <stack>

template <typename T> 
class Iterator {
    private:
        stack <Node<T>*> mstack;
        stack <Node<T>*> pstack;
        Node<T> *current;
        bool pass;

    public:
        Iterator() : current{nullptr}, pass{false} {}

        Iterator(Node<T> *node) : current{node}, pass{false} {
            mstack.push(nullptr);
        }

        Iterator<T>& operator=(const Iterator<T> &other) {      
            this->current = other.current;
            return *this;
        }

        bool operator!=(Iterator<T> other) {
            return this->current != other.current;
        }

        Iterator<T>& operator++() {
            if (pass) current = current->right;
            while (current) {
                mstack.push(current);
                current = current->left;
            }
            current = mstack.top();
            pstack.push(current);
            mstack.pop();
            pass = true;
            return *this;
        }

        Iterator<T>& operator--() {
            pstack.pop();
            current = pstack.top();
            return *this;
        }

        T operator*() {
            if(this->current)
                return this->current->data;
            throw out_of_range("Empty Tree");
        }
};

#endif
