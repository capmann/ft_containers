
#ifndef MAP_HPP
# define MAP_HPP

#include <memory>
#include <cmath>
#include <string>
#include <iostream>
#include "red_black_tree.hpp"
#include "map_utils.hpp"
#include "vector_iterators.hpp"

//std::map is a sorted associative container that contains key-value pairs with unique keys. 
//Keys are sorted by using the comparison function Compare. 
//Search, removal, and insertion operations have logarithmic complexity. 
//Maps are usually implemented as red-black trees

//in a map, the key values are generally used to sort and uniquely identify the elements, while the mapped values store the content associated to this key.
//The types of key and mapped value may differ and are grouped together in member type value_type, which is a pair combining them.
//Internally, the elements in a map are always sorted by its keys following a specific strict weak ordering criterion indicated by its internal comparison object.
//Map containers are generally slower than unordered_map containers to access individual elements by their key, but they allow the direct iteration on subsets based on their order.
//The mapped values in a map can be accessed directly by their corresponding key using the bracket operator.


//Compare: a binary predicate that takes two element keys as arguments and returns a bool. 
//The expression comp(a, b) shall return true is a is considered to go before b. 
//The map object uses this expression to determine both the order the elements follow in the container, and whether two elements keys are equivalent.
//Two objects are equivalent if !comp(a,b) && !comp(b,a).


namespace ft {

template <class Key, class T, class Compare = std::less<Key>,
    class Allocator = std::allocator<pair<const Key, T> > >
class map {

public:

	typedef Key																		key_type;
	typedef T																		mapped_type;
	typedef ft::pair<const key_type, mapped_type>									value_type;
	typedef Compare 																key_compare;
	typedef Allocator																allocator_type;	
	typedef typename allocator_type::reference										reference;
	typedef typename allocator_type::const_reference								const_reference;
	typedef typename allocator_type::pointer										pointer;
	typedef typename allocator_type::const_pointer									const_pointer;
	typedef typename ft::Node<value_type>*											node_pointer;
	typedef	typename ft::Tree<value_type, Compare>::bi_iterator						iterator;
	typedef typename ft::Tree<const value_type, Compare>::bi_iterator				const_iterator;
	typedef typename ft::bi_reverse_iterator<iterator>								reverse_iterator;					
	typedef typename ft::bi_reverse_iterator<const_iterator>						const_reverse_iterator;					
	typedef typename ft::Tree<value_type, Compare>::bi_iterator::difference_type	difference_type;
	typedef size_t																	size_type;

	struct value_compare: public std::binary_function<value_type,value_type,bool> {
			protected:
					Compare comp;

			public:
					value_compare	(Compare c): comp(c) {};
					typedef	bool result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					value_compare	(value_compare const & c): comp(c.comp) {};
					bool	operator() (const value_type &x, const value_type &y) const {
							return comp(x.first, y.first);}
				};

private:
	key_compare						_key_compare;
	value_compare					_value_compare;
	allocator_type					_alloc;
	Tree<value_type, key_compare>	_tree;

public:

//constructors
	map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _key_compare(comp), _value_compare(comp), _alloc(alloc), _tree(_key_compare) {}
	template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _key_compare(comp), _value_compare(comp), _alloc(alloc), _tree(_key_compare) { insert(first, last); }
	map(const map& copy) : _key_compare(copy._key_compare), _value_compare(copy._value_compare) { insert(copy.begin(), copy.end()); }

//destructor
	~map(void) { this->clear();}

//assignment operator
	map & operator=(map const & rhs) {
		_tree.clear();
		_key_compare = rhs._key_compare;
		_value_compare = rhs._value_compare;
		for (const_iterator it = rhs.begin(); it != rhs.end(); ++it)
			insert(ft::make_pair(it->first, it->second));
		return (*this); }

//Iterators	
	iterator 				begin() { return _tree.begin(); }
	const_iterator 			begin () const { return const_iterator(_tree.begin()); }
	iterator 				end() { return _tree.end(); }
	const_iterator 			end() const { return const_iterator(_tree.end()); }
	reverse_iterator		rbegin() { return _tree.rbegin(); }
	const_reverse_iterator	rbegin() const { return _tree.rbegin(); }
	reverse_iterator		rend() { return _tree.rend(); }
	const_reverse_iterator	rend() const { return _tree.rend(); }

//Capacity
	size_type	size() const { return _tree.size(_tree.getRoot()); }
	size_type	max_size() const { return _tree._alloc.max_size();}
	bool		empty() const { return (this->size() == 0); }

//Element access
	mapped_type&		operator[](const key_type& k) { return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;}

//Modifiers
	pair<iterator, bool>	insert(const value_type& val) {
		bool	b = find(val.first) == end();
		if (b)
			_tree.insert(_tree.getRoot(), val);
		iterator it = find(val.first);
		return (ft::pair<iterator, bool>(it, b));}

