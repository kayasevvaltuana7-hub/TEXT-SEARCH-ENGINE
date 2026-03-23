#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RENK_SIFIRLA "\x1b[0m"
#define RENK_KIRMIZI "\x1b[31m"
#define RENK_YESIL "\x1b[32m"
#define RENK_SARI "\x1b[33m"
#define RENK_MAVI "\x1b[36m"
#define KALIN_YAZI "\x1b[1m"

void kmp_search(const char *dosya_yollari[], int dosya_sayisi, const char *aranan_kelime);
void ekrani_temizle(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    
int devam_et = 1;

    while (devam_et) {
    ekrani_temizle();
    
    printf("%s%s", RENK_MAVI, KALIN_YAZI);
    printf("╭══════════════════════════════════════════════════╮\n");
    printf("║                METİN ARAMA MOTORU                ║\n");
    printf("╰══════════════════════════════════════════════════╯\n");
    printf("%s", RENK_SIFIRLA);
    
    char aranan_kelime[100];
    int dosya_sayisi;
    char dosya_isimleri[10][100];
    const char *dosyalar[10];

    printf("\n%s Aranacak kelime:%s", RENK_SARI, RENK_SIFIRLA);
    scanf("%99s", aranan_kelime);

    printf(" \n%s Dosya sayisi: %s", RENK_SARI, RNEK_SIFIRLA);
    scanf("%d", &dosya_sayisi);
        
    if (scanf("%d", &dosya_sayisi) != 1) {
            printf("%sHatali giris!%s\n", RENK_KIRMIZI, RENK_SIFIRLA);
            break;
        }

   if (dosya_sayisi > 10) dosya_sayisi = 10;
   if (dosya_sayisi <= 0) dosya_sayisi = 1;

    for (int i = 0; i < dosya_sayisi; i++) {
        printf(" %s %d. dosya adi:(ORN.:metin.txt) %s ",RENK_SARI, i + 1, RENK_SIFIRLA);
        scanf("%99s", dosya_isimleri[i]);
        dosyalar[i] = dosya_isimleri[i];
    }

    kmp_search(dosyalar, dosya_sayisi, aranan_kelime);
   
    printf("\n%s────────────────────────────────────────────────────%s\n", RENK_MAVI, RENK_SIFIRLA);
    printf("  [1] Yeni Arama Yap\n");
    printf("  [0] Programdan Cik\n");
    printf("%s  Seciminiz: %s", RENK_SARI, RENK_SIFIRLA);
        
        int secim;
        scanf("%d", &secim);
        if (secim == 0) {
            devam_et = 0;
            printf("\n%sSistemden cikiliyor... %s\n", RENK_YESIL, RENK_SIFIRLA);
        }
    }
    return 0;
}
