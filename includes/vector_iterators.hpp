#ifndef VECTOR_ITERATORS_HPP
# define VECTOR_ITERATORS_HPP

#include <memory>
#include <string>
#include <iostream>
#include <limits>

namespace ft {

template < class Iterator > 
struct	iterator_traits {

	typedef typename Iterator::difference_type					difference_type; // type to express the result of substracting one iterator from another
	typedef typename Iterator::value_type						value_type; // type of element the iterator can point to
	typedef typename Iterator::reference						reference;
	typedef typename Iterator::pointer							pointer;
	typedef typename Iterator::iterator_category				iterator_category; // should be random access iterator
};

template < class T > 
struct	iterator_traits<T*> {

	typedef std::ptrdiff_t						difference_type; // type to express the result of substracting one iterator from another
	typedef T									value_type; // type of element the iterator can point to
	typedef T&									reference;
	typedef T*									pointer;
	typedef std::random_access_iterator_tag		iterator_category; // should be random access iterator
};

template < class T > 
struct	iterator_traits<const T*> {

	typedef std::ptrdiff_t						difference_type; // type to express the result of substracting one iterator from another
	typedef T									value_type; // type of element the iterator can point to
	typedef const T&							reference;
	typedef const T*							pointer;
	typedef std::random_access_iterator_tag		iterator_category; // should be random access iterator
};

template < class T >
class iterator {

public:

	typedef typename iterator_traits<T>::iterator_category			iterator_category;
	typedef typename iterator_traits<T>::value_type					value_type;
	typedef typename iterator_traits<T>::difference_type			difference_type;
	typedef typename iterator_traits<T>::pointer					pointer;
	typedef typename iterator_traits<T>::reference					reference;
	typedef const value_type *										const_iterator_type;

	iterator() : _ptr(NULL) {}
	iterator(T ptr) : _ptr(ptr) {}
	T	get_ptr() const { return this->_ptr; }
	iterator(const iterator & it) : _ptr(it._ptr) {}
	
	iterator& 	operator=(iterator const & rhs) {
		this->_ptr = rhs._ptr;
		return (*this); }

	reference	operator*() const { return *(this->_ptr); }
	pointer		operator->() const { return this->_ptr; }

	iterator&	operator++() { this->_ptr++; return *this; };
	iterator	operator++(int) { return (this->_ptr)++; }
	iterator&	operator--() { this->_ptr--; return *this; }
	iterator	operator--(int) { return (this->_ptr)--; } 

	iterator	operator+(difference_type n) const { return (this->_ptr + n); }
	iterator	operator+=(difference_type n) { return (this->_ptr += n); }
	iterator	operator-(difference_type n) const { return (this->_ptr - n); }
	iterator	operator-=(difference_type n) { return (this->_ptr -= n); }
	reference	operator[](difference_type n) const { return (this->_ptr[n]); }

	operator const	iterator<const_iterator_type>() { return iterator<const_iterator_type>(const_cast<const_iterator_type>(this->_ptr));}

