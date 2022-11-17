#include <boost/test/unit_test.hpp>

#include "Leaf.h"
#include "Types_Leaf.h"
#include "TestData.h"

namespace dp {

    using std::shared_ptr, std::make_shared;

    BOOST_AUTO_TEST_CASE(TestOnLine) {
        shared_ptr<Empty_Config> config = make_shared<Empty_Config>(Empty_Config());
        config->mode = 2;
        shared_ptr<CurrLeaf> root = make_shared<CurrLeaf>(CurrLeaf(0.0, 0.0, 2.0, split_decision, config));
        root->balance_tree(true);
        // nw   ne
        // sw   se
        root->balance_tree();
        // nw_nw, nw_ne, ne_nw, ne_ne
        // nw_sw, nw_se, ne_sw, ne_se
        // sw_nw, sw_ne, se_nw, se_ne
        // sw_sw, sw_se, se_sw, se_se
        root->balance_tree();

        // nw block
        // nw          , ne
        //             ,
        // sw          , (se_nw, se_ne)
        //             , (se_sw, se_se)

        shared_ptr<CurrLeaf> nw_block = root->children[nw];
        BOOST_CHECK_EQUAL(nw_block->children[nw]->children.size(), 0);
        BOOST_CHECK_EQUAL(nw_block->children[ne]->children.size(), 0);
        BOOST_CHECK_EQUAL(nw_block->children[sw]->children.size(), 0);
        // the se part can or cannot be 0. This is based on the precision
        // of the floating point operation.

        // ne block
        // nw_nw       , ne_nw, ne_ne
        //             , ne_sw, ne_se
        // sw_nw, sw_ne, se_nw, se_ne
        // sw_sw, sw_se, se_sw, se_se
        shared_ptr<CurrLeaf> ne_block = root->children[ne];
        BOOST_CHECK_EQUAL(ne_block->children[nw]->children.size(), 4);
        BOOST_CHECK_EQUAL(ne_block->children[ne]->children.size(), 4);
        BOOST_CHECK_EQUAL(ne_block->children[sw]->children.size(), 4);
        BOOST_CHECK_EQUAL(ne_block->children[se]->children.size(), 4);

        // sw block
        // nw          , ne_nw, ne_ne
        //             , ne_sw, ne_se
        // sw_nw, sw_ne, se_nw, se_ne
        // sw_sw, sw_se, se_sw, se_se
        shared_ptr<CurrLeaf> sw_block = root->children[sw];
        BOOST_CHECK_EQUAL(sw_block->children[nw]->children.size(), 4);
        BOOST_CHECK_EQUAL(sw_block->children[ne]->children.size(), 4);
        BOOST_CHECK_EQUAL(sw_block->children[sw]->children.size(), 4);
        BOOST_CHECK_EQUAL(sw_block->children[se]->children.size(), 4);

        // se block
        // (nw_nw, nw_ne), ne
        // (nw_sw, nw_se),
        // sw          , se
        //             ,
        shared_ptr<CurrLeaf> se_block = root->children[se];
        // for nw same as for nw_block
        BOOST_CHECK_EQUAL(se_block->children[se]->children.size(), 0);
        BOOST_CHECK_EQUAL(se_block->children[sw]->children.size(), 4);
        BOOST_CHECK_EQUAL(se_block->children[ne]->children.size(), 4);
    }
}
