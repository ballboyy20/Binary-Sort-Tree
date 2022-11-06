#ifndef BINARYSORTTTREE_HPP
#define BINARYSORTTTREE_HPP
#include <vector>
#include <iostream>

class Node;

class BinarySortTree
{
public:
    BinarySortTree()=default;
    BinarySortTree(const BinarySortTree& treeToBeCopied);
    BinarySortTree(BinarySortTree&& other);
    virtual ~BinarySortTree();

    BinarySortTree& operator=(BinarySortTree&& otherTree);
    BinarySortTree& operator=(const BinarySortTree& otherTree);


    void insert_value(double value);
    void delete_value(Node* root, double value);
    void clear_tree();
    std::vector<double> get_sorted_values();

    void make_tree_from_vector(const std::vector<double> vectorThatWillBeTree);

protected:
    Node* rootNode{nullptr};
};

#endif
