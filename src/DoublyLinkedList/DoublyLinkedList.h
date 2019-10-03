#pragma once

#include <iostream>
using namespace std;

class Node {
public:
	Node(int value);

	int data;
	Node* next;
	Node* prev;
};

class DoublyLinkedList {
private:
	size_t m_list_size;
	Node* m_list_head;
	Node* m_list_tail;

public:
	DoublyLinkedList();
	~DoublyLinkedList() = default;

	void push_back(int data);
	void pop_back();
	void push_front(int data);
	void pop_front();
	void remove_node(Node* ptr);
	void insert_after(Node* after, int new_data);

	size_t get_size() const;
	Node* get_node(size_t index) const;
	Node* get_list_head() const;
	Node* get_list_tail() const;

};
