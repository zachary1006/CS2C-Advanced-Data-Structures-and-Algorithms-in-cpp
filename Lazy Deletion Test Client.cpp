/*
Name: Zachary Simon
Class: CS 2C
Due Date: 10/24/2016
Instructor: Dave Harden
Name of File: a4_1.cpp


This program tests the functionality of the Binary Tree construct, 
FHlazySearchTree. The tree uses lazy deletion, where nodes are marked 
as deleted, rather than actually removed. If necessary, the nodes can be 
removed by the collectGarbage() method. 

The client must create the tree and call the methods, but no direct input 
from the end-user is required once the progrma is running. If desired, 
the state of the tree can be manually printed out using a functor and 
the traverse() method. Nodes that exist but are marked as "deleted" will 
not appear on the traverse() results. 

*/

// Assignment #4 Instructor Solution
// CS 2C, Foothill College, Michael Loceff

// --------------- main ---------------

// CS 2C  Simple Search Tree Client - Lazy Deletion, int data
#include <iostream>
#include <string>
#include <stack>
#include "FHlazySearchTree.h"
using namespace std;

template <typename Object>
class PrintObject
{
public:
    void operator()(Object obj)
    {
        cout << obj << " ";
    }
};

int main()
{
    int k;
    FHsearch_tree<int> searchTree;
    PrintObject<int> intPrinter;

    searchTree.traverse(intPrinter);

    cout << "\ninitial size: " << searchTree.size() << endl;
    searchTree.insert(50);
    searchTree.insert(20);
    searchTree.insert(30);
    searchTree.insert(70);
    searchTree.insert(10);
    searchTree.insert(60);

    cout << "After populating -- traversal and sizes: \n";
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "Collecting garbage on new tree - should be no garbage." << endl;
    searchTree.collectGarbage();
    cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    // test assignment operator
    FHsearch_tree<int> searchTree2 = searchTree;

    cout << "\n\nAttempting 1 removal: \n";
    if (searchTree.remove(20))
        cout << "removed " << 20 << endl;
    cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "Collecting Garbage - should clean 1 item. " << endl;
    searchTree.collectGarbage();
    cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "Collecting Garbage again - no change expected. " << endl;
    searchTree.collectGarbage();
    cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    // test soft insertion and deletion:

    cout << "Adding 'hard' 22 - should see new sizes. " << endl;
    searchTree.insert(22);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "\nAfter soft removal. " << endl;
    searchTree.remove(22);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "Repeating soft removal. Should see no change. " << endl;
    searchTree.remove(22);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "Soft insertion. Hard size should not change. " << endl;
    searchTree.insert(22);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "\n\nAttempting 100 removals: \n";
    for (k = 100; k > 0; k--)
    {
        if (searchTree.remove(k))
            cout << "removed " << k << endl;
    }
    searchTree.collectGarbage();

    cout << "\nsearchTree now:\n";
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    searchTree2.insert(500);
    searchTree2.insert(200);
    searchTree2.insert(300);
    searchTree2.insert(700);
    searchTree2.insert(100);
    searchTree2.insert(600);
    cout << "\nsearchTree2:\n";
    searchTree2.traverse(intPrinter);
    cout << "\ntree 2 size: " << searchTree2.size()
        << "  Hard size: " << searchTree2.sizeHard() << endl;

    // -----------------Zach's additions------------------
    cout << endl << endl; 
    
    FHsearch_tree<int> searchTree3; 
    for (int i = 0; i < 3; ++i)
    {
        searchTree3.insert(i); 
    }
    searchTree3.remove(2); 
    cout << "Max value: " << searchTree3.findMax() << endl; 
    searchTree3.insert(2);
    cout << "Max value: " << searchTree3.findMax() << endl;
    searchTree3.remove(1);
    cout << "Max value: " << searchTree3.findMax() << endl;
    searchTree3.remove(2); 
    cout << "Max value: " << searchTree3.findMax() << endl;
    searchTree3.collectGarbage();
    cout << "Max value: " << searchTree3.findMax() << endl;
    for (int i = 0; i < 4; ++i) 
    {
        searchTree3.insert(i); 
    }
    cout << "Max value: " << searchTree3.findMax() << endl;
    searchTree3.remove(1); 
    searchTree3.remove(2);
    cout << "Max value: " << searchTree3.findMax() << endl;
    searchTree3.insert(2); 
    searchTree3.remove(3);
    cout << "Max value: " << searchTree3.findMax() << endl;
    searchTree3.insert(4);
    cout << "Max value: " << searchTree3.findMax() << endl;
    searchTree3.collectGarbage();
    cout << "Max value: " << searchTree3.findMax() << endl;
    searchTree3.remove(0);
    cout << "Max value: " << searchTree3.findMax() << endl;
    searchTree3.traverse(intPrinter); 
    cout << "\nHard size: " << searchTree3.sizeHard() << " soft size: " << 
        searchTree3.size() << "\n"; 
    searchTree3.remove(2); 
    searchTree3.remove(4);
    //The calls below cause an abort, 
    //because the tree only contains nodes marked as deleted
    /*cout << "Max value: " << searchTree3.findMax() << endl;*/
    /*cout << "Min value: " << searchTree3.findMin() << endl; */
    searchTree3.collectGarbage();
    /*cout << "Max value: " << searchTree3.findMax() << endl;*/
    cout << "Hard size: " << searchTree3.sizeHard() << " soft size: " <<
        searchTree3.size() << "\n";
    searchTree3.insert(10); 
    cout << "Hard size: " << searchTree3.sizeHard() << " soft size: " <<
        searchTree3.size() << "\n";

    FHsearch_tree<int> searchTree4; 
    searchTree4.collectGarbage(); 


    return 0;
}

