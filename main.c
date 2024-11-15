#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main () {
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
    
    printf("masukkan password anda : ");
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
    printf("%s",username);
    return 0;
}
