#ifndef MENU_H
#define MENU_H

#include "bibliotheque.h"

/**
 * @brief Menu principal pour la gestion du catalogue des livres.
 * @param biblio Pointeur vers la bibliothèque.
 */
void menu_catalogue_livre(Bibliotheque *biblio);

/**
 * @brief Menu principal pour la gestion des membres.
 * @param biblio Pointeur vers la bibliothèque.
 */
void menu_gestion_membres(Bibliotheque *biblio);

/**
 * @brief Menu principal pour la gestion des emprunts et retours.
 * @param biblio Pointeur vers la bibliothèque.
 */
void menu_gestion_emprunt_retour(Bibliotheque *biblio);

#endif
