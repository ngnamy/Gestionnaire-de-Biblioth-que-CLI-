#include "membres.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utilitaire.h"

void saisir_membre(Membre *membre, int prochain_id) {
    membre->id_membre = prochain_id;

    // --- 1. Nom ---
    printf("Entrer votre nom : ");
    if (fgets(membre->nom, MAX_NOM_MEMBRE, stdin) != NULL) {
        if (membre->nom[strlen(membre->nom) - 1] != '\n') {
            vider_buffer();
        }
        membre->nom[strcspn(membre->nom, "\n")] = '\0';
    }

    // --- 2. Numéro de téléphone (avec boucle de validation) ---
    while (1) {
        printf("Entrer votre numéro (9 chiffres commençant par 6) : ");
        if (fgets(membre->telephone, MAX_TEL_MEMBRE, stdin) != NULL) {
            if (membre->telephone[strlen(membre->telephone) - 1] != '\n') {
                vider_buffer();
            }
            membre->telephone[strcspn(membre->telephone, "\n")] = '\0';

            if (valider_numero(membre->telephone)) break;

            fprintf(stderr, "[Erreur] Numéro invalide au Cameroun.\n");
        }
    }

    // --- 3. Date d'inscription ---
    while (1) {
        printf("Entrer la date d'inscription (YYYY-MM-DD) : ");
        if (fgets(membre->date_inscription, TAILLE_DATE, stdin) != NULL) {
            if (membre->date_inscription[strlen(membre->date_inscription) - 1] != '\n') {
                vider_buffer();
            }
            membre->date_inscription[strcspn(membre->date_inscription, "\n")] = '\0';

            if (valider_date(membre->date_inscription)) break;

            fprintf(stderr, "[Erreur] Format YYYY-MM-DD obligatoire.\n");
        }
    }

    membre->nb_emprunts_actifs = 0;
    printf("\n[Succès] Membre enregistré avec l'ID : %d\n", membre->id_membre);
}

void afficher_membre(const Membre *membre) {
    if (membre == NULL) {
        fprintf(stderr, "[Erreur] Impossible d'afficher : pointeur membre NULL.\n");
        return;
    }

    printf("\n==================================================\n");
    printf("  FICHE MEMBRE [ID: %d]\n", membre->id_membre);
    printf("==================================================\n");
    printf("  Nom         : %s\n", membre->nom);
    printf("  Téléphone   : %s\n", membre->telephone);
    printf("  Inscription : %s\n", membre->date_inscription);

    // Affichage du statut des emprunts
    printf("  Statut      : ");
    if (membre->nb_emprunts_actifs == 0) {
        printf("Aucun livre en cours\n");
    } else {
        printf("%d livre(s) emprunté(s)\n", membre->nb_emprunts_actifs);
    }

    printf("--------------------------------------------------\n");
}

void sauvegarder_membre (const Membre *membre, FILE *fichier) {
    if (membre == NULL || fichier == NULL) {
        fprintf(stderr, "Impossible de sauvegarder le membre ou d'écrire dans le fichier.\n");
        return;
    }

    fprintf(
            fichier,
            "%d|%s|%s|%s|%d\n",
            membre->id_membre,
            membre->nom,
            membre->telephone,
            membre->date_inscription
        );
}
