#include <stdio.h>
#include <string.h>
#define CARACTERES_MAX 80 // define uma constante referente aos caracteres máximos com valor igual a 80

//                          protótipos das funções que serão utilizadas no projeto (pt.1):

// -> menus de múltiplas opções

int menuInicial();
int menuCadastro();
int menuLogin();
int menuPrincipal();
int listarContas();
int editarSenha();
int excluirConta();

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

struct Usuario {  // define um struct com as variáveis que irão ser usadas
    char email[CARACTERES_MAX];
    char senha[CARACTERES_MAX];
    char nome[CARACTERES_MAX];
};

struct Usuario emailsenha[50]; //define um limite grande para usuários 
    int quantidade = 0;
    char email_digitado[CARACTERES_MAX];
    char senha_digitada[CARACTERES_MAX];

//                          váriaveis globais:


// valor do carrinho
float carrinho = 0;   

// lista que vai amarzenar os livros que estão no carrinho
char carrinhoLivros[25][50];     
int carrinhoValores[25];         

// variável que vai contar quantos livros estão no carrinho e vai ajudar a mostrar cada um deles
int contadorLivros = 0;


//                          protótipos das funções que serão utilizadas no projeto (pt.2):

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
    printf("=========================================\n\n");
    printf("-----------------------------------------\n");
    printf("    (1)     Entrar em uma conta existente\n");
    printf("    (2)     Criar uma conta nova\n");
    printf("    (3)     Sair do sorvil\n");
    printf("    (4)     Listar contas cadastradas\n");
    printf("    (5)     Editar senha\n");
    printf("    (6)     Excluir conta\n");
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
    case 4:
        return listarContas();
        break;
    case 5:
        printf("Você está sendo redirencionado para o menu de editar senha\n");
        return editarSenha();
        break;
    case 6:
        printf("Você está sendo redirencionado para o menu de excluir conta\n");
        return excluirConta();
        break;
    default:
        printf("Opção inválida, por favor, selecione uma opção válida.\n");
        return menuInicial();
        break;
    }   
}

struct Usuario novo_usuario;        //struct para novos usuários

int valideEmail(struct Usuario novo_usuario){       //função para analisar se a conta para ser cadastrada está nos padrões
        for (int i = 0; i < quantidade; i++) {
          if (strcmp(novo_usuario.email, emailsenha[i].email) == 0) {
            return 0;  //comparação se o email já existe
          }
        }

        if (strlen(novo_usuario.email) < CARACTERES_MAX   //comparação se o email e senha estão dentro dos parâmetros
     && strlen(novo_usuario.senha) < CARACTERES_MAX
     &&
            strchr(novo_usuario.email, '@') != NULL) {    //análise se o email possui o caractere ' @ '
            return 1;
        } 
      return 0;
}

void loginErrado() {        //função para caso email/senha estejam fora do padrão exigido
  printf("Erro de cadastramento, possíveis motivos:\n1- email e/ou senha "
         "atingiram 80 ou mais caracteres.\n2- o email não possui o caractere "
         "'@'.\n3- O email já está cadastrado no sistema.\n\n");
}

/* Menu feito para cadastrar contas novas ao programa, esta função é a que valida os e-mails
fazendo assim, o segundo requisito das propostas da avaliação:
            -> Validação de email.*/

int menuCadastro(){

    // inputs do usuário

    printf("=========================================\n");
    printf("             Menu de Cadastro            \n");
    printf("=========================================\n\n");
    printf("Informe seu nome:\n");
    scanf(" %[^\n]s", novo_usuario.nome);
    printf("Crie seu email:\n");
    scanf(" %[^\n]s", novo_usuario.email);
    printf("Digite sua senha:\n");
    scanf(" %[^\n]s", novo_usuario.senha);

        if (valideEmail(novo_usuario) == 1) {
          emailsenha[quantidade] = novo_usuario;
          quantidade++;
          printf("Conta cadastrada com sucesso! Realize o login para continuar!\n");
          return menuInicial();
        }
        else {
          loginErrado();
          return menuCadastro();
        }  
      }


/* Menu feito para que o usuário entre em uma conta pré-existente.
   É a segunda parte do primeiro requisito proposto: Realizar Login.*/
