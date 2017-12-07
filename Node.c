
// Tipo Boleano // 
#define true 1    //
#define false 0 //
//////////////////

typedef struct node Node;
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
    Node *filho = ze_ninguem;
    Node *pai = NULL;
    while(filho->sub_esquerda != NULL){
        pai   = filho; 
        filho = filho->sub_esquerda;
    }
    pai->sub_esquerda = filho->sub_direita;
    return filho;
}

int remover(Node **raiz, int valor){
    if((*raiz) == NULL)
        return false;// Não achou valor

    int mudou_altura;
    if(valor < (*raiz)->chave){// remover recursivamente da subarvore esquerda
        mudou_altura = remover(&((*raiz)->sub_esquerda), valor);
        if(mudou_altura){ //mudou altura da subarvore esquerda
            (*raiz)->balanco++;
            if((*raiz)->balanco == 2){
                rotacao_esquerda(raiz);
                // if ((*raiz)->sub_esquerda->sub_direita != NULL){
                //     (*raiz)->sub_esquerda->balanco++;
                //     (*raiz)->balanco--;
                // // }
                if((*raiz)->balanco == 1)
                    return false;
            }else if((*raiz)->balanco == 1){
                return false;
            }else if((*raiz)->balanco == 0){
                return true;
            }

            return true;
        }
    }else if(valor > (*raiz)->chave){
        mudou_altura = remover(&((*raiz)->sub_direita), valor);
        if(mudou_altura){
            (*raiz)->balanco--
;
            if((*raiz)->balanco == -2){
                rotacao_direita(raiz);
                // (*raiz)->sub_direita->balanco--;
                // (*raiz)->balanco++;
                if((*raiz)->balanco == -1)
                    return false;
            }else if((*raiz)->balanco == -1){
                return false;
            }else if((*raiz)->balanco == 0){
                return true;
            }

            return true;
        }
    }else{
        if(valor == (*raiz)->chave){
            // remover nó folha
            if((*raiz)->sub_esquerda == NULL && (*raiz)->sub_direita == NULL){
                (*raiz) = NULL;
                return true;
            }else{

                // remover nó com duas subarvores
                if((*raiz)->sub_esquerda != NULL && (*raiz)->sub_direita != NULL){
                    Node *sucessor = achaSucessor((*raiz));
                    (*raiz)->chave = sucessor->chave;
                    sucessor = NULL;
                    // tem mais coisa aqui

                // remover quando só tem o filho esquerdo
                }else if((*raiz)->sub_esquerda != NULL){
                    (*raiz)->chave = (*raiz)->sub_esquerda->chave;

                    (*raiz)->sub_esquerda = NULL;
                
                // remover quando só tem o filho direito
                }else{
                    (*raiz)->chave = (*raiz)->sub_direita->chave;
                    (*raiz)->sub_direita = NULL;
                }
            }

            return true;
        }
    }

    return false;
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
    aux1->sub_direita->balanco  = 0;
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
