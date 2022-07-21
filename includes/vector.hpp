
#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <string>
#include <iostream>
#include "vector_iterators.hpp"

namespace ft {

template < class T, class Alloc = std::allocator<T> > 
class	vector {

public:

	typedef T														value_type;
	typedef Alloc													allocator_type;
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
	typedef	typename ft::iterator<T*>								iterator;
	typedef typename ft::iterator<const T*>							const_iterator;
	typedef typename ft::reverse_iterator<iterator>					reverse_iterator;					
	typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;					
	typedef typename ft::iterator<T*>::difference_type				difference_type;
	typedef size_t													size_type;

private:
	size_type			_size;
	size_type			_capacity;
	pointer				_container;
	allocator_type		_alloc;

public:

//constructors
	vector(const allocator_type& alloc = allocator_type()) : _size(size_type()), _capacity(0), _container(NULL), _alloc(alloc) {}
	vector(size_type n, const value_type &val = value_type(), const allocator_type& alloc=allocator_type()) : _size(0), _capacity(0), _container(NULL), _alloc(alloc) { assign(n, val); }
	template <class InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _size(size_type()), _capacity(0), _container(NULL), _alloc(alloc) { assign(first, last); }
	vector(const vector & copy) : _size(size_type()), _capacity(0), _container(NULL), _alloc(allocator_type()) { *this = copy; }

//destructor
	~vector(void) {
		this->clear();
		if (this->_capacity)
			this->_alloc.deallocate(this->_container, this->_capacity); // releases a block of storage previously allocated. The elements in the array are not destroyed by a call to this member function. 
		this->_capacity = 0;}

//assignment operator
	vector & operator=(vector const & rhs) {
		if (rhs._container != this->_container) {
		this->clear();
		this->assign(rhs.begin(), rhs.end());}
		return (*this); }

//Iterators	
	iterator 				begin() { if (empty()) return end(); return iterator(this->_container); }
	const_iterator 			begin () const { if (empty()) return end(); return const_iterator(this->_container); }
	iterator 				end() { return iterator(this->_container + this->_size); }
	const_iterator 			end() const { return const_iterator(this->_container + this->_size); }
	reverse_iterator		rbegin() { return reverse_iterator(this->end()); }
	const_reverse_iterator	rbegin() const { return const_iterator(rbegin()); }
	reverse_iterator		rend() { return reverse_iterator(this->begin()); }
	const_reverse_iterator	rend() const { return const_iterator(rend()); }

//Capacity
	size_type	size() const { return this->_size; }
	size_type	capacity() const { return this->_capacity; }
	size_type	max_size() const { return this->_alloc.max_size();}
	bool		empty() const { return (this->_size == 0); }

	void		reserve(size_type n) {
		pointer	tmp;
		size_t	tmp_cap;
		if (n <= this->_alloc.max_size()) {
			if (n > this->_capacity) {
				tmp_cap = (this->_capacity ? this->_capacity : 1);
				while (tmp_cap < n)
					tmp_cap = tmp_cap * 2;
				tmp = this->_alloc.allocate(tmp_cap);
				for (size_t i = 0; i < this->_size; i++)
					this->_alloc.construct(tmp + i, *(this->_container + i));
				if (this->_capacity) {
					for (size_t i = 0; i < this->_size; i++)
						this->_alloc.destroy(this->_container + i);
					this->_alloc.deallocate(this->_container, this->_capacity);}
				this->_container = tmp;
				this->_capacity = tmp_cap;}}
		else
			throw std::length_error("vector");}

	void	resize(size_type n, value_type val = value_type()) {
		this->reserve(n);
		for (size_t i = this->_size; i < n; i++) {
				this->_alloc.construct(this->_container + i, val);
				this->_size++; }
		for (size_t	i = this->_size; i > n; i--) {
				this->_alloc.destroy(this->_container + i - 1);
				this->_size--; } 		
		
}

//Element access
	reference		operator[](size_type n) { return this->_container[n]; }
	const reference	operator[](size_type n) const { return this->_container[n]; }

	reference		at(size_type n) {
		if (n < this->_size)
			return ((*this)[n]);
		throw std::out_of_range("vector"); }

