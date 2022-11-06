#ifndef NODE_HPP
#define NODE_HPP

class Node
{
public:
    Node(double constructorValueInsideTheNode);
    virtual ~Node() = default;

    Node* get_left_child() const;
    void set_left_child(Node *leftChild);

    Node* get_right_child() const;
    void set_right_child(Node *rightChild);

    double get_value() const;
    void set_value(double valueInsideTheNode);

protected:
    Node* privateLeftChild{nullptr};
    Node* privateRightChild{nullptr};
    double privateValueInTheNode{0.0};
};


#endif // NODE_HPP
