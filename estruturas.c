#pragma warning(disable : 4996)
#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Cadastra as pessoas contidas no arquivo no sistema
// Pré-condição: nome de aruqivo válido,  sem caracteres nao permitidos pelo sistema operacional
// Pós-condição: retorna a lista com as pessoas lidas
ListaPessoa* LerArquivo(char* nomeArquivo, ListaPessoa* pessoas, ListaCPF** cpfs)
{
	FILE* arquivo = fopen(nomeArquivo, "r");
	Pessoa pessoaAuxiliar;

	while (1)
	{

		iniciaPessoa(&pessoaAuxiliar);
		fscanf(arquivo, "%*[ ]");
		fscanf(arquivo, "%[^;]", pessoaAuxiliar.nome);//obgrigatorio
		fscanf(arquivo, "%*c");

		fscanf(arquivo, "%*[ ]");
		fscanf(arquivo, "%d", &pessoaAuxiliar.idade);//obrigatorio
		fscanf(arquivo, "%*c");

		fscanf(arquivo, "%*[ ]");
		fscanf(arquivo, "%c", &pessoaAuxiliar.sexo);//obrigatorio
		fscanf(arquivo, "%*c");

		fscanf(arquivo, "%*[ ]");
		fscanf(arquivo, "%d", &pessoaAuxiliar.rg);//obrigatorio
		fscanf(arquivo, "%*c");

		fscanf(arquivo, "%*[ ]");
		fscanf(arquivo, "%[^;]", pessoaAuxiliar.cpf);//obrigatorio
		fscanf(arquivo, "%*c");

		fscanf(arquivo, "%*[ ]");
		fscanf(arquivo, "%[^;]", pessoaAuxiliar.telefone);
		fscanf(arquivo, "%*c");


		fscanf(arquivo, "%*[ ]");
		fscanf(arquivo, "%[^;]", pessoaAuxiliar.endereco);
		fscanf(arquivo, "%*c");


		fscanf(arquivo, "%*[ ]");
		fscanf(arquivo, "%[^;]", pessoaAuxiliar.profissao);
		fscanf(arquivo, "%*c");


		fscanf(arquivo, "%*[ ]");
		fscanf(arquivo, "%d", &pessoaAuxiliar.prioridade);//obrigatorio
		fscanf(arquivo, "%*c");
		if (feof(arquivo))
		{
			break;

		}

		if ((cpfIsContido(*cpfs, pessoaAuxiliar.cpf)) == 0 && pessoaAuxiliar.nome[0] != '\0' && pessoaAuxiliar.idade != 0 &&
			pessoaAuxiliar.sexo == 'F' || pessoaAuxiliar.sexo == 'M' && pessoaAuxiliar.rg != 0 && pessoaAuxiliar.prioridade != 0)
		{
			pessoas = inserePessoa(pessoas, pessoaAuxiliar);
			*cpfs = insereCpf(*cpfs, pessoaAuxiliar.cpf);
		}


	}

	fclose(arquivo);
	return pessoas;
}

// Insere uma pessoa na lista de pessoas
// Pré-condição: nenhum
// Pós-condiçao: retorna a lista de pessoas com a pessoa inserida
ListaPessoa* inserePessoa(ListaPessoa* pessoas, Pessoa pessoa)
{
	ListaPessoa* listaAuxiliar = (ListaPessoa*)malloc(sizeof(ListaPessoa));

	listaAuxiliar->habitante = pessoa;
	listaAuxiliar->proximo = pessoas;
	return listaAuxiliar;
}

// Localiza uma pessoa na lista de pessoas pelo CPF
// Pré-condição: a string do CPF não pode ser maior que 11 caracteres
// Pós-condição: retorna a pessoa encontrada na lista ou NULL caso não for encontrada
ListaPessoa* FindPessoaByCPF(ListaPessoa* pessoas, char cpf[])
{
	if (strcmp(pessoas->habitante.cpf, cpf) == 0)
	{
		return pessoas;
	}
	else
	{
		return FindPessoaByCPF(pessoas->proximo, cpf);
	}
	return NULL;
}

