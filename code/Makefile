
CC = gcc
CFLAGS = -Wall -std=c99
IOM_DIR = lib/iom361_r2
RNDM_DIR = lib/random_float_generator
TREE_DIR = lib/temp_humid_tree
OBJECTS = main.o iom361_r2.o float_rndm.o temp_humid_tree.o
TARGET = temp_humid_test.out

$(TARGET) : $(OBJECTS)
	$(CC) -o $@ $^

main.o : main.c main.h
iom361_r2.o : $(IOM_DIR)/iom361_r2.c $(IOM_DIR)/iom361_r2.h
	$(CC) $(CFLAGS) -c $<

float_rndm.o : $(RNDM_DIR)/float_rndm.c $(RNDM_DIR)/float_rndm.h
	$(CC) $(CFLAGS) -c $<

temp_humid_tree.o : $(TREE_DIR)/temp_humid_tree.c \
					$(TREE_DIR)/temp_humid_tree.h
	$(CC) $(CFLAGS) -c $<

# Phony is used to label actions rather than targets
.Phony : clean
clean :
	rm $(OBJECTS) $(TARGET)