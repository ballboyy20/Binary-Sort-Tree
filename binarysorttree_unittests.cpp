#include "gtest/gtest.h"
#include "node.hpp"
#include "binarysorttree.hpp"
#include "BSTutils.hpp"


class BinarySortTreeSpy: public BinarySortTree
{
public:
    Node* get_root()
    {
        return rootNode;
    }
    void set_root(Node *node)
    {
        rootNode = node;
    }
};

class NodeForTestingDelete:public Node
{
public:

    NodeForTestingDelete(double valueInsideTestingDeleteNode): Node {privateValueInTheNode} {}

    ~NodeForTestingDelete()
    {
        numberDeleted++;
    }

    static int get_number_deleted()
    {
        return numberDeleted;
    }

protected:
    static int numberDeleted;
};

int NodeForTestingDelete::numberDeleted{0}; //Static Varibles need to be define and intitalized outside the class

class PreBuiltTree:public testing::Test
{
public:
    PreBuiltTree()
    {
        node7 = new Node{7};
        node5 = new Node{5};
        node10 = new Node{10};
        node4 = new Node{4};

        testingTree.set_root(node7);
        Node* root{testingTree.get_root()};
        root->set_left_child(node5);
        root->set_right_child(node10);
        root->get_left_child()->set_left_child(node4);
    }

    void TearDown()
    {
        testingTree.set_root(nullptr);
    }

    virtual ~PreBuiltTree()
    {
        delete node7;
        delete node5;
        delete node4;
        delete node10;
    }

protected:
    BinarySortTreeSpy testingTree;
    Node* node7{nullptr};
    Node* node5{nullptr};
    Node* node10{nullptr};
    Node* node4{nullptr};
};




class PreBuiltTreeToDelete:public testing::Test
{
public:
    PreBuiltTreeToDelete()
    {
        testingTree.set_root(new NodeForTestingDelete{7});
        Node* root{testingTree.get_root()};
        root->set_left_child(new NodeForTestingDelete{5});
        root->set_right_child(new NodeForTestingDelete{10});
    }
protected:
    BinarySortTreeSpy testingTree;
};




class PreBuiltTreeForTestingMove:public testing::Test
{
public:
    PreBuiltTreeForTestingMove()
    {
        node7 = new Node{7};
        node5 = new Node{5};
        node3 = new Node{3};

        testingTree.set_root(node7);
        Node* root{testingTree.get_root()};
        root->set_left_child(node5);
        root->set_right_child(node3);
    }
    void TearDown()
    {
        testingTree.set_root(nullptr);
    }
protected:
    BinarySortTreeSpy testingTree;
    Node* node7{nullptr};
    Node* node5{nullptr};
    Node* node3{nullptr};
};

TEST(BSTInsert, GiveATreeWithARootAndLeftChild_WhenInsertedingALesserValue_ExpectLeftGrandkidIsNotNullAndHasCorrectValue)
{
    BinarySortTreeSpy tree;
    Node* root = new Node{3};
    tree.set_root(root);
    double value{2};

    tree.insert_value(value);

    ASSERT_TRUE(tree.get_root()->get_left_child() != nullptr);
    EXPECT_EQ(value, tree.get_root()->get_left_child()->get_value());

    delete root->get_left_child();
    delete root;
    tree.set_root(nullptr);
}

TEST(BSTInsert, GiveATreeWithARootAndRightChild_WhenInsertingAGreaterValue_ExpectRightChildIsNotNullAndHasCorrectValue)
{
    BinarySortTreeSpy testingTree;
    Node* root = new Node{3};
    testingTree.set_root(root);
    double testingValue{4};

    testingTree.insert_value(testingValue);

    ASSERT_TRUE(testingTree.get_root()->get_right_child() != nullptr);
    EXPECT_EQ(testingValue, testingTree.get_root()->get_right_child()->get_value());

    delete root->get_right_child();
    delete root;
    testingTree.set_root(nullptr);
}

TEST(BSTInsert, GiveATreeWithARootAndRightChild_WhenInsertedingAGreaterValueToATreeWithTwoValuesAlready_ExpectRightGrandkidIsNotNullAndHasCorrectValue)
{
    BinarySortTreeSpy testingTree;
    Node* root = new Node{3};
    testingTree.set_root(root);
    double testingValue{4};
    double testingValueTwo{6};

    testingTree.insert_value(testingValue);

    ASSERT_TRUE(testingTree.get_root()->get_right_child() != nullptr);

    EXPECT_EQ(testingValue, testingTree.get_root()->get_right_child()->get_value());

    delete root->get_right_child();
    delete root;
    testingTree.set_root(nullptr);
}