// Insere um grupo de número info na lista de grupos
// Pré-condição: número info não pode ser negativo
// Pós-condiçao: retorna a lista de grupos com o novo grupo inserido
ListaGrupo* insereGrupo(ListaGrupo* grupo, int numero)
{

	ListaGrupo* aux = (ListaGrupo*)malloc(sizeof(ListaGrupo));
	aux->grupo.numero = numero;
	aux->grupo.bSituacao = 0;
	aux->proximo = grupo;
	return aux;
}

// Remove uma pessoa cadastrada da lista de pessoas
// Pré-condição: o tamanho da string do CPF não pode ser maior que 11 caracteres
// Pós-condiçao: retorna a lista de pessoas com a pessa removida
ListaPessoa* removePessoa(ListaPessoa* pessoas, char cpf[])
{
	ListaPessoa* ant = pessoas;//elemento anterior
	ListaPessoa* p = pessoas;// para encontrar o elemento a ser retirado

	while (p != NULL && strcmp(p->habitante.cpf, cpf) != 0)
	{ //localiza o elemento
		ant = p;
		p = p->proximo;
	}
	if (p != NULL)
	{ //elemento encontrado
		if (p == pessoas)//remoção na cabeça
			pessoas = pessoas->proximo;//atualizaa cabeça
		else//remoção do meio
			ant->proximo = p->proximo;
		free(p);//libera o nó do elemento removido
	}
	else
		printf("Pessoa não encontrada\n");
	return pessoas;//retorna a lista
}

// Inicia a lista com os grupos de 1 a numero_de_grupos, com estoque zerado
// Pré-condição: numero_de_grupos deve ser inteiro positivo
// Pós-condição: retorna a cabeça da lista dos grupos
ListaGrupo* iniciaGrupos(ListaGrupo* grupos, int numero_de_grupos)
{
	int i = 0;
	for (i = 1; i <= numero_de_grupos; i++)
	{
		grupos = insereGrupo(grupos, i);
	}
	return grupos;
}

// Verifica se um determinado CPF já está cadastrado n sistema
// Pre-condição: o tamanho da string do CPF não pode ultrapassar 11 caracteres
// Pós-condiçao:  retorna 1 se o CPF está contido na lista ou 0 se não está contido
int cpfIsContido(ListaCPF* cpfs, char cpf[])
{
	if (cpfs == NULL)
		return 0;
	if (strcmp(cpfs->cpf, cpf) == 0)
		return 1;
	else
		return cpfIsContido(cpfs->prox, cpf);
	return 0;
}

// Insere um novo CPF na lista de CPFs
// Pré-condição: o tamanho da string CPFs pode ter até 11 caracteres
// Pós-condiçao: retorna a lista de CPFs
ListaCPF* insereCpf(ListaCPF* cpfs, char cpf[])
{
	ListaCPF* aux = (ListaCPF*)malloc(sizeof(ListaCPF));
	strcpy(aux->cpf, cpf);
	aux->prox = cpfs;
	return aux;
}

// Altera o conteúdo da estrutura pessoa com informações nulas, "\0", 0, NULL, etc.
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void iniciaPessoa(Pessoa* pessoa)
{
	pessoa->nome[0] = '\0';
	pessoa->idade = 0;
	pessoa->sexo = 'z';
	pessoa->rg = 0;
	pessoa->cpf[0] = '\0';
	pessoa->telefone[0] = '\0';
	pessoa->endereco[0] = '\0';
	pessoa->profissao[0] = '\0';
	pessoa->prioridade = 0;
	pessoa->bVacinada = 0;
	pessoa->covid.dose1.bRealizada = 0;
	pessoa->covid.dose2.bRealizada = 0;
}

