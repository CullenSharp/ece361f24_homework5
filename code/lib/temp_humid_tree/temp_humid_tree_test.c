/**
 * @file temp_humid_tree_test.c
 * @brief 
 * A minimal testbench for a binary search tree ADT targeted to the
 * Temp/Humidity BST from ECE 361 HW #5
 *
 * @version:	1.0.0
 * @author:		Cullen Sharp (cts6@pdx.edu)
 * @date: 		5-Dec-2024
 */

#include <stdio.h>
#include <time.h>
#include "temp_humid_tree.h"

int main() {
    TempHumidTreePtr_t tree = NULL;
    DataItem_t test = {
        .timestamp = (time_t) 1728842051,
        .humid = 0.55,
        .temp = 42.3
    };


    // test the null cases
    insert(tree, test);
    search(tree, (time_t) 1728842051);
    inorder(tree);
    destroy(tree);
    putchar('\n');

    // Load test data
    DataItem_t test_data[] = {
        [0].timestamp = (time_t) 1728842051,
        [0].humid = 2.45,
        [0].temp = 25.4,
        [1].timestamp = (time_t) 1572523110,
        [1].humid = 45.45,
        [1].temp = 25.4,
        [2].timestamp = (time_t) 1828842051,
        [2].humid = 20.45,
        [2].temp = 25.4,
        [3].timestamp = (time_t) 1838842051,
        [3].humid = 35.45,
        [3].temp = 2.4,
        [4].timestamp = (time_t) 1628842051,
        [4].humid = 0.45,
        [4].temp = 25.4,
    };

    // Initialize tree
    tree = createTempHumidTree();

    // Load with test cases
    for (int i = 0; i < 5; ++i)
        insert(tree, test_data[i]);

    // Test search
    for (int i = 0; i < 5; ++i)
        search(tree, test_data[i].timestamp);
    putchar('\n');

    // Test some cases not found in tree
    search(tree, (time_t) 0);
    search(tree, (time_t) 1628842052);
    putchar('\n');

    // Test inorder
    inorder(tree);

    // Clean up
    destroy(tree);
}