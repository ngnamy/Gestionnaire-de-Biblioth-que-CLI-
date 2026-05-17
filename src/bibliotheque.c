#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/bibliotheque.h"
#include "../include/livre.h"
#include "../include/membres.h"
#include "../include/utilitaire.h"

void initialiser_bibliotheque(Bibliotheque *bibliotheque, int capacite_livres, int capacite_membres) {
    bibliotheque->livres = (Livre *)malloc(capacite_livres * sizeof(Livre));
    if (bibliotheque->livres == NULL) {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour les livres.\n");
        exit(EXIT_FAILURE);
    }
    bibliotheque->nb_livres = 0;
    bibliotheque->prochain_id_livre = 1; // Commence à 1 pour éviter les ID nuls
    bibliotheque->capacite_livres = capacite_livres;

    bibliotheque->membres = (Membre *)malloc(capacite_membres * sizeof(Membre));
    if (bibliotheque->membres == NULL) {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour les membres.\n");
        free(bibliotheque->livres); // Libérer la mémoire déjà allouée pour les livres
        exit(EXIT_FAILURE);
    }
    bibliotheque->nb_membres = 0;
    bibliotheque->prochain_id_membre = 1; // Initialise le compteur d'ID de membre
    bibliotheque->capacite_membres = capacite_membres;

    // Initialisation des noms de fichiers par défaut
    snprintf(bibliotheque->fichier_livres, MAX_TAILLE_FICHIER, "livres.dat");
    snprintf(bibliotheque->fichier_membres, MAX_TAILLE_FICHIER, "membres.dat");
}

void detruire_bibliotheque(Bibliotheque *bibliotheque) {
    free(bibliotheque->livres);
    bibliotheque->livres = NULL;
    bibliotheque->nb_livres = 0;
    bibliotheque->capacite_livres = 0;

    free(bibliotheque->membres);
    bibliotheque->membres = NULL;
    bibliotheque->nb_membres = 0;
    bibliotheque->capacite_membres = 0;
}

void ajouter_livre(Bibliotheque *bibliotheque, Livre nouveau_livre) {
    if (bibliotheque->nb_livres >= bibliotheque->capacite_livres) {
        int nouvelle_capacite = bibliotheque->capacite_livres * 2;
        Livre *nouveau_tableau = (Livre *)realloc(bibliotheque->livres, nouvelle_capacite * sizeof(Livre));
        if (nouveau_tableau == NULL) {
            fprintf(stderr, "Erreur : Échec de la réallocation mémoire pour les livres.\n");
            return; // On peut choisir de quitter ou de gérer l'erreur autrement
        }
        bibliotheque->livres = nouveau_tableau;
        bibliotheque->capacite_livres = nouvelle_capacite;
    }
    bibliotheque->livres[bibliotheque->nb_livres] = nouveau_livre;
    bibliotheque->nb_livres++;
}

void afficher_bibliotheque(const Bibliotheque *bibliotheque){
    if (bibliotheque == NULL) {
        fprintf(stderr, "Erreur : Impossible d'afficher une bibliothèque NULL.\n");
        return;
    }
    printf("\n=== Bibliothèque : %d livre(s) ===\n", bibliotheque->nb_livres);
    for (int i = 0; i < bibliotheque->nb_livres; i++) {
        afficher_livre(&bibliotheque->livres[i]);
    }
}

int rechercher_livre(const Bibliotheque *bibliotheque, int id) {
    if (bibliotheque == NULL || bibliotheque->livres == NULL) {
        return -1;
    }
    return rechercher_livre_par_id(bibliotheque, bibliotheque->nb_livres, id);
}

void modifier_livre(Bibliotheque *bibliotheque, int id) {
    int index = rechercher_livre(bibliotheque, id);
    if (index < 0) {
        fprintf(stderr, "Erreur : Aucun livre avec l'identifiant %d\n", id);
        return;
    }

    int choix = 0;
    do {
        printf("\n=== Que voulez-vous modifier ? ===\n");
        printf("1. L'ISBN\n2. Le titre\n3. L'auteur\n4. Année de publication\n5. Annuler\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1) {
            fprintf(stderr, "Saisie invalide.\n");
            vider_buffer();
            choix = 0;  // force une nouvelle itération
            continue;
        }
        vider_buffer();

        switch (choix) {
            case 1:  // Modifier ISBN
                modifier_isbn(bibliotheque, index);  // fonction dédiée
                break;
            case 2:
                modifier_titre(bibliotheque, index);
                break;
            case 3:
                modifier_auteur(bibliotheque, index);
                break;
            case 4:
                modifier_annee_publication(bibliotheque, index);
                break;
            case 5:
                printf("Modification annulée.\n");
                break;
            default:
                fprintf(stderr, "Choix invalide (1-5).\n");
                choix = 0;
        }
    } while (choix != 5);
}

