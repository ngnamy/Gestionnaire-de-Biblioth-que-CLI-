#include <time.h>
#include  <stdlib.h>
#include <stdio.h>
#include  <string.h>
#include "../include/utilitaire.h"

#include <ctype.h>

int annee_actuelle () {
    time_t t = time(NULL);
    struct tm *info = localtime(&t);
    if (info != NULL) {
        return info->tm_year + 1900;
    }
    return -1;
}

void calculer_echeance(char *date_echeance) {
    time_t maintenant = time(NULL);
    struct tm *echeance = localtime(&maintenant);

    if (echeance == NULL) {
        snprintf(date_echeance, 11, "0000-00-00");
        return;
    }

    // On ajoute la durée
    echeance->tm_mday += DUREE_EMPRUNT;

    // On normalise (gère les changements de mois/année)
    mktime(echeance);

    // Optionnel : Si c'est un dimanche (0), on décale au lundi (+1 jour)
    if (echeance->tm_wday == 0) {
        echeance->tm_mday += 1;
        mktime(echeance);
    }

    // On formate en YYYY-MM-DD
    strftime(date_echeance, 11, "%Y-%m-%d", echeance);
}

void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int valider_numero(const char *numero) {
    // 1. Vérification de la longueur (9 chiffres exactement)
    if (strlen(numero) != 9) {
        return 0;
    }

    // 2. Vérification du premier chiffre (6 pour mobile, 2 pour fixe)
    if (numero[0] != '6' && numero[0] != '2') {
        return 0;
    }

    // 3. Vérification que tout le reste sont des chiffres
    for (int i = 0; i < 9; i++) {
        if (!isdigit(numero[i])) {
            return 0;
        }
    }

    return 1;
}

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int valider_date (const char *date){
    int y, m, d;

    // 1. Vérifier la longueur de la chaîne (doit être "YYYY-MM-DD", donc 10 caractères)
    if (strlen(date) != 10) {
        return 0;
    }

    // 2. Vérifier la présence des tirets aux bonnes positions
    if (date[4] != '-' || date[7] != '-') {
        return 0;
    }

    // 3. Tenter de parser la date. Utiliser %d pour permettre des mois/jours à un chiffre
    if (sscanf(date, "%d-%d-%d", &y, &m, &d) != 3) {
        return 0;
    }

    // 4. Vérifier les limites de mois et jour
    if (m < 1 || m > 12 || d < 1 || d > 31) {
        return 0;
    }

    // 5. Vérifier les jours par mois
    if (m == 4 || m == 6 || m == 9 || m == 11) { // Avril, Juin, Septembre, Novembre ont 30 jours
        if (d > 30) return 0;
    } else if (m == 2) { // Février
        if (isLeapYear(y)) {
            if (d > 29) return 0; // Année bissextile, Février a 29 jours
        } else {
            if (d > 28) return 0; // Année non bissextile, Février a 28 jours
        }
    }

    // Si toutes les vérifications passent
    return 1;
}

int recherche_dichotomique_livre(Livre *livres, int taille, int id) {
    int debut = 0, fin = taille - 1;
    
    while (debut <= fin) {
        int milieu = debut + (fin - debut) / 2;
        
        if (livres[milieu].id > id) {
            fin = milieu - 1;
        } else if (livres[milieu].id < id) {
            debut = milieu + 1;
        } else {
            return milieu;  // trouvé
        }
    }
    return -1;
}

void modifier_isbn(Bibliotheque *b, int index) {
    int type;
    do {
        printf("1. ISBN-10\n2. ISBN-13\nVotre choix : ");
        if (scanf("%d", &type) != 1 || (type != 1 && type != 2)) {
            fprintf(stderr, "Choix invalide.\n");
            vider_buffer();
            continue;
        }
        vider_buffer();
        break;
    } while (1);
    
    char tmp_isbn[14];  // 13 + \0
    int taille_attendue = (type == 1) ? 10 : 13;
    while (1) {
        printf("Entrer l'ISBN (%d chiffres) : ", taille_attendue);
        if (scanf("%13s", tmp_isbn) != 1) {
            fprintf(stderr, "Erreur de lecture.\n");
            vider_buffer();
            continue;
        }
        vider_buffer();
        if (est_isbn_valide(tmp_isbn, taille_attendue)) {
            strcpy(b->livres[index].isbn, tmp_isbn);
            break;
        }
        fprintf(stderr, "ISBN invalide.\n");
    }
}

void modifier_titre(Bibliotheque *b, int index) {
    char nouveau_titre[TAILLE_MAX_TITRE];
    printf("Nouveau titre : ");
    fgets(nouveau_titre, TAILLE_MAX_TITRE, stdin);
    nouveau_titre[strcspn(nouveau_titre, "\n")] = '\0'; // supprime le saut de ligne
    char *nouveau_titre_trim = str_trim(nouveau_titre);
    if (strlen(nouveau_titre_trim) <= 0) {
        fprintf(stderr, "Erreur : la chaine de caractère est vide.");
        return;
    }
    strncpy(b->livres[index].titre, nouveau_titre, TAILLE_MAX_TITRE - 1);
    strncpy(b->livres[index].titre, nouveau_titre_trim, TAILLE_MAX_TITRE - 1);
    b->livres[index].titre[TAILLE_MAX_TITRE - 1] = '\0';
}

