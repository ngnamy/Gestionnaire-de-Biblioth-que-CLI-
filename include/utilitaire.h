#ifndef UTILITAIRE_H
#define UTILITAIRE_H

#define DUREE_EMPRUNT 11

/**
 * @brief Fonction qui renvoi l'année actuelle
 * @return int Un entier qui représente l'année en question
 */
int annee_actuelle ();

/**
 * @brief Fonction qui calcul la date échéance de remise de livre emprunté à la bibliothèque
 * 
 * @return void
 */
void calculer_echeance (char *date_echeance);

/**
 * @brief Fonction pour vider le buffer d'entrée standard.
 * Elle est utilisée pour éviter les problèmes de saisie lors de l'utilisation de fonctions de lecture comme scanf ou fgets, en consommant tous les caractères restants dans le buffer d'entrée jusqu'à ce qu'un saut de ligne soit rencontré ou que le buffer soit vide.
 * @return void
 */
void vider_buffer();

#endif