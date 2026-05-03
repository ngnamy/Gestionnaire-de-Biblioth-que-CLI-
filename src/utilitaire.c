
#include <time.h>
#include "../include/utilitaire.h"

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