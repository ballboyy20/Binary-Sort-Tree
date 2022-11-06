#include "binarysorttree.hpp"
#include "node.hpp"
#include "BSTutils.hpp"

BinarySortTree::BinarySortTree(const BinarySortTree& treeToBeCopied)
{
    this->rootNode = copy_tree(treeToBeCopied.rootNode);
}

BinarySortTree::BinarySortTree(BinarySortTree&& otherTree)
{
    (*this) = std::move(otherTree);
}

BinarySortTree::~BinarySortTree()
{
    clear_tree();
}

void BinarySortTree::clear_tree()
{
    delete_tree(rootNode);
    rootNode=nullptr;
}

void BinarySortTree::insert_value(double value)
{
    if(rootNode == nullptr)
    {
        rootNode = new Node{value};
    }
    else
    {
        insert_value_into_tree(rootNode, value);
    }
}

std::vector<double> BinarySortTree::get_sorted_values()
{
    std::vector<double> sortedVector{get_values_using_inorder_traversal(rootNode)};
    return sortedVector;
}

BinarySortTree& BinarySortTree::operator=(const BinarySortTree& otherTree)
{
    this->rootNode = copy_tree(otherTree.rootNode);

    return *this;
}

BinarySortTree& BinarySortTree::operator=(BinarySortTree&& otherTree)
{
    if(this->rootNode != nullptr)
    {
        clear_tree();
    }
    this->rootNode = otherTree.rootNode;
    otherTree.rootNode = nullptr;
    return *this;
}

void BinarySortTree::make_tree_from_vector(const std::vector<double> vectorThatWillBeTree)
{
    for (int i = 0; i < vectorThatWillBeTree.size(); i++)
    {
        insert_value(vectorThatWillBeTree[i]);
    }
}

