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
	int bRealizada;// 0 ou 1, realizada ou não
	Data data;
	char marca[MAX_MARCA];
}Dose;

// Estrutura com as doses de cada vacinação
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
	int bSituacao;  // 0 ou 1, representa verdadeiro ou falso para a liberação do grupo
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

// Lista de cpf já cadastrados no sistema
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

//FUNÇÕES DE MENU

// Informa as opções de ação disponíveis no sistema
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void MenuPrincipal(ListaPessoa** pessoas,ListaGrupo** grupos,ListaVacinas** vacinas,ListaCPF** cpfs);

// Contém todos os relatórios necessários
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void MenuRelatorios(ListaPessoa** pessoas, ListaGrupo** grupos, ListaVacinas** vacinas, ListaCPF** cpfs);

// Apresenta as opções de vacinação
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void MenuVacinacao(ListaPessoa** pessoas, ListaGrupo** grupos, ListaVacinas** vacinas, ListaCPF** cpfs);

// Apresenta o menu para retirar um habitante
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void retirarHabitante(ListaPessoa** pessoas);

// Apresenta o menu para liberar um grupo
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void LiberarGrupo(ListaGrupo** grupos);

// Apresenta um menu para registrar uma vacinação
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void registrarVacinacao(ListaPessoa** pessoas, ListaGrupo* grupos, ListaVacinas** vacinas);

// Apresenta um menu para registrar lotes de vacinas
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void registrarLoteVacinas(ListaVacinas** vacinas);

//FUNÇÕES DE INICIALIZAÇÃO

// Inicia a lista com os grupos de 1 a numero_de_grupos, com estoque zerado
// Pré-condição: numero_de_grupos deve ser inteiro positivo
// Pós-condição: retorna a cabeça da lista dos grupos
ListaGrupo* iniciaGrupos(ListaGrupo* grupos, int numero_de_grupos);

// Altera o conteúdo da estrutura pessoa com informações nulas, "\0", 0, NULL, etc.
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void iniciaPessoa(Pessoa* pessoa);

//FUNÇÕES DE INSERÇÃO

// Cadastra as pessoas contidas no arquivo no sistema
// Pré-condição: nome de aruqivo válido,  sem caracteres nao permitidos pelo sistema operacional
// Pós-condição: retorna a lista com as pessoas lidas
ListaPessoa* LerArquivo(char* nomeArquivo, ListaPessoa* pessoas, ListaCPF** cpfs);

// Insere um novo CPF na lista de CPFs
// Pré-condição: o tamanho da string CPFs pode ter até 11 caracteres
// Pós-condiçao: retorna a lista de CPFs
ListaCPF* insereCpf(ListaCPF* cpfs, char cpf[]);

// Insere uma pessoa na lista de pessoas
// Pré-condição: nenhum
// Pós-condiçao: retorna a lista de pessoas com a pessoa inserida
ListaPessoa* inserePessoa(ListaPessoa* pessoas, Pessoa pessoa);

// Insere um grupo de número info na lista de grupos
// Pré-condição: número info não pode ser negativo
// Pós-condiçao: retorna a lista de grupos com o novo grupo inserido
ListaGrupo* insereGrupo(ListaGrupo* grupo, int info);

// Libera um grupo da lista de grupos
// Pré-condição: número info não pode ser negativo
// Pós-condiçao: retorna a lista de grupos com o grupo liberado
ListaGrupo* liberaGrupo(ListaGrupo* grupos, int info);

// Insere uma nova marca de vacina com seu estoque, se houver
// Pré-condição: nenhuma
// Pós-condiçao: retorna a lista de vacinas com a nova marca inserida
ListaVacinas* insereVacina(ListaVacinas* vacinas, Vacina vacina);

// Insere estoque de vacina, de uma marca nova ou já cadastrada
// Pré-condição: quantidade de vacinas não pode ser negativa
// Pós-condiçao: retorna lista de vacinas com o novo estoque inserido
ListaVacinas* registrarLoteVacina(ListaVacinas* vacinas, char marca[], int quantidade);

// Acha uma marca de vacina com estoque
// Pré-condição: nenhuma
// Pós-condiçao: retorna uma string com a marca com estoque registrada
char* vacinaComEstoque(ListaVacinas* vacinas);

// Registra a vacinação de um habitante cadastrado no sistema
// Pré-condição: o tamanho da string CPF não pode ultrapassar 11 caracteres e deve já estar inserido no sistema
// Pós-condiçao: retorna a lista de pessoas tendo modificado o estado de sua vacinação
ListaPessoa* RegistraVacinacao(ListaPessoa* pessoas, ListaGrupo* grupos, ListaVacinas** vacinas, char cpf[]);

// Conta a quantidade de grupos prioritários
// Pré-condição: nenhuma
// Pós-condiçao: retorna a quantidade de grupos prioritários
int conta_grupos(ListaGrupo* grupos);

// Insere uma pessoa no sistema a partir das informações fornecidas pelo teclado
// Pré-condição: nenhuma
// Pós-condiçao: retorna a lista de pessoas com a pessoa inserida
ListaPessoa* LerTeclado(ListaPessoa* pessoas, ListaCPF** cpfs);

//FUNÇÕES DE BUSCA:

// Localiza uma pessoa na lista de pessoas pelo CPF
// Pré-condição: a string do CPF não pode ser maior que 11 caracteres
// Pós-condição: retorna a pessoa encontrada na lista ou NULL caso não for encontrada
ListaPessoa* FindPessoaByCPF(ListaPessoa* pessoas, char cpf[]);

