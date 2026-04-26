// aide : https://www.youtube.com/watch?v=1HjT_VUHHjI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "ouvrirFichier.h"

char *lireLigne(FILE *f, char *ligne);
void parserCommande(char *ligne, char *commande);
void trouverCommande(char *ligne, char *commande);

struct gestionErreur gestionErreur;

int ouvrirLeFichier(char *nomfichier)
{
    FILE *f;
    f = fopen(nomfichier, "r");
    if (f == NULL)
    {
        printf("Echec ouverture du fichier : le fichier %s n'existe pas\n", nomfichier);
        exit(1);
    }
    gestionErreur.numero_ligne = 1;
    char ligne[500]; // attention taille
    char commande[500];
    if (f != NULL)
    {
        ;
        while (lireLigne(f, ligne) != NULL)
        {
            parserCommande(ligne, commande);
            gestionErreur.numero_ligne += 1;
        }
    }
    fclose(f);
    return 0;
}

char *lireLigne(FILE *f, char *ligne)
{
    char *chaine_ligne = fgets(ligne, 500, f);
    if (chaine_ligne != NULL)
    {
        strcpy(gestionErreur.instruction_commande, chaine_ligne);
    }
    return chaine_ligne;
}

void trouverCommande(char *ligne, char *commande)
{
    int i = 0;
    while (ligne[i] != ' ' && ligne[i] != '\0' && ligne[i] != '\n')
    {
        commande[i] = ligne[i];
        i++;
    }
    commande[i] = '\0';

    if (ligne[i] == ' ')
    {
        i++;
    }
    // enlever espace dans ligne

    int j = 0;
    while (ligne[j] != '\0')
    {
        ligne[j] = ligne[i];
        i++;
        j++;
    }
    ligne[j] = '\0';
}

void erreur()
{
    printf("Erreur à la ligne %d : %s", gestionErreur.numero_ligne, gestionErreur.instruction_commande);
}

void parserCommande(char *ligne, char *commande)
{
    trouverCommande(ligne, commande);

    if (strcmp(commande, "cd") == 0)
    {
        parserCd(ligne);
    }
    else if (strcmp(commande, "ls") == 0)
    {
        parserLs(ligne);
    }
    else if (strcmp(commande, "print") == 0)
    {
        parserPrint(ligne);
    }
    else if (strcmp(commande, "pwd") == 0)
    {
        parserPwd(ligne);
    }
    else if (strcmp(commande, "mkdir") == 0)
    {
        parserMkdir(ligne);
    }
    else if (strcmp(commande, "touch") == 0)
    {
        parserTouch(ligne);
    }
    else if (strcmp(commande, "rm") == 0)
    {
        parserRm(ligne);
    }
    else if (strcmp(commande, "cp") == 0)
    {
        parserCp(ligne);
    }
    else if (strcmp(commande, "mv") == 0)
    {
        parserMv(ligne);
    }
    else if (strcmp(commande, "find") == 0)
    {
        parserFind(ligne);
    }
    else
    {
        erreur();
        printf("La commande %s n'existe pas \n", commande);
        exit(1);
    }
}