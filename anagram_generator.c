//=======================================================================================
//=======================================================================================
//========	This program will find all of the permutations of a word without duplicates.
//========	By:		John Grant
//========	Date:		19 February 2015
//========	Requested by: 	-----------------
//=======================================================================================
//=======================================================================================
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

// GLOBAL VARIABLES
typedef int8_t bool;
#define true 1
#define false 0
int IDX = 0;

void swap(char *x, char *y);
char **findAnagrams(char *a);
bool dictionaryLookup(char* word);
void permute(char *a, int i, int n, char *merge);

int main() {
	int i, count = 0;
	bool word = false;

	// The longest word in English language has 45 char + 1 for null terminator.
	char* input = NULL;
	input = (char*)malloc(46*sizeof(char)); 
	if (input == NULL) {
		printf("ERROR RETURNED FROM [temp1]: NO MEMORY ALLOCATED\n");
		return -1;
	}

	while (word == false){
		printf("Enter a single word from the dictionary: ");
		scanf("%s", input);
		// Ask until an English word is entered.
		word = dictionaryLookup(input); 
		if (word == -1) {
			printf("Error from dictionary function in main");
			return -1;
		}
	}

	// Find all the anagrams to the input word, exit on error.
	char** temp = findAnagrams(input);
	if ((int)temp == -1)
		return -1;

	// Print out the permutations in the designated format.
	printf("[");
	for (i = 0; i < IDX; i++) {
		if (strcmp(temp[i], input) != 0) {
			printf("%s", temp[i]);
			count++;
			if (i != IDX - 1) printf(", ");
		}
		if (i != 0 && i % 14 == 0) printf("\n\t"); // To make more easy to read
	}
	printf("]\n");

	free(input);
	free(temp);
	input = NULL;
	temp = NULL;
	return 0;
}

