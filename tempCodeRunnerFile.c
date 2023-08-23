int menuCadastro(){
    char email[80];
    char senha[8];
    int opcaoLogin;

    printf("=========================================\n");
    printf("              Menu de Login              \n");
    printf("=========================================\n");
    printf("\n");
    printf("[E-mail:]");
    scanf("%[^\n]", &email);
    printf(" [Senha:]");
    scanf("%s", senha);
    printf("\n");
    
    if(strlen(email) > 80){
        printf("O email deve conter, no máximo, 80 caracteres\n");
        printf("você deseja tentar criar uma conta novamente(1) ou voltar para o menu principal?(2)");
        scanf("%i", &opcaoLogin);
        switch (opcaoLogin)
        {
        case 1:
            return menuCadastro();
            break;
        case 2:
            return menuInicial();
            break;
        default:
            break;
        }
    };
}