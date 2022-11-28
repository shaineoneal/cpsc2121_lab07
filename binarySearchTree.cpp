/*
 * Name: Shaine O'Neal
 * Date Submitted: 11/9/2022
 * Lab Section: 4
 * Assignment Name: Binary Search Tree
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>
#include <bits/stdc++.h>

#include "binarySearchTree.h"

using namespace std;

//sets the size of the node passed in
void fix_size(Node *T) {
    T->size = 1;
    if (T->left) T->size += T->left->size;
    if (T->right) T->size += T->right->size;
}

// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k) {
    if (T == nullptr) return new Node(k);
    if (k < T->key) T->left = insert(T->left, k);
    else T->right = insert(T->right, k);
    fix_size(T);
    return T;
}

// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
vector<int> inorder_traversal(Node *T) {
    vector<int> inorder;
    vector<int> rhs;
    if (T == nullptr) return inorder;
    inorder=inorder_traversal(T->left);
    inorder.push_back(T->key);
    rhs=inorder_traversal(T->right);
    inorder.insert(inorder.end(), rhs.begin(), rhs.end());
    return inorder;
}

// return a pointer to the node with key k in tree T, or nullptr if it doesn't exist
Node *find(Node *T, int k) {
    if(T == nullptr) return nullptr;

    else if (T->key == k) return T;
    else if (T->key < k) return find(T->right, k);
    else if (T->key > k) return find(T->left, k);
    return nullptr;
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
    assert(T!=nullptr && r>=0 && r<T->size);

    //Implement Node *select(Node *T, int r)
    int nodeRank = T->left->size;
    if (T->left == nullptr) nodeRank = 0;

    if (nodeRank == r) return T;
    //moves to the left child
    else if (nodeRank > r) return select(T->left, r);
    //moves to the right child
    else if (nodeRank < r) return select(T->right, r - nodeRank - 1);
    
    return nullptr;
}

// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.  
Node *join(Node *L, Node *R)
{
    Node * root;
    Node * sub;
    // choose either the root of L or the root of R to be the root of the joined tree
    // (where we choose with probabilities proportional to the sizes of L and R)
    
    //Implement Node *join(Node *L, Node *R)
    if (L == nullptr) return R;
    if (R == nullptr) return L;
    else {
        double probL = abs(L->size) / (abs(L->size) + abs(R->size));
        if (rand() % 2 <= probL) { root = R; sub = L; } //right becomes root
        else {root = L; sub = R; } //left becomes root

        //if subtree is smaller than root tree
        if(sub->key < root->key) {
            //combine root->left with subtree
            Node * subHead = sub;
            //move to largest value of subtree
            while(sub != nullptr) {
                sub = sub->right;
            }
            //add the smallest part of root to sub
            sub = root->left;
            root->left = subHead;
        }
        //if subtree is larger than root tree
        else {
            Node * subHead = sub;
            //move to smallest value of subtree
            while(sub != nullptr) {
                sub = sub->left;
            }
            sub = root->right;
            root->right = subHead;
        }


        /*//if node right of root is greater than first key in sub
        if(root->right != nullptr && root->right->key > sub->key) {
            //iterate to highest val in sub
            while(sub->right != nullptr) {
                sub = sub->right;
            }

            sub->right = root->left;
            root->left = sub;
        }
        else {
            R->left = join(L, R->left);
            fix_size(R);
            return R;
        } 

        return nullptr;
    }
    
}

// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
Node *remove(Node *T, int k)
{
    assert(T != nullptr);
  
    //Implement Node *remove(Node *T, int k)

    //if T is empty
    if(T == nullptr) return T;

    if(k < T->key) T->left = remove(T->left, k);
    else if (k > T->key) T->right = remove(T->right, k);

    else {
        //node has no children
        if (T->left==NULL && T->right==NULL)
            return NULL;
        
        // node with only one child or no child
        else if (T->left == NULL) {
            Node * temp = T->right;
            free(T);
            return temp;
        }
        else if (T->right == NULL) {
            Node * temp = T->left;
            free(T);
            return temp;
        }

        //node has 2 children

        Node * temp = join(T->right, T->left);
        T->key = temp->key;
        T->left = temp->left;
        T->right = temp->right;

        free(temp);
    }

    fix_size(T);

    return T;
}

// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(Node *T, int k, Node **L, Node **R)
{
    //Implement void split(Node *T, int k, Node **L, Node **R)
    /*Node * fullT = T;
    Node * tempL = T;
    Node * tempR = T;


    //if first node is k
    if(T->key == k) {
        *R = fullT->right;
        tempL->right = nullptr;
        *L = tempL;
    }
    else if(T->key > k) {
        //while the node is greater than key
        while(tempL != nullptr && tempL->key > k) {
            //move down a node to the left
            tempR = insert(fullT->right, k)
            tempL = tempL->left;
        }
        
        *L = tempL;
        if (tempL != nullptr) {
            tempL->right = nullptr;
            *R = join(fullT->right, tempL->right);
        }
        else { *R = fullT->right; }
        
    }
    else {
        while(tempR != nullptr && tempR->key < k) {
            //move down a node to the right
            tempR = tempR->right;
        }
        
        //
        //if(tempR != nullptr) fix_size(tempR);
        *R = tempR;
        if (tempR != nullptr) {
            tempR->left = nullptr;
            tempL = join(fullT->left, tempR->left);
        }
        //if(tempL != nullptr) fix_size(tempL);
        else {
            tempL->right = nullptr;
            *L = tempL;
        }
    }*/

    Node * tree = T;
    Node * rhs = T->right;
    Node * lhs = T;
    //make lhs include head node and everything to the left
    lhs->right = nullptr;

    //if first node's key is equal to k
    if(tree->key == k) {
        *R = rhs;
        *L = lhs;
    }
    //if k is less than the first node
    else if(k < tree->key) {
        while(lhs != nullptr && k < lhs->key) { 
            //add value at node to rhs
            rhs = insert(rhs, lhs->key);
            //move to next smallest node
            lhs = lhs->left;
            //repeat until lhs->key is less than k || lhs = nullptr
        }

        if(lhs != nullptr) {
    
            rhs = join(lhs->right, rhs);
            lhs->right = nullptr;
            fix_size(lhs);
        }
       
    }
    else {
        while(rhs != nullptr && k > rhs->key) {
            //add value at node to lhs
            lhs = insert(lhs, rhs->key);
            //move to next largest node
            rhs = rhs->right;
            //repeat until rhs->key is greater than k || rhs = nullptr
        }
        if(rhs != nullptr) {
            lhs = join(rhs->left, lhs);
            rhs->left = nullptr;
            fix_size(rhs);
        }
    }
    
    
    *L = lhs;
    *R = rhs;
    
}