	const reference	at(size_type n) const {
		if (n < this->_size)
			return ((*this)[n]);
		throw std::out_of_range("vector"); }

	reference		front() { return (*this)[0]; }
	reference		back() { return (*this)[this->_size -1]; }
	const reference	front() const { return (*this)[0]; }
	const reference	back() const { return (*this)[this->_size - 1]; }


//Modifiers
	template <class InputIterator>
	void	assign(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
		size_t			i = 0;
		for (InputIterator it = first; it != last; it++)
			i++;
		this->resize(i);
		i = 0;
		for (InputIterator it = first; it != last; it++)
			this->_alloc.construct(this->_container + i++, *it); }

	void	assign(size_t n, const value_type& val) {
		this->resize(n);
		for (size_t i = 0; i < n; i++)
			this->_alloc.construct(this->_container + i, val);}

	void	push_back(const value_type& val) {
		this->resize(this->_size + 1);
		this->_alloc.construct(this->_container + this->_size - 1, val);}

	void	pop_back() {
		this->_alloc.destroy(this->_container + --this->_size); }

	iterator	insert(iterator position, const value_type& val) {
		size_type	i = 0;
		for (iterator it = this->begin(); it != position; it++)
			i++;
		this->resize(this->_size + 1);
		iterator new_pos = this->begin() + i;
		for (iterator it = this->end() - 1; it != new_pos; it--) {
			this->_alloc.destroy(&(*it));
			this->_alloc.construct(&(*it), *(it - 1));}
		this->_alloc.destroy(&(*new_pos));
		this->_alloc.construct(&(*new_pos), val);
		return(new_pos);}

	void	insert(iterator position, size_type n, const value_type& val) {
		for (size_type	i = 0; i < n; i++)
			position = this->insert(position, val);}

	template <class InputIterator>
		void	insert(iterator position, InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
			InputIterator	it;
			last--;
			first--;
			for (it = last; it != first; it--)
				position = insert(position, *it); }

	iterator	erase(iterator position) {
		return (erase(position, position + 1));}

	iterator	erase(iterator first, iterator last) {
		size_t		i = 0;
		iterator	it(this->_container);
		for (it = first; it != last; it++)
			i++;
		for (it = first + i; it != this->end(); it++) {
			this->_alloc.destroy(&(*(it - i)));
			this->_alloc.construct(&(*(it - i)), *it);}
		for (it = this->end() - 1; it != this->end() - i; it--)		
			this->_alloc.destroy(&(*it));
		this->resize(this->_size - i);
		return(first); }

	void	swap(vector & x) {
		size_type	tmp_size = this->_size;
		size_type	tmp_cap = this->_capacity;
		pointer		tmp_container = this->_container;
		this->_size = x._size;
		this->_capacity = x._capacity;
		this->_container = x._container;
		x._size = tmp_size;
		x._capacity =  tmp_cap;
		x._container = tmp_container; }

	void	clear() {
		while (this->_size)
			this->_alloc.destroy(this->_container + (--this->_size));}

//getters
	pointer&		get_ptr(void) { return this->_container; }
	allocator_type	get_allocator() const { return this->_alloc; }
};

// Relational operators overload
	template <class T,class Alloc>
		bool	operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { 
			typename vector<T, Alloc>::size_type	i;
			if (lhs.size() != rhs.size())
				return false;
			for (i = 0; i < lhs.size(); i++)
				if (lhs[i] != rhs[i])
					return false;
			return true; }
	template <class T,class Alloc>
		bool	operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(lhs == rhs); }	
	template <class T,class Alloc>
		bool	operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }	
	template <class T,class Alloc>
		bool	operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return (lhs == rhs || lhs < rhs); }	
	template <class T,class Alloc>
		bool	operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(lhs <= rhs); }	
	template <class T,class Alloc>
		bool	operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(lhs < rhs); }

// Swap(vector)
	template <class T, class Alloc>
		void	swap(vector<T, Alloc>& x, vector<T, Alloc>& y) { x.swap(y); }
}

#endif

