#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
