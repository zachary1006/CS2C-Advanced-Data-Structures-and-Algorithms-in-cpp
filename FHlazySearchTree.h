/*
Name: Zachary Simon
Class: CS 2C
Due Date: 10/24/2016
Instructor: Dave Harden
Name of File: FHlazySearchTree.h


This file implements a binary search tree that uses lazy deletion, where 
nodes are only marked as deleted, rather than actually removed. If necessary, 
the nodes can be removed by the collectGarbage() method. Printing of the tree 
is allowed through the traverse() function, which requires a functor to 
operate correctly. The tree also contains methods to find the currently 
enabled minimum, maximum, height, as well as insertion, and soft and hard
deletion methods. 


void collectGarbage();
This is the public method of a pair designed to permanently remove all the nodes 
that have been marked as deleted. This function calls its private counterpart 
(named below), protecting the private data from the client. 
Precondition: must be called on a valid tree. May be called on an empty tree, 
    or a tree with no "deleted" nodes, with no negative effects. 
Postcondition: all nodes marked as "deleted" are permanently removed from the 
    tree. 


void collectGarbage(FHs_treeNode<Comparable> * &root);
This is the private method of a pair designed to permanently remove all nodes 
that have been marked as deleted. This is the private function called by its 
public counterpart (above), and this method actually manipulates the data in 
the tree. It relies on the removeHard() method to do the work for it. It 
traverses the entire tree, checking each node for deletion, and removing 
it if it is marked as "deleted." 
Precondition: must be called on a valid tree. May be called on an empty tree, 
    or a tree with no "deleted" nodes, with no negative effects. 
Postcondition: all nodes marked as "deleted" are permanetnly removed from the 
    tree. 


int sizeHard() const { return mSizeHard; }
sizeHard returns the total number of nodes in the tree, both deleted and undeleted. 
Compare with size(), which returns the number of undeleted nodes only. 
Precondition: must be called on a valid tree. An empty tree's mSizeHard 
    variable is initialized to 0. 
Postcondition: returns the integer value of mSizeHard


FHs_treeNode<Comparable> *findMinHard(FHs_treeNode<Comparable> *root) const;
This method is necessary to perform garbage collection on nodes marked as "deleted." 
Helps removeHard() (below) perform garbage collection. When called, this method 
returns the minimum node in the tree, deleted or undeleted. 
Precondition: must be called on a valid tree or subtree
Postcondition: Lowest node in the given subtree, deleted or not, is returned. 
    If the node is NULL, NULL is returned. (This is handled by removeHard(), below.) 


bool removeHard(FHs_treeNode<Comparable> * &root, const Comparable &x);
removeHard() is an integral helper method for collectGarbage(). If a node has 
been marked as "deleted," collectGarbage() calls removeHard() to permanently 
remove it. This method finds the node to be deleted, and performs rotations with 
the nodes below it to maintaint tree integrity, if necessary, before deleting 
the appropriate node. 
Precondition: A valid subtree and existing root in the subtree must be passed in. 
Postcondition: returns true if the node was found and successfully removed; false 
    otherwise. 


*/

// File FHsearch_tree.h
// Template definitions for FHsearchTrees, which are general trees
#ifndef FHSEARCHTREE_H
#define FHSEARCHTREE_H

// ---------------------- FHs_treeNode Prototype --------------------------
template <class Comparable>
class FHs_treeNode
{
public:
    FHs_treeNode(const Comparable & d = Comparable(),
        FHs_treeNode *lt = NULL,
        FHs_treeNode *rt = NULL, 
        bool isDeleted = false)
        : lftChild(lt), rtChild(rt), data(d), deleted(isDeleted)
    { }

    FHs_treeNode *lftChild, *rtChild;
    Comparable data;
    bool deleted; 

    // for use only with AVL Trees
    virtual int getHeight() const { return 0; }
    virtual bool setHeight(int height) { return true; }
};

// ---------------------- FHsearch_tree Prototype --------------------------
template <class Comparable>
class FHsearch_tree
{
protected:
    int mSize, mSizeHard;
    FHs_treeNode<Comparable> *mRoot;

public:
    FHsearch_tree() { mSize = 0;; mSizeHard = 0; mRoot = NULL; }
    FHsearch_tree(const FHsearch_tree &rhs)
    {
        mRoot = NULL; mSize = 0; mSizeHard = 0; *this = rhs;
    }
    ~FHsearch_tree() { clear(); }

    const Comparable &findMin() const;
    const Comparable &findMax() const;
    const Comparable &find(const Comparable &x) const;

