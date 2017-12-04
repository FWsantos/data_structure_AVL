#include <stdlib.h>
#include <stdio.h>

struct noh{
	int chave, fatbal;
	struct noh *dir, *esq, *anc;
};

void* busca(struct noh *A, int x){
	while(A!=NULL){
		if(x==A->chave) return A;
		if(x < A->chave) A = A->esq;
		else A = A->dir;
	}
	return NULL;
}

void* aloca_noh( int x ){
	struct noh *p = malloc(sizeof(struct noh));
	*p = (struct noh){x,0,NULL,NULL,NULL}; 
	return p;
}


void rotdir(struct noh **A){
	struct noh *P;
	P = (*A)->esq;
	P->anc = (*A)->anc;
	(*A)->esq = P->dir;
	if((*A)->esq!=NULL) 
		(*A)->esq->anc = *A;
	(*A)->fatbal=0;
	P->dir = *A;
	P->fatbal=0;
	(*A)->anc = P;
	*A = P;
	if((*A)->anc!=NULL){
		if((*A)->chave < (*A)->anc->chave)
			(*A)->anc->esq = *A;
		else
			(*A)->anc->dir = *A;
	}
}

void rotesq(struct noh **A){
	struct noh *P;
	P = (*A)->dir;
	P->anc = (*A)->anc;
	(*A)->dir = P->esq;
	if((*A)->dir!=NULL) 
		(*A)->dir->anc = *A;
	(*A)->fatbal=0;
	P->esq = *A;
	P->fatbal=0;
	(*A)->anc = P;
	*A = P;
	if((*A)->anc!=NULL){
		if((*A)->chave < (*A)->anc->chave)
			(*A)->anc->esq = *A;
		else
			(*A)->anc->dir = *A;
	}
}

void rotdirdupla(struct noh **A){
	rotesq(&((*A)->esq));
	(*A)->esq->fatbal = -1;
	rotdir(A);
}

void rotesqdupla(struct noh **A){
	rotdir(&((*A)->dir));
	(*A)->dir->fatbal = 1;
	rotesq(A);
}

void AVL_consertar( struct noh **A){
	if((*A)->fatbal==2){
		if((*A)->dir->fatbal==1)
			rotesq(A);
		else
			rotesqdupla(A);
	}
	else if((*A)->fatbal==-2){
		if((*A)->esq->fatbal==-1)
			rotdir(A);
		else
			rotdirdupla(A);
	}
	return;
}

void* AVL_inserir( struct noh **A, int x ){
	struct noh *p = aloca_noh(x), *i = *A, *anc = NULL;
	if( *A==NULL ){
		*A = p;
		return *A;
	}
	while( i != NULL ){
		if( x == i->chave ) return *A;
		if( x < i->chave ){
			anc = i;
			i = i->esq;
		}
		else{
			anc = i;
			i = i->dir;
		}
	}
	if( x > anc->chave ){
		anc->fatbal++;
		anc->dir = p;
	}
	else{
		anc->fatbal--;
		anc->esq = p;
	}
	p->anc = anc;
	i = anc;
	while(i!=NULL){
		if(i->fatbal==0) i=NULL;
		else if(i->fatbal==1 || i->fatbal==-1){
			if(i->anc != NULL){
				if(i->chave < i->anc->chave)
					i->anc->fatbal--;
				else
					i->anc->fatbal++;
			}
			i = i->anc;
		}
		else {
			if(i==(*A))
				AVL_consertar(A);
			else AVL_consertar(&i);
			i = NULL;
		}
	}
	return *A;
}

void* sucessor( struct noh *A ){
	if(A->dir!=NULL){
		A=A->dir;
		while(A->esq!=NULL)
			A=A->esq;
		return A;
	}
	else{
		while(A->anc < A)
			A=A->anc;
		return A->anc;
	}
}