void inscrire_membre(Bibliotheque *bibliotheque) {
    if (bibliotheque->nb_membres >= bibliotheque->capacite_membres) {
        int nouvelle_capacite = bibliotheque->capacite_membres * 2;
        Membre *nouveau_tableau = (Membre *)realloc(bibliotheque->membres, nouvelle_capacite * sizeof(Membre));
        if (nouveau_tableau == NULL) {
            fprintf(stderr, "Erreur : Échec de la réallocation mémoire pour les membres.\n");
            return;
        }
        bibliotheque->membres = nouveau_tableau;
        bibliotheque->capacite_membres = nouvelle_capacite;
    }
    Membre nouveau_membre;
    saisir_membre(&nouveau_membre, bibliotheque->prochain_id_membre++);
    bibliotheque->membres[bibliotheque->nb_membres] = nouveau_membre;
    bibliotheque->nb_membres++;
    printf("Membre '%s' ajouté avec succès (ID: %d).\n", nouveau_membre.nom, nouveau_membre.id_membre);
}

void afficher_membres(const Bibliotheque *bibliotheque) {
    if (bibliotheque == NULL) {
        fprintf(stderr, "Erreur : Impossible d'afficher une bibliothèque NULL.\n");
        return;
    }
    printf("\n=== Membres de la Bibliothèque : %d membre(s) ===\n", bibliotheque->nb_membres);
    if (bibliotheque->nb_membres == 0) {
        printf("Aucun membre enregistré.\n");
        return;
    }
    for (int i = 0; i < bibliotheque->nb_membres; i++) {
        afficher_membre(&bibliotheque->membres[i]);
    }
}

void supprimer_livre(Bibliotheque *bibliotheque, int id) {
    int index = rechercher_livre(bibliotheque, id);
    if (index == -1) {
        printf("Livre non trouvé.\n");
        return;
    }
    for (int i = index; i < bibliotheque->nb_livres - 1; i++) {
        bibliotheque->livres[i] = bibliotheque->livres[i + 1];
    }
    bibliotheque->nb_livres--;
    printf("Livre supprimé avec succès.\n");
}

void trier_bibliotheque(Bibliotheque *bibliotheque) {
    if (bibliotheque == NULL || bibliotheque->nb_livres < 2) return;
    qsort(bibliotheque->livres, bibliotheque->nb_livres, sizeof(Livre), (int (*)(const void *, const void *))comparer_livres);
    printf("Catalogue trié par titre avec succès.\n");
}

void radier_membre(Bibliotheque *bibliotheque, int id_membre) {
    int index = rechercher_membre(bibliotheque, id_membre);
    if (index == -1) {
        printf("Membre non trouvé.\n");
        return;
    }

    if (bibliotheque->membres[index].nb_emprunts_actifs > 0) {
        printf("Impossible de radier ce membre : il a encore des livres empruntés.\n");
        return;
    }

    for (int i = index; i < bibliotheque->nb_membres - 1; i++) {
        bibliotheque->membres[i] = bibliotheque->membres[i + 1];
    }
    bibliotheque->nb_membres--;
    printf("Membre radié avec succès.\n");
}

void sauvegarder_bibliotheque(const Bibliotheque *bibliotheque) {
    FILE *f = fopen(bibliotheque->fichier_livres, "w");
    if (!f) return;
    for (int i = 0; i < bibliotheque->nb_livres; i++) {
        sauvegarder_livre(&bibliotheque->livres[i], f);
    }
    fclose(f);

    f = fopen(bibliotheque->fichier_membres, "w");
    if (!f) return;
    for (int i = 0; i < bibliotheque->nb_membres; i++) {
        sauvegarder_membre(&bibliotheque->membres[i], f);
    }
    fclose(f);
}

void effectuer_emprunt(Bibliotheque *bibliotheque, int id_livre, int id_membre) {
    int idx_l = rechercher_livre(bibliotheque, id_livre);
    int idx_m = rechercher_membre(bibliotheque, id_membre);

    if (idx_l == -1 || idx_m == -1) {
        printf("Livre ou Membre introuvable.\n");
        return;
    }

    if (bibliotheque->livres[idx_l].est_emprunte) {
        printf("Le livre est déjà emprunté.\n");
        return;
    }

    if (bibliotheque->membres[idx_m].nb_emprunts_actifs >= MAX_EMPRUNTS_MEMBRE) {
        printf("Limite d'emprunts atteinte pour ce membre.\n");
        return;
    }

    bibliotheque->livres[idx_l].est_emprunte = 1;
    bibliotheque->livres[idx_l].id_emprunteur = id_membre;
    calculer_echeance(bibliotheque->livres[idx_l].date_echeance);
    bibliotheque->membres[idx_m].nb_emprunts_actifs++;

    printf("Emprunt réussi. Date de retour : %s\n", bibliotheque->livres[idx_l].date_echeance);
}

