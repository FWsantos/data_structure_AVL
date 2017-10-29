typedef struct node Node;
typedef struct node{
	int key;
	int FB;
	Node *son_left;
	Node *son_right;
} Node;

void insert_value(Node **root, int x){
	if ((*root) == NULL){
		(*root) = (Node *)malloc(sizeof(Node));
		**root = (Node){x, 0, NULL, NULL};
	}else{
		if (x < (*root)->key){
			insert_value(&((*root)->son_left), x);
		}else if (x > (*root)->key){
			insert_value(&((*root)->son_right), x);
		}else{
			printf("A árvore já possui essa chave!\n");
		}
	}	
}

void print_values(Node **root, int height){
	if ((*root) != NULL){
		int i;
		for(i = 0; i < height; ++i) printf("\t");
		printf("%d\n", (*root)->key);
		print_values(&((*root)->son_left), height+1);
		print_values(&((*root)->son_right), height+1);
	}
}

int get_FB(Node **root, int height){
	if((*root) == NULL) return height-1;
	int l = get_FB(&((*root)->son_left), height+1);
	int r = get_FB(&((*root)->son_right), height+1);
	(*root)->FB = r-l;
	if (l>=r) return l;
	return r;
}

void print_FBs(Node **root, int height){
	if ((*root) != NULL){
		int i;
		for(i = 0; i < height; ++i) printf("\t");
		printf("%d\n", (*root)->FB);
		print_FBs(&((*root)->son_left), height+1);
		print_FBs(&((*root)->son_right), height+1);
	}
}
void rotate_right(Node **root){
	Node *aux1, *aux2;
	aux1 = (*root)->son_left;
	aux2 = aux1->son_right;
	aux1->son_right = (*root);
	(*root)->son_left = aux2;
	(*root) = aux1;
}
void rotate_left(Node **root){
	Node *aux1, *aux2;
	aux1 = (*root)->son_right;
	aux2 = aux1->son_left;
	aux1->son_left = (*root);
	(*root)->son_right = aux2;
	(*root) = aux1;
}
void rotate_left_right(Node **root){
	rotate_left(&((*root)->son_left));
	rotate_right(root);
}
void rotate_right_left(Node **root){
	rotate_right(&((*root)->son_right));
	rotate_left(root);
}