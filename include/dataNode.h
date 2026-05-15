#ifndef DATANODE_H
#define DATANODE_H
#include <stdbool.h>

struct noeud;
struct liste_noeud;

struct noeud
{
    bool est_dossier;
    char nom[100];
    struct noeud *pere;
    struct noeud *racine;
    struct liste_noeud *fils;
};

struct liste_noeud
{
    struct noeud *no;
    struct liste_noeud *succ;
};

typedef struct noeud noeud;
typedef struct liste_noeud liste_noeud;

// variable globale
extern noeud *noeudCourant;

#define OK 0
#define ERREUR_EXECUTION 1
#define ERREUR_PARSE 2
#define FIN_FICHIER 3

#endif
