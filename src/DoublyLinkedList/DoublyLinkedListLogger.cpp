#include "DoublyLinkedListLogger.h"
#include "DoublyLinkedList.h"

DoublyLinkedListLogger::DoublyLinkedListLogger(DoublyLinkedList* ptr) : m_list(ptr)
{
}

void DoublyLinkedListLogger::print_all_values()
{
	const Node* ptr_current_element = m_list->get_list_head();
	if (ptr_current_element != nullptr)
	{
		while (ptr_current_element != nullptr)
		{
			cout << ptr_current_element->data << "<->";
			ptr_current_element = ptr_current_element->next;
		}

		std::cout << " || ";
		print_size();
	}
	else
	{
		std::cout << "List is empty" << std::endl;
	}
}

void DoublyLinkedListLogger::print_size()
{
	std::cout << "Size of Doubly Linked List = " << m_list->get_size() << std::endl;
}

void DoublyLinkedListLogger::print_list_head()
{
	const Node* node = m_list->get_list_head();
	if (node)
	{
		std::cout << "List head = " << node->data << std::endl;
	}
	else
	{
		std::cout << "List head doesnt exist " << std::endl;
	}
}

void DoublyLinkedListLogger::print_list_tail()
{
	const Node* node = m_list->get_list_tail();
	if (node)
	{
		std::cout << "List tail = " << node->data << std::endl;
	}
	else
	{
		std::cout << "List tail doesnt exist " << std::endl;
	}
}