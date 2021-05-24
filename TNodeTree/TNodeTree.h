#ifndef TNODETREE_H
#define TNODETREE_H

#include "TNode.h"
#include "TMapTreeIterator.h"

template<class TK, class TV>
class TNodeTree : public TNode<TK, TV>
{
public:
	TNodeTree* l;
	TNodeTree* r;

	TNodeTree(TK k = 0, TV v = 0);
	TNodeTree(const TNodeTree& p);

	friend class TMapTreeIterator<TK, TV>;
};

template<class TK, class TV>
inline TNodeTree<TK, TV>::TNodeTree(TK k, TV v) :TNode<TK,TV>::TNode(k,v)
{
	this->l = NULL;
	this->r = NULL;
}

template<class TK, class TV>
inline TNodeTree<TK, TV>::TNodeTree(const TNodeTree& p) :TNode<TK, TV>::TNode(p)
{
	this->l = NULL;
	this->r = NULL;
}

#endif

