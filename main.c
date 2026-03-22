#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void kmp_search(const char *dosya_yollari[], int dosya_sayisi, const char *aranan_kelime);

int main() {
    char aranan_kelime[100];
    int dosya_sayisi;
    char dosya_isimleri[10][100];
    const char *dosyalar[10];

    printf("Aranacak kelime: ");
    scanf("%99s", aranan_kelime);

    printf("Dosya sayisi: ");
    scanf("%d", &dosya_sayisi);

    if (dosya_sayisi > 10) dosya_sayisi = 10;

    for (int i = 0; i < dosya_sayisi; i++) {
        printf("%d. dosya adi: ", i + 1);
        scanf("%99s", dosya_isimleri[i]);
        dosyalar[i] = dosya_isimleri[i];
    }

    kmp_search(dosyalar, dosya_sayisi, aranan_kelime);

    return 0;
}