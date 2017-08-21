#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEDIA 6
#define LINHA 1000
#define CHECA_FREQUENCIA_SE_APROVADO_POR_NOTA 0

//Definindo um tipo Bool global ao escopo do programa
typedef enum _bool {
	true = 1,
	false = 0
} Bool;

//Retorna o sexo
char retornaSexo(){
	char sexo[2] = {'m','f'};
	int r = (int) rand()%2;
	return sexo[r];
}

//Estrutura que sera armazenada na lista
struct aluno {
	int matricula;
	int idade;
	char nome[50];
	char sexo;
	float n1,n2,n3;
	float media;
	int frequencia;
};
typedef struct aluno Aluno;

/*
	struct aluno construtorAluno(int matricula, int idade, char *nome, float n1, float n2, float n3)
	- tipo: struct aluno
	- descricao: controi uma struct do tipo aluno e a retorna
*/
Aluno construtorAluno(int matricula, int idade, char *nome, char sexo, float n1, float n2, float n3, int frequencia){
	struct aluno a;
	a.matricula = matricula;
	a.idade = idade;
	strcpy(a.nome, nome);
	a.sexo = sexo;
	a.n1 = n1;
	a.n2 = n2;
	a.n3 = n3;
	a.media = ((n1 + n2 + n3) / 3);
	a.frequencia = frequencia;
	
	return a;
}

//Elemento que armazena os dados e o ponteiro para o proximo elemento do tipo elemento
struct elemento {
	struct aluno dados;
	struct elemento *proximo;	
};

typedef struct elemento *Lista; //ponteiro para o elemento, ou seja, um ponteiro para a cabeça da lista
typedef struct elemento Elem; //elemento de cada lista 

/*	
	Lista* controi()
	- tipo: Lista* (ponteiro para a cabeça da lista)
	- descricao: Retorna um elemento do tipo Lista* que aponta para NULL
*/
Lista* constroi() {
	Lista *l = (Lista*) malloc(sizeof(Lista));
	if(l != NULL)
		*l = NULL;
	return l;
}

/*
	void destroi(Lista *l)
	- tipo: void
	- descricao: Realiza um loop na lista e desaloca cada nó. Ao final desaloca a cabeça da lista (Lista*)
*/
void destroi(Lista *l) {
	if(l != NULL){
		Elem *no; //aloca um no da lista
		while((*l) != NULL){
			no = *l;
			(*l) = (*l)->proximo;
			free(no);
		}
		free(l);
	}
}

/*	
	void imprimeLista(Lista *l)
	- tipo: void
	- descricao: Imprime os dados de cada nó presente na lista
*/
void imprimeLista(Lista *l) {
	if(l != NULL){
		if(*l == NULL){
			printf("Nada a imprimir!");
		} else {
			Elem *no = (*l);
			while(no != NULL){
				
				printf("Matricula: %d", no->dados.matricula);
				printf("\n");
				printf("Idade: %d", no->dados.idade);
				printf("\n");
				printf("Nome: %s", no->dados.nome);
				printf("\n");
				if(no->dados.sexo == 'm'){
					printf("Sexo: Masculino");
				} else {
					printf("Sexo: Feminino");
				}
				printf("\n");
				printf("Nota 1: %.2f", no->dados.n1);
				printf("\t");
				printf("Nota 2: %.2f", no->dados.n2);
				printf("\t");
				printf("Nota 3: %.2f", no->dados.n3);
				printf("\n");
				printf("Media: %.2f", no->dados.media);
				printf("\n");
				printf("Frequencia: %d %", no->dados.frequencia);
				
				printf("\n-------------------\n");
				no = no->proximo;
			}
		}
	}
}

/*
	void imprimeAluno(struct aluno a)
*/
void imprimeAluno(struct aluno a){
	printf("\n-------------------\n");
	printf("Matricula: %d", a.matricula);
	printf("\n");
	printf("Idade: %d", a.idade);
	printf("\n");
	printf("Nome: %s", a.nome);
	printf("\n");
	if(a.sexo == 'm'){
		printf("Sexo: Masculino");
	} else {
		printf("Sexo: Feminino");
	}
	printf("\n");
	printf("Nota 1: %.2f", a.n1);
	printf("\t");
	printf("Nota 2: %.2f", a.n2);
	printf("\t");
	printf("Nota 3: %.2f", a.n3);
	printf("\n");
	printf("Media: %.2f", a.media);
	printf("\n-------------------\n");
	printf("Frequencia: %d", a.frequencia);
	printf("\n");
}

/*
	Bool insereInicio(Lista *l, struct aluno a)
	- tipo: Bool
	- descricao: Insere um novo aluno na lista 
*/
Bool insereInicio(Lista *l, struct aluno a) {
	if(l == NULL)
		return false;
	Elem *no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL)
		return false;
	no->dados = a;
	no->proximo = (*l);
	*l = no;
	
	return true;
}

