#include <iostream>
#include <vector> // dynamic array that increases because use memory on heap
#include <array> // static array that can not be increased std::array<Type, Num_elemnts> arr;
#include "Book.h"
#include <pugixml.hpp>
#include <assert.h>

using namespace std;

std::string const XML_FILE_PATH = "MyDemo.xml";

void BooksSerialization(const std::vector<Book>& items) // function that perform serialization from vector to XML file
{
	pugi::xml_document doc;
	pugi::xml_node bookstore = doc.append_child("Bookstore"); // xml_node type element as child of doc
	pugi::xml_attribute attribute = bookstore.append_attribute("atr"); // add attribute to bookstore node
	attribute.set_value("C/C++ books");

	for (const Book& item : items)
	{
		pugi::xml_node book = bookstore.append_child("book");

		pugi::xml_node title = book.append_child("title");
		pugi::xml_node title_text = title.append_child(pugi::node_pcdata);
		title_text.set_value(item.m_title.c_str());

		pugi::xml_node author = book.append_child("author");
		pugi::xml_node author_text = author.append_child(pugi::node_pcdata);
		author_text.set_value(item.m_author.c_str());

		pugi::xml_node year = book.append_child("year");
		pugi::xml_node year_text = year.append_child(pugi::node_pcdata);
		year_text.set_value(to_string(item.m_year).c_str());
		
		pugi::xml_node price = book.append_child("price");
		pugi::xml_node price_text = price.append_child(pugi::node_pcdata);
		price_text.set_value(to_string(item.m_price).c_str());
	}

	bool saveSucceeded = doc.save_file(XML_FILE_PATH.c_str(), "   ");
	assert(saveSucceeded);
}

vector<Book> BooksDeserialization(const std::string& path) // function that perform deserialization from XML file to vector
{
	/*pugi::xml_document doc;
	doc.load_file(path.c_str());

	for (pugi::xml_node node : doc.child("Bookstore"))
	{
		cout << "title = " << (node.child_value("title")) << endl;
		cout << "author = " << (node.child_value("author")) << endl;
		cout << "year = " << (node.child_value("year")) << endl;
		cout << "price = " << (node.child_value("price")) << endl;
		cout << "=======================================" << endl;
	}*/

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(path.c_str());

	pugi::xpath_query book_query("/Bookstore/book");
	pugi::xpath_query title_query("title/text()");
	pugi::xpath_query author_query("author/text()");
	pugi::xpath_query year_query("year/text()");
	pugi::xpath_query price_query("price/text()");

	pugi::xpath_node_set xpath_books = doc.select_nodes(book_query);
	size_t numBooks = xpath_books.size();

	vector<Book> vectorOfBooksAfterDeserialization;
	vectorOfBooksAfterDeserialization.reserve(numBooks);

	for (pugi::xpath_node xpath_book : xpath_books)
	{
		// Since Xpath results can be nodes or attributes, you must explicitly get the node out with .node()
		pugi::xml_node book = xpath_book.node();

		pugi::xml_node title = book.select_node(title_query).node();
		pugi::xml_node author = book.select_node(author_query).node();
		pugi::xml_node year = book.select_node(year_query).node();
		pugi::xml_node price = book.select_node(price_query).node();

		std::cout << "title : " << title.value() << std::endl;
		std::cout << "author: " << author.value() << std::endl;
		std::cout << "year : " << year.value() << std::endl;
		std::cout << "price: " << price.value() << std::endl;

		vectorOfBooksAfterDeserialization.push_back(Book(title.value(), author.value(), stoul(string(year.value())), stoi(string(price.value()))));
	}

	return vectorOfBooksAfterDeserialization;
}

int main()
{
	Book book1{ "C Programming Absolute Beginner's Guide", "Greg Perry", 2013, 21 };
	Book book2{ "The C Programming Language", "Brian W. Kernighan", 2000, 49 };
	Book book3{ "Learn C the Hard Way", "Zed A. Shaw", 2015, 26 };
	Book book4{ "Head First C", "David Griffiths", 2012, 45 };
	Book book5{ "C Programming: A Modern Approach", "K. N. King", 2000, 55 };
	Book book6{ "C++ Primer", "Stanley B. Lippman", 2012, 40 };
	Book book7{ "Effective Modern C++", "Scott Meyers", 2014, 38 };
	Book book8{ "The C++ Programming Language", "Bjarne Stroustrup", 2013, 52 };
	Book book9{ "Accelerated C++: Practical Programming by Example", "Andrew Koenig ", 2000, 32 };
	Book book10{ "Programming: Principles and Practice Using C++ (Developer's Library)", "Bjarne Stroustrup", 2008, 18 };

	std::array<Book, 10> booksArray = { book1, book2, book3, book4, book5, book6, book7, book8, book9, book10 }; // make copy of Book instance to array

	vector<Book> vectorOfBooks;
	vectorOfBooks.reserve(booksArray.size()); // change capacity - reserve enough memory
	for (int i = 0; i < booksArray.size(); i++)
	{
		std::cout << "SIZE = " << vectorOfBooks.size() << " CAPACITY = " << vectorOfBooks.capacity() << std::endl;
		vectorOfBooks.push_back(booksArray[i]);
	}

	for (int i = 0; i < vectorOfBooks.size(); i++)
		cout << i+1 << ". " << vectorOfBooks[i];

	BooksSerialization(vectorOfBooks);

	vector<Book> vectorOfBooksFromXML = BooksDeserialization(XML_FILE_PATH);

	for (int i = 0; i < vectorOfBooksFromXML.size(); i++)
		cout << i + 1 << ". " << vectorOfBooksFromXML[i];

	return EXIT_SUCCESS;
}