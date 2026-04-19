#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "commandesAffiche.h"
#include "commandesAjoutSuppression.h"
#include "commandesParcours.h"
#include "utile.h"

noeud *noeudCourant = NULL;

void init()
{
    noeudCourant = malloc(sizeof(noeud));
    if (noeudCourant == NULL)
    {
        printf("Échec d'allocation\n");
        exit(1);
    }
    noeudCourant->est_dossier = true;
    noeudCourant->nom[0] = '\0';
    noeudCourant->pere = noeudCourant;
    noeudCourant->racine = noeudCourant;
    noeudCourant->fils = NULL;
}

int main()
{
    init();
    printf("Début :\n");
    ls();

    printf("\nAjout d'un dossier:\n");
    mkdir("Cours");
    mkdir("Td");
    touch("edt");

    cd("Cours");
    mkdir("ProjetC");
    mkdir("Anglais");

    cd("..");
    cd("Td");
    touch("td1");
    touch("td2");

    cd("../Cours/ProjetC");
    mkdir("ok");
    cd("ok");
    
    cd ("../../");
    ls();

    pwd();

    print();

    //test rm
    printf("\nTest RM\n");
    //cd("/");
    //rm("edt");
    print();

    printf("\nTest MV\n");
    //mv("/Cours/ProjetC/ok", "/OkAtRoot");
    print();

    // printf("\n--- Test RM soi-même ---\n");
    // cd("/");
    // cd("/Cours/ProjetC");
    // rm("/Cours/ProjetC");

    // printf("\n--- Test RM ancêtre ---\n");
    // cd("/");
    // cd("/Cours/ProjetC");
    // rm("/Cours");

    printf("\nTest RM dossier\n");
    //cd("/");
    //rm("Td");

    //tesp pwd
    pwd();
    print();

    // test cp
    cp("ProjetC", "Anglais/nouveau");
    printf("ajout cp: \n");
    print();

    free_noeud(noeudCourant->racine);

    return 0;
}
