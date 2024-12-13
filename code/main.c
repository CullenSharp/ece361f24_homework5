/**
 * @file main.c
 * @brief 
 * The source file for the main application of ece361 hw5
 *
 * @version:	1.0.0
 * @author:		Cullen Sharp (cts6@pdx.edu)
 * @date: 		5-Dec-2024
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include "main.h"
#include "lib/iom361_r2/iom361_r2.h"

// global variables
uint32_t* io_base;

// Shuffles an array of dataItems
static void shuffle(DataItemPtr_t readings) {
    DataItem_t temp;
    int random_loc;
    for (int i = 0; i < DAYS; ++i) {
        random_loc = rand() % DAYS;
        temp = readings[random_loc];
        readings[random_loc] = readings[i];
        readings[i] = temp;
    }
}

int main() {
    int rtn_code, i;
    int secs, mins, hour, mday, mon, year;
    char date_time_buf[32] = {'\0'};
    char ch;
    struct tm date_time_str;
    TempHumidTreePtr_t tree = createTempHumidTree();

    // Init iom
    io_base = iom361_initialize(16,16,&rtn_code);
    if (rtn_code != 0) {
        printf("FATAL(main): Could not initialize I/O module\n");
		return 1;
	}
	printf("\n");

    // Seed random number generator
    srand(time(NULL));

    // greet the user and display the working directory for the application
    printf("ECE 361 - temp and humidity tree (cts6@pdx.edu)\n");
    errno = 0;
    char *buf = getcwd(NULL, 0);    // allocates a buffer large enough to hold the path
    
    if (buf == NULL) {
        perror("getcwd");
        printf("Could not display the path\n");
    }
    else {
        printf("Current working directory: %s\n", buf);
        free(buf);
    }
    printf("\n");

    populateBST(tree);

    while(1) {
        i = 0;
        printf("Enter timestamp (mm/dd/yyyy hh:mm:ss): ");
        while ((ch = getchar()) != '\n')
            date_time_buf[i++] = ch;

        date_time_buf[i] = '\0';

        if (date_time_buf[0] == '\0')
            break;
        
        sscanf(date_time_buf,
            " %2d / %2d / %4d %2d : %2d : %2d",
            &mon, &mday, &year, &hour, &mins, &secs);
        
        date_time_str.tm_year = year - 1900;
        date_time_str.tm_mon = mon - 1;
        date_time_str.tm_mday = mday;
        date_time_str.tm_hour = hour - 7;
        date_time_str.tm_min = mins;
        date_time_str.tm_sec = secs;
        date_time_str.tm_isdst = 1;
        search(tree, mktime(&date_time_str));
    }

    printf("Printing the whole table\n");
    inorder(tree);
    destroy(tree);

    printf("Thank you for using my program!\n");
    return 0;
}


void populateBST(TempHumidTreePtr_t tree) {
    DataItem_t readings[DAYS];
    struct tm time_str;
    time_str.tm_year = 2024 - 1900;
    time_str.tm_mon = 11 - 1;
    time_str.tm_mday = 1;
    time_str.tm_hour = 0;
    time_str.tm_min = 0;
    time_str.tm_sec = 1;
    time_str.tm_isdst = 1;

    if (io_base == NULL) {
        printf("ERROR: populateBST: base address does not exist.\n");
        return;
    }

    if (tree == NULL) {
        printf("ERROR: populateBST: tree does not exist.\n");
        return;
    }

    // Generate readings
    for (int day = 0; day < DAYS; ++day) {
        uint32_t temp_reg_val, humid_reg_val;
        _iom361_setSensor1_rndm(TEMP_RANGE_LOW, TEMP_RANGE_HI, HUMID_RANGE_LOW, HUMID_RANGE_HI);

        readings[day].timestamp = mktime(&time_str);
        time_str.tm_mday++;

        temp_reg_val = iom361_readReg(io_base, TEMP_REG, NULL);
        readings[day].temp = (temp_reg_val/ powf(2,20)) * 200.0 - 50;

        humid_reg_val = iom361_readReg(io_base, HUMID_REG, NULL);
        readings[day].humid = (humid_reg_val/powf(2,20)) * 100;
    }

    shuffle(readings);

    for (int i = 0; i < DAYS; ++i) {
        insert(tree, readings[i]);
    }
}