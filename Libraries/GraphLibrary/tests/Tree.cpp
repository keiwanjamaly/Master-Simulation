#include <boost/test/unit_test.hpp>

#include "Tree.h"
#include "GraphLibrary_Types.h"

namespace gl {
    BOOST_AUTO_TEST_CASE(testConstructorOfTree) {
        shared_ptr<gl::Tree> tree_parent = make_shared<Tree>();
        shared_ptr<gl::Tree> tree_child = make_shared<Tree>(tree_parent);
        BOOST_TEST(tree_parent->getParent(), nullptr);
        BOOST_TEST(tree_child->getParent(), tree_parent);
    }

    BOOST_AUTO_TEST_CASE(testAttatchChildrenAndGetChild) {
        shared_ptr<gl::Tree> tree = make_shared<Tree>();

        // nullptr should be returned, if there are no children attached
        BOOST_TEST(tree->getChild(nw) == nullptr);
        BOOST_TEST(tree->getChild(ne) == nullptr);
        BOOST_TEST(tree->getChild(sw) == nullptr);
        BOOST_TEST(tree->getChild(se) == nullptr);

        // test that the correct amount of leafs is attached
        tree->attachLeaves();
        BOOST_TEST(tree->getChild(nw));
        BOOST_TEST(tree->getChild(ne));
        BOOST_TEST(tree->getChild(sw));
        BOOST_TEST(tree->getChild(se));

        // test that leafs are not attached twice
        BOOST_CHECK_THROW(tree->attachLeaves(), std::runtime_error);
    }

    BOOST_AUTO_TEST_CASE(testHasChildren) {
        shared_ptr<gl::Tree> tree = make_shared<Tree>();
        tree->attachLeaves();

        BOOST_TEST(tree->hasChildren() == true);
        BOOST_TEST(tree->getChild(nw)->hasChildren() == false);
    }

    BOOST_AUTO_TEST_CASE(testIsRoot) {
        shared_ptr<gl::Tree> tree = make_shared<Tree>();

        tree->attachLeaves();

        BOOST_TEST(tree->isRoot() == true);
        BOOST_TEST(tree->getChild(nw)->isRoot() == false);
        BOOST_TEST(tree->getChild(ne)->isRoot() == false);
        BOOST_TEST(tree->getChild(sw)->isRoot() == false);
        BOOST_TEST(tree->getChild(se)->isRoot() == false);
    }

    BOOST_AUTO_TEST_CASE(testGetChildOfParent) {
        shared_ptr<gl::Tree> tree = make_shared<Tree>();

        BOOST_CHECK_THROW(tree->getChildOfParent(nw), std::runtime_error);

        tree->attachLeaves();

        BOOST_TEST(tree->getChild(nw)->getChildOfParent(nw) == tree->getChild(nw));
        BOOST_TEST(tree->getChild(nw)->getChildOfParent(ne) == tree->getChild(ne));
        BOOST_TEST(tree->getChild(nw)->getChildOfParent(sw) == tree->getChild(sw));
        BOOST_TEST(tree->getChild(nw)->getChildOfParent(se) == tree->getChild(se));
    }

    BOOST_AUTO_TEST_CASE(testGetAllLeafs) {
        shared_ptr<gl::Tree> tree = make_shared<Tree>();
        tree->attachLeaves();

        vector<shared_ptr<gl::Tree>> allLeafs;
        tree->getAllLeafs(allLeafs);
        vector<shared_ptr<gl::Tree>> referenceVector = {tree,
                                                        tree->getChild(nw),
                                                        tree->getChild(ne),
                                                        tree->getChild(sw),
                                                        tree->getChild(se)};

        BOOST_CHECK_EQUAL_COLLECTIONS(allLeafs.begin(), allLeafs.end(), referenceVector.begin(), referenceVector.end());
    }

    BOOST_AUTO_TEST_CASE(testGetDepth) {
        shared_ptr<gl::Tree> tree = make_shared<Tree>();
        tree->attachLeaves();

        BOOST_TEST(tree->getDepth() == 0);
        BOOST_TEST(tree->getChild(nw)->getDepth() == 1);
    }
}

