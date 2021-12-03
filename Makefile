# Make environment
CC=gcc
CFLAGS=-g -Wall

# files
TARGET=		anagram_generator

SOURCES=	permutation_generator.c

$(TARGET) : $(TARGET)
	$(CC) $(CFLAGS) -o $@ $(SOURCES)

clean : 
	rm -f $(TARGET) 
