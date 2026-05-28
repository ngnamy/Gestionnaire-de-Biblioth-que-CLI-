#ifndef UTILITAIRE_H
#define UTILITAIRE_H

#include "livre.h"
#include "bibliotheque.h"

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

/**
 * @brief Fonction permettant de valider le format d'un numéro de téléphone.
 * @param numero Numéro de téléphone à valider.
 * @return retourne un entier 1 représentant le succès et 0 l'échec de validation.
 */
int valider_numero (const char *numero);

/**
 * @brief Fonction pour vérifier si une année est bissextile
 * @param year
 * @return Un entier 1 représentant le succès et 0 l'échec.
 */
int isLeapYear(int year);

/**
 * @brief Fonction qui permet de valider une date au format YYYY-MM-DD
 * @param date Un pointeur vers la date à valider
 * @return Un entier 1 représentant le succès et 0 l'échec de validation.
 */
int valider_date (const char *date);

/**
 * @brief Fonction pour rechercher dichotement un livre dans le tableau de livre.
 * @param livres Un pointeur vers la structure de livre.
 * @param id L'identifient du livre à rechercher.
 * @return Un entier representant l'index du livre dans le tableau ou -1 dans le cas où aucun livre n'a été trouvé.
 */
int recherche_dichotomique_livre (Livre *livres, int taille, int id);

/**
 * @brief Procédure qui permet de modifier l'ISBN d'un livre dans la bibliothèque.
 * @param b Un pointeur vers la structure de la bibliothèque.
 * @param index L'index du livre dans le tableau de livres de la bibliothèque dont l'ISBN doit être modifié.
 */
void modifier_isbn(Bibliotheque *b, int index);

/**
 * @brief Procédure qui permet de modifier le titre d'un livre dans la bibliothèque.
 * @param b Un pointeur vers la structure de la bibliothèque.
 * @param index L'index du livre dans le tableau de livres de la bibliothèque dont le titre doit être modifié.
 */
void modifier_titre (Bibliotheque *b, int index);

/**
 * @brief Procédure qui permet de modifier l'auteur d'un livre dans la bibliothèque.
 * @param b Un pointeur vers la structure de la bibliothèque.
 * @param index L'index du livre dans le tableau de livres de la bibliothèque dont l'auteur doit être modifié.
 */
void modifier_auteur (Bibliotheque *b, int index);

/**
 * @brief Procédure qui permet de modifier l'année de publication d'un livre dans la bibliothèque.
 * @param b Un pointeur vers la structure de la bibliothèque.
 * @param index L'index du livre dans le tableau de livres de la bibliothèque dont l'auteur doit être modifié.
 */
void modifier_annee_publication (Bibliotheque *b, int index);

/**
 * @brief Procédure permet d'afficher le menu de catalogue des livres
 * @param biblio .
 */
void menu_catalogue_livre (Bibliotheque *biblio);

/**
 * @brief Procédure permet d'afficher le menu de catalogue des livres
 * 
 */
void menu_gestion_membres (Bibliotheque *biblio);

/**
 * @brief Procédure permet d'afficher le menu emprunt et retour de livre
 */
void menu_gestion_emprunt_retour (Bibliotheque *biblio);

/**
 * @brief Fonction permetant de rechercher un livre dans la bibliothèque par son identifient. 
 * @param biblio Un pointeur vers la structure de la bibliothèque.
 * @param id Un entier représentant l'identifient du livre à rechercher.
 * @param taille Un entier représentant la taille du tableau de livre.
 * @return int Un entier representant l'index du livre dans le tableau ou -1 dans le cas où aucun livre n'a été trouvé.
 */
int rechercher_livre_par_id (const Bibliotheque *biblio, int taille, int id);

/**
 * @brief Fonction permet de rechercher un livre dans le tableau de livres en utilisant son titre.
 * @param b Un pointeur vers la structure de la bibliothèque.
 * @param titre Le titre du livre à rechercher.
 * @param taille Un entier représentant la taille du tableau de livre.
 * @return int Un entier representant l'index du livre dans le tableau ou -1 dans le cas où aucun livre n'a été trouvé.
 */
int rechercher_livre_par_titre(const Bibliotheque *biblio, int taille, const char *titre);

/**
 * @brief Fonction permet de rechercher un livre dans le tableau de livres en utilisant son auteur.
 * @param b Un pointeur vers la structure de la bibliothèque.
 * @param auteur L'auteur du livre à rechercher.
 * @param taille Un entier représentant la taille du tableau de livre.
 * @return int Un entier representant l'index du livre dans le tableau ou -1 dans le cas où aucun livre n'a été trouvé.
 */
int rechercher_livre_par_auteur(const Bibliotheque *biblio, int taille, const char *auteur);

/**
 * @brief Fonction permet de rechercher un livre dans le tableau de livres en utilisant son ISBN.
 * @param biblio Un pointeur vers la structure de la bibliothèque.
 * @param isbn L'ISBN du livre à rechercher.
 * @param taille Un entier représentant la taille du tableau de livre.
 * @return int Un entier representant l'index du livre dans le tableau ou -1 dans le cas où aucun livre n'a été trouvé.
 */
int rechercher_livre_par_isbn(const Bibliotheque *biblio, int taille, const char *isbn);

/**
 * @brief Fonction qui permet de supprimer des caractères vides en début et fin de chaine.
 * @param str Un pointeur vers la chaine de caractère.
 * @return Un pointeur vers la chaine de caractère après suppression des caractères vides en début et fin de chaine.
 */
char *str_trim (char *str);

/**
 * @brief Fonction qui permet de vérifier si une année est bissextile ou pas
 * @param annee Un entier représentant l'année à vérifier.
 * @return int Un entier 1 si l'année est bissextile 0 si elle ne l'est pas.
 */
int est_bissextile(int annee);

/**
 * @brief Cette fonction permet de valider une date d'inscription de membre.
 * @param date La date à vérifier.
 * @return int Un entier 1 si l'année est bissextile 0 si elle ne l'est pas. 
 */
int valider_date_inscription_membre(const char *date);

/**
 * @brief Fonction qui convertit une chaîne de caractères en minuscules.
 * @param str La chaîne de caractères à convertir.
 * @param str_len La longueur de la chaîne de caractères.
 * @return Un pointeur vers la nouvelle chaîne de caractères convertie en minuscules.
 */
char *str_toLower(const char *str, int str_len);

/**
 * @brief Fonction pour vérifier l'unicité d'un code isbn dans une bibliothèque, en parcourant le tableau de livres de la bibliothèque et en comparant l'ISBN de chaque livre avec l'ISBN fourni en paramètre. Si un livre avec le même ISBN est trouvé, la fonction retourne 0 pour indiquer que l'ISBN n'est pas unique. Si aucun livre avec le même ISBN n'est trouvé après avoir parcouru tout le tableau, la fonction retourne 1 pour indiquer que l'ISBN est unique dans la bibliothèque.
 * @param bibliotheque Un pointeur vers la structure de la bibliothèque.    
 * @param isbn L'ISBN à vérifier pour l'unicité.
 * @return int Un entier 1 si l'ISBN est unique dans la bibliothèque, 0 sinon.
 */
int validate_Unique_Isbn(Bibliotheque *bibliotheque, const char *isbn);

#endif