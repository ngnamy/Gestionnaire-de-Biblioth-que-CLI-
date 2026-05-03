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

void saisir_livre(Livre *livre) {

    printf ("Entrer l' identifiant du livre : ");
    int id;
    if (scanf("%d", &id) != 1) {
        fprintf(stderr, "La saisie de l' identifiant doit être un entier positif");
        return;
    }
    getchar();

    printf("=== Entrer l' isbn du livre ===\n");
    printf ("1. isbn avec 10 chiffres : \n");
    printf ("2. isbn avec 13 chiffres : \n");
    printf("Votre choix : ");

    int choix;
    if (scanf("%d", &choix) != 1) {
        fprintf(stderr, "La saisie du choix doit être un entier positif soit 1 ou ");
        return;
    }
    getchar();


    // validation de l' isbn
    char *isbn = (char *)malloc(14 * sizeof(char));
    if (isbn == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour l' isbn");
        return;
    }

    switch (choix) {
        case 1:
            printf("Entrer l' isbn avec 10 chiffres : ");
            char *isbn_10 = realloc(isbn, 11 * sizeof(char));
            if (isbn_10 == NULL) {
                fprintf(stderr, "Erreur d'allocation mémoire pour l' isbn");
                return;
            }
            isbn = isbn_10;
            if (scanf("%s", isbn) != 1) {
                fprintf(stderr, "La saisie de l' isbn doit être des caractère d'entier compris de taille 10 (avant 2007) ou  13 (depuis 2007)");
                return;
            }
            getchar();


            if (!est_isbn_valide(isbn, 10)) {
                fprintf(stderr, "L' isbn doit être valide (*********X ou **********X) pour les années avant 2007 et ************* pour les années après 2007, avec * uniquement des chiffres de 0 à 9");
                return;
            }
            break;
        case 2:
            printf("Entrer l' isbn avec 13 chiffres : ");
            char *isbn_13 = realloc(isbn, 14 * sizeof(char));
            if (isbn_13 == NULL) {
                fprintf(stderr, "Erreur d'allocation mémoire pour l' isbn");
                return;
            }
            isbn = isbn_13;
            if (scanf("%s", isbn) != 1) {
                fprintf(stderr, "La saisie de l' isbn doit être des caractère d'entier compris de taille 10 (avant 2007) ou  13 (depuis 2007)");
                return;
            }
            getchar();


            if (!est_isbn_valide(isbn, 13)) {
                fprintf(stderr, "L' isbn doit être valide (*********X ou **********X) pour les années avant 2007 et ************* pour les années après 2007, avec * uniquement des chiffres de 0 à 9");
                return;
            }
            break;
        default:
            printf("Choix invalide");
            return;
    }

    printf("Entrer le titre du livre : ");
    char titre[TAILLE_MAX_TITRE];
    if (scanf("%s", titre) != 1) {
        fprintf(stderr, "La saisie du titre doit être des caractères alphabétiques");
        return;
    }
    getchar();


    printf("Entrer l'auteur du livre : ");
    char auteur[TAILLE_MAX_AUTEUR];
    if (scanf("%s", auteur) != 1) {
        fprintf(stderr, "La saisie de l'auteur doit être des caractères alphabétiques");
        return;
    }
    getchar();


    printf("Entrer l'année de publication du livre : ");
    int annee;
    if (scanf("%d", &annee) != 1) {
        fprintf(stderr, "La saisie de l'année doit être un entier positif");
        return;
    }
    getchar();


    int annee_ac = annee_actuelle();
    if (annee < 1450 || annee > annee_ac) {
        fprintf(stderr, "L'année de publication doit être entre 1450 et %d", annee_ac);
        return;
    }

    int est_emprunte = 0;

    int id_emprunteur = -1;

    char date_echeance[TAILLE_MAX_DATE];
    calculer_echeance (date_echeance);

    livre->id = id;

    strncpy(livre->isbn, isbn, sizeof(&isbn));
    livre->isbn[sizeof(isbn) - 1] = '\0';

    strncpy(livre->titre, titre, sizeof(titre));
    livre->titre[sizeof(titre) - 1] = '\0';

    strncpy(livre->auteur, titre, sizeof(auteur));
    livre->auteur[sizeof(auteur) - 1] = '\0';

    livre->annee_publication = annee;

    livre->est_emprunte = est_emprunte;

    livre->id_emprunteur = id_emprunteur;

    strncpy(livre->date_echeance, date_echeance, sizeof(date_echeance));
    livre->date_echeance[sizeof(date_echeance) - 1] = '\0';
}
