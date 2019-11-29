/* <--------------- Programme principal  ---------------> */

#include <stdio.h>
#include <stdlib.h>
#include "tp4_abr.h"
#include "tp4_abr.c"

#define NOMRE_CHOIX_MENU 8
const char* CHOIX_MENU_TEXTE[NOMRE_CHOIX_MENU] = {
    "Créer un ABR (Arbre Binaire de Recherche",
    "Afficher tous les réservations",
    "Ajouter une réservation",
    "Modifier une réservation",
    "Supprimer une réservation",
    "Afficher les réservations d'une entreprise",
    "Supprimer l'arbre",
    "Quitter",
};

int main() {
    /* <--------------- Variables  ---------------> */

    // Compteur
    int i,j;

    // Choix menu
    int choix_menu;
 
    /* <--------------- Programme principal utilisateur  ---------------> */

    puts("                _                     _     _             _               \n     /\\        | |                   | |   (_)           (_)              \n    /  \\   _ __| |__  _ __ ___  ___  | |__  _ _ __   __ _ _ _ __ ___  ___ \n   / /\\ \\ | '__| '_ \\| '__/ _ \\/ __| | '_ \\| | '_ \\ / _` | | '__/ _ \\/ __|\n  / ____ \\| |  | |_) | | |  __/\\__ \\ | |_) | | | | | (_| | | | |  __/\\__ \\\n /_/    \\_\\_|  |_.__/|_|  \\___||___/ |_.__/|_|_| |_|\\__,_|_|_|  \\___||___/");
    /*
                _                     _     _             _               
     /\        | |                   | |   (_)           (_)              
    /  \   _ __| |__  _ __ ___  ___  | |__  _ _ __   __ _ _ _ __ ___  ___ 
   / /\ \ | '__| '_ \| '__/ _ \/ __| | '_ \| | '_ \ / _` | | '__/ _ \/ __|
  / ____ \| |  | |_) | | |  __/\__ \ | |_) | | | | | (_| | | | |  __/\__ \
 /_/    \_\_|  |_.__/|_|  \___||___/ |_.__/|_|_| |_|\__,_|_|_|  \___||___/
    */                                                                          

    // Boucle principale                                                                          
    while (choix_menu != 8) {
        choix_menu = 0; // Réinitialisation

        // Affichage menu
        printf("Que voulez-vous faire ?\n");
        for (i = 1; i < NOMRE_CHOIX_MENU + 1; i++) {
            printf("%d. %s\n", i, CHOIX_MENU_TEXTE[i-1]);
        }
        
        // Entrée du choix et validation
        choix_menu = validation__entree_int(choix_menu, 1, NOMRE_CHOIX_MENU + 1);

        switch (choix_menu) {
            case 1:
            // Créer un ABR
                break;
            case 2:
            // Afficher tous les réservations
                break;
            case 3:
            // Ajouter une réservation
                break;
            case 4:
            // Modifier une réservation
                break;
            case 5:
            // Supprimer une réservation
                break;
            case 6:
            // Afficher les réservations d'une entreprise
                break;
            case 7:
            // Supprimer l'arbre
                break;    
            default:
                break;
        }
        return 0;
    }

}
