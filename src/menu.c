#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "../include/menu.h"
#include "../include/utilitaire.h"
#include "../include/bibliotheque.h"
#include "../include/livre.h"
#include "../include/membres.h"

static int demander_confirmation(const char *message) {
    char reponse[10];
    printf("%s (o/n) : ", message);
    if (fgets(reponse, sizeof(reponse), stdin)) {
        if (reponse[0] == 'o' || reponse[0] == 'O') {
            return 1;
        }
    }
    return 0;
}

void menu_catalogue_livre (Bibliotheque *biblio) {
    int choix_cat = 0;
    do {
        printf("\n--- GESTION DU CATALOGUE ---\n");
        printf("1. Afficher tous les livres\n2. Ajouter un livre\n3. Rechercher un livre \n");
        printf("4. Modifier un livre\n5. Supprimer un livre\n6. Trier le catalogue de livre\n7. Retour\n");
        printf("Choix : ");
        scanf("%d", &choix_cat); vider_buffer();
        switch(choix_cat) {
            case 1: {afficher_bibliotheque(biblio); break;}
            case 2: {
                Livre n; saisir_livre(&n, biblio, biblio->prochain_id_livre++);
                ajouter_livre(biblio, n); break;
            }
            case 3: {
                int choix_rech;
                printf("\n--- Rechercher par ---\n");
                printf("1. ID\n2. Auteur\n3. Titre\n4. ISBN\n5. Annuler\nChoix : ");
                if (scanf("%d", &choix_rech) != 1) {
                    vider_buffer();
                    printf("Choix invalide.\n");
                    break;
                }
                vider_buffer();

                int idx = -1;
                if (choix_rech == 1) {
                    int id;
                    printf("ID à rechercher : ");
                    if (scanf("%d", &id) == 1) idx = rechercher_livre_par_id(biblio, biblio->nb_livres, id);
                    vider_buffer();
                } else if (choix_rech == 2) {
                    char auteur[TAILLE_MAX_AUTEUR];
                    printf("Nom de l'auteur : ");
                    fgets(auteur, TAILLE_MAX_AUTEUR, stdin);
                    auteur[strcspn(auteur, "\n")] = 0;
                    
                    int *resultat_array = rechercher_array_livre_par_auteur(biblio, biblio->nb_livres, auteur);
                    if (resultat_array == NULL) {
                        printf("Aucun livre trouvé pour cet auteur.\n");
                    } else {
                        for (int i = 0; resultat_array[i] != -1; i++) {
                            afficher_livre(&biblio->livres[resultat_array[i]]);
                        }
                        free(resultat_array); // Libération de la mémoire
                    }
                    idx = -1; // On remet idx à -1 pour éviter l'affichage double après le switch
                    break;
                } else if (choix_rech == 3) {
                    char titre[TAILLE_MAX_TITRE];
                    printf("Titre du livre : ");
                    fgets(titre, TAILLE_MAX_TITRE, stdin);
                    titre[strcspn(titre, "\n")] = 0;
                    idx = rechercher_livre_par_titre(biblio, biblio->nb_livres, titre);
                } else if (choix_rech == 4) {
                    char isbn[TAILLE_MAX_ISBN];
                    printf("ISBN du livre : ");
                    fgets(isbn, TAILLE_MAX_ISBN, stdin);
                    isbn[strcspn(isbn, "\n")] = 0;
                    idx = rechercher_livre_par_isbn(biblio, biblio->nb_livres, isbn);
                } else if (choix_rech == 5) {printf("Choix annulé.\n"); break;}

                if(idx != -1) {
                    afficher_livre(&biblio->livres[idx]);
                } else if (choix_rech >= 1 && choix_rech <= 4) {
                    printf("Livre introuvable.\n");
                }
                break;
            }
            case 4: {
                printf("Veillez choisir la méthode de modification\n");
                printf("1. ID\n2. Auteur\n3. Titre\n4. Annuler\nVotre choix : ");
                int choix_mod;
                if (scanf("%d", &choix_mod) != 1) {
                    fprintf(stderr, "Choix invalide.\n");
                    vider_buffer();
                    break;
                }
                vider_buffer();

                if (choix_mod == 1) {
                    int id;
                    printf("ID à modifier : ");
                    if (scanf("%d", &id) != 1) {
                        fprintf(stderr, "Erreur : ID non valide, dois être un entier positif.");
                        vider_buffer();
                        return;
                    }
                    vider_buffer();
                    modifier_livre(biblio, id); break;
                } else if (choix_mod == 2) {
                    char auteur[TAILLE_MAX_AUTEUR];
                    printf("Auteur à modifier : ");
                    if (fgets(auteur, TAILLE_MAX_AUTEUR, stdin) != NULL) {
                        auteur[strcspn(auteur, "\n")] = 0;
                        modifier_livre_par_auteur(biblio, auteur);
                    } else {
                        fprintf(stderr, "Erreur de lecture de l'auteur.\n");
                    }
                    break;
                    
                } else if (choix_mod == 3) {
                    char titre[TAILLE_MAX_TITRE];
                    printf("Titre à modifier : ");
                    if (fgets(titre, TAILLE_MAX_TITRE, stdin) != NULL) {
                        titre[strcspn(titre, "\n")] = 0;
                        modifier_livre_par_titre(biblio, titre);
                    } else {
                        fprintf(stderr, "Erreur de lecture du titre.\n");
                    }
                    break;
                }
                break;  // Empêche le fall-through vers case 5
            }
            case 5: {
                printf("Veillez entrer la méthode de suppression.\n");
                printf("1. ID\n2. Auteur\n3. Titre\n4. ISBN\n5. Annuler\nVotre choix : ");
                int choix_sup;
                if (scanf("%d", &choix_sup) != 1) {
                    fprintf(stderr, "Choix invalide.\n");
                    vider_buffer();
                    break;
                }
                vider_buffer(); // Nettoie le '\n' pour que les fgets suivants fonctionnent

                switch (choix_sup)
                {
                case 1: {
                    printf("ID à supprimer : ");
                    int id;
                    if (scanf("%d", &id) == 1) {
                        vider_buffer();
                        if (demander_confirmation("Êtes-vous sûr de vouloir supprimer ce livre ?")) {
                            supprimer_livre(biblio, id);
                        } else {
                            printf("Suppression annulée.\n");
                        }
                    } else {
                        fprintf(stderr, "ID invalide.\n");
                        vider_buffer();
                    }
                    break; 
                }
                case 2: {
                    printf("Auteur à supprimer : ");
                    char auteur[TAILLE_MAX_AUTEUR];
                    fgets(auteur, TAILLE_MAX_AUTEUR, stdin);
                    auteur[strcspn(auteur, "\n")] = 0;
                    if (demander_confirmation("Êtes-vous sûr de vouloir supprimer les livres de cet auteur ?")) {
                        supprimer_livre_par_auteur(biblio, auteur);
                    } else {
                        printf("Suppression annulée.\n");
                    }
                    break; 
                }
                case 3: {
                    printf("Titre à supprimer : ");
                    char titre[TAILLE_MAX_TITRE];
                    fgets(titre, TAILLE_MAX_TITRE, stdin);
                    titre[strcspn(titre, "\n")] = 0;
                    if (demander_confirmation("Êtes-vous sûr de vouloir supprimer ce livre ?")) {
                        supprimer_livre_par_titre(biblio, titre);
                    } else {
                        printf("Suppression annulée.\n");
                    }
                    break; 
                }
                case 4: {
                    printf("ISBN à supprimer : ");
                    char isbn[TAILLE_MAX_ISBN];
                    fgets(isbn, TAILLE_MAX_ISBN, stdin);
                    isbn[strcspn(isbn, "\n")] = 0;
                    if (demander_confirmation("Êtes-vous sûr de vouloir supprimer ce livre ?")) {
                        supprimer_livre_par_isbn(biblio, isbn);
                    } else {
                        printf("Suppression annulée.\n");
                    }
                    break; 
                }
                case 5: {
                    break; // Annuler
                }
                default:
                    fprintf(stderr, "Choix invalide.\n");
                    break;
                }
                break;
            }
            case 6: {
                printf("Trier les livres par\n1. ID\n2. Titre\n3. Auteur\n4. Annuler\nVotre choix : ");
                int choix_t;
                if (scanf("%d", &choix_t) != 1) {
                    fprintf(stderr, "Erreur : le choix dois être un entier positif valide.");
                    vider_buffer();
                    return;
                }
                vider_buffer();

                if (choix_t == 1) {
                    trier_bibliotheque_par_id(biblio);
                } else if (choix_t == 2) {
                    trier_bibliotheque(biblio);
                } else if (choix_t == 3) {
                    trier_bibliotheque_par_auteur(biblio);
                } else if (choix_t == 4) {
                    printf("Choix annuler.");
                    break;
                } else {
                    printf("choix invalide.");
                    break;
                }
                break;
            }
        }
    } while (choix_cat != 7);
}

