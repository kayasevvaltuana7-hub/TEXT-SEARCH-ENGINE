#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RENK_SIFIRLA "\x1b[0m"
#define RENK_KIRMIZI "\x1b[31m"
#define RENK_YESIL   "\x1b[32m"
#define RENK_SARI    "\x1b[33m"
#define RENK_MAVI    "\x1b[36m"
#define KALIN_YAZI   "\x1b[1m"

int processFile(char fileName[], char searchWord[]);

void ekrani_temizle() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    int devam_et = 1;

    // Dinamik Menü Döngümüz
    while (devam_et) {
        ekrani_temizle();
        
        printf("%s%s", RENK_MAVI, KALIN_YAZI);
        printf("╭══════════════════════════════════════════════════╮\n");
        printf("║                 METİN ARAMA MOTORU               ║\n");
        printf("╰══════════════════════════════════════════════════╯\n");
        printf("%s", RENK_SIFIRLA);

        char aranan_kelime[100];
        int dosya_sayisi = 0;
        char dosya_isimleri[10][100];

        printf("\n%s  Aranacak kelime: %s", RENK_SARI, RENK_SIFIRLA);
        scanf("%99s", aranan_kelime);

        printf("%s  Aranacak dosya sayısı %s", RENK_SARI, RENK_SIFIRLA);
        if (scanf("%d", &dosya_sayisi) != 1) {
            printf("%sHatali giris!%s\n", RENK_KIRMIZI, RENK_SIFIRLA);
            break;
        }

        
        if (dosya_sayisi > 10) dosya_sayisi = 10;
        if (dosya_sayisi <= 0) dosya_sayisi = 1;

        for (int i = 0; i < dosya_sayisi; i++) {
            printf("%s      -> %d. dosya adi (orn: metin.txt): %s", RENK_SARI, i + 1, RENK_SIFIRLA);
            scanf("%99s", dosya_isimleri[i]);
        }

        int genel_toplam_tekrar = 0;
        int basarisiz_dosya = 0;
        
        for (int i = 0; i < dosya_sayisi; i++) {
            
            int sonuc = processFile(dosya_isimleri[i], aranan_kelime);
            
            if (sonuc == -1) {
                basarisiz_dosya++; 
            } else {
                // Dosya başarıyla okunduysa, içindeki kelime sayısını genel toplama ekliyoruz
                genel_toplam_tekrar += sonuc; 
            }
        }

        // --- İSTATİSTİKSEL ÖZET TABLOMUZ ---
        printf("\n%s%s  ✓ ARAMA İŞLEMİ TAMAMLANDI%s\n", RENK_YESIL, KALIN_YAZI, RENK_SIFIRLA);
        printf("  ╭─ İstatistiksel Özet Tablosu ─────────────────────╮\n");
        printf("  │ Aranan Kelime     : %-28s │\n", aranan_kelime);
        printf("  │ Taranan Dosya     : %-28d │\n", dosya_sayisi - basarisiz_dosya);
        printf("  │ Toplam Frekans    : %-28d │\n", genel_toplam_tekrar);
        printf("  ╰──────────────────────────────────────────────────╯\n");

        printf("\n%s────────────────────────────────────────────────────%s\n", RENK_MAVI, RENK_SIFIRLA);
        printf("  [1] Yeni Arama Yap\n");
        printf("  [0] Programdan Cik\n");
        printf("%s  Seciminiz: %s", RENK_SARI, RENK_SIFIRLA);
        
        int secim;
        scanf("%d", &secim);
        if (secim == 0) {
            devam_et = 0;
            printf("\n%sSistemden cikiliyor...%s\n", RENK_YESIL, RENK_SIFIRLA);
        }
    }

    return 0;
}
