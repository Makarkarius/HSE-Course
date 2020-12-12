#pragma once
#include <cstddef>

namespace task {


class list {

public:

    list();
    list(size_t count, const int& value = int());
	list(const list& other);

    ~list();
    list& operator=(const list& other);


    int& front();
    const int& front() const;

    int& back();
    const int& back() const;


    bool empty() const;
    size_t size() const;
    void clear();


    void push_back(const int& value);
    void pop_back();
    void push_front(const int& value);
    void pop_front();
    void resize(size_t count);
    void swap(list& other);


    void remove(const int value);
    void unique();
    void sort();

       
    void print() { // for debug
        node *curr = this->head;
        for(size_t i = 0; i < sz; i++) {
            std::cout << curr->value << " ";
            curr = curr->next;
        }
        std::cout << "\n";
    }

private:
	void init() {
		head = nullptr;
		tail = nullptr;
		sz = 0;
	}

    struct node {
        int value;
        node *next;
    };

    
    size_t sz;
    node *head, *tail;
    

};

}
