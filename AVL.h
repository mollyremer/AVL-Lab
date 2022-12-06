#pragma once

#include "AVLInterface.h"
#include "Node.h"

using namespace std;

class AVL : public AVLInterface{
private:
    Node * root = NULL;
	Node * parentNode = NULL; 
    bool cameFromRight = true; 

public:
	AVL() {}
	virtual ~AVL() {}
	int calcHeight(Node * n);

	void balanceTree(Node *& n);
	bool insertNode(Node *& currentNode, int data);

	bool leftleftImbalance(Node *& n);
	bool rightRightImbalance(Node *& n);
	bool leftRightImbalance(Node *& n);
	bool rightLeftImbalance(Node *& n);

	void rightRotate(Node *& n);
	void leftRotate(Node *& n);

	bool recAdd(Node *& currentNode, int data);
	bool recRemove(Node *& currentNode, int data);
	bool twoChildrenRemove(Node *& node, Node *& inheritor);
	void recClear(Node *& node);

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	NodeInterface * getRootNode() const;

	/*
	* Attempts to add the given int to the AVL tree
	* Rebalances the tree if data is successfully added
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool add(int data);

	/*
	* Attempts to remove the given int from the AVL tree
	* Rebalances the tree if data is successfully removed
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool remove(int data);

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void clear();
};
