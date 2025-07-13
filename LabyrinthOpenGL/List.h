#pragma once
#include <iostream>
using namespace std;

namespace _List {

    template <typename T>
    class Node {
    public:
        T info;
        Node* next;

        Node(T value) : info(value), next(nullptr) {}

        void printNode() const {
            cout << "INFO: " << info << " | SELF: " << this
                << " | NEXT: " << next << endl;
        }
    };

    template <typename U>
    class List {
    private:
        Node<U>* head;
        Node<U>* tail;
        size_t count;

    public:
        class Iterator {
        private:
            Node<U>* current;
        public:
            Iterator(Node<U>* node) : current(node) {}

            U& operator*() { return current->info; }
            Iterator& operator++() {
                current = current->next;
                return *this;
            }
            bool operator!=(const Iterator& other) const {
                return current != other.current;
            }
        };

        Iterator begin() const { return Iterator(head); }
        Iterator end() const { return Iterator(nullptr); }

        List() : head(nullptr), tail(nullptr), count(0) {}
        ~List() { clear(); }

        void push_back(U value) {
            Node<U>* node = new Node<U>(value);
            if (!head)
                head = tail = node;
            else {
                tail->next = node;
                tail = node;
            }
            ++count;
        }

        void push_front(U value) {
            Node<U>* node = new Node<U>(value);
            node->next = head;
            head = node;
            if (!tail) tail = node;
            ++count;
        }

        void pop_front() {
            if (!head) throw runtime_error("List is empty");
            Node<U>* temp = head;
            head = head->next;
            delete temp;
            --count;
            if (!head) tail = nullptr;
        }

        void pop_back() {
            if (!head) throw runtime_error("List is empty");

            if (head == tail) {
                delete head;
                head = tail = nullptr;
            }
            else {
                Node<U>* prev = head;
                while (prev->next != tail)
                    prev = prev->next;

                delete tail;
                tail = prev;
                tail->next = nullptr;
            }
            --count;
        }

        void remove_at(size_t index) {
            if (index >= count) throw out_of_range("Index out of range");
            if (index == 0) return pop_front();

            Node<U>* prev = head;
            for (size_t i = 0; i < index - 1; ++i)
                prev = prev->next;

            Node<U>* toDelete = prev->next;
            prev->next = toDelete->next;
            if (toDelete == tail) tail = prev;
            delete toDelete;
            --count;
        }

        void insert(size_t index, U value) {
            if (index > count) throw out_of_range("Index out of range");
            if (index == 0) return push_front(value);
            if (index == count) return push_back(value);

            Node<U>* prev = head;
            for (size_t i = 0; i < index - 1; ++i)
                prev = prev->next;

            Node<U>* node = new Node<U>(value);
            node->next = prev->next;
            prev->next = node;
            ++count;
        }

        U& operator[](size_t index) {
            if (index >= count) throw out_of_range("Index out of range");
            Node<U>* current = head;
            for (size_t i = 0; i < index; ++i)
                current = current->next;
            return current->info;
        }

        size_t size() const { return count; }
        bool empty() const { return count == 0; }

        void clear() {
            Node<U>* current = head;
            while (current) {
                Node<U>* next = current->next;
                delete current;
                current = next;
            }
            head = tail = nullptr;
            count = 0;
        }

        void showList() const {
            Node<U>* p = head;
            if (!p) {
                cout << "List is empty!\n";
                return;
            }
            while (p) {
                p->printNode();
                p = p->next;
            }
        }
    };

}
