#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataNode.h"
#include <stdbool.h>

#include "utile.h"

// ajout à la fin de fils

void ajouterFilsANoeudCourant(noeud *nouveauFils, noeud *pere)
{
    if (pere->fils == NULL)
    {
        pere->fils = malloc(sizeof(liste_noeud));
        pere->fils->no = nouveauFils;
        pere->fils->succ = NULL;
    }
    else
    {
        liste_noeud *copie = pere->fils;
        while (copie->succ != NULL)
        {
            copie = copie->succ;
        }
        copie->succ = malloc(sizeof(liste_noeud));
        copie->succ->no = nouveauFils;
        copie->succ->succ = NULL;
    }
    nouveauFils->pere = pere;
}

void free_noeud(noeud *noeud)
{
    if (noeud == NULL)
    {
        return;
    }
    liste_noeud *copie = noeud->fils;
    while (copie != NULL)
    {
        liste_noeud *suivant = copie->succ;
        free_noeud(copie->no);
        free(copie);
        copie = suivant;
    }
    free(noeud);
}

noeud *trouver_noeud(const char *chem)
{
    if (chem == NULL || strlen(chem) == 0)
    {
        return NULL;
    }

    char *copie_chem = malloc((strlen(chem) + 1) * sizeof(char));

    if (copie_chem == NULL)
    {
        printf( "Erreur d'allocation mémoire.\n");
        exit(1);
    }

    strcpy(copie_chem, chem);

    char *chemin = strtok(copie_chem, "/");

    noeud *actuel = chem[0] == '/' ? noeudCourant->racine : noeudCourant;

    noeud *trouve = actuel;

    while (chemin != NULL)
    {
        if (strcmp(chemin, "..") == 0)
        {
            trouve = actuel->pere;
        }
        else if (strcmp(chemin, ".") == 0)
        {
            trouve = actuel;
        }
        else
        {
            trouve = chercher_fils(actuel, chemin);
        }
        if (trouve == NULL)
        {
            free(copie_chem);
            return NULL;
        }

        chemin = strtok(NULL, "/");

        if (chemin != NULL)
        {
            if (!trouve->est_dossier)
            {
                free(copie_chem);
                return NULL;
            }
            actuel = trouve;
        }
    }
    free(copie_chem);
    return trouve;
}

//alloue de la mémoire dans chemin etv nom
void separer_chemin(const char *chem2, char **chemin, char **nom)
{
    char *copie = malloc(strlen(chem2) + 1);
    if (copie == NULL) {
        printf("Erreur de malloc");
        exit(1);
    }

    strcpy(copie, chem2);

    char *slash = strrchr(copie, '/');

    if (slash == NULL) { // cas pour "td1"
        
        *nom = malloc(strlen(copie) + 1);
        *chemin = malloc(2*sizeof(char)); 
        
        if (*nom == NULL || *chemin == NULL) {
            printf("Erreur de malloc");
            exit(1);
        }
        strcpy(*nom, copie);
        strcpy(*chemin, ".");

    } else {
        *nom = malloc(strlen(slash + 1) + 1);
        if (*nom == NULL) 
        {
            printf("Erreur de malloc");
            exit(1);
        }
        strcpy(*nom, slash + 1);

        if (slash == copie) { // slash au début
            *chemin = malloc(2*sizeof(char));
            if (*chemin == NULL) 
            {
                printf("Erreur de malloc");
                exit(1);
            }
            strcpy(*chemin, "/");
        } else {
            *slash = '\0';
            *chemin = malloc(strlen(copie) + 1);
            if (*chemin ==NULL) 
            {
                printf("Erreur de malloc");
                exit(1);
            }
            strcpy(*chemin, copie);
        }
    }

    free(copie);
}

bool est_ancetre(noeud *potentiel_ancetre, noeud *depart)
{
    noeud *temp = depart;

    while (temp != temp->racine)
    {
        if (temp == potentiel_ancetre)
        {
            return true;
        }
        temp = temp->pere;
    }
    return temp == potentiel_ancetre;
}

noeud *chercher_fils(noeud *parent, const char *nom)
{
    if (parent == NULL)
    {
        return NULL;
    }

    liste_noeud *liste = parent->fils;

    while (liste != NULL)
    {
        if (strcmp(liste->no->nom, nom) == 0)
        {
            return liste->no;
        }
        liste = liste->succ;
    }
    return NULL;
}

void retirer_fils(noeud *parent, noeud *cible)
{
    if (parent == NULL || parent->fils == NULL || cible == NULL)
    {
        return;
    }

    liste_noeud *courant = parent->fils;
    liste_noeud *precedent = NULL;

    while (courant != NULL && courant->no != cible)
    {
        precedent = courant;
        courant = courant->succ;
    }
    if (courant != NULL)
    {
        if (precedent == NULL) // si c'est le premier fils de la liste
        {
            parent->fils = courant->succ;
        }
        else
        {
            precedent->succ = courant->succ;
        }
        free(courant);
    }
}
