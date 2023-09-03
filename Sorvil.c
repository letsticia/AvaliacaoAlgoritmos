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
    char nome[100];
    char genero[50];
    float valor;
};

//                          váriaveis globais:

// usuário e senha pré-definidos.
char admin[80] = "admin@admin.com";
char senhaAdmin[8] = "12345678";

// valor do carrinho
float carrinho = 0;


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
    int opcaoFiccao = 0;
    struct estoque ficcao[5];

    strcpy(ficcao[0].nome, "1984");
    strcpy(ficcao[0].genero, "Ficção");
    ficcao[0].valor = 45.0;

    strcpy(ficcao[1].nome, "Neuromancer");
    strcpy(ficcao[1].genero, "Ficção");
    ficcao[1].valor = 37.5;

    strcpy(ficcao[2].nome, "Duna");
    strcpy(ficcao[2].genero, "Ficção");
    ficcao[2].valor = 52.0;

    strcpy(ficcao[3].nome, "O Guia do Mochileiro das Galáxias");
    strcpy(ficcao[3].genero, "Ficção");
    ficcao[3].valor = 29.99;

    strcpy(ficcao[4].nome, "O Conto da Aia");
    strcpy(ficcao[4].genero, "Ficção");
    ficcao[4].valor = 42.8;

    printf("=========================================\n");
    printf("             LIVROS DE FICCAO            \n");
    printf("=========================================\n");
    printf("\n");

    for (int contador = 0; contador < 5; contador++)
    {
        printf("[NOME:   ]      %s\n", ficcao[contador].nome);
        printf("[GENERO: ]      %s\n", ficcao[contador].genero);
        printf("[VALOR:  ]      %.2f\n", ficcao[contador].valor);
        printf("[ID:     ]      %i\n\n", contador);
    }
    printf("[5]       VOLTAR AO MENU            [6]     PRÓXIMA PÁGINA\n\n\n");
    printf("Para adicionar algum livro, digite o id deles, se não, ultilize\nos outros ids para voltar ao menu ou ir para a próxima página");
    scanf("%i", &opcaoFiccao);

    switch (opcaoFiccao){
    case 0:
        carrinho = carrinho + ficcao[0].valor;
        return livrosFiccao();
        break;
    case 1:
        carrinho = carrinho + ficcao[1].valor;
        return livrosFiccao();
        break;
    case 2:
        carrinho = carrinho + ficcao[2].valor;
        return livrosFiccao();
        break;
    case 3:
        carrinho = carrinho + ficcao[3].valor;
        return livrosFiccao();
        break;
    case 4:
        carrinho = carrinho + ficcao[4].valor;
        return livrosFiccao();
        break;
    case 5:
        return menuPrincipal();
        break;
    case 6:
        return livrosRomance();
        break;
    default:
        printf("Opçao inválida, selecione uma opção válida.");
        return livrosFiccao();
        break;
    }
}

int livrosRomance(){

    int opcaoRomance;
    struct estoque romance[4];
    

    strcpy(romance[0].nome, "Orgulho e Preconceito");
    strcpy(romance[0].genero, "Romance");
    romance[0].valor = 28.5;

    strcpy(romance[1].nome, "O Amor nos Tempos do Cólera");
    strcpy(romance[1].genero, "Romance");
    romance[1].valor = 34.2;

    strcpy(romance[2].nome, "Como Eu Era Antes de Você");
    strcpy(romance[2].genero, "Romance");
    romance[2].valor = 31.75;

    strcpy(romance[3].nome, "Anna Karenina");
    strcpy(romance[3].genero, "Romance");
    romance[3].valor = 48.9;

    strcpy(romance[4].nome, "Outlander");
    strcpy(romance[4].genero, "Romance");
    romance[4].valor = 39.6;

    printf("=========================================\n");
    printf("            LIVROS DE ROMANCE            \n");
    printf("=========================================\n");
    printf("\n");

    for (int contador = 0; contador < 5; contador++)
    {
        printf("[NOME:   ]      %s\n", romance[contador].nome);
        printf("[GENERO: ]      %s\n", romance[contador].genero);
        printf("[VALOR:  ]      %.2f\n", romance[contador].valor);
        printf("[ID:     ]      %i\n\n", contador);
    }
    printf("[5]       VOLTAR AO MENU            [6]     PRÓXIMA PÁGINA\n\n\n");
    printf("Para adicionar algum livro, digite o id deles, se não, ultilize\nos outros ids para voltar ao menu ou ir para a próxima página");
    scanf("%i", &opcaoRomance);

    switch (opcaoRomance){
    case 0:
        carrinho = carrinho + romance[0].valor;
        return livrosRomance();
        break;
    case 1:
        carrinho = carrinho + romance[1].valor;
        return livrosRomance();
        break;
    case 2:
        carrinho = carrinho + romance[2].valor;
        return livrosRomance();
        break;
    case 3:
        carrinho = carrinho + romance[3].valor;
        return livrosRomance();
        break;
    case 4:
        carrinho = carrinho + romance[4].valor;
        return livrosRomance();
        break;
    case 5:
        return menuPrincipal();
        break;
    case 6:
        //return livrosMisterio();
        break;
    default:
        printf("Opçao inválida, selecione uma opção válida.");
        return livrosFiccao();
        break;
    }
}