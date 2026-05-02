#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include "livre.h"
#include "membres.h"

#define MAX_TAILLE_FICHIER 50
#define MAX_EMPRUNTS_MEMBRE 3

/**
 * @brief Structure représentant une bibliothèque.
 * Elle contient les informations suivantes :
 * @param livres Un tableau dynamique de structures Livre représentant les livres disponibles dans la bibliothèque.
 * @param nb_livres Le nombre de livres actuellement présents dans la bibliothèque.
 * @param capacite_livres La capacité maximale du tableau de livres, utilisée pour gérer la mémoire dynamique.
 * @param membres Un tableau dynamique de structures Membre représentant les membres inscrits dans la bibliothèque.
 * @param nb_membres Le nombre de membres actuellement inscrits dans la bibliothèque.
 * @param capacite_membres La capacité maximale du tableau de membres, utilisée pour gérer la mémoire dynamique.
 * @param fichier_livres Le nom du fichier où les informations des livres sont sauvegardées ou chargées.
 * @param fichier_membres Le nom du fichier où les informations des membres sont sauvegardées ou chargées.
 */
typedef struct {
    Livre *livres;
    int nb_livres;
    int capacite_livres;

    Membre *membres;
    int nb_membres;
    int capacite_membres;
    
    char fichier_livres[MAX_TAILLE_FICHIER];
    char fichier_membres[MAX_TAILLE_FICHIER];
} Bibliotheque;

/**
 * @brief Fonction pour initialiser une bibliothèque.
 * Elle prend en paramètre un pointeur vers une structure Bibliotheque, des entiers représentant les capacités initiales pour les tableaux de livres et de membres, alloue la mémoire nécessaire pour les tableaux de livres et de membres, initialise le nombre de livres et de membres à zéro, et configure les noms des fichiers pour la sauvegarde et le chargement des informations de la bibliothèque.
 * @param bibliotheque Un pointeur vers une structure Bibliotheque à initialiser.
 * @param capacite_livres Un entier représentant la capacité initiale du tableau de livres de la bibliothèque.
 * @param capacite_membres Un entier représentant la capacité initiale du tableau de membres de la bibliothèque.
 * @return void
 */
void initialiser_bibliotheque(Bibliotheque *bibliotheque, int capacite_livres, int capacite_membres);

/**
 * @brief Fonction pour supprimer tous les livres de la bibliothèque.
 * Elle prend en paramètre un pointeur vers une structure Bibliotheque et libère la mémoire allouée pour le tableau de livres, initialise le nombre de livres à zéro, et réinitialise la capacité du tableau.
 * @param bibliotheque Un pointeur vers une structure Bibliotheque dont les livres seront supprimés.
 * @return void
 */
void detruire_bibliotheque(Bibliotheque *bibliotheque);

/**
 * @brief Fonction pour ajouter un livre à la bibliothèque.
 * Elle prend en paramètre un pointeur vers une structure Bibliotheque et une structure Livre représentant le nouveau livre à ajouter, vérifie si la capacité du tableau de livres est suffisante pour ajouter le nouveau livre, et si nécessaire, réalloue la mémoire pour augmenter la capacité du tableau de livres avant d'ajouter le nouveau livre et d'incrémenter le nombre de livres dans la bibliothèque.
 * @param bibliotheque Un pointeur vers une structure Bibliotheque à laquelle le nouveau livre sera ajouté.
 * @param nouveau_livre Une structure Livre représentant le nouveau livre à ajouter à la bibliothèque.
 * @return void
 */
void ajouter_livre(Bibliotheque *bibliotheque, Livre nouveau_livre);

/**
 * @brief Fonction pour afficher les informations de tous les livres présents dans la bibliothèque.
 * Elle prend en paramètre un pointeur vers une structure Bibliotheque et affiche les informations de chaque livre présent dans le tableau de livres de manière formatée, en utilisant la fonction afficher_livre pour afficher les détails de chaque livre.
 * @param bibliotheque Un pointeur vers une structure Bibliotheque dont les livres seront affichés.
 * @return void
 */
