#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Filme {
    char nomeFilme[50];
    struct Filme* proximo;
} Filme;

Filme* adicionarNaListaFilme(Filme* lista, const char* nomeFilme) {
    Filme* newFilme = (Filme*)malloc(sizeof(Filme));
    if (newFilme == NULL) {
        printf("Erro: Falha na alocação de memória para o filme.\n");
        exit(1);
    }
    strncpy(newFilme->nomeFilme, nomeFilme, sizeof(newFilme->nomeFilme));

    if (lista == NULL) {
        newFilme->proximo = newFilme;
    } 
    else {
        newFilme->proximo = lista->proximo;
        lista->proximo = newFilme;
    }
    return newFilme;
}

Filme* buscarFilme(Filme* lista, const char* nomeFilme) {
    if (lista == NULL) {
        return NULL;
    }
Filme* atual = lista->proximo;
    do {
        if (strcmp(atual->nomeFilme, nomeFilme) == 0) {
            return atual;
        } 
        atual = atual->proximo;
    } 
    while (atual != lista->proximo);
        return NULL;
}

int qtdDeFilmesNaLista(Filme* lista) {
    if (lista == NULL) {
        return 0;
    }

    int contador = 0;
    Filme* atual = lista->proximo;
    do {
        contador++;
        atual = atual->proximo;
    } 
    while (atual != lista->proximo);
    
    return contador;
}

Filme* apagarFilme(Filme* lista, const char* nomeFilme) {
    if (lista == NULL) {
        return NULL;
    }

    Filme* anterior = lista;
    Filme* atual = lista->proximo;
    do {
        if (strcmp(atual->nomeFilme, nomeFilme) == 0) {
            anterior->proximo = atual->proximo;
            free(atual);
            if (atual == lista) {
                lista = (anterior == atual) ? NULL : anterior;
            }
            return lista;
        }
        anterior = atual;
        atual = atual->proximo;
    } 
    while (atual != lista->proximo);

    return lista;
}

void liberarLista(Filme* lista) {
    if (lista == NULL) {
        return;
    }

    Filme* atual = lista->proximo;
    while (atual != lista) {
        Filme* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(lista);
}

int main() {
	setlocale(LC_ALL, "Portuguese");
    Filme* lista = NULL;
    int opcao;

    do {
        printf("Escolha uma opção: ");
        printf("\n0-) sair");
        printf("\n1-) adicionar filme");
        printf("\n2-) buscar filme");
        printf("\n3-) contar filmes");
        printf("\n4-) remover filme\n");
        scanf("%d", &opcao);

switch (opcao) {
            case 0: {
                liberarLista(lista);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n\n");
                break;
            }
            case 1: {
                char nomeFilme[50];
            printf("Digite o nome do filme que deseja adicionar na lista: ");
                scanf("%s", nomeFilme);
                lista = adicionarNaListaFilme(lista, nomeFilme);
                printf("O filme %s foi adicionado na lista.\n\n");
                break;
            }
            case 2: {
                char nome[50];
                printf("Digite o nome do filme que deseja buscar: ");
                scanf("%s", nome);
                Filme* filmeEncontrado = buscarFilme(lista, nome);
             
                if (filmeEncontrado != NULL) {
                    printf("Filme encontrado: %s.\n\n", filmeEncontrado-> nomeFilme);
                } 
                else {
                    printf("Filme não encontrado.\n\n");
                }
                break;
            }
            case 3: {
                int qtdFilme = qtdDeFilmesNaLista(lista);
                printf("A quantidade de filmes presentes na lista é: %d.\n\n", qtdFilme);
                break;
            }
            case 4: {
                char nome[50];
              printf("Digite o nome do filme que deseja remover da lista: ");
                scanf("%s", nome);
                lista = apagarFilme(lista, nome);
                printf("Filme removido da lista.\n\n");
                break;
            }
        }
    } 
    while (opcao != 0);

    return 0;
}

