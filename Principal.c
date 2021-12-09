#include <stdio.h>
#include <stdlib.h>

// constante repesenta o tamanho da tabela
#define M 20

// estrutura Pessoa com nome e uma matrícula
typedef struct{
    int cpf;
    char nome[50];
    char endereco[50];
    int agencia;
    int conta;
    char tipoConta[20];
    char banco[20];
}Cliente;

// nossa tabela hash do tipo Pessoa
Cliente tabelaHash[M];

// inicializa nossa tabela com o valor de codigo -1
void inicializarTabela(){
    int i;
    for(i = 0; i < M; i++)
        tabelaHash[i].cpf = -1;
}

// função de espalhamento (resto da divisão da chave por M)
int gerarCodigoHash(int chave){
    return chave % M;
}

// função para ler e retornar uma pessoa
Cliente lerCliente(){
    Cliente c;
    printf("Digite o cpf: ");
    scanf("%d", &c.cpf);
    scanf("%*c");
    printf("Digite o nome completo: ");
    fgets(c.nome, 50, stdin);
    printf("Digite o endereco: ");
    fgets(c.endereco, 50, stdin);
    printf("Digite a agencia: ");
    scanf("%d", &c.agencia);
    printf("Digite a conta: ");
    scanf("%d", &c.conta);
    scanf("%*c");
    printf("Digite o tipo de conta: ");
    fgets(c.tipoConta, 20, stdin);
    printf("Digite o nome do banco: ");
    fgets(c.banco, 20, stdin);
    return c;
}

// inserir uma pessoa na tabela
void inserir_elem(){
    Cliente cli = lerCliente();
    int indice = gerarCodigoHash(cli.cpf);
    while(tabelaHash[indice].cpf != -1) {
    	indice = gerarCodigoHash(indice + 1);
	} tabelaHash[indice] = cli;
    
    return;
}

Cliente* buscar(int chave){
    int indice = gerarCodigoHash(chave);
    while(tabelaHash[indice].cpf != -1){
        if(tabelaHash[indice].cpf == chave) {
        	
            return &tabelaHash[indice];
		}
        else {
        	indice = gerarCodigoHash(indice + 1);
		}
    }
    
    return NULL;
}

void imprimir(){
    int i;
    printf("\n------------------------TABELA---------------------------\n");
    for(i = 0; i < M; i++){
        if(tabelaHash[i].cpf != -1)
            printf("Cliente [%d] = CPF: %d \tNome: %s \tEndereco: %s \tAgencia: %d \tConta: %d \tTipo de Conta: %s \tBanco: %s", i, tabelaHash[i].cpf, tabelaHash[i].nome, tabelaHash[i].endereco, tabelaHash[i].agencia, tabelaHash[i].conta, tabelaHash[i].tipoConta, tabelaHash[i].banco);
        else
            printf("%2d =\n", i);
    }
    printf("\n----------------------------------------------------------\n");
}

int main() {
	int op, chave;
    Cliente *c;

    inicializarTabela();

    do{
    //--------------- Exibir menu ---------------------//
        puts("\n\t\t\t\tTABELA HASH (CLIENTES)\n");
        puts("\t1  - INSERIR ELEMENTO\n \t2  - BUSCAR ELEMENTO\n \t3  - IMPRIMIR TABELA\n \t0  - SAIR");
        printf("\nINFORME SUA OPCAO:\n");
        scanf("%d", &op);//Escolha da Opção

        switch(op){
	        case 0:
	            printf("Saindo...\n");
	            break;
	        case 1:
	            inserir_elem();
	            break;
	        case 2:
	            printf("Digite a matricula a ser buscada: ");
	            scanf("%d", &chave);
	            c = buscar(chave);
	
	            if(c)
	                printf("\n\tCPF: %3d \tNome: %s \tEndereco: %s \tAgencia: %d \tConta: %d \tTipo de Conta: %s \tBanco: %s", c->cpf, c->nome, c->endereco, c->agencia, c->conta, c->tipoConta, c->banco);
	            else
	                printf("\nMatricula nao encontrada!\n");
	            break;
	        case 3:
	            imprimir();
	            break;
	        default:
	            printf("Opcao invalida!\n");
	        }
    }while(op != 0);
}
