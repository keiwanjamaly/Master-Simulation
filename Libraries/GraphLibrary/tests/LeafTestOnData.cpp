//
// Created by Keiwan Jamaly on 18.10.22.
//
#include "gtest/gtest.h"
#include "Leaf.h"
#include "Types.h"
#include "TestData.h"

namespace dp {

    TEST(TestOnData, TestOnLine) {
        Leaf<Line> root = Leaf<Line>(0.0, 0.0, 2.0, split_decision);
        root.balance_tree(true);
        // nw   ne
        // sw   se
        root.balance_tree(true);
        // nw_nw, nw_ne, ne_nw, ne_ne
        // nw_sw, nw_se, ne_sw, ne_se
        // sw_nw, sw_ne, se_nw, se_ne
        // sw_sw, sw_se, se_sw, se_se
        root.balance_tree();

        // nw block
        // nw          , ne
        //             ,
        // sw          , (se_nw, se_ne)
        //             , (se_sw, se_se)

        Leaf<Line> nw_block = root.children[nw];
        ASSERT_EQ(nw_block.children[nw].children.size(), 0);
        ASSERT_EQ(nw_block.children[ne].children.size(), 0);
        ASSERT_EQ(nw_block.children[se].children.size(), 0);
        // the se part can or cannot be 0. This is based on the precision
        // of the floating point operation.

        // ne block
        // nw_nw, nw_ne, ne_nw, ne_ne
        // nw_sw, nw_se, ne_sw, ne_se
        // sw_nw, sw_ne, se_nw, se_ne
        // sw_sw, sw_se, se_sw, se_se
        Leaf<Line> ne_block = root.children[ne];
        ASSERT_EQ(ne_block.children[nw].children.size(), 4);
        ASSERT_EQ(ne_block.children[ne].children.size(), 4);
        ASSERT_EQ(ne_block.children[sw].children.size(), 4);
        ASSERT_EQ(ne_block.children[se].children.size(), 4);

        // sw block
        // nw_nw, nw_ne, ne_nw, ne_ne
        // nw_sw, nw_se, ne_sw, ne_se
        // sw_nw, sw_ne, se_nw, se_ne
        // sw_sw, sw_se, se_sw, se_se
        Leaf<Line> sw_block = root.children[sw];
        ASSERT_EQ(sw_block.children[nw].children.size(), 4);
        ASSERT_EQ(sw_block.children[ne].children.size(), 4);
        ASSERT_EQ(sw_block.children[sw].children.size(), 4);
        ASSERT_EQ(sw_block.children[se].children.size(), 4);

        // se block
        // (nw_nw, nw_ne), ne
        // (nw_sw, nw_se),
        // sw          , se
        //             ,
        Leaf<Line> se_block = root.children[se];
        // for nw same as for nw_block
        ASSERT_EQ(se_block.children[ne].children.size(), 0);
        ASSERT_EQ(se_block.children[sw].children.size(), 0);
        ASSERT_EQ(se_block.children[se].children.size(), 0);
    }
}
