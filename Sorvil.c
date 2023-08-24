#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//                               fução main(ultilizada para iniciar um loop entre as funções)
int main(){

    menuInicial();

    return 0; 
    // sai da função main, fechando, assim, o programa.
}

//                              Os livros serão postos em um vetor da struct estoque.
struct estoque
{
    char nome;
    char genero;
    float valor;
};

//                          váriaveis globais:

// usuário e senha pré-definidos.
char admin[80] = "admin@admin.com";
char senhaAdmin[8] = "12345678";

// valor do carrinho
int carrinho = 0;


struct estoque ficcao[5];


//                          protótipos das funções que serão utilizadas no projeto:

// -> menus de múltiplas opções

int menuInicial();
int menuCadastro();
int menuLogin();
int menuPrincipal();
int menuCarrinho();


// -> menus de filtros de livros

int livrosFiccao();
int livrosRomance();
int livrosMisterio();
int livrosFantasia();
int livrosTerror();


//                          declaração das funções do projeto

/* Menu feito para que o usuário escolha entre logar em uma conta existente, criar uma nova
    uma conta nova ou sair do programa
    É a primeira parte do primeiro requisito proposto: Realizar Login.*/
int menuInicial(){
    
    // variável que permite a navegação no menu inicial.    
    int opcao;

    printf("=========================================\n");
    printf("              Menu Inicial               \n");
    printf("=========================================\n");
    printf("\n");
    printf("-----------------------------------------\n");
    printf("    (1)     Entrar em uma conta existente\n");
    printf("    (2)     Criar uma conta nova\n");
    printf("    (3)     Sair do sorvil\n");
    printf("-----------------------------------------\n");

    printf("Selecione uma das opções acima: ");
    scanf("%i", &opcao);
    switch (opcao){
    case 1:
        printf("Você está sendo redirencionado para o menu de Login\n");
        return menuLogin();
        break;
    case 2:
        printf("Você está sendo redirencionado para o menu de Criação de Contas\n");
        return menuCadastro();
        break;
    case 3:
        return 0;
        break;
    default:
        printf("Opção inválida, por favor, selecione uma opção válida.\n");
        menuInicial();
        break;
    }
    
}


/* Menu feito para cadastras contas novas ao programa, esta função é a que valida os e-mails
fazendo assim, o segundo requisito das propostas da avaliação:
            -> Validação de email.*/
int menuCadastro(){
    char email[80];
    char senha[8];

    int quantidadesArroba;
    int opcaoLogin;


    printf("=========================================\n");
    printf("              Menu de Login              \n");
    printf("=========================================\n");
    printf("\n");
    printf("[E-mail:]");
    scanf("%s", email);
    printf(" [Senha:]");
    scanf("%s", senha);
    printf("\n");

    if (!strcmp(admin, email)){
        printf("Este e-mail já está sendo utilizado");
        return menuCadastro();
        }
    
    if(strlen(email) > 80){
        printf("O e-mail deve conter, no máximo, 80 caracteres\n");
        return menuCadastro();

    } else{
        for(int contador = 0; contador < strlen(email); contador++){
            if (email[contador] == '@'){
                quantidadesArroba++;
            }
        }
        if (quantidadesArroba = 1){
            printf("O e-mail  é válido!\n");
            if (strlen(senha) <= 8){
                printf("Conta cadastrada com sucesso! Você está sendo redirecionado\n");
                printf("para o menu principal! Boas compras!\n");
                return menuPrincipal();
            } else{
                printf("A senha deve conter, no máximo, 8 caracteres\n");
                return menuCadastro();
            }    
        } else{
            printf("A quantidade de @ no e-mail deve ser igual a 1\n");
            return menuCadastro();
        }
        
    }
}

/* Menu feito para que o usuário entre em uma conta pré-existente.
   É a segunda parte do primeiro requisito proposto: Realizar Login.*/
int menuLogin(){
    int opcao;
    int validado = 0; 

    // input da tela de login.
    char email[80];
    char senha[8];

    printf("=========================================\n");
    printf("              Menu de Login              \n");
    printf("=========================================\n");
    printf("\n");
    printf("[E-mail:]");
    scanf("%s", email);
    printf(" [Senha:]");
    scanf("%s", senha);
    printf("\n");

    // comparando se o email e a senha digitados estão corretos
    // se sim, o usuário é redirecionado para a tela principal
    // se não, o usuário tem que escolher entre tentar logar novamente
    // ou voltar ao menu inicial.
    if ((!strcmp(admin, email)) && (!strcmp(senhaAdmin, senha))){
        printf("Login realizado com sucesso!\n");
        return menuPrincipal();
    } else{
        printf("Email e/ou senha incorretos\n\n");
        printf("Você deseja tentar logar novamente(1) ou voltar ao menu principal?(2)");
        scanf("%i", &opcao);
        switch (opcao){
        case 1:
            return menuLogin();
            break;
        case 2:
            printf("Você está sendo redirecionado para o menu inicial");
            return menuInicial();
            break;
        default:
            return 0;
            break;
        }
    }
}
        

/* Menu em que o usuário pode navegar entre todas as outras tela, assim, completando dois requisitos de uma vez.
Sendo estes:
    -> Apresentar menu de opções
    -> Mensagem de boas vindas*/
int menuPrincipal(){

    printf("=========================================\n");
    printf("              Menu Principal             \n");
    printf("=========================================\n");
    printf("\n");
    printf("   Seja bem-vindo(a) ao Sorvil! Livros\n");
    printf("        novos e de qualidade só aqui!\n");
    printf("\n");
    printf("-----------------------------------------\n");
    printf("    (1)     Visualizar todos os livros\n");
    printf("    (2)     Visualizar livros de ficção\n");
    printf("    (3)     Visualizar livros de romance\n");
    printf("    (4)     Visualizar livros de mistério\n");
    printf("    (5)     Visualizar livros de fantasia\n");
    printf("    (6)     Visualizar livros de terror\n");
    printf("    (7)     Visualizar carrinho\n");
    printf("    (8)     Sair do Sorvil\n");
    printf("-----------------------------------------\n");
    printf("Selecione uma das opções acima: "); 
}


/* Menu de carrinho, o qual mostra a total das compras do usuário, além de mostrar quais itens estão no carrinho, também pergunta
qual o método de pagamento. Essa função cumpre o requisito de:
            -> Operações básicas sobre pelo menos 1 item (cadastrar, listar, editar e excluir)*/

// Sorteio (apresentar uma cartela de rifa em formato retangular  para participar de um sorteio)

int livrosFiccao(){
    struct estoque ficcao[5];

    ficcao[0].nome = "1984";
    ficcao[0].genero = "Ficção";
    ficcao[0].valor = 45;

    ficcao[1].nome = "Neuromancer";
    ficcao[1].genero = "Ficção";
    ficcao[1].valor = 37.5;

    ficcao[2].nome = "Duna";
    ficcao[2].genero = "Ficção";
    ficcao[2].valor = 52;

    ficcao[3].nome = "O Guia do Mochileiro das Galáxias";
    ficcao[3].genero = "Ficção";
    ficcao[3].valor = 29.99;

    ficcao[4].nome = "O Conto da Aia";
    ficcao[4].genero = "Ficção";
    ficcao[4].valor = 42.8;
}

