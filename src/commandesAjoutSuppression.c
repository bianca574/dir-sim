#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataNode.h"
#include <stdbool.h>

#include "utile.h"

#include "commandesAjoutSuppression.h"
#include "ouvrirFichier.h"

// utile seulement pour touch et mkdir

void cheminAbsoluPreparartionCreation(const char *nom, char **chemin, char **dernierNomDossier, noeud **pereDuDossier){

    //découpe le chemin pour trouver le pere après
    separer_chemin(nom, chemin, dernierNomDossier);

    if (chercher_fils(noeudCourant, *dernierNomDossier) != NULL)
    {
        erreur();
        printf("%s existe déjà.\n", *dernierNomDossier);
        exit(1);
    }
    
    *pereDuDossier=  trouver_noeud(*chemin);
     if (*pereDuDossier == NULL){
        erreur();
        printf("Erreur : le dossier %s n'existe pas\n", *chemin);
        exit(1);
    }


}
// fonctionne pour chemin absolu et relatif
void mkdir(const char *nom)
{   
    char *chemin;
    char *dernierNomDossier;
    noeud *pereDuDossier;
    cheminAbsoluPreparartionCreation(nom, &chemin, &dernierNomDossier, &pereDuDossier);

    noeud *nouveauDossier;
    nouveauDossier = malloc(sizeof(noeud));
    if (nouveauDossier == NULL)
    {
        printf("Échec d'allocation\n");
        exit(1);
    }
    nouveauDossier->est_dossier = true;
    strncpy(nouveauDossier->nom, dernierNomDossier, 99);
    nouveauDossier->nom[99] = '\0';
    nouveauDossier->pere = pereDuDossier;
    nouveauDossier->racine = noeudCourant->racine;
    nouveauDossier->fils = NULL;

    ajouterFilsANoeudCourant(nouveauDossier, pereDuDossier);

    free(chemin);
    free(dernierNomDossier);
}

void nomInvalide(const char *nom)
{
    if (nom[0] == '\0')
    {
        erreur();
        printf("Attention le nom d'un fichier a été ajouté mais il est incorrect ! Le nom de ce fichier est vide. Changez le !!\n");
        exit(1);
    }
    if (strlen(nom) > 99)
    {
        erreur();
        printf("Attention le nom d'un fichier a été ajouté mais il est incorrect ! Le nom de ce fichier est trop long. Changez le !!\n");
        exit(1);
    }
    int i = 0;
    while (nom[i] != '\0')
    {
        if (!(nom[i] >= 'a' && nom[i] <= 'z') && !(nom[i] >= 'A' && nom[i] <= 'Z') && !(nom[i] >= '0' && nom[i] <= '9'))
        {
            erreur();
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
            erreur();
            printf("Attention le nom d'un fichier a été ajouté mais il est incorrect ! Le nom de ce fichier existe déja dans ce répertoire. Changez le !!\n");
            exit(1);
        }
        nfils_copie = nfils_copie->succ;
    }
}

// fonctionne pour chemin absolu et relatif
void touch(const char *nom)
{
    char *chemin;
    char *dernierNomFichier;
    noeud *pereDuDossier;
    cheminAbsoluPreparartionCreation(nom, &chemin, &dernierNomFichier, &pereDuDossier);

    nomInvalide(dernierNomFichier);

    noeud *nouveaufichier;
    nouveaufichier = malloc(sizeof(noeud));
    if (nouveaufichier == NULL)
    {
        erreur();
        printf("Echec d'allocation du fichier");
        exit(1);
    }
    nouveaufichier->est_dossier = false;
    strncpy(nouveaufichier->nom, dernierNomFichier, 99);
    nouveaufichier->nom[99] = '\0';
    nouveaufichier->pere = pereDuDossier;
    nouveaufichier->racine = noeudCourant->racine;
    nouveaufichier->fils = NULL;

    ajouterFilsANoeudCourant(nouveaufichier, pereDuDossier);

    free(dernierNomFichier);
    free(chemin);
}

