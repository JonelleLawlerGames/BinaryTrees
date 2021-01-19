#ifndef SIMPLETREE_H
#define SIMPLETREE_H

// Forward references.
template <typename T> class Container;

template <typename T, typename Iterator>
class SimpleTree : public Container<T> {
public:
	virtual Iterator root() const = 0;
	virtual Iterator parent(Iterator& position) const = 0;
	virtual bool isInternal(Iterator& position) const = 0;
	virtual bool isExternal(Iterator& position) const = 0;
	virtual bool isRoot(Iterator& position) const = 0;
	virtual void swap(Iterator& first, Iterator& second) = 0;
	virtual void replace(Iterator& position, T element) = 0;


	// VIRTUAL DEPTH FUNCTION (PART 1 OF LAB)
	virtual int depth(Iterator position) = 0;

	virtual int depthNonRecursive(Iterator& position) = 0;


	// minimum
	virtual Iterator treeMinimum(Iterator& position) = 0;

	// Height 
	virtual int height(Iterator position) = 0; 


};

#include "Container.h"
#endif