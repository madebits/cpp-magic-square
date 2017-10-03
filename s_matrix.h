/*
 *	MagicSQ - Magic Square Filler.
 *	(c) 2000 by Vasian CEPA. All rights reserved.
 *	
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

/************************************************
 S_MATRIX class - A dynamic integer square matrix
 ************************************************/

typedef struct {
	int* m; /* we represent the matrix as a vector inside */
	int n;  /* private size of square matrix n*n          */
	int (*getElement)();
	void (*setElement)();
	int (*getSize)();
	void (*print)();
} S_MATRIX;

/* methods */

S_MATRIX* create_S_MATRIX(int dimension);
void destroy_S_MATRIX(S_MATRIX* m);

int getElement(S_MATRIX* m, int i, int j);
void setElement(S_MATRIX* m, int i, int j, int value);

int getSize(S_MATRIX* m);
void print(S_MATRIX* m);

/************************************************
 END of S_MATRIX class
 ************************************************/

