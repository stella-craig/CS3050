#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include "bst.h"

// Local functions
//Helper functions :)
NODE* InsertForReal(NODE* parent, NODE* newNode);
void InOrderHelper(NODE *node, NODEVISITFUNC func);
void PreOrderHelper(NODE *node, NODEVISITFUNC func);
void PostOrderHelper(NODE *node, NODEVISITFUNC func);

// These are stubs.  That is, you need to implement these functions.

//Create an empty BST
BST * NewBST()
{
    BST *myBST = (BST *)malloc(sizeof(BST)); //allocate size
    myBST->node = NULL; //set all pointers to null
    myBST->left = NULL;
    myBST->right = NULL;
    return myBST; //return the bst pointer
}

//Insert a new node into the BST
void TreeInsert(BST *pBST, void *satellite, long long key)
{
    //Create a new node with the details passed
    NODE* newNode = malloc(sizeof(NODE));
    newNode->key = key;
    newNode->satellite = satellite;
    newNode->left = NULL;
    newNode->right = NULL;

    pBST->node = InsertForReal(pBST->node, newNode); //use helper function
}

//TreeInsert helper function
NODE* InsertForReal(NODE* parent, NODE* newNode)
{
    if (parent == NULL) {
        // parent is NULL, so make the new node the root
        return newNode;
    } else if (newNode->key < parent->key) {
        // newNode should go in the left subtree
        parent->left = InsertForReal(parent->left, newNode);
    } else if (newNode->key > parent->key) {
        // newNode should go in the right subtree
        parent->right = InsertForReal(parent->right, newNode);
    } else {
        // newNode has the same key as an existing node, so replace the satellite data
        parent->satellite = newNode->satellite;
        free(newNode);  // don't need the newNode anymore
    }
    return parent;
}

void InOrder(BST * pBST, NODEVISITFUNC func){
    if (pBST->node == NULL) {
        return;  // empty tree, nothing to do
    }
    InOrderHelper(pBST->node, func);
}

void InOrderHelper(NODE *node, NODEVISITFUNC func) {
    if (node == NULL) {
        return;  // reached the end of a subtree
    }
    InOrderHelper(node->left, func);  // process left subtree
    func(node->satellite);  // process current node
    InOrderHelper(node->right, func);  // process right subtree
}

void PreOrder(BST *pBST, NODEVISITFUNC func) {
    if (pBST->node == NULL) {
        return;  // empty tree, nothing to do
    }
    PreOrderHelper(pBST->node, func);
}

void PreOrderHelper(NODE *node, NODEVISITFUNC func) {
    if (node == NULL) {
        return;  // reached the end of a subtree
    }
    func(node->satellite);  // process current node
    PreOrderHelper(node->left, func);  // process left subtree
    PreOrderHelper(node->right, func);  // process right subtree
}

void PostOrder(BST *pBST, NODEVISITFUNC func) {
    if (pBST->node == NULL) {
        return;  // empty tree, nothing to do
    }
    PostOrderHelper(pBST->node, func);
}

void PostOrderHelper(NODE *node, NODEVISITFUNC func) {
    if (node == NULL) {
        return;  // reached the end of a subtree
    }
    PostOrderHelper(node->left, func);  // process left subtree
    PostOrderHelper(node->right, func);  // process right subtree
    func(node->satellite);  // process current node
}

void *Search(BST *pBST, long long key) {
    NODE *node = pBST->node;
    while (node != NULL) {
        if (key == node->key) {
            return node->satellite;  // found the node, return its satellite data
        } else if (key < node->key) {
            node = node->left;  // search the left subtree
        } else {
            node = node->right;  // search the right subtree
        }
    }
    return NULL;  // node not found
}

void TreeDelete(BST *pBST, long long key) {
    NODE *parent = NULL;
    NODE *node = pBST->node;
    
    // search for the node to be deleted
    while (node != NULL) {
        if (key == node->key) {
            break;  // found the node to be deleted
        } else if (key < node->key) {
            parent = node;
            node = node->left;  // search the left subtree
        } else {
            parent = node;
            node = node->right;  // search the right subtree
        }
    }
    
    // if node is NULL, the key wasn't found, so there's nothing to delete
    if (node == NULL) {
        return;
    }
    
    // determine which case applies
    if (node->left == NULL && node->right == NULL) {  // case 1: node has no children
        if (parent == NULL) {  // node is the root
            pBST->node = NULL;
        } else if (parent->left == node) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(node);  // delete the node
    } else if (node->left == NULL || node->right == NULL) {  // case 2: node has one child
        NODE *child = node->left != NULL ? node->left : node->right;
        if (parent == NULL) {  // node is the root
            pBST->node = child;
        } else if (parent->left == node) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        free(node);  // delete the node
    } else {  // case 3: node has two children
        NODE *successor = node->right;
        parent = node;
        while (successor->left != NULL) {
            parent = successor;
            successor = successor->left;
        }
        // copy the satellite data of the successor node to the node to be deleted
        node->key = successor->key;
        node->satellite = successor->satellite;
        // delete the successor node (it has at most one right child)
        if (parent->left == successor) {
            parent->left = successor->right;
        } else {
            parent->right = successor->right;
        }
        free(successor);  // delete the successor node
    }
}
