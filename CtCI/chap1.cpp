#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//1.1
// init bitmap after creating
// while(*str), not while(str)
#define ASCII_CODE_SIZE		128
bool isUnique(char* str)
{
	bool* found = (bool*)malloc(sizeof(bool) * ASCII_CODE_SIZE);

	if (found) {
		memset(found, 0, sizeof(bool) * ASCII_CODE_SIZE);
	}
	else {
		return false;
	}

	while (*str) {
		if (found[*str] == true) {
			return false;
		}
		found[*str] = true;
		str++;
	}

	return true;
}

//1.2
// is each character unique ? boolean type if yes, int type if no.
bool isPermutation(char* strA, char* strB)
{
	int* charBin = (int*)malloc(sizeof(int) * ASCII_CODE_SIZE);
	int lenA = strlen(strA);
	int lenB = strlen(strB);

	if (charBin) {
		memset(charBin, 0, sizeof(int) * ASCII_CODE_SIZE);
	}
	else {
		return false;
	}

	if ((lenA != lenB) || (lenA == 0) ) {
		return false;
	}

	while (*strA) {
		charBin[*strA]++;
		strA++;
	}

	while (*strB) {
		charBin[*strB]--;
		if (charBin[*strB] < 0) {
			return false;
		}
		strB++;
	}

	return true;
}

//1.4
// is null string a palindrome ? 
// reinit ptr after string reaches '/0' -> or use for instead while w/ str++
bool isPalindromePermutation(char* str)
{
	int* occurrence = (int*)malloc(sizeof(int) * ASCII_CODE_SIZE);
	int len = strlen(str);
	bool oddFound = false;

	if (occurrence) {
		memset(occurrence, 0, sizeof(int) * ASCII_CODE_SIZE);
	}
	else {
		return false;
	}

	// Counter
	//while (*str) {
	for(int i=0; i<len; i++) {
		occurrence[str[i]]++;
		//str++;	this will move ptr to '/0'
	}

	for (int i = 0; i < len; i++) {
		if ((occurrence[str[i]] & 1) != 0) {
			if (oddFound == true) {
				return false;
			}
			oddFound = true;
		}
	}

	return true;
}

#define MAX(A, B)		((A) > (B) ? (A) : (B))
#define ABS(A)			((A) > 0 ? (A) : (A) * (-1))

//1.5 char edit like insert, remove, or replace => same str?
// move next in one string only if lenA != lenB
// asdfjkl & asejkl : 2 edits away(replace & insert) -> needs 'continue'
bool isOneEditAway(char* strA, char* strB)
{
	int lenA = strlen(strA);
	int lenB = strlen(strB);

	bool mismatchFound = false;

	// same or +/-1
	if (ABS(lenA - lenB) > 1) {
		printf("%d %d\n", lenA, lenB);
		return false;
	}

	// count mismatches 
	while (*strA && *strB) {
		if (*strA != *strB) {
			printf("%c %c\n", *strA, *strB);
			if (mismatchFound == true) {
				return false;
			}

			mismatchFound = true;

			if (lenA > lenB) {
				strA++;
				continue;
			}
			else if (lenA < lenB){
				strB++;
				continue;
			}
			else {
				// same length : move both forward 
			}
		}
		
		strA++;
		strB++;
	}

	return true;
}

//1.6
// index should be the current one at the bottom of for loop. It will advance at the top of for loop.
char* string_compression(char* str)
{
	int len = strlen(str);
	char* res = (char*)malloc(sizeof(char) * len);
	int count;

	printf("%s\n", str);

	if (res) {
		memset(res, 0, sizeof(char) * len);
	}
	else {
		return NULL;
	}

	//          1      
	//0123456789012345
	//Hello, world!
	// 	i = 2, j = 3   -> i = 4
	// 	i = 2, j = 3~6 -> i = 7
	// aaa bbbbb c dddd ee fff k
	for (int i = 0; i < len; i++) {
		printf("%c", str[i]);
		count = 1;

		if (i == len - 1) {								// last charcter
			printf("%d ", count);
		} else {

			if (str[i] == str[i + 1]) {					// found repeating
				count = 2;
				int j;
				for (j = i + 1; j < len - 1; j++) {		// next one repeating ?
					if (str[j] == str[j + 1]) {
						count++;
					}
					else {
						break;							// no more repeating
					}
				}
				i = j;									// don't use i = j + 1. There's i++ above !!!
			}
			printf("%d ", count);
		}
	}

	return res;
}


//1.7 
// cw : transpose -> swap columns
// ccw: transpose -> reverse columns
/*
void rotate(vector<vector<int>>& matrix) {

}*/

//1.8
bool zero_matrix(int** matrix, int len)
{
	return true;
}

//1.9
bool string_rotation(char* stra, char* strb)
{
	return true;
}




int main()
{
	char astr[] = "asdfjkl";
	char bstr[] = "asefjkl";	// asefjkl
	char cstr[] = "aaabbbbbcddddeefffk"; // aaabbbbbcddddeefffk


// 1.1
	if (isUnique(cstr)) {
		printf("1.1 no dup found\n");
	}
	else {
		printf("1.1 dup found\n");
	}

// 1.2
	if (isPermutation(astr, bstr)) {
		printf("1.2 permutation\n");
	}
	else {
		printf("1.2 not permutation\n");
	}

// 1.4
	if (isPalindromePermutation(bstr)) {
		printf("1.4 permutation of palindrome\n");
	}
	else {
		printf("1.4 not permutation of palindrome\n");
	}

// 1.5
	if (isOneEditAway(astr, bstr)) {
		printf("1.5 one edit away\n");
	}
	else {
		printf("1.5 more than one edit away\n");
	}

// 1.6
	printf("\n1.6 %s", string_compression(cstr));


	return 0;
}