#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int score = 0;
int level = 1;

void tampilanAwal();
void selamatDatang();

int main (int banyakArgumen, char *argumen[]) {
    tampilanAwal();

    if (banyakArgumen != 3) {
        printf("Harus terdapat 3 argumen saat menjalankan program!\n");
        printf("Cara penggunaan : ./main Username Password!\n");
        return 1;
    }

    FILE *fpw = fopen("database/login.bin","wb");
    if (fpw == NULL) {
        printf("gagal membuka file!");
        return EXIT_FAILURE;
    }

    char username[50],password[50];

    printf("masukkan username :");
    fgets(username,sizeof(username),stdin);
    username[strcspn(username, "\n")] = '\0';
    
    printf("masukkan password :");
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
    char user[50], pass[50];
    int ctrl = 0;

    string[0] = strtok(username,"@");
    while(string[ctrl++] != NULL) {
        string[ctrl] = strtok(NULL,"@");
    }

    strcpy(user, string[0]);
    strcpy(pass, string[1]);

    printf("=============================================\n");
    printf("=         Registrasi Anda Berhasil          =\n");
    printf("=============================================\n");
    printf("=  Silahkan Login ntuk memulai permainan!   =\n");
    printf("=============================================\n");
    printf("=       Tekan enter untuk melanjutkan       =\n");
    printf("=============================================");
    getchar();

    char userLog[20], passLog[20];
    printf("Masukkan username :");
    fgets(userLog, sizeof(userLog), stdin);

    printf("Masukkan password :");
    fgets(passLog, sizeof(passLog), stdin);

    char userLogin[10], passLogin[10];
    strcpy(userLogin,argumen[1]);
    strcpy(passLogin,argumen[2]);

    if((strcmp(userLogin, user)) == 0 && (strcmp(passLogin, pass) == 0)) {
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
    printf("============================================");
    getchar();
}
void tampilkanMenu() {
        printf("=============================================\n");
        printf("=              🎮 MENU UTAMA 🎮             =\n");
        printf("=============================================\n");
        printf("=  1️⃣  Lanjutkan Permainan                  =\n");
        printf("=  2️⃣  Keluar dari Permainan                =\n");
        printf("=  3️⃣  Restart Permainan                    =\n");
        printf("=============================================\n");
        printf("🌟 Skor Anda Saat Ini: %d\n", score);
        printf("=============================================\n");
        printf("👉 Pilih opsi Anda (1/2/3): ");
        int pilihan;
        scanf("%d", &pilihan);
            getchar(); 

            switch (pilihan) {
                case 1:
                    lanjutkanPermainan();
                    break;
                case 2:
                    keluarPermainan();
                    break;
                case 3:
                    restartPermainan();
                    break;
                default:
                    printf("❌ Pilihan tidak valid. Silakan coba lagi!\n");
            }

    }
   void lanjutkanPermainan() {
        printf("\n=============================================\n");
        printf("=       Anda memilih untuk melanjutkan!     =\n");
        printf("=============================================\n");
        switch (level) {
        case 1:
            pertanyaan1();
            break;
        case 2:
            pertanyaan2();
            break;
        default:
            printf("âŒ Pertanyaan untuk level %d belum tersedia!\n", level);
    }
}
    
    void keluarPermainan() {
        printf("\n=============================================\n");
        printf("=       Terima kasih telah bermain!         =\n");
        printf("=============================================\n");
        printf("ðŸ‘‹ Sampai jumpa lagi!\n");
    }

    \
    void restartPermainan() {
        printf("\n=============================================\n");
        printf("=       Permainan telah di-restart!         =\n");
        printf("=============================================\n");
        score = 0; 
        level = 1;
        printf("ðŸŒŸ Skor Anda sekarang: %d\n", score);
        getchar();
        pertanyaan1();
    }

