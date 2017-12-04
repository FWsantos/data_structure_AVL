// Tipo Boleano // 
#define true 1	//
#define false 0 //
//////////////////

typedef struct node Node;
int saberOLadoDoFilho(Node *filho);
void rotacao_esquerda(Node **raiz);
void rotacao_esquerda_direita(Node **raiz);
void rotacao_direita(Node **raiz);
void rotacao_direita_esquerda(Node **raiz);
// void inserir(Node **raiz, int x);
// Node **busca(Node **raiz, int valor);
// int remover(Node **raiz, int valor);
// Node *achaSucessor(Node *ze_ninguem);


typedef struct node{
	int chave;
	int balanco;
	Node *pai;
	Node *sub_esquerda;
	Node *sub_direita;
} Node;

int inserir(Node **raiz, int x){
	if ((*raiz) == NULL){
		(*raiz) = (Node *)malloc(sizeof(Node));
		**raiz = (Node){x, 0, NULL, NULL, NULL};
		return true;
	}else{
		int mudou_altura;
		if (x < (*raiz)->chave){
			mudou_altura = inserir(&((*raiz)->sub_esquerda), x);
			(*raiz)->sub_esquerda->pai = (*raiz);
			// Se ouve alteração na altura
			if (mudou_altura){
				(*raiz)->balanco--;
				if ((*raiz)->balanco == -2){
					if((*raiz)->sub_esquerda->balanco == 1)
						rotacao_esquerda_direita(raiz);
					else
						rotacao_direita(raiz);
					return false;
				}else if((*raiz)->balanco == 0){
					return false;
				}else if((*raiz)->balanco == -1){
					return true;
				}
			}			
		}else if (x > (*raiz)->chave){
			mudou_altura = inserir(&((*raiz)->sub_direita), x);
			(*raiz)->sub_direita->pai = (*raiz);
			// Se ouve alteração na altura
			if(mudou_altura){
				(*raiz)->balanco++;
				if ((*raiz)->balanco == 2){
					if((*raiz)->sub_direita->balanco == -1)
						rotacao_direita_esquerda(raiz);
					else
						rotacao_esquerda(raiz);
					return false;
				}else if((*raiz)->balanco == 0){
					return false;
				}else if((*raiz)->balanco == 1){
					return true;
				}
			}
		}else{
			printf("A árvore já possui essa chave!\n");
		}
		// Se altura não mudou ou
		// quando já possui aquela chave
		// ele retorna falso
		return false;
	}	
}

Node **busca(Node **raiz, int valor){
	if ((*raiz) == NULL || (*raiz)->chave == valor)
		return raiz;
	if ((*raiz)->chave > valor)
		return busca(&((*raiz)->sub_esquerda), valor);
	if ((*raiz)->chave < valor)
		return busca(&((*raiz)->sub_direita), valor);
}

Node *achaSucessor(Node *ze_ninguem){
	Node *aux1 = ze_ninguem;
	while(aux1->sub_esquerda != NULL){
		aux1 = aux1->sub_esquerda;
	}
	return aux1;
}

