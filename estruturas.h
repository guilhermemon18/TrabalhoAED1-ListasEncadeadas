#pragma once
#pragma warning(disable : 4996)
#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#define MAX_NOME 50
#define MAX_CPF 12
#define MAX_TELEFONE 12
#define MAX_ENDERECO 150
#define MAX_PROFISSAO 50
#define MAX_MARCA 30
#define MAX_GRUPOS 5

// Estrutura para datas
typedef struct
{
	int dia;
	int mes;
	int ano;
}Data;

// Estrutura para as doses das vacinas
typedef struct
{
	int bRealizada;// 0 ou 1, realizada ou n�o
	Data data;
	char marca[MAX_MARCA];
}Dose;

// Estrutura com as doses de cada vacina��o
typedef struct
{
	Dose dose1;
	Dose dose2;
}Vacinacao;

// Estrutura com os dados de uma pessoa
typedef struct {
	char nome[MAX_NOME];
	int idade;
	char sexo;
	int rg;
	char cpf[MAX_CPF];
	char telefone[MAX_TELEFONE];
	char endereco[MAX_ENDERECO];
	char profissao[MAX_PROFISSAO];
	int prioridade;
	int bVacinada;
	Vacinacao covid;
}Pessoa;

// Estrutura para o grupo a ser vacinado
typedef struct
{
	int numero;     //numero do grupo
	int bSituacao;  // 0 ou 1, representa verdadeiro ou falso para a libera��o do grupo
}Grupo;

// Estrutura para vacina
typedef struct
{
	char nome[MAX_NOME];
	int estoque;
}Vacina;

// Lista de pessoas cadastradas
typedef struct noPessoa
{
	Pessoa habitante;
	struct noPessoa* proximo;
}ListaPessoa;

// Lista de cpf j� cadastrados no sistema
typedef struct noCPF
{
	char cpf[MAX_CPF];
	struct noCPF* prox;
}ListaCPF;

// Lista para os 5 grupos de prioridade
typedef struct noGrupo
{
	Grupo grupo;
	struct noGrupo* proximo;
}ListaGrupo;

// Lista para as vacinas
typedef struct noVacinas
{
	Vacina vacina;
	struct noVacinas * proximo;
}ListaVacinas;

//FUN��ES DE MENU

// Informa as op��es de a��o dispon�veis no sistema
// Pr�-condi��o: nenhuma
// P�s-condi��o: nenhuma
void MenuPrincipal(ListaPessoa** pessoas,ListaGrupo** grupos,ListaVacinas** vacinas,ListaCPF** cpfs);

// Cont�m todos os relat�rios necess�rios
// Pr�-condi��o: nenhuma
// P�s-condi��o: nenhuma
void MenuRelatorios(ListaPessoa** pessoas, ListaGrupo** grupos, ListaVacinas** vacinas, ListaCPF** cpfs);

// Apresenta as op��es de vacina��o
// Pr�-condi��o: nenhuma
// P�s-condi��o: nenhuma
void MenuVacinacao(ListaPessoa** pessoas, ListaGrupo** grupos, ListaVacinas** vacinas, ListaCPF** cpfs);

// Apresenta o menu para retirar um habitante
// Pr�-condi��o: nenhuma
// P�s-condi��o: nenhuma
void retirarHabitante(ListaPessoa** pessoas);

// Apresenta o menu para liberar um grupo
// Pr�-condi��o: nenhuma
// P�s-condi��o: nenhuma
void LiberarGrupo(ListaGrupo** grupos);

// Apresenta um menu para registrar uma vacina��o
// Pr�-condi��o: nenhuma
// P�s-condi��o: nenhuma
void registrarVacinacao(ListaPessoa** pessoas, ListaGrupo* grupos, ListaVacinas** vacinas);

// Apresenta um menu para registrar lotes de vacinas
// Pr�-condi��o: nenhuma
// P�s-condi��o: nenhuma
void registrarLoteVacinas(ListaVacinas** vacinas);

//FUN��ES DE INICIALIZA��O

// Inicia a lista com os grupos de 1 a numero_de_grupos, com estoque zerado
// Pr�-condi��o: numero_de_grupos deve ser inteiro positivo
// P�s-condi��o: retorna a cabe�a da lista dos grupos
ListaGrupo* iniciaGrupos(ListaGrupo* grupos, int numero_de_grupos);

// Altera o conte�do da estrutura pessoa com informa��es nulas, "\0", 0, NULL, etc.
// Pr�-condi��o: nenhuma
// P�s-condi��o: nenhuma
void iniciaPessoa(Pessoa* pessoa);

//FUN��ES DE INSER��O

// Cadastra as pessoas contidas no arquivo no sistema
// Pr�-condi��o: nome de aruqivo v�lido,  sem caracteres nao permitidos pelo sistema operacional
// P�s-condi��o: retorna a lista com as pessoas lidas
ListaPessoa* LerArquivo(char* nomeArquivo, ListaPessoa* pessoas, ListaCPF** cpfs);

