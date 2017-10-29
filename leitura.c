#include <stdio.h>
int main()
{
	int i;
	char url[]="entrada.txt", ch;
	FILE *arq;

	arq = fopen(url, "r");  // Abre arquivo  em modo de leitura.
	if(arq == NULL)
		printf("Erro, não foi possivel abrir o arquivo.\n");
	else
		for (i = 0; (ch=fgetc(arq))!=EOF; ++i){
			if (ch != ' ')
				printf("%c", ch);
		}

	printf("\n");
	return 0;
}