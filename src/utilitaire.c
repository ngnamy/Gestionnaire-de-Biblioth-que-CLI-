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
    strncpy(b->livres[index].titre, nouveau_titre, TAILLE_MAX_TITRE - 1);
    b->livres[index].titre[TAILLE_MAX_TITRE - 1] = '\0';
}

void modifier_auteur (Bibliotheque *b, int index) {
    char nouveau_auteur[TAILLE_MAX_AUTEUR];
    printf("Nouvel auteur : ");
    fgets(nouveau_auteur, TAILLE_MAX_AUTEUR, stdin);
    nouveau_auteur[strcspn(nouveau_auteur, "\n")] = '\0'; // supprime le saut de ligne
    strncpy(b->livres[index].auteur, nouveau_auteur, TAILLE_MAX_AUTEUR - 1);
    b->livres[index].auteur[TAILLE_MAX_AUTEUR - 1] = '\0';
}

void modifier_annee_publication (Bibliotheque *b, int index) {
    int nouvelle_annee;
    printf("Nouvelle année de publication : ");
    if (scanf("%d", &nouvelle_annee) != 1) {
        fprintf(stderr, "Erreur : L'année doit être un entier.\n");
        vider_buffer();
        return;
    }
    b->livres[index].annee_publication = nouvelle_annee;
}