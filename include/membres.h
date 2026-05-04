#ifndef MEMBRES_H
#define MEMBRES_H

#include <stdio.h>

#define MAX_NOM_MEMBRE 50
#define MAX_TEL_MEMBRE 11
#define TAILLE_DATE 12 // Changed from 11 to 12 to accommodate "YYYY-MM-DD\n\0"

/**
 * @brief Structure représentant un membre de la bibliothèque.
 * Elle contient les informations suivantes :
 * @param id_membre Un identifiant unique pour chaque membre de la bibliothèque, utilisé pour différencier les membres et faciliter la gestion des emprunts et des retours.
 * @param nom Un tableau de caractères de taille 50 représentant le nom du membre, utilisé pour afficher le nom du membre dans la bibliothèque et faciliter la recherche et l'identification des membres par les utilisateurs.
 * @param telephone Un tableau de caractères de taille 20 représentant le numéro de téléphone du membre, utilisé pour contacter le membre en cas de besoin, notamment pour les notifications liées aux emprunts et aux retours des livres.
 * @param date_inscription Un tableau de caractères de taille 11 représentant la date d'inscription du membre au format "YYYY-MM-DD", utilisé pour suivre la date à laquelle le membre s'est inscrit à la bibliothèque et gérer les informations liées à son compte.
 * @param nb_emprunts_actifs Un entier représentant le nombre d'emprunts actifs que le membre a actuellement, utilisé pour limiter le nombre d'emprunts qu'un membre peut avoir en même temps et gérer les règles d'emprunt dans la bibliothèque.
 */
typedef struct {
    int id_membre;
    char nom[MAX_NOM_MEMBRE];
    char telephone[MAX_TEL_MEMBRE];
    char date_inscription[TAILLE_DATE];
    int nb_emprunts_actifs;
} Membre;

/**
 * @brief Fonction pour saisir les informations d'un membre.
 * Elle prend en paramètre un pointeur vers une structure Membre et un entier représentant le prochain identifiant de membre à attribuer, remplit les champs de la structure Membre avec les données saisies par l'utilisateur, en utilisant le prochain identifiant de membre pour attribuer un identifiant unique au nouveau membre, et initialise le nombre d'emprunts actifs du membre à zéro.
 * @param membre Un pointeur vers une structure Membre à remplir avec les données saisies par l'utilisateur.
 * @param prochain_id Un entier représentant le prochain identifiant de membre à attribuer au nouveau membre.
 * @return void
 */
void saisir_membre(Membre *membre, int prochain_id);

/**
 * @brief Fonction pour afficher les informations d'un membre.
 * Elle prend en paramètre un pointeur vers une structure Membre et affiche les champs de cette structure de manière formatée, en affichant l'identifiant du membre, son nom, et le nombre d'emprunts actifs qu'il a actuellement.
 * @param membre Un pointeur vers une structure Membre dont les informations seront affichées.
 * @return void
 */
void afficher_membre(const Membre *membre);

/**
 * @brief Fonction pour sauvegarder les informations d'un membre dans un fichier.
 * Elle prend en paramètre un pointeur vers une structure Membre et un pointeur vers un fichier ouvert en écriture.
 * @param membre Un pointeur vers la structure Membre à sauvegarder.
 * @param fichier Un pointeur vers le fichier ouvert (en mode binaire "ab" ou "wb").
 * @return void
 */
void sauvegarder_membre(const Membre *membre, FILE *fichier);

#endif