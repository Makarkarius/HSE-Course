#include <iostream>
#include "list.h"

using namespace std;

task::list::list() {
	init();
}

task::list::list(size_t count, const int& value) {
	init();
    for(size_t i = 0; i < count; i++) {
        push_back(value);
    }
}

task::list::list(const list& other) {
	init();
	node *tmp = other.head;
	for (size_t i = 0; i < other.sz; i++) {
		push_back(tmp->value);
		tmp = tmp->next;
	}
}

task::list::~list() {
	node *tmp = head, *next;
	while(tmp != nullptr) {
		next = tmp->next;
		delete tmp;
		tmp = next;
	}

}

task::list& task::list::operator=(const list& other) {
	clear();
    node *tmp = other.head;
	for (size_t i = 0; i < other.sz; i++) {
		push_back(tmp->value);
		tmp = tmp->next;
    }
    return *this;
}

int& task::list::front() {
	if (empty())
		throw "list is empty";
	else
		return head->value;
}

const int& task::list::front() const {
	if (empty())
		throw "list is empty";
	else
		return head->value;
}

int& task::list::back() {
	if (empty())
		throw "list is empty";
	else
		return tail->value;
}

const int& task::list::back() const {
	if (empty())
		throw "list is empty";
	else
		return tail->value;
}

bool task::list::empty() const {
	return (sz == 0 ? 1 : 0);
}

size_t task::list::size() const {
	return sz;
}

void task::list::clear() {
	this->~list();
	head = nullptr;
	tail = nullptr;
	sz = 0;
}

void task::list::push_back(const int& _value) {
	node *tmp = new node;
	tmp->next = nullptr;
	tmp->value = _value;
    if(head == nullptr) {
        head = tmp;
        tail = tmp;
    } else {
        tail->next = tmp;
        tail = tmp;
    }
	sz++;
} 

void task::list::pop_back() {
	if (empty())
		return;
	if (sz == 1) {
		clear();
		return;
	}
	node *tmp = head;
	for (size_t i = 0; i < sz - 2; i++)
		tmp = tmp->next;
	delete tmp->next;
	tmp->next = nullptr;
	tail = tmp;
	sz--;
	if (sz == 1)
		head = tmp;
}

void task::list::push_front(const int& _value) {
	if (empty()) {
		push_back(_value);
		return;
	}
	node *tmp = new node;
	tmp->value = _value;
	tmp->next = head;
	head = tmp;
	sz++;
}

void task::list::pop_front() {
	if (empty())
		return;
	if (sz == 1) {
		clear();
		return;
	}
	node *first = head->next;
	delete head;
	head = first;
	sz--;
	if (sz == 1)
		tail = first;
}

void task::list::resize(size_t count) {
	if (count == 0) {
		clear();
		return;
	}
	if (sz == 0) {
		for (size_t i = 0; i < count; i++) {
			push_back(int());
		}
	}
	if (count >= sz) {
		node *tmp = tail;
		for (size_t i = 0; i < count - sz; i++) {
			node *add = new node;
			add->next = nullptr;
			add->value = int();
			tmp->next = add;
			tmp = tmp->next;
		}
		tail = tmp;
	} else {
		node *tmp = head, *next;
		for (size_t i = 0; i < count - 1; i++) {
			tmp = tmp->next;
		}
		tail = tmp;
		tmp = tmp->next;
		tail->next = nullptr;
		for (size_t i = count; i < sz; i++) {
			next = tmp->next;
			delete tmp;
			tmp = next;
		}
	}
	sz = count;
}

void task::list::swap(list& other) {
	std::swap(head, other.head);
	std::swap(sz, other.sz);
}

void task::list::remove(const int _value) {
	if (sz == 0)
		return;

	node *curr = head;
	node *prev = nullptr;

	bool head_set = 0; // checker if head set

	while (curr != nullptr) {
		if (curr->value == _value) {
			node *tmp = curr->next;
			delete curr;
			if(prev != nullptr)
				prev->next = nullptr;
			curr = tmp;
			sz--;
		} else {
			if (!head_set) {
				head = curr;
				head_set = 1;
			}
			if(prev != nullptr)
				prev->next = curr;
			prev = curr;
			curr = curr->next;
		}
	}
	tail = prev;
	if(tail != nullptr)
		tail->next = nullptr;
	if (sz == 0) {
		head = nullptr;
		tail = nullptr;
		return;
	}
	
}

void task::list::unique() {
	if (sz < 2)
		return;
	node *curr = head->next;
	node *prev = head;
	while(curr != nullptr) {
		if (curr->value == prev->value) {
			node *next = curr->next;
			delete curr;
			prev->next = nullptr;
			curr = next;
			sz--;
		} else {
			prev->next = curr;
			prev = curr;
			curr = curr->next;
		}
	}
	tail = prev;
}

void task::list::sort() {
	if (sz < 2)
		return;
	for (size_t j = 0; j < sz; j++) {
		node *curr = head;
		for (size_t i = 0; i < sz - 1; i++) {
			if (curr->value > curr->next->value)
				std::swap(curr->value, curr->next->value);
			curr = curr->next;
		}
	}
}