void modifier_auteur (Bibliotheque *b, int index) {
    char nouveau_auteur[TAILLE_MAX_AUTEUR];
    printf("Nouvel auteur : ");
    fgets(nouveau_auteur, TAILLE_MAX_AUTEUR, stdin);
    nouveau_auteur[strcspn(nouveau_auteur, "\n")] = '\0'; // supprime le saut de ligne
    char *nouveau_auteur_trim = str_trim(nouveau_auteur);
    if (strlen(nouveau_auteur_trim) <= 0) {
        fprintf(stderr, "Erreur : la chaine de caractère est vide.");
        return;
    }
    strncpy(b->livres[index].auteur, nouveau_auteur, TAILLE_MAX_AUTEUR - 1);
    strncpy(b->livres[index].auteur, nouveau_auteur_trim, TAILLE_MAX_AUTEUR - 1);
    b->livres[index].auteur[TAILLE_MAX_AUTEUR - 1] = '\0';
    printf("Réussie : Modification du nom de l'auteur effectuée.");
}

void modifier_annee_publication (Bibliotheque *b, int index) {
    int nouvelle_annee;
    while (1) {
        printf("Nouvelle année de publication (1450 - 2026) : ");
        if (scanf("%d", &nouvelle_annee) == 1) {
            vider_buffer(); // Toujours nettoyer le buffer après un scanf int

            if (nouvelle_annee >= 1450 && nouvelle_annee <= 2026) {
                b->livres[index].annee_publication = nouvelle_annee;
                printf("[Succès] Année mise à jour.\n");
                break;
            }
        } else {
            vider_buffer();
        }
        fprintf(stderr, "[Erreur] Année invalide. Veuillez recommencer.\n");
    }
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
                printf("1. ID\n2. Auteur\n3. Titre\n4. Annuler\nChoix : ");
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
                } else if (choix_rech == 4) {printf("Choix annulé.\n"); break;}

                if(idx != -1) {
                    afficher_livre(&biblio->livres[idx]);
                } else {
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
                        supprimer_livre(biblio, id);
                    } else {
                        fprintf(stderr, "ID invalide.\n");
                    }
                    break; 
                }
                case 2: {
                    printf("Auteur à supprimer : ");
                    char auteur[TAILLE_MAX_AUTEUR];
                    fgets(auteur, TAILLE_MAX_AUTEUR, stdin);
                    auteur[strcspn(auteur, "\n")] = 0;
                    supprimer_livre_par_auteur(biblio, auteur);
                    break; 
                }
                case 3: {
                    printf("Titre à supprimer : ");
                    char titre[TAILLE_MAX_TITRE];
                    fgets(titre, TAILLE_MAX_TITRE, stdin);
                    titre[strcspn(titre, "\n")] = 0;
                    supprimer_livre_par_titre(biblio, titre);
                    break; 
                }
                case 4: {
                    printf("ISBN à supprimer : ");
                    char isbn[TAILLE_MAX_ISBN];
                    fgets(isbn, TAILLE_MAX_ISBN, stdin);
                    isbn[strcspn(isbn, "\n")] = 0;
                    supprimer_livre_par_isbn(biblio, isbn);
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
                        radier_membre(biblio, id_a_radier);
                    } else {
                        fprintf(stderr, "ID invalide.\n");
                    }
                    vider_buffer();
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


int rechercher_livre_par_id (const Bibliotheque *biblio, int taille, int id) {
    if (biblio == NULL || biblio->livres == NULL) {
        fprintf(stderr, "Impossible de faire la recherche avec une bibliothèque ou des livres non initialisés\n");
        return -1;
    }
    Livre *livres = biblio->livres;

    for (int i = 0; i < taille; i++) {
        if (livres[i].id == id) return i;
    }
    return -1;
}

int rechercher_livre_par_auteur(const Bibliotheque *biblio, int taille, const char *auteur) {
    if (biblio == NULL || biblio->livres == NULL) {
        fprintf(stderr, "Erreur : bibliothèque non initialisée\n");
        return -1;
    }
    Livre *livres = biblio->livres;

    if(auteur == NULL || strlen(auteur) == 0) {
        fprintf(stderr, "Erreur : L'auteur ne doit pas être vide.");
        return -1;
    }
    char *auteur_lower = str_toLower(auteur, TAILLE_MAX_AUTEUR);
    int result = -1;

    for (int i = 0; i < taille; i++) {
        char *auteur_toLower = str_toLower(livres[i].auteur, TAILLE_MAX_AUTEUR);
        if (auteur_toLower && auteur_lower && strcmp(auteur_toLower, auteur_lower) == 0) {
            result = i;
            free(auteur_toLower);
            break;
        }
        free(auteur_toLower);
    }
    free(auteur_lower);
    return result;
}