    bool empty() const { return (mSize == 0); }
    int size() const { return mSize; }
    int sizeHard() const { return mSizeHard; }
    void clear() { makeEmpty(mRoot); }
    const FHsearch_tree & operator=(const FHsearch_tree &rhs);

    bool insert(const Comparable &x);
    bool remove(const Comparable &x);
    bool contains(const Comparable &x) const { return find(mRoot, x) != NULL; }
    void collectGarbage(); 

    template <class Processor>
    void traverse(Processor func) const { traverse(mRoot, func); }
    int showHeight() const { return findHeight(mRoot); }

protected:
    FHs_treeNode<Comparable> *clone(FHs_treeNode<Comparable> *root) const;
    FHs_treeNode<Comparable> *findMin(FHs_treeNode<Comparable> *root) const;
    FHs_treeNode<Comparable> *findMinHard(FHs_treeNode<Comparable> *root) const; 
    FHs_treeNode<Comparable> *findMax(FHs_treeNode<Comparable> *root) const;
    FHs_treeNode<Comparable> *find(FHs_treeNode<Comparable> *root,
        const Comparable &x) const;
    bool insert(FHs_treeNode<Comparable> * &root,
        const Comparable &x);
    bool remove(FHs_treeNode<Comparable> * &root, const Comparable &x);
    bool removeHard(FHs_treeNode<Comparable> * &root, const Comparable &x);
    void collectGarbage(FHs_treeNode<Comparable> * &root);
    void makeEmpty(FHs_treeNode<Comparable> * &subtreeToDelete);
    template <class Processor>
    void traverse(FHs_treeNode<Comparable> *treeNode,
        Processor func, int level = -1) const;
    int findHeight(FHs_treeNode<Comparable> *treeNode, int height = -1) const;

public:
    // for exception throwing
    class EmptyTreeException {};
    class NotFoundException {};
};

// FHsearch_tree public method definitions -----------------------------
template <class Comparable>
const Comparable & FHsearch_tree<Comparable>::findMin() const
{
    if (mRoot == NULL || mSize == 0)
        throw EmptyTreeException();
    return findMin(mRoot)->data;
}

template <class Comparable>
const Comparable & FHsearch_tree<Comparable>::findMax() const
{
    if (mRoot == NULL || mSize == 0)
    {
        throw EmptyTreeException();
    }
    return findMax(mRoot)->data;
}

template <class Comparable>
const Comparable &FHsearch_tree<Comparable>::find(
    const Comparable &x) const
{
    FHs_treeNode<Comparable> *resultNode;

    resultNode = find(mRoot, x);
    if (resultNode == NULL || resultNode->deleted)
        throw NotFoundException();
    return resultNode->data;
}


template <class Comparable>
const FHsearch_tree<Comparable> &FHsearch_tree<Comparable>::operator=
(const FHsearch_tree &rhs)
{
    if (&rhs != this)
    {
        clear();
        mRoot = clone(rhs.mRoot);
        mSize = rhs.size();
        mSizeHard = rhs.sizeHard(); 
    }
    return *this;
}

template <class Comparable>
bool FHsearch_tree<Comparable>::insert(const Comparable &x)
{
    if (insert(mRoot, x))
    {
        mSize++;
        return true;
    }
    return false;
}

//This is the "soft" removal. It just marks the node as deleted. 
template <class Comparable>
bool FHsearch_tree<Comparable>::remove(const Comparable &x)
{
    if (remove(mRoot, x))
    {
        mSize--;
        return true;
    }
    return false;
}

//This is the "hard" removal. It removes all nodes marked as "deleted." 
template <class Comparable>
void FHsearch_tree<Comparable>::collectGarbage()
{
    collectGarbage(mRoot); 
}

template <class Comparable>
template <class Processor>
void FHsearch_tree<Comparable>::traverse(FHs_treeNode<Comparable> *treeNode,
    Processor func, int level) const
{
    if (treeNode == NULL)
        return;
    // we're not doing anything with level but its there in case we want it
    traverse(treeNode->lftChild, func, level + 1);
    if (!treeNode->deleted)
        func(treeNode->data);
    traverse(treeNode->rtChild, func, level + 1);
}


// FHsearch_tree private method definitions -----------------------------
template <class Comparable>
FHs_treeNode<Comparable> *FHsearch_tree<Comparable>::clone(
    FHs_treeNode<Comparable> *root) const
{
    FHs_treeNode<Comparable> *newNode;
    if (root == NULL)
        return NULL;

    newNode = new FHs_treeNode<Comparable>(
        root->data,
        clone(root->lftChild), clone(root->rtChild), 
        root->deleted);
    return newNode;
}