void afficher_bibliotheque(const Bibliotheque *bibliotheque);

/**
 * @brief Fonction pour rechercher un livre dans la bibliothèque par son identifiant.
 * Elle prend en paramètre un pointeur vers une structure Bibliotheque et un entier représentant l'identifiant du livre à rechercher, parcourt le tableau de livres de la bibliothèque pour trouver un livre dont l'identifiant correspond à celui recherché, et retourne l'index du livre trouvé dans le tableau de livres ou -1 si aucun livre avec l'identifiant spécifié n'est trouvé.
 * @param bibliotheque Un pointeur vers une structure Bibliotheque dans laquelle le livre sera recherché.
 * @param id L'identifiant du livre à rechercher dans la bibliothèque.
 * @return L'index du livre trouvé dans le tableau de livres ou -1 si aucun livre avec l'identifiant spécifié n'est trouvé.
 */
int rechercher_livre(const Bibliotheque *bibliotheque, int id);

/**
 * @brief Fonction pour modifier les informations d'un livre dans la bibliothèque.
 * Elle prend en paramètre un pointeur vers une structure Bibliotheque et un entier représentant l'identifiant du livre à modifier, et permet de mettre à jour les informations du livre correspondant.
 * @param bibliotheque Un pointeur vers une structure Bibliotheque dans laquelle le livre sera modifié.
 * @param id L'identifiant du livre à modifier dans la bibliothèque.
 * @return void
 */
void modifier_livre(Bibliotheque *bibliotheque, int id);

/**
 * @brief Fonction pour supprimer un livre de la bibliothèque.
 * Elle prend en paramètre un pointeur vers une structure Bibliotheque et un entier représentant l'identifiant du livre à supprimer, et supprime le livre correspondant de la bibliothèque en réorganisant le tableau de livres pour combler l'espace laissé par le livre supprimé.
 * @param bibliotheque Un pointeur vers une structure Bibliotheque dans laquelle le livre sera supprimé.
 * @param id L'identifiant du livre à supprimer de la bibliothèque.
 * @return void
 */
void supprimer_livre(Bibliotheque *bibliotheque, int id);

/**
 * @brief Fonction pour trier les livres de la bibliothèque par ordre alphabétique de leur titre.
 * Elle prend en paramètre un pointeur vers une structure Bibliotheque et trie le tableau de livres de la bibliothèque en utilisant la fonction comparer_livres pour comparer les titres des livres et les réorganiser dans l'ordre alphabétique.
 * @param bibliotheque Un pointeur vers une structure Bibliotheque dont les livres seront triés.
 * @return void
 */
void trier_bibliotheque(Bibliotheque *bibliotheque);

/**
 * @brief Fonction pour sauvegarder les informations de la bibliothèque dans un fichier.
 * Elle prend en paramètre un pointeur vers une structure Bibliotheque et écrit les informations de tous les livres présents dans la bibliothèque dans un fichier spécifié par le champ nom_fichier de la structure Bibliotheque, en utilisant la fonction sauvegarder_livre pour écrire les détails de chaque livre dans le fichier de manière formatée.
 * @param bibliotheque Un pointeur vers une structure Bibliotheque dont les informations seront sauvegardées dans un fichier.
 * @return void
 */
void sauvegarder_bibliotheque(const Bibliotheque *bibliotheque);

/**
 * @brief Fonction pour charger les informations de la bibliothèque à partir d'un fichier.
 * Elle prend en paramètre un pointeur vers une structure Bibliotheque et lit les informations de tous les livres présents dans un fichier spécifié par le champ nom_fichier de la structure Bibliotheque, en utilisant la fonction saisir_livre pour remplir les détails de chaque livre à partir des données lues dans le fichier, et ajoute chaque livre chargé à la bibliothèque en utilisant la fonction ajouter_livre.
 * @param bibliotheque Un pointeur vers une structure Bibliotheque dans laquelle les informations seront chargées.
 * @return void
 */
void charger_bibliotheque(Bibliotheque *bibliotheque);

