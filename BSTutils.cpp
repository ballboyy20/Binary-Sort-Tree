#include "BSTutils.hpp"


void insert_value_into_tree(Node* root, double value)
{
    if(value < root->get_value())
    {
        insert_value_into_left_side(root, value);
    }

    else
    {
        insert_value_into_right_side(root, value);
    }
}

void insert_value_into_left_side(Node* root, double value)
{
    if(root->get_left_child() == nullptr)
    {
        root->set_left_child(new Node{value});
    }
    else
    {
        insert_value_into_tree(root->get_left_child(), value);
    }
}

void insert_value_into_right_side(Node* root, double value)
{
    if(root->get_right_child() == nullptr)
    {
        root->set_right_child(new Node{value});
    }
    else
    {
        insert_value_into_tree(root->get_right_child(),value);
    }
}

std::vector<double> get_values_using_inorder_traversal(const Node* node)
{
    std:: vector<double> valuesInOrder;
    if(node != nullptr)
    {
        std::vector<double> leftValues = get_values_using_inorder_traversal(node->get_left_child());
        std::vector<double> rightValues = get_values_using_inorder_traversal(node->get_right_child());

        valuesInOrder.insert(valuesInOrder.end(), leftValues.begin(), leftValues.end());
        valuesInOrder.push_back(node->get_value());
        valuesInOrder.insert(valuesInOrder.end(), rightValues.begin(), rightValues.end());
    }

    return valuesInOrder;
}

void delete_tree(Node* node)
{
    if(node != nullptr)
    {
        delete_tree(node->get_left_child());
        delete_tree(node->get_right_child());
        delete node;
    }
}

Node* copy_tree(Node* rootNode)
{
    if(rootNode != nullptr)
    {
        Node* copiedNode = new Node{rootNode->get_value()};
        copiedNode->set_left_child(copy_tree(rootNode->get_left_child()));
        copiedNode->set_right_child(copy_tree(rootNode->get_right_child()));
        return copiedNode;
    }
    return nullptr;
}
