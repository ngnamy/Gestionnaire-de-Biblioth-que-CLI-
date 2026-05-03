#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/livre.h"

int main () {
    Livre *nouveau_livre = NULL;
    nouveau_livre = (Livre *)malloc(sizeof(Livre));

    if (nouveau_livre == NULL) {
        fprintf(stderr, "Echec de l'allocation mémoire pour le nouveau livre");
        return 1;
    }

    saisir_livre (nouveau_livre);

    printf("=== Les informations liées au nouveau livre ===");

    printf("ID: %d\n"
            "Isbn: %s\n"
            "Titre: %s\n"
            "Auteur: %s\n"
            "Année publication: %d\n"
            "Est emprunté: %d\n"
            "Id emprunteur: %d\n"
            "Date échéance: %s",
            nouveau_livre->id,
            nouveau_livre->isbn,
            nouveau_livre->titre,
            nouveau_livre->auteur,
            nouveau_livre->annee_publication,
            nouveau_livre->est_emprunte,
            nouveau_livre->id_emprunteur,
            nouveau_livre->date_echeance    
        );

    return 0;
}