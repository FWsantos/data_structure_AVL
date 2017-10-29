#include <stdio.h>
#include <stdlib.h>
#include "Node.c"
int main(){
	Node *root = NULL;
	int a;
	while(scanf("%d", &a)){
		insert_value(&root, a);
	}
	system("clear");
	printf("\n");
	print_values(&root, 0);
	printf("altura : %d\n", get_FB(&root, 1));
	// print_FBs(&root, 0);
	return 0;
}