/*
	Bool insereFinal(Lista *l, struct aluno a)
	- tipo: Bool
	- descricao: Insere um novo aluno no final da lista 
*/
Bool insereFinal(Lista *l, struct aluno a){
	if(l == NULL)
		return false;
	Elem *no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL)
		return false;
	no->dados = a;
	no->proximo = NULL;
	if((*l) == NULL){
		*l = no;	
	} else {
		Elem *temp = (*l);
		while(temp->proximo != NULL)
			temp = temp->proximo;
		temp->proximo = no;
	}
	return true;
}

/*
	Bool insereOrdenadamente(Lista *l, struct aluno a)
	- tipo: Bool
	- descricao: Insere um novo aluno na lista de acordo com a sua nota
*/
Bool insereOrdenadamente(Lista *l, struct aluno a) {
	if(l == NULL)
		return false;
	Elem *no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL)	
		return false;
	no->dados = a;
	if((*l) == NULL){
		no->proximo = NULL;
		*l = no;
		return true;
	} else {
		Elem *atual = (*l), *anterior;
		while(atual != NULL && atual->dados.matricula < a.matricula){
			anterior = atual;
			atual = atual->proximo;
		}
		if(atual == (*l)){ //nao saiu do lugar
			no->proximo = *l;
			*l = no;
		} else {
			no->proximo = atual;
			anterior->proximo = no;	
		}
		return true;
	}
}

/*
	Bool removeInicio(Lista *l)
	- tipo: Bool
	- descricao: Insere um novo aluno na lista de acordo com a sua nota
*/
Bool removeInicio(Lista *l) {
	if(l == NULL || (*l) == NULL)
		return false;
	Elem *no = (*l);
	*l = no->proximo;
	free(no);
	return true;
}

/*
	Bool removeFinal(Lista *l)
	- tipo: Bool
	- descricao: Insere um novo aluno na lista de acordo com a sua nota
*/
Bool removeFinal(Lista *l){
	if(l == NULL || (*l) == NULL)
		return false;
	Elem *atual = (*l), *anterior;
	while(atual->proximo != NULL){
		anterior = atual;
		atual = atual->proximo;
	}
	if(atual == (*l)){
		*l = atual->proximo;
	} else {
		anterior->proximo = NULL;
	}
	free(atual);
	return true;
}

/*
	Bool removeAluno(Lista *l, int matricula)
	- tipo: Bool
	- descricao: Insere um novo aluno na lista de acordo com a sua nota
*/
Bool removeAluno(Lista *l, int matricula){
	if(l == NULL && (*l) == NULL)
		return false;
	Elem *atual = (*l), *anterior;
	while(atual != NULL && atual->dados.matricula != matricula){
		anterior = atual;
		atual = atual->proximo;
	}
	if(atual == NULL)
		return false;
	if(atual == (*l)){
		*l = atual->proximo;
	} else {
		anterior->proximo = atual->proximo;
	}
	free(atual);
	return true;
}

/*
	Bool buscaAluno(Lista *l, int matricula)
	- tipo: Bool
	- descricao: Insere um novo aluno na lista de acordo com a sua nota
*/
Bool buscaAluno(Lista *l, int matricula, struct aluno *a){
	if(l == NULL || (*l) == NULL)
		return;
	Elem *no = (*l);
	while(no != NULL){
		if(no->dados.matricula == matricula){
			*a = no->dados;
		}
		no = no->proximo;
	}
	return true;
}

/*
	int tamanhoLista(Lista *l)
*/
int tamanhoLista(Lista *l){
	int tamanho = 0;
	if(l == NULL || (*l) == NULL)
		return 0;
	Elem *no = (*l);
	while(no != NULL){
		tamanho++;
		no = no->proximo;
	}
	return tamanho;
}

/*
	Lista *listaAprovados(Lista* li)
*/
Lista *listaAprovados(Lista *l){
	if(l == NULL || (*l) == NULL)
		return;
	Elem *no = (*l);
	Lista *ap = constroi();
	if(ap == NULL)
		return;
	while(no != NULL){
		if(CHECA_FREQUENCIA_SE_APROVADO_POR_NOTA == 1){
			if(no->dados.media >= MEDIA && no->dados.frequencia >= 75){
				insereOrdenadamente(ap, no->dados);
			}	
		} else {
			if(no->dados.media >= MEDIA){
				insereOrdenadamente(ap, no->dados);
			}
		}
		no = no->proximo;
	}
	return ap;
}

/*
	Lista *listaReprovados(Lista* li)
*/
Lista *listaReprovados(Lista *l){
	if(l == NULL || (*l) == NULL)
		return;
	Elem *no = (*l), *novo = NULL;
	Lista *rp = constroi();
	if(rp == NULL)
		return;
	while(no != NULL){
		if(CHECA_FREQUENCIA_SE_APROVADO_POR_NOTA == 1){
			if(no->dados.media < MEDIA && no->dados.frequencia >= 75){
				insereOrdenadamente(rp, no->dados);
			}	
		} else {
			if(no->dados.media < MEDIA){
				insereOrdenadamente(rp, no->dados);
			}
		}
		no = no->proximo;
	}
	return rp;
}