// Libera um grupo da lista de grupos
// Pré-condição: número info não pode ser negativo
// Pós-condiçao: retorna a lista de grupos com o grupo liberado
ListaGrupo* liberaGrupo(ListaGrupo* grupos, int info)
{
	ListaGrupo* grupoSolicitado = FindGrupoByNumber(grupos, info);

	if (grupoSolicitado->grupo.numero == 1)
		grupoSolicitado->grupo.bSituacao = 1;//libera o grupo por ser o primeiro sem consultar
	else
	{
		ListaGrupo* aux = FindGrupoByNumber(grupos, info - 1);//info - 1, pois precisa verficiar o grupo anteiror para liberar
		if (aux->grupo.bSituacao == 1)//se o grupo anterior está  liberado
			grupoSolicitado->grupo.bSituacao = 1;//libera o grupo
		else
			printf("O grupo anterior deve ser liberado primeiro\n");
	}
	return grupos;
}

// Encontra um grupo prioritário pelo seu número
// Pre-condição: o número info deve ser inteiro positivo
// Pós-condiçao: retorna a vacina encontrada na lista
ListaGrupo* FindGrupoByNumber(ListaGrupo* grupos, int info)
{
	if (grupos->grupo.numero == info)
		return grupos;
	else
		return FindGrupoByNumber(grupos->proximo, info);
	return NULL;
}

// Insere uma nova marca de vacina com seu estoque, se houver
// Pré-condição: nenhuma
// Pós-condiçao: retorna a lista de vacinas com a nova marca inserida
ListaVacinas* insereVacina(ListaVacinas* vacinas, Vacina vacina)
{
	ListaVacinas* listaAuxiliar = (ListaVacinas*)malloc(sizeof(ListaVacinas));

	listaAuxiliar->vacina = vacina;
	listaAuxiliar->proximo = vacinas;
	return listaAuxiliar;
}

// Encontra uma marca de vacina pelo seu nome
// Pré-condição: nenhuma
// Pós-condição: retorna a vacina encontrada na lista ou retorna NULL se não achar
ListaVacinas* FindVacinaByName(ListaVacinas* vacinas, char nomeVacina[])
{
	if (strcmp(vacinas->vacina.nome, nomeVacina) == 0)
		return vacinas;
	else
		return FindVacinaByName(vacinas->proximo, nomeVacina);
	return NULL;
}

// Insere estoque de vacina, de uma marca nova ou já cadastrada
// Pré-condição: quantidade de vacinas não pode ser negativa
// Pós-condiçao: retorna lista de vacinas com o novo estoque inserido
ListaVacinas* registrarLoteVacina(ListaVacinas* vacinas, char marca[], int quantidade)
{
	Vacina vacina;
	vacina.estoque = quantidade;
	strcpy(vacina.nome, marca);

	if (isVacinaRegistrada(vacinas, marca))//vacina nao registrada deve ser inserida no catálago
	{
		ListaVacinas* aux = FindVacinaByName(vacinas, marca);
		aux->vacina.estoque += quantidade;
	}
	else//vacina ja inserida, só deve ter seu estoque atualizado.
	{
		vacinas = insereVacina(vacinas, vacina);//insere a vacina
	}
	return vacinas;
}

// Insere estoque de vacina, de uma marca nova ou já cadastrada
// Pré-condição: quantidade de vacinas não pode ser negativa
// Pós-condiçao: retorna lista de vacinas com o novo estoque inserido
int isVacinaRegistrada(ListaVacinas* vacinas, char marca[])
{
	if (vacinas == NULL)
		return 0;
	if (strcmp(vacinas->vacina.nome, marca) == 0)
		return 1;
	else
		return isVacinaRegistrada(vacinas->proximo, marca);
}

// Verifica se um grupo prioritário está liberado para vacinação
// Pré-condição: o número info deve ser um inteiro positivo
// Pós-condiçao: retorna 1 se o grupo está liberado e 0 se não estiver liberado
int isLiberado(ListaGrupo* grupos, int info)
{
	ListaGrupo* aux = FindGrupoByNumber(grupos, info);//acha o grupo
	return aux->grupo.bSituacao;//retorna a situação
}

