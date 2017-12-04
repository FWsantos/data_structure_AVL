/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  teste
 *
 *        Version:  1.0
 *        Created:  12/03/17 17:03:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "arvores.h"

int main( int argc, char *argv[] ){
	struct noh *A = NULL, *AVL=NULL, *AB=NULL;
	int V[30000];
	int n=-1, i, j;
	clock_t t;
	printf("inicio:\n");
	srand(time(NULL));
	
	for ( i=0; n!=0; i++ ) {
		scanf("%d", &n);
		AVL_inserir(&A, n);
	}
	n=-1;

	print_valores(A,0);

	printf("remover:\n");
	for ( int i=0; n!=0; i++ ) {
		scanf("%d", &n);
		AVL_remover(&A, n);
	}
	
		print_valores(A,0);

	for(i=0;i<30000;i++){
		V[i] = i+1;
	}
	for(i=(30000-2); i>0;i--){
		j=rand() % (i+1);
		n=V[i];
		V[i] = V[j];
		V[j]=n;
	}
	t=clock();
	for(i=0;i<30000;i++)
		AVL_inserir(&AVL, V[i]);
	t=clock() - t;

	printf("\n\n\ninsercao AVL: %f\n", ((float)t)/CLOCKS_PER_SEC);

	t=clock();
	for(i=1;i<1000000;i++)
		for(j=1;j<10;j++)
			busca(AVL, i);
	t=clock() -t;

	printf("Busca	AVL: %f\n\n", ((float)t)/CLOCKS_PER_SEC);


	t=clock();
	for(i=0;i<30000;i++)
		AB_inserir(&AB, V[i]);
	t=clock() - t;

	printf("insercao ABin: %f\n", ((float)t)/CLOCKS_PER_SEC);


	t=clock();
	for(i=1;i<1000000;i++)
		for(j=1;j<10;j++)
			busca(AB, i);
	t=clock() -t;

	printf("Busca	ABin: %f\n", ((float)t)/CLOCKS_PER_SEC);

	
//	percurso_ord(A);
	return 0;
}

