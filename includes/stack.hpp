
#ifndef STACK_HPP
# define STACK_HPP

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "vector.hpp"
#include "vector_iterators.hpp"

//Stacks are a type of container adaptor, specifically designed to operate in a LIFO context (last-in first-out), where elements are inserted and extracted only from one end of the container.
//Elements are pushed/popped from the "back" of the specific container, which is known as the top of the stack

namespace ft {

template < class T, class Container = ft::vector<T> > 
class	stack {

public:

	typedef T								value_type;
	typedef Container						container_type;
	typedef typename Container::size_type	size_type;

protected:

	container_type	c;

public:
//constructors: constructs a stack container adaptor object 
	explicit stack(const container_type& c = container_type()) : c(c) {}

//destructor
	~stack(void) {}

//operator=
	stack&	operator=(const stack& rhs) { this->c = rhs.c; return *this; }

//Member functions	

	bool			empty() const { return this->c.empty(); }
	size_type		size() const { return this->c.size(); }
	value_type	& 	top() { return this->c.back(); }
	void			push(const value_type & val) { return this->c.push_back(val); }
	void			pop() { return this->c.pop_back(); }

//Relational operators

	friend bool	operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return (lhs.c == rhs.c); }
	friend bool	operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return (lhs.c != rhs.c); }
	friend bool	operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return (lhs.c >= rhs.c); }
	friend bool	operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return (lhs.c > rhs.c); }
	friend bool	operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return (lhs.c <= rhs.c); }
	friend bool	operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return (lhs.c < rhs.c); }

};
}

#endif

