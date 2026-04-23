// aide : https://www.youtube.com/watch?v=1HjT_VUHHjI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "ouvrirFichier.h"

char *lireLigne(FILE *f, char *ligne);
void parserCommande(char *ligne, char *commande);
void trouverCommande(char *ligne, char *commande);


int ouvrirLeFichier(){
    FILE *f;
    f = fopen("monfichier.txt", "r");
    if (f== NULL){
        printf("echec ouverture du fichier");
        exit(1);
    } 
    char ligne[500]; // attention taille
   char commande [500];
    if (f!= NULL){;
        while (lireLigne(f, ligne) != NULL){
            parserCommande(ligne, commande);
        } 
        
    }   
    fclose(f);
    return 0;

}


char *lireLigne(FILE *f, char *ligne){
   return fgets(ligne, 20, f);
}


void trouverCommande(char *ligne, char *commande){
    int i=0;
    while (ligne[i] != ' ' && ligne[i] != '\0' && ligne[i] != '\n'){
        commande[i] = ligne[i];
        i++;
    }
    commande[i] ='\0';

    i+=1; // enlever espace dans ligne

    int j =0;
    while (ligne[j] != '\0'){
        ligne[j]= ligne[i];
        i++;
        j++;
    }
    ligne[j] = '\0';
    
}

void parserCommande(char *ligne, char *commande){
    trouverCommande(ligne, commande);

    if (strcmp(commande, "cd") == 0){
        
    }else if (strcmp(commande, "ls") == 0){
        parserLs(ligne);
    }else if(strcmp(commande, "print") == 0){

    }else if(strcmp(commande, "pwd") == 0){
        parserPwd(ligne);
    }else if(strcmp(commande, "mkdir") == 0){
        
    }else if(strcmp(commande, "touch") == 0){
        
    }else if(strcmp(commande, "rm") == 0){
        
    }else if(strcmp(commande, "cp") == 0){
        
    }else if(strcmp(commande, "mv") == 0){
        
    }else if(strcmp(commande, "find") == 0){
        
    }else {
        printf("la commande n'existe pas");
        exit(1);
    }   
}