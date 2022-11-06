#ifndef BSTUTILS_HPP
#define BSTUTILS_HPP
#include <vector>
#include "node.hpp"
#include "binarysorttree.hpp"

std::vector<double> get_values_using_inorder_traversal(const Node* node);

std::vector<double> get_values_using_preorder_traversal(const Node* node);

void insert_value_into_tree(Node* root, double value);

void insert_value_into_left_side(Node* root, double value);

void insert_value_into_right_side(Node* root, double value);

void delete_tree(Node* node);

Node* copy_tree(Node* rootNode);

Node* move_tree(BinarySortTree treeBeingMoved);

#endif // BSTUTILS_HPP