/* My program run: 


initial size: 0
After populating -- traversal and sizes:
10 20 30 50 60 70
tree 1 size: 6  Hard size: 6
Collecting garbage on new tree - should be no garbage.
tree 1 size: 6  Hard size: 6


Attempting 1 removal:
removed 20
tree 1 size: 5  Hard size: 6
Collecting Garbage - should clean 1 item.
tree 1 size: 5  Hard size: 5
Collecting Garbage again - no change expected.
tree 1 size: 5  Hard size: 5
Adding 'hard' 22 - should see new sizes.
10 22 30 50 60 70
tree 1 size: 6  Hard size: 6

After soft removal.
10 30 50 60 70
tree 1 size: 5  Hard size: 6
Repeating soft removal. Should see no change.
10 30 50 60 70
tree 1 size: 5  Hard size: 6
Soft insertion. Hard size should not change.
10 22 30 50 60 70
tree 1 size: 6  Hard size: 6


Attempting 100 removals:
removed 70
removed 60
removed 50
removed 30
removed 22
removed 10

searchTree now:

tree 1 size: 0  Hard size: 0

searchTree2:
10 20 30 50 60 70 100 200 300 500 600 700
tree 2 size: 12  Hard size: 12


Max value: 1
Max value: 2
Max value: 2
Max value: 0
Max value: 0
Max value: 3
Max value: 3
Max value: 2
Max value: 4
Max value: 4
Max value: 4
2 4
Hard size: 3 soft size: 2
Hard size: 0 soft size: 0
Hard size: 1 soft size: 1

*/


/* ---------------------- Demo Run (from assignment) --------------------------
initial size: 0
After populating -- traversal and sizes:
10 20 30 50 60 70
tree 1 size: 6  Hard size: 6
Collecting garbage on new tree - should be no garbage.
tree 1 size: 6  Hard size: 6


Attempting 1 removal:
removed 20
tree 1 size: 5  Hard size: 6
Collecting Garbage - should clean 1 item.
tree 1 size: 5  Hard size: 5
Collecting Garbage again - no change expected.
tree 1 size: 5  Hard size: 5
Adding 'hard' 22 - should see new sizes.
10 22 30 50 60 70
tree 1 size: 6  Hard size: 6

After soft removal.
10 30 50 60 70
tree 1 size: 5  Hard size: 6
Repeating soft removal. Should see no change.
10 30 50 60 70
tree 1 size: 5  Hard size: 6
Soft insertion. Hard size should not change.
10 22 30 50 60 70
tree 1 size: 6  Hard size: 6


Attempting 100 removals:
removed 70
removed 60
removed 50
removed 30
removed 22
removed 10

searchTree now:

tree 1 size: 0  Hard size: 0

searchTree2:
10 20 30 50 60 70 100 200 300 500 600 700
tree 2 size: 12  Hard size: 12
Press any key to continue . . .
---------------------------------------------------------------------- */