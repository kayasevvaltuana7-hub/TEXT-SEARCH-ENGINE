#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void kmp_search_logic(const char *aranan, const char *satir, int satir_no, int *toplam) {
    int m = strlen(aranan);
    int n = strlen(satir);
    if (m == 0) return;

    char *pat = malloc(m + 1);
    for (int i = 0; i < m; i++) pat[i] = tolower((unsigned char)aranan[i]);
    
    int *fail = calloc(m, sizeof(int));
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && pat[i] != pat[j]) j = fail[j - 1];
        if (pat[i] == pat[j]) j++;
        fail[i] = j;
    }

    int count = 0;
    j = 0;
    for (int i = 0; i < n; i++) {
        char c = tolower((unsigned char)satir[i]);
        while (j > 0 && c != pat[j]) j = fail[j - 1];
        if (c == pat[j]) j++;
        if (j == m) {
            count++;
            j = fail[j - 1];
        }
    }

    if (count > 0) {
        printf("  [Satir %d] %dx bulundu: %s\n", satir_no, count, satir);
        *toplam += count;
    }

    free(pat);
    free(fail);
}

int process_file(char *name, char *word) {
    FILE *f = fopen(name, "r");
    if (!f) {
        printf("  [!] Hata: %s acilamadi.\n", name);
        return -1;
    }

    char buf[1024];
    int line = 1, total = 0;
    while (fgets(buf, sizeof(buf), f)) {
        buf[strcspn(buf, "\r\n")] = 0;
        kmp_search_logic(word, buf, line++, &total);
    }
    fclose(f);
    return total;
}

int main() {
    char kelime[100], dosyalar[10][100];
    int adet, secim = 1;

    while (secim) {
        printf("\n=== METIN ARAMA MOTORU ===\n");
        printf("Aranacak kelime: ");
        scanf("%99s", kelime);

        printf("Kac dosya taranacak: ");
        if (scanf("%d", &adet) != 1) break;

        for (int i = 0; i < adet && i < 10; i++) {
            printf("  -> %d. dosya adi (uzantisiyla): ", i + 1);
            scanf("%99s", dosyalar[i]);
        }

        int genel = 0;
        for (int i = 0; i < adet && i < 10; i++) {
            printf("\n--- %s inceleniyor ---\n", dosyalar[i]);
            int res = process_file(dosyalar[i], kelime);
            if (res > 0) genel += res;
        }

        printf("\nTOPLAM BULUNAN: %d\n", genel);
        printf("Yeni arama [1] / Cikis [0]: ");
        scanf("%d", &secim);
    }
    return 0;
}