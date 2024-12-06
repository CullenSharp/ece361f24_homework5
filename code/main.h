/**
 * @file main.h
 * @brief 
 * The header file for the main application of ece361 hw5
 *
 * @version:	1.0.0
 * @author:		Cullen Sharp (cts6@pdx.edu)
 * @date: 		5-Dec-2024
 */
#include <stdint.h>
#include "lib/temp_humid_tree/temp_humid_tree.h"

#ifndef _MAIN_H
#define _MAIN_H

// typedefs, enums and constants
#define TEMP_RANGE_LOW	42.0
#define TEMP_RANGE_HI	52.0
#define HUMID_RANGE_LOW	72.6
#define HUMID_RANGE_HI	87.3
#define DAYS 30

/**
 * Populates the BST with a month's worth of readings
 * 
 * @brief
 * Tasks: 
 *      1. generate 30 readings by interfacing with the iom361 module
 *      2. for each reading supply a timestamp utilizing time.h
 *      3. Store each one in an array
 *      4. Shuffle the array
 *      5. Insert into a bst utilizing temp_humid_tree.h
 * 
 * @param tree the pointer to the current tree instance
 */
void populateBST(TempHumidTreePtr_t tree);

#endif