#ifndef LIVRE_H
#define LIVRE_H

#define  TAILLE_MAX_TITRE 100
#define  TAILLE_MAX_AUTEUR 50
#define  TAILLE_MAX_DATE 11
#define  TAILLE_MAX_ISBN 14

#include <stdio.h>

/**
 * @brief Structure représentant un livre de la bibliothèque.
 * Elle contient les informations suivantes :
 * @param id Un identifiant unique pour chaque livre de la bibliothèque, utilisé pour différencier les livres et faciliter la gestion des emprunts et des retours.
 * @param isbn Un tableau de caractères de taille 20 représentant le numéro ISBN du livre, utilisé pour identifier de manière unique le livre dans la bibliothèque et faciliter la recherche et l'organisation des livres.
 * @param titre Un tableau de caractères de taille 100 représentant le titre du livre, utilisé pour afficher le titre du livre dans la bibliothèque et faciliter la recherche et l'identification des livres par les utilisateurs.
 * @param auteur Un tableau de caractères de taille 50 représentant le nom de l'auteur du livre, utilisé pour afficher le nom de l'auteur dans la bibliothèque et faciliter la recherche et l'identification des livres par les utilisateurs.
 * @param annee_publication Un entier représentant l'année de publication du livre, utilisé pour afficher l'année de publication dans la bibliothèque et faciliter la recherche et l'identification des livres par les utilisateurs.
 * @param est_emprunte Un entier représentant si le livre est actuellement emprunté (1) ou disponible (0), utilisé pour gérer l'état d'emprunt du livre dans la bibliothèque et éviter les conflits lors des emprunts et des retours.
 * @param id_emprunteur Un entier représentant l'identifiant du membre qui a emprunté le livre (ou -1 si le livre n'est pas emprunté), utilisé pour suivre quel membre a emprunté le livre et faciliter la gestion des emprunts et des retours dans la bibliothèque.
 * @param date_echeance Un tableau de caractères de taille 11 représentant la date d'échéance du retour du livre au format "YYYY-MM-DD", utilisé pour suivre la date limite de retour du livre et gérer les notifications liées aux retours dans la bibliothèque.
 */
typedef struct Livre {
    int id;
    char isbn[TAILLE_MAX_ISBN];
    char titre[TAILLE_MAX_TITRE];
    char auteur[TAILLE_MAX_AUTEUR];
    int annee_publication;

    int est_emprunte;
    int id_emprunteur;
    char date_echeance[TAILLE_MAX_DATE];
} Livre;

/**
 * @brief Fonction pour saisir les informations d'un livre.
 * Elle prend en paramètre un pointeur vers une structure Livre
 * et remplit les champs de cette structure avec les données saisies par l'utilisateur.
 * @param livre Un pointeur vers une structure Livre à remplir avec les données saisies par l'utilisateur.
 * @param prochain_id Un entier qui représente le prochain identifiant
 * @return void
 */
void saisir_livre(Livre *livre, int prochain_id);

/**
 * Fonction pour afficher les informations d'un livre.
 * Elle prend en paramètre un pointeur vers une structure Livre
 * et affiche les champs de cette structure de manière formatée.
 * @param livre Un pointeur vers une structure Livre dont les informations seront affichées.
 * @return void
 */
void afficher_livre(const Livre *livre);

/**
 * Fonction pour comparer deux livres.
 * Elle prend en paramètre deux pointeurs vers des structures Livre
 * et compare les titres des livres de manière lexicographique.
 * @param livre_a Un pointeur vers la première structure Livre à comparer.
 * @param livre_b Un pointeur vers la deuxième structure Livre à comparer.
 * @return Un entier négatif si le titre du livre a est inférieur au titre du livre b,
 *         zéro si les titres sont égaux, ou un entier positif si le titre du livre a est supérieur au titre du livre b.
 */
int comparer_livres(const Livre *livre_a, const Livre *livre_b);

/**
 * @brief Fonction pour sauvegarder les informations d'un livre dans un fichier.
 * Elle prend en paramètre un pointeur vers une structure Livre et un pointeur vers un fichier ouvert en écriture, et écrit les champs de la structure Livre dans le fichier de manière formatée.
 * @param livre Un pointeur vers une structure Livre dont les informations seront sauvegardées dans le fichier.
 * @param fichier Un pointeur vers un fichier ouvert en écriture où les informations du livre seront sauvegardées.
 * @return void
 */
void sauvegarder_livre(const Livre *livre, FILE *fichier);

/**
 * @brief Fonction pour vérifier si un ISBN est valide.
 * Elle prend en paramètre un pointeur vers une chaîne de caractères représentant un ISBN, et retourne 1 si l'ISBN est valide, 0 sinon.
 * @param isbn Un pointeur vers une chaîne de caractères représentant un ISBN.
 * @param type Un entier représentant le type d'ISBN à valider (0 pour ISBN-10, 1 pour ISBN-13).
 * @return 1 si l'ISBN est valide, 0 sinon.
 */
int est_isbn_valide(const char *isbn, int type);

#endif // LIVRE_H
