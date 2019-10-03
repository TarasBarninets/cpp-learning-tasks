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
	~DoublyLinkedList();

	void push_back(int data);
	void pop_back();
	void push_front(int data);
	void pop_front();
	Node* list_head();
	Node* list_tail();
	void remove_node(Node* ptr);
	void insert_after(Node* after, int new_data);
	Node* get_node(size_t index);
	size_t get_size();

	// added only for testing purpouse, will be removed in final implementation
	void print_all_values();
	void print_size();
	void print_list_head();
	void print_list_tail();
};