// Verifica se há estoque de uma determinada marca de vacina
// Pré-condição: a marca da vacina já deve estar cadastrada
// Pós-condiçao: retorna 1 se a marca tem estoque disponível e 0 se não
int isThereEstoqueVacinaByMarca(ListaVacinas* vacinas, char nome[])
{
	ListaVacinas* aux = FindVacinaByName(vacinas, nome);
	if (aux->vacina.estoque > 0)
		return 1;
	else
		return 0;
}

// Verifica a partir do CPF da pessoa se ela já recebeu as duas doses
// Pré-condição: o tamanho da string do CPF não pode ultrapassar 11 caracteres
// Pós-condiçao: retorna 1 se a pessoa já recebeu as duas doses da vacina e 0 se ela ainda não recebeu
int isVacinada(ListaPessoa* pessoas, char cpf[])
{
	ListaPessoa* aux = FindPessoaByCPF(pessoas, cpf);
	if (aux->habitante.bVacinada == 1)
		return 1;
	else
		return 0;
}

// Verifica se uma pessoa já tomou a primeira dose da vacina
// Pré-condição: o tamanho da string do CPF não pode ultrapassar 11 caracteres
// Pós-condiçao: retorna 1 se a pessoa já recebeu a primeira dose ou 0 se não recebeu
int hasPrimeiraDose(ListaPessoa* pessoas, char cpf[])
{
	ListaPessoa* aux = FindPessoaByCPF(pessoas, cpf);
	return aux->habitante.covid.dose1.bRealizada;
}

// Acha uma marca de vacina com estoque
// Pré-condição: nenhuma
// Pós-condiçao: retorna uma string com a marca com estoque registrada
char* vacinaComEstoque(ListaVacinas* vacinas)
{
	if (vacinas == NULL)
		return NULL;
	if (isThereEstoqueVacinaByMarca(vacinas, vacinas->vacina.nome))
		return vacinas->vacina.nome;
	else
		return vacinaComEstoque(vacinas->proximo);
}

// Verifica se tem estoque de qualquer marca de vacina
// Pré-condição: nenhuma
// Pós-condiçao: retorna 1 se houver qualquer marca com estoque de vacinas
int isThereEstoqueGeral(ListaVacinas* vacinas)
{
	if (vacinas == NULL)
		return 0;
	else
		return 1;
}

// Remove uma unidade de vacina do estoque de determinada marca
// Pré-condição: nenhuma
// Pós-condiçao: retorna a lista de vacinas com o estoque já alterado
ListaVacinas* remove1Dose(ListaVacinas* vacinas, char marca[])
{
	ListaVacinas* aux = FindVacinaByName(vacinas, marca);
	aux->vacina.estoque--;//remove 1 vacina do estoque
	return vacinas;
}

