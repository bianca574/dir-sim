#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

#include "commandesAffiche.h"
#include "commandesAjoutSuppression.h"
#include "commandesParcours.h"
#include "commandesFind.h"

#include "ouvrirFichier.h"

void parserLs(char *ligneSansCommande)
{
    //printf("%sok", ligneSansCommande);
    
    char *strToken = strtok(ligneSansCommande, " \n");

    if (strToken != NULL)
    {
        strToken = strtok(NULL, " \n");
    }
    else
    {
        ls("");
        return;
    }
    if (strToken != NULL)
    {
        erreur();
        printf("La commande ls a trop d'argument.\n");
        exit(1);
    }
    else
    {
        ls(ligneSansCommande);
    }
}

void parserPwd(char *ligneSansCommande)
{
    if (ligneSansCommande[0] == '\0' || ligneSansCommande[0] == '\n')
    {
        pwd();
    }
    else
    {
        erreur();
        printf("La commande pwd ne doit prendre aucun argument. Trop d'arguments sont donnés.\n"); // à voir si on change
        exit(1);
    }
}

void parserPrint(char *ligneSansCommande)
{
    if (ligneSansCommande[0] == '\0' || ligneSansCommande[0] == '\n')
    {
        print();
    }
    else
    {
        erreur();
        printf("La commande print ne doit prendre aucun argument. Trop d'arguments sont donnés.\n"); // à voir si on change
        exit(1);
    }
}

// aide : https://koor.fr/C/cstring/strtok.wp

void parserMkdir(char *ligneSansCommande)
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
        exit(1);
    }

    if (strToken != NULL)
    {
        erreur();
        printf("La commande mkdir a trop d'argument.\n");
        exit(1);
    }
    else
    {
        mkdir(ligneSansCommande);
    }
}

void parserTouch(char *ligneSansCommande)
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
        exit(1);
    }

    if (strToken != NULL)
    {
        erreur();
        printf("La commande touch demande un argument. Trop d'arguments sont donnés.\n");
        exit(1);
    }
    else
    {
        touch(ligneSansCommande);
    }
}

void parserCp(char *ligneSansCommande)
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
        printf("La commande cp demande deux arguments. Aucun n'est donné.\n");
        exit(1);
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
        exit(1);
    }

    if (strToken != NULL)
    {
        erreur();
        printf("La commande cp demande deux arguments. Trop d'arguments sont donnés.\n");
        exit(1);
    }
    else
    {
        cp(chem1, chem2);
    }
}

void parserCd(char *ligneSansCommande)
{
    char *strToken = strtok(ligneSansCommande, " \n");

    if (strToken == NULL)
    {
        cd("");
    }
    else
    {
        strToken = strtok(NULL, " \n");

        if (strToken != NULL)
        {
            erreur();
            printf("La commande cd demande un argument. Trop d'arguments sont donnés.\n");
            exit(1);
        }
        cd(ligneSansCommande);
    }
}

void parserRm(char *ligneSansCommande)
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
        exit(1);
    }
    if (strToken != NULL)
    {
        erreur();
        printf("La commande rm demande un argument. Trop d'arguments sont donnés.\n");
        exit(1);
    }
    else
    {
        rm(ligneSansCommande);
    }
}

void parserMv(char *ligneSansCommande)
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
        exit(1);
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
        exit(1);
    }

    if (strToken != NULL)
    {
        erreur();
        printf("La commande mv demande deux arguments. Trop d'arguments sont donnés.\n");
        exit(1);
    }
    else
    {
        mv(chem1, chem2);
    }
}

void parserFind(char *ligneSansCommande)
{
    int cap = 1;
    int argc = 0;
    char **args = malloc(cap * sizeof(char *));

    if (args == NULL)
    {
        erreur();
        printf("Erreur d'allocation mémoire.\n");
        exit(1);
    }

    char *strToken = strtok(ligneSansCommande, " \n");

    if (strToken == NULL)
    {
        free(args);
        erreur();
        printf("La commande find demande au moins un argument. Aucun n'est donné.\n");
        exit(1);
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
                exit(1);
            }
            args = temp;
        }
        args[argc++] = strToken;
        strToken = strtok(NULL, " \n");
    }
    find(argc, args);

    free(args);
}