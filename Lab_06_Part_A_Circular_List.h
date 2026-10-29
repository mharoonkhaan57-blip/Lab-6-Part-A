#ifndef LAB06_PART_A_CIRCULAR_LIST_H
#define LAB06_PART_A_CIRCULAR_LIST_H

/* Name: M.Haroon-Ur-Rasheed Khan | Reg. No: Ai-9 | Subject: DSA | Sec: A */
// Lab 06 Part A: Menu-driven circular linked list

#include <iostream>
#include <string>
#include <utility>

using namespace std;

struct BookNode
{
    int id;
    string title;
    BookNode* next;

    BookNode(int bookID, const string& bookTitle)
        : id(bookID), title(bookTitle), next(nullptr) {}
};

class CircularLinkedList
{
private:
    BookNode* head;       // head points to the last node
    BookNode* current;    // current book on the display
    int count;

    int normalizeIndex(int index) const
    {
        return ((index % count) + count) % count;
    }

    BookNode* getNodeAt(int index) const
    {
        BookNode* node = head->next; // first node
        while (index-- > 0)
            node = node->next;
        return node;
    }

    void clear()
    {
        while (count > 0)
            delete Remove();
    }

    void copyFrom(const CircularLinkedList& other)
    {
        if (other.count == 0)
            return;

        BookNode* node = other.head->next;
        for (int i = 0; i < other.count; i++)
        {
            InsertAt(new BookNode(node->id, node->title), count);
            node = node->next;
        }
    }

public:
    CircularLinkedList() : head(nullptr), current(nullptr), count(0) {}

    CircularLinkedList(const CircularLinkedList& other)
        : head(nullptr), current(nullptr), count(0)
    {
        copyFrom(other);
    }

    CircularLinkedList& operator=(const CircularLinkedList& other)
    {
        if (this != &other)
        {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    ~CircularLinkedList() { clear(); }

    bool IsEmpty() const { return count == 0; }
    bool IsNotEmpty() const { return count > 0; }

    void Insert(BookNode* book)
    {
        if (book == nullptr)
            return;

        if (head == nullptr)
        {
            head = book;
            book->next = book;
            current = book;
        }
        else
        {
            book->next = head->next;
            head->next = book;
        }
        count++;
    }

    BookNode* Remove()
    {
        if (IsEmpty())
            return nullptr;

        BookNode* first = head->next;

        if (first == head)
        {
            head = nullptr;
            current = nullptr;
        }
        else
        {
            head->next = first->next;
            if (current == first)
                current = first->next;
        }

        first->next = nullptr;
        count--;
        return first;
    }

    void InsertAt(BookNode* book, int index)
    {
        if (book == nullptr)
            return;

        if (count == 0)
        {
            Insert(book);
            return;
        }

        if (index < 0)
            index = normalizeIndex(index);
        else if (index > count)
            index %= count;

        if (index == 0)
        {
            Insert(book);
            return;
        }

        book->next = head->next;

        if (index == count)
        {
            head->next = book;
            head = book;
        }
        else
        {
            BookNode* previous = getNodeAt(index - 1);
            book->next = previous->next;
            previous->next = book;
        }
        count++;
    }

    BookNode* RemoveAt(int index)
    {
        if (IsEmpty())
            return nullptr;

        index = normalizeIndex(index);
        if (index == 0)
            return Remove();

        BookNode* previous = getNodeAt(index - 1);
        BookNode* removed = previous->next;
        previous->next = removed->next;

        if (removed == head)
            head = previous;
        if (current == removed)
            current = removed->next;

        removed->next = nullptr;
        count--;
        return removed;
    }

    void Swap(int firstIndex, int secondIndex)
    {
        if (IsEmpty())
            return;

        firstIndex = normalizeIndex(firstIndex);
        secondIndex = normalizeIndex(secondIndex);
        if (firstIndex == secondIndex)
            return;

        BookNode* first = getNodeAt(firstIndex);
        BookNode* second = getNodeAt(secondIndex);
        swap(first->id, second->id);
        swap(first->title, second->title);
    }

    void Sort()
    {
        for (int i = 0; i < count; i++)
        {
            for (int j = i + 1; j < count; j++)
            {
                BookNode* first = getNodeAt(i);
                BookNode* second = getNodeAt(j);
                if (first->id > second->id)
                {
                    swap(first->id, second->id);
                    swap(first->title, second->title);
                }
            }
        }
    }

    void Reverse()
    {
        if (count < 2)
            return;

        BookNode* oldTail = head;
        BookNode* oldFirst = head->next;
        BookNode* previous = oldTail;
        BookNode* currentNode = oldFirst;

        while (currentNode != oldTail)
        {
            BookNode* next = currentNode->next;
            currentNode->next = previous;
            previous = currentNode;
            currentNode = next;
        }

        oldTail->next = previous;
        head = oldFirst;
    }

    void MoveNext()
    {
        if (current != nullptr)
            current = current->next;
    }

    void PrintCurrent() const
    {
        if (current == nullptr)
            cout << "Collection is empty.\n";
        else
            cout << "Current book: " << current->id
                 << " - " << current->title << '\n';
    }

    void Print() const
    {
        if (IsEmpty())
        {
            cout << "Collection is empty.\n";
            return;
        }

        BookNode* node = head->next;
        for (int i = 0; i < count; i++)
        {
            cout << i << " | " << node->id << " | " << node->title;
            if (node == current)
                cout << " [CURRENT]";
            cout << '\n';
            node = node->next;
        }
        cout << "Total books: " << count << '\n';
    }
};

#endif