// Insere um novo CPF na lista de CPFs
// Pr�-condi��o: o tamanho da string CPFs pode ter at� 11 caracteres
// P�s-condi�ao: retorna a lista de CPFs
ListaCPF* insereCpf(ListaCPF* cpfs, char cpf[]);

// Insere uma pessoa na lista de pessoas
// Pr�-condi��o: nenhum
// P�s-condi�ao: retorna a lista de pessoas com a pessoa inserida
ListaPessoa* inserePessoa(ListaPessoa* pessoas, Pessoa pessoa);

// Insere um grupo de n�mero info na lista de grupos
// Pr�-condi��o: n�mero info n�o pode ser negativo
// P�s-condi�ao: retorna a lista de grupos com o novo grupo inserido
ListaGrupo* insereGrupo(ListaGrupo* grupo, int info);

// Libera um grupo da lista de grupos
// Pr�-condi��o: n�mero info n�o pode ser negativo
// P�s-condi�ao: retorna a lista de grupos com o grupo liberado
ListaGrupo* liberaGrupo(ListaGrupo* grupos, int info);

// Insere uma nova marca de vacina com seu estoque, se houver
// Pr�-condi��o: nenhuma
// P�s-condi�ao: retorna a lista de vacinas com a nova marca inserida
ListaVacinas* insereVacina(ListaVacinas* vacinas, Vacina vacina);

// Insere estoque de vacina, de uma marca nova ou j� cadastrada
// Pr�-condi��o: quantidade de vacinas n�o pode ser negativa
// P�s-condi�ao: retorna lista de vacinas com o novo estoque inserido
ListaVacinas* registrarLoteVacina(ListaVacinas* vacinas, char marca[], int quantidade);

// Acha uma marca de vacina com estoque
// Pr�-condi��o: nenhuma
// P�s-condi�ao: retorna uma string com a marca com estoque registrada
char* vacinaComEstoque(ListaVacinas* vacinas);

// Registra a vacina��o de um habitante cadastrado no sistema
// Pr�-condi��o: o tamanho da string CPF n�o pode ultrapassar 11 caracteres e deve j� estar inserido no sistema
// P�s-condi�ao: retorna a lista de pessoas tendo modificado o estado de sua vacina��o
ListaPessoa* RegistraVacinacao(ListaPessoa* pessoas, ListaGrupo* grupos, ListaVacinas** vacinas, char cpf[]);

// Conta a quantidade de grupos priorit�rios
// Pr�-condi��o: nenhuma
// P�s-condi�ao: retorna a quantidade de grupos priorit�rios
int conta_grupos(ListaGrupo* grupos);

// Insere uma pessoa no sistema a partir das informa��es fornecidas pelo teclado
// Pr�-condi��o: nenhuma
// P�s-condi�ao: retorna a lista de pessoas com a pessoa inserida
ListaPessoa* LerTeclado(ListaPessoa* pessoas, ListaCPF** cpfs);

//FUN��ES DE BUSCA:

// Localiza uma pessoa na lista de pessoas pelo CPF
// Pr�-condi��o: a string do CPF n�o pode ser maior que 11 caracteres
// P�s-condi��o: retorna a pessoa encontrada na lista ou NULL caso n�o for encontrada
ListaPessoa* FindPessoaByCPF(ListaPessoa* pessoas, char cpf[]);

// Encontra uma marca de vacina pelo seu nome
// Pr�-condi��o: nenhuma
// P�s-condi��o: retorna a vacina encontrada na lista ou retorna NULL se n�o achar
ListaVacinas* FindVacinaByName(ListaVacinas* vacinas, char nomeVacina[]);

// Encontra um grupo priorit�rio pelo seu n�mero
// Pre-condi��o: o n�mero info deve ser inteiro positivo
// P�s-condi�ao: retorna a vacina encontrada na lista
ListaGrupo* FindGrupoByNumber(ListaGrupo* grupos, int info);

//FUN��ES DE VERIFIC���O:

// Verifica se um determinado CPF j� est� cadastrado n sistema
// Pre-condi��o: o tamanho da string do CPF n�o pode ultrapassar 11 caracteres
// P�s-condi�ao:  retorna 1 se o CPF est� contido na lista ou 0 se n�o est� contido
int cpfIsContido(ListaCPF* cpfs, char cpf[]);

// Verifica se uma pessoa j� tomou a primeira dose da vacina
// Pr�-condi��o: o tamanho da string do CPF n�o pode ultrapassar 11 caracteres
// P�s-condi�ao: retorna 1 se a pessoa j� recebeu a primeira dose ou 0 se n�o recebeu
int hasPrimeiraDose(ListaPessoa* pessoas, char cpf[]);

