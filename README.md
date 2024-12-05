# ECE 361 Homework 5

## Overview

As I see it, there are three main sections to this assignment: 

### Implementing a binary search tree

The header file is located in the directory "roy_files". It's missing the implementation. Inspiration can be drawn from Karumanchi's binary search tree. Along the way comments should be added in the style of Doxygen. Once the implementation is done, the module should be **ran through a testbench**.

### Populating the BST

We then need to write a function `populateBST` that uses the `time.h` library and the `iom361` to generate a month's worth of timestamped temperature and humidity readings, then inserts the data into a binary search tree.

> **Note:** \
> It is not optimal to insert in order, so we'll shuffle the data first.

### Writing the main loop

The user is prompted to enter a date; the program then searches the BST; if found, print out the data, otherwise print a useful message. We'll terminate the main loop when the user enters a blank line.

## To Do

- Write the implementation for the BST
    - Review the provided code: Karumanchi's and Roy's
- Document the code
