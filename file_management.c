#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RENK_SIFIRLA "\x1b[0m"
#define RENK_KIRMIZI "\x1b[31m"
#define RENK_YESIL   "\x1b[32m"
#define RENK_SARI    "\x1b[33m"
#define RENK_MAVI    "\x1b[36m"
#define KALIN_YAZI   "\x1b[1m"

int kmpSearch(char searchWord[], char lineBuffer[]);

// Ana gorev fonksiyonumuz
int processFile(char fileName[], char searchWord[]) {
    FILE* filePtr = fopen(fileName, "r");
    
    if (filePtr == NULL) {
        // Hata mesajını kırmızı verelim
        printf("%s[!] HATA: '%s' dosyasi acilamadi.%s\n", RENK_KIRMIZI, fileName, RENK_SIFIRLA);
        return -1; 
    }

    char lineBuffer[1024];
    int lineNumber = 1;
    int totalMatches = 0;

    while (fgets(lineBuffer, sizeof(lineBuffer), filePtr) != NULL) {
       
        lineBuffer[strcspn(lineBuffer, "\n")] = '\0';

        // KMP'e gonder
        int lineFound = kmpSearch(searchWord, lineBuffer);
        
        if (lineFound > 0) {
            totalMatches += lineFound;
            
            printf("  %s[%d. Satir]%s: %s\n", RENK_YESIL, lineNumber, RENK_SIFIRLA, lineBuffer);
        }
        lineNumber++;
    }

    fclose(filePtr);
    return totalMatches; // Sonucu Main'e yollar
}
