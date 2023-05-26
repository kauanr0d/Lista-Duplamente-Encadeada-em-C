#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
  struct Nodo *prox;
  struct Nodo *ant;
  int elemento;
} Nodo;

typedef struct Lista {
  Nodo *inicio;
  int tam;
} Lista;

void iniciarLista(Lista *l) {
  l->inicio = NULL;
  l->tam = 0;
}
int tamanhoLista(Lista *l) { return l->tam; }

int inserir(Lista *l, int elemento, int pos) {
  Nodo *inserido = (Nodo *)malloc(sizeof(Nodo));

  if (inserido != NULL) {
    inserido->elemento = elemento;
    if (pos <= l->tam + 1 || pos > 0) {
      if (pos == 1) {
        inserido->ant = NULL;
        inserido->prox = l->inicio;
        if (l->inicio != NULL) {
          l->inicio->ant = inserido;
        }
        l->inicio = inserido;
      } else {
        Nodo *aux;
        aux = l->inicio;
        for (int i = 2; i < pos; i++) {
          aux = aux->prox;
        }
        Nodo *atual = aux->prox;
        inserido->prox = atual;
        aux->prox = inserido;
        inserido->ant = aux;
      }
    }
  }
  l->tam++;
  return 1;
}

int excluir(Lista *lista, int pos) {
  Nodo *excluido, *aux;
  
  if (pos <= lista->tam && pos > 0) {
    if (pos == 1) {
      excluido = lista->inicio;
      excluido->prox->ant = NULL;
      lista->inicio = excluido->prox;
      free(excluido);
      lista->tam--;
    } else {
      aux = lista->inicio;
      for (int i = 2; i < pos; i++) {
        aux = aux->prox;
      }
      Nodo *proximo = aux->prox->prox;
      if (proximo == NULL) {
        excluido = aux->prox;
        aux->prox = excluido->prox;
      } else {
        proximo->ant = aux;
        excluido = aux->prox;
        aux->prox = proximo;
      }
      free(excluido);
      lista->tam--;
    }
  } else {
    return 0;
  }
  return 1;
}

void imprimirReverso(Lista *lista) {
  Nodo *ultimo;
  ultimo = lista->inicio;
  while (ultimo->prox != NULL) {
    ultimo = ultimo->prox;
  }
  while (ultimo != NULL) {
    printf("%d\n", ultimo->elemento);
    ultimo = ultimo->ant;
  }
}

Lista lista_dupla;
int main(void) {
  iniciarLista(&lista_dupla);
  int a;
  inserir(&lista_dupla, 1, 1);
  inserir(&lista_dupla, 2, 2);
  inserir(&lista_dupla, 3, 3);
  inserir(&lista_dupla, 4, 4);
  imprimirReverso(&lista_dupla);
  excluir(&lista_dupla, 1);
  printf("\n\n");
  imprimirReverso(&lista_dupla);
  return 0;
}