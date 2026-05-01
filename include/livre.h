#ifndef LIVRE_H
#define LIVRE_H

#define  TAILLE_MAX_TITRE 100
#define  TAILLE_MAX_AUTEUR 50

#include <stdio.h>

/**
 * Structure représentant un livre dans la bibliothèque.
 * Elle contient les informations suivantes :
 * - id : un identifiant unique pour chaque livre
 * - titre : le titre du livre
 * - auteur : le nom de l'auteur du livre
 * - annee_publication : l'année de publication du livre
 * - prix : le prix du livre
 * - quantite : la quantité de ce livre disponible dans la bibliothèque
 */
typedef struct {
    int id;
    char titre[TAILLE_MAX_TITRE];
    char auteur[TAILLE_MAX_AUTEUR];
    int annee_publication;
    float prix;
    int quantite;
} Livre;

/**
 * Fonction pour saisir les informations d'un livre.
 * Elle prend en paramètre un pointeur vers une structure Livre
 * et remplit les champs de cette structure avec les données saisies par l'utilisateur.
 * @param livre Un pointeur vers une structure Livre à remplir avec les données saisies par l'utilisateur.
 * @return void
 */
void saisir_livre(Livre *livre);

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
 * Fonction pour sauvegarder les informations d'un livre dans un fichier.
 * Elle prend en paramètre un pointeur vers une structure Livre et un pointeur vers un fichier ouvert en écriture, et écrit les champs de la structure Livre dans le fichier de manière formatée.
 * @param livre Un pointeur vers une structure Livre dont les informations seront sauvegardées dans le fichier.
 * @param fichier Un pointeur vers un fichier ouvert en écriture où les informations du livre seront sauvegardées.
 * @return void
 */
void sauvegarder_livre(const Livre *livre, FILE *fichier);

#endif // LIVRE_H