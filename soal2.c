#include <stdio.h>

int main() {
    int num;

    // Meminta input bilangan dari pengguna
    printf("Masukkan sebuah bilangan: ");
    scanf("%d", &num);

    // Pemeriksaan logika: apakah bilangan lebih besar dari 10 dan kurang dari 20
    if (num > 10 && num < 20) {
        printf("Bilangan %d lebih besar dari 10 dan kurang dari 20.\n", num);
    } else {
        printf("Bilangan %d tidak berada di antara 10 dan 20.\n", num);
    }

    // Operator ternary: menentukan apakah bilangan genap atau ganjil
    printf("Bilangan %d adalah %s.\n", num, (num % 2 == 0) ? "genap" : "ganjil");

    // Menampilkan hasil increment dan decrement
    printf("Hasil increment dari %d adalah %d.\n", num, num + 1);
    printf("Hasil decrement dari %d adalah %d.\n", num, num - 1);

    return 0;
}
