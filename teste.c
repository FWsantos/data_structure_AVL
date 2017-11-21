#include <stdio.h>
#include <stdlib.h>
#include "Node.c"
int main(){
	Node *root = NULL;
	Node **teste = NULL;
	int a;
	while(scanf("%d", &a)){
		inserir(&root, a);
	}
	system("clear");
	printf("\n");
	print_valores(&root, 0);
	teste = busca(&root, 13);
	if ((*teste) == NULL)
	{
		printf("Deu rui\n");
	}else{

	printf("Valor achado%i\n", (*teste)->chave);
	}
	// printf("altura : %d\n", get_FB(&root, 1));
	// print_FBs(&root, 0);
	return 0;
}