/**
 * @brief Fonction pour effectuer un emprunt de livre dans la bibliothèque.
 * Elle prend en paramètre un pointeur vers une structure Bibliotheque, un entier représentant l'identifiant du livre à emprunter, et un entier représentant l'identifiant du membre qui emprunte le livre, vérifie si le livre est disponible pour l'emprunt, met à jour les informations du livre pour indiquer qu'il est emprunté et associe l'identifiant du membre emprunteur au livre, et gère les cas où le livre n'est pas disponible ou où le membre a atteint la limite d'emprunts actifs.
 * @param bibliotheque Un pointeur vers une structure Bibliotheque dans laquelle l'emprunt sera effectué.
 * @param id_livre L'identifiant du livre à emprunter dans la bibliothèque.
 * @param id_membre L'identifiant du membre qui emprunte le livre dans la bibliothèque.
 * @return void
 */
void effectuer_emprunt(Bibliotheque *bibliotheque, int id_livre, int id_membre);

/**
 * @brief Fonction pour effectuer un retour de livre dans la bibliothèque.
 * Elle prend en paramètre un pointeur vers une structure Bibliotheque et un entier représentant l'identifiant du livre à retourner, vérifie si le livre est actuellement emprunté, met à jour les informations du livre pour indiquer qu'il est disponible et dissocie l'identifiant du membre emprunteur du livre, et gère les cas où le livre n'est pas actuellement emprunté ou où l'identifiant du livre spécifié n'existe pas dans la bibliothèque.
 * @param bibliotheque Un pointeur vers une structure Bibliotheque dans laquelle le retour sera effectué.
 * @param id_livre L'identifiant du livre à retourner dans la bibliothèque.
 * @return void
 */
void effectuer_retour(Bibliotheque *bibliotheque, int id_livre);

/**
 * @brief Fonction pour lister les livres en retard.
 * Elle prend en paramètre un pointeur vers une structure Bibliotheque et une chaîne de caractères représentant la date actuelle, et affiche les informations des livres qui sont en retard de retour.
 * @param bibliotheque Un pointeur vers une structure Bibliotheque contenant les livres à vérifier.
 * @param date_actuelle Une chaîne de caractères représentant la date actuelle au format "YYYY-MM-DD".
 * @return void
 */
void lister_livres_en_retard(const Bibliotheque *bibliotheque, const char *date_actuelle);

/**
 * @brief Fonction pour inscrire un nouveau membre dans la bibliothèque.
 * Elle prend en paramètre un pointeur vers une structure Bibliotheque et permet d'ajouter un nouveau membre à la bibliothèque.
 * @param bibliotheque Un pointeur vers une structure Bibliotheque dans laquelle le nouveau membre sera inscrit.
 * @return void
 */
void inscrire_membre(Bibliotheque *bibliotheque);

/**
 * @brief Fonction pour rechercher un membre dans la bibliothèque.
 * Elle prend en paramètre un pointeur vers une structure Bibliotheque et un entier représentant l'identifiant du membre à rechercher, et retourne l'index du membre ou -1 si non trouvé.
 * @param bibliotheque Un pointeur vers une structure Bibliotheque contenant les membres à rechercher.
 * @param id_membre L'identifiant du membre à rechercher dans la bibliothèque.
 * @return L'index du membre trouvé dans le tableau de membres ou -1 si aucun membre avec l'identifiant spécifié n'est trouvé.
 */
int rechercher_membre(const Bibliotheque *bibliotheque, int id_membre);

/**
 * @brief Fonction pour radier un membre de la bibliothèque.
 * Elle prend en paramètre un pointeur vers une structure Bibliotheque et un entier représentant l'identifiant du membre à radier, et supprime le membre correspondant de la bibliothèque en réorganisant les données des membres pour combler l'espace laissé par le membre radié, et gère les cas où le membre à radier n'existe pas ou a des emprunts actifs en
 * @param bibliotheque Un pointeur vers une structure Bibliotheque.
 * @param id_membre L'identifiant du membre à radier.
 * @return void
 */
void radier_membre(Bibliotheque *bibliotheque, int id_membre);
#endif