// Registra a vacinação de um habitante cadastrado no sistema
// Pré-condição: o tamanho da string CPF não pode ultrapassar 11 caracteres e deve já estar inserido no sistema
// Pós-condiçao: retorna a lista de pessoas tendo modificado o estado de sua vacinação
ListaPessoa* RegistraVacinacao(ListaPessoa* pessoas, ListaGrupo* grupos, ListaVacinas** vacinas, char cpf[])
{
	struct tm* data_hora_atual;
	time_t segundos;//vari�vel para os segundos
	time(&segundos);
	data_hora_atual = localtime(&segundos);
	ListaPessoa* pessoaAtual = FindPessoaByCPF(pessoas, cpf);//acha a pessoa

	if (isVacinada(pessoas, cpf))
	{
		printf("Habitante já vacinado\n");
		return pessoas;
	}

	if (!(hasPrimeiraDose(pessoas, cpf)))//se tem primeira dose, entao é a segunda dose que vai tomar, senão é a primeira
	{
		if (isLiberado(grupos, pessoaAtual->habitante.prioridade) && isThereEstoqueGeral(*vacinas))//se o grupo da pesssoa ta liberado e o há vacinas pode vacinar.
		{
			char* nome_vacina = vacinaComEstoque(*vacinas);//retorna o nome da vacina disponivel
			(*vacinas) = remove1Dose(*vacinas, nome_vacina);//desconta 1 dose da vacina usada
			pessoaAtual->habitante.covid.dose1.bRealizada = 1;// torna verdadeira a realização
			strcpy(pessoaAtual->habitante.covid.dose1.marca, nome_vacina);//copia o nome da marca
			pessoaAtual->habitante.covid.dose1.data.dia = data_hora_atual->tm_mday;//regrista a data mes e ano
			pessoaAtual->habitante.covid.dose1.data.mes = data_hora_atual->tm_mon + 1;
			pessoaAtual->habitante.covid.dose1.data.ano = data_hora_atual->tm_year + 1900;
		}
		else
		{
			if (isLiberado(grupos, pessoaAtual->habitante.prioridade) == 0)
				printf("O habitante não pode ser vacinado, porque seu grupo não está liberado para vacinação\n");
			if (isThereEstoqueGeral(*vacinas) == 0)
				printf("Não é possível vacinar, estoque zerado\n");
		}
	}
	else
	{
		//verifica o estoque especifico, pois é segunda dose, precisa ser a mesma marca
		if (isThereEstoqueVacinaByMarca(*vacinas, pessoaAtual->habitante.covid.dose1.marca) && isLiberado(grupos, pessoaAtual->habitante.prioridade))
		{
			(*vacinas) = remove1Dose(*vacinas, pessoaAtual->habitante.covid.dose1.marca);//desconta 1 dose da mesma vacina usada na primeira dose.
			pessoaAtual->habitante.covid.dose2.data.dia = data_hora_atual->tm_mday;//regrista a data mes e ano
			pessoaAtual->habitante.covid.dose2.data.mes = data_hora_atual->tm_mon + 1;
			pessoaAtual->habitante.covid.dose2.data.ano = data_hora_atual->tm_year + 1900;
			pessoaAtual->habitante.bVacinada = 1;//pessoa está vacinada.
			pessoaAtual->habitante.covid.dose2.bRealizada = 1;
		}
		else
		{
			if (isLiberado(grupos, pessoaAtual->habitante.prioridade) == 0)
				printf("O habitante não pode ser vacinado, porque seu grupo não está liberado para vacinação\n");
			if (isThereEstoqueVacinaByMarca(*vacinas, pessoaAtual->habitante.covid.dose1.marca) == 0)
				printf("Não é possível vacinar, estoque zerado\n");
		}
	}
	return pessoas;
}

// Gera um relatório do  número de doses no estoque por tipo de vacina
// Pré-condição: nenhuma
// Pós-condiçao: nenhuma
void relatDosesEstoqVacin(ListaVacinas* vacinas)
{
	if (vacinas != NULL)
	{
		printf("Marca: %s\n", vacinas->vacina.nome);
		printf("Estoque: %d\n", vacinas->vacina.estoque);
		relatDosesEstoqVacin(vacinas->proximo);
	}
}

// Conta a quantidade de habitantes que já receberam a primeira dose da vacina
// Pré-condição: nenhuma
// Pós-condiçao: retorna a quantidade de habitantes que já receberam a primeira dose da vacina
int contaVacinados1Dose(ListaPessoa* pessoas)
{
	int soma = 0;
	if (pessoas == NULL)
		return 0;
	while (pessoas != NULL)
	{
		if (pessoas->habitante.covid.dose1.bRealizada == 1)
			soma++;
		pessoas = pessoas->proximo;
	}
	return soma;
}

// Gera um relatório da listra de habitantes (nome, CPF) vacinados somente com a primeira dose
// Pré-condição: nenhuma
// Pós-condiçao: nenhuma
void relatVacinados1Dose(ListaPessoa* pessoas)
{

	if (pessoas != NULL)
	{
		if (pessoas->habitante.covid.dose1.bRealizada == 1)
		{
			printf("Nome: %s\n", pessoas->habitante.nome);
			printf("CPF: %s\n", pessoas->habitante.cpf);
		}
		relatVacinados1Dose(pessoas->proximo);
	}
}

