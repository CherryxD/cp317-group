#pragma once
#include <stdio.h>
#include <stdlib.h>
// Fills a character array with a given character. 
// character is the character to repeat. 
// length is the number of times to repeat the character. 
// string is a character array to be filled with the character. 
// Returns a pointer to the filled character array. 
char* repeat(char character, int length, char* string); 
// Concatenates the source string onto the end of the destination string.
// destination is the string to be added to. 
// source is the string to be appended onto the destination string. 
// Returns a pointer to - modified destination string. 
char* concatenate(char* destination, char* source); 
// Scans a string and finds the index of the first occurence of a character. 
// str is the string to be scanned. 
// character is the character to scan for. 
// Returns the index of the first occurence of the character. Returns -1 if 
// the character is not found. 
int getIndex(char* string, char character); 
// Compares two strings.
// stringl is the first string.
// string2 is the second string.
// Returns -1 if stringl is less than string2, 0 if they are equal, and 1 if stringl is greater than string2. 
// A string is less than another string if it would appear earlier in a dictionary.
int compare(char* string1, char* string2); 
// Creates a string using dynamic memory allocation. 
// source is the string to be copied. 
// Returns a pointer to the newly created string. 
char* create(char* source); 
// Gets the length of a string. 
// string is the string to determine the length of. 
// Returns the length of the string. 
int getLength(char* string); 
// Returns a substring from a string. 
// string is the string to be processed. 
// start is the starting index (inclusve) of the substring. 
// end is the ending index (exclusive) of the substring. 
// destination is the string array to copy the substring to. 
// Returns a pc: - • - array. 
char* substring(char* source, int start, int end, char* destination); 
// Counts the number of instances of a given character in a string. 
// source is the string to be scanned. 
// character is the character to be scanned for.
// Returns the number of instances of the charcter. 
int countCharacter(char* source, char character); 
// Counts the number of substrings appearing in a source string. 
// source is the string to be scanned. 
// substring is the substring to search for. 
// Returns the number of instances of the substring. 
int countSubstring(char* source, char* substring); 
// Converts a string to upper case. 
// source is the string to convert. 
// Returns a pointer to the converted source string. 
// Note that only alpha characters are converted. Numeric and non-alphanumeric characters are unaffected. 
char* toUpper(char* source); 
// Converts a string to lower case. 
// source is the string to convert.
// Returns a pointer to the converted source string.
// Note that only alpha characters are converted. Numeric and non-alphanumeric characters are unaffected. 
char* toLower(char* source); 
// Swaps two strings. 
// strl is the first string. 
// str2 is the second string. 
void swap(char* str1, char* str2); 
// Sorts a string array. 
// stringArray is the string array to be sorted. 
// length is the length of the array. 
// type is the sorting type. 'a' for ascending, and 'd' for descending. 
// Returns a point,- ted string array. 
char** sort(char** stringArray, int length, char type); 

char* repeat(char character, int length, char* string) {
	for (int i = 0; i < length; i++) {
		string[i] = character;
    }
	string[length] = '\0';
	return string;
}

char* concatenate(char* destination, char* source) {
	int lenD, lenS;
	lenD = getLength(destination);
	lenS = getLength(source);
	for (int i = 0; source[i] != '\0'; i++) {
		destination[i+lenD] = source[i];
	}
	destination[lenD+lenS] = '\0';
	return destination;
}

int getIndex(char* string, char character) {
	int index = -1;
	for (int i = 0; string[i] != '\0'; i++) {
		if (string[i] == character) {
			index = i;
			break;
		}
	}
	return index;
}

int compare(char* string1, char* string2) {
	char* temp1 = malloc(sizeof(char)*64);
	temp1 = string1;
	temp1 = toLower(temp1);
	char* temp2 = malloc(sizeof(char)*64);
	temp2 = string2;
	temp2 = toLower(temp2);
	for (int i = 0; temp1[i] != '\0' && temp2[i] != '\0'; i++) {
		if (temp1[i] > temp2[i]) {
			return 1;
		}
		else if (temp2[i] > temp1[i]) {
			return -1;
		}
	}
	if (getLength(temp1) > getLength(temp2)) {
		return 1;
	}
	else if (getLength(temp1) < getLength(temp2)) {
		return -1;
	}
	free(temp1);
	free(temp2);
	return 0;
}

char* create(char* source) {
	int lenS = getLength(source);
	char* newS = malloc(sizeof(char) * (lenS + 1));
	for (int i = 0; i < lenS; i++) {
		newS[i] = source[i];
	}
	newS[lenS] = '\0';
	return newS;
}

int getLength(char* string) {
	int len = 0;
	for (int i = 0; string[i] != '\0'; i++) {
		len++;
	}
	return len;
}

char* substring(char* source, int start, int end, char* destination) {
	destination = malloc(sizeof(char) * (end - start));
	for (int i = start; i < end; i++) {
		destination[i - start] = source[i];
	}
	destination[end] = '\0';
	return destination;
}
 
int countCharacter(char* source, char character) {
	int output = 0;
	for (int i = 0; source[i] != '\0'; i++) {
		if (source[i] == character) {
			output += 1;
		}
	}
	return output;
}

int countSubstring(char* source, char* substringC) {
	int value;
	int lenSub = getLength(substringC);
	int lenSrc = getLength(source);
	char* moreSub = malloc(sizeof(char) * (lenSub));
	for (int i = 0; i <= (lenSrc - lenSub); i++) {
		moreSub = substring(source, i, i + lenSub, moreSub);
		if (compare(moreSub, substringC) == 0) {
			value ++;
		}
		free(moreSub);
	}
	return value;
}

char* toUpper(char* source) {
	int len = getLength(source);
	for(int i = 0; i < len; i++) {
		if (source[i] > 96 && source[i] < 123) {
			source[i] = source[i] - 32;
		}
	}
	return source;
}
 
char* toLower(char* source) {
	int len = getLength(source);
	for(int i = 0; i < len; i++) {
		if (source[i] > 64 && source[i] < 91) {
			source[i] = source[i] + 32;
		}
	}
	return source;
}

void swap(char* str1, char* str2) {
	char temp;
	int len1 = getLength(str1);
	int len2 = getLength(str2);
	int higher;
	if (len1 > len2) {
		str2 = realloc(str2, sizeof(char) * len1);
		str2[len1] = '\0';
		higher = len1;
	}
	else if (len2 > len1) {
		str1 = realloc(str1, sizeof(char) * len2);
		str1[len2] = '\0';
		higher = len2;
	}
	int i;
	for (i = 0; i < higher; i++) {
		temp = str1[i];
		str1[i] = str2[i];
		str2[i] = temp;
	}
}

char** sort(char** stringArray, int length, char type) {
	char* temp;
	int sort = 0;
	int i;
	int j;
	while (sort == 0) {
		sort = 1;
		for (i = 0; i < length - 1; i++) {
			j = 0;
			for (j = 0; j < length - 1; j++) {
				if (compare(stringArray[j], stringArray[j+1]) > 0) {
					temp = stringArray[j+1];
					stringArray[j+1] = stringArray[j];
					stringArray[j] = temp;
					sort = 0;
				}
			}
			if (type == 'd') {
				for (i = 0; i < length/2; i++) {
					temp = stringArray[j+1];
					stringArray[j+1] = stringArray[j];
					stringArray[j] = temp;
				}
			}
		}
	}
	return stringArray;
}