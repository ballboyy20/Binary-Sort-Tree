#include "node.hpp"

Node::Node(double constructorValueInsideTheNode)
{
   privateValueInTheNode = constructorValueInsideTheNode;
}

void Node::set_left_child(Node* leftChild)
{
    privateLeftChild = leftChild;
}

Node* Node::get_left_child() const
{
    return privateLeftChild;
}

void Node::set_right_child(Node *rightChild)
{
    privateRightChild = rightChild;
}

Node* Node::get_right_child() const
{
    return privateRightChild;
}

void Node::set_value(double valueInsideTheNode)
{
    privateValueInTheNode = valueInsideTheNode;
}

double Node::get_value() const
{
    return privateValueInTheNode;
}
