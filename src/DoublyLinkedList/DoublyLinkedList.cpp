#include "DoublyLinkedList.h"

void traversal_items_in_list(Node* ptr)
{
	// Recursion fall
	if (!ptr)
		return; // Recursion exit
	std::cout << ptr->data << std::endl;
	traversal_items_in_list(ptr->next);
	// Recursion rise
}

Node::Node(int value) : data(value),
next(nullptr),
prev(nullptr)
{
}

DoublyLinkedList::DoublyLinkedList() : m_list_size(0),
m_list_head(nullptr),
m_list_tail(nullptr)
{
}

DoublyLinkedList::~DoublyLinkedList()
{
	while (m_list_head != nullptr)
	{
		Node* temp_node = m_list_head;
		std::cout << "DoublyLinkedList destructor for node " << temp_node->data << std::endl;
		m_list_head = m_list_head->next;
		--m_list_size;
		delete temp_node;
	}
}


void DoublyLinkedList::push_front(int data) {
	std::cout << "Called push_front() : " << data << std::endl;
	Node* new_node = new Node(data);
	++m_list_size;

	if (m_list_head)
	{
		new_node->next = m_list_head;
		m_list_head->prev = new_node;
	}
	else
	{
		m_list_tail = new_node;
	}

	m_list_head = new_node;
}

void DoublyLinkedList::pop_front() {
	std::cout << "Called pop_front() : " << m_list_head->data << std::endl;

	if (m_list_size == 0)
	{
		std::cout << "Cant delete element. List is empty";
		return;
	}

	if (m_list_size > 1)
	{
		--m_list_size;
		m_list_head->next->prev = nullptr;
		Node* temp_head = m_list_head;
		m_list_head = m_list_head->next;
		delete temp_head;
	}
	else
	{
		delete m_list_head;
		--m_list_size;
		m_list_head = nullptr;
		m_list_tail = nullptr;
		std::cout << "Deleted last element. List is empty";
	}
}

void DoublyLinkedList::push_back(int data)
{
	std::cout << "Called push_back() : " << data << std::endl;
	Node* new_node = new Node(data);
	++m_list_size;
	if(m_list_tail)
	{
		m_list_tail->next = new_node;
		new_node->prev = m_list_tail;
		new_node->next = nullptr;
		m_list_tail = new_node;
	}
	else
	{
		m_list_head = m_list_tail = new_node;
	}
}

void DoublyLinkedList::pop_back()
{
	std::cout << "Called pop_back() : " << m_list_tail->data << std::endl;

	if (m_list_size == 0)
	{
		std::cout << "Cant delete element. List is empty";
		return;
	}

	if (m_list_size > 1)
	{
		Node* previouseNode = m_list_tail->prev;
		previouseNode->next = nullptr;
		delete m_list_tail;
		m_list_tail = previouseNode;
	}
	else
	{
		delete m_list_tail;
		m_list_tail = nullptr;
		m_list_head = nullptr;
		std::cout << "Deleted last element. List is empty !" << std::endl;
	}

	--m_list_size;
}

Node* DoublyLinkedList::get_list_head() const
{
	return m_list_head;
}

Node* DoublyLinkedList::get_list_tail() const
{
	return m_list_tail;
}


void DoublyLinkedList::remove_node(Node* ptr)
{
	if (ptr == nullptr)
	{
		cout << "Cant remove - dont exist this node" << endl;
		return;
	}

	std::cout << "Called remove_node() : " << ptr->data << std::endl;

	if (ptr == m_list_head)
	{
		ptr->next->prev = nullptr;
		m_list_head = ptr->next;
	}
	else if (ptr == m_list_tail)
	{
		ptr->prev->next = nullptr;
		m_list_tail = ptr->prev;
	}
	else
	{
		ptr->next->prev = ptr->prev;
		ptr->prev->next = ptr->next;
	}

	--m_list_size;
	delete ptr;
}


void DoublyLinkedList::insert_after(Node* after, int new_data)
{
	std::cout << "Called insert_after() : " << new_data << " " << std::endl;
	if (!after)
	{
		// invalid pointer
		return;
	}
	if (after == m_list_tail) //if insert after tail
	{
		++m_list_size;
		Node* new_node = new Node(new_data);
		new_node->prev = after;
		new_node->next = nullptr;
		after->next = new_node;
		return;
	}
	else
	{
		// construct new elemnt and set correct pointer to prev and next elements
		++m_list_size;
		Node* new_node = new Node(new_data);
		new_node->prev = after;
		new_node->next = after->next;

		after->next->prev = new_node;
		after->next = new_node;
	}
}

Node* DoublyLinkedList::get_node(size_t index) const
{
	size_t temp_list_size = m_list_size;
	if (index <= temp_list_size)
	{
		Node* result_node = nullptr;

		bool isInLeftSide = (index <= (temp_list_size / 2));
		if (isInLeftSide)
		{
			size_t current_position = 0;
			result_node = m_list_head;
			while (current_position != index)
			{
				++current_position;
				result_node = result_node->next;
			}
		}
		else
		{
			-- temp_list_size;
			result_node = m_list_tail;
			while (temp_list_size != index)
			{
				--temp_list_size;
				result_node = result_node->prev;
			}
		}

		cout << "Node by index [" << index << "] = " << result_node->data << std::endl;
		return result_node;
	}
	else
	{
		return nullptr;
	}


}

size_t DoublyLinkedList::get_size() const
{
	return m_list_size;
}