// Encontra uma marca de vacina pelo seu nome
// Pré-condição: nenhuma
// Pós-condição: retorna a vacina encontrada na lista ou retorna NULL se não achar
ListaVacinas* FindVacinaByName(ListaVacinas* vacinas, char nomeVacina[]);

// Encontra um grupo prioritário pelo seu número
// Pre-condição: o número info deve ser inteiro positivo
// Pós-condiçao: retorna a vacina encontrada na lista
ListaGrupo* FindGrupoByNumber(ListaGrupo* grupos, int info);

//FUNÇÕES DE VERIFICÃÇÃO:

// Verifica se um determinado CPF já está cadastrado n sistema
// Pre-condição: o tamanho da string do CPF não pode ultrapassar 11 caracteres
// Pós-condiçao:  retorna 1 se o CPF está contido na lista ou 0 se não está contido
int cpfIsContido(ListaCPF* cpfs, char cpf[]);

// Verifica se uma pessoa já tomou a primeira dose da vacina
// Pré-condição: o tamanho da string do CPF não pode ultrapassar 11 caracteres
// Pós-condiçao: retorna 1 se a pessoa já recebeu a primeira dose ou 0 se não recebeu
int hasPrimeiraDose(ListaPessoa* pessoas, char cpf[]);

// Verifica a partir do CPF da pessoa se ela já recebeu as duas doses
// Pré-condição: o tamanho da string do CPF não pode ultrapassar 11 caracteres
// Pós-condiçao: retorna 1 se a pessoa já recebeu as duas doses da vacina e 0 se ela ainda não recebeu
int isVacinada(ListaPessoa* pessoas, char cpf[]);

// Verifica se há estoque de uma determinada marca de vacina
// Pré-condição: a marca da vacina já deve estar cadastrada
// Pós-condiçao: retorna 1 se a marca tem estoque disponível e 0 se não
int isThereEstoqueVacinaByMarca(ListaVacinas* vacinas, char nome[]);

// Verifica se um grupo prioritário está liberado para vacinação
// Pré-condição: o número info deve ser um inteiro positivo
// Pós-condiçao: retorna 1 se o grupo está liberado e 0 se não estiver liberado
int isLiberado(ListaGrupo* grupos, int info);

// Verifica se tem estoque de qualquer marca de vacina
// Pré-condição: nenhuma
// Pós-condiçao: retorna 1 se houver qualquer marca com estoque de vacinas
int isThereEstoqueGeral(ListaVacinas* vacinas);

// Verifica se uma marca de vacina está registrada no sistema
// Pré-condição: nenhuma
// Pós-condiçao: retorna 1 se a marca já está registrada e 0 se ainda não foi registrada
int isVacinaRegistrada(ListaVacinas* vacinas, char marca[]);

//FUNÇÕES DE REMOÇÃO

// Remove uma pessoa cadastrada da lista de pessoas
// Pré-condição: o tamanho da string do CPF não pode ser maior que 11 caracteres
// Pós-condiçao: retorna a lista de pessoas com a pessa removida
ListaPessoa* removePessoa(ListaPessoa* pessoas, char cpf[]);

// Remove uma unidade de vacina do estoque de determinada marca
// Pré-condição: nenhuma
// Pós-condiçao: retorna a lista de vacinas com o estoque já alterado
ListaVacinas* remove1Dose(ListaVacinas* vacinas, char marca[]);

//FUNÇÕES DE RELATÓRIO

// Gera um relatório do  número de doses no estoque por tipo de vacina
// Pré-condição: nenhuma
// Pós-condiçao: nenhuma
void relatDosesEstoqVacin(ListaVacinas* vacinas);

// Gera um relatório da listra de habitantes (nome, CPF) vacinados somente com a primeira dose
// Pré-condição: nenhuma
// Pós-condiçao: nenhuma
void relatVacinados1Dose(ListaPessoa* pessoas);

// Gera um relatório com o número de habitantes vacinados, já com a segunda dose
// Pré-condição: nenhuma
// Pós-condiçao: nenhuma
void relatNumVacinados2Doses(int num);

// Conta quantas pessoas já receberam as duas doses de uma vacina
// Pré-condição: nenhuma
// Pós-condiçao: retorna a quantidade de pessoas que já receberam as duas doses de uma vacina
int contaVacinados2Doses(ListaPessoa* pessoas);

// Imprime as apenas as pessoas do grupo informado que não estão vacinadas
// Pré-condição: o número do grupo deve ser um inteiro positivo
// Pós-condiçao: nenhuma
void imprimeGrupoNaoVacinado(ListaPessoa* pessoas, int grupo);

// Gera um relatório com a lista de habitantes (nome, CPF) não vacinados agrupados por grupo prioritário
// Pré-condição: nenhuma
// Pós-condiçao: nenhuma
void relatNaoVacinados(ListaPessoa* pessoas,ListaGrupo* grupos);

// Gera um relatório do número de habitantes por grupo prioritário
// Pré-condição: nenhuma
// Pós-condiçao: nenhuma
void relatHabitantesPorGrupo(ListaPessoa* pessoas,ListaGrupo* grupos);

// Conta a quantidade de pessoas em determinado grupo
// Pré-condição: o número do grupo deve ser um inteiro positivo
// Pós-condiçao: retorna a quantidade de pessoas no grupo fornecido
int conta_habitantes_grupo_atual(ListaPessoa* pessoas, int grupo);

// Conta a quantidade de habitantes que já receberam a primeira dose da vacina
// Pré-condição: nenhuma
// Pós-condiçao: retorna a quantidade de habitantes que já receberam a primeira dose da vacina
int contaVacinados1Dose(ListaPessoa* pessoas);

#endif // ESTRUTURAS_H
