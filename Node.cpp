#include "Node.h"

using namespace std;

int Node::getData() const{
    return data;
}

Node * Node::getLeftChild() const{
    return leftChild;
}

Node * Node::getRightChild() const{
    return rightChild;
}

int Node::getHeight(){
    return height;
}




