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
        // enlever les \n à la fin du mot pour éviter de faire des sauts de ligne lors d'affichage
        int i = 0;
        while (ligne[i] != '\0')
        {
            if (ligne[i] == '\n')
            {
                ligne[i] = '\0';
                break;
            }
            i++;
        }
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
    printf("Erreur à la ligne %d : %s\n", gestionErreur.numero_ligne, gestionErreur.instruction_commande);
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
    else if (strcmp(commande, "") == 0 || strcmp(commande, "#") == 0) // les lignes vides et les commentaires sont ignorés
    {
    }
    else
    {
        erreur();
        printf("La commande %s n'existe pas \n", commande);
        exit(1);
    }
}

void lancerTerminal()
{
    char ligne[500];
    char commande[500];

    printf("DirSim : Terminal interactif\n");
    printf("Commandes : cd, ls, pwd, mkdir, print, touch, rm, cp, mv, find [-d|-f] [-s mot] [-r regex]\n");
    printf("Taper 'exit' pour quitter.\n");

    gestionErreur.numero_ligne = 0; // compteur des lignes initialisé à 0

    while (1)
    {
        printf("dirsim:");
        if (noeudCourant == noeudCourant->racine)
        {
            printf("/");
        }
        else // on reconstruit le chemin à partir de où on est
        {
            noeud *pile[200];
            int n = 0;
            noeud *tmp = noeudCourant;
            while (tmp != tmp->racine && n < 200)
            {
                pile[n++] = tmp;
                tmp = tmp->pere;
            }
            for (int i = n - 1; i >= 0; i--)
            {
                printf("/%s", pile[i]->nom);
            }
        }
        printf("$ ");
        fflush(stdout); // force l'affichage immédiat du prompt - ce qui s'affiche avant que l'utilisateur tape

        if (fgets(ligne, sizeof(ligne), stdin) == NULL)
        {
            printf("\n");
            break;
        }
        // enlever le \n final
        int i = 0;
        while (ligne[i] != '\0')
        {
            if (ligne[i] == '\n')
            {
                ligne[i] = '\0';
                break;
            }
            i++;
        }
        if (strcmp(ligne, "exit") == 0)
        {
            printf("A bientôt!\n");
            break;
        }
        if (ligne[0] == '\0')
        {
            continue; // pour ne pas incrémenter le compteur des lignes
        }
        strcpy(gestionErreur.instruction_commande, ligne);
        gestionErreur.numero_ligne++;

        parserCommande(ligne, commande);
    }
}