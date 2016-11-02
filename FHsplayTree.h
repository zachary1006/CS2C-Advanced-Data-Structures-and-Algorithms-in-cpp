/*
Name: Zachary Simon
Class: CS 2C
Due Date: 10/31/2016
Instructor: Dave Harden
Name of File: FHsplayTree.h


This file implements a splay tree, where any nodes that are accessed are moved 
to the top of the tree, making future accesses faster. FHsplayTree inherits from 
FHsearch_tree.h. With this implementation, the client can insert() and remove() 
nodes, check if the tree contains() a node, find() a node, and show the 
root (showRoot()). There are protected functions that splay the tree and 
rotate with left/right child, as well. 

The Comparable value used MUST have the < operator overloaded for use, or the 
tree will not work. 


bool insert(const Comparable &x);
Inserts an object (x) into the tree, splaying the tree so that x becomes the root. 
    Returns true if successful, false if unsuccessful. False will be returned if 
    the object is already in the tree. 
Preconditions: x must be comparable with the < operator. 
Postconditions: x is inserted into the tree, and is now the root of the tree. 
    Returns true if successful, false if unsuccessful. 


bool remove(const Comparable &x);
Attempts to remove an object (x) from the tree. True will be returned if successful; 
    false will be returned if the object is not found in the tree. 
Preconditions: x must be comparable with the < operator. 
Postconditions: If x is in the tree, it is removed. If there are values below x in 
    the tree, the next-highest value becomes the root. Otherwise, the next-highest 
    value becomes the root. 


bool contains(const Comparable & x);
Returns a bool depending on whether or not a tree contains a given object (x). 
Preconditions: x must be comparable with the < operator. 
Postconditions: Returns true if the tree contains x, false otherwise. The tree 
    is splayed during operation, x (or a value close to it) becomes the root 
    of the tree. 


const Comparable& find(const Comparable &x);
If successful, it returns the object found in the tree. If unsuccessful, it throws 
    either an EmptyTreeException() or a NotFoundException(). 
Preconditions: x must be comparable with the < operator. 
Postconditions: Returns object found if successful, otherwise returns an exception. 
    Tree is splayed during method, so x (or a value close to it) becomes the root. 


const Comparable &showRoot();
Returns the data of the tree root, or an automatic default object if there is no 
    master root. 
Preconditions: (None)
Postconditions: Returns data of tree root. 


void splay(FHs_treeNode<Comparable>* &root, const Comparable &x);
Splays the tree searching for x. Reassembles the tree after either successfully 
    finding x or discovering that the value is not in the tree. Tree is re-
    assembled before returning, with x in the root if found, otherwise a value 
    close to it in the root. 
Preconditions: x must be comparable with the < operator. 
Postconditions: Tree is splayed so that x becomes the root (if it exists in the tree). 


void rotateWithLeftChild(FHs_treeNode<Comparable>* &k2);
Rotates a node with its left child. Used when splaying the tree. 
Preconditions: Node k2 must belong to the same tree being splayed. 
Postconditions: Node k2 takes on the value of its left child, with 
    its value being placed in its right tree. 


void rotateWithRightChild(FHs_treeNode<Comparable>* &k2);
Rotates a node with its right child. Used when splaying the tree. 
Precondition: Node k2 must belong to the same tree being splayed. 
Postconditions: Node k2 takes on the value of its right child, with 
    its value being placed in its left tree. 

    
*/

#ifndef FHSPLAYTREE_H
#define FHSPLAYTREE_H
#include "Fhsearch_tree.h"


// --------------------- FHsplayTree Prototype --------------------- 
template <class Comparable> 
class FHsplayTree : public FHsearch_tree<Comparable>
{
public: 
    bool insert(const Comparable &x); 
    bool remove(const Comparable &x); 
    bool contains(const Comparable & x); 
    const Comparable& find(const Comparable &x); 

    const Comparable &showRoot(); 

protected: 
    void splay(FHs_treeNode<Comparable>* &root, const Comparable &x); 
    void rotateWithLeftChild(FHs_treeNode<Comparable>* &k2); 
    void rotateWithRightChild(FHs_treeNode<Comparable>* &k2); 
};






template <class Comparable> 
bool FHsplayTree<Comparable>::insert(const Comparable &x)
{
    if (this->mRoot == NULL)
    {
        this->mRoot = new FHs_treeNode<Comparable>(x, NULL, NULL); 
        this->mSize++; 
        return true; 
    }
    else
    {
        splay(this->mRoot, x); 
    }
    if (x < this->mRoot->data)
    {
        FHs_treeNode<Comparable> *newNode = new FHs_treeNode<Comparable>(x, this->mRoot->lftChild, this->mRoot);
        this->mRoot = newNode; 
        this->mSize++; 
        return true; 
    }
    else if (this->mRoot->data < x)
    {
        FHs_treeNode<Comparable> *newNode = new FHs_treeNode<Comparable>(x, this->mRoot, this->mRoot->rtChild);
        this->mRoot = newNode;
        this->mSize++; 
        return true;
    }
    else
    {
        //x is already in the tree
        return false; 
    }
}






