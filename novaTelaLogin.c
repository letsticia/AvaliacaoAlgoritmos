#include <stdio.h>
#include <string.h>
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
      printf("Email: %s | Senha: %s\n", emailsenha[i].email, emailsenha[i].senha);
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
     && strchr(novo_usuario.email, '@') != NULL) {    //análise se o email possui o caractere ' @ '
            return 1;
        } 
      return 0;
}

int main() {            // função principal do código

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
  return 0;
}