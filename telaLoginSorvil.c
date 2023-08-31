#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define caracteres_max 80 // define uma constante referente aos caracteres máximos com valor igual a 80

struct Usuario {  // define um struct com as variáveis que irão ser usadas
  char email[caracteres_max];
  char senha[caracteres_max];
  char nome[caracteres_max];
};

struct Usuario emailsenha[50]; //define um limite grande para usuários 
int quantidade = 0;
char email_digitado[caracteres_max];
char senha_digitada[caracteres_max];

void logar() {                      //função de login após cadastramento da conta
  printf("Digite seu email:\n");
  scanf(" %[^\n]s", email_digitado);
  printf("Digite sua senha:\n");
  scanf(" %[^\n]s", senha_digitada);
}

struct Usuario novo_usuario;        //struct para novos usuários

void cadastrar() {              //função para cadastrar uma nova conta
  printf("Informe seu nome:\n");
  scanf(" %[^\n]s", novo_usuario.nome);
  printf("Crie seu email:\n");
  scanf(" %[^\n]s", novo_usuario.email);
  printf("Digite sua senha:\n");
  scanf(" %[^\n]s", novo_usuario.senha);
}

void cadastrar2() {         //função usada caso email/senha estejam fora do exigido, para nao pegar o nome da pessoa denovo
  printf("Crie seu email:\n");
  scanf(" %[^\n]s", novo_usuario.email);
  printf("Digite sua senha:\n");
  scanf(" %[^\n]s", novo_usuario.senha);
}

void telaDeLogin() {                // função para a tela de login inicial
  printf("======= TELA DE LOGIN =======\n1- Entrar na conta\n2- Cadastra-se\n3- "
         "Encerrar programa\n4- Listar contas cadastradas\n5- Editar senha"
         "\n6- Excluir conta"
         "\n=============================\n");
}

void loginErrado() {        //função para caso email/senha estejam fora do padrão exigido
  printf("Erro de cadastramento, possíveis motivos:\n1- email e/ou senha "
         "atingiram 80 ou mais caracteres.\n2- o email não possui o caractere "
         "'@'.\n3- O email já está cadastrado no sistema.\n\n");
}

void listarContas() {               //função para listar todas as contas cadastradas
  if (quantidade == 0) {
    printf("Ainda não há contas cadastradas.\n\n");
  } else {
    printf("============= Contas cadastradas =============\n");
    for (int i = 0; i < quantidade; i++) {
      printf("Email: %s | Senha: %s\n", emailsenha[i].email,
             emailsenha[i].senha);
    }
    printf("==============================================\n");
  }
}

void editarSenha() {        //função para editar senha de uma conta já cadastrada
  printf("Confirme seu email:\n");
  scanf(" %[^\n]s", email_digitado);
  printf("Confirme sua senha:\n");
  scanf(" %[^\n]s", senha_digitada);

  int encontrado = 0;
  for (int i = 0; i < quantidade; i++) {
    if (strcmp(email_digitado, emailsenha[i].email) == 0 &&
        strcmp(senha_digitada, emailsenha[i].senha) == 0) {
      printf("Email e senha confirmados. Digite a nova senha:\n");
      scanf(" %[^\n]s", emailsenha[i].senha);
      printf("Senha atualizada com sucesso!\n");
      encontrado = 1;
      break;
    }
  }
  if (!encontrado) {
    printf("Email e/ou senha incorretos. Tente novamente.\n");
  }
}

int encontrado = 0;
int opcao;

void loginCerto() {     //função para realizar o login
  for (int i = 0; i < quantidade; i++) {
    if (strcmp(email_digitado, emailsenha[i].email) == 0 &&
        strcmp(senha_digitada, emailsenha[i].senha) == 0) {
      printf("Login realizado com sucesso!\nSeja bem-vindo, sr(a). %s\n", emailsenha[i].nome);
      encontrado = 1;
      opcao = 3;
      break;
    }
  }
}

void excluirConta() {               //função para excluir a conta
  printf("Confirme seu email:\n");
  scanf(" %[^\n]s", email_digitado);
  printf("Confirme sua senha:\n");
  scanf(" %[^\n]s", senha_digitada);

  int encontrado = 0;
  for (int i = 0; i < quantidade; i++){
    if(strcmp(email_digitado, emailsenha[i].email) == 0 &&
       strcmp(senha_digitada, emailsenha[i].senha) == 0) {
      strcpy(emailsenha[i].email, emailsenha[i+1].email);
      strcpy(emailsenha[i].senha, emailsenha[i+1].senha);
      printf("Conta excluida com sucesso!\n");
      quantidade--;
      encontrado = 1;
      break;
    }
  }
  if(!encontrado) {
    printf("Email e/ou senha incorretos. Tente novamente.\n");
  }
}

int valideEmail(struct Usuario novo_usuario){       //função para analisar se a conta para ser cadastrada está nos padrões
        for (int i = 0; i < quantidade; i++) {
          if (strcmp(novo_usuario.email, emailsenha[i].email) == 0) {
            return 0;  //comparação se o email já existe
          }
        }

        if (strlen(novo_usuario.email) < caracteres_max   //comparação se o email e senha estão dentro dos parâmetros
     && strlen(novo_usuario.senha) < caracteres_max
     &&
            strchr(novo_usuario.email, '@') != NULL) {    //análise se o email possui o caractere ' @ '
            return 1;
        } 
      return 0;
}


//                               fução main(ultilizada para iniciar um loop entre as funções)
int main(){

      while (opcao != 3) {
    telaDeLogin();
    scanf("%d", &opcao);
    switch (opcao) {
    case 1:
      while (1) {
        logar();
        loginCerto();
        if (encontrado) {
          break;
        } else {
          printf("Login e/ou senha incorreto. Tente novamente.\n");
        }
        
      } 
      break;
    case 2:
      while (1) {
        cadastrar();
        if (valideEmail(novo_usuario) == 1) {
          emailsenha[quantidade] = novo_usuario;
          quantidade++;
          printf("Conta cadastrada com sucesso!\n");
          break;
        }
        else {
          while(1){
          loginErrado();
          cadastrar2(); 
          if (valideEmail(novo_usuario) == 1) {
            emailsenha[quantidade] = novo_usuario;
            quantidade++;
            printf("Conta cadastrada com sucesso!\n");
            break;
          }
          }
          break;
        }  
      }
    
      break;
    case 3:
      printf("Encerrando programa...\n");
      return 0;
    case 4:
      if(quantidade == 0){
        printf("Não há contas para serem listadas.\n");
      }
      else{
        listarContas();
      }
      break;
    case 5:
      if(quantidade == 0){
        printf("Não há contas para serem editadas.\n");
      }
      else{
        editarSenha();
      }
      break;
    case 6:
      if(quantidade == 0){
        printf("Não há contas para serem excluídas.\n");
      }
      else{
        excluirConta();
      }
      break;
    default:
      printf("opção inválida.\n");
      return 1;
    }
  }

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