template <class Comparable>
FHs_treeNode<Comparable> *FHsearch_tree<Comparable>::findMin(
    FHs_treeNode<Comparable> *root) const
{
    if (root == NULL)
        return NULL; 
    FHs_treeNode<Comparable> *temp = findMin(root->lftChild); 
    if (temp != NULL)
        return temp; 
    if (!root->deleted)
        return root; 
    return findMin(root->rtChild); 
}

template <class Comparable> 
FHs_treeNode<Comparable> *FHsearch_tree<Comparable>::findMinHard(
    FHs_treeNode<Comparable> *root) const
{
    if (root == NULL)
        return NULL;
    if (root->lftChild == NULL)
        return root;
    return findMinHard(root->lftChild); 
}

template <class Comparable>
FHs_treeNode<Comparable> *FHsearch_tree<Comparable>::findMax(
    FHs_treeNode<Comparable> *root) const
{
    if (root == NULL)
    {
        return NULL;
    }
    FHs_treeNode<Comparable> *temp = findMax(root->rtChild);
    if (temp != NULL)
        return temp;
    if (!root->deleted) 
        return root; 
    return findMax(root->lftChild);
}

template <class Comparable>
FHs_treeNode<Comparable>* FHsearch_tree<Comparable>::find(
    FHs_treeNode<Comparable> *root, const Comparable &x) const
{
    if (root == NULL)
        return NULL;

    if (x < root->data)
        return find(root->lftChild, x);
    if (root->data < x)
        return find(root->rtChild, x);
    if (root->deleted)
        return NULL; 
    return root;
}

template <class Comparable>
bool FHsearch_tree<Comparable>::insert(
    FHs_treeNode<Comparable> * &root, const Comparable &x)
{
    if (root == NULL)
    {
        root = new FHs_treeNode<Comparable>(x, NULL, NULL);
        mSizeHard++; 
        return true;
    }
    else if (x < root->data)
        return insert(root->lftChild, x);
    else if (root->data < x)
        return insert(root->rtChild, x);
    else if (root->data == x && root->deleted) {
        root->deleted = false; 
        return true; 
    }
    return false; // duplicate
}

template <class Comparable>
bool FHsearch_tree<Comparable>::remove(
    FHs_treeNode<Comparable> * &root, const Comparable &x)
{
    if (root == NULL)
        return false;

    if (x < root->data)
        return remove(root->lftChild, x);
    if (root->data < x)
        return remove(root->rtChild, x);

    // found the node
    if (!root->deleted)
    {
        root->deleted = true;
        return true;
    }
    else if (root->deleted)
    {
        return false; 
    }

    return false;
}


template <class Comparable>
bool FHsearch_tree<Comparable>::removeHard(
    FHs_treeNode<Comparable> * &root, const Comparable &x)
{
    if (root == NULL)
        return false;

    if (x < root->data)
        return remove(root->lftChild, x);
    if (root->data < x)
        return remove(root->rtChild, x);

    // found the node
    if (root->lftChild != NULL && root->rtChild != NULL)
    {
        FHs_treeNode<Comparable> *minNode = findMinHard(root->rtChild);
        root->data = minNode->data;
        root->deleted = false; 
        removeHard(root->rtChild, minNode->data);
    }
    else
    {
        FHs_treeNode<Comparable> *nodeToRemove = root;
        root = (root->lftChild != NULL) ? root->lftChild : root->rtChild;
        delete nodeToRemove;
    }
    return true;
}

template <class Comparable>
void FHsearch_tree<Comparable>::collectGarbage(FHs_treeNode<Comparable> * &root)
{
    if (root == NULL)
        return; 

    collectGarbage(root->lftChild); 
    collectGarbage(root->rtChild);
    if (root->deleted)
    {
        removeHard(root, root->data);
        mSizeHard--;
    }
}

template <class Comparable>
void FHsearch_tree<Comparable>::makeEmpty(
    FHs_treeNode<Comparable> * &subtreeToDelete)
{
    if (subtreeToDelete == NULL)
        return;

    // remove children
    makeEmpty(subtreeToDelete->lftChild);
    makeEmpty(subtreeToDelete->rtChild);

    // clear client's pointer
    delete subtreeToDelete;
    subtreeToDelete = NULL;
    --mSize;
}

template <class Comparable>
int FHsearch_tree<Comparable>::findHeight(FHs_treeNode<Comparable> *treeNode,
    int height) const
{
    int leftHeight, rightHeight;

    if (treeNode == NULL)
        return height;
    height++;
    leftHeight = findHeight(treeNode->lftChild, height);
    rightHeight = findHeight(treeNode->rtChild, height);
    return (leftHeight > rightHeight) ? leftHeight : rightHeight;
}

#endif