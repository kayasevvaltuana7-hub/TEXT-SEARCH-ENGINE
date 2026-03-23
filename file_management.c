#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//KMP prototipi
void kmp_search(const char *dosya_yollari[], int dosya_sayisi, const char *aranan_kelime) {
    int m = strlen(aranan_kelime);
    char pattern[1024];
    for (int i = 0; i < m; i++)
        pattern[i] = tolower(aranan_kelime[i]);
    pattern[m] = '\0';

    int fail[1024] = {0};
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j])
            j = fail[j - 1];
        if (pattern[i] == pattern[j])
            j++;
        fail[i] = j;
    }

    for (int d = 0; d < dosya_sayisi; d++) {
        FILE *f = fopen(dosya_yollari[d], "r");
        if (!f) {
            printf("Dosya bulunamadi: %s\n", dosya_yollari[d]);
            continue;
        }

        printf("\n=== %s ===\n", dosya_yollari[d]);

        char satir[4096];
        int satir_no = 0;
        int toplam_tekrar = 0;

        while (fgets(satir, sizeof(satir), f)) {
            satir_no++;
            int n = strlen(satir);

            char satir_lower[4096];
            for (int i = 0; i < n; i++)
                satir_lower[i] = tolower(satir[i]);
            satir_lower[n] = '\0';

            int count = 0;
            j = 0;
            for (int i = 0; i < n; i++) {
                while (j > 0 && satir_lower[i] != pattern[j])
                    j = fail[j - 1];
                if (satir_lower[i] == pattern[j])
                    j++;
                if (j == m) {
                    count++;
                    j = fail[j - 1];
                }
            }

            if (count > 0) {
                satir[strcspn(satir, "\n")] = '\0';
                printf("  Satir %d (%dx): %s\n", satir_no, count, satir);
                toplam_tekrar += count;
            }
        }

        printf("  Toplam tekrar: %d\n", toplam_tekrar);
        fclose(f);
    }
}

//ana gorev fonksiyonumuz
int processFile (char fileName[], char searchWord[])
 {
    FILE*filePtr=fopen(fileName, "r");
    
    if (filePtr == NULL) {
        return -1; 
    }

    char lineBuffer [1024];
    int lineNumber=1;
    int totalMatches=0;

    while (fgets ( lineBuffer, sizeof(lineBuffer), filePtr) != NULL) {
        
        //KMP'e gonder
        int lineFound=kmpSearch(searchWord, lineBuffer );
        
        if (lineFound>0) {
            totalMatches +=lineFound;
            //Arayuzu burada duzenleyebiliriz
            printf("[%d. Satir]: %s", lineNumber, lineBuffer);
        }
        lineNumber++;
    }

    fclose(filePtr);
    return totalMatches; //sonucu Main'e yollar
}
