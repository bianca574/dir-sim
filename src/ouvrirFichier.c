#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "ouvrirFichier.h"

// aide : https://www.youtube.com/watch?v=1HjT_VUHHjI

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
    char ligne[500];    // attention taille, au plus 500 caractères en une ligne
    char commande[500]; // pour stocker le nom de la commande de "ligne"
    if (f != NULL)
    {
        while (lireLigne(f, ligne) != NULL) // si encore une ligne de disponible
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
    // lire dans le fichier f la premiere ligne (ie jusqu'à \n)
    // taille jusqu'a 499 autorisée
    char *chaine_ligne = fgets(ligne, 500, f);

    if (chaine_ligne != NULL)
    {
        int i = 0;
        int a_un_retour_a_la_ligne = -1;

        // compter caractères et pour enlever le \n à l'indice donnée
        while (ligne[i] != '\0')
        {
            if (ligne[i] == '\n')
            {
                a_un_retour_a_la_ligne = 1;
                ligne[i] = '\0';
                break;
            }
            i++;
        }

        // si la taille est >=500 , il n'y a pas de \n à cause du fget qui a pas tout lu
        if (a_un_retour_a_la_ligne == -1 && strlen(ligne) == 499)
        {
            printf("Erreur à la ligne %d : %s\n", gestionErreur.numero_ligne, ligne);
            printf("La ligne est beaucoup trop longue (>=500 caractères)\n");
            exit(1);
        }

        // enlever les \n à la fin du mot pour éviter de faire des sauts de ligne lors d'affichage
        ligne[i] = '\0';

        strcpy(gestionErreur.instruction_commande, chaine_ligne);
    }
    return chaine_ligne;
}

// ligne passée en paramètre correspond à l'entièreté de la ligne du fichier
// commande sera vide
// Après la fin de la focntion, commande aura le nom de la commande de la ligne et dans ligne, il n'y a plus le nom de la commande
void trouverCommande(char *ligne, char *commande)
{
    int i = 0;
    // on accepte espace du début
    while (ligne[i] == ' ')
    {
        i++;
    }

    // on met le nom de la commande
    int j = 0;
    while (ligne[i] != ' ' && ligne[i] != '\0' && ligne[i] != '\n')
    {
        commande[i] = ligne[i];
        i++;
        j++;
    }
    commande[j] = '\0'; // fin de la commande

    // enlever espace entre le nom de la commande et arguments dans ligne
    if (ligne[i] == ' ')
    {
        i++;
    }

    // dans ligne, on enleve le nom de la commande
    int k = 0;
    while (ligne[i] != '\0')
    {
        ligne[k] = ligne[i];
        i++;
        k++;
    }
    ligne[k] = '\0';
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