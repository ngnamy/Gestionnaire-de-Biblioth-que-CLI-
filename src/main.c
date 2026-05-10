#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/livre.h"
#include "../include/bibliotheque.h"
#include "../include/membres.h"
#include "../include/utilitaire.h"

int main () {
    printf("=== Bienvenue dans le gestionnaire de bibliothèque CLI ===\n");
    
    Bibliotheque biblio;
    // On initialise une seule fois au début pour éviter les fuites mémoire
    initialiser_bibliotheque(&biblio, 10, 10);
    
    // Chargement automatique au démarrage
    charger_bibliotheque(&biblio);
    printf("Base de données chargée avec succès.\n");

    int choix = 0;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Gestion du catalogue (Livres)\n");
        printf("2. Gérer les membres\n");
        printf("3. Gérer les emprunts et retours\n");
        printf("4. Quitter\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1) {
            fprintf(stderr, "Choix invalide. Veuillez entrer un nombre.\n");
            vider_buffer();
            continue;
        }
        vider_buffer();

        switch (choix)
        {
        case 1: // Gestion du catalogue
            {
                menu_catologue_livre(&biblio);
                sauvegarder_bibliotheque(&biblio);
            }
            break;
        case 2: // Gérer les membres
            {
                menu_gestion_membres(&biblio);
                sauvegarder_bibliotheque(&biblio);
            }
            break;
        case 3: // Gérer les emprunts
            {
                menu_gestion_emprunt_retour(&biblio);
                sauvegarder_bibliotheque(&biblio);
            }
            break;
        case 4: // Quitter
            printf("Sauvegarde des données en cours...\n");
            sauvegarder_bibliotheque(&biblio);
            printf("Fermeture du programme. Au revoir !\n");
            break;
        default:
            fprintf(stderr, "Option invalide. Veuillez choisir entre 1 et 4.\n");
        }

    } while (choix != 4); // On continue tant que l'utilisateur ne quitte pas

    // Libération de la mémoire avant de quitter
    detruire_bibliotheque(&biblio);
    return 0;
}