#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <memory>
#include <string>
#include <iostream>
#include "map_utils.hpp"
#include "set_utils.hpp"

#define BLACK 'B'
#define RED	'R'

namespace ft {

template <class T>
struct Node {

	T				value;
	Node*			parent;
	Node*			left;
	Node*			right;
	bool			color;

	Node() : value(0), parent(NULL), left(NULL), right(NULL), color(0) {}
	Node(const T& value) : value(value), parent(NULL), left(NULL), right(NULL), color(0) {}
	Node(const T& value, const Node* node) :  value(value), parent(node->parent), left(node->left), right(node->right), color(node->color) {}
    Node(const Node& copy) : value(copy.value), parent(copy.parent), left(copy.left), right(copy.right), color(copy.right) {}
	~Node() {}

	template<class U>
    Node<U> & operator=(Node<U> & rhs) {
		new (this) Node<U>(rhs);
        return (*this);}

	operator	Node<const T>() {
		return Node<const T>(
			reinterpret_cast<const T*>(value),
			reinterpret_cast<Node<const T>*>(parent),
			reinterpret_cast<Node<const T>*>(left),
			reinterpret_cast<Node<const T>*>(right),
			reinterpret_cast<const bool*>(color));}

};

template <class T, class Compare, class Allocator = std::allocator<Node<T> > >
class Tree {

public:
	typedef Node<T>													node_type;
	typedef Node<const T>											const_node_type;
	typedef Compare 												key_compare;
	typedef Allocator												allocator_type;	
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef Node<T>*												pointer;
	typedef Node<const T>*											const_pointer;

	class value_compare {
		friend class Tree;
	protected:
		Compare comp;
        value_compare	(Compare c): comp(c) {};
	public:
        typedef	bool 	result_type;
        typedef	T	first_argument_type;
        typedef T	second_argument_type;
		bool operator()(const T& x, const T& y) const { return comp(x, y);}
	};

	allocator_type	_alloc;
protected:
	const_pointer			_root;
	const_pointer	_nil;
	key_compare		_key_compare;
	value_compare	_value_compare;

public:
//Constructors && Destructors 
	Tree() :  _root(NULL), _nil(NULL), _key_compare(key_compare()), _value_compare(_key_compare) {}
	Tree(key_compare comp) : _root(NULL), _nil(NULL), _key_compare(comp), _value_compare(_key_compare) {}
	Tree(const T & rootValue, key_compare comp) : _root(NULL), _nil(NULL), _key_compare(comp), _value_compare(_key_compare) { createNode(rootValue); }
	Tree(const Tree & copy) : _root(copy._root), _nil(copy._nil), _key_compare(copy._key_compare), _value_compare(copy._value_compare) {*this = copy;}
	~Tree() { clear(); }

	operator	Tree<const T, key_compare>() {
		return Tree<const T, key_compare>(
			reinterpret_cast<Tree<const T, key_compare>*>(_root),
			reinterpret_cast<Tree<const T, key_compare>*>(_nil));}

//assignment operator
	Tree & operator=(Tree const & rhs) {
		clear();
		_root = rhs._root;
		_nil = rhs._nil;
		_key_compare = rhs._key_compare;
		_value_compare = rhs._value_compare;
		return (*this); }

