remover_AVL(@p:^no_AVL, K:inteiro, @mudou_h:logico):logico;
var q:^No_AVL;  // ponteiro auxiliar para nó
inicio
se  p = NULO então
    retornar Falso; // não achou a chave K a ser removida
se K < p^.chave então // remover recursivamente na subárvore esquerda
    se remover_AVL(p^.esq, K, mudou_h) então // ocorreu remoção na subárvore esquerda
        inicio
        se mudou_h então
            inicio  // mudou altura da subárvore esquerda de p
            p^.fb := p^.fb + 1; // fator de balanço incrementa 1 unidade
            caso p^.fb
                2:  p := rotacao_esquerda(p);
                    se (p->fb=1) então mudou_h := Falso;
                1: mudou_h := Falso; // não mudou a altura da subárvore de raiz p
               // 0: mudou_h := Verdadeiro; // desnecessário pois mudou_h já é Verdadeiro
            fim
        retornar Verdadeiro;
        fim
senão
    se K > p^.chave então
        se remover_AVL(p^.dir, K, mudou_h) então // ocorreu remoção na s.a. direita
            inicio
            se mudou_h então
                inicio  // mudou altura da subárvore direita de p
                p^.fb := p^.fb - 1; // fator de balanço decrementa 1 unidade
                caso p^.fb
                    -2: p := rotacao_direita(p);
                        se (p->fb = -1) então mudou_h := Falso;
                    -1: mudou_h := Falso; // não mudou a altura da subárvore de raiz p
                //   0: mudou_h := Verdadeiro; // desnecessário pois mudou_h já é Verdadeiro
                fim
            retornar Verdadeiro;
            fim
    senão inicio
            se K = p^.chave então // achou a chave K
                inicio
                se p^.esq=Nulo e p^.dir=Nulo então
                    inicio // nó folha
                    delete p;
                    p := Nulo; // Aterra a subárvore respectiva do nó pai
                    mudou_h := Verdadeiro;
                    fim
                senão se p^.esq<>Nulo e p^.dir<>Nulo então
                        inicio  // nó tem duas subárvores
                        q := Predecessor(p);  // retorna nó com chave predecessora
                        p^.chave := q^.chave;
                        remover(p^.esq,p^.chave,mudou_h);
                        fim
                      senão inicio // tem apenas uma subárvore
                            se p^.esq<>Nulo então
                                inicio
                                p^.chave := p^.esq^.chave;
                                delete p^.esq;
                                p^.esq := Nulo;
                                fim
                            senão   inicio
                                    p^.chave := p^.dir^.chave;
                                    delete(p^.dir);
                                    p^.dir := Nulo;
                                    fim;
                            mudou_h = Verdadeiro;
                            fim;
                retornar Verdadeiro;
                fim
            fim
retornar Falso;
fim;

Predecessor(u:^No_AVL):^No_AVL // retorna nó contendo chave predecessora
inicio
u = u^.esq; // aponta para a raiz da subárvore esquerda
enquanto(u^.dir<>Nulo) faça  // procura a maior chave da subárvore esquerda
    u := u^.dir;
retornar u;  // retorna o predecessor
fim;