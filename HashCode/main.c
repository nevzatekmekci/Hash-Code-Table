//
//  main.c
//  AlgoritmaAnalizi3
//
//  Created by nevzat on 10/12/15.
//  Copyright © 2015 nevzat. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#define BOYUT 1000
int h1(int key);
int h2(int key);
const char *options[BOYUT][100];
char kelime[BOYUT][20];
char kelime2[BOYUT];
char search[30];
char dizin[BOYUT];
char dosya[BOYUT];
int limit;
int main(int argc, const char * argv[]) {
    FILE *file,*file2;
    file= fopen("/Users/nevzat/Desktop/AlgoritmaAnalizi3/AlgoritmaAnalizi3/stop-word-list.txt","r+");
    
    int c,c2,i,j,key;
    if (file==NULL)
    {
        perror("cannot open file to read");
    }
    int count=0,value,control=0;
    limit = 2 >= count / 0.6;
    
    c = fscanf(file,"%s",kelime[count]);
    while(c != EOF) {
        printf("%d %s\n",(count+1),kelime[count++]);
        c = fscanf(file,"%s",kelime[count]);
    }
    limit = 3*count;
    strcat(dizin, "/Users/nevzat/Desktop/AlgoritmaAnalizi3/AlgoritmaAnalizi3/");
    char stopWord[1000][20];
    char hashTable[1000][20];
    
    memset(stopWord, 0, sizeof(stopWord));
    memset(hashTable, 0, sizeof(hashTable));
    char buf[10] = {0};
    for (i=0; i<count+1; i++) {
        for(j=0;j<strlen(kelime[i]);j++){
            printf("%c",kelime[i][j]);
        }
        printf("\n");
    }
    
    for(i=0;i<count;i++){
        key=0;
        for(j=0;j < strlen(kelime[i]); j++)
            key += (kelime[i][j] - 'a' )*26*i ;
        j=0;
        value = (h1(key) + j*h2(key)) % limit;
        while (stopWord[value][0]!='\0') {
            j++;
            value = (h1(key) + j*h2(key)) % limit;
        }
        strcpy(stopWord[value], kelime[i]);

    }
    
    file = fopen("/Users/nevzat/Desktop/AlgoritmaAnalizi3/AlgoritmaAnalizi3/documentList.txt","r+");
    if (file==NULL)
    {
        perror("cannot open file to read");
    }
    c = fscanf(file,"%s",dosya);
    while(c != EOF) {
        file2 = fopen(strcat(dizin, dosya), "r+");
        if (file2==NULL)
        {
            perror("cannot open file to read");
        }
        c2 = fscanf(file2,"%s",kelime2);
        while(c2 != EOF) {
                key=0;
                for(j=0;j < strlen(kelime2); j++)
                    key += (kelime2[j] - 'a' )*26*j ;
                j=0;
                value = (h1(key) + j*h2(key)) % limit;
            if(!strcmp(kelime2, stopWord[value])){
                printf("Kelime stopwordde\n");
                control = 1;
            }
                while ((stopWord[value][0]!="")&&(control==0)) {
                    j++;
                    value = (h1(key) + j*h2(key)) % limit;
                    if(!strcmp(kelime2, stopWord[value])){
                        printf("Kelime stopwordde\n");
                        control = 1;
                    }
                }
            if(control==0){
                j=0;
                value = (h1(key) + j*h2(key)) % limit;
                while ((hashTable[value][0]!="")&&(strcmp(kelime2, hashTable[value]))) {
                    j++;
                    value = (h1(key) + j*h2(key)) % limit;
                }
                if(strcmp(kelime2, hashTable[value])){
                    //Aynı kelimeyse dokuman ısmını ekle
                    strcpy(hashTable[value], kelime2);
                }
                strcat(hashTable[value],strcat(",", dosya));
            }
            memset(kelime2, 0, sizeof(kelime2));
            c2 = fscanf(file2,"%s",dosya);
        }
        c = fscanf(file,"%s",dosya);
    }
    
    do{
        printf("Aramak için bir kelime giriniz\n");
        gets(&search);
        
        
        printf("Devam etmek istermisiniz? 1/0?:");
        scanf("%d",&control);
    }while (control==1);
    EXIT(1);

    

    
    return 0;
}
/*
int key(char[] word)
{
    int value=0,j;
    for(j=0;j < strlen(word); j++)
        value += (word[j] - 'a' )*26*j ;
}
 */
int h1(int key)
{
    return key%limit;
}
int h2(int key)
{
    return 1 + (key % (limit-1));
}
