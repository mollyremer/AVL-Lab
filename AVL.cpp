#include "AVL.h"

NodeInterface * AVL::getRootNode() const{
    return root;
}

int AVL::calcHeight(Node * n){
    if (n == nullptr){
        return -1;
    }
    int left = calcHeight(n->leftChild);
    int right = calcHeight(n->rightChild);
    return max(left, right) + 1;
}

void AVL::balanceTree(Node *& n){
    if (n == nullptr) { return; }
    else {
     cout << "balancing " << n->data << endl;
    }
    if (leftleftImbalance(n)){
        rightRotate(n);
        return;
    }
    else if (rightRightImbalance(n)){
        leftRotate(n);
        return;
    }
    else if (leftRightImbalance(n)){
        leftRotate(n->leftChild);
        rightRotate(n);
        return;
    }
    else if (rightLeftImbalance(n)){
        rightRotate(n->rightChild);
        leftRotate(n);
        return;
    }
    else {
        return;
    }
}

bool AVL::add(int data){
    return insertNode(root, data);
}

bool AVL::insertNode(Node *& currentNode, int data){
    if (currentNode == nullptr){
        currentNode = new Node(data);
        cout << "added " << currentNode->data << endl;
        return true;
    }
    if (currentNode->data == data){
        return false;
    }
    if (currentNode->data > data){
        bool added = insertNode(currentNode->leftChild, data);
        if (added){
            balanceTree(currentNode);
        }
        return added;
    }
    if (currentNode->data < data){
        bool added = insertNode(currentNode->rightChild, data);
        if (added){
            balanceTree(currentNode);
        }
        return added;
    }
}

bool AVL::leftleftImbalance(Node *& n){
    if(calcHeight(n->leftChild) - calcHeight(n->rightChild) > 1){
        if(calcHeight(n->leftChild->leftChild) >= calcHeight(n->leftChild->rightChild)){
            return true;
        } 
    } 
    return false;
}

bool AVL::rightRightImbalance(Node *& n){
    if(calcHeight(n->leftChild) - calcHeight(n->rightChild) < -1){
        if(calcHeight(n->rightChild->rightChild) >= calcHeight(n->rightChild->leftChild)){
            return true;
        }
    }
    return false;
}

bool AVL::leftRightImbalance(Node *& n){
    if(calcHeight(n->leftChild) - calcHeight(n->rightChild) > 1){
        if(calcHeight(n->leftChild->leftChild) < calcHeight(n->leftChild->rightChild)){
            return true;
        } 
    }
    return false;
}

bool AVL::rightLeftImbalance(Node *& n){
    if(calcHeight(n->leftChild) - calcHeight(n->rightChild) < -1){
        if(calcHeight(n->rightChild->leftChild) > calcHeight(n->rightChild->rightChild)){
            return true;
        } 
    }
    return false;
}

void AVL::rightRotate(Node *& n){
    Node* temp = n;
    n = n->leftChild;// Set pointer to n to point to k
    temp->leftChild = n->rightChild; // Set n's left to point to k's right
    n->rightChild = temp; // Set k's right to point to n
}

void AVL::leftRotate(Node *& n){
    Node* temp = n; 
    n = n->rightChild; // Set pointer to n to point to k
    temp->rightChild = n->leftChild; // Set n's right to point to k's left
    n->leftChild = temp; // Set k's left to point to n
}

bool AVL::remove(int data){
    cout << "removing " << data << endl;
    return recRemove(root, data);
}

bool AVL::recRemove(Node *& currentNode, int data){
    if (currentNode == nullptr){
        cout << "could not find " << data << endl;
        return false;
    }
    else if (currentNode->data > data){
        bool removed = recRemove(currentNode->leftChild, data);
        if (removed){
            balanceTree(currentNode);
        }
        return removed;
    }
    else if (currentNode->data < data){
        bool removed = recRemove(currentNode->rightChild, data);
        if (removed){
            balanceTree(currentNode);
        }
        return removed;
    }
    else if (currentNode->data == data){
        if (currentNode->leftChild == nullptr && currentNode->rightChild == nullptr){
            delete currentNode;
            currentNode = nullptr;
        }
        else if (currentNode->leftChild == nullptr){
            currentNode = currentNode->rightChild;
            delete currentNode->rightChild;
            currentNode->rightChild = nullptr;
        }
        else if (currentNode->rightChild == nullptr){
            currentNode = currentNode->leftChild;
            delete currentNode->leftChild;
            currentNode->leftChild = nullptr;
        }
        else{
            twoChildrenRemove(currentNode, currentNode->leftChild);
            balanceTree(currentNode);
        }
        return true;
    }
}

bool AVL::twoChildrenRemove(Node *& n, Node *& inheritor){
    if (inheritor->rightChild != NULL){
        return twoChildrenRemove(n, inheritor->rightChild);
    }
    else {
        n->data = inheritor->data;
        return recRemove(n->leftChild, inheritor->data);
    }
}

void AVL::clear(){
    cout << "clear" << endl;
    recClear(root);
}

void AVL::recClear(Node *& node){
    if (node == nullptr){
        return;
    }

    recClear(node->leftChild);
    recClear(node->rightChild);

    node = nullptr;
    delete node;
}