TEST_F(PreBuiltTree, GivenAPreBuiltTree_WhenLookingForARoot_ExpectCorrectValueForRoot)
{
    ASSERT_TRUE(testingTree.get_root()->get_value() == node7->get_value());\
    TearDown();
}

TEST_F(PreBuiltTree, GivenAPreBuiltTree_WhenLookingForARightChildOfTheRoot_ExpectCorrectValueForRightChild)
{
    ASSERT_TRUE(testingTree.get_root()->get_right_child()->get_value() == node10->get_value());
    TearDown();
}

TEST_F(PreBuiltTree, GivenAPreBuiltTree_WhenLookingForALeftChildOfTheRoot_ExpectCorrectValueForLeftChild)
{
    ASSERT_TRUE(testingTree.get_root()->get_left_child()->get_value() == node5->get_value());
    TearDown();
}

TEST_F(PreBuiltTree, GivenAPreBuiltTree_WhenLookingForALeftGrandChildOfTheRoot_ExpectCorrectValueForGrandLeftChild)
{
    ASSERT_TRUE(testingTree.get_root()->get_left_child()->get_left_child()->get_value() == node4->get_value());
    TearDown();
}

TEST_F(PreBuiltTree, GivenAPreBuiltTree_WhenInsertingALargerValue_ExpectCorrectValueInCorrectPlace_ORIGINAL)
{
    double testingValue{11};
    testingTree.insert_value(testingValue);
    ASSERT_TRUE(testingTree.get_root()->get_right_child()->get_right_child()->get_value() == testingValue);
    EXPECT_EQ(11, testingTree.get_root()->get_right_child()->get_right_child()->get_value());
    delete testingTree.get_root()->get_right_child()->get_right_child();
    TearDown();
}

TEST_F(PreBuiltTree, GivenAPreBuiltTree_WhenInsertingALesserValue_ExpectCorrectValueInCorrectPlace)
{
    double testingValue{2};
    testingTree.insert_value(testingValue);
    ASSERT_TRUE(testingTree.get_root()->get_left_child()->get_left_child()->get_left_child() != nullptr);
    EXPECT_EQ(testingValue, testingTree.get_root()->get_left_child()->get_left_child()->get_left_child()->get_value());
    delete testingTree.get_root()->get_right_child()->get_left_child();
    TearDown();
}

TEST_F(PreBuiltTree, GivenAPreBuiltTree_WhenInsertingALesserValue_ExpectCorrectValueInCorrectPlace_Testingtest)
{
    double testingValue{2};
    double testingValueTwo{3};
    testingTree.insert_value(testingValue);
    testingTree.insert_value(testingValueTwo);
    ASSERT_TRUE(testingTree.get_root()->get_left_child()->get_left_child()->get_left_child() != nullptr);
    EXPECT_EQ(testingValue, testingTree.get_root()->get_left_child()->get_left_child()->get_left_child()->get_value());

    ASSERT_TRUE(testingTree.get_root()->get_left_child()->get_left_child()->get_left_child()->get_right_child() != nullptr);
    EXPECT_EQ(testingValueTwo, testingTree.get_root()->get_left_child()->get_left_child()->get_left_child()->get_right_child()->get_value());

    delete testingTree.get_root()->get_left_child()->get_left_child()->get_right_child();
    delete testingTree.get_root()->get_right_child()->get_left_child();
    TearDown();
}

TEST_F(PreBuiltTree, GivenAPreBuiltTree_WhenYouHaveAFewValuesInTheTree_ExpectValuesToComeBackInNumericalOrder)
{
    std::vector<double> testingSortedVectorValuesFromTestFixture{node4->get_value(),node5->get_value(),node7->get_value(),node10->get_value()};
    std::vector<double> testingSortedVectorValuesFromFunction{testingTree.get_sorted_values()};
    ASSERT_EQ(testingSortedVectorValuesFromFunction , testingSortedVectorValuesFromTestFixture);
}

TEST_F(PreBuiltTree, GivenAPreBuiltTreeAndAVectorOfDoubles_WhenWePassVectorIntoFunction_ExpectTheTreesToBeEqual)
{
    std::vector<double> testingVector{node7->get_value(),node5->get_value(),node10->get_value(),node4->get_value()};
    BinarySortTreeSpy makeTreeFromVectorFunctionTestingTree;
    makeTreeFromVectorFunctionTestingTree.make_tree_from_vector(testingVector);

    std::vector<double> testingVectorValuesFromTestFixture{testingTree.get_sorted_values()};
    std::vector<double> testingVectorValuesFromFunction{makeTreeFromVectorFunctionTestingTree.get_sorted_values()};
    ASSERT_EQ(testingVectorValuesFromFunction , testingVectorValuesFromTestFixture);

    delete makeTreeFromVectorFunctionTestingTree.get_root();
    makeTreeFromVectorFunctionTestingTree.set_root(nullptr);
    TearDown();
}

