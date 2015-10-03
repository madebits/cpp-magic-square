/*
 *	MagicSQ - Magic Square Filler.
 *	(c) 2000 by Vasian CEPA. All rights reserved.
 *	http://madebits.com
 */

#include "s_matrix.h"

void magic_fill(S_MATRIX*);
void printUsage(char*);

int main(int argc, char *argv[]){
	int dimension = 0;
	S_MATRIX* m = NULL;

	if (argc == 1) {
		printUsage(argv[0]);
		return 1;
	} else {
		dimension = atoi(argv[1]);
	}

	if(dimension <= 0 || dimension % 2 == 0){
		printUsage(argv[0]);
		return 1;
	}

	m = create_S_MATRIX(dimension);
	if(m == NULL){
	   fprintf(stderr, "\nOut of Memory Error! Aborting");
	   abort();
	}
	dimension = m->getSize(m);
	if(dimension == 0){
		fprintf(stderr, "\nOut of Memory Error! Aborting");
		destroy_S_MATRIX(m);
		abort();
	}

	magic_fill(m);
	m->print(m);
	destroy_S_MATRIX(m);
	return 0;
}

/* odd magic square fill logic */
void magic_fill(S_MATRIX* m){
	int i = 0, k = 0, j = 0;
	int n = m->getSize(m);
	int n2 = n*n;

	if(n == 0){
		puts("Oops! Empty matrix! Aborting!");
		return;
	}

	j = (n-1)/2;
	while(k++ < n2){
		#ifdef DEBUG
	   		fprintf(stderr,"(i,j)=[%d][%d] (%d)\n", i, j, k);
		#endif
		m->setElement(m,i,j,k);
		if(i==0){
			if(j == n - 1) i++;
			else{
				i = n - 1;
				j++;
			}
		} else {
			if(j == n - 1){
				i--;
				j = 0;
			} else {
				if(m->getElement(m,i-1,j+1) == 0){
					i--;
					j++;
				} else {
					i++;
				}
			}
		}
	}
}

/* simple help */
void printUsage(char *programName) {
	fprintf(stderr,"MagicSQ - (c) 2000 by Vasian CEPA - http://madebits.com\n");
	fprintf(stderr,"Usage: %s n > my-magic-square.txt\n", programName);
	fprintf(stderr,"Where: n an odd integer of matrix dimensions. Even numbers are not supported.\n");
}

/* EOF */
