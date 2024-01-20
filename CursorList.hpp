#ifndef ZESTAW4_CURSORLIST_HPP
#define ZESTAW4_CURSORLIST_HPP

#include <stdexcept>
#include <iostream>

template <class T>
class CursorList
{
private:
    using Pair = std::pair<T, T>;

    struct Node
    {
        Pair coordinates;
        int next;
    };

    Node *data;
    int head;
    int tail;
    int spare;
    int current_size;
    int capacity;

    void erase(int i);

    void insert(int i, const Pair &coordinates);

public:
    explicit CursorList(int cap = 100);

    void push_front(const Pair &coordinates);
    void push_back(const Pair &coordinates);

    void pop_front();
    void pop_back();

    int size() const;
    bool empty() const;
    void clear();

    int getHead() const { return head; }
    Pair getData(int i) const { return data[i].coordinates; }
    int getNext(int i) const { return data[i].next; }

    int find(const Pair &coordinates);

    int remove(const Pair &coordinates);

    int allocate();
    void deallocate(int i);

    void printList();

    ~CursorList();
};

template <class T>
CursorList<T>::CursorList(int cap) : data(new Node[cap]), head(-1), tail(-1), spare(0), current_size(0), capacity(cap)
{
    int i = 0;
    while (i < capacity)
    {
        data[i].next = i + 1;
        ++i;
    }

    data[capacity - 1].next = -1;
}

template <class T>
void CursorList<T>::push_front(const Pair &coordinates)
{
    insert(head, coordinates);
}

template <class T>
void CursorList<T>::pop_front()
{
    erase(head);
}

template <class T>
void CursorList<T>::push_back(const Pair &coordinates)
{
    insert(spare, coordinates);
}

template <class T>
void CursorList<T>::pop_back()
{
    erase(tail);
}

template <class T>
int CursorList<T>::size() const
{
    return current_size;
}

template <class T>
bool CursorList<T>::empty() const
{
    return current_size == 0;
}

template <class T>
void CursorList<T>::clear()
{
    current_size = 0;
    head = -1;
    tail = -1;
    spare = 0;
    delete[] data;
    data = new Node[capacity];
    int i = 0;
    while (i < capacity)
    {
        data[i].next = i + 1;
        ++i;
    }
}

template <class T>
int CursorList<T>::find(const Pair &coordinates)
{
    int idx = head;
    int count = 0;

    while (count < size())
    {
        if (data[idx].coordinates == coordinates)
        {
            return idx;
        }
        idx = data[idx].next;
        ++count;
    }

    return -1;
}

template <class T>
void CursorList<T>::erase(int i)
{
    if (empty())
    {
        throw std::out_of_range("Underflow - list is empty.");
    }

    --current_size;
    int element;

    if (size() == 0)
    {
        element = i;
        deallocate(i);
        return;
    }

    if (i == head)
    {
        element = i;
        head = data[head].next;
        deallocate(i);
        return;
    }

    if (i == tail)
    {
        element = i;

        int idx = head;
        while (data[idx].next != tail)
        {
            idx = data[idx].next;
        }
        tail = idx;
        data[tail].next = -1;
        deallocate(i);
        return;
    }
}

template <class T>
void CursorList<T>::insert(int i, const Pair &coordinates)
{
    if (size() == capacity)
    {
        throw std::out_of_range("Overflow - list is full.");
    }

    ++current_size;

    if (size() == 1)
    {
        int newIdx = allocate();
        data[newIdx].coordinates = coordinates;
        head = tail = newIdx;
        data[tail].next = -1;

        return;
    }
    else if (i == head)
    {
        int newIdx = allocate();
        data[newIdx].coordinates = coordinates;
        data[newIdx].next = head;
        head = newIdx;

        return;
    }
    else if (i == spare)
    {
        int newIdx = allocate();
        data[newIdx].coordinates = coordinates;
        data[tail].next = newIdx;
        tail = newIdx;
        data[tail].next = -1;

        return;
    }
}

template <class T>
int CursorList<T>::remove(const Pair &coordinates)
{
    int idx = head;
    int count = 0;
    

    int prevIdx = -1;

    while (count < size())
    {
        if (data[idx].coordinates == coordinates)
        {
            if (prevIdx == -1)
            {
                head = data[idx].next;
            }
            else
            {
                data[prevIdx].next = data[idx].next;
            }

            current_size--;
            return idx;
        }

        prevIdx = idx;
        idx = data[idx].next;
        ++count;
    }

    return -1;
}

template <class T>
int CursorList<T>::allocate()
{
    int temp = spare;
    spare = data[spare].next;
    return temp;
}

template <class T>
void CursorList<T>::deallocate(int i)
{
    data[i].next = spare;
    spare = i;
}

template <class T>
void CursorList<T>::printList()
{
    if (empty())
    {
        std::cout << "List is empty." << std::endl;
        return;
    }

    int idx = head;
    while (idx != -1)
    {
        std::cout << "(" << data[idx].coordinates.first << ", " << data[idx].coordinates.second << ") ";
        idx = data[idx].next;
    }
    std::cout << std::endl;
}

template <class T>
CursorList<T>::~CursorList()
{
    delete[] data;
}

#endif // ZESTAW4_CURSORLIST_HPP
