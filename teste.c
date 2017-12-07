#include <stdio.h>
#include <stdlib.h>
#include "Node.c"
int main(){
	Node *root = NULL;
	Node **teste = NULL;
	int a, b = 13;
	while(scanf("%d", &a)){
		inserir(&root, a);
	}
	system("clear");
	printf("\n");
	print_valores(&root, 0);
	
	
	printf("\n");
	print_balanco(&root, 0);
	// printf("\n");
	// fflush(stdin);
	// printf("insira um valor a remover: ");
	// scanf("%d", &b);
	// printf("%d\n", b);
	// remover(&root, 5);
	// printf("\n");
	// print_valores(&root, 0);
	// print_balanco(&root, 0);
	
	return 0;
}
