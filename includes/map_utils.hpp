#ifndef MAP_UTILS_HPP
# define MAP_UTILS_HPP

#include <memory>
#include <string>
#include <iostream>
#include <limits>
#include "red_black_tree.hpp"

namespace ft {

template <class T1, class T2> 
struct pair {
	
	typedef T1	first_type;
	typedef T2	second_type;

	pair() : first(first_type()), second(second_type()) {}
	pair(const pair<T1, T2>&pr) : first(pr.first), second(pr.second) {} 
	template <class U, class V>
		pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {}
	pair(const first_type& a, const second_type& b) : first(a), second(b) {}


	operator pair<const first_type, second_type>() { return pair<const first_type, second_type>(first, second);}
	
	template <class U, class V>
		operator pair<U, V>() { return pair<U, V>(static_cast<U>(first), static_cast<V>(second));}

// //assignment operator
	pair & operator=(pair const & rhs) {
		new (this) pair(rhs);
		return (*this); }
	
	void	swap(pair& pr) {
		first_type	tmp_first;
		second_type	tmp_second;
		tmp_first = this->first;
		this->first = pr.first;
		pr.first = tmp_first;
		tmp_second = this->second;
		this->second = pr.second;
		pr.second = tmp_second;}

	first_type	first;
	second_type	second;
};

template <class T1, class T2>
  bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return lhs.first==rhs.first && lhs.second==rhs.second; }
template <class T1, class T2>
  bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return !(lhs==rhs); }
template <class T1, class T2>
  bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return lhs.first<rhs.first; }
template <class T1, class T2>
  bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return !(rhs<lhs); }
template <class T1, class T2>
  bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return rhs<lhs; }
template <class T1, class T2>
  bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return !(lhs<rhs); }

template< class T1, class T2 >
	ft::pair<T1,T2> make_pair( T1 t, T2 u ) { return (ft::pair<T1, T2>(t, u));}

template< class InputIt1, class InputIt2 >
bool lexicographical_compare_pair( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 ) {
	while (first1 != last1)
	{
		if (first2 == last2 || first2->second < first1->second)
			return false;
		else if (first1->second < first2->second)
			return true;
		first1++;
		first2++;
	}
	return (first2 != last2); }

template <class Iterator>
class bi_reverse_iterator {

public:
	typedef Iterator														iterator_type;
	typedef typename std::iterator_traits<iterator_type>::iterator_category	iterator_category;
	typedef typename std::iterator_traits<iterator_type>::value_type		value_type;
	typedef typename std::iterator_traits<iterator_type>::difference_type	difference_type;
	typedef typename std::iterator_traits<iterator_type>::pointer			pointer;
	typedef typename std::iterator_traits<iterator_type>::reference			reference;
	typedef typename iterator_type::pairRef									pairRef;
	typedef typename iterator_type::pairPointer								pairPointer;
	typedef typename iterator_type::const_tree::bi_iterator					const_iterator_type;

	bi_reverse_iterator() {}
	bi_reverse_iterator(const iterator_type & it) : _current(it) {}
	bi_reverse_iterator(const bi_reverse_iterator & it) { *this = it; }
	bi_reverse_iterator& 	operator=(bi_reverse_iterator const & rhs) {
		this->_current = rhs._current;
		return (*this); }

	iterator_type	base() const { return _current; }
	pairRef		operator*() const { iterator_type	base(_current); --base; return *base; }
	pairPointer	operator->() const { return &(operator*()); }

	bi_reverse_iterator&	operator++() { --_current; return *this; };
	bi_reverse_iterator		operator++(int) { return _current--; }
	bi_reverse_iterator&	operator--() { ++_current; return *this; }
	bi_reverse_iterator		operator--(int) { return _current++; } 

	bool operator==(const bi_reverse_iterator& rhs) { return (_current == rhs._current); }
	bool operator!=(const bi_reverse_iterator& rhs) { return (_current != rhs._current); }

	operator const	bi_reverse_iterator<const_iterator_type>() { 
		
		return bi_reverse_iterator<const_iterator_type>(static_cast<const_iterator_type>(this->_current));
	}

	protected:
		iterator_type	_current;
};

}



#endif

