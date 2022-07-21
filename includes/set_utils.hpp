#ifndef SET_UTILS_HPP
# define SET_UTILS_HPP

#include <memory>
#include <string>
#include <iostream>
#include <limits>
#include "set_binary_tree.hpp"
#include "vector_iterators.hpp"

namespace ft {

template <class Iterator>
class set_reverse_iterator {

public:
	typedef Iterator														iterator_type;
	typedef typename std::iterator_traits<iterator_type>::iterator_category	iterator_category;
	typedef typename std::iterator_traits<iterator_type>::value_type		value_type;
	typedef typename std::iterator_traits<iterator_type>::difference_type	difference_type;
	typedef typename std::iterator_traits<iterator_type>::pointer			pointer;
	typedef typename std::iterator_traits<iterator_type>::reference			reference;
	typedef typename iterator_type::TRef									TRef;
	typedef typename iterator_type::TPointer								TPointer;
	typedef typename iterator_type::const_tree::bi_iterator					const_iterator_type;

	set_reverse_iterator() {}
	set_reverse_iterator(const iterator_type & it) : _current(it) {}
	template <class U>
	set_reverse_iterator(const set_reverse_iterator<U>& other) : _current(other.base()) {}

	template <class U>
	set_reverse_iterator& operator=(const set_reverse_iterator<U>& other) {
		this->_current = other.base();
		return (*this); }

	iterator_type	base() const { return _current; }
	TRef		operator*() const { iterator_type	base(_current); --base; return *base; }
	TPointer	operator->() const { return &(operator*()); }

	set_reverse_iterator&	operator++() { --_current; return *this; };
	set_reverse_iterator		operator++(int) { return _current--; }
	set_reverse_iterator&	operator--() { ++_current; return *this; }
	set_reverse_iterator		operator--(int) { return _current++; } 

	bool operator==(const set_reverse_iterator& rhs) { return (_current == rhs._current); }
	bool operator!=(const set_reverse_iterator& rhs) { return (_current != rhs._current); }

	operator const	set_reverse_iterator<const_iterator_type>() { 
		return set_reverse_iterator<const_iterator_type>(static_cast<const_iterator_type>(this->_current));
	}

	protected:
		iterator_type	_current;
};

}

#endif