void rm(const char *chem)
{
    if (chem == NULL || strlen(chem) == 0 || strcmp(chem, "/") == 0)
    {
        erreur();
        printf("Impossible de supprimer %s.\n", chem);
        exit(1);
    }

    noeud *cible = trouver_noeud(chem);

    if (cible == NULL)
    {
        erreur();
        printf("le chemin %s n'existe pas.\n", chem);
        exit(1);
    }

    if (est_ancetre(cible, noeudCourant))
    {
        erreur();
        printf("Impossible de supprimer %s. \n", chem);
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
        erreur();
        printf("Le chemin %s n'existe pas.\n", chem1);
        exit(1);
    }
    char *parent_dest_chem;
    char *nouveau_nom;

    noeud *chem2_noeud = trouver_noeud(chem2);

    if (chem2_noeud != NULL && chem2_noeud->est_dossier)
    {
        parent_dest_chem = NULL;
        nouveau_nom = malloc(strlen(cible->nom) + 1);
        if (nouveau_nom == NULL)
        {
            printf("Erreur malloc.\n");
            exit(1);
        }
        strcpy(nouveau_nom, cible->nom);
    }
    else
    {
        separer_chemin(chem2, &parent_dest_chem, &nouveau_nom);
        chem2_noeud = trouver_noeud(parent_dest_chem);
    }

    noeud *dest_parent = chem2_noeud;

    if (dest_parent == NULL || !dest_parent->est_dossier)
    {
        erreur();
        printf("La destination %s n'est pas un dossier valide.\n", chem2);
        free(parent_dest_chem);
        free(nouveau_nom);
        exit(1);
    }
    if (est_ancetre(cible, dest_parent))
    {
        erreur();
        printf("Impossible de déplacer un dossier dans lui-même ou un de ses fils.\n");
        free(parent_dest_chem);
        free(nouveau_nom);
        exit(1);
    }
    if (chercher_fils(dest_parent, nouveau_nom))
    {
        erreur();
        printf("%s existe déja dans ce dossier.\n", nouveau_nom);
        free(parent_dest_chem);
        free(nouveau_nom);
        exit(1);
    }
    retirer_fils(cible->pere, cible);

    strcpy(cible->nom, nouveau_nom);

    ajouterFilsANoeudCourant(cible, dest_parent);

    cible->pere = dest_parent;

    free(parent_dest_chem);
    free(nouveau_nom);
}

// fonction auxiliaire pour copier le no_a_cp au pere
noeud *cp_noeud(noeud *no_a_cp, noeud *pere)
{
    noeud *copie_de_no;
    copie_de_no = malloc(sizeof(noeud));
    if (copie_de_no == NULL)
    {
        printf("Erreur de malloc");
        exit(1);
    }
    copie_de_no->est_dossier = no_a_cp->est_dossier;
    copie_de_no->racine = no_a_cp->racine;
    strcpy(copie_de_no->nom, no_a_cp->nom);
    ajouterFilsANoeudCourant(copie_de_no, pere);

    copie_de_no->fils = NULL;
    liste_noeud *copie_des_fils = no_a_cp->fils;

    while (copie_des_fils != NULL)
    {
        cp_noeud(copie_des_fils->no, copie_de_no);
        copie_des_fils = copie_des_fils->succ;
    }
    return copie_de_no;
}

void verifier_doublon(noeud *dest, const char *nom)
{
    liste_noeud *f = dest->fils;

    while (f != NULL)
    {
        if (strcmp(f->no->nom, nom) == 0)
        {
            erreur();
            printf("Attention %s existe déjà dans le dossier.\n", nom);
            exit(1);
        }
        f = f->succ;
    }
}

noeud *verifier_destination(const char *chemin)
{
    noeud *dest = trouver_noeud(chemin);

    if (dest == NULL || !dest->est_dossier)
    {
        erreur();
        printf("Attention le dernier nom du chemin %s n'est pas correct (pas un dossier ou n'existe pas)\n", chemin);
        exit(1);
    }

    return dest;
}
void verifier_sous_arbre(noeud *depart, noeud *dest)
{
    noeud *tmp = dest;

    while (tmp != tmp->pere)
    {
        if (tmp == depart)
        {
            erreur();
            printf("Le chemin se trouve dans le sous-arbre.\n");
            exit(1);
        }
        tmp = tmp->pere;
    }
}

void cp(const char *chem1, const char *chem2)
{
    noeud *chemin1 = trouver_noeud(chem1);
    if (chemin1 == NULL)
    {
        erreur();
        printf("Le chemin %s n'est pas correct.", chem1);
        exit(1);
    }

    char *chemin;
    char *nom;

    // dans nom = nom du dossier/fichier
    // chemin = s'arrête au père
    separer_chemin(chem2, &chemin, &nom);

    noeud *dest = verifier_destination(chemin);
    verifier_doublon(dest, nom);
    verifier_sous_arbre(chemin1, dest);

    noeud *copie = cp_noeud(chemin1, dest);
    strcpy(copie->nom, nom);

    free(chemin);
    free(nom);
}
