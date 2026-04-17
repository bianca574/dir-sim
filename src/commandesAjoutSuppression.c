#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataNode.h"
#include <stdbool.h>

#include "utile.h"

#include "commandesAjoutSuppression.h"

void mkdir(const char *nom)
{
    if (chercher_fils(noeudCourant, nom) != NULL)
    {
        printf("Erreur : Un dossier avec ce nom existe déjà.\n");
        exit(1);
    }
    noeud *nouveauDossier;
    nouveauDossier = malloc(sizeof(noeud));
    if (nouveauDossier == NULL)
    {
        printf("Échec d'allocation\n");
        exit(1);
    }
    nouveauDossier->est_dossier = true;
    strncpy(nouveauDossier->nom, nom, 99);
    nouveauDossier->nom[99] = '\0';
    nouveauDossier->pere = noeudCourant;
    nouveauDossier->racine = noeudCourant->racine;
    nouveauDossier->fils = NULL;

    ajouterFilsANoeudCourant(noeudCourant, nouveauDossier);
}

void touch(const char *nom)
{
    if (nom[0] == '\0')
    {
        printf("Attention le nom d'un fichier a été ajouté mais il est incorrect ! Le nom de ce fichier est vide. Changez le !!\n");
        exit(1);
    }
    if (strlen(nom) > 99)
    {
        printf("Attention le nom d'un fichier a été ajouté mais il est incorrect ! Le nom de ce fichier est trop long. Changez le !!\n");
        exit(1);
    }
    int i = 0;
    while (nom[i] != '\0')
    {
        if (!(nom[i] >= 'a' && nom[i] <= 'z') && nom[i] >= 'A' && nom[i] <= 'Z' && nom[i] >= '0' && nom[i] <= 9)
        {
            printf("Attention le nom d'un fichier a été ajouté mais il est incorrect ! Le nom de ce fichier ne contient pas que des caractères alpha-numériques. Changez le !!\n");
            exit(1);
        }
        i++;
    }
    // doublons ?
    liste_noeud *nfils_copie = noeudCourant->fils;

    while (nfils_copie != NULL)
    {
        if (strcmp(nom, nfils_copie->no->nom) == 0)
        {
            printf("Attention le nom d'un fichier a été ajouté mais il est incorrect ! Le nom de ce fichier existe déja dans ce répertoire. Changez le !!\n");
            exit(1);
        }
        nfils_copie = nfils_copie->succ;
    }

    // création fichier

    if (chercher_fils(noeudCourant, nom) != NULL)
    {
        printf("Erreur : Un fichier avec ce nom existe déjà.\n");
        exit(1);
    }
    noeud *nouveaufichier;
    nouveaufichier = malloc(sizeof(noeud));
    if (nouveaufichier == NULL)
    {
        printf("Echec d'allocation du fichier");
        exit(1);
    }
    nouveaufichier->est_dossier = false;
    strncpy(nouveaufichier->nom, nom, 99);
    nouveaufichier->nom[99] = '\0';
    nouveaufichier->pere = noeudCourant;
    nouveaufichier->racine = noeudCourant->racine;
    nouveaufichier->fils = NULL;

    ajouterFilsANoeudCourant(noeudCourant, nouveaufichier);
}

void rm(const char *chem)
{
    if (chem == NULL || strlen(chem) == 0 || strcmp(chem, "/") == 0)
    {
        printf("Erreur : Impossible de supprimer les dossiers/fichiers indiqués.\n");
        exit(1);
    }

    noeud *cible = trouver_noeud(chem);

    if (cible == NULL)
    {
        printf("Erreur : le chemin n'existe pas.\n");
        exit(1);
    }
    if (est_ancetre(cible, noeudCourant))
    {
        printf("Erreur : Impossible de supprimer les dossiers/fichiers indiqués.\n");
        exit(1);
    }
    retirer_fils(cible->pere, cible);
    free_noeud(cible);
}

void mv(const char *chem1, const char *chem2)
{
    noeud *cible = trouver_noeud(chem1);

    if (cible == NULL)
    {
        printf("Erreur : Le chemin n'existe pas.\n");
        exit(1);
    }
    char parent_dest_chem[100];
    char nouveau_nom[100];

    separer_chemin(chem2, parent_dest_chem, nouveau_nom);

    noeud *dest_parent = trouver_noeud(parent_dest_chem);

    if (dest_parent == NULL || !dest_parent->est_dossier)
    {
        printf("Erreur : La destination n'est pas un dossier valide.\n");
        exit(1);
    }
    if (est_ancetre(cible, dest_parent))
    {
        printf("Erreur : Impossible de déplacer un dossier dans lui-même ou un de ses fils.\n");
        exit(1);
    }
    if (chercher_fils(dest_parent, nouveau_nom))
    {
        printf("Erreur : Le dossier/fichier que vous voulez déplacer existe déja dans ce dossier.\n");
        exit(1);
    }
    retirer_fils(cible->pere, cible);

    strcpy(cible->nom, nouveau_nom);

    ajouterFilsANoeudCourant(dest_parent, cible);

    cible->pere = dest_parent;
}