//-----------------------------------------------------------------------
// A simple pass by reference function to swap characters. 
//-----------------------------------------------------------------------
void swap(char *x, char *y) {
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

//-----------------------------------------------------------------------
// A function that recursively (pre-order) finds all of the possible 
// permutations of a word and concatenates them into a single array of characters.
// Inputs:
// 	1. A String
// 	2. A starting point
// 	3. The ending point
//  4. A pointer to store the concatenation of all possible permutations
//-----------------------------------------------------------------------
void permute(char *a, int i, int n, char *merged) {
	int j;
	if (i == n) {
		// Concatenate all the permutations together.
		strncpy(&merged[IDX*n], a, n);
		IDX++;
	}
	else {
		for (j = i; j < n; j++) {
			// Go to the left side of recursive tree.
			swap((&a[i]), (&a[j]));

			// Begin the recursive call until the end (until a leaf).
			permute(a, i + 1, n, merged);

			// Go to the right side of recursive tree.
			swap((&a[i]), (&a[j]));
		}
	}
}

//-----------------------------------------------------------------------
// A function that receives all the possible permutations of a word into 
// an a 2D array and then cross references the words with a dictionary to 
// find all the possible anagrams that exists.
// Inputs:
// 	1. A String
// Return:
// 	Returns a pointer to an array of strings
// 		(an array of an array of characters).
//-----------------------------------------------------------------------
char** findAnagrams(char *a) {
	int len = strlen(a), fact = 1, i;

	// Finds the factorial of the word entered in order
	// to calculate how many permutations to receive
	// memory for.
	for (i = 1; i <= len; i++)
		fact = fact * i;

	// Allocates memory for the concatenated string.
	char* merged = (char*)malloc(fact*len);

	// Memory is allocated for the 2d array that will have
	// the permutations in list form.
	char** permutations = NULL;
	permutations = (char**)malloc(fact*sizeof(char*));  // Memory for height
	if (permutations == NULL) {
		printf("ERROR RETURNED FROM [permutation1]: NO MEMORY ALLOCATED\n");
		return (char**)-1;
	}
	for (i = 0; i<fact; i++) {
		*(permutations + i) = (char*)malloc((len+1)* sizeof(char)); // Memory for length
		if (permutations == NULL) {
			printf("ERROR RETURNED FROM [permutation2]: NO MEMORY ALLOCATED\n");
			return (char**)-1;
		}
	}

	// Memory is allocated for the 2d array that will have
	// the permutations dispose of duplicates in permutations.
	char** temp = NULL;
	temp = (char**)malloc(fact*sizeof(char*));  // Memory for height
	if (temp == NULL) {
		printf("ERROR RETURNED FROM [temp1]: NO MEMORY ALLOCATED\n");
		return (char**)-1;
	}
	for (i = 0; i<fact; i++) {
		*(temp + i) = (char*)malloc((len + 1)* sizeof(char)); // Memory for length
		if (temp == NULL) {
			printf("ERROR RETURNED FROM [permutation2]: NO MEMORY ALLOCATED\n");
			return (char**)-1;
		}
	}

	// Memory is allocated for the 2d array that will have
	// the anagrams in list form.
	char** anagrams = NULL;
	anagrams = (char**)malloc(fact*sizeof(char*));  // Memory for height
	if (anagrams == NULL) {
		printf("ERROR RETURNED FROM [anagrams1]: NO MEMORY ALLOCATED\n");
		return (char**)-1;
	}
	for (i = 0; i<fact; i++) {
		*(anagrams + i) = (char*)malloc((len + 1)* sizeof(char)); // Memory for length
		if (anagrams == NULL) {
			printf("ERROR RETURNED FROM [anagrams2]: NO MEMORY ALLOCATED\n");
			return (char**)-1;
		}
	}

	// Find all of the permutations of the entered word.
	permute(a, 0, len, merged);

	// Loop that separates the merged permutations into a 
	// double array of characters and adds a null terminator.
	for (i = 0, IDX = 0; i < fact; i++){
		int j;
		for (j = 0; j < len; j++){
			permutations[i][j] = merged[IDX];
			temp[i][j] = merged[IDX];
			permutations[i][j+1] = '\0';
			temp[i][j + 1] = '\0';
			IDX++;
		}
	}

	free(merged);
	merged = NULL;

	// Find all the duplicate words and change them to the entered word.
	for (i = 0; i < fact; i++) {
		bool flag = false;
		int j;
		for (j = 0; j < fact; j++) {
			if (strcmp(temp[i], permutations[j]) == 0) {
				if (flag == false)
					flag = true;
				else {
					permutations[i] = permutations[0];
				}
			}
		}
	}

	// Save all words except the entered word into a temp 2D array.
	for (i = 0, IDX = 0; i < fact; i++) {
		if (strcmp(permutations[i], permutations[0]) != 0) {
			strcpy(temp[IDX], permutations[i]);
			IDX++;
		}
	}

	// Search the dictionary for an anagram to each word in temp.
	int count = IDX;
	IDX = 0;
	for (i = 0; i < count; i++) {
		if (dictionaryLookup(temp[i])==true) {
			anagrams[IDX] = temp[i];
			IDX++;
		}
	}

	// Frees all memory that's not returned to main().
	free(temp);
	free(permutations);
	temp = NULL;
	permutations = NULL;
	return anagrams;
}

bool dictionaryLookup(char* word) {
	FILE* file = fopen("/usr/share/dict/american-english", "r"); /* should check the result */
	if (file == NULL) {
		printf("Error when opening the dictionary!\n");
		return -1;
	}
	char* line = NULL;
	line = (char*)malloc(46*sizeof(char)); 
	if (line == NULL) {
		printf("ERROR RETURNED FROM [temp1]: NO MEMORY ALLOCATED\n");
		return -1;
	}

	while (fgets(line, sizeof(line), file)) {
		if (line == NULL) {
			printf("Error getting line!\n");
			fclose(file);
			free(line);
			line = NULL;
			return -1;
		}
		int i = strncmp(word, line, strlen(word));
		if (i == 0) {
			fclose(file);
			free(line);
			line = NULL;
			return true; 
		}
	}

	fclose(file);
	free(line);
	line = NULL;
	return false;
}
