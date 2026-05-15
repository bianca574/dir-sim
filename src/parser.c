#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

#include "commandesAffiche.h"
#include "commandesAjoutSuppression.h"
#include "commandesParcours.h"
#include "commandesFind.h"

#include "ouvrirFichier.h"


// aide : https://koor.fr/C/cstring/strtok.wp


int parserLs(char *ligneSansCommande)
{
    //strtok renvoie le "mot" jusqu'au premier espace ou \n
    char *strToken = strtok(ligneSansCommande, " \n");

    if (strToken != NULL)
    {
        // on regarde s'il y a un autre argument après
        strToken = strtok(NULL, " \n");
    }
    else
    {
        // pas d'argument
        if (ls("") != OK){
            return ERREUR_EXECUTION;
        }
        return OK;
    }
    // il y a un 2eme argument
    if (strToken != NULL)
    {
        erreur();
        printf("La commande ls a trop d'argument.\n");
        return ERREUR_PARSE;
    }
    else
    {
        if (ls(ligneSansCommande) != OK){
            return ERREUR_EXECUTION;
        }
    }
    return OK;
}

int parserPwd(char *ligneSansCommande)
{
    if (ligneSansCommande[0] == '\0' || ligneSansCommande[0] == '\n')
    {
        pwd();
    }
    else
    {
        erreur();
        printf("La commande pwd ne doit prendre aucun argument. Trop d'arguments sont donnés.\n"); // à voir si on change
        return ERREUR_PARSE;
    }
    return OK;
}

int parserPrint(char *ligneSansCommande)
{
    if (ligneSansCommande[0] == '\0' || ligneSansCommande[0] == '\n')
    {
        print();
    }
    else
    {
        erreur();
        printf("La commande print ne doit prendre aucun argument. Trop d'arguments sont donnés.\n"); // à voir si on change
        return ERREUR_PARSE;;
    }
    return OK;
}

int parserMkdir(char *ligneSansCommande)
{

    char *strToken = strtok(ligneSansCommande, " \n");

    if (strToken != NULL)
    {
        strToken = strtok(NULL, " \n");
    }
    else
    {
        erreur();
        printf("La commande mkdir demande un argument. Aucun n'est donné.\n");
        return ERREUR_PARSE;
    }

    if (strToken != NULL)
    {
        erreur();
        printf("La commande mkdir a trop d'argument.\n");
        return ERREUR_PARSE;
    }
    else
    {
        if (mkdir(ligneSansCommande) != OK){
            return ERREUR_PARSE;
        }
    }
    return OK;
}

int parserTouch(char *ligneSansCommande)
{
    char *strToken = strtok(ligneSansCommande, " \n");

    if (strToken != NULL)
    {
        strToken = strtok(NULL, " \n");
    }
    else
    {
        erreur();
        printf("La commande touch demande un argument. Aucun n'est donné.\n");
        return ERREUR_PARSE;
    }

    if (strToken != NULL)
    {
        erreur();
        printf("La commande touch demande un argument. Trop d'arguments sont donnés.\n");
        return ERREUR_PARSE;;
    }
    else
    {
        if (touch(ligneSansCommande) != OK){
            return ERREUR_EXECUTION;
        }
    }
    return OK;
}

int parserCp(char *ligneSansCommande)
{
    char *strToken = strtok(ligneSansCommande, " \n");
    char *chem1 = NULL;
    char *chem2 = NULL;

    if (strToken != NULL)
    {
        chem1 = strToken; // on garde l'information
        strToken = strtok(NULL, " \n");
    }
    else
    {
        erreur();
        printf("La commande cp demande deux arguments. Aucun n'est donné.\n");
        return ERREUR_PARSE;
    }

    if (strToken != NULL)
    {
        chem2 = strToken;
        strToken = strtok(NULL, " \n");
    }
    else
    {
        erreur();
        printf("La commande cp demande deux arguments. Un seul est donné.\n");
        return ERREUR_PARSE;
    }

    if (strToken != NULL)
    {
        erreur();
        printf("La commande cp demande deux arguments. Trop d'arguments sont donnés.\n");
        return ERREUR_PARSE;
    }
    else
    {
        if (cp(chem1, chem2) != OK){
            return ERREUR_EXECUTION;
        }
    }
    return OK;
}

int parserCd(char *ligneSansCommande)
{
    char *strToken = strtok(ligneSansCommande, " \n");

    if (strToken == NULL)
    {
        if (cd("") != OK){
            return ERREUR_EXECUTION;
        }
    }
    else
    {
        strToken = strtok(NULL, " \n");

        if (strToken != NULL)
        {
            erreur();
            printf("La commande cd demande un argument. Trop d'arguments sont donnés.\n");
            return ERREUR_PARSE;
        }
        if (cd(ligneSansCommande) != OK){
            return ERREUR_EXECUTION;
        }
    }
    return OK;
}

int parserRm(char *ligneSansCommande)
{
    char *strToken = strtok(ligneSansCommande, " \n");

    if (strToken != NULL)
    {
        strToken = strtok(NULL, " \n");
    }
    else
    {
        erreur();
        printf("La commande rm demande un argument. Aucun n'est donné.\n");
        return ERREUR_PARSE;
    }
    if (strToken != NULL)
    {
        erreur();
        printf("La commande rm demande un argument. Trop d'arguments sont donnés.\n");
        return ERREUR_PARSE;
    }
    else
    {
        if (rm(ligneSansCommande)!= OK){
            return ERREUR_EXECUTION;
        }
    }
    return OK;
}

int parserMv(char *ligneSansCommande)
{
    char *strToken = strtok(ligneSansCommande, " \n");
    char *chem1 = NULL;
    char *chem2 = NULL;

    if (strToken != NULL)
    {
        chem1 = strToken;
        strToken = strtok(NULL, " \n");
    }
    else
    {
        erreur();
        printf("La commande mv demande deux arguments. Aucun n'est donné.\n");
        return ERREUR_PARSE;
    }

    if (strToken != NULL)
    {
        chem2 = strToken;
        strToken = strtok(NULL, " \n");
    }
    else
    {
        erreur();
        printf("La commande mv demande deux arguments. Un seul est donné.\n");
        return ERREUR_PARSE;
    }

    if (strToken != NULL)
    {
        erreur();
        printf("La commande mv demande deux arguments. Trop d'arguments sont donnés.\n");
        return ERREUR_PARSE;
    }
    else
    {
        if (mv(chem1, chem2) != OK){
            return ERREUR_EXECUTION;
        }
    }
    return OK;
}

int parserFind(char *ligneSansCommande)
{
    int cap = 1;
    int argc = 0;
    char **args = malloc(cap * sizeof(char *));

    if (args == NULL)
    {
        erreur();
        printf("Erreur d'allocation mémoire.\n");
        return ERREUR_PARSE;
    }

    char *strToken = strtok(ligneSansCommande, " \n");

    if (strToken == NULL)
    {
        free(args);
        erreur();
        printf("La commande find demande au moins un argument. Aucun n'est donné.\n");
        return ERREUR_PARSE;
    }

    while (strToken != NULL)
    {
        if (argc >= cap)
        {
            cap *= 2;
            char **temp = realloc(args, cap * sizeof(char *));
            if (temp == NULL)
            {
                free(args);
                erreur();
                printf("Erreur de réallocation.\n");
                return ERREUR_PARSE;
            }
            args = temp;
        }
        args[argc++] = strToken;
        strToken = strtok(NULL, " \n");
    }
    if (find(argc, args) != OK){
        return ERREUR_EXECUTION;
    }

    free(args);
    return OK;
}