// insert key k into the tree T, returning a pointer to the resulting tree
Node *insert_random(Node *T, int k)
{
    // If k is the Nth node inserted into T, then:
    // with probability 1/N, insert k at the root of T
    // otherwise, insert_random k recursively left or right of the root of T
    
    Node * temp = T;
    Node * fin;

    if(temp == nullptr) {
        temp = insert(temp, k);
    }
    else if (temp->key != k) {
        

        Node * L;
        Node * R;

        //generate random value
        int r = rand() % temp->size;

        //if random value = 0; insert it as that node
        if (r == 0) {
            //split subtree into L and R
            split(temp, k, &L, &R);
            //insert new base node
            temp = new Node(k);
            temp->left = L;
            temp->right = R;
        }
        else if (k < temp->key) {
            insert_random(temp->left, k);
        }
        else if (k > temp->key) {
            insert_random(temp->right, k);
        }
        fix_size(temp);

    }


    
/*    //else if (T->key != k) {
    while(temp != nullptr) {
        Node * L;
        Node * R;

        //if( T->size == 0 ) { fix_size(T); }

        int random = rand() % temp->size;
        
        //insert as base node
        if (random == 0) {
            
            //divide existing tree into L and R
            split(temp, k, &L, &R);
            //insert new val into fin
            fin = (insert(fin, k));
            //assign fin left and right to L and R
            fin->left = L;
            fin->right = R;
            fix_size(fin);
        }
        else if(k > T->key) {
            insert_random(temp->right, k);
        }
        else {
            insert_random(temp->left, k);
        }    
        
        // increment the tree size
        //T->size++;    

    }*/

    
}

void printVector(vector<int> v) {
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

int main(void) {
    vector<int> inorder;
    vector<int> A(10,0);
    
    // put 0..9 into A[0..9] in random order
    for (int i=0; i<10; i++) A[i] = i;
    for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
    cout << "Contents of A (to be inserted into BST):\n";
    printVector(A);
    
    // insert contents of A into a BST
    Node *T = nullptr;
    for (int i=0; i<10; i++) T = insert(T, A[i]);
    
    // print contents of BST (should be 0..9 in sorted order)
    cout << "Contents of BST (should be 0..9 in sorted order):\n";
    inorder=inorder_traversal(T);
    printVector(inorder);
  
    // test select
    /*for (int i=0; i<10; i++) {
        Node *result = select(T, i);
        if ((result == nullptr) || (result->key != i)) cout << "Select test failed for select(" << i << ")!\n";
    }
  
    // test find: Elements 0..9 should be found; 10 should not be found
    cout << "Elements 0..9 should be found; 10 should not be found:\n";
    for (int i=0; i<11; i++) 
      if (find(T,i)) cout << i << " found\n";
      else cout << i << " not found\n";*/
  
    // test split
    Node *L, *R;
    split(T, 4, &L, &R);
    cout << "Contents of left tree after split (should be 0..4):\n";
    inorder=inorder_traversal(L);
    printVector(inorder);
    cout << "Left tree size " << L->size << "\n";
    cout << "Contents of right tree after split (should be 5..9):\n";
    inorder=inorder_traversal(R);
    printVector(inorder);
    cout << "Right tree size " << R->size << "\n";
      
    // test join
    T = join(L, R);
    cout << "Contents of re-joined tree (should be 0..9)\n";
    inorder=inorder_traversal(T);
    printVector(inorder);
    cout << "Tree size " << T->size << "\n";
    
    // test remove
      //printBT(T);
      //  
      //T = remove(T, 1);
      //cout << "Contents of tree after removing 1" << ":\n";
//
      //printBT(T);
    for (int i=0; i<10; i++) A[i] = i;
    for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);

  

    for (int i=0; i<10; i++) {

        printBT(T);
        
      T = remove(T, A[i]);
      cout << "Contents of tree after removing " << A[i] << ":\n";
      inorder=inorder_traversal(T);
      printVector(inorder);
      if (T != nullptr)
        cout << "Tree size " << T->size << "\n";
        }
  
    // test insert_random
    cout << "Inserting 1 million elements in order; this should be very fast...\n";
    for (int i=0; i<1000000; i++) { T = insert_random(T, i); }
    cout << "Tree size " << T->size << "\n";
    cout << "Done\n";
    
    return 0;
} 
  