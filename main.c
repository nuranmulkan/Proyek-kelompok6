#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int score = 0;
int restart = 0;

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

void pertanyaan1(int *skor) {
    printf("\nPertanyaan 1: Apa ibu kota Indonesia?\n");
    printf("a. Jakarta\nb. Bandung\nc. Surabaya\nd. Yogyakarta\n");
    printf("Jawaban Anda: ");
    
    time_t start_time, end_time;
    double elapsed_time;
    char jawaban1;

    time(&start_time);
    scanf(" %c", &jawaban1);
    time(&end_time);

    elapsed_time = difftime(end_time, start_time);

    if (elapsed_time > 30) {
        printf("\nWaktu habis! Jawaban tidak dihitung.\n");
    } else {
        if (jawaban1 == 'a' || jawaban1 == 'A') {
            printf("Jawaban Anda benar!\n");
            *skor += 1000;
        } else {
            printf("Jawaban Anda salah.\n");
        }
    }
    printf("\n=============================================\n");
}
void displayCorrectAnswerMessage() {
    printf("\n=============================\n");
    printf("  Selamat, Anda Benar! \n");
    printf("=============================\n");
}

void askQuestion(const char *question, const char *correctAnswer, int *skor) {
    char answer[100];

    printf("\nPertanyaan:\n%s\n", question);
    printf("Masukkan jawaban Anda: ");
    scanf(" %99[^\n]", answer);

    // Gunakan if-else untuk mengecek jawaban, baik huruf besar maupun kecil
    if ((strcmp(answer, correctAnswer) == 0) ||
        (strcmp(answer, "a") == 0 && strcmp(correctAnswer, "A") == 0) ||
        (strcmp(answer, "b") == 0 && strcmp(correctAnswer, "B") == 0) ||
        (strcmp(answer, "c") == 0 && strcmp(correctAnswer, "C") == 0) ||
        (strcmp(answer, "d") == 0 && strcmp(correctAnswer, "D") == 0)) {
        displayCorrectAnswerMessage();
        (*skor) += 10;
        
    } else {
        printf("\nJawaban Anda salah. \n");
    }

void tampilkanMenu(int skor) {
    printf("\n=============================================\n");
    printf("=        1. Lanjutkan Permainan             =\n");
    printf("=        2. Keluar dari permainan           =\n");
    printf("=        3. Restart Permainan               =\n");
    printf("=============================================\n");
    printf("Skor Anda: %d\n", skor);
    printf("Pilihan Anda: ");
}

void permainan(int *skor) {
    char pilihan[2];
    
    while (1) {
        tampilkanMenu(*skor);
        fgets(pilihan, sizeof(pilihan), stdin);
        pilihan[strcspn(pilihan, "\n")] = '\0';

        if (pilihan[0] == '1') {
            pertanyaan1(skor);
        } else if (pilihan[0] == '2') {
            printf("\n=============================================\n");
            printf("=        Terima kasih telah bermain!        =\n");
            printf("=============================================\n");
            break;
        } else if (pilihan[0] == '3') {
            printf("\n=============================================\n");
            printf("=            Permainan di-restart!          =\n");
            printf("=============================================\n");
            break;
        }
    }
}

int main (int banyakArgumen, char *argumen[]) {
    tampilanAwal();

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

    printf("\n\n=============================================\n");
    printf("=         Registrasi Anda Berhasil          =\n");
    printf("=============================================\n");
    printf("=  Silahkan Login ntuk memulai permainan!   =\n");
    printf("=============================================\n");
    printf("=       Tekan enter untuk melanjutkan       =\n");
    printf("=============================================\n\n");
    getchar();

    char userLog[20], passLog[20];
    printf("Masukkan username :");
    fgets(userLog, sizeof(userLog), stdin);

    printf("Masukkan password :");
    fgets(passLog, sizeof(passLog), stdin);

    
    char userLogin[10], passLogin[10];
    if (banyakArgumen != 3) {
        printf("Gagal Login!");
        printf("Cara penggunaan : ./main Username Password!");
    }

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
    
        permainan(skor);
        restart = 0;
    }

    return 0;
}