	const_pointer	getRoot() const {return this->_root;}
	const_pointer	getNil() const {return this->_nil;}

//Determine if the tree is empty
bool	isEmpty(const_pointer node) const {return node == NULL;}
bool	isLeaf(const_pointer node) const {return node->left == NULL && node->right == NULL;}
size_t	size(const_pointer	node) const {
	if (!isEmpty(node))
		return 1 + size(node->left) + size(node->right);
	else return 0;}

//Create node
const_pointer	createNode(const T& value) {
    node_type	node(value);
    node.left = node.right = NULL;
   	pointer ptr = _alloc.allocate(1);
   	_alloc.construct(ptr, node);
	const_pointer	ptr_;
	ptr_ = reinterpret_cast<const_pointer>(ptr);
	if (!_root)
		_root = ptr_;
	else node.color = 'R';
    return (ptr_);}

//Insert
const_pointer	insert(const_pointer node, const T& value) {
	if (isEmpty(node))
		return createNode(value);
	if (_value_compare(value, node->value)) {
		node->left = insert(node->left, value);
		node->left->parent = node;}
	else if (!_value_compare(value, node->value)) {
		node->right = insert(node->right, value);
		node->right->parent = node;}
	node = fixInsert(node);
	return node;}

const_pointer	fixInsert(const_pointer node) {
	while (node->parent && node->parent->color == 'R') {
		if (node->parent == node->parent->parent->right) {
			const_pointer uncle = node->parent->parent->left;
			if (uncle->color == 'R') {
				uncle->color = 'B';
				node->parent->color = 'B';
				node->parent->parent->color = 'R';
				node = node->parent->parent;}
			else if (node == node->parent->left) {
				node = node->parent;
				node = leftRotate(node);}
			node->parent->color = 'B';
			node->parent->parent->color = 'R';}
		else {
			const_pointer uncle = node->parent->parent->right;
			if (uncle->color == 'R') {
				uncle->color = 'B';
				node->parent->color = 'B';
				node->parent->parent->color = 'R';
				node = node->parent->parent;}
			else if (node == node->parent->right) {
				node = node->parent;
				node = rightRotate(node);}
			node->parent->color = 'B';
			node->parent->parent->color = 'R';}}
	_root->color = 'B';
	return node;}

//display the tree
void	inorder(pointer	node) {
	if (node) {
		this->inorder(node->left);
		std::cout << node->value.first << " && " << node->value.second << std::endl;
		this->inorder(node->right);}}

const_pointer	find(const_pointer root, const T& value) const {
	if (root == NULL || value == root->value)
		return reinterpret_cast<const_pointer>(root);
	else if (_value_compare(value, root->value))
		return (find(root->left, value));
	else return (find(root->right, value));}

//maximum
const_pointer	maximum(const_pointer node) const {
	while (node && node->right)
		node = node->right;
	return reinterpret_cast<const_pointer>(node);}

//minimum
const_pointer	minimum(const_pointer node) const {
	while (node && node->left)
		node = node->left;
	return reinterpret_cast<const_pointer>(node);}

//LowerBound
const_pointer	lowerBound(const_pointer node, const T& k) const {
	while (node && node->right && _value_compare(node->value, k))
		node = node->right;
	if (k > maximum(_root)->value)
		return 0;
	return reinterpret_cast<const_pointer>(node);}

//UpperBound
const_pointer	upperBound(const_pointer node, const T& k) const {
	while (node && node->right && !(_value_compare(k, node->value)))
		node = node->right;
	if (k >= maximum(_root)->value)
		return 0;
	return reinterpret_cast<const_pointer>(node);}

//Delete node
const_pointer	deleteNode(const_pointer root, const T& value) {
	if (!root)
		return root;
	if (_value_compare(value, root->value))
		root->left = deleteNode(root->left, value);
	else if (_value_compare(root->value, value))
		root->right = deleteNode(root->right, value);
	else
	{
		if (isLeaf(root)) {
			_alloc.destroy(reinterpret_cast<pointer>(root));
			_alloc.deallocate(reinterpret_cast<pointer>(root), 1);
			if (root == _root)
				_root = _nil;
			return _nil;}
		else if (root->left == NULL) {
			const_pointer	tmp = root->right;
			tmp->parent = root->parent;
			if (root == _root)
				_root = tmp;
			_alloc.destroy(reinterpret_cast<pointer>(root));
			_alloc.deallocate(reinterpret_cast<pointer>(root), 1);
			root = _nil;
			return tmp;}
		else if (root->right == NULL) {
			const_pointer tmp = root->left;
			tmp->parent = root->parent;
			if (root == _root)
				_root = tmp;
			_alloc.destroy(reinterpret_cast<pointer>(root));
			_alloc.deallocate(reinterpret_cast<pointer>(root), 1);
			root = _nil;
			return tmp;}
		const_pointer	tmp = minimum(root->right);
		const_node_type	root_tmp(tmp->value, root);
		*root = root_tmp;
		root->right = deleteNode(root->right, tmp->value);}
		root = fixDelete(root);
		return root;}

const_pointer	fixDelete(const_pointer node) {
	while (node != _root && node->color == 'B') {
		if (node == node->parent->left) {
			const_pointer sibling = node->parent->right;
			if (sibling->color == 'R') {
				sibling->color = 'B';
				node->parent->color = 'R';
				leftRotate(node->parent);
				sibling = node->parent->right;}
			if (sibling->left->color == 'B' && sibling->right->color == 'B') {
				sibling->color = 'R';
				node = node->parent;}
			else if (sibling->right->color == 'B') {
				sibling->left->color = 'B';
				sibling->color = 'R';
				rightRotate(sibling);
				sibling = node->parent->right;}
			sibling->color = node->parent->right->color;
			node->parent->color = 'B';
			sibling->right->color = 'B';
			leftRotate(node->parent);
			node = _root;}
		else {
			const_pointer sibling = node->parent->left;
			if (sibling->color == 'R') {
				sibling->color = 'B';
				node->parent->color = 'R';
				rightRotate(node->parent);
				sibling = node->parent->left;}
			if (sibling->right->color == 'B' && sibling->left->color == 'B') {
				sibling->color = 'R';
				node = node->parent;}
			else if (sibling->left->color == 'B') {
				sibling->right->color = 'B';
				sibling->color = 'R';
				leftRotate(sibling);
				sibling = node->parent->left;}
			sibling->color = node->parent->left->color;
			node->parent->color = 'B';
			sibling->left->color = 'B';
			rightRotate(node->parent);
			node = _root;}}
	node->color = 'B';
	return node;}

const_pointer	leftRotate(const_pointer node) {
	const_pointer x = node->right;
	const_pointer y = x->left;
	x->left = node;
	node->right = y;
	node->parent = x;
	if (y != _nil)
		y->parent = node;
	return x;}

const_pointer	rightRotate(const_pointer node) {
	const_pointer x = node->left;
	const_pointer y = x->right;
	x->right = node;
	node->left = y;
	node->parent = x;
	if (y != _nil)
		y->parent = node;
	return x;}

void	clear() {
	while (_root != _nil) 
		_root = deleteNode(_root, _root->value);}

void	swap(Tree & x) {
	const_pointer	tmp_root = _root;
	const_pointer tmp_nil = _nil;
	key_compare	tmp_key = _key_compare;
	value_compare	tmp_value = _value_compare;
	_root = x._root;
	_nil = x._nil;
	_key_compare = x._key_compare;
	_value_compare = x._value_compare;
	x._root = tmp_root;
	x._nil = tmp_nil;
	x._key_compare = tmp_key;
	x._value_compare = tmp_value;}

class bi_iterator {

public:
	typedef std::bidirectional_iterator_tag						iterator_category;
	typedef Node<T>												value_type;
	typedef Node<const T>										const_value_type;
	typedef size_t												difference_type;
	typedef value_type*											pointer;
	typedef T*													TPointer;
	typedef Tree<T, Compare>									tree;
	typedef Tree<const T, Compare>								const_tree;
	typedef const_value_type*									const_pointer;
	typedef value_type&											reference;
	typedef T&													TRef;
	typedef const_tree *										const_iterator_type;

