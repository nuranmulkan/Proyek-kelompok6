#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

int cekKosong(char *input) {
    if (strlen(input) == 0) {
        printf("Input tidak boleh kosong. Silakan coba lagi.\n");
        return 0;
    }
    return 1;
}

int main() {
    tampilanAwal();

    FILE *fpw = fopen("database/login.bin", "wb");
    if (fpw == NULL) {
        printf("Gagal membuka file!");
        return EXIT_FAILURE;
    }

    char username[50], password[50];

    do {
        printf("Masukkan username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';
    } while (!cekKosong(username));

    do {
        printf("Masukkan password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';
    } while (!cekKosong(password));

    strcat(username, "@");
    strcat(username, password);

    fwrite(username, sizeof(char), sizeof(username) / sizeof(char), fpw);
    fclose(fpw);

    FILE *fpr = fopen("database/login.bin", "rb");
    if (fpr == NULL) {
        printf("Gagal membuka file!");
        return EXIT_FAILURE;
    }

    fread(username, sizeof(char), sizeof(username) / sizeof(char), fpr);
    fclose(fpr);

    char *string[3];
    char user[50], pass[50];
    int ctrl = 0;

    string[0] = strtok(username, "@");
    while (string[ctrl++] != NULL) {
        string[ctrl] = strtok(NULL, "@");
    }

    strcpy(user, string[0]);
    strcpy(pass, string[1]);

    printf("\n\n=============================================\n");
    printf("=         Registrasi Anda Berhasil          =\n");
    printf("=============================================\n");
    printf("=  Silahkan Login untuk memulai permainan!  =\n");
    printf("=============================================\n");
    printf("=       Tekan enter untuk melanjutkan       =\n");
    printf("=============================================\n\n");
    getchar();

    char userLog[20], passLog[20];
    printf("Masukkan username :");
    fgets(userLog, sizeof(userLog), stdin);
    userLog[strcspn(userLog, "\n")] = '\0';

    printf("Masukkan password :");
    fgets(passLog, sizeof(passLog), stdin);
    passLog[strcspn(passLog, "\n")] = '\0';

    if ((strcmp(userLog, user) == 0) && (strcmp(passLog, pass) == 0)) {
        printf("\n\n=============================================\n");
        printf("=        SELAMAT ANDA BERHASIL LOGIN!       =\n");
        printf("=============================================\n");
        printf("=  Tekan enter untuk melanjutkan permainan  =\n");
        printf("=============================================\n");
        getchar();
    } else {
        printf("=============================================\n");
        printf("=             ANDA GAGAL LOGIN!             =\n");
        printf("=============================================\n");
    }

    return 0;
}
