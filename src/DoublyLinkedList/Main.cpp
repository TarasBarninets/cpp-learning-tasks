#include "DoublyLinkedList.h"
#include "DoublyLinkedListLogger.h"

int main()
{
	DoublyLinkedList new_list;
	DoublyLinkedListLogger new_logger(&new_list);

	for (int i = 0; i < 10; i++)
		new_list.push_front(i);
	new_logger.print_all_values();

	new_list.push_front(8);
	new_logger.print_all_values();

	new_list.pop_front();
	new_logger.print_all_values();

	new_list.pop_front();
	new_list.pop_front();
	new_list.pop_front();
	new_logger.print_all_values();

	new_list.pop_front();
	new_list.pop_front();
	new_list.pop_front();
	new_list.pop_front();
	new_list.pop_front();
	new_list.pop_front();
	new_logger.print_all_values();

	new_list.pop_front();
	new_logger.print_all_values();

	new_list.push_back(10);
	new_logger.print_all_values();

	new_list.push_back(11);
	new_list.push_back(12);
	new_list.push_back(13);
	new_list.push_back(14);
	new_list.push_back(15);
	new_list.push_back(16);
	new_logger.print_all_values();

	new_list.push_back(0);
	new_logger.print_all_values();

	new_list.push_front(9);
	new_logger.print_all_values();

	new_list.pop_back();
	new_logger.print_all_values();
	new_logger.print_list_head();
	new_logger.print_list_tail();

	new_list.pop_back();
	new_list.pop_back();
	new_logger.print_all_values();
	new_logger.print_list_head();
	new_logger.print_list_tail();

	Node* node_by_index1 = new_list.get_node(2);
	new_list.insert_after(node_by_index1, 33);
	new_logger.print_all_values();

	Node* node_by_index3 = new_list.get_node(3);
	new_list.remove_node(node_by_index3);
	new_logger.print_all_values();

	Node* node_by_index4 = new_list.get_node(0);
	new_list.remove_node(node_by_index4);
	new_logger.print_all_values();

	Node* node_by_index5 = new_list.get_node(4);
	new_list.remove_node(node_by_index5);
	new_logger.print_all_values();

	Node* node_by_index6 = new_list.get_node(2);
	new_list.remove_node(node_by_index6);
	new_logger.print_all_values();

	new_list.push_front(8);
	new_list.push_front(27);
	new_list.push_front(22);
	new_list.push_back(37);
	new_list.push_back(41);
	new_list.push_back(99);
	new_logger.print_all_values();
	new_logger.print_size();
	new_logger.print_list_tail();

	return EXIT_SUCCESS;
}