template <class Comparable> 
bool FHsplayTree<Comparable>::remove(const Comparable &x)
{
    FHs_treeNode<Comparable> *newRoot; 

    if (this->mRoot == NULL)
    {
        return false; 
    }
    else
    {
        splay(this->mRoot, x); 
    }
    if ((this->mRoot->data < x) || (x < this->mRoot->data))
    {
        //x not found in tree
        return false; 
    }
    if (this->mRoot->lftChild == NULL)
    {
        newRoot = this->mRoot; 
    }
    else
    {
        newRoot = this->mRoot->lftChild; 
        splay(newRoot, x); 
        newRoot->rtChild = this->mRoot->rtChild; 
    }
    delete this->mRoot; 
    this->mRoot = newRoot; 
    this->mSize--; 
    return true; 
}






template <class Comparable>
bool FHsplayTree<Comparable>::contains(const Comparable & x)
{
    if (this->mRoot == NULL)
    {
        return false; 
    }
    splay(this->mRoot, x); 
    if ((x < this->mRoot->data) || (this->mRoot->data < x))
    {
        return false; 
    }
    return true; 
}






template <class Comparable> 
const Comparable& FHsplayTree<Comparable>::find(const Comparable &x)
{
    if (this->mRoot == NULL)
    {
        throw typename FHsearch_tree<Comparable>::EmptyTreeException(); 
    }

    splay(this->mRoot, x); 
    if ((this->mRoot->data < x) || (x < this->mRoot->data))
    {
        throw typename FHsearch_tree<Comparable>::NotFoundException(); 
    }
    else 
    {
        return showRoot();
    }
}







template <class Comparable> 
const Comparable& FHsplayTree<Comparable>::showRoot()
{
    if (this->mRoot == NULL)
    {
        FHs_treeNode<Comparable> *newNode = new FHs_treeNode<Comparable>(); 
        return newNode->data; 
    }
    return this->mRoot->data; 
}






template <class Comparable> 
void FHsplayTree<Comparable>::splay(FHs_treeNode<Comparable>* &root, const Comparable &x)
{
    FHs_treeNode<Comparable> *rightTree = NULL;
    FHs_treeNode<Comparable> *leftTree = NULL;
    FHs_treeNode<Comparable> *rightTreeMin = NULL;
    FHs_treeNode<Comparable> *leftTreeMax = NULL;

    while (root != NULL)
    {

        if (x < root->data)
        {

            if (root->lftChild == NULL)
            {
                //x not in tree 
                break; 
            }
            if (x < root->lftChild->data)
            {
                //zig-zig (left) 
                rotateWithLeftChild(root); 
                if (root->lftChild == NULL)
                {
                    //x not in tree
                    break; 
                }
            }

            if (rightTree == NULL)
            {
                rightTree = root;
                rightTreeMin = root; 
            }
            else
            {
                rightTreeMin->lftChild = root; 
                rightTreeMin = root; 
            }

            root = root->lftChild; 
        }
        else if (root->data < x)
        {

            if (root->rtChild == NULL)
            {
                //x not in tree
                break; 
            }
            if (root->rtChild->data < x)
            {
                //zig-zig (right) 
                rotateWithRightChild(root); 
                if (root->rtChild == NULL)
                {
                    //x not in tree
                    break; 
                }
            }

            if (leftTree == NULL)
            {
                leftTree = root; 
                leftTreeMax = root; 
            }
            else
            {
                leftTreeMax->rtChild = root; 
            }

            root = root->rtChild;
        }
        else
        {
            //we found x at root 
            break; 
        }
    }

    //reassemble 
    if (leftTree != NULL)
    {
        leftTreeMax->rtChild = root->lftChild; 
        root->lftChild = leftTree; 
    }
    if (rightTree != NULL)
    {
        rightTreeMin->lftChild = root->rtChild; 
        root->rtChild = rightTree; 
    }
}






template <class Comparable> 
void FHsplayTree<Comparable>::rotateWithLeftChild(FHs_treeNode<Comparable>* &k2)
{
    FHs_treeNode<Comparable> *k1 = k2->lftChild; 
    k2->lftChild = k1->rtChild; 
    k1->rtChild = k2; 
    k2 = k1; 
}






template <class Comparable> 
void FHsplayTree<Comparable>::rotateWithRightChild(FHs_treeNode<Comparable>* &k2)
{
    FHs_treeNode<Comparable> *k1 = k2->rtChild; 
    k2->rtChild = k1->lftChild; 
    k1->lftChild = k2; 
    k2 = k1; 
}

#endif


/* ------- Sample Run -------
Initial size: 0
New size: 32

Traversal:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32

oops splay -1 --> root: 1 height: 16
oops splay 0 --> root: 1 height: 16
splay 1 --> root: 1 height: 16
splay 2 --> root: 2 height: 9
splay 3 --> root: 3 height: 6
splay 4 --> root: 4 height: 6
splay 5 --> root: 5 height: 5
splay 6 --> root: 6 height: 6
splay 7 --> root: 7 height: 6
splay 8 --> root: 8 height: 7
splay 9 --> root: 9 height: 8

Test of showRoot() on empty tree:
0
*/