// Gera um relatório com o número de habitantes vacinados, já com a segunda dose
// Pré-condição: nenhuma
// Pós-condiçao: nenhuma
void relatNumVacinados2Doses(int num)
{
	printf("Número de vacinados com 2 doses: %d\n", num);
}

// Conta quantas pessoas já receberam as duas doses de uma vacina
// Pré-condição: nenhuma
// Pós-condiçao: retorna a quantidade de pessoas que já receberam as duas doses de uma vacina
int contaVacinados2Doses(ListaPessoa* pessoas)
{
	int soma = 0;
	if (pessoas == NULL)
		return 0;
	while (pessoas != NULL)
	{
		if (pessoas->habitante.bVacinada == 1)
			soma++;
		pessoas = pessoas->proximo;
	}
	return soma;
}

// Imprime as apenas as pessoas do grupo informado que não estão vacinadas
// Pré-condição: o número do grupo deve ser um inteiro positivo
// Pós-condiçao: nenhuma
void imprimeGrupoNaoVacinado(ListaPessoa* pessoas, int grupo)
{
	if (pessoas != NULL)
	{
		if (pessoas->habitante.prioridade == grupo)
		{
			if (pessoas->habitante.bVacinada == 0)
			{
				printf("Nome: %s\n", pessoas->habitante.nome);
				printf("CPF: %s\n", pessoas->habitante.cpf);
			}
		}
		imprimeGrupoNaoVacinado(pessoas->proximo, grupo);
	}
}

// Conta a quantidade de grupos prioritários
// Pré-condição: nenhuma
// Pós-condiçao: retorna a quantidade de grupos prioritários
int conta_grupos(ListaGrupo* grupos)
{
	int soma = 0;
	if (grupos == NULL)
		return 0;
	while (grupos != NULL)
	{
		soma++;
		grupos = grupos->proximo;
	}
	return soma;
}

// Gera um relatório com a lista de habitantes (nome, CPF) não vacinados agrupados por grupo prioritário
// Pré-condição: nenhuma
// Pós-condiçao: nenhuma
void relatNaoVacinados(ListaPessoa* pessoas, ListaGrupo* grupos)
{
	int max = conta_grupos(grupos);
	int i = 0;
	for (i = 0; i < max; i++)
	{
		printf("GRUPO %d:\n", i + 1);
		imprimeGrupoNaoVacinado(pessoas, i + 1);
	}
}

// Gera um relatório do número de habitantes por grupo prioritário
// Pré-condição: nenhuma
// Pós-condiçao: nenhuma
void relatHabitantesPorGrupo(ListaPessoa* pessoas, ListaGrupo* grupos)
{
	int max = conta_grupos(grupos);
	int i = 0;
	for (i = 0; i < max; i++)
	{
		printf("Grupo%d: %d\n", i + 1, conta_habitantes_grupo_atual(pessoas, i + 1));
	}
}

// Conta a quantidade de pessoas em determinado grupo
// Pré-condição: o número do grupo deve ser um inteiro positivo
// Pós-condiçao: retorna a quantidade de pessoas no grupo fornecido
int conta_habitantes_grupo_atual(ListaPessoa* pessoas, int grupo)
{
	int soma = 0;
	if (pessoas == NULL)
		return 0;
	while (pessoas != NULL)
	{
		if (pessoas->habitante.prioridade == grupo)
			soma++;
		pessoas = pessoas->proximo;
	}
	return soma;
}