	bi_iterator() : _ptr(NULL), _parent(NULL) {}
	bi_iterator(const_pointer ptr) : _ptr(ptr), _parent(NULL) {}
	bi_iterator(const_pointer ptr, const_pointer parent) : _ptr(ptr), _parent(parent) {}
	const_pointer	get_ptr() const { return this->_ptr; }
	bi_iterator(const bi_iterator & it) : _ptr(it._ptr), _parent(it._parent) {}

	bi_iterator& 	operator=(bi_iterator const & rhs) {
		this->_ptr = rhs._ptr;
		this->_parent = rhs._parent;
		return (*this); }
	
	//successor
	const_pointer	successor(const_pointer node) const {
		if (node && node->right)
			return (_tree.minimum(node->right));
		const_pointer	y;
		y = node->parent;
		while (y != NULL && _tree._value_compare(y->value, node->value)) {
			node = y;
			y = y->parent;}
		return y;}

	//predecessor
	const_pointer	predecessor(const_pointer node) const {
		if (!node)
			return (node->parent);
		if (node && node->left)
			return (_tree.maximum(node->left));
		const_pointer	y;
		y = node->parent;
		while (y && node == y->left) {
			node = y;
			y = y->parent;}
		return y;}

	TRef			operator*() const { pointer ptr = reinterpret_cast<pointer>(_ptr); return ptr->value; }
	TPointer		operator->() const { return &(operator*()); }

	bi_iterator&	operator++() { _parent = _ptr; this->_ptr = successor(this->_ptr); return *this; };
	bi_iterator		operator++(int) { bi_iterator tmp = *this; ++(*this); return tmp; }
	bi_iterator&	operator--() { 
		if (!_ptr)
			_ptr = _parent;
		else 
			this->_ptr = predecessor(this->_ptr); 
		return *this; }
	bi_iterator		operator--(int) { bi_iterator tmp = *this; --(*this); return tmp; } 

	bool operator==(const bi_iterator& rhs) { return (this->get_ptr() == rhs.get_ptr()); }
	bool operator!=(const bi_iterator& rhs) { return (this->get_ptr() != rhs.get_ptr()); }

    operator typename const_tree::bi_iterator() {
        return (typename const_tree::bi_iterator(reinterpret_cast<const_pointer>(_ptr), reinterpret_cast<const_pointer>(_parent)));}	

	protected:
		const_pointer						_ptr;
		const_pointer						_parent;
		tree						_tree;
};

//Iterators
bi_iterator										begin() const { bi_iterator	it(minimum(getRoot()), _nil); return it;}
bi_iterator										end() const { bi_iterator	it(_nil, maximum(getRoot())); return it;}
set_reverse_iterator<bi_iterator>				rbegin() const { set_reverse_iterator<bi_iterator>	it(end()); return it;}
set_reverse_iterator<bi_iterator>				rend() const { set_reverse_iterator<bi_iterator>	it(begin()); return it;}

};

}

#endif
