#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"
#include <vector>
#include <stdexcept>
#include <algorithm>

template <typename T>
class LinkedList
{
public:
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    LinkedList(const LinkedList &other)
    {
        head = nullptr;
        tail = nullptr;
        length = 0;
        Node<T> *current = other.head;
        while (current != nullptr)
        {
            append(current->value);
            current = current->next;
        }
    }

    LinkedList(LinkedList &&other) noexcept
        : head(other.head), tail(other.tail), length(other.length)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.length = 0;
    }

    LinkedList &operator=(LinkedList &&other) noexcept
    {
        if (this != &other)
        {
            Node<T> *current = head;
            while (current != nullptr)
            {
                Node<T> *next = current->next;
                delete current;
                current = next;
            }
            head = other.head;
            tail = other.tail;
            length = other.length;
            other.head = nullptr;
            other.tail = nullptr;
            other.length = 0;
        }
        return *this;
    }
    LinkedList &operator=(const LinkedList &other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        Node<T> *current = head;
        Node<T> *next = nullptr;
        while (current != nullptr)
        {
            next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        length = 0;
        current = other.head;
        while (current != nullptr)
        {
            append(current->value);
            current = current->next;
        }
        return *this;
    }

    bool operator==(const LinkedList &other)
    {
        if (length != other.length)
        {
            return false;
        }
        Node<T> *current = head;
        Node<T> *otherCurrent = other.head;
        while (current != nullptr)
        {
            if (current->value != otherCurrent->value)
            {
                return false;
            }
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
        return true;
    }

    ~LinkedList()
    {
        Node<T> *current = head;
        Node<T> *next = nullptr;
        while (current != nullptr)
        {
            next = current->next;
            delete current;
            current = next;
        }
    }

    void append(T value)
    {
        Node<T> *newNode = new Node<T>(value);
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        length++;
    }

    void prepend(T value)
    {
        Node<T> *newNode = new Node<T>(value);
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        length++;
    }

    int getLength() const
    {
        return length;
    }

    static LinkedList<T> fromVector(std::vector<T> vec)
    {
        LinkedList<T> list;
        for (T value : vec)
        {
            list.append(value);
        }
        return list;
    }

    T operator[](int index)
    {
        if (index < 0 || index >= length)
        {
            // Redundant; this is already checked in the test
            throw std::out_of_range("Index out of range");
        }
        Node<T> *current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->value;
    }

    void reverse()
    {
        Node<T> *current = head;
        while (current != nullptr)
        {
            std::swap(current->next, current->prev);
            current = current->prev;
        }
        std::swap(head, tail);
    }

    void removePosition(int position)
    {
        if (position < 0 || position >= length)
        {
            throw std::out_of_range("Index out of range");
        }
        Node<T> *current = head;
        for (int i = 0; i < position; i++)
        {
            current = current->next;
        }
        if (current->prev != nullptr)
        {
            current->prev->next = current->next;
        }
        if (current->next != nullptr)
        {
            current->next->prev = current->prev;
        }
        if (position == 0)
        {
            head = current->next;
        }
        if (position == length - 1)
        {
            tail = current->prev;
        }
        delete current;
        length--;
    }

    void removeValue(T value)
    {
        Node<T> *current = head;
        while (current != nullptr)
        {
            if (current->value == value)
            {
                if (current->prev != nullptr)
                {
                    current->prev->next = current->next;
                }
                if (current->next != nullptr)
                {
                    current->next->prev = current->prev;
                }
                if (current == head)
                {
                    head = current->next;
                }
                if (current == tail)
                {
                    tail = current->prev;
                }
                Node<T> *temp = current;
                current = current->next;
                delete temp;
                length--;
            }
            else
            {
                current = current->next;
            }
        }
    }

    // #ifdef TESTING
    // For testing purposes, to get TDD off the ground
    Node<T> *testGetHead()
    {
        return head;
    }
    Node<T> *testGetTail()
    {
        return tail;
    }
    // #endif // TESTING
private:
    Node<T> *head;
    Node<T> *tail;
    int length;
};

#endif // LINKED_LIST_H
