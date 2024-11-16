#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void tampilanAwal() {
    printf("============================================\n");
    printf("=                                          =\n");
    printf("=             SELAMAT DATANG               =\n");
    printf("=                                          =\n");
    printf("============================================\n");
    printf("=      WHO WANTS TO BE A MILLIONAIRE       =\n");
    printf("============================================\n");
    printf("=                                          =\n");
    printf("= Tekan enter untuk melanjutkan registrasi =\n");
    printf("=                                          =\n");
    printf("============================================\n");
    getchar();

}

int main () {
    tampilanAwal();


    FILE *fpw = fopen("database/login.bin","wb");
    if (fpw == NULL) {
        printf("hallo");
        printf("gagal membuka file!");
        printf("hallo 1");
        return EXIT_FAILURE;
    }

    char username[20],password[20];

    printf("masukkan username anda :");
    fgets(username,sizeof(username),stdin);
    username[strcspn(username, "\n")] = '\0';
    
    printf("masukkan password anda :");
    fgets(password,sizeof(password),stdin);
    password[strcspn(password, "\n")] = '\0';

    strcat(username, "@");
    strcat(username,password);

    fwrite(username,sizeof(char),sizeof(username)/sizeof(char),fpw);

    fclose(fpw);

    FILE *fpr = fopen("database/login.bin","rb");

    if (fpr == NULL) {
        printf("gagal membuka file!");
        return EXIT_FAILURE;
    }

    fread(username,sizeof(char),sizeof(username)/sizeof(char),fpr);

    fclose(fpr);
    char *string[3];
    char user[20], pass[20];
    int ctrl = 0;

    string[0] = strtok(username,"@");
    while(string[ctrl++] != NULL) {
        string[ctrl] = strtok(NULL,"@");
    }

    strcpy(user, string[0]);
    strcpy(pass, string[1]);

    printf("\n\n=============================================\n");
    printf("=         Registrasi Anda Berhasil          =\n");
    printf("=============================================\n");
    printf("= Silahkan Log in untuk memulai permainan!  =\n");
    printf("=============================================\n");

    
    char userLogin[10], passLogin[10];

    printf("\nUsername:");
    fgets(userLogin,sizeof(userLogin),stdin);
    userLogin[strcspn(userLogin, "\n")] = '\0';

    printf("Password:");
    fgets(passLogin,sizeof(passLogin),stdin);
    passLogin[strcspn(passLogin, "\n")] = '\0';
    
    if((strcmp(userLogin, user)) == 0 && (strcmp(passLogin, pass) == 0)) {
        printf("SELAMAT ANDA BERHASIL LOGIN!\n");
    } else {
        printf("AND LOGIN GAGAL!\n");
    }
    printf("=============================================\n");
    printf("=  Tekan enter untuk melanjutkan permainan  =\n");
    printf("=============================================\n");
    getchar();

    return 0;
}