void effectuer_retour(Bibliotheque *bibliotheque, int id_livre) {
    int idx_l = rechercher_livre(bibliotheque, id_livre);
    if (idx_l == -1 || !bibliotheque->livres[idx_l].est_emprunte) {
        printf("Le livre n'est pas marqué comme emprunté.\n");
        return;
    }

    int id_m = bibliotheque->livres[idx_l].id_emprunteur;
    int idx_m = rechercher_membre(bibliotheque, id_m);

    bibliotheque->livres[idx_l].est_emprunte = 0;
    bibliotheque->livres[idx_l].id_emprunteur = -1;
    strcpy(bibliotheque->livres[idx_l].date_echeance, "0000-00-00");

    if (idx_m != -1) {
        bibliotheque->membres[idx_m].nb_emprunts_actifs--;
    }

    printf("Livre retourné avec succès.\n");
}

int rechercher_membre(const Bibliotheque *bibliotheque, int id_membre) {
    for (int i = 0; i < bibliotheque->nb_membres; i++) {
        if (bibliotheque->membres[i].id_membre == id_membre) return i;
    }
    return -1;
}

void charger_bibliotheque(Bibliotheque *bibliotheque) {
    // Chargement des livres
    FILE *f_livres = fopen(bibliotheque->fichier_livres, "r");
    if (f_livres) {
        Livre l;
        char ligne[256];
        while (fgets(ligne, sizeof(ligne), f_livres)) {
            if (sscanf(ligne, "%d|%13[^|]|%99[^|]|%49[^|]|%d|%d|%d|%10s",
                   &l.id, l.isbn, l.titre, l.auteur, &l.annee_publication,
                   &l.est_emprunte, &l.id_emprunteur, l.date_echeance) == 8) {
                ajouter_livre(bibliotheque, l);
                if (l.id >= bibliotheque->prochain_id_livre) {
                    bibliotheque->prochain_id_livre = l.id + 1;
                }
            }
        }
        fclose(f_livres);
    }

    // Chargement des membres
    FILE *f_membres = fopen(bibliotheque->fichier_membres, "r");
    if (f_membres) {
        Membre m;
        char ligne[256];
        while (fgets(ligne, sizeof(ligne), f_membres)) {
            if (sscanf(ligne, "%d|%49[^|]|%10[^|]|%10[^|]|%d",
                       &m.id_membre, m.nom, m.telephone, m.date_inscription, &m.nb_emprunts_actifs) == 5) {
                if (bibliotheque->nb_membres >= bibliotheque->capacite_membres) {
                    int nouvelle_capacite = bibliotheque->capacite_membres * 2;
                    Membre *temp = realloc(bibliotheque->membre, nouvelle_capacite * sizeof[membre]);
                    if (temp == NULL) {
                        fprintf(stderr, "Erreur : Echec d'allocation mémoire au chargement de la bibliothèque.");
                        return;
                    }
                    bibliotheque->membre = temp;
                    bibliotheque->capacite_membres = nouvelle_capacite;
                }
                bibliotheque->membre[bibliotheque->nb_membres++] = m;
                if (m.id_membre >= bibliotheque->prochain_id_membre) {
                    bibliotheque->prochain_id_membre = m.id_membre + 1;
                }
            }
        }
        fclose(f_membres);
    }
}

void lister_livres_en_retard(const Bibliotheque *bibliotheque, const char *date_actuelle) {
    printf("\n=== LIVRES EN RETARD (Date actuelle : %s) ===\n", date_actuelle);
    int count = 0;
    for (int i = 0; i < bibliotheque->nb_livres; i++) {
        if (bibliotheque->livres[i].est_emprunte) {
            // Comparaison simple de chaînes YYYY-MM-DD
            if (strcmp(bibliotheque->livres[i].date_echeance, date_actuelle) < 0) {
                printf("ID: %d | Titre: %s | Échéance: %s | Emprunteur ID: %d\n",
                       bibliotheque->livres[i].id, bibliotheque->livres[i].titre,
                       bibliotheque->livres[i].date_echeance, bibliotheque->livres[i].id_emprunteur);
                count++;
            }
        }
    }
    if (count == 0) printf("Aucun retard détecté.\n");
}

int generer_id_livre(const Livre *livres, int nb_livres) {
    return (nb_livres == 0) ? 1 : livres[nb_livres - 1].id + 1;
}

