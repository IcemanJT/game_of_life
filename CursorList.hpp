#ifndef ZESTAW4_CURSORLIST_HPP
#define ZESTAW4_CURSORLIST_HPP

#include <stdexcept>
#include <iostream>

// #########################################-Declaration-#############################################################

template <class T, int N>
class CursorList
{
private:
    struct Node
    {
        T data;
        int next;
    };

    Node *data;
    int head;  // first element
    int tail;  // last element
    int spare; // first free cell
    int current_size;
    int capacity;

    T erase(int i);

    template <class U>
    void insert(int i, U &&x);

public:
    explicit CursorList(int cap = N);

    template <class U>
    void push_front(U &&x);

    template <class U>
    void push_back(U &&x);

    T pop_front();
    T pop_back();

    int size();
    bool empty();
    void clear();
    int find(const T &x);

    int remove(const T &x);

    int allocate();
    void deallocate(int i);

    int prevNode_finder(int i);

    template <class U>
    bool replace(const T &x, U &&y);

    void printList();

    ~CursorList();
};

// #########################################-Definision-#############################################################

template <class T, int N>
CursorList<T, N>::CursorList(int cap) : data(new Node[cap]), head(-1), tail(-1), spare(0), current_size(0), capacity(cap)
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

template <class T, int N>
template <class U>
void CursorList<T, N>::push_front(U &&x)
{
    insert(head, std::forward<U>(x));
}

template <class T, int N>
T CursorList<T, N>::pop_front()
{
    return erase(head);
}

template <class T, int N>
template <class U>
void CursorList<T, N>::push_back(U &&x)
{
    insert(spare, std::forward<U>(x));
}

template <class T, int N>
T CursorList<T, N>::pop_back()
{
    return erase(tail);
}

template <class T, int N>
int CursorList<T, N>::size()
{
    return current_size;
}

template <class T, int N>
bool CursorList<T, N>::empty()
{
    return current_size == 0;
}

template <class T, int N>
void CursorList<T, N>::clear()
{
    current_size = 0;
    head = -1;
    tail = -1;
    spare = 0;
    delete[] data;
    data = new Node[capacity];
}

template <class T, int N>
int CursorList<T, N>::find(const T &x)
{
    int idx = head;
    int count = 0;

    while (count < size())
    {
        if (data[idx].data == x)
        {
            return idx;
        }
        idx = data[idx].next;
        ++count;
    }

    return -1;
}

template <class T, int N>
T CursorList<T, N>::erase(int i)
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
        return element;
    }

    if (i == head)
    {
        element = data[head].data;
        head = data[head].next;
        deallocate(i);
        return element;
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

        return element;
    }

    return -1;
}

template <class T, int N>
template <class U>
void CursorList<T, N>::insert(int i, U &&x)
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
    else
    {
        int newIdx = allocate();
        data[newIdx].data = std::forward<U>(x);
        int prevNode = prevNode_finder(i);
        data[newIdx].next = data[prevNode].next;
        data[prevNode].next = newIdx;

        return;
    }
}

template <class T, int N>
int CursorList<T, N>::remove(const T &x)
{
    int count = 0;

    for (int idx = 0; idx < size(); ++idx)
    {
        if (data[idx] == x)
        {
            erase(idx); // erase moves element data[idx-1] to data[idx]
            --idx;      // decrement so remove won't skip element behind idx
            ++count;
        }
    }

    return count;
}

template <class T, int N>
int CursorList<T, N>::allocate()
{
    int temp = spare;
    spare = data[spare].next;
    return temp;
}

template <class T, int N>
void CursorList<T, N>::deallocate(int i)
{
    data[i].next = spare;
    spare = i;
}

template <class T, int N>
int CursorList<T, N>::prevNode_finder(int i)
{
    if (i == head || i < 0 || i >= capacity)
    {
        return -1;
    }

    int node_before_node_i = head;
    int counter = 0;

    while (counter < i - 1)
    {
        node_before_node_i = data[node_before_node_i].next;
        ++counter;
    }

    return node_before_node_i;
}

template <class T, int N>
template <class U>
bool CursorList<T, N>::replace(const T &x, U &&y)
{
    int idx = find(x);

    if (idx != -1)
    {
        data[idx].data = std::forward<U>(y);
        return true;
    }

    return false;
}

template <class T, int N>
void CursorList<T, N>::printList()
{
    if (empty())
    {
        std::cout << "List is empty." << std::endl;
        return;
    }
}

#endif // ZESTAW4_CURSORLIST_HPP