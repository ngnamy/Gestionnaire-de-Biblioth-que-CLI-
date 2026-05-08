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
                int choix_cat = 0;
                do {
                    printf("\n--- GESTION DU CATALOGUE ---\n");
                    printf("1. Afficher tous les livres\n2. Ajouter un livre\n3. Rechercher un livre (ID)\n");
                    printf("4. Modifier un livre\n5. Supprimer un livre\n6. Trier par titre\n7. Retour\n");
                    printf("Choix : ");
                    scanf("%d", &choix_cat); vider_buffer();
                    switch(choix_cat) {
                        case 1: afficher_bibliotheque(&biblio); break;
                        case 2: {
                            Livre n; saisir_livre(&n, biblio.prochain_id_livre++);
                            ajouter_livre(&biblio, n); break;
                        }
                        case 3: {
                            int id; printf("ID à rechercher : "); scanf("%d", &id); vider_buffer();
                            int idx = rechercher_livre(&biblio, id);
                            if(idx != -1) afficher_livre(&biblio.livres[idx]);
                            else printf("Livre introuvable.\n");
                            break;
                        }
                        case 4: {
                            int id; printf("ID à modifier : "); scanf("%d", &id); vider_buffer();
                            modifier_livre(&biblio, id); break;
                        }
                        case 5: {
                            int id; printf("ID à supprimer : "); scanf("%d", &id); vider_buffer();
                            supprimer_livre(&biblio, id); break;
                        }
                        case 6: trier_bibliotheque(&biblio); break;
                    }
                } while (choix_cat != 7);
            }
            break;
        case 2: // Gérer les membres
            {
                int choix_membre = 0;
                do {
                    printf("\n=== GESTION DES MEMBRES ===\n");
                    printf("1. Afficher tous les membres\n");
                    printf("2. Inscrire un nouveau membre\n");
                    printf("3. Radier un membre\n");
                    printf("4. Retour au menu principal\n");
                    printf("Votre choix : ");

                    if (scanf("%d", &choix_membre) != 1) {
                        fprintf(stderr, "Choix invalide. Veuillez entrer un nombre.\n");
                        vider_buffer();
                        continue;
                    }
                    vider_buffer();

                    switch (choix_membre) {
                        case 1:
                            afficher_membres(&biblio);
                            break;
                        case 2:
                            inscrire_membre(&biblio);
                            break;
                        case 3:
                            {
                                int id_a_radier;
                                printf("Entrez l'ID du membre à radier : ");
                                if (scanf("%d", &id_a_radier) == 1) {
                                    radier_membre(&biblio, id_a_radier);
                                } else {
                                    fprintf(stderr, "ID invalide.\n");
                                }
                                vider_buffer();
                            }
                            break;
                        case 4: break; // Retour au menu principal
                        default: fprintf(stderr, "Option invalide. Veuillez choisir entre 1 et 4.\n"); break;
                    }
                } while (choix_membre != 4);
            }
            break;
        case 3: // Gérer les emprunts
            {
                int choix_emprunt = 0;
                do {
                    printf("\n=== GESTION DES EMPRUNTS ===\n");
                    printf("1. Emprunter un livre\n");
                    printf("2. Retourner un livre\n");
                    printf("3. Voir les livres en retard\n");
                    printf("4. Retour au menu principal\n");
                    printf("Votre choix : ");
                    scanf("%d", &choix_emprunt);
                    vider_buffer();

                    if (choix_emprunt == 1) {
                        int id_l, id_m;
                        printf("ID du livre : "); scanf("%d", &id_l);
                        printf("ID du membre : "); scanf("%d", &id_m);
                        effectuer_emprunt(&biblio, id_l, id_m);
                    } else if (choix_emprunt == 2) {
                        int id_l;
                        printf("ID du livre à retourner : "); scanf("%d", &id_l);
                        effectuer_retour(&biblio, id_l);
                    } else if (choix_emprunt == 3) {
                        // On génère une date fictive ou réelle pour le test
                        char aujourdhui[11];
                        time_t t = time(NULL);
                        strftime(aujourdhui, 11, "%Y-%m-%d", localtime(&t));
                        lister_livres_en_retard(&biblio, aujourdhui);
                    }
                } while (choix_emprunt != 4);
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