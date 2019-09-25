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
            if (!root) return false;
            Node<T> *temp = root;
            while (temp) {
                if (data <= temp->data) {
                    if (temp->data == data) 
                        return true;
                    else
                        temp = temp->left;
                } else {
                    temp = temp->right;
                }
            } return false;
        } 

        void insert(T data) {
            Node<T> *insert = new Node<T>(data);
            this->nodes++;
            if (!root) {
                root = insert;
                return;
            }
            Node<T> *temp = root;
            while (temp) {
                if (data <= temp->data) {
                    if (temp->left) temp = temp->left;
                    else {
                        temp->left = insert;
                        return;
                    }
                } else {
                    if (temp->right) temp = temp->right;
                    else {
                        temp->right = insert;
                        return;
                    }
                }
            }
        }

        bool remove(T data) {
            if (nodes > 0) {
                Node<T> **pointer = &root;
                while (*pointer) {
                    if (data <= (*pointer)->data) {
                        if ((*pointer)->data == data) {
                            if (!((*pointer)->left))
                                deNode(pointer);
                            else
                                swapyDel(pointer);
                            return true;
                        } else
                            pointer = &(*pointer)->left;
                    } else 
                        pointer = &(*pointer)->right;
                }
            } return false;
        }

        size_t size() {
            return this->nodes;
        }

        size_t height() {
            return Height(root);
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

        Iterator<T> begin() {
            Iterator<T> it(root);
            return ++it;
        }

        Iterator<T> end() {
            Iterator<T> it;
            return it;
        }

        ~BSTree() {
            if (root) destroy(root);
        }

    private:
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
                    if (!(*pointer)->left)
                        deNode(pointer);
                    else 
                        deNode(pointer, false);
                    return;
                } else 
                    pointer = &(*pointer)->right;
            }
        }

        int Height(Node<T>* nodo) {
            if (!nodo) return 0;
            int left = Height(nodo->left);
            int right = Height(nodo->right);
            if (left > right) return left + 1;
            return right + 1;
        }

        void printOrder (Node<T>* nodo, int order) {
            if (order == 0) {
                cout << nodo->data << " ";
                if (nodo->left) printOrder(nodo->left, 0);
                if (nodo->right) printOrder(nodo->right, 0);
            } if (order == 1) {
                if (nodo->left) printOrder(nodo->left, 1);
                cout << nodo->data << " ";
                if (nodo->right) printOrder(nodo->right, 1);
            } if (order == 2) {
                if (nodo->left) printOrder(nodo->left, 2);
                if (nodo->right) printOrder(nodo->right, 2);
                cout << nodo->data << " ";
            }
        }

        void destroy (Node<T>* nodo) {
            if (nodo->left) destroy(nodo->left);
            if (nodo->right) destroy(nodo->right);
            delete nodo;
        }
};

#endif
