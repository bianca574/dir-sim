#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

#include "commandesAffiche.h"
#include "commandesAjoutSuppression.h"
#include "commandesParcours.h"

void parserLs(char *ligneSansCommande){
    if (ligneSansCommande[0] == '\0') {
        ls();
    }else {
        printf("la commande ls n'a pas d'argument"); // à voir si on change
        exit(1);
    }
}
void parserPwd(char *ligneSansCommande){
    if (ligneSansCommande[0] == '\0') {
        pwd();
    }else {
        printf("la commande pwd n'a pas d'argument"); // à voir si on change
        exit(1);
    }
}