int remover(Node **raiz, int valor){
	int slf;
	Node *aux1;
	Node **query = busca(raiz, valor);
	if ((*query) == NULL)
		return -1;

	slf = saberOLadoDoFilho((*query));
	
	if ((*query)->sub_esquerda == NULL){
		if ((*query)->sub_direita == NULL){
			// Remover folha
			if (slf == 1){
				(*query)->pai->balanco++;
				(*query)->pai->sub_esquerda = NULL;
			}else{
				(*query)->pai->balanco--;
				(*query)->pai->sub_direita = NULL;
			}
		}else{
			// remover quando só tem filho direito
			aux1 = (*query)->sub_direita;

			if((*query)->pai != NULL){
				if (slf == 1){
					(*query)->pai->balanco++;
					(*query)->pai->sub_esquerda = aux1;
				}else{
					(*query)->pai->balanco--;
					(*query)->pai->sub_direita = aux1;
				}
			}else{
				(*query) = aux1;
			}

			aux1->pai = (*query)->pai;
		}
	}else{
		if ((*query)->sub_direita == NULL){
			// remover quando só tem filho esquerdo
			aux1 = (*query)->sub_esquerda;
			if((*query)->pai != NULL){
				if (slf == 1){
					(*query)->pai->balanco++;
					(*query)->pai->sub_esquerda = aux1;
				}else{
					(*query)->pai->balanco--;
					(*query)->pai->sub_direita = aux1;
				}
			}else{
				(*query) = aux1;
			}

			aux1->pai = (*query)->pai;	
		}else{
			// Remover quando tem dois filhos
			aux1 = achaSucessor((*query)->sub_direita);
			if((*query)->sub_direita == aux1){
				aux1->pai->sub_direita = aux1->sub_direita;

				aux1->pai = (*query)->pai;
				aux1->sub_esquerda = (*query)->sub_esquerda;
				aux1->sub_esquerda->pai = aux1;
				aux1->sub_direita = (*query)->sub_direita;
				aux1->sub_direita->pai = aux1;
			}else{
				aux1->pai->sub_esquerda = aux1->sub_direita;
				
				aux1->sub_direita->pai = aux1->pai;
				aux1->pai = (*query)->pai;
				aux1->sub_esquerda = (*query)->sub_esquerda;
				aux1->sub_esquerda->pai = aux1;
				aux1->sub_direita = (*query)->sub_direita;
				aux1->sub_direita->pai = aux1;
			}
			printf("deu ruim\n");

			aux1->pai = (*query)->pai;
			aux1->sub_esquerda = (*query)->sub_esquerda;
			aux1->sub_esquerda->pai = aux1;
			aux1->sub_direita = (*query)->sub_direita;
			aux1->sub_direita->pai = aux1;

			if (slf == 1){
				(*query)->pai->balanco++;
				(*query)->pai->sub_esquerda = aux1;
			}else{
				(*query)->pai->balanco--;
				(*query)->pai->sub_direita = aux1;
			}
		}

	}

	// Desalocar
	// free(*query);
	// (*query) = NULL;
	return 0;
}

int saberOLadoDoFilho(Node *filho){
	if (filho->pai == NULL)
		return 0;
	if (filho->pai->sub_esquerda == filho)
		return 1;
	return 2;
}

void rotacao_direita(Node **raiz){
	Node *aux1, *aux2;
	aux1 = (*raiz)->sub_esquerda;
	aux2 = aux1->sub_direita;
	aux1->sub_direita = (*raiz);
	(*raiz)->sub_esquerda = aux2;
	(*raiz) = aux1;

	// atualizar balanco
	aux1->balanco = 0;
	aux1->sub_direita->balanco = 0;

	//atualizar pai
	aux1->pai = aux1->sub_direita->pai;
	aux1->sub_direita->pai = aux1;
	if(aux1->sub_direita->sub_esquerda != NULL)
		aux1->sub_direita->sub_esquerda->pai = aux1->sub_direita;
}
void rotacao_esquerda(Node **raiz){
	Node *aux1, *aux2;
	aux1 = (*raiz)->sub_direita;
	aux2 = aux1->sub_esquerda;
	aux1->sub_esquerda = (*raiz);
	(*raiz)->sub_direita = aux2;
	(*raiz) = aux1;

	// atualizar balanco
	aux1->balanco = 0;
	aux1->sub_esquerda->balanco = 0;

	//atualizar pai
	aux1->pai = aux1->sub_esquerda->pai;
	aux1->sub_esquerda->pai = aux1;
	if(aux1->sub_esquerda->sub_direita != NULL)
		aux1->sub_esquerda->sub_direita->pai = aux1->sub_esquerda;
}
void rotacao_esquerda_direita(Node **raiz){
	rotacao_esquerda(&((*raiz)->sub_esquerda));
	rotacao_direita(raiz);
}
void rotacao_direita_esquerda(Node **raiz){
	rotacao_direita(&((*raiz)->sub_direita));
	rotacao_esquerda(raiz);
}

void print_valores(Node **raiz, int height){
	if ((*raiz) != NULL){
		int i;
		for(i = 0; i < height; ++i) printf("\t");
		printf("%d\n", (*raiz)->chave);
		print_valores(& ((*raiz)->sub_direita), height+1);
		print_valores(&((*raiz)->sub_esquerda), height+1);
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
		print_balanco(&((*raiz)->sub_direita), height+1);
		print_balanco(&((*raiz)->sub_esquerda), height+1);
	}
}