void menu_gestion_membres (Bibliotheque *biblio) {
    int choix_membre = 0;
    do {
        printf("\n=== GESTION DES MEMBRES ===\n");
        printf("1. Afficher tous les membres\n");
        printf("2. Inscrire un nouveau membre\n");
        printf("3. Radier un membre\n");
        printf("4. Modifier membre\n");
        printf("5. Retour au menu principal\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix_membre) != 1) {
            fprintf(stderr, "Choix invalide. Veuillez entrer un nombre.\n");
            vider_buffer();
            continue;
        }
        vider_buffer();

        switch (choix_membre) {
            case 1:
                afficher_membres(biblio);
                break;
            case 2:
                inscrire_membre(biblio);
                break;
            case 3:
                {
                    int id_a_radier;
                    printf("Entrez l'ID du membre à radier : ");
                    if (scanf("%d", &id_a_radier) == 1) {
                        vider_buffer();
                        if (demander_confirmation("Êtes-vous sûr de vouloir radier ce membre ?")) {
                            radier_membre(biblio, id_a_radier);
                        } else {
                            printf("Radiation annulée.\n");
                        }
                    } else {
                        fprintf(stderr, "ID invalide.\n");
                        vider_buffer();
                    }
                }
                break;
            case 4:
                {
                int id_membre;
                printf("Entrez l'ID du membre à modifier : ");

                if (scanf("%d", &id_membre) == 1) {
                    vider_buffer();
                    modifier_membre(biblio, id_membre);
                } else {
                    fprintf(stderr, "ID invalide.\n");
                    vider_buffer();
                }
                }
                break;  // ← break manquant : empêchait le fall-through vers case 5
            case 5: break; // Retour au menu principal
            default: fprintf(stderr, "Option invalide. Veuillez choisir entre 1 et 4.\n"); break;
        }
    } while (choix_membre != 5);
}

void menu_gestion_emprunt_retour (Bibliotheque *biblio) {
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
            printf("ID du livre : ");
            if (scanf("%d", &id_l) != 1) { vider_buffer(); continue; }
            printf("ID du membre : ");
            if (scanf("%d", &id_m) != 1) { vider_buffer(); continue; }
            vider_buffer();
            effectuer_emprunt(biblio, id_l, id_m);
        } else if (choix_emprunt == 2) {
            int id_l;
            printf("ID du livre à retourner : ");
            if (scanf("%d", &id_l) != 1) { vider_buffer(); continue; }
            vider_buffer();
            effectuer_retour(biblio, id_l);
        } else if (choix_emprunt == 3) {
            // On génère une date fictive ou réelle pour le test
            char aujourdhui[11];
            time_t t = time(NULL);
            strftime(aujourdhui, 11, "%Y-%m-%d", localtime(&t));
            lister_livres_en_retard(biblio, aujourdhui);
        }
    } while (choix_emprunt != 4);
}
