/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:01:26 by cmarteau          #+#    #+#             */
/*   Updated: 2022/07/20 01:01:28 by cmarteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

#include <memory>
#include <cmath>
#include <string>
#include <iostream>
#include "set_binary_tree.hpp"
#include "set_utils.hpp"
#include "map_utils.hpp"

namespace ft {

template <class T, class Compare = std::less<T>,
    class Allocator = std::allocator<T> >
class set {

public:

	typedef T																		key_type;
	typedef T																		value_type;
	typedef Compare 																key_compare;
	typedef Allocator																allocator_type;	
	typedef typename allocator_type::reference										reference;
	typedef typename allocator_type::const_reference								const_reference;
	typedef typename allocator_type::pointer										pointer;
	typedef typename allocator_type::const_pointer									const_pointer;
	typedef typename ft::Node<value_type>*											node_pointer;
	typedef	typename ft::Tree<const value_type, Compare>::bi_iterator				iterator;
	typedef typename ft::Tree<const value_type, Compare>::bi_iterator				const_iterator;
	typedef typename ft::set_reverse_iterator<iterator>								reverse_iterator;					
	typedef typename ft::set_reverse_iterator<const_iterator>						const_reverse_iterator;					
	typedef typename ft::Tree<value_type, Compare>::bi_iterator::difference_type	difference_type;
	typedef size_t																	size_type;

	class value_compare: public std::binary_function<value_type,value_type,bool> {
		friend class set;
			protected:
					Compare comp;
					value_compare	(Compare c): comp(c) {};

			public:
					typedef	bool result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					value_compare	(value_compare const & c): comp(c.comp) {};
					bool	operator() (const value_type &x, const value_type &y) const {
							return comp(x, y);}
				};

private:
	key_compare						_key_compare;
	value_compare					_value_compare;
	allocator_type					_alloc;
	Tree<value_type, key_compare>	_tree;

public:

//constructors
	set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _key_compare(comp), _value_compare(comp), _alloc(alloc), _tree(_key_compare) {}
	template <class InputIterator>
		set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _key_compare(comp), _value_compare(comp), _alloc(alloc), _tree(_key_compare) { insert(first, last); }
	set(const set& copy) : _key_compare(copy._key_compare), _value_compare(copy._value_compare) { insert(copy.begin(), copy.end()); }

//destructor
	~set(void) { this->clear();}

//assignment operator
	set & operator=(set const & rhs) {
		_tree.clear();
		_key_compare = rhs._key_compare;
		_value_compare = rhs._value_compare;
		insert(rhs.begin(), rhs.end());
		return (*this); }

//Iterators	
	iterator 				begin() { 
		if (empty())
			return end();
		return  _tree.begin(); }
	const_iterator 			begin () const { 
		if (empty())
			return end();
		return _tree.begin(); }
	iterator 				end() { return _tree.end(); }
	const_iterator 			end() const { return _tree.end(); }
	reverse_iterator		rbegin() { return end(); }
	const_reverse_iterator	rbegin() const { return end(); }
	reverse_iterator		rend() { return begin(); }
	const_reverse_iterator	rend() const { return begin(); }

//Capacity
	size_type	size() const { return _tree.size(_tree.getRoot()); }
	size_type	max_size() const { return _tree._alloc.max_size();}
	bool		empty() const { return (this->size() == 0); }

//Modifiers
	pair<iterator, bool>	insert(const value_type& val) {
		bool	b = find(val) == end();
		if (b)
			_tree.insert(_tree.getRoot(), val);
		iterator it = find(val);
		return (ft::pair<iterator, bool>(it, b));}

	iterator		insert(iterator position, const value_type& val) {
		(void)position;
		return (insert(val).first);}

	template <class InputIterator>
		void		insert(InputIterator first, InputIterator last) {
			for (InputIterator it = first; it != last; ++it) {
				insert(*it);}}

	void		erase(iterator position) {
		_tree.deleteNode(_tree.getRoot(), *position);}

	size_type	erase(const value_type& k) {
		iterator it = find(k);
		if (it != _tree.getNil()) {
			_tree.deleteNode(_tree.getRoot(), *it);
			return 1;}
		return 0;}

	void		erase(iterator first, iterator last) {
		iterator tmp;
		for (iterator it = first; it != last;) {
			tmp = it;
			it++;
			erase(tmp);
		}}

	void	swap(set& x) {
		_tree.swap(x._tree);}

	void	clear() { _tree.clear(); }

//Observers
	key_compare		key_comp()	const { return _key_compare; }
	value_compare	value_comp() const {return _value_compare; }

// Operations
	iterator		find(const value_type& k) const {
		iterator	it(_tree.find(_tree.getRoot(), k));
		return it;}

	size_type		count(const value_type& k) const {
		if (const_iterator(find(k)) != end())
			return 1;
		return 0;}
	
	iterator		lower_bound (const value_type& k) const {
		iterator	it(_tree.lowerBound(_tree.getRoot(), k));
		return it;}

	iterator		upper_bound (const value_type& k) const {
		iterator	it(_tree.upperBound(_tree.getRoot(), k));
		return it;}
	
	pair<iterator, iterator>				equal_range (const value_type& k) const {
		return ft::make_pair(lower_bound(k), upper_bound(k));}

//Getter 
	allocator_type	get_allocator() const { return this->_alloc; }
};

//Relational operators overload
	template< class T, class Compare, class Alloc >
		bool operator==( const ft::set<T,Compare, Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs ) {
			if (lhs.size() != rhs.size())
				return (false);
			else
			for (typename ft::set<T,Compare,Alloc>::const_iterator it = lhs.begin(), it2 = rhs.begin(); it != lhs.end(); it++, it2++)
				if (*it != *it2)
					return (false);
			return (true);}
	template <class T, class Alloc>
		bool	operator!=(const set<T, Alloc>& lhs, const set<T, Alloc>& rhs) { return !(lhs == rhs); }	
	template <class T, class Alloc>
		bool	operator<(const set<T, Alloc>& lhs, const set<T, Alloc>& rhs) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }	
	template <class T,class Alloc>
		bool	operator<=(const set<T, Alloc>& lhs, const set<T, Alloc>& rhs) { return (lhs == rhs || lhs < rhs); }	
	template <class T,class Alloc>
		bool	operator>(const set<T, Alloc>& lhs, const set<T, Alloc>& rhs) { return !(lhs <= rhs); }	
	template <class T,class Alloc>
		bool	operator>=(const set<T, Alloc>& lhs, const set<T, Alloc>& rhs) { return !(lhs < rhs); }

//Swap(set)
	template <class T, class Alloc>
		void	swap(set<T, Alloc>& x, set<T, Alloc>& y) { x.swap(y); }
}

#endif


