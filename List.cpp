#include "List.h"
#include "CommonHeaders.h"
#include <iostream>

//===========//
// Help Node //
//===========//

Node::Node(double v) : value(v)
{
}

Node::~Node()
{
	if (DEBUG_PRINT)
	{
		std::cout << "-->> ~Node() -->> " << value << std::endl;
	}
}

//=====================//
// Default constructor //
//=====================//

List::List() = default;

//==================//
// Copy constructor //
//==================//

List::List(const List& other)
{
	List list;

	auto tmp = other.head;
	while (tmp)
	{
		list.Insert(tmp->value);
		tmp = tmp->next;
	}

	head = list.head;
	size = other.size;
	list.head = nullptr;
}

//=============================//
// Copy assignment constructor //
//=============================//

List& List::operator=(const List& other)
{
	if (&other != this)
	{
		List list;

		Node* tmp = other.head;
		while (tmp)
		{
			list.Insert(tmp->value);
			tmp = tmp->next;
		}

		head = list.head;
		size = other.size;
		list.head = nullptr;
	}

	return *this;
}

//==================//
// Move constructor //
//==================//

List::List(List&& other) noexcept
{
	if (&other != this)
	{
		head = other.head;
		size = other.size;
		other.head = nullptr;
		other.size = 0;
	}
}

//=============================//
// Move assignment constructor //
//=============================//

List& List::operator=(List&& other) noexcept
{
	if (&other != this)
	{
		head = other.head;
		size = other.size;
		other.head = nullptr;
		other.size = 0;
	}
	return *this;
}

//============================//
// Several constructors below //
//============================//

List::List(const std::initializer_list<double>& l)
{
	for (const auto& el: l)
	{
		Insert(el);
	}
}

List::List(const std::vector<double>& v)
{
	for (const auto& el: v)
	{
		Insert(el);
	}
}

//===========================================//
// Append list of nodes via initializer list //
//===========================================//

void List::Append(const std::initializer_list<double>& l)
{
	for (const auto& el: l)
	{
		Insert(el);
	}
}

//=================================//
// Append list of nodes via vector //
//=================================//

void List::Append(const std::vector<double>& l)
{
	for (const auto& el: l)
	{
		Insert(el);
	}
}

//===============//
// Insert a node //
//===============//

void List::Insert(double v)
{
	auto newNode = new Node(v);

	if (head == nullptr)
	{
		lastNode = newNode;
		head = newNode;
		size++;
	}
	else
	{
		lastNode->next = newNode;
		lastNode = newNode;
		size++;
	}
}

//============//
// Print list //
//============//

void List::Print() const
{
	if (DEBUG_PRINT)
	{
		auto tmp = head;

		while (tmp)
		{
			std::cout << "-->> Print() -->> " << tmp->value << std::endl;
			tmp = tmp->next;
		}
	}
}

//==========================================//
// Erase a node in list with specific value //
//==========================================//

int List::EraseOne(double value)
{
	auto tmp = head;

	// check the first element
	if (tmp && tmp->value == value)
	{
		head = head->next;
		delete tmp;
		size--;
		return 0;
	}

	// check the rest elements
	while (tmp)
	{
		if (tmp->next && tmp->next->value == value)
		{
			auto tmp2 = tmp->next->next;
			delete tmp->next;
			size--;
			tmp->next = tmp2;
			return 0;
		}
		tmp = tmp->next;
	}

	return -1;
}

//=============================================//
// Erase all nodes in list with specific value //
//=============================================//

int List::EraseAll(double value)
{
	int errorCode = 0;

	while (errorCode == 0)
	{
		errorCode = EraseOne(value);
	}

	return errorCode;
}

//=============================================//
// Erase all nodes in list with specific value //
//=============================================//

void List::Clear()
{
	while (head)
	{
		auto tmp = head;
		head = head->next;
		delete tmp;
		size--;
	}

	head = nullptr;
}

//=======================================//
// Get the number of element in the list //
//=======================================//

size_t List::Size() const
{
	return size;
}

//============================//
// Check if the list is empty //
//============================//

bool List::Empty() const
{
	return size == 0;
}

//===================//
// Reverses the list //
//===================//

void List::Reverse()
{
	auto current = head;
	Node* prev = nullptr;
	Node* next;

	while (current)
	{
		// Store next
		next = current->next;

		// Reverse current node's pointer
		current->next = prev;

		// Move pointers one position ahead.
		prev = current;
		current = next;
	}

	head = prev;
}

[[nodiscard]] int64_t List::FindOne(double v) const
{
	auto tmp = head;
	int64_t pos = -1;

	while (tmp)
	{
		pos++;
		if(tmp->value == v)
		{
			return pos;
		}
		tmp = tmp->next;
	}

	return -1;
}

[[nodiscard]] std::vector<int64_t> List::FindAll(double v) const
{
	auto tmp = head;
	int64_t pos = -1;
	std::vector<int64_t> positions;

	while (tmp)
	{
		pos++;
		if(tmp->value == v)
		{
			positions.push_back(pos);
		}
		tmp = tmp->next;
	}

	return positions;
}


//============//
// Destructor //
//============//

List::~List()
{
	Clear();
}