int menuLogin(){

    // variável que possibilita navegar nesse menu
    int opcao;
 
    // variável de auxílio para procura do email inserido com o email existente
    int encontrado = 0;

    // input da tela de login.

    printf("=========================================\n");
    printf("              Menu de Login              \n");
    printf("=========================================\n\n");
    printf("[E-mail:] ");
    scanf(" %[^\n]s", email_digitado);
    printf("[Senha:] ");
    scanf(" %[^\n]s", senha_digitada);
    printf("\n");

    // comparando se o email e a senha digitados estão corretos
    // se sim, o usuário é redirecionado para a tela principal
    // se não, o usuário tem que escolher entre tentar logar novamente
    // ou voltar ao menu inicial.

    for (int i = 0; i < quantidade; i++) {
      if (strcmp(email_digitado, emailsenha[i].email) == 0 && strcmp(senha_digitada, emailsenha[i].senha) == 0) {
        printf("Login realizado com sucesso!\nSeja bem-vindo, sr(a). %s\n", emailsenha[i].nome);
        encontrado = 1;
      break;
      }
    }
    if (encontrado) {
      return menuPrincipal();
    } 
    else {
      printf("Login e/ou senha incorreto. Tente novamente.\n");
      printf("Você deseja tentar logar novamente(1) ou voltar ao menu principal?(2)\n");
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
int listarContas() {               //função para listar todas as contas cadastradas
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
  return menuInicial();
}

int editarSenha() {        //função para editar senha de uma conta já cadastrada
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
      return menuInicial();
      encontrado = 1;
      break;
    }
  }
  if (!encontrado) {
    printf("Email e/ou senha incorretos. Tente novamente.\n");
  }
}

int excluirConta() {               //função para excluir a conta
  printf("Confirme seu email:\n");
  scanf(" %[^\n]s", email_digitado);
  printf("Confirme sua senha:\n");
  scanf(" %[^\n]s", senha_digitada);

  int encontrado = 0;
  for (int i = 0; i < quantidade; i++){
    if(strcmp(email_digitado, emailsenha[i].email) == 0 && strcmp(senha_digitada, emailsenha[i].senha) == 0) {
      strcpy(emailsenha[i].email, emailsenha[i+1].email);
      strcpy(emailsenha[i].senha, emailsenha[i+1].senha);
      printf("Conta excluida com sucesso!\n");
      return menuInicial();
      quantidade--;
      encontrado = 1;
      break;
    }
  }
  if(!encontrado) {
    printf("Email e/ou senha incorretos. Tente novamente.\n");
    return menuInicial();
  }
}

/* Menu em que o usuário pode navegar entre todas as outras tela, assim, completando dois requisitos de uma vez.
Sendo estes:
    -> Apresentar menu de opções
    -> Mensagem de boas vindas*/
int menuPrincipal(){

    // variável que possibilita navegar neste menu
    int opcaoPrincipal;

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
    printf("    (9)     Fazer loggout\n");
    printf("-----------------------------------------\n");
    printf("Selecione uma das opções acima: "); 
    scanf("%i", &opcaoPrincipal);

    switch (opcaoPrincipal){

    case 1:
        return livrosFiccao();
        break;

    case 2:
        return livrosFiccao();
        break;

    case 3:
        return livrosRomance();
        break;

    case 4:
        return livrosMisterio();

    case 5:
        return livrosFantasia();
        break;

    case 6:
        return livrosTerror();
        break;

    case 7:
        return menuCarrinho();
        break;

    case 8:
        return 0;
        break;

    case 9:
        return menuInicial();
        break;
    default:
        printf("opção inválida, por favor, digite uma opção válida");
        return menuPrincipal();
        break;
    }
}


/* Menu de carrinho, o qual mostra a total das compras do usuário, além de mostrar quais itens estão no carrinho, também pergunta
qual o método de pagamento. Essa função cumpre o requisito de:
            -> Operações básicas sobre pelo menos 1 item (cadastrar, listar, editar e excluir)*/

