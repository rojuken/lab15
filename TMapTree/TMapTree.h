#ifndef TMAPTREE_H
#define TMAPTREE_H

#include <fstream>
#include <iostream>
#include <queue>
#include "TNodeTree.h"
#include "TMapTreeIterator.h"

template <class TK, class TV>
class TMapTree
{
protected:
	TNodeTree<TK, TV>* root;
	int count;

public:
	TMapTree();
	TMapTree(const TMapTree<TK,TV>& p);
	virtual ~TMapTree();

	virtual TV& operator[](TK i);

	virtual TV Find(TK k);
	virtual void Delete(TK k);
	virtual void Add(TK k, TV v);
	virtual int GetCount();

	typedef TMapTreeIterator<TK, TV> iterator;
	friend class TMapTreeIterator<TK, TV>;
	TMapTreeIterator<TK, TV> Begin();

};

template<class TK, class TV>
inline TMapTree<TK, TV>::TMapTree()
{
	this->count = 0;
	this->root = NULL;
}

template<class TK, class TV>
inline TMapTree<TK, TV>::TMapTree(const TMapTree<TK, TV>& p)
{
	count = p.count;
	if (p.root!= NULL)
	{
		root = new TNodeTree<TK, TV>(*(p.root));
		std::queue<TNodeTree<TK, TV>*> q;
		q.push(p.root);

		std::queue<TNodeTree<TK, TV>*> q2;
		q2.push(root);

		while (!q.empty())
		{
			TNodeTree<TK, TV>* cur1 = q.front();
			TNodeTree<TK, TV>* cur2 = q2.front();

			q.pop();
			q2.pop();

			if (cur1->l != NULL)
			{
				TNodeTree<TK, TV>* t = new TNodeTree<TK, TV>(*(cur1->l));
				cur2->l = t;

				q.push(cur1->l);
				q2.push(cur2->l);
			}
			if (cur1->r != NULL)
			{
				TNodeTree<TK, TV>* t = new TNodeTree<TK, TV>(*(cur1->r));
				cur2->r = t;

				q.push(cur1->r);
				q2.push(cur2->r);
			}
		}
	}
}

template<class TK, class TV>
inline TMapTree<TK, TV>::~TMapTree()
{
	if (this->root != NULL)
	{
		std::queue<TNodeTree<TK, TV>*> q;
		q.push(this->root);
		while (!q.empty())
		{
			if (q.front()->l != NULL)
				q.push(q.front()->l);
			if(q.front()->r!=NULL)
				q.push(q.front()->r);
			delete q.front();
			q.pop();
		}
	}
}

template<class TK, class TV>
inline TV &TMapTree<TK, TV>::operator[](TK i)
{
	TNodeTree<TK, TV>* res(root);
	while (res)
	{
		if (res->GetKey() == i)
			return res->val;
		if (i < res->GetKey() && res->l)
			res = res->l;
		else res = res->r;
	}

	TNodeTree<TK, TV>* t = new TNodeTree<TK, TV>(i, 0);
	if (i < res->GetKey())
		res->l = t;
	else
		res->r = t;
}

template<class TK, class TV>
inline TV TMapTree<TK, TV>::Find(TK k)
{
	TNodeTree<TK, TV>* res(this->root);
	while (res)
	{
		if (res->GetKey() == k)
			return res->GetVal();
		if (k < res->GetKey())
			res = res->l;
		else
			res = res->r;
	}
	throw new std::exception;
}

template<class TK, class TV>
inline void TMapTree<TK, TV>::Delete(TK k)
{
	TNodeTree<TK, TV>* res(this->root);
	TNodeTree<TK, TV>* prev = NULL;
	bool left = false;
	while (true)
	{
		if (res->GetKey() == k)
		{
			if (res == root)
			{
				this->~TMapTree();
				return;
			}
			if (!res->l && !res->r)
			{
				if (left)
					prev->l = NULL;
				else
					prev->r = NULL;
				delete res;
				return;
			}
			if (res->l && res->r)
			{
				TNodeTree<TK, TV>* left = res->l;
				TNodeTree<TK, TV>* right = res->r;
				while (right->l)
					right = right->l;
				right->l = left;
				if (left)
					prev->l = res->r;
				else
					prev->r = res->r;
				delete res;
				return;
			}
			if (res->l || res->r)
			{
				if (res->l)
				{
					if (left)
						prev->l = res->l;
					else
						prev->r = res->l;
				}
				else
				{
					if (left)
						prev->l = res->r;
					else
						prev->r = res->r;
				}
				return;
			}
			throw new std::exception;
		}
		prev = res;
		if (k < res->GetKey() && res->l)
		{
			res = res->l;
			left = true;
		}
		else
		{
			res = res->r;
			left = false;
		}
	}
	throw new std::exception;
}

template<class TK, class TV>
inline void TMapTree<TK, TV>::Add(TK k, TV v)
{
	if (this->root == NULL)
	{
		root = new TNodeTree<TK, TV>(k, v);
		count++;
		return;
	}

	TNodeTree<TK, TV>* cur = root;

	while (true)
	{
		if (cur->GetKey() == k)
			return;
		if (k > cur->GetKey())
		{
			if (cur->r == NULL)
			{
				cur->r = new TNodeTree<TK, TV>(k, v);
				count++;
				return;
			}
			else
				cur = cur->r;
		}
		else if (k < cur->GetKey())
		{
			if (cur->l == NULL)
			{
				cur->l = new TNodeTree<TK, TV>(k, v);
				count++;
				return;
			}
			else
				cur = cur->l;
		}
	}
}

template<class TK, class TV>
inline int TMapTree<TK, TV>::GetCount()
{
	return this->count;
}

template<class TK, class TV>
inline TMapTreeIterator<TK, TV> TMapTree<TK, TV>::Begin()
{
	return TMapTree::iterator(*this);
}

#endif