void AVL_remover( struct noh **A, int x ){
	int fb;
	struct noh *z, *y, *i;
	z = busca((*A), x);
	if(z==NULL) return;
	if(z->esq == NULL && z->dir == NULL){
		if(z==(*A)){
			(*A)=NULL;
			free(*A);
			return;
		}
		if(z == z->anc->esq){
			z->anc->esq = NULL;
			z->anc->fatbal++;
		}
		else{
			z->anc->dir = NULL;
			z->anc->fatbal--;
		}
	}
	else{
		if(z->esq == NULL){
			if(z==(*A)){
				*A = (*A)->dir;
			}
			else if(z == z->anc->esq){
				z->anc->esq = z->dir;
				z->anc->fatbal++;
			}
			else{
				z->anc->dir = z->dir;
				z->anc->fatbal--;
			}
			if(z->dir!=NULL)
				z->dir->anc = z->anc;
		}
		else if(z->dir == NULL){
			if(z==(*A)){
				*A=(*A)->esq;
			}
			else if(z == z->anc->esq){
				z->anc->esq = z->esq;
				z->anc->fatbal++;
			}
			else{
				z->anc->dir = z->esq;
				z->anc->fatbal--;
			}
			z->esq->anc = z->anc;
		}
		else{
			y = sucessor(z);
			if(y==z->dir){
				y->anc = z->anc;
				y->esq = z->esq;
				z->esq->anc = y;
				y->fatbal = z->fatbal - 1;
				if(z == z->anc->esq){
					z->anc->esq = y;
					if(y->fatbal == 0)
						y->anc->fatbal++;
				}
				else{
					z->anc->dir = y;
					if(y->fatbal == 0)
						y->anc->fatbal--;
				}
			}
			else{
				fb=z->fatbal;
				y->anc->esq = y->dir;
				y->anc->fatbal++;
				if(y->dir!=NULL)
					y->dir->anc = y->anc;
				for(i=y->anc; i->anc!=z; i->anc->fatbal++){
					if(i->fatbal==1)
						i=z->dir;
					else if(i->fatbal==0)
						i = i->anc;
					else
						AVL_consertar(&i);
				}
				AVL_consertar(&i);

				if(fb!=0 && z->dir->fatbal==0)
					y->fatbal=z->fatbal - 1;
				else
					y->fatbal = z->fatbal;
				y->anc = z->anc;
				y->esq = z->esq;
				y->dir = z->dir;
				z->esq->anc = y;
				z->dir->anc = y;
				if(z==(*A)){
					*A = y;
				}
				else if(z == z->anc->esq){
					z->anc->esq = y;
					if(y->fatbal == 0)
						y->anc->fatbal++;
				}
				else{
					z->anc->dir = y;
					if(y->fatbal == 0)
						y->anc->fatbal--;
				}
			}
		}
	}

	for(i=z->anc; i!=(*A) && i!=NULL; i=i->anc){
		if(i->fatbal==0)
			if(i==i->anc->esq)
				i->anc->fatbal++;
			else
				i->anc->fatbal--;
		if(i->fatbal==1 || i->fatbal==-1)
			i= (*A);
		else
			AVL_consertar(&i);
	}
	AVL_consertar(A);

	free(z);
}

void* AB_inserir( struct noh **A, int x ){
	struct noh *p = aloca_noh(x), *i = *A, *anc = NULL;
	if( *A==NULL ){
		*A = p;
		return *A;
	}
	while( i != NULL ){
		if( x == i->chave ) return *A;
		if( x < i->chave ){
			anc = i;
			i = i->esq;
		}
		else{
			anc = i;
			i = i->dir;
		}
	}
	if( x > anc->chave )
		anc->dir = p;
	else anc->esq = p;
	p->anc = anc;
	return *A;
}

void percurso_ord( struct noh* A ){
	if( A!= NULL ){
		percurso_ord( A->esq );
		printf("%d\n", A->chave);
		percurso_ord(A->dir);   	
	}
	return;
}

void print_valores(struct noh *raiz, int height){
	if (raiz != NULL){
		int i;
		for(i = 0; i < height; ++i) printf("\t");
			printf("%d(%d)\n", raiz->chave, raiz->fatbal);
		print_valores(raiz->esq, height+1);
		print_valores(raiz->dir, height+1);
	}
}