int *rechercher_array_livre_par_auteur(const Bibliotheque *bibliotheque, int taille, const char *auteur) {
        if (bibliotheque == NULL || bibliotheque->livres == NULL) {
        fprintf(stderr, "Erreur : bibliothèque non initialisée\n");
        return NULL;
    }
    Livre *livres = bibliotheque->livres;

    if(auteur == NULL || strlen(auteur) == 0) {
        fprintf(stderr, "Erreur : L'auteur ne doit pas être vide.");
        return NULL;
    }
    char *auteur_lower = str_toLower(auteur, TAILLE_MAX_AUTEUR);
    int *result = NULL;
    int trouve = 0;

    for (int i = 0; i < taille; i++) {
        char *auteur_toLower = str_toLower(livres[i].auteur, TAILLE_MAX_AUTEUR);
        if (auteur_toLower && auteur_lower && strcmp(auteur_toLower, auteur_lower) == 0) {
            trouve++;
            // On alloue trouve + 1 pour garder de la place pour la sentinelle -1
            int *temp = realloc(result, sizeof(int) * (trouve + 1));
            if (temp == NULL) {
                fprintf(stderr, "Erreur de mémoire lors de la recherche par auteur.\n");
                free(auteur_toLower);
                free(auteur_lower);
                free(result);
                return NULL;
            }
            result = temp;
            result[trouve - 1] = i; // Stocke l'index correct (0-indexed)
            result[trouve] = -1;    // Marqueur de fin de tableau
        }
        free(auteur_toLower);
    }
    free(auteur_lower);
    return result;
}

int rechercher_livre_par_titre(const Bibliotheque *biblio, int taille, const char *titre) {
    if (biblio == NULL || biblio->livres == NULL) {
        fprintf(stderr, "Erreur : bibliothèque non initialisée\n");
        return -1;
    }
    Livre *livres = biblio->livres;

    if(titre == NULL || strlen(titre) == 0) {
        fprintf(stderr, "Erreur : Le titre ne doit pas être vide.");
        return -1;
    }
    char *titre_lower = str_toLower(titre, TAILLE_MAX_TITRE);
    int result = -1;

    for (int i = 0; i < taille; i++) {
        char *titre_toLower = str_toLower(livres[i].titre, TAILLE_MAX_TITRE);
        if (titre_toLower && titre_lower && strcmp(titre_toLower, titre_lower) == 0) {
            result = i;
            free(titre_toLower);
            break;
        }
        free(titre_toLower);
    }
    free(titre_lower);
    return result;
}

int rechercher_livre_par_isbn(const Bibliotheque *biblio, int taille, const char *isbn) {
    if (biblio == NULL || biblio->livres == NULL) {
        fprintf(stderr, "Erreur : bibliothèque non initialisée\n");
        return -1;
    }
    Livre *livres = biblio->livres;

    for (int i = 0; i < taille; i++) {
        if (strcmp(livres[i].isbn, isbn) == 0)
            return i;
    }
    return -1;
}

char *str_trim (char *str) {
    char *end;

    // Supprimer au début
    while(isspace((unsigned char)*str)) str++;

    // La chaine n' a que des caractères vides.
    if(*str == 0)
        return str;

    // Supprimer à la fin.
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Mettre le caractère de fin de chaine à la fin.
    *(end+1) = 0;

    return str;
}

int est_bissextile(int annee) {
    if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0)) {
        return 1;
    }
    return 0;
}

int valider_date_inscription_membre(const char *date) {
    // 1. Vérification du format de base (YYYY-MM-DD)
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return 0;
    }

    // 2. Extraction des valeurs
    int a, m, j;
    sscanf(date, "%d-%d-%d", &a, &m, &j);

    // 3. Validation des plages
    if (a < 2000 || a > 2026) return 0; // Cohérence (on est en 2026)
    if (m < 1 || m > 12) return 0;
    if (j < 1 || j > 31) return 0;

    // 4. Validation spécifique des mois
    int jours_par_mois[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Ajustement pour février (année bissextile)
    if (est_bissextile(a)) jours_par_mois[2] = 29;

    if (j > jours_par_mois[m]) {
        return 0; // Ex: 31 juin n'existe pas
    }

    return 1;
}

char *str_toLower(const char *str, int str_len) {
    if (str == NULL) return NULL;
    char *lower_str = malloc(str_len + 1);
    if (lower_str == NULL) return NULL;
    
    for (int i = 0; i < str_len; i++) {
        lower_str[i] = (char)tolower((unsigned char)str[i]);
        if (str[i] == '\0') break;
    }
    lower_str[str_len] = '\0';
    return lower_str;
}

int validate_Unique_Isbn(Bibliotheque *bibliotheque, const char *isbn) {
    if (bibliotheque == NULL || bibliotheque->livres == NULL) {
        fprintf(stderr, "Erreur : bibliothèque non initialisée\n");
        return 0;
    }
    for (int i = 0; i < bibliotheque->nb_livres; i++) {
        if (strcmp(bibliotheque->livres[i].isbn, isbn) == 0) {
            return 0; // ISBN déjà existant
        }
    }
    return 1; // ISBN unique
}