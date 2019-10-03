#include "DoublyLinkedList.h"

void main()
{
	DoublyLinkedList new_list;

	for (int i = 0; i < 10; i++)
		new_list.push_front(i);

	new_list.print_all_values();
	new_list.push_front(8);
	new_list.print_all_values();
	new_list.pop_front();
	new_list.print_all_values();
	new_list.pop_front();
	new_list.pop_front();
	new_list.pop_front();
	new_list.print_all_values();
	new_list.pop_front();
	new_list.pop_front();
	new_list.pop_front();
	new_list.pop_front();
	new_list.pop_front();
	new_list.pop_front();
	new_list.print_all_values();
	new_list.pop_front();
	std::cout << std::endl;
	new_list.print_all_values();

	new_list.push_back(10);
	new_list.print_all_values();
	new_list.push_back(11);
	new_list.push_back(12);
	new_list.push_back(13);
	new_list.push_back(14);
	new_list.push_back(15);
	new_list.push_back(16);
	new_list.print_all_values();
	new_list.push_back(0);
	new_list.print_all_values();
	new_list.push_front(9);
	new_list.print_all_values();
	new_list.pop_back();
	new_list.print_all_values();
	new_list.print_list_head();
	new_list.print_list_tail();
	new_list.pop_back();
	new_list.pop_back();
	new_list.print_all_values();
	new_list.print_list_head();
	new_list.print_list_tail();

	Node* node_by_index1 = new_list.get_node(2);
	Node* node_by_index2 = new_list.get_node(0);

	new_list.insert_after(node_by_index1, 33);
	new_list.print_all_values();

	Node* node_by_index3 = new_list.get_node(3);
	new_list.remove_node(node_by_index3);

	new_list.print_all_values();

	Node* node_by_index4 = new_list.get_node(0);
	new_list.remove_node(node_by_index4);
	new_list.print_all_values();

	Node* node_by_index5 = new_list.get_node(4);
	new_list.remove_node(node_by_index5);
	new_list.print_all_values();

	Node* node_by_index6 = new_list.get_node(2);
	new_list.remove_node(node_by_index6);
	new_list.print_all_values();

	new_list.push_front(8);
	new_list.push_front(27);
	new_list.push_front(22);
	new_list.push_back(37);
	new_list.push_back(41);
	new_list.push_back(99);

	new_list.print_all_values();
}