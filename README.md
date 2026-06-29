# Gestionnaire de Bibliothèque (CLI)

Bienvenue dans le projet **Gestionnaire de Bibliothèque** ! Il s'agit d'une application en ligne de commande (CLI) écrite en langage C, permettant de gérer facilement une bibliothèque (livres, membres, emprunts et retours).

## Fonctionnalités 🚀

- **Catalogue de livres** :
  - Ajouter, modifier, rechercher ou supprimer un livre (par ID, Auteur, Titre ou ISBN).
  - Affichage de tous les livres avec un système de pagination.
  - Tri du catalogue par ID, Titre ou Auteur.
- **Gestion des membres** :
  - Inscription, modification, radiation.
  - Suivi des membres et de leurs emprunts actifs.
- **Gestion des emprunts** :
  - Emprunter un livre (mise à jour automatique de la disponibilité).
  - Retourner un livre.
  - Liste des livres en retard.
- **Persistance des données** :
  - Les données sont sauvegardées et chargées automatiquement à l'aide de fichiers structurés (`livres.dat`, `membres.dat`, `emprunts.dat`).
  - Historique complet des transactions conservé dans `historique.dat`.

## Prérequis 🛠️

Pour compiler et exécuter le projet, vous aurez besoin de :
- Un compilateur C (par exemple `gcc`).
- `make` pour utiliser le Makefile fourni.

## Compilation et Exécution 💻

Le projet est livré avec un **Makefile** simplifié pour vous faciliter la vie.

Pour compiler et lancer le programme en une seule étape :
```bash
make run
```

Si vous souhaitez uniquement compiler (génère l'exécutable `start` ou `start.exe`) :
```bash
make all
```

Pour nettoyer les fichiers compilés (`*.o` et `.exe`) :
```bash
make clean
```

## Structure du Projet 📁

- `src/` : Contient tous les fichiers sources (`.c`).
  - `main.c` : Point d'entrée de l'application.
  - `menu.c` : Gestion complète des interfaces textuelles et menus de l'utilisateur.
  - `bibliotheque.c` : Fonctions principales pour manipuler les données globales et la persistance.
  - `livre.c` & `membres.c` : Logique spécifique liée aux livres et aux membres.
  - `utilitaire.c` : Fonctions utilitaires (recherche, chaînes de caractères, saisie utilisateur robuste).
- `include/` : Contient tous les fichiers d'en-têtes (`.h`).

## Architecture Technique 🧠

- **Mémoire Dynamique** : Les listes de livres et de membres utilisent des tableaux alloués dynamiquement (avec `malloc` et `realloc`), ce qui permet au gestionnaire de ne pas être limité par une taille fixe !
- **Robuste aux erreurs** : Les saisies (`scanf`, `fgets`) sont validées pour éviter les crashs lorsque l'utilisateur entre du texte au lieu de nombres. Un système de "vidage de buffer" est utilisé de manière systématique.
- **Formats de données** : Le stockage utilise un délimiteur de type pipe (`|`) ce qui permet de stocker des chaînes avec des espaces sans corrompre le fichier de sauvegarde.

---
*Projet personnel développé en langage C.*