	protected:
		T	_ptr;
};

template <class Iterator1, class Iterator2 >
	bool operator==(const ft::iterator<Iterator1>& lhs, const ft::iterator<Iterator2>&rhs) { return (lhs.get_ptr() == rhs.get_ptr()); }
template <class Iterator1, class Iterator2 >
	bool operator!=(const ft::iterator<Iterator1>& lhs, const ft::iterator<Iterator2>&rhs) { return (lhs.get_ptr() != rhs.get_ptr()); }
template <class Iterator1, class Iterator2 >
	bool operator<(const ft::iterator<Iterator1>& lhs, const ft::iterator<Iterator2>&rhs) { return (lhs.get_ptr() < rhs.get_ptr()); }
template <class Iterator1, class Iterator2 >
	bool operator<=(const ft::iterator<Iterator1>& lhs, const ft::iterator<Iterator2>&rhs) { return (lhs.get_ptr() <= rhs.get_ptr()); }
template <class Iterator1, class Iterator2 >
	bool operator>(const ft::iterator<Iterator1>& lhs, const ft::iterator<Iterator2>&rhs) { return (lhs.get_ptr() > rhs.get_ptr()); }
template <class Iterator1, class Iterator2 >
	bool operator>=(const ft::iterator<Iterator1>& lhs, const ft::iterator<Iterator2>&rhs) { return (lhs.get_ptr() >= rhs.get_ptr()); }

template <class Iter>
iterator<Iter>
	operator+(typename iterator<Iter>::difference_type n, const iterator<Iter>& it) { return (it + n); }
template <class Iter>
typename iterator<Iter>::difference_type
	operator-(const iterator<Iter>& lhs, const iterator<Iter>& rhs) { return (lhs.get_ptr() - rhs.get_ptr()); }
template <class Iter1, class Iter2>
typename iterator<Iter1>::difference_type
	operator-(const iterator<Iter1>& lhs, const iterator<Iter2>& rhs) { return (lhs.get_ptr() - rhs.get_ptr()); }

template<bool Cond, class T = void> struct enable_if {};
template<class T> struct enable_if<true, T> { typedef T type; };

template < bool B >
	struct	integral_const { static const bool	value = B; };
template < class T >
	struct is_integral : integral_const<false> {};
template <>
	struct is_integral<bool> : integral_const<true> {};
template <>
	struct is_integral<char> : integral_const<true> {};
template <>
	struct is_integral<wchar_t> : integral_const<true> {};
template <>
	struct is_integral<signed char> : integral_const<true> {};
template <>
	struct is_integral<short int> : integral_const<true> {};
template <>
	struct is_integral<int> : integral_const<true> {};
template <>
	struct is_integral<long int> : integral_const<true> {};
template <>
	struct is_integral<long long int> : integral_const<true> {};
template <>
	struct is_integral<unsigned char> : integral_const<true> {};
template <>
	struct is_integral<unsigned short int> : integral_const<true> {};
template <>
	struct is_integral<unsigned int> : integral_const<true> {};
template <>
	struct is_integral<unsigned long int> : integral_const<true> {};
template <>
	struct is_integral<unsigned long long int> : integral_const<true> {};

template < class Iterator >
class reverse_iterator {

public: 
	typedef Iterator												iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;
	typedef const value_type *										const_iterator_type;

	reverse_iterator() : current(NULL) {}
	reverse_iterator(iterator_type x) : current(x) {}
	template <class U>
	reverse_iterator(const reverse_iterator<U>& other) : current(other.base()) {}

	template <class U>
	reverse_iterator& operator=(const reverse_iterator<U>& other) {
		this->current = other.base();
		return (*this); }

	iterator_type base() const { return this->current; }

	reference	operator*() const { Iterator tmp(this->current); tmp--; return *tmp; }
	pointer		operator->() const { return &(operator*()); }

	reverse_iterator&	operator++() { --this->current; return *this; };
	reverse_iterator	operator++(int) { return this->current--; }
	reverse_iterator&	operator--() { ++this->current; return *this; }
	reverse_iterator	operator--(int) { return this->current++; } 

	reverse_iterator	operator+(difference_type n) const { return (this->current - n); }
	reverse_iterator	operator+=(difference_type n) { return (this->current -= n); }
	reverse_iterator	operator-(difference_type n) const { return (this->current + n); }
	reverse_iterator	operator-=(difference_type n) { return (this->current += n); }
	reference			operator[](difference_type n) const { return (this->current[- n - 1]); }

	operator const	reverse_iterator<const_iterator_type>() { return reverse_iterator<const_iterator_type>(const_cast<const_iterator_type>(this->current));}

	protected:
		iterator_type	current;	
};

template <class Iterator1, class Iterator2 >
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>&rhs) { return (lhs.base() == rhs.base()); }
template <class Iterator1, class Iterator2 >
	bool operator==(const iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>&rhs) { return (lhs.base() == rhs.base()); }
template <class Iterator1, class Iterator2 >
	bool operator==(const reverse_iterator<Iterator1>& lhs, const iterator<Iterator2>&rhs) { return (lhs.base() == rhs.base()); }
template <class Iterator1, class Iterator2 >
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>&rhs) { return (lhs.base() != rhs.base()); }
template <class Iterator1, class Iterator2 >
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>&rhs) { return (lhs.base() > rhs.base()); }
template <class Iterator1, class Iterator2 >
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>&rhs) { return (lhs.base() >= rhs.base()); }
template <class Iterator1, class Iterator2 >
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>&rhs) { return (lhs.base() < rhs.base()); }
template <class Iterator1, class Iterator2 >
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>&rhs) { return (lhs.base() <= rhs.base()); }

template <class Iter>
reverse_iterator<Iter>
	operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it) { return (it + n); }
template <class Iter>
typename reverse_iterator<Iter>::difference_type
	operator-(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) { return rhs.base() - lhs.base(); }
template <class Iter1, class Iter2>
typename reverse_iterator<Iter1>::difference_type
	operator-(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) { return (rhs.base() - lhs.base()); }

template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 ) {
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1)
			return false;
		else if (*first1 < *first2)
			return true;
		first1++;
		first2++;
	}
	return (first2 != last2); }
}

#endif