int generer_id_membre(const Membre *membres, int nb_membres) {
    return (nb_membres == 0) ? 1 : membres[nb_membres - 1].id_membre + 1;
}

void modifier_nom (Bibliotheque *bibliotheque, int index) {
    printf("1. Confirmer la modification\n2. Annuler\n");

    int choix;
    do {
        printf("Votre choix : ");
        if (scanf("%d", &choix) != 1) {
            fprintf(stderr, "Choix invalide : Le choix doit être un entier (1 ou 2)\n");
            vider_buffer();
            choix = 0;  // Forcer une nouvelle itération
            continue;
        }
        vider_buffer();  // Consomme le '\n' laissé par scanf

        switch (choix) {
        case 1: {
            printf("Entrez le nouveau nom : ");

            char nouveau_nom[MAX_NOM_MEMBRE];
            if (fgets(nouveau_nom, MAX_NOM_MEMBRE, stdin) == NULL) {
                fprintf(stderr, "Erreur : Nom invalide.\n");
                choix = 0;  // Rester dans la boucle
                break;
            }
            // Supprimer le '\n' — pas besoin de vider_buffer() après fgets
            nouveau_nom[strcspn(nouveau_nom, "\n")] = '\0';

            if (strlen(str_trim(nouveau_nom)) > 0) {
                strncpy(bibliotheque->membres[index].nom, nouveau_nom, MAX_NOM_MEMBRE - 1);
                bibliotheque->membres[index].nom[MAX_NOM_MEMBRE - 1] = '\0';
                printf("Réussie : Nom modifié avec succès.\n");
                choix = 2;  // Quitter la boucle proprement
            } else {
                fprintf(stderr, "Erreur : Le nom ne peut pas être vide.\n");
                choix = 0;  // Rester dans la boucle
            }
            break;
        }
        case 2:
            printf("Modification annulée.\n");
            break;
        default:
            fprintf(stderr, "Choix invalide : veuillez recommencer.\n");
            choix = 0;
        }
    } while (choix != 2);
}

void modifier_telephone (Bibliotheque *bibliotheque, int index) {
    char tmp_tel[MAX_TEL_MEMBRE];
    while (1) {
        printf("Entrez le nouveau numéro de téléphone (9 chiffres, commençant par 6 ou 2) : ");
        if (fgets(tmp_tel, MAX_TEL_MEMBRE, stdin) == NULL) {
            fprintf(stderr, "Erreur de lecture.\n");
            continue;
        }
        tmp_tel[strcspn(tmp_tel, "\n")] = '\0';

        if (valider_numero(tmp_tel)) {
            strncpy(bibliotheque->membres[index].telephone, tmp_tel, MAX_TEL_MEMBRE - 1);
            bibliotheque->membres[index].telephone[MAX_TEL_MEMBRE - 1] = '\0';
            printf("Téléphone modifié avec succès.\n");
            break;
        }
        fprintf(stderr, "[Erreur] Numéro invalide. Réessayez.\n");
    }
}

void modifier_date_inscription (Bibliotheque *bibliotheque, int index) {
    char tmp_date[TAILLE_DATE];
    while (1) {
        printf("Entrez la nouvelle date d'inscription (YYYY-MM-DD) : ");
        if (fgets(tmp_date, TAILLE_DATE, stdin) == NULL) {
            fprintf(stderr, "Erreur de lecture.\n");
            continue;
        }
        tmp_date[strcspn(tmp_date, "\n")] = '\0';

        if (valider_date_inscription_membre(tmp_date)) {
            strncpy(bibliotheque->membres[index].date_inscription, tmp_date, TAILLE_DATE - 1);
            bibliotheque->membres[index].date_inscription[TAILLE_DATE - 1] = '\0';
            printf("Date d'inscription modifiée avec succès.\n");
            break;
        }
        fprintf(stderr, "[Erreur] Format YYYY-MM-DD obligatoire et année entre 2000 et %d.\n", annee_actuelle());
    }
}

void modifier_membre (Bibliotheque *bibliotheque, int id_membre) {
    int index = rechercher_membre(bibliotheque, id_membre);
    if (index == -1) {
        printf("Membre non trouvé.\n");
        return;
    }

    int choix;
    do {

        printf("Que voulez-vous modifier ?\n");
        printf("1. Nom\n");
        printf("2. Téléphone\n");
        printf("3. Date d'inscription\n");
        printf("4. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        vider_buffer();

        switch (choix) {
            case 1:
                modifier_nom(bibliotheque, index);
                break;
            case 2:
                modifier_telephone(bibliotheque, index);
                break;
            case 3:
                modifier_date_inscription(bibliotheque, index);
                break;
            case 4:
                break;
            default:
                printf("Choix invalide : veillez recommencer.\n");
        }
    } while (choix != 4);

}