	iterator		insert(iterator position, const value_type& val) {
		(void)position;
		return (insert(val)).first;}

	template <class InputIterator>
		void		insert(InputIterator first, InputIterator last) {
			for (InputIterator it = first; it != last; ++it) {
				insert(ft::make_pair(it->first, it->second));}}

	void		erase(iterator position) {
		_tree.deleteNode(_tree.getRoot(), *position);}

	size_type	erase(const key_type& k) {
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

	void	swap(map& x) {
		_tree.swap(x._tree);}

	void	clear() { _tree.clear(); }

//Observers
	key_compare		key_comp()	const { return _key_compare; }
	value_compare	value_comp() const {return _value_compare; }

//Operations
	iterator		find(const key_type& k) {
		iterator	it(_tree.find_key(_tree.getRoot(), k));
		return (it == _tree.getNil() ? end() : it);}

	const_iterator	find(const key_type& k) const {
		const_iterator	it(_tree.find_key(_tree.getRoot(), k));
		return (it);}

	size_type		count(const key_type& k) const {
		if (find(k) != end())
			return 1;
		return 0;}
	
	iterator		lower_bound (const key_type& k) {
		iterator	it(_tree.lowerBound(_tree.getRoot(), k));
		return (it == _tree.getNil() ? end() : it);}
	
	const_iterator	lower_bound (const key_type& k) const {
		const_iterator	it(_tree.lowerBound(_tree.getRoot(), k));
		return (it);}

	iterator		upper_bound (const key_type& k) {
		iterator	it(_tree.upperBound(_tree.getRoot(), k));
		return (it == _tree.getNil() ? end() : it);}
		
	const_iterator	upper_bound (const key_type& k) const {
		const_iterator	it(_tree.upperBound(_tree.getRoot(), k));
		return (it);}

	pair<const_iterator, const_iterator>	equal_range (const key_type& k) const {
		return ft::make_pair(lower_bound(k), upper_bound(k));}

	pair<iterator, iterator>				equal_range (const key_type& k) {
		return ft::make_pair(lower_bound(k), upper_bound(k));}

//Getter 
	allocator_type	get_allocator() const { return this->_alloc; }
};

//Relational operators overload
	template< class Key, class T, class Compare, class Alloc >
		bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
			if (lhs.size() != rhs.size())
				return (false);
			else
			for (typename ft::map<Key,T,Compare,Alloc>::const_iterator it = lhs.begin(), it2 = rhs.begin(); it != lhs.end(); it++, it2++)
				if (*it != *it2)
					return (false);
			return (true);}
	template <class Key, class T, class Alloc>
		bool	operator!=(const map<Key, T, Alloc>& lhs, const map<Key, T, Alloc>& rhs) { return !(lhs == rhs); }	
	template <class Key, class T, class Alloc>
		bool	operator<(const map<Key, T, Alloc>& lhs, const map<Key, T, Alloc>& rhs) {
			return ft::lexicographical_compare_pair(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }	
	template <class Key, class T,class Alloc>
		bool	operator<=(const map<Key, T, Alloc>& lhs, const map<Key, T, Alloc>& rhs) { return (lhs == rhs || lhs < rhs); }	
	template <class Key, class T,class Alloc>
		bool	operator>(const map<Key, T, Alloc>& lhs, const map<Key, T, Alloc>& rhs) { return !(lhs <= rhs); }	
	template <class Key, class T,class Alloc>
		bool	operator>=(const map<Key, T, Alloc>& lhs, const map<Key, T, Alloc>& rhs) { return !(lhs < rhs); }

//Swap(map)
	template <class Key, class T, class Alloc>
		void	swap(map<Key, T, Alloc>& x, map<Key, T, Alloc>& y) { x.swap(y); }
}

#endif

