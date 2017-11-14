typedef struct node Node;
typedef struct node{
	int chave;
	int balanco;
	Node *pai;
	Node *sub_esquerda;
	Node *sub_direita;
} Node;

void inserir_valor(Node **raiz, int x){
	if ((*raiz) == NULL){
		(*raiz) = (Node *)malloc(sizeof(Node));
		**raiz = (Node){x, 0, NULL, NULL};
	}else{
		if (x < (*raiz)->chave){
			inserir_valor(&((*raiz)->sub_esquerda), x);
		}else if (x > (*raiz)->chave){
			inserir_valor(&((*raiz)->sub_direita), x);
		}else{
			printf("A árvore já possui essa chave!\n");
		}
	}	
}

void print_valores(Node **raiz, int height){
	if ((*raiz) != NULL){
		int i;
		for(i = 0; i < height; ++i) printf("\t");
		printf("%d\n", (*raiz)->chave);
		print_valores(&((*raiz)->sub_esquerda), height+1);
		print_valores(&((*raiz)->sub_direita), height+1);
	}
}

int get_balanco(Node **raiz, int height){
	if((*raiz) == NULL) return height-1;
	int l = get_balanco(&((*raiz)->sub_esquerda), height+1);
	int r = get_balanco(&((*raiz)->sub_direita), height+1);
	(*raiz)->balanco = r-l;
	if (l>=r) return l;
	return r;
}

void print_balanco(Node **raiz, int height){
	if ((*raiz) != NULL){
		int i;
		for(i = 0; i < height; ++i) printf("\t");
		printf("%d\n", (*raiz)->balanco);
		print_balanco(&((*raiz)->sub_esquerda), height+1);
		print_balanco(&((*raiz)->sub_direita), height+1);
	}
}
void rotacao_direita(Node **raiz){
	Node *aux1, *aux2;
	aux1 = (*raiz)->sub_esquerda;
	aux2 = aux1->sub_direita;
	aux1->sub_direita = (*raiz);
	(*raiz)->sub_esquerda = aux2;
	(*raiz) = aux1;
}
void rotacao_esquerda(Node **raiz){
	Node *aux1, *aux2;
	aux1 = (*raiz)->sub_direita;
	aux2 = aux1->sub_esquerda;
	aux1->sub_esquerda = (*raiz);
	(*raiz)->sub_direita = aux2;
	(*raiz) = aux1;
}
void rotacao_esquerda_direita(Node **raiz){
	rotacao_esquerda(&((*raiz)->sub_esquerda));
	rotacao_direita(raiz);
}
void rotacao_direita_esquerda(Node **raiz){
	rotacao_direita(&((*raiz)->sub_direita));
	rotacao_esquerda(raiz);
}