int menuCarrinho(){

    // variável que possibilita navegar neste menu
    int opcaoCarrinho;

    printf("=========================================\n");
    printf("           Carrinho de Compras           \n");
    printf("=========================================\n\n");

    if (contadorLivros == 0){
        printf("Você não colocou nada no seu carrinho ainda!\nVocê deseja voltar ao menu (1) ou você deseja\n sair do sorvill?");
    } 
    else{
        printf("Os seguintes livros estão no seu carrinho:");
        printf("[ID]        NOME              VALOR(R$)");
        for(int contador = 0; contador < contadorLivros; contador++){
            printf("[%i]        %s              R$%.2f");
        }
        
        // falta 
        //--> opcao de excluir, caso o usuario queira.
        // editar 
        // adicionar mais

    }
}

// Sorteio (apresentar uma cartela de rifa em formato retangular  para participar de um sorteio)


// Menu que irá exibir os livros de Ficção

int livrosFiccao(){

    // variável que vai ser ultilizada para navegar nesse menu
    int opcaoFiccao = 0;

    // criando o vetor para os livros de ficção da struct estoque
    struct estoque ficcao[5];


    //  declarando os livros de ficção dentro do vetor

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


    // parte visivel ao usuário

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

    // switch que permitirá que o usuário escolha qual o livro e se quer voltar ao menu ou ir para a prox pag

    if (0 <= opcaoFiccao <= 4){
      carrinho = carrinho + ficcao[opcaoFiccao].valor;
      strcpy(carrinhoLivros[contadorLivros], ficcao[opcaoFiccao].nome);
      carrinhoValores[contadorLivros] = ficcao[opcaoFiccao].valor;
      contadorLivros ++;
      return livrosFiccao();

    } else{
      switch (opcaoFiccao){
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
}

// Menu que irá exibir os livros de Romance

int livrosRomance(){

    // variável que vai ser ultilizada para navegar nesse menu
    int opcaoRomance;

    // criando o vetor para os livros de romance da struct estoque
    struct estoque romance[4];
    
    //  declarando os livros de Romance dentro do vetor

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

     // parte visivel ao usuário

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

    // switch que permitirá que o usuário escolha qual o livro e se quer voltar ao menu ou ir para a prox pag
    if (0 <= opcaoRomance <= 4){
      carrinho = carrinho + romance[opcaoRomance].valor;
      strcpy(carrinhoLivros[contadorLivros], romance[opcaoRomance].nome);
      carrinhoValores[contadorLivros] = romance[opcaoRomance].valor;
      contadorLivros ++;
      return livrosFiccao();}
    else{
      switch (opcaoRomance){
      case 5:
          return menuPrincipal();
          break;
      case 6:
          return livrosMisterio();
          break;
      default:
          printf("Opçao inválida, selecione uma opção válida.");
          return livrosRomance();
          break;
    }
    }
}

// Menu que irá exibir os livros de Mistério

int livrosMisterio(){

    // variável que vai ser ultilizada para navegar nesse menu
    int opcaoMisterio;

    // criando o vetor para os livros de romance da struct estoque
    struct estoque misterio[4];

    //  declarando os livros de Misterio dentro do vetor

    strcpy(misterio[0].nome, "O Código Da Vinci");
    strcpy(misterio[0].genero, "Mistério");
    misterio[0].valor = 27.95;

    strcpy(misterio[1].nome, "Sherlock Holmes: As Aventuras");
    strcpy(misterio[1].genero, "Mistério");
    misterio[1].valor = 23.7;

    strcpy(misterio[2].nome, "Garota Exemplar");
    strcpy(misterio[2].genero, "Mistério");
    misterio[2].valor = 32.4;

    strcpy(misterio[3].nome, "O Silêncio dos Inocentes");
    strcpy(misterio[3].genero, "Mistério");
    misterio[3].valor = 29.15;

    strcpy(misterio[4].nome, "A Garota no Trem");
    strcpy(misterio[4].genero, "Mistério");
    misterio[4].valor = 25.8;

    // parte visivel ao usuário

    printf("=========================================\n");
    printf("           LIVROS DE MISTÉRIO            \n");
    printf("=========================================\n");
    printf("\n");

    for (int contador = 0; contador < 5; contador++)
    {
        printf("[NOME:   ]      %s\n", misterio[contador].nome);
        printf("[GENERO: ]      %s\n", misterio[contador].genero);
        printf("[VALOR:  ]      %.2f\n", misterio[contador].valor);
        printf("[ID:     ]      %i\n\n", contador);
    }
    printf("[5]       VOLTAR AO MENU            [6]     PRÓXIMA PÁGINA\n\n\n");
    printf("Para adicionar algum livro, digite o id deles, se não, ultilize\nos outros ids para voltar ao menu ou ir para a próxima página");
    scanf("%i", &opcaoMisterio);

    // switch que permitirá que o usuário escolha qual o livro e se quer voltar ao menu ou ir para a prox pag

    if (0 <= livrosMisterio <= 4){
      carrinho = carrinho + misterio[opcaoMisterio].valor;
      strcpy(carrinhoLivros[contadorLivros], misterio[opcaoMisterio].nome);
      carrinhoValores[contadorLivros] = misterio[opcaoMisterio].valor;
      contadorLivros ++;
      return livrosFiccao();
    } else{
    switch (opcaoMisterio){
    case 5:
        return menuPrincipal();
        break;
    case 6:
        return livrosFantasia();
        break;
    default:
        printf("Opçao inválida, selecione uma opção válida.");
        return livrosMisterio();
        break;
    }  // tobias q fez
    }
}

// Menu que irá exibir os livros de Fantasia

int livrosFantasia(){

    // variável que vai ser ultilizada para navegar nesse menu
    int opcaoFantasia;

    // criando o vetor para os livros de romance da struct estoque
    struct estoque fantasia[4];

    //  declarando os livros de Fantasia dentro do vetor

    strcpy(fantasia[0].nome, "O Senhor dos Anéis");
    strcpy(fantasia[0].genero, "Fantasia");
    fantasia[0].valor = 56.75;

    strcpy(fantasia[1].nome, "Harry Potter e a Pedra Filosofal");
    strcpy(fantasia[1].genero, "Fantasia");
    fantasia[1].valor = 42.0;

    strcpy(fantasia[2].nome, "Crônicas de Nárnia: O Leão, a Feiticeira e o Guarda-Roupa");
    strcpy(fantasia[2].genero, "Fantasia");
    fantasia[2].valor = 30.25;

    strcpy(fantasia[3].nome, "A Guerra dos Tronos");
    strcpy(fantasia[3].genero, "Fantasia");
    fantasia[3].valor = 47.5;

    strcpy(fantasia[4].nome, "Percy Jackson e o Ladrão de Raios");
    strcpy(fantasia[4].genero, "Fantasia");
    fantasia[4].valor = 33.9;

    // parte visivel ao usuário

    printf("=========================================\n");
    printf("           LIVROS DE FANTASIA            \n");
    printf("=========================================\n");
    printf("\n");

    for (int contador = 0; contador < 5; contador++)
    {
        printf("[NOME:   ]      %s\n", fantasia[contador].nome);
        printf("[GENERO: ]      %s\n", fantasia[contador].genero);
        printf("[VALOR:  ]      %.2f\n", fantasia[contador].valor);
        printf("[ID:     ]      %i\n\n", contador);
    }
    printf("[5]       VOLTAR AO MENU            [6]     PRÓXIMA PÁGINA\n\n\n");
    printf("Para adicionar algum livro, digite o id deles, se não, ultilize\nos outros ids para voltar ao menu ou ir para a próxima página");
    scanf("%i", &opcaoFantasia);

    // switch que permitirá que o usuário escolha qual o livro e se quer voltar ao menu ou ir para a prox pag

    switch (opcaoFantasia){
    case 0:
        carrinho = carrinho + fantasia[0].valor;
        strcpy(carrinhoLivros[contadorLivros], fantasia[0].nome);
        carrinhoValores[contadorLivros] = fantasia[0].valor;
        contadorLivros ++;
        return livrosRomance();
        break;
    case 1:
        carrinho = carrinho + fantasia[1].valor;
        strcpy(carrinhoLivros[contadorLivros], fantasia[1].nome);
        carrinhoValores[contadorLivros] = fantasia[1].valor;
        contadorLivros ++;
        return livrosRomance();
        break;
    case 2:
        carrinho = carrinho + fantasia[2].valor;
        strcpy(carrinhoLivros[contadorLivros], fantasia[2].nome);
        carrinhoValores[contadorLivros] = fantasia[2].valor;
        contadorLivros ++;
        return livrosRomance();
        break;
    case 3:
        carrinho = carrinho + fantasia[3].valor;
        strcpy(carrinhoLivros[contadorLivros], fantasia[3].nome);
        carrinhoValores[contadorLivros] = fantasia[3].valor;
        contadorLivros ++;
        return livrosRomance();
        break;
    case 4:
        carrinho = carrinho + fantasia[4].valor;
        strcpy(carrinhoLivros[contadorLivros], fantasia[4].nome);
        carrinhoValores[contadorLivros] = fantasia[4].valor;
        contadorLivros ++;
        return livrosRomance();
        break;
    case 5:
        return menuPrincipal();
        break;
    case 6:
        return livrosTerror();
        break;
    default:
        printf("Opçao inválida, selecione uma opção válida.");
        return livrosMisterio();
        break;
    }
}

// Menu que irá exibir os livros de Romance

int livrosTerror(){

    // variável que vai ser ultilizada para navegar nesse menu
    int opcaoTerror;

    // criando o vetor para os livros de romance da struct estoque
    struct estoque terror[4];

    //  declarando os livros de Romance dentro do vetor

    strcpy(terror[0].nome, "O Iluminado");
    strcpy(terror[0].genero, "Terror");
    terror[0].valor = 36.6;

    strcpy(terror[1].nome, "Psicose");
    strcpy(terror[1].genero, "Terror");
    terror[1].valor = 31.2;

    strcpy(terror[2].nome, "O Exorcista");
    strcpy(terror[2].genero, "Terror");
    terror[2].valor = 39.75;

    strcpy(terror[3].nome, "Coraline");
    strcpy(terror[3].genero, "Terror");
    terror[3].valor = 22.85;

    strcpy(terror[4].nome, "O Chamado de Cthulhu");
    strcpy(terror[4].genero, "Terror");
    terror[4].valor = 28.1;

     // parte visivel ao usuário

    printf("=========================================\n");
    printf("            LIVROS DE TERROR             \n");
    printf("=========================================\n");
    printf("\n");

    for (int contador = 0; contador < 5; contador++)
    {
        printf("[NOME:   ]      %s\n", terror[contador].nome);
        printf("[GENERO: ]      %s\n", terror[contador].genero);
        printf("[VALOR:  ]      %.2f\n", terror[contador].valor);
        printf("[ID:     ]      %i\n\n", contador);
    }
    printf("[5]       VOLTAR AO MENU            [6]     PRÓXIMA PÁGINA\n\n\n");
    printf("Para adicionar algum livro, digite o id deles, se não, ultilize\nos outros ids para voltar ao menu ou ir para a próxima página");
    scanf("%i", &opcaoTerror);

    // switch que permitirá que o usuário escolha qual o livro e se quer voltar ao menu ou ir para a prox pag

    switch (opcaoTerror){
    case 0:
        carrinho = carrinho + terror[0].valor;
        strcpy(carrinhoLivros[contadorLivros], terror[0].nome);
        carrinhoValores[contadorLivros] = terror[0].valor;
        contadorLivros ++;
        return livrosRomance();
        break;
    case 1:
        carrinho = carrinho + terror[1].valor;
        strcpy(carrinhoLivros[contadorLivros], terror[1].nome);
        carrinhoValores[contadorLivros] = terror[1].valor;
        contadorLivros ++;
        return livrosRomance();
        break;
    case 2:
        carrinho = carrinho + terror[2].valor;
        strcpy(carrinhoLivros[contadorLivros], terror[2].nome);
        carrinhoValores[contadorLivros] = terror[2].valor;
        contadorLivros ++;
        return livrosRomance();
        break;
    case 3:
        carrinho = carrinho + terror[3].valor;
        strcpy(carrinhoLivros[contadorLivros], terror[3].nome);
        carrinhoValores[contadorLivros] = terror[3].valor;
        contadorLivros ++;
        return livrosRomance();
        break;
    case 4:
        carrinho = carrinho + terror[4].valor;
        strcpy(carrinhoLivros[contadorLivros], terror[4].nome);
        carrinhoValores[contadorLivros] = terror[4].valor;
        contadorLivros ++;
        return livrosRomance();
        break;
    case 5:
        return menuPrincipal();
        break;
    case 6:
        return menuCarrinho();
        break;
    default:
        printf("Opçao inválida, selecione uma opção válida.");
        return livrosMisterio();
        break;
    }
}


        
