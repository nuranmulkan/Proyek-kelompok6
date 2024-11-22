#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

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

int main() {
    int restart = 1;
    while (restart) {
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

        fwrite(username, sizeof(char), strlen(username), fpw);
        fwrite(password, sizeof(char), strlen(password), fpw);
        fclose(fpw);

        FILE *fpr = fopen("database/login.bin", "rb");
        if (fpr == NULL) {
            printf("Gagal membuka file!");
            return EXIT_FAILURE;
        }

        fread(username, sizeof(char), sizeof(username), fpr);
        fread(password, sizeof(char), sizeof(password), fpr);
        fclose(fpr);

        printf("\n\n=============================================\n");
        printf("=         Registrasi Anda Berhasil          =\n");
        printf("=============================================\n");
        printf("=  Silahkan Login untuk memulai permainan!  =\n");
        printf("=============================================\n");
        printf("=       Tekan enter untuk melanjutkan       =\n");
        printf("=============================================\n\n");
        getchar();

        char userLog[50], passLog[50];
        int login_berhasil = 0;
        while (!login_berhasil) {
            printf("Masukkan username :");
            fgets(userLog, sizeof(userLog), stdin);
            userLog[strcspn(userLog, "\n")] = '\0';

            printf("Masukkan password :");
            fgets(passLog, sizeof(passLog), stdin);
            passLog[strcspn(passLog, "\n")] = '\0';

            if ((strcmp(userLog, username) == 0) && (strcmp(passLog, password) == 0)) {
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

        int skor = 0;
        char pilihan[2];

        while (1) {
            tampilkanMenu(skor);
            fgets(pilihan, sizeof(pilihan), stdin);
            pilihan[strcspn(pilihan, "\n")] = '\0';

            if (pilihan[0] == '1') {
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
                        skor += 1000;
                    } else {
                        printf("Jawaban Anda salah.\n");
                    }
                }

                printf("\n=============================================\n");
            } else if (pilihan[0] == '2') {
                printf("\n=============================================\n");
                printf("=        Terima kasih telah bermain!        =\n");
                printf("=============================================\n");
                restart = 0;
                break;
            } else if (pilihan[0] == '3') {
                printf("\n=============================================\n");
                printf("=            Permainan di-restart!          =\n");
                printf("=============================================\n");
                break;
            }
        }
    }

    return 0;
}
