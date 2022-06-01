#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "estruturas.h"
#include <string.h>

int main()
{
	setlocale(LC_ALL, "portuguese");// possibilita imprimir caracteres usados na lingua portuguesa;
	ListaPessoa* pessoas = NULL;
	ListaCPF* cpfs = NULL;
	ListaGrupo* grupos = NULL;
	ListaVacinas* vacinas = NULL;
	ListaVacinas* testeVacina = NULL;
	grupos = iniciaGrupos(grupos, MAX_GRUPOS);

	pessoas = LerArquivo("dados.txt", pessoas,&cpfs);
	MenuPrincipal(&pessoas, &grupos, &vacinas, &cpfs);

	return 0;
}