TEST_F(PreBuiltTreeToDelete, GivenAPreBuiltTreeAndVectorOfDoubles_ExpectTheCounterToBeEqualToTheAmountOfNodesInTree)
{
    int amountOfNodesThatShouldBeDeleted{3};
    testingTree.clear_tree();
    EXPECT_EQ(nullptr, testingTree.get_root());
    EXPECT_EQ(amountOfNodesThatShouldBeDeleted, NodeForTestingDelete::get_number_deleted());
}

TEST_F(PreBuiltTree, GivenABSTSpyAndPreBuiltTree_WhenBSTSpyIsInitializedAsAPreBuiltTree_ExpectTheRootNodeValuesAndValuesInOrderToBeIdentical)
{
    BinarySortTreeSpy newCopiedTree(testingTree);
    ASSERT_EQ(testingTree.get_root()->get_value() , newCopiedTree.get_root()->get_value());
    ASSERT_EQ(testingTree.get_sorted_values() , newCopiedTree.get_sorted_values());
    TearDown();
}

TEST_F(PreBuiltTree, GivenAPreBuiltTreeAndAnotherTree_WhenSettingThemEqualToEachOther_ExpectTheRootNodeValuesAndValuesInOrderToBeIdentical)
{
    BinarySortTreeSpy newCopiedTree;
    newCopiedTree = testingTree;
    ASSERT_EQ(testingTree.get_root()->get_value() , newCopiedTree.get_root()->get_value());
    ASSERT_EQ(testingTree.get_sorted_values() , newCopiedTree.get_sorted_values());
    TearDown();
}

TEST_F(PreBuiltTreeToDelete, GivenAPreBuiltTreeAndNewTree_WhenPreBuiltTreeWillBeMovedToNewTreeUsingOperator_ExpectNewTreeToHaveSameValueInRootNodeThatPreBuiltTreeToDeleteHas)
{
    BinarySortTreeSpy newTree;

    double tempValueHolderForTesting{testingTree.get_root()->get_value()};

    newTree = std::move(testingTree);

    double tempValueHolderForTestingTwo{newTree.get_root()->get_value()};

    ASSERT_EQ(tempValueHolderForTestingTwo , tempValueHolderForTesting);
}

TEST_F(PreBuiltTreeForTestingMove, GivenAPreBuiltTreeForTestingMoveAndNewTree_WhenPreBuiltTreeForTestingMoveWillBeMovedToNewTree_ExpectSortedValuesToBeTheSame)
{
    BinarySortTreeSpy newTree;

    std::vector <double> testingTreeSortedValues{testingTree.get_sorted_values()};

    newTree = std::move(testingTree);

    std::vector<double> newTreeSortedValues{newTree.get_sorted_values()};

    ASSERT_EQ(testingTreeSortedValues, newTreeSortedValues);

    TearDown();
}

TEST_F(PreBuiltTreeToDelete, GivenAPreBuiltTreeAndNewTree_WhenPreBuiltTreeWillBeMovedToNewTreeUsingConstructor_ExpectNewTreeToHaveSameValueInRootNodeThatPreBuiltTreeToDeleteHas)
{

    double tempValueHolderForTesting{testingTree.get_root()->get_value()};

    BinarySortTreeSpy newTree(testingTree);

    double tempValueHolderForTestingTwo{newTree.get_root()->get_value()};

    ASSERT_EQ(tempValueHolderForTestingTwo , tempValueHolderForTesting);
}

TEST_F(PreBuiltTreeForTestingMove, GivenAPreBuiltTreeForTestingMoveAndNewTree_WhenPreBuiltTreeForTestingMoveWillBeMovedToNewTreeUsingConstructor_ExpectSortedValuesToBeTheSame)
{
    std::vector <double> testingTreeSortedValues{testingTree.get_sorted_values()};

    BinarySortTreeSpy newTree(testingTree);

    std::vector<double> newTreeSortedValues{newTree.get_sorted_values()};

    ASSERT_EQ(testingTreeSortedValues, newTreeSortedValues);

    TearDown();
}
