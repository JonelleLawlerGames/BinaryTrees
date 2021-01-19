#ifndef LINKEDBINARYTREE_H
#define LINKEDBINARYTREE_H

// Forward references.
template <typename T, typename Iterator>class BinaryTree;
template <typename T>class BinaryTreeNode;
template <typename T>class Container;

template <typename T, typename Iterator>
class LinkedBinaryTree : public BinaryTree<T, Iterator> {
public:
	// LinkedBinaryTree specific member functions
	// Constructor          
	LinkedBinaryTree(T element);
	// Copy constructor
	LinkedBinaryTree(LinkedBinaryTree<T, Iterator> const& other) {
		copy(other);
	}
	// Destructor
	~LinkedBinaryTree() {
		destroy();
	}

	// Generic container functions
	virtual int size() const;
	virtual bool isEmpty() const;

	// Generic SimpleTree functions
	virtual Iterator root() const;
	virtual Iterator parent(Iterator& position) const;
	virtual bool isInternal(Iterator& position) const;
	virtual bool isExternal(Iterator& position) const;
	virtual bool isRoot(Iterator& position) const;
	virtual void swap(Iterator& first, Iterator& second);
	virtual void replace(Iterator& position, T element);

	// Depth functions 
	virtual int depth(Iterator position);
	virtual int depthNonRecursive(Iterator& position);

	// BinaryTree functions
	virtual Iterator& leftChild(Iterator& position) const;
	virtual Iterator& rightChild(Iterator& position) const;

	// Functions to return tree iterators
	Iterator& begin();
	Iterator& end();

	// Binary search tree function - inserts a new key
	Iterator insertItem(T key, Iterator iter, Iterator iterParent);
	// Binary search tree function - searches for a key
	Iterator treeSearch(T key, Iterator iter);

	// Minimum function 
	virtual Iterator treeMinimum(Iterator& position);

	// Height function
	virtual int height(Iterator position);

	// Delete function
	void deleteItem(Iterator position);


	

private:
	BinaryTreeNode<T>* m_root;     // Pointer to the root node
	int m_count;                    // Number of nodes in the tree

	void copy(LinkedBinaryTree<T, Iterator> const& other);
	void destroy();
};

template <typename T, typename Iterator>
LinkedBinaryTree<T, Iterator>::LinkedBinaryTree(T element) : m_count(1) {
	m_root = new BinaryTreeNode<T>(element, this, 0);
}

template <typename T, typename Iterator>
void LinkedBinaryTree<T, Iterator>::copy(LinkedBinaryTree<T, Iterator> const& other) {
	m_root = new BinaryTreeNode<T>(*(other.m_root));
	m_count = other.m_count;
}

template <typename T, typename Iterator>
void LinkedBinaryTree<T, Iterator>::destroy() {
	delete m_root;
}


template <typename T, typename Iterator>
int LinkedBinaryTree<T, Iterator>::size() const {
	return m_count;
}

template <typename T, typename Iterator>
bool LinkedBinaryTree<T, Iterator>::isEmpty() const {
	return (m_count == 0);
}

template <typename T, typename Iterator>
void LinkedBinaryTree<T, Iterator>::swap(Iterator& first, Iterator& second) {
	T temp = (*first);
	(*first) = (*second);
	(*second) = temp;
}

template <typename T, typename Iterator>
void LinkedBinaryTree<T, Iterator>::replace(Iterator& position, T element) {
	(*position) = element;
}


template <typename T, typename Iterator>
Iterator LinkedBinaryTree<T, Iterator>::root() const {
	return Iterator(m_root);
}

template <typename T, typename Iterator>
Iterator LinkedBinaryTree<T, Iterator>::parent(Iterator& position) const {
	return position.node()->parent();
}

template <typename T, typename Iterator>
bool LinkedBinaryTree<T, Iterator>::isInternal(Iterator& position) const {
	return (position.node()->leftChild() != 0 || position.node()->rightChild() != 0);
}

template <typename T, typename Iterator>
bool LinkedBinaryTree<T, Iterator>::isExternal(Iterator& position) const {
	return (position.node()->leftChild() == 0 && position.node()->rightChild() == 0);
}

template <typename T, typename Iterator>
bool LinkedBinaryTree<T, Iterator>::isRoot(Iterator& position) const {
	return (position == m_root);
}

template <typename T, typename Iterator>
Iterator& LinkedBinaryTree<T, Iterator>::leftChild(Iterator& position) const {
	Iterator& iter = position;
	if (position.node() != 0) { // this checks if there is a pointer NOT if it is the root 
		iter = position.node()->leftChild();
	}
	return iter;
}

// DEPTH FUNCTION 


template<typename T, typename Iterator>
int LinkedBinaryTree<T, Iterator>::depth(Iterator position)
{

	// if this is the root node
	if (isRoot(position))
	{
		return 0;
	}

	else
	{
		position.up(); // moves one position up from node (parent) 
		return 1 + (this->depth(position)); // this means the function is recursive

	}

	// THIS FUNCTION GOES UP ONE FROM POSITION (PARENT) and calls itself until it hits 0. once it hits 0 it calls the return one last time and will add 1 to depth. 
}

