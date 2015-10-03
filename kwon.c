/***************************************************************************/
/*                       < <<   MAGIC  SQUARE   >> >                       */
/*                                     - Programed by;  Shin, Kwon Young.  */
/***************************************************************************/

/*
 * Original URL	http://user.chollian.net/~brainstm/source.htm
 *
 * This code has been modified by Vasian CEPA to make use of dynamic memory
 * alocation, and to be suitable for use in batch mode.
 * The original algorithms are not changed.
 * The 'random()' function is renamed to 'kwon_random()' to
 * avoid conficts with the same 'stdlib.h' named function that
 * is included in 's_matrix.h' file.
 *
 * http://madebits.com
 */

#include "s_matrix.h" /* offers support for integer dynamic square matrices */

S_MATRIX* m;

void odd_num(int n);
void even_num(int n);
void output(int n);
void _swap(int i1, int j1, int i2, int j2);
int kwon_random(int n);
void printUsage(char* progName);
void printLogo();

int main(int argc, char *argv[])
{
	int n;

	if (argc != 2){
		printUsage(argv[0]);
	} else {
		n = atoi(argv[1]);
	}
	if(n < 3){
		printUsage(argv[0]);
	}

	printLogo();
	m = create_S_MATRIX(n);
	if(m == NULL){
	   fprintf(stderr, "\nOut of Memory Error! Aborting");
	   abort();
	}
	n = m->getSize(m);
	if(n == 0){
		fprintf(stderr, "\nOut of Memory Error! Aborting");
		destroy_S_MATRIX(m);
		abort();
	}

	if(n%2) odd_num(n);
	else even_num(n);

	output(n);
	/* m->print(m); */

	destroy_S_MATRIX(m);
	return 0;
}

void odd_num(int n)
{
    int i,j,num=1;
    int nn=n*3/2;

    for(i=0; i < n; i++)
        for(j=0; j < n; j++)
            m->setElement(m,(j-i+nn)%n,(i*2-j+n)%n,num++);
}

void even_num(int n)
{
    int i,j,num=1;
    int nminus=n-1,nmiddle=n/2,nn=n*n+1;
    int osl=0;
    int switch_row[2];
    int last_switch_column;
    int first_block=(n-2)/4,second_block=nminus-first_block;
    int first_inside=n/4,second_inside=nminus-first_inside;

    for(j=0; j < n; j++)
        for(i=0; i < n; i++) {
            if(i >= first_inside && i <= second_inside && j >= first_inside && j <= second_inside)
                m->setElement(m,i,j,num);
            else if((i > first_block && i < second_block) || (j > first_block && j < second_block))
                m->setElement(m,i,j,nn-num);
            else m->setElement(m,i,j,num);
            num++;
        }
    if(!(n%4)) return;

    switch_row[0]=kwon_random(nmiddle-1)+first_block+1;
    switch_row[1]=kwon_random(nmiddle-1);
    if(switch_row[1] >= first_block) switch_row[1]+=(nmiddle+1);
    last_switch_column=kwon_random(nmiddle-1);
    if(last_switch_column >= first_block) last_switch_column+=(nmiddle+1);

/* Simply, you can write as follows..
    switch_row[0]=nmiddle;
    switch_row[1]=0;
    last_switch_column=0;
*/

    for(i=0; i < nmiddle; i++) {
        if(i==first_block || i==second_block) {
            osl=1-osl;
            continue;
        }
        _swap(second_block, i, second_block, nminus-i);
        _swap(i, first_block, nminus-i, first_block);
        _swap(i, second_block, nminus-i, second_block);
        _swap(i, switch_row[osl], nminus-i, switch_row[osl]);
    }
    for(i=first_block+1; i < second_block; i++) {
        _swap(first_block, i, second_block, i);
        _swap(i, first_block, i, second_block);
    }
    _swap(first_block, nmiddle, second_block, nmiddle);
    _swap(last_switch_column, first_block, last_switch_column, second_block);
}

void output(int n)
{
    int i,j,err=0;
    unsigned long sum,sl,sc,sd1=0,sd2=0;

    sum=(unsigned long)n*(n*n+1)/2;
    fprintf(stderr, "SUM = %lu ",sum);
    for(j=0; j < n; j++) {
        sd1+=m->getElement(m,j,j);
        sd2+=m->getElement(m,j,n-j-1);
        sl=0;
        sc=0;
        for(i=0; i < n; i++) {
            sl+=m->getElement(m,i,j);
            sc+=m->getElement(m,j,i);
        }
        if(sl!=sum) {
            err++;
            fprintf(stderr,"\n> Sum of the row-(%d) is %lu. It's incorrect..",j+1,sl);
        }
        if(sc!=sum) {
            err++;
            fprintf(stderr,"\n> Sum of the column-(%d) is %lu. It's incorrect..",j+1,sc);
        }
    }
    if(sd1!=sum) {
        err++;
        fprintf(stderr,"\n> Sum of the diagonal-(\\) is %lu. It's incorrect..",j+1,sd1);
    }
    if(sd2!=sum) {
        err++;
        fprintf(stderr,"\n> Sum of the diagonal-(/) is %lu. It's incorrect..",j+1,sd2);
    }
    if(err) fprintf(stderr,"\n\n* %d errors are happened.",err);
    else fprintf(stderr,"- O.K. -\n");

    for(j=0; j < n; j++) {
        /* printf("\n%2d)] ",j+1); */
        printf("\n");
        fprintf(stderr,"%4d)]  ",j+1);
        for(i=0; i < n; i++) {
            char* f = NULL;
            if(i == n-1) f = "%d";
            else f = "%d,";
            printf(f,m->getElement(m,i,j));
        }
    }
}

void _swap(int i1, int j1, int i2, int j2)
{
    int k;

    k=m->getElement(m,i1,j1);
    m->setElement(m,i1,j1,m->getElement(m,i2,j2));
    m->setElement(m,i2,j2,k);
}

/* max number returned by rand is 0xFFFF */
int kwon_random(int n)
{
	return (n/0xFFFF)*rand();
}

void printUsage(char *progName)
{
	printLogo();
	fprintf(stderr, "\nUsage: %s n > my-magic-square.txt", progName);
	fprintf(stderr, "\nWhere: n is the integer dimension of matrix (n > 2)");
	exit(1);
}

void printLogo()
{
    fprintf(stderr,"\n***************************************************************************");
    fprintf(stderr,"\n*                     <  < <   MAGIC  SQUARE   > >  >                     *");
    fprintf(stderr,"\n*            by;  Kwon Young Shin(brainstm@chollian.net)                  *");
    fprintf(stderr,"\n***************************************************************************\n\n");
}

/* EOF */
