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

// Seed the random number generator
srand(time(NULL));

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
    int rtn_code;
    iom361_initialize(io_base, 16, 16, &rtn_code);

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

    // Init iom
    io_base = iom361_initialize(16, 16, &rtn_code);
    if (rtn_code != 0) {
        printf("FATAL(main): Could not initialize I/O module\n");
		return 1;
	}
	printf("\n");
    return 0;
}


populateBST(TempHumidTreePtr_t tree) {
    DataItem_t readings[DAYS];
    time_t date = 1730473635; // == nov 1 2024 8:07:15

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

        readings[day].timestamp = date;

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