/*
	Retorna os dados da lista em formato string
*/
char **dadosLista(Lista *l){
	if(l == NULL || (*l) == NULL)
		return;
	
	int tamanho = tamanhoLista(l);
	int matricula, i = 0, j = 0;
	char *buffer, *nome;
	float n1,n2,n3,media;
	Elem *no = (*l);
		
	char **dados;
	dados = (char **) malloc(tamanho * sizeof(char*));
	if(dados){
		for(j = 0; j < tamanho; j++){
			dados[j] = (char *) malloc(LINHA * sizeof(char));
			if(!dados)
				return;
		}	
	}
	
	while(no != NULL){
		sprintf (
			*(dados + (i)), 
			"\n----------\nMatricula: %d\nNome: %s\nSexo: %c\nNota 1: %.2f\nNota 2: %.2f\nNota 3: %.2f\nMedia: %.2f\nFrequencia: %d\n----------\n", 
			no->dados.matricula, no->dados.nome, no->dados.sexo, no->dados.n1, no->dados.n2, no->dados.n3, no->dados.media, no->dados.frequencia
		);
		no = no->proximo;
		i++;
	}
	
	return dados;
}

/*
	Media de uma turma
*/
float mediaTurma(Lista *l){
	if(l == NULL || (*l) == NULL)
		return 0;
	float somaNotas = 0;
	int total = tamanhoLista(l);
	Elem *no = (*l);
	while(no != NULL){
		somaNotas += no->dados.media;
		no = no->proximo;
	}
	return ((somaNotas)/total);
}

/*
	Relatorio completo da turma
*/
char *relatorioTurma(Lista *l, Lista *aprovados, Lista *reprovados){
	char *buffer = (char *) malloc(LINHA * sizeof(char));
	if(!buffer)
		return;
	sprintf(
		buffer,
	 	"\n----------\nQuantidade de de alunos aprovados: %d\n----------\nQuantidade de Alunos Reprovados: %d\n----------\nMedia Global: %.2f\n----------\n",
	 	tamanhoLista(aprovados), tamanhoLista(reprovados), mediaTurma(l)
	);
	return buffer;
}


/*
	Aplicação principal
*/
int main(){
	srand(time(NULL)); //define o seed para rand()
	Lista *l = constroi(); //lista principal
	Lista *aprovados, *reprovados;
	FILE *listaAlunos, *arquivoAprovados, *arquivoReprovados, *relatorio;
	struct aluno a;
	int i = 0, j = 0;
	
	//Preenche uma lista de 30 alunos aleatoriamente
	for(i = 1; i <= 30; i++){
		int idade = rand()%((30 - 18) + 1) + 18; 
		float n1 = rand() % 11;
		float n2 = rand() % 11;
		float n3 = rand() % 11;
		int frequencia = rand()%101; 
		char nome[50];
		char buffer[10];
		char sexo = retornaSexo();
		
		//Nome do aluno
		strcpy(nome, "Aluno ");
		sprintf(buffer, "%d", i);
		strcat(nome, buffer);
		
		a = construtorAluno(i, idade, nome, sexo, n1, n2, n3, frequencia);
		insereOrdenadamente(l, a);
	}
	
	aprovados = listaAprovados(l);
	reprovados = listaReprovados(l);
	
	int tamanhoListaAlunos = tamanhoLista(l);
	int tamanhoListaAprovados = tamanhoLista(aprovados);
	int tamanhoListaReprovados = tamanhoLista(reprovados);
	
	listaAlunos = fopen("listaAlunos.txt", "w");
	arquivoAprovados = fopen("listaAprovados.txt", "w");
	arquivoReprovados = fopen("listaReprovados.txt", "w");
	relatorio = fopen("relatorioTurma.txt", "w");
	
	if(listaAlunos && aprovados && reprovados){
		for(i = 0; i < tamanhoListaAlunos; i++){
			fprintf(listaAlunos, "%s\n", dadosLista(l)[i]);
		}
		for(i = 0; i < tamanhoListaAprovados; i++){
			fprintf(arquivoAprovados, "%s\n", dadosLista(aprovados)[i]);
		}
		for(i = 0; i < tamanhoListaReprovados; i++){
			fprintf(arquivoReprovados, "%s\n", dadosLista(reprovados)[i]);
		}
		fprintf(relatorio, "%s", relatorioTurma(l, aprovados,reprovados));
		printf("Alunos gerados com sucesso\n");
		printf("%s\n", relatorioTurma(l,aprovados,reprovados));
	} else {
		printf("Erro ao abrir os arquivos !\n");
	}
	
	fclose(listaAlunos);
	fclose(arquivoAprovados);
	fclose(arquivoReprovados);
	fclose(relatorio);

	destroi(l);
	destroi(aprovados);
	destroi(reprovados);
	
	return 0;
}
