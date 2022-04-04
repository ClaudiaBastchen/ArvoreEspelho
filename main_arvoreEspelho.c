#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
   char info;
   struct arvore *esq;
   struct arvore *dir;
} Arvore;


Arvore*  cria_arv_vazia (void);
Arvore*  arv_constroi (char c, Arvore* e, Arvore* d);
int      verifica_arv_vazia (Arvore* a);
Arvore*  arv_libera (Arvore* a);
int      arv_pertence (Arvore* a, char c);
void     arv_imprime (Arvore* a);
int eh_espelho(Arvore * arv_a, Arvore * arv_b);
Arvore * cria_espelho(Arvore * arv_a);

Arvore* cria_arv_vazia (void) {
   return NULL;
}

Arvore* arv_constroi (char c, Arvore* e, Arvore* d) {
  Arvore* a = (Arvore*)malloc(sizeof(Arvore));
  a->info = c;
  a->esq = e;
  a->dir = d;
  return a;
}

int verifica_arv_vazia (Arvore* a) {
  return (a == NULL);
}

Arvore* arv_libera (Arvore* a) {
  if (!verifica_arv_vazia(a)) {
    arv_libera (a->esq);
    arv_libera (a->dir);
    free(a);
  }
  return NULL;
}

int eh_espelho(Arvore * arv_a, Arvore * arv_b) {
  if (arv_a == NULL && arv_b == NULL)
    return 1;

  if (arv_a == NULL || arv_b == NULL)
    return 0;

  if (arv_a->info == arv_b->info &&
      eh_espelho(arv_a->esq, arv_b->dir) &&
      eh_espelho(arv_a->dir, arv_b->esq))
    return 1;
  else
    return 0;
}

Arvore * cria_espelho(Arvore * arv_a) {
  if (arv_a != NULL) {
    struct Arvore* temp;

    cria_espelho(arv_a->esq);
    cria_espelho(arv_a->dir);

    temp = arv_a->esq;
    arv_a->esq  = arv_a->dir;
    arv_a->dir = temp;
  }

  return arv_a;
}

int main (int argc, char *argv[]) {
  Arvore *t, *t1, *t2, *t3, *t4, *t5;

  t1 = arv_constroi('d', cria_arv_vazia(), cria_arv_vazia());
  t2 = arv_constroi('b', t1, cria_arv_vazia());
  t3 = arv_constroi('e', cria_arv_vazia(), cria_arv_vazia());
  t4 = arv_constroi('f', cria_arv_vazia(), cria_arv_vazia());
  t5 = arv_constroi('c', t3, t4);
  t  = arv_constroi('a', t2, t5);

  // Arvore *espT, *espT1, *espT2, *espT3, *espT4, *espT5;

  // espT1 = arv_constroi('d', cria_arv_vazia(), cria_arv_vazia());
  // espT2 = arv_constroi('b', cria_arv_vazia(), espT1);
  // espT3 = arv_constroi('e', cria_arv_vazia(), cria_arv_vazia());
  // espT4 = arv_constroi('f', cria_arv_vazia(), cria_arv_vazia());
  // espT5 = arv_constroi('c', espT4, espT3);
  // espT  = arv_constroi('a', espT5, espT2);

  Arvore *espT = t;

  espT = cria_espelho(espT);

  int eh_espelho_ou_nao = eh_espelho(t, espT);

  if (eh_espelho_ou_nao)
    printf("eh espelho\n");
  else
    printf("nao eh espelho\n");

  return 0;
}
