#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include "iterator.h"

template <typename T> 
class BSTree {
    Node<T> *root;
    int nodes;

    public:
        BSTree() : root{nullptr}, nodes{0} {};

        bool find(T data) { 
            if (nodes > 0) {
                Node<T> *temp = root;
                while (temp) {
                    if (data <= temp->data) {
                        if (temp->data == data) 
                            return true;
                        else
                            temp = temp->left;
                    } else {
                        if (temp->data == data) 
                            return true;
                        else
                            temp = temp->right;
                    }
                }
            } return false;
        } 

        void insert(T data) {
            Node<T> *insert = new Node<T>(data);
            if (!root) {
                root = insert;
                return;
            } else {
                Node<T> *temp = root;
                while (temp) {
                    if (data <= temp->data) {
                        if (temp->left) temp = temp->left;
                        else {
                            temp->left = insert;
                            break;
                        }
                    } else {
                        if (temp->right) temp = temp->right;
                        else {
                            temp->right = insert;
                            break;
                        }
                    }
                }
            } this->nodes++;
        }

        bool remove(T data) {
            if (nodes > 0) {
                Node<T> **pointer = &root;
                while (*pointer) {
                    if (data <= (*pointer)->data) {
                        if (findToDel(pointer, data)) 
                            return true;
                        else
                            pointer = &(*pointer)->left;
                    } else {
                        if (findToDel(pointer, data)) 
                            return true;
                        else 
                            pointer = &(*pointer)->right;   
                    }
                }
            } return false;
        }

        bool findToDel (Node<T>** pointer, T data) {
            if ((*pointer)->data == data) {
                if (!((*pointer)->left)) {
                    deNode(pointer);
                    return true;
                } else {
                    swapyDel(pointer);
                    return true;
                }
            } return false;
        }

        void deNode (Node<T>** pointer, bool right = true) {
            Node<T> *temp = *pointer;
            if (right) *pointer = temp->right;
            else *pointer = temp->left;
            delete temp;
            this->nodes--;
        }

        void swapyDel (Node<T>** pointer) {
            Node<T> *temp = *pointer;
            pointer = &(*pointer)->left;
            while (*pointer) {
                if (!(*pointer)->right) {
                    temp->data = (*pointer)->data;
                    if (!(*pointer)->left) {
                        deNode(pointer);
                        return;
                    } else {
                        deNode(pointer, false);
                        return;
                    }
                } else {
                    pointer = &(*pointer)->right;
                }
            }
        }

        size_t size() {
            return this->nodes;
        }

        size_t height() {
            // TODO
        }

        void traversePreOrder() {
            printOrder (root,0);
        }

        void traverseInOrder() {
            printOrder (root,1);
        }

        void traversePostOrder() {
            printOrder (root,2);
        }

        void printOrder (Node<T>* nodo, int order) {
            if (order == 0) {
                cout << nodo->data << " ";
                if (nodo->left) printOrder(nodo->left, 0);
                if (nodo->right) printOrder(nodo->right, 0);
            }
            if (order == 1) {
                if (nodo->left) printOrder(nodo->left, 1);
                cout << nodo->data << " ";
                if (nodo->right) printOrder(nodo->right, 1);
            }
            if (order == 2) {
                if (nodo->left) printOrder(nodo->left, 2);
                if (nodo->right) printOrder(nodo->right, 2);
                cout << nodo->data << " ";
            }
        }

        Iterator<T> begin() {
            // TODO
        }

        Iterator<T> end() { 
            // TODO
        }

        void destroy (Node<T>* nodo) {
            if (nodo->left) destroy(nodo->left);
            if (nodo->right) destroy(nodo->right);
            delete nodo;
        }

        ~BSTree() {
            if (root) destroy(root);
        }
};

#endif
