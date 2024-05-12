#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public:
    Node(T value) : value(value), next(nullptr), prev(nullptr){};
    ~Node(){};
    T value;
    Node<T> *next;
    Node<T> *prev;
};
#endif // NODE_H