// Insere uma pessoa no sistema a partir das informações fornecidas pelo teclado
// Pré-condição: nenhuma
// Pós-condiçao: retorna a lista de pessoas com a pessoa inserida
ListaPessoa* LerTeclado(ListaPessoa* pessoas, ListaCPF** cpfs)
{
	Pessoa pessoaAuxiliar;

	iniciaPessoa(&pessoaAuxiliar);

	printf("Campos obrigatórios devem ser preenchidos!\n");

	printf("Digite o nome(obrigatório):");
	scanf("%[^\n]", pessoaAuxiliar.nome);//obgrigatorio
	scanf("%*c");

	printf("Digite a idade(obrigatório):");
	scanf("%d", &pessoaAuxiliar.idade);//obrigatorio
	scanf("%*c");

	printf("Digite o sexo F para femino e M para masculino(obrigatório):");
	scanf("%c", &pessoaAuxiliar.sexo);//obrigatorio

	printf("Digite o RG(obrigatório):");
	scanf("%d", &pessoaAuxiliar.rg);//obrigatorio
	scanf("%*c");

	printf("Digite o CPF(obrigatório):");
	scanf("%[^\n]", pessoaAuxiliar.cpf);//obrigatorio
	scanf("%*c");
	while (cpfIsContido(*cpfs, pessoaAuxiliar.cpf))
	{
		printf("Esse CPF já foi cadastrado, insira outro\n");
		printf("Digite o CPF(obrigatório):");
		scanf("%[^\n]", pessoaAuxiliar.cpf);//obrigatorio
		scanf("%*c");
	}

	printf("Digite o telefone:");
	scanf("%[^\n]", pessoaAuxiliar.telefone);
	scanf("%*c");

	printf("Digite o endereço:");
	scanf("%[^\n]", pessoaAuxiliar.endereco);
	scanf("%*c");

	printf("Digite a profissão:");
	scanf("%[^\n]", pessoaAuxiliar.profissao);
	scanf("%*c");

	printf("Digite  a prioridade:");
	scanf("%d", &pessoaAuxiliar.prioridade);//obrigatorio
	scanf("%*c");

	if ((cpfIsContido(*cpfs, pessoaAuxiliar.cpf)) == 0 && pessoaAuxiliar.nome[0] != '\0' && pessoaAuxiliar.idade != 0 &&
		pessoaAuxiliar.sexo == 'F' || pessoaAuxiliar.sexo == 'M' && pessoaAuxiliar.rg != 0 && pessoaAuxiliar.prioridade != 0)
	{
		pessoas = inserePessoa(pessoas, pessoaAuxiliar);
		*cpfs = insereCpf(*cpfs, pessoaAuxiliar.cpf);
	}
	return pessoas;
}

// Informa as opções de ação disponíveis no sistema
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void MenuPrincipal(ListaPessoa** pessoas, ListaGrupo** grupos, ListaVacinas** vacinas, ListaCPF** cpfs)
{
	int numero;

	printf("Escolha uma opção\n");
	printf("1.Vacinação\n");
	printf("2.Relatórios\n");
	printf("3.Sair\n");

	scanf("%d", &numero);
	scanf("%*c");
	system("cls");
	switch (numero)
	{
	case 1:
		MenuVacinacao(pessoas, grupos, vacinas, cpfs);
		break;
	case 2:
		MenuRelatorios(pessoas, grupos, vacinas, cpfs);
		break;
	case 3:
		printf("Até mais\n");
		system("pause");
		exit(0);
		break;
	default:
		printf("Opção inválida, tente novamente\n");// caso nao seja um op�ao valida
		MenuPrincipal(pessoas, grupos, vacinas, cpfs);
	}
	MenuPrincipal(pessoas, grupos, vacinas, cpfs);
}

