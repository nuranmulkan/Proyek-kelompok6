#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef struct {
    char username[50];
    char password[50];
} User;

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

void tampilkanMenu(int skor) {
    printf("\n=============================================\n");
    printf("=        1. Lanjutkan Permainan             =\n");
    printf("=        2. Keluar dari permainan           =\n");
    printf("=        3. Restart Permainan               =\n");
    printf("=============================================\n");
    printf("Skor Anda: %d\n", skor);
    printf("Pilihan Anda: ");
}

int cekKosong(char *input) {
    if (strlen(input) == 0) {
        printf("Input tidak boleh kosong. Silakan coba lagi.\n");
        return 0;
    }
    return 1;
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

void simpanDataUser(User *user) {
    FILE *fpw = fopen("database/login.bin", "wb");
    if (fpw == NULL) {
        printf("Gagal membuka file!");
        exit(EXIT_FAILURE);
    }
    fwrite(user, sizeof(User), 1, fpw);
    fclose(fpw);
}

int loginUser(User *user) {
    char userLog[50], passLog[50];
    int login_berhasil = 0;
    while (!login_berhasil) {
        printf("Masukkan username :");
        fgets(userLog, sizeof(userLog), stdin);
        userLog[strcspn(userLog, "\n")] = '\0';

        printf("Masukkan password :");
        fgets(passLog, sizeof(passLog), stdin);
        passLog[strcspn(passLog, "\n")] = '\0';

        if ((strcmp(userLog, user->username) == 0) && (strcmp(passLog, user->password) == 0)) {
            printf("\n\n=============================================\n");
            printf("=        SELAMAT ANDA BERHASIL LOGIN!       =\n");
            printf("=============================================\n");
            printf("=  Tekan enter untuk melanjutkan permainan  =\n");
            printf("=============================================\n");
            getchar();
            login_berhasil = 1;
        } else {
            printf("=============================================\n");
            printf("=             ANDA GAGAL LOGIN!             =\n");
            printf("=============================================\n");
        }
    }
    return login_berhasil;
}

int main() {
    int restart = 1;
    while (restart) {
        tampilanAwal();

        User user;

        do {
            printf("Masukkan username: ");
            fgets(user.username, sizeof(user.username), stdin);
            user.username[strcspn(user.username, "\n")] = '\0';
        } while (!cekKosong(user.username));

        do {
            printf("Masukkan password: ");
            fgets(user.password, sizeof(user.password), stdin);
            user.password[strcspn(user.password, "\n")] = '\0';
        } while (!cekKosong(user.password));

        simpanDataUser(&user);

        FILE *fpr = fopen("database/login.bin", "rb");
        if (fpr == NULL) {
            printf("Gagal membuka file!");
            return EXIT_FAILURE;
        }
        fread(&user, sizeof(User), 1, fpr);
        fclose(fpr);

        printf("\n\n=============================================\n");
        printf("=         Registrasi Anda Berhasil          =\n");
        printf("=============================================\n");
        printf("=  Silahkan Login untuk memulai permainan!  =\n");
        printf("=============================================\n");
        printf("=       Tekan enter untuk melanjutkan       =\n");
        printf("=============================================\n\n");
        getchar();

        loginUser(&user);

        int skor = 0;
        permainan(&skor);

        restart = 0;
    }

    return 0;
}
