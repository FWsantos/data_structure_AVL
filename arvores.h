struct noh;

void* aloca_noh( int );

void* busca(struct noh*, int );

void AVL_consertar( struct noh *);

void AVL_inserir( struct noh **, int );

void* sucessor( struct noh * );

void AVL_remover( struct noh **, int );

void* AB_inserir( struct noh **, int );

void percurso_ord( struct noh* );

void print_valores(struct noh *, int);
