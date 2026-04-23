#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

#include "commandesAffiche.h"
#include "commandesAjoutSuppression.h"
#include "commandesParcours.h"

void parserLs(char *ligneSansCommande){
    //printf("%sok", ligneSansCommande);
    if (ligneSansCommande[0] == '\0' || ligneSansCommande[0] == '\n') {
        ls();
    }else {
        printf("la commande ls n'a pas d'argument\n"); // à voir si on change
        exit(1);
    }
}
void parserPwd(char *ligneSansCommande){
    //printf("%s", ligneSansCommande);
    if (ligneSansCommande[0] == '\0' || ligneSansCommande[0] == '\n') {
        pwd();
    }else {
        printf("la commande pwd n'a pas d'argument\n"); // à voir si on change
        exit(1);
    }
}

void parserPrint(char *ligneSansCommande){
    if (ligneSansCommande[0] == '\0' || ligneSansCommande[0] == '\n') {
        print();
    }else {
        printf("la commande print n'a pas d'argument\n"); // à voir si on change
        exit(1);
    }
}


// aide : https://koor.fr/C/cstring/strtok.wp

void parserMkdir(char *ligneSansCommande){
    
    char * strToken = strtok(ligneSansCommande, " \n");

    if (strToken != NULL){
        strToken = strtok(NULL, " \n");
    }

    if (strToken != NULL){
        printf("la commande mkdir a trop d'argument.\n");
        exit(1);
    }
    else { 
        mkdir(ligneSansCommande);
    }
}

void parserTouch(char *ligneSansCommande){
    
    char * strToken = strtok(ligneSansCommande, " \n");

    if (strToken != NULL){
        strToken = strtok(NULL, " \n");
    }

    if (strToken != NULL){
        printf("la commande touch a trop d'argument.\n");
        exit(1);
    }
    else { 
        touch(ligneSansCommande);
    }
}


void parserCp(char *ligneSansCommande){
    char * strToken = strtok(ligneSansCommande, " \n");
    char *chem1=NULL;
    char*chem2=NULL;

    if (strToken != NULL){
        chem1 =strToken;
        strToken = strtok(NULL, " \n");
    }

    if (strToken != NULL){
        chem2 = strToken;
        strToken = strtok(NULL, " \n");
    }

    if (strToken != NULL){
        printf("la commande cp a trop d'argument.\n");
        exit(1);
    }else {
        cp(chem1, chem2);
    }
}