#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/livre.h"
#include "../include/membres.h"

int main () {
    Membre *nouveau_membre = NULL;
    nouveau_membre = (Membre *)malloc(sizeof(Membre));

    if (nouveau_membre == NULL) {
        fprintf(stderr, "Echec de l'allocation mémoire pour le nouveau membre");
        return 1;
    }
    saisir_membre (nouveau_membre, 2);
    afficher_membre (nouveau_membre);
    return 0;
}