// Verifica a partir do CPF da pessoa se ela j� recebeu as duas doses
// Pr�-condi��o: o tamanho da string do CPF n�o pode ultrapassar 11 caracteres
// P�s-condi�ao: retorna 1 se a pessoa j� recebeu as duas doses da vacina e 0 se ela ainda n�o recebeu
int isVacinada(ListaPessoa* pessoas, char cpf[]);

// Verifica se h� estoque de uma determinada marca de vacina
// Pr�-condi��o: a marca da vacina j� deve estar cadastrada
// P�s-condi�ao: retorna 1 se a marca tem estoque dispon�vel e 0 se n�o
int isThereEstoqueVacinaByMarca(ListaVacinas* vacinas, char nome[]);

// Verifica se um grupo priorit�rio est� liberado para vacina��o
// Pr�-condi��o: o n�mero info deve ser um inteiro positivo
// P�s-condi�ao: retorna 1 se o grupo est� liberado e 0 se n�o estiver liberado
int isLiberado(ListaGrupo* grupos, int info);

// Verifica se tem estoque de qualquer marca de vacina
// Pr�-condi��o: nenhuma
// P�s-condi�ao: retorna 1 se houver qualquer marca com estoque de vacinas
int isThereEstoqueGeral(ListaVacinas* vacinas);

// Verifica se uma marca de vacina est� registrada no sistema
// Pr�-condi��o: nenhuma
// P�s-condi�ao: retorna 1 se a marca j� est� registrada e 0 se ainda n�o foi registrada
int isVacinaRegistrada(ListaVacinas* vacinas, char marca[]);

//FUN��ES DE REMO��O

// Remove uma pessoa cadastrada da lista de pessoas
// Pr�-condi��o: o tamanho da string do CPF n�o pode ser maior que 11 caracteres
// P�s-condi�ao: retorna a lista de pessoas com a pessa removida
ListaPessoa* removePessoa(ListaPessoa* pessoas, char cpf[]);

// Remove uma unidade de vacina do estoque de determinada marca
// Pr�-condi��o: nenhuma
// P�s-condi�ao: retorna a lista de vacinas com o estoque j� alterado
ListaVacinas* remove1Dose(ListaVacinas* vacinas, char marca[]);

//FUN��ES DE RELAT�RIO

// Gera um relat�rio do  n�mero de doses no estoque por tipo de vacina
// Pr�-condi��o: nenhuma
// P�s-condi�ao: nenhuma
void relatDosesEstoqVacin(ListaVacinas* vacinas);

// Gera um relat�rio da listra de habitantes (nome, CPF) vacinados somente com a primeira dose
// Pr�-condi��o: nenhuma
// P�s-condi�ao: nenhuma
void relatVacinados1Dose(ListaPessoa* pessoas);

// Gera um relat�rio com o n�mero de habitantes vacinados, j� com a segunda dose
// Pr�-condi��o: nenhuma
// P�s-condi�ao: nenhuma
void relatNumVacinados2Doses(int num);

// Conta quantas pessoas j� receberam as duas doses de uma vacina
// Pr�-condi��o: nenhuma
// P�s-condi�ao: retorna a quantidade de pessoas que j� receberam as duas doses de uma vacina
int contaVacinados2Doses(ListaPessoa* pessoas);

// Imprime as apenas as pessoas do grupo informado que n�o est�o vacinadas
// Pr�-condi��o: o n�mero do grupo deve ser um inteiro positivo
// P�s-condi�ao: nenhuma
void imprimeGrupoNaoVacinado(ListaPessoa* pessoas, int grupo);

// Gera um relat�rio com a lista de habitantes (nome, CPF) n�o vacinados agrupados por grupo priorit�rio
// Pr�-condi��o: nenhuma
// P�s-condi�ao: nenhuma
void relatNaoVacinados(ListaPessoa* pessoas,ListaGrupo* grupos);

// Gera um relat�rio do n�mero de habitantes por grupo priorit�rio
// Pr�-condi��o: nenhuma
// P�s-condi�ao: nenhuma
void relatHabitantesPorGrupo(ListaPessoa* pessoas,ListaGrupo* grupos);

// Conta a quantidade de pessoas em determinado grupo
// Pr�-condi��o: o n�mero do grupo deve ser um inteiro positivo
// P�s-condi�ao: retorna a quantidade de pessoas no grupo fornecido
int conta_habitantes_grupo_atual(ListaPessoa* pessoas, int grupo);

// Conta a quantidade de habitantes que j� receberam a primeira dose da vacina
// Pr�-condi��o: nenhuma
// P�s-condi�ao: retorna a quantidade de habitantes que j� receberam a primeira dose da vacina
int contaVacinados1Dose(ListaPessoa* pessoas);

#endif // ESTRUTURAS_H
