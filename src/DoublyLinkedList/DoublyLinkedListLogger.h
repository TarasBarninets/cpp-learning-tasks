#pragma once

class DoublyLinkedList;

class DoublyLinkedListLogger {
public:
	DoublyLinkedListLogger(DoublyLinkedList* ptr);
	~DoublyLinkedListLogger() = default;

	void print_all_values();
	void print_size();
	void print_list_head();
	void print_list_tail();

private:
	DoublyLinkedList* m_list;
};