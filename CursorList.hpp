 // Creator: Jeremi Toroj
// Date: 2.01.2024

#ifndef ZESTAW4_CURSORLIST_HPP
#define ZESTAW4_CURSORLIST_HPP

#include <stdexcept>
#include <iostream>

// #########################################-Declaration-#############################################################

template <class T>
class CursorList
{
private:
    struct Node
    {
        T x;
        T y;
        int next;
    };

    Node *data;
    int head;  // first element
    int tail;  // last element
    int spare; // first free cell
    int current_size;
    int capacity;

    void erase(int i);

    template <class U>
    void insert(int i, U &&x);

public:
    explicit CursorList(int cap = 100);

    template <class U>
    void push_front(U &&x, U &&y);

    template <class U>
    void push_back(U &&x, U &&y);

    void pop_front();
    void pop_back();

    int size();
    bool empty();
    void clear();

    int find(const T &x, const T &y);

    int remove(const T &x, const T &y);

    int allocate();
    void deallocate(int i);

    void printList();

    ~CursorList();
};

// #########################################-Definision-#############################################################

template <class T>
CursorList<T>::CursorList(int cap) : data(new Node[cap]), head(-1), tail(-1), spare(0), current_size(0), capacity(cap)
{
    int i = 0;
    while (i < capacity)
    {
        data[i].next = i + 1;
        ++i;
    }

    // creating two lists: spare and data
    data[capacity - 1].next = -1;
}

template <class T>
template <class U>
void CursorList<T>::push_front(U &&x, U &&y)
{
    insert(head, std::forward<U>(x, y));
}

template <class T>
void CursorList<T>::pop_front()
{
    erase(head);
}

template <class T>
template <class U>
void CursorList<T>::push_back(U &&x, U &&y)
{
    insert(spare, std::forward<U>(x, y));
}

template <class T>
void CursorList<T>::pop_back()
{
    erase(tail);
}

template <class T>
int CursorList<T>::size()
{
    return current_size;
}

template <class T>
bool CursorList<T>::empty()
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
}

template <class T>
int CursorList<T>::find(const T &x, const T &y)
{
    int idx = head;
    int count = 0;

    while (count < size())
    {
        if (data[idx].x == x && data[idx].y == y)
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
        element = data[head].data;
        deallocate(i);
        return;
    }

    if (i == head)
    {
        element = data[head].data;
        head = data[head].next;
        deallocate(i);
        return;
    }

    if (i == tail)
    {
        element = data[tail].data;

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

    throw std::runtime_error("Something went wrong.");
}

template <class T>
template <class U>
void CursorList<T>::insert(int i, U &&x)
{
    if (size() == capacity)
    {
        throw std::out_of_range("Overflow - list is full.");
    }

    ++current_size;

    if (size() == 1)
    {
        int newIdx = allocate();
        data[newIdx].data = std::forward<U>(x);
        head = tail = newIdx;
        data[tail].next = -1;

        return;
    }
    else if (i == head)
    {
        int newIdx = allocate();
        data[newIdx].data = std::forward<U>(x);
        data[newIdx].next = head;
        head = newIdx;

        return;
    }
    else if (i == spare)
    {
        int newIdx = allocate();
        data[newIdx].data = std::forward<U>(x);
        data[tail].next = newIdx;
        tail = newIdx;
        data[tail].next = -1;

        return;
    }
}

template <class T>
int CursorList<T>::remove(const T &x, const T &y)
{
    for (int idx = 0; idx < size(); ++idx)
    {
        if (data[idx].x == x && data[idx].y == y)
        {
            erase(idx);
            return 0;
        }
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
}

template <class T>
CursorList<T>::~CursorList()
{
    delete[] data;
}

#endif // ZESTAW4_CURSORLIST_HPP