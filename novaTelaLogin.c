#include <stdio.h>
#include <string.h>
#define caracteres_max 80

struct Usuario {
  char email[caracteres_max];
  char senha[caracteres_max];
  char nome[caracteres_max];
};

struct Usuario emailsenha[caracteres_max];
int quantidade = 0;
char email_digitado[caracteres_max];
char senha_digitada[caracteres_max];

void logar() {
  printf("Digite seu email:\n");
  scanf(" %[^\n]s", email_digitado);
  printf("Digite sua senha:\n");
  scanf(" %[^\n]s", senha_digitada);
}

struct Usuario novo_usuario;

void cadastrar() {
  printf("Informe seu nome:\n");
  scanf(" %[^\n]s", novo_usuario.nome);
  printf("Crie seu email:\n");
  scanf(" %[^\n]s", novo_usuario.email);
  printf("Digite sua senha:\n");
  scanf(" %[^\n]s", novo_usuario.senha);
}

void cadastrar2() {
  printf("Crie seu email:\n");
  scanf(" %[^\n]s", novo_usuario.email);
  printf("Digite sua senha:\n");
  scanf(" %[^\n]s", novo_usuario.senha);
}

void telaDeLogin() {
  printf("======= TELA DE LOGIN =======\n1- Entrar na conta\n2- Cadastra-se\n3- "
         "Encerrar programa\n4- Listar contas cadastradas\n5- Editar senha"
         "\n6- Excluir conta"
         "\n=============================\n");
}

void loginErrado() {
  printf("Erro de cadastramento, possíveis motivos:\n1- email e/ou senha "
         "atingiram 80 ou mais caracteres.\n2- o email não possui o caractere "
         "'@'.\n3- O email já está cadastrado no sistema.\n\n");
}

void listarContas() {
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

void editarSenha() {
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
int op;

void loginCerto() {
  for (int i = 0; i < quantidade; i++) {
    if (strcmp(email_digitado, emailsenha[i].email) == 0 &&
        strcmp(senha_digitada, emailsenha[i].senha) == 0) {
      printf("Login realizado com sucesso!\nSeja bem-vindo, sr(a). %s\n", emailsenha[i].nome);
      encontrado = 1;
      op = 3;
      break;
    }
  }
}

void excluirConta() {
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
      printf("Conta excluida com êxito!\n");
      quantidade--;
      encontrado = 1;
      break;
    }
  }
  if(!encontrado) {
    printf("Email e/ou senha incorretos. Tente novamente.\n");
  }
}

int valideEmail(struct Usuario novo_usuario){
        for (int i = 0; i < quantidade; i++) {
          if (strcmp(novo_usuario.email, emailsenha[i].email) == 0) {
            return 0;
          }
        }

        if (strlen(novo_usuario.email) < caracteres_max
     && strlen(novo_usuario.senha) < caracteres_max
     &&
            strchr(novo_usuario.email, '@') != NULL) {
            return 1;
        } 
      return 0;
}

int main() {

  while (op != 3) {
    telaDeLogin();
    scanf("%d", &op);
    switch (op) {
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
          printf("Conta cadastrada com êxito!\n");
          break;
        }
        else {
          while(1){
          loginErrado();
          cadastrar2(); 
          if (valideEmail(novo_usuario) == 1) {
            emailsenha[quantidade] = novo_usuario;
            quantidade++;
            printf("Conta cadastrada com êxito!\n");
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
      printf("Opção inválida.\n"); //ver aq
      return 1;
    }
  }
  return 0;
}