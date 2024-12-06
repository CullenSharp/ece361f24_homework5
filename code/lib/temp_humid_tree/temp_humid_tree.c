/**
 * @file temp_humid_tree.c
 * @brief 
 * This is source file for a binary search tree ADT targeted to the
 * Temp/Humidity BST from ECE 361 HW #5
 *
 * @version:	1.0.1	
 * @author:		Cullen Sharp (cts6@pdx.edu)
 * @date: 		5-Dec-2024
 *
 * @note code is based on the BinarySearchTree example used during
 * the ECE 361 lectures which is based on Karumanchi's example code
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "temp_humid_tree.h"

static void _inorder(BSTNodePtr_t root) {
    if (root == NULL)
        return;

    char date_time_buf[32];
    struct tm *date_time_str;
    date_time_str = gmtime(&root->data.timestamp);
    strftime(date_time_buf,
             sizeof(date_time_buf),
             "%a %b %_d %T %Y",
             date_time_str);

    _inorder(root->left); 
    printf("| %s | %3.1fC | %3.1f%%    |\n",
        date_time_buf, root->data.temp, root->data.humid); 
    _inorder(root->right);
}

static void _destroy(BSTNodePtr_t root) {
    if (root == NULL)
        return;

    _destroy(root->left);
    _destroy(root->right);

    free(root);
}

TempHumidTreePtr_t createTempHumidTree(void) {
    TempHumidTreePtr_t tree = malloc(sizeof(TempHumidTree_t));
    if (tree == NULL) {
        printf("ERROR: temp_humid_tree(create): Could not create tree\n");
        return NULL;
    }

    tree->n = 0;
    tree->root = NULL;
    return tree;
}

BSTNodePtr_t insert(TempHumidTreePtr_t tree, DataItem_t info) {
    BSTNodePtr_t tempNode = malloc(sizeof(BSTNode_t));
    if (tempNode == NULL) {
        printf("ERROR: temp_humid_tree(insert): failed to allocate new node\n");
        return NULL;
    }

    if (tree == NULL) {
        printf("ERROR: temp_humid_tree(insert): tree does not exist\n");
        return NULL;
    }

    BSTNodePtr_t current;
    BSTNodePtr_t parent;

    tempNode->data = info;
    tempNode->left = NULL;
    tempNode->right = NULL;

    // If empty, put at root
    if (tree->root == NULL) {
        tree->root = tempNode;
        return tempNode;
    } else {
        current = tree->root;
        parent = NULL;

        while(1) {
            parent = current;

            // If less than, go left
            if (tempNode->data.timestamp < parent->data.timestamp) {
                current = current->left;

                if (current == NULL) {
                    parent->left = tempNode;
                    return tempNode;
                }
            } else {
                current = current->right;
                if (current == NULL) {
                    parent->right = tempNode;
                    return tempNode;
                }
            }
        }
    }
}

BSTNodePtr_t search(TempHumidTreePtr_t tree, time_t timestamp) {
    char date_time_buf[32];
    struct tm *date_time_str;
    date_time_str = gmtime(&timestamp);
    strftime(date_time_buf,
             sizeof(date_time_buf),
             "%a %b %_d %T %Y",
             date_time_str);

    if (tree == NULL) {
        printf("ERROR: temp_humid_tree(search): tree does not exist\n");
        return NULL;
    }

    BSTNodePtr_t current = tree->root;
    printf("Searching\n");

    while(current->data.timestamp != timestamp) {
        if (current->data.timestamp > timestamp) {
            current = current->left;
        } else {
            current = current->right;
        }

        if (current == NULL) {
            printf("Did not find data for timestamp %s\n", date_time_buf);
            return NULL;
        }
    }

    printf("FOUND! %s\n", date_time_buf);
    return current;
}

void inorder(TempHumidTreePtr_t tree) {
    if (tree == NULL) {
        printf("ERROR: temp_humid_tree(inorder): tree does not exist.\n");
        return;
    }

    if (tree->root == NULL) {
        printf("ERROR: temp_humid_tree(inorder): tree is unpopulated.\n");
        return;
    }
    printf("+---------------------------------------------+\n");
    printf("| Date                     | Temp  | Humidity |\n");
    printf("+---------------------------------------------+\n");
    _inorder(tree->root);
    printf("+---------------------------------------------+\n");
}

void destroy(TempHumidTreePtr_t tree) {
    if (tree == NULL)
        return;
    
    _destroy(tree->root);
    free(tree);
}