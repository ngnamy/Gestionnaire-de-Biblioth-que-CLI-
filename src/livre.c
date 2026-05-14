#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../include/livre.h"
#include "../include/utilitaire.h"


int est_isbn_valide(const char *isbn, int type) {
    int len = strlen(isbn);
    if (len != type) return 0;

    if (type == 10) {
        int somme = 0;
        for (int i = 0; i < 9; i++) {
            if (!isdigit(isbn[i])) return 0;
            somme += (isbn[i] - '0') * (10 - i);
        }
        // Le 10ème caractère peut être un chiffre ou 'X'
        if (isbn[9] == 'X' || isbn[9] == 'x') {
            somme += 10;
        } else if (isdigit(isbn[9])) {
            somme += (isbn[9] - '0');
        } else {
            return 0;
        }
        return (somme % 11 == 0);
    } 
    
    if (type == 13) {
        int somme = 0;
        for (int i = 0; i < 13; i++) {
            if (!isdigit(isbn[i])) return 0;
            int chiffre = isbn[i] - '0';
            // Coefficient 1 pour les positions paires, 3 pour les impaires
            somme += (i % 2 == 0) ? chiffre : chiffre * 3;
        }
        return (somme % 10 == 0);
    }

    return 0;
}

void saisir_livre(Livre *livre, int prochain_id) {
    int choix;
    int annee_pub;
    int annee_ac = annee_actuelle();

    // Initialisation immédiate de l'ID
    livre->id = prochain_id;

    // --- 1. Choix du type d'ISBN ---
    do {
        printf("\n=== Type d'ISBN ===\n");
        printf("1. ISBN-10\n2. ISBN-13\nVotre choix : ");
        
        if (scanf("%d", &choix) != 1) {
            fprintf(stderr, "Erreur : Saisie invalide. Veuillez entrer 1 ou 2.\n");
            vider_buffer();
            continue; 
        }
        vider_buffer();

        if (choix < 1 || choix > 2) {
            printf("Choix hors limites. Réessayez.\n");
        }
    } while (choix < 1 || choix > 2);

    // --- 2. Saisie de l'ISBN ---
    while (1) {
        printf("Entrer l'ISBN (%d chiffres) : ", (choix == 1) ? 10 : 13);
        
        // On limite la lecture à TAILLE_MAX_ISBN - 1 caractères pour éviter le dépassement du tableau
        if (scanf("%13s", livre->isbn) != 1) { // TAILLE_MAX_ISBN (14) - 1 = 13
            fprintf(stderr, "Erreur de lecture de l'ISBN.\n");
            vider_buffer();
            continue;
        }
        vider_buffer();

        int taille_attendue = (choix == 1) ? 10 : 13;
        if (est_isbn_valide(livre->isbn, taille_attendue)) {
            break; // ISBN correct, on sort de la boucle
        }
        fprintf(stderr, "Erreur : L'ISBN est invalide pour ce format.\n");
    }

    // --- 3. Titre du livre (utilisation de fgets pour les espaces) ---
    printf("Entrer le titre du livre : ");
    
    if (fgets(livre->titre, TAILLE_MAX_TITRE, stdin) != NULL) {
        livre->titre[strcspn(livre->titre, "\n")] = '\0';
    }

    // --- 4. Auteur du livre ---
    printf("Entrer l'auteur du livre : ");
    if (fgets(livre->auteur, TAILLE_MAX_AUTEUR, stdin) != NULL) {
        livre->auteur[strcspn(livre->auteur, "\n")] = '\0';
    }

    // --- 5. Année de publication ---
    while (1) {
        printf("Entrer l'année de publication (1450 - %d) : ", annee_ac);
        if (scanf("%d", &annee_pub) != 1) {
            fprintf(stderr, "Erreur : Veuillez entrer un nombre entier.\n");
            vider_buffer();
            continue;
        }
        vider_buffer();

        if (annee_pub >= 1450 && annee_pub <= annee_ac) {
            livre->annee_publication = annee_pub;
            break;
        }
        fprintf(stderr, "Erreur : L'année doit être comprise entre 1450 et %d.\n", annee_ac);
    }

    // --- 6. Initialisation des états système ---
    livre->est_emprunte = 0;
    livre->id_emprunteur = -1;
    strcpy(livre->date_echeance, "0000-00-00"); // Le livre est disponible, pas d'échéance.

    printf("\n[Succès] Livre '%s' enregistré avec l'ID %d.\n", livre->titre, livre->id);
}

void afficher_livre(const Livre *livre) {
    if (livre == NULL) {
        fprintf(stderr, "Erreur : Impossible d'afficher un livre inexistant (NULL).\n");
        return;
    }

    printf("--------------------------------------------------\n");
    printf("  [Livre ID: %d]\n", livre->id);
    printf("--------------------------------------------------\n");
    printf("  Titre       : %s\n", livre->titre);
    printf("  Auteur      : %s\n", livre->auteur);
    printf("  ISBN        : %s\n", livre->isbn);
    printf("  Année       : %d\n", livre->annee_publication);
    
    // Affichage intelligent de l'état
    if (livre->est_emprunte) {
        printf("  État        : EMPRUNTÉ (par Membre ID %d)\n", livre->id_emprunteur);
        printf("  Échéance    : %s\n", livre->date_echeance);
    } else {
        printf("  État        : DISPONIBLE\n");
    }
    printf("--------------------------------------------------\n");
}

int comparer_livres(const Livre *livre_a, const Livre *livre_b) {
    if (livre_a == NULL || livre_b == NULL) {
        fprintf(stderr, "Erreur : Impossible de comparer des livres lorsque l'un d'eux est NULL.\n");
        return 0; // On peut choisir de les considérer égaux ou de retourner une erreur
    }
    return strcmp(livre_a->titre, livre_b->titre);
}

void sauvegarder_livre(const Livre *livre, FILE *fichier) {
    if (livre == NULL || fichier == NULL) {
        fprintf(stderr, "Erreur : Impossible de sauvegarder un livre ou d'écrire dans un fichier NULL.\n");
        return;
    }
    fprintf(fichier, "%d|%s|%s|%s|%d|%d|%d|%s\n",
            livre->id,
            livre->isbn,
            livre->titre,
            livre->auteur,
            livre->annee_publication,
            livre->est_emprunte,
            livre->id_emprunteur,
            livre->date_echeance);
}