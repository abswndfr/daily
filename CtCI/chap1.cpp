#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//1.1
// init bitmap after creating
// while(*str), not while(str)
// A = 0;  (A--) < 0 ? true : false;  -> false !!!!.  use A--; A < 0 ? true : false !!!!!
#define ASCII_CODE_SIZE		128
bool isUnique(char* str)
{
	bool* isFound = (bool*)malloc(sizeof(bool) * ASCII_CODE_SIZE);

	if (isFound) {
		memset(isFound, false, sizeof(bool) * ASCII_CODE_SIZE);
	}
	else {
		//
	}

	while (*str) {
		if (isFound[*str] == true) {
			return false;
		}
		else {
			isFound[*str] = true;
		}

		str++;
	}

	return true;
}

//1.2
// is each character unique ? boolean type if yes, int type if no.
bool isPermutation(char* strA, char* strB)
{
	int* charBin = (int*)malloc(sizeof(int) * ASCII_CODE_SIZE);
	if (charBin) {
		memset(charBin, 0, sizeof(int) * ASCII_CODE_SIZE);
	}

	while (*strA) {
		charBin[*strA]++;
		strA++;
	}

	while (*strB) {
		charBin[*strB]--;
		if ((charBin[*strB]) < 0) {
			return false;
		}
		strB++;
	}

	return true;
}

//1.4
// is null string a palindrome ? 
// init bitmap after creating
// reinit ptr after string reaches '/0' -> or use for instead while w/ str++
bool isPalindromePermutation(char* str)
{
	char* tmp = str;
	int* charBin = (int*)malloc(sizeof(int) * ASCII_CODE_SIZE);
	memset(charBin, 0, sizeof(int) * ASCII_CODE_SIZE);

	bool isOddFound = false;

	while (*tmp) {
		charBin[*tmp]++;
		tmp++;
	}

	while (*str) {
		if (charBin[*str] & 1) {
			if (isOddFound) {
				return false;
			}
			else {
				isOddFound = true;
			}
		}
		str++;
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
	bool isDiffFound = false;

	if (ABS(strlen(strA) - strlen(strB)) > 1) {
		return false;
	}
	else {
		while (*strA && *strB) {
			//printf("%c %c\n", *strA, *strB);
			if (*strA != *strB) {
				if (isDiffFound == true) {
					return false;
				}
				else {
					isDiffFound = true;
				}
				
				if ((*(strA+1) == *strB)) {
					strA++;
					continue;
				}
				else if (*(strA) == *(strB+1)) {
					strB++;
					continue;
				}
			}
			strA++;
			strB++;
		}
	}

	return true;
}

//1.6
// index should be the current one at the bottom of for loop. It will advance at the top of for loop.
// count is already 2 if 1st matching is found
//
// helllo, world!
// 01234567890123
//   i
//    jj
//     i
//  aaa bbbbb c  dddd ee fff k
//  a3  b5    c1 d4   e2 f3 k1
char* string_compression(char* str)
{
	int count = 0;
	int len = strlen(str);
	char* res = (char*)malloc(sizeof(len));
	int index = 0;

	for (int i = 0; i < len; i++) {
		count = 1;
		//printf("%c", str[i]);
		res[index] = str[i];
		index++;

		if (i == len-1) {
		}
		else {
			if (str[i] == str[i + 1]) {
				count = 2;
				for (int j = i + 1; j < len - 1; j++) {
					if (str[j] == str[j + 1]) {
						count++;
					}
					else {
						i = j;
						break;
					}
				}
			}
		}
		//printf("%d", count);
		//_itoa(count, &res[index], 10);
		res[index] = count + '0';
		index++;
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
	if (isUnique(astr)) {
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
