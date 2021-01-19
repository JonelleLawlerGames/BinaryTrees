#include "LinkedBinaryTree.h"
#include "BinaryTreeIterator.h"

#include <iostream>
#include <stack>

// Jonelle Lawler 16/01/2020

// TO DO 
// 1) Write a global function in the same source file as main to perform an preorder traversal on a binary tree. DONE 
// 2) Write a non-recursive version of the above function

template <typename T>
void binaryPreorder(BinaryTreeNode<T>* node)
{

	std::cout << node->element() << std::endl;

	if (node->leftChild() != nullptr) // check if element has left child 
	{
		binaryPreorder(node->leftChild().node()); // function calls itself 


		if (node->rightChild() != nullptr) // then check the right 
		{
			binaryPreorder(node->rightChild().node()); // function calls itself 

		}
	}

	else if (node->leftChild() == nullptr)
	{

		if (node->rightChild() != nullptr) // then check the right 
		{
			binaryPreorder(node->rightChild().node()); // function calls itself 

		}
	}

}

template <typename T>
void binaryInorder(BinaryTreeNode<T>* node)
{
	std::stack<BinaryTreeNode<T>*> theStack;

	// node->element = current
	while (node != nullptr || theStack.empty() == false)
	{
		// check the current isn't null
		while (node != nullptr)
		{
			theStack.push(node); // push current
			node = node->leftChild().node(); // go to the left 
		}

		// then current = null 
		node = theStack.top();
		theStack.pop(); // delete top

		std::cout << node->element() << std::endl; // print left

		node = node->rightChild().node(); // go right
	}

}

int main() {


	// nodes
	LinkedBinaryTree<int, BinaryTreeIterator<int>> myTree(58); // 10 is the root
	BinaryTreeIterator<int> iter = myTree.root();
	BinaryTreeIterator<int> parentOfIter = myTree.parent(iter);

	// INSERT ITEMS INTO TREE
	myTree.insertItem(31, iter, parentOfIter);
	myTree.insertItem(90, iter, parentOfIter);
	myTree.insertItem(25, iter, parentOfIter);
	myTree.insertItem(42, iter, parentOfIter);
	myTree.insertItem(62, iter, parentOfIter);
	myTree.insertItem(95, iter, parentOfIter);
	myTree.insertItem(12, iter, parentOfIter);
	myTree.insertItem(27, iter, parentOfIter);
	myTree.insertItem(36, iter, parentOfIter);
	myTree.insertItem(43, iter, parentOfIter);
	myTree.insertItem(75, iter, parentOfIter);

	// Reset the tree iterator to the root.
	iter = myTree.root();

	//// OUTPUT THE CONTENTS OF THE TREE BEFORE AN ITEM HAS BEEN DELETED 
	//std::cout << "Tree before item deleted: " << std::endl;
	//binaryInorder(myTree.root().node());

	iter.downLeft();

	// DELETE ITEM
	myTree.deleteItem(iter);

	// SHOW NEW TREE
	std::cout << "Tree after node deleted: " << std::endl;
	binaryInorder(myTree.root().node());

	system("PAUSE");
}