// Contém todos os relatórios necessários
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void MenuRelatorios(ListaPessoa** pessoas, ListaGrupo** grupos, ListaVacinas** vacinas, ListaCPF** cpfs)
{
	int numero;

	printf("Escolha uma opção de relatório\n");
	printf("1.Número de doses no estoque por tipo de vacina\n");
	printf("2.Lista de habitantes vacinados com 1 dose\n");
	printf("3.Número de vacinados com 2 doses\n");
	printf("4.Lista de habitantes não vacinados agrupados pelo grupo prioritário\n");
	printf("5.Número de habitantes por grupo prioritário\n");
	printf("6.Menu Principal\n");

	scanf("%d", &numero);
	scanf("%*c");
	system("cls");
	switch (numero)
	{
	case 1:
	    if(*vacinas == NULL)
            printf("Não há estoques de vacinas.\n\n");
		relatDosesEstoqVacin(*vacinas);
		break;
	case 2:
	    if (contaVacinados1Dose(*pessoas) == 0)
        {
		printf("Nenhuma Pessoa Vacinada com a 1ª dose!\n\n");
        }
		relatVacinados1Dose(*pessoas);
		break;
	case 3:
		relatNumVacinados2Doses(contaVacinados2Doses(*pessoas));
		break;
	case 4:
		relatNaoVacinados(*pessoas, *grupos);
		break;
	case 5:
		relatHabitantesPorGrupo(*pessoas, *grupos);
		break;
	case 6:
		MenuPrincipal(pessoas, grupos, vacinas, cpfs);
	default:
		printf("Opção inválida, tente novamente\n\n");// caso nao seja um op�ao valida
		MenuRelatorios(pessoas, grupos, vacinas, cpfs);
	}
	MenuRelatorios(pessoas, grupos, vacinas, cpfs);
}

// Apresenta as opções de vacinação
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void MenuVacinacao(ListaPessoa** pessoas, ListaGrupo** grupos, ListaVacinas** vacinas, ListaCPF** cpfs)
{
	int numero;

	printf("Escolha uma opção de Vacinação\n");
	printf("1.Retirar habitante\n");
	printf("2.Liberar grupo prioritário\n");
	printf("3.Registrar vacinação\n");
	printf("4.Registrar lote de vacinas\n");
	printf("5.Cadastrar habitante\n");
	printf("6.Menu Principal\n");

	scanf("%d", &numero);
	scanf("%*c");
	system("cls");
	switch (numero)
	{
	case 1:
		retirarHabitante(pessoas);
		break;
	case 2:
		LiberarGrupo(grupos);
		break;
	case 3:
		registrarVacinacao(pessoas, *grupos, vacinas);
		break;
	case 4:
		registrarLoteVacinas(vacinas);
		break;
	case 5:
		*pessoas = LerTeclado(*pessoas, cpfs);
		break;
	case 6:
		MenuPrincipal(pessoas, grupos, vacinas, cpfs);
		break;
	default:
		printf("Opção inválida, tente novamente\n");// caso nao seja um opçao valida
		MenuVacinacao(pessoas, grupos, vacinas, cpfs);
	}
	MenuVacinacao(pessoas, grupos, vacinas, cpfs);
}

// Apresenta o menu para retirar um habitante
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void retirarHabitante(ListaPessoa** pessoas)
{
	char cpf[MAX_CPF];
	printf("Digite o CPF da pessoa a ser removida:");
	scanf("%[^\n]s", cpf);
	scanf("%*c");
	(*pessoas) = removePessoa(*pessoas, cpf);
}

// Apresenta o menu para liberar um grupo
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void LiberarGrupo(ListaGrupo** grupos)
{
	int grupo;
	printf("Digite o numero do grupo a ser liberado: de% d a% d\n", 1, conta_grupos(*grupos));
	scanf("%d", &grupo);
	*grupos = liberaGrupo(*grupos, grupo);
}

// Apresenta um menu para registrar uma vacinação
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void registrarVacinacao(ListaPessoa** pessoas, ListaGrupo* grupos, ListaVacinas** vacinas)
{
	char cpf[MAX_CPF];
	printf("Digite o CPF da pessoa a ser vacinada:");
	scanf("%[^\n]", cpf);
	scanf("%*c");
	*pessoas = RegistraVacinacao(*pessoas, grupos, vacinas, cpf);
}

// Apresenta um menu para registrar lotes de vacinas
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void registrarLoteVacinas(ListaVacinas** vacinas)
{
	char marca[MAX_MARCA];
	int quantidade;
	printf("Digite a marca da vacina:");
	scanf("%[^\n]", marca);
	scanf("%*c");
	printf("Digite a quantidade a ser adicionada ao estoque:");
	scanf("%d", &quantidade);
	*vacinas = registrarLoteVacina(*vacinas, marca, quantidade);
}