template<typename T, typename Iterator>
inline int LinkedBinaryTree<T, Iterator>::depthNonRecursive(Iterator& position)
{
	int depth = 0;
	while (isRoot(position) != true)
	{
		position.up();
		depth++;
	}

	return depth;
}

template <typename T, typename Iterator>
Iterator& LinkedBinaryTree<T, Iterator>::rightChild(Iterator& position) const {
	Iterator& iter = position;
	if (position.node() != 0) {
		iter = position.node()->rightChild();
	}
	return iter;
}

template <typename T, typename Iterator>
Iterator LinkedBinaryTree<T, Iterator>::treeSearch(T key, Iterator iter) {
	/*if n is an external node and key(n) <> k then
  return NULL KEY
if k == key(n) then
  return n
else if k < key(n) then
  return treeSearch(k, T.leftChild(n))
else
  { we know that k > key(n) }
  return treeSearch(k, T.rightChild(n))*/

if (iter.node() == 0 || isExternal(iter) && (*iter) != key) {
	return Iterator(0);
}
if (key == (*iter)) {
	return iter;
}
else if (key < (*iter)) {
	return treeSearch(key, leftChild(iter));
}
else {
	return treeSearch(key, rightChild(iter));
}
}

// MINIMUM FUNCTION 
template<typename T, typename Iterator>
inline Iterator LinkedBinaryTree<T, Iterator>::treeMinimum(Iterator& position)
{


	while (position.downLeft() == true)
	{
		position.downLeft();
	}


	return position;

}






template<typename T, typename Iterator>
inline int LinkedBinaryTree<T, Iterator>::height(Iterator position)
{


	if (isInternal(position))
	{

		int leftSide = 0;
		int rightSide = 0;

		if (position.node()->leftChild() != nullptr)
		{
			leftSide = height(position.node()->leftChild());
		}


		if (position.node()->rightChild() != nullptr)
		{
			rightSide = height(position.node()->rightChild());
		}


		if (leftSide > rightSide)
		{
			return leftSide + 1;
		}
		else
		{
			return rightSide + 1;
		}

	}
	return 0;
}

template<typename T, typename Iterator>
inline void LinkedBinaryTree<T, Iterator>::deleteItem(Iterator position)
{
	// DELETE LEAF NODE 
	if (isExternal(position))
	{
		// Compare the node to its parent. 
		// If its bigger than its parent, it is the right child of it. Delete the parent's right child. 
		if (parent(position).node()->element() > position.node()->element())
		{
			parent(position).node()->setLeftChild(0);
		}
		// If its smaller than its parent, it is the left child of it. Delete the parent's left child. 
		if (parent(position).node()->element() < position.node()->element())
		{
			parent(position).node()->setRightChild(0);
		}

	}
	// DELETE AN INTERNAL NODE WITH ONE CHILD NODE 
	if (isInternal(position))
	{
		// check if there is a left child  only
		if (position.node()->leftChild() != nullptr && position.node()->rightChild() == nullptr)
		{
			// set your parent's left child to be your left child 
			parent(position).node()->setLeftChild(leftChild(position).node());

			// set your child's parent to  be your parent
			leftChild(position).node()->setParent(parent(position).node());
		}


		// check if there is a right child  only 
		else if (position.node()->rightChild() != nullptr && position.node()->leftChild() == nullptr)
		{
			// set your parent's right child to be your left child 
			parent(position).node()->setRightChild(rightChild(position).node());

			// set your child's parent to  be your parent
			rightChild(position).node()->setParent(parent(position).node());
		}


		// TWO CHILD NODES
		else if (position.node()->rightChild() != nullptr && position.node()->leftChild() != nullptr)
		{
			// set your parent your right child's left child 
			
			// replace the position with the largest element on the left subtree or the 
			// smallest element on the right subtree
			
			Iterator nodeToDelete = position;

			nodeToDelete.downRight();

			while (isInternal(nodeToDelete))
			{
				nodeToDelete.downLeft();
			}


	
			// replace node with left most
			position.node()->setElement(nodeToDelete.node()->element());

//			std::cout << position.node()->element() << std::endl;

			deleteItem(nodeToDelete);
		}

	}	

}
	


template <typename T, typename Iterator>
Iterator LinkedBinaryTree<T, Iterator>::insertItem(T key, Iterator iter,
	Iterator iterParent) {
	BinaryTreeNode<T>* node = iter.node();
	if (node == 0) {
		node = new BinaryTreeNode<T>(key, this);
		node->setLeftChild(0);
		node->setRightChild(0);
		node->setParent(iterParent.node());
		m_count++;
	}
	else if (key < node->element()) {
		Iterator tempIter = insertItem(key, node->leftChild(), iter);
		node->setLeftChild(tempIter.node());
	}
	else if (key > node->element()) {
		Iterator tempIter = insertItem(key, node->rightChild(), iter);
		node->setRightChild(tempIter.node());
	}

	return Iterator(node);
}

template <typename T, typename Iterator>
Iterator& LinkedBinaryTree<T, Iterator>::begin() {
	return Iterator(m_root);
}

template <typename T, typename Iterator>
Iterator& LinkedBinaryTree<T, Iterator>::end() {
	return m_root->parent();
}




#include "BinaryTree.h"
#include "BinaryTreeNode.h"
#endif