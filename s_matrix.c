/*
 *	MagicSQ - Magic Square Filler.
 *	(c) 2000 by Vasian CEPA. All rights reserved.
 *	
 */

#include "s_matrix.h"

/*****************************************
 Start of S_MATRIX class member functions:
 *****************************************/
/* private methods */
static void setSize(S_MATRIX* , int);
#ifdef DEBUG
static void checkBound(S_MATRIX* , int, int);
#endif

/* constructor */
S_MATRIX* create_S_MATRIX(int dimension){
	S_MATRIX* m = NULL;
	if(dimension < 1) return NULL;
	m = (S_MATRIX*)malloc(sizeof(S_MATRIX));
	if(m == NULL) return m;
	m->getElement = &getElement;
	m->setElement = &setElement;
	m->getSize = &getSize;
	m->print = &print;
	m->m = (int*)malloc(dimension * dimension * sizeof(int));
	if(m->m == NULL){
		setSize(m,0);
		puts("Oops! Allocation of memory failed!");
	} else{
	   	setSize(m, dimension);
		memset((void*)m->m, 0, dimension * dimension * sizeof(int));
	}
	return m;
}

/* destructor */
void destroy_S_MATRIX(S_MATRIX* m){
	if(m == NULL) return;
	if(m->getSize(m) != 0)
		free((void*)m->m);
	free((void*)m);
}

int getElement(S_MATRIX* m, int i, int j){
	#ifdef DEBUG
		checkBound(m, i, j);
	#endif
	return *(m->m + i*(m->getSize(m)) + j);
}

void setElement(S_MATRIX* m, int i, int j, int value){
	int p = 0;
	#ifdef DEBUG
		checkBound(m, i, j);
	#endif
	p = (i * m->getSize(m) + j);
	*( m->m + p) = value;
}

/* it is an integer square matrix */
int getSize(S_MATRIX* m){
	return m->n;
}

/* private */
static void setSize(S_MATRIX* m, int n){
	m->n = n;
}

#ifdef DEBUG
/* private */
static void checkBound(S_MATRIX* m, int i, int j){
	int ib = (i<0 || i > m->n - 1) ? 0 : 1;
	int jb = (i<0 || i > m->n - 1) ? 0 : 1;
	if(!ib || !jb){
		fprintf(stderr,"Array Index Out of Bounds! (%d, %d)", i, j);
		destroy_S_MATRIX(m);
		exit(2);
	}
}
#endif

void print(S_MATRIX* m){
	int i,j;
	int n = m->getSize(m);
	fprintf(stderr,"MagicSQ - (c) 2000 by Vasian CEPA - \n");
	for(i = 0; i<n; i++){
		printf("\n");
		for(j=0; j< n; j++){
			char *f;
			if(j == n - 1)
				f = "%d";
			else
				f = "%d,";
			printf(f, m->getElement(m,i,j));
		}
	}
}

/*************************************
 END of S_MATRIX class implementation.
 *************************************/

