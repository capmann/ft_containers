#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <memory>
#include <string>
#include <iostream>
#include "map_utils.hpp"

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

    Node & operator=(Node & rhs) {
		new (this) Node(rhs);
        return (*this);}

	operator	Node<const T>() {
		return Node<const T>(
			reinterpret_cast<const T*>(value),
			reinterpret_cast<Node<const T>*>(parent),
			reinterpret_cast<Node<const T>*>(left),
			reinterpret_cast<Node<const T>*>(right),
			reinterpret_cast<const bool*>(color));}

};

template <class pair, class Compare, class Allocator = std::allocator<Node<pair> > >
class Tree {

public:
	typedef typename pair::first_type								Key;
	typedef typename pair::second_type								value;	
	typedef Node<pair>												node_type;
	typedef Compare 												key_compare;
	typedef Allocator												allocator_type;	
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef Node<pair>*												pointer;
	typedef Node<const pair>*										const_pointer;

	class value_compare {
	protected:
		Compare comp;
	public:
        value_compare	(Compare c): comp(c) {};
        typedef	bool 	result_type;
        typedef	pair	first_argument_type;
        typedef pair	second_argument_type;
		typedef Key		key_type;
		bool operator()(const pair& x, const pair& y) const { return comp(x.first, y.first);}
		bool operator()(const Key& x, const Key& y) const { return comp(x, y);}
	};

	allocator_type	_alloc;
protected:
	pointer			_root;
	pointer			_nil;
	key_compare		_key_compare;
	value_compare	_value_compare;

public:
//Constructors && Destructors 
	Tree() :  _root(NULL), _nil(NULL), _key_compare(key_compare()), _value_compare(_key_compare) {}
	Tree(key_compare comp) : _root(NULL), _nil(NULL), _key_compare(comp), _value_compare(_key_compare) {}
	Tree(const value & rootValue, key_compare comp) : _root(NULL), _nil(NULL), _key_compare(comp), _value_compare(_key_compare) { createNode(rootValue); }
	Tree(const Tree & copy) : _root(copy._root), _nil(copy._nil), _key_compare(copy._key_compare), _value_compare(copy._value_compare) {*this = copy;}
	~Tree() { clear(); }

	operator	Tree<const pair, key_compare>() {
		return Tree<const pair, key_compare>(
			reinterpret_cast<Tree<const pair, key_compare>*>(_root),
			reinterpret_cast<Tree<const pair, key_compare>*>(_nil));}

//assignment operator
	Tree & operator=(Tree const & rhs) {
		clear();
		_root = rhs._root;
		_nil = rhs._nil;
		_key_compare = rhs._key_compare;
		_value_compare = rhs._value_compare;
		return (*this); }

	pointer	getRoot() const {return this->_root;}
	pointer	getNil() const {return this->_nil;}

//Determine if the tree is empty
bool	isEmpty(pointer node) const {return node == NULL;}
bool	isLeaf(pointer node) const {return node->left == NULL && node->right == NULL;}
size_t	size(pointer	node) const {
	if (!isEmpty(node))
		return 1 + size(node->left) + size(node->right);
	else return 0;}

//Create node
pointer	createNode(const pair& value) {
    node_type	node(value);
    node.left = node.right = NULL;
    pointer ptr = _alloc.allocate(1);
   	_alloc.construct(ptr, node);
	if (!_root)
		_root = ptr;
	else node.color = 'R';
    return (ptr);}

//Insert
pointer	insert(pointer node, const pair& value) {
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

pointer	fixInsert(pointer node) {
	while (node->parent && node->parent->color == 'R') {
		if (node->parent == node->parent->parent->right) {
			pointer uncle = node->parent->parent->left;
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
			pointer uncle = node->parent->parent->right;
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

//search inside the tree
pointer	find(pointer root, const pair& value) {
	if (root == NULL || value == root->value)
		return root;
	else if (_value_compare(value, root->value))
		return (find(root->left, value));
	else return (find(root->right, value));}

const_pointer	find(pointer root, const pair& value) const {
	if (root == NULL || value == root->value)
		return reinterpret_cast<const_pointer>(root);
	else if (_value_compare(value, root->value))
		return (find(root->left, value));
	else return (find(root->right, value));}

//search inside the tree only with the key
pointer	find_key(pointer node, Key key) {
	if (!node || key == node->value.first)
		return node;
	else if (_value_compare(key, node->value.first))
		return (find_key(node->left, key));
	else return (find_key(node->right, key));}

//search inside the tree only with the key
const_pointer	find_key(pointer node, Key key) const {
	if (!node || key == node->value.first)
		return reinterpret_cast<const_pointer>(node);
	else if (_value_compare(key, node->value.first))
		return (find_key(node->left, key));
	else return (find_key(node->right, key));}

//maximum
pointer	maximum(pointer node) const {
	while (node && node->right)
		node = node->right;
	return node;}

//minimum
pointer	minimum(pointer node) const {
	while (node && node->left)
		node = node->left;
	return node;}

//LowerBound
pointer	lowerBound(pointer node, Key k) {
	while (node && node->right && _value_compare(node->value.first, k))
		node = node->right;
	if (k > maximum(_root)->value.first)
		return _nil;
	return node;}

//UpperBound
pointer	upperBound(pointer node, Key k) {
	while (node && node->right && !(_value_compare(k, node->value.first)))
		node = node->right;
	if (k >= maximum(_root)->value.first)
		return _nil;
	return node;}

//LowerBound
const_pointer	lowerBound(pointer node, Key k) const {
	while (node && node->right && _value_compare(node->value.first, k))
		node = node->right;
	if (k > maximum(_root)->value.first)
		return 0;
	return reinterpret_cast<const_pointer>(node);}

//UpperBound
const_pointer	upperBound(pointer node, Key k) const {
	while (node && node->right && !(_value_compare(k, node->value.first)))
		node = node->right;
	if (k >= maximum(_root)->value.first)
		return 0;
	return reinterpret_cast<const_pointer>(node);}

//LowerBound
pointer	lowerBound(pointer node, pair k) {
	while (node && node->right && _value_compare(node->value, k))
		node = node->right;
	if (k > maximum(_root)->value)
		return _nil;
	return node;}

//UpperBound
pointer	upperBound(pointer node, pair k) {
	while (node && node->right && !(_value_compare(k, node->value)))
		node = node->right;
	if (k >= maximum(_root)->value)
		return _nil;
	return node;}

//LowerBound
const_pointer	lowerBound(pointer node, pair k) const {
	while (node && node->right && _value_compare(node->value, k))
		node = node->right;
	if (k > maximum(_root)->value)
		return 0;
	return reinterpret_cast<const_pointer>(node);}

//UpperBound
const_pointer	upperBound(pointer node, pair k) const {
	while (node && node->right && !(_value_compare(k, node->value)))
		node = node->right;
	if (k >= maximum(_root)->value)
		return 0;
	return reinterpret_cast<const_pointer>(node);}

//Delete node
pointer	deleteNode(pointer root, pair& value) {
	if (!root)
		return root;
	if (_value_compare(value, root->value))
		root->left = deleteNode(root->left, value);
	else if (_value_compare(root->value, value))
		root->right = deleteNode(root->right, value);
	else
	{
		if (isLeaf(root)) {
			_alloc.destroy(root);
			_alloc.deallocate(root, 1);
			if (root == _root)
				_root = _nil;
			return _nil;}
		else if (root->left == NULL) {
			pointer	tmp = root->right;
			tmp->parent = root->parent;
			if (root == _root)
				_root = tmp;
			_alloc.destroy(root);
			_alloc.deallocate(root, 1);
			root = _nil;
			return tmp;}
		else if (root->right == NULL) {
			pointer tmp = root->left;
			tmp->parent = root->parent;
			if (root == _root)
				_root = tmp;
			_alloc.destroy(root);
			_alloc.deallocate(root, 1);
			root = _nil;
			return tmp;}
		pointer	tmp = minimum(root->right);
		node_type	root_tmp(tmp->value, root);
		*root = root_tmp;
		root->right = deleteNode(root->right, tmp->value);}
		root = fixDelete(root);
		return root;}

pointer	fixDelete(pointer node) {
	while (node != _root && node->color == 'B') {
		if (node == node->parent->left) {
			pointer sibling = node->parent->right;
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
			pointer sibling = node->parent->left;
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

pointer	leftRotate(pointer node) {
	pointer x = node->right;
	pointer y = x->left;
	x->left = node;
	node->right = y;
	node->parent = x;
	if (y != _nil)
		y->parent = node;
	return x;}

pointer	rightRotate(pointer node) {
	pointer x = node->left;
	pointer y = x->right;
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
	pointer	tmp_root = _root;
	pointer tmp_nil = _nil;
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
	typedef std::bidirectional_iterator_tag							iterator_category;
	typedef Node<pair>												value_type;
	typedef Node<const pair>										const_value_type;
	typedef size_t													difference_type;
	typedef value_type*												pointer;
	typedef pair*													pairPointer;
	typedef Tree<pair, Compare>										tree;
	typedef Tree<const pair, Compare>								const_tree;
	typedef const_value_type*										const_pointer;
	typedef value_type&												reference;
	typedef pair&													pairRef;
	typedef const_tree *											const_iterator_type;

	bi_iterator() : _ptr(NULL), _parent(NULL) {}
	bi_iterator(pointer ptr) : _ptr(ptr), _parent(NULL) {}
	bi_iterator(pointer ptr, pointer parent) : _ptr(ptr), _parent(parent) {}
	pointer	get_ptr() const { return this->_ptr; }
	bi_iterator(const bi_iterator & it) : _ptr(it._ptr), _parent(it._parent) {}
	bi_iterator& 	operator=(bi_iterator const & rhs) {
		this->_ptr = rhs._ptr;
		this->_parent = rhs._parent;
		return (*this); }

	//successor
	pointer	successor(pointer node) const {
		if (node && node->right)
			return (_tree.minimum(node->right));
		pointer	y;
		y = node->parent;
		while (y != NULL && _tree._value_compare(y->value, node->value)) {
			node = y;
			y = y->parent;}
		return y;}

	//predecessor
	pointer	predecessor(pointer node) const {
		if (!node)
			return (node->parent);
		if (node && node->left)
			return (_tree.maximum(node->left));
		pointer	y;
		y = node->parent;
		while (y && node == y->left) {
			node = y;
			y = y->parent;}
		return y;}

	pairRef			operator*() const { return this->_ptr->value; }
	pairPointer		operator->() const { return &(operator*()); }

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
		pointer						_ptr;
		pointer						_parent;
		tree						_tree;
};

//Iterators
bi_iterator										begin() const { bi_iterator	it(minimum(getRoot()), _nil); return it;}
bi_iterator										end() const { bi_iterator	it(_nil, maximum(getRoot())); return it;}
bi_reverse_iterator<bi_iterator>				rbegin() const { bi_reverse_iterator<bi_iterator>	it(end()); return it;}
bi_reverse_iterator<bi_iterator>				rend() const { bi_reverse_iterator<bi_iterator>	it(begin()); return it;}

};

}

#endif
