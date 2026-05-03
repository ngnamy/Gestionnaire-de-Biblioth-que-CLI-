#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../include/livre.h"
#include "../include/utilitaire.h"


int est_isbn_valide(const char *isbn, int taille) {
    int longueur = strlen(isbn);
    if (longueur != taille) {
        return 0;
    }
    for (int i = 0; i < longueur; i++) {
        if (!isdigit(isbn[i])) {
            return 0;
        }
    }
    return 1;
}

int generer_id_livre(Livre *structure_livre, int taille) {

    if (structure_livre == NULL) {
        return 1; // Si la structure est nulle, on commence à 1
    }
    int id = 1;
    for (int i = 0; i < taille; i++) {
        id++;
    }
    return id + 1;
}

void saisir_livre(Livre *livre) {

    Livre *structure_livre = NULL;
    int id = generer_id_livre(structure_livre, 0);

    printf("=== Entrer l' isbn du livre ===\n");
    printf ("1. isbn avec 10 chiffres\n");
    printf ("2. isbn avec 13 chiffres\n");
    printf("Votre choix : ");

    int choix;
    if (scanf("%d", &choix) != 1) {
        fprintf(stderr, "La saisie du choix doit être 1 ou 2\n");
        return;
    }
    vider_buffer();

    char temp_isbn[TAILLE_MAX_ISBN];

    switch (choix) {
        case 1:
            printf("Entrer l' isbn avec 10 chiffres : ");
            if (scanf("%13s", temp_isbn) != 1) {
                fprintf(stderr, "Erreur de saisie de l'isbn\n");
                return;
            }
            vider_buffer();
            if (!est_isbn_valide(temp_isbn, 10)) {
                fprintf(stderr, "Erreur : L'isbn 10 chiffres est invalide.\n");
                return;
            }
            break;
        case 2:
            printf("Entrer l' isbn avec 13 chiffres : ");
            if (scanf("%13s", temp_isbn) != 1) {
                fprintf(stderr, "Erreur de saisie de l'isbn\n");
                return;
            }
            vider_buffer();
            if (!est_isbn_valide(temp_isbn, 13)) {
                fprintf(stderr, "Erreur : L'isbn 13 chiffres est invalide.\n");
                return;
            }
            break;
        default:
            printf("Choix invalide\n");
            return;
    }

    printf("Entrer le titre du livre : ");
    if (fgets(livre->titre, TAILLE_MAX_TITRE, stdin) != NULL) {
        livre->titre[strcspn(livre->titre, "\n")] = '\0';
    }

    printf("Entrer l'auteur du livre : ");
    if (fgets(livre->auteur, TAILLE_MAX_AUTEUR, stdin) != NULL) {
        livre->auteur[strcspn(livre->auteur, "\n")] = '\0';
    }

    printf("Entrer l'année de publication du livre : ");
    int annee_publication;
    if (scanf("%d", &annee_publication) != 1) {
        fprintf(stderr, "La saisie de l'année doit être un entier positif");
        return;
    }
    vider_buffer();


    int annee_ac = annee_actuelle();
    if (annee_publication < 1450 || annee_publication > annee_ac) {
        fprintf(stderr, "L'année de publication doit être entre 1450 et %d", annee_ac);
        return;
    }

    int est_emprunte = 0;

    int id_emprunteur = -1;

    livre->id = id;
    strncpy(livre->isbn, temp_isbn, TAILLE_MAX_ISBN - 1);
    livre->isbn[TAILLE_MAX_ISBN - 1] = '\0';
    livre->annee_publication = annee_publication;
    livre->est_emprunte = est_emprunte;
    livre->id_emprunteur = id_emprunteur;
    calculer_echeance(livre->date_echeance);
}
