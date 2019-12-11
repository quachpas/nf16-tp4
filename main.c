/* <--------------- Programme principal  ---------------> */
#include "tp4_abr.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    // Arbre
    int boolArbre = 0; //0 s'il n'y a pas d'abre créer, 1 s'il y a un arbre créer
    T_Arbre ABR;
    //Variables utilisateur
    int idEntreprise;
    char jour[3], mois[3];
    char dateFormatee[5];
    T_Inter intervalleReservation, nouvelIntervalle;
 
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
        choix_menu = validation_entree_int(choix_menu, 1, NOMRE_CHOIX_MENU + 1);

        switch (choix_menu) {
            case 1:
            // Créer un ABR
                afficher_infos_choix_menu(choix_menu, CHOIX_MENU_TEXTE);
                if (!boolArbre) {
                    ABR = NULL;
                    boolArbre = 1;
                    printf("L'arbre a ete créé.\n");
                }
                else{
                    printf("L'arbre a déjà été créér.\n");
                }
                break;
            case 2:
            // Afficher tous les réservations
                afficher_infos_choix_menu(choix_menu, CHOIX_MENU_TEXTE);
                if (boolArbre) {
                    affiche_abr(ABR);
                }
                else{
                    printf("Aucun arbre n'a été créé.\n");
                }
                break;
            case 3:
            // Ajouter une réservation
                dateFormatee[0] = '\0';
                mois[0] = '\0';
                jour[0] = '\0';
                
                afficher_infos_choix_menu(choix_menu, CHOIX_MENU_TEXTE);
                if (boolArbre) {
                    do {
                        printf("Veuillez saisir l'ID de l'entreprise: \t");
                        scanf("%d", &idEntreprise);
                        if (idEntreprise < 0) {
                            printf("Veuillez saisir un id d'entreprise supérieur ou égal à 0");
                        }
                        //Vérifie que l'utilisateur indique une bonne valeur idEntreprise
                    } while (idEntreprise <0);
                    
                    do {
                        printf("Veuillez saisir le jour de debut de la reservation (JJ MM): \t");
                        scanf("%s %s", jour, mois);
                        if (atoi(jour)> 31 && atoi(jour)<0 && atoi(mois)<0 && atoi(mois)>12) {
                            printf("Veuillez saisir une date valide.\n");
                        }
                        //Verification entrée Début Reservation
                    } while (atoi(jour)> 31 && atoi(jour)<0 && atoi(mois)<0 && atoi(mois)>12);
                    
                    if (mois[0] == '0') {
                        mois[0] = mois[1];
                        mois[1] = '\0';
                        //Reformatage de la date
                    }
                    strcat(dateFormatee, mois);
                    strcat(dateFormatee, jour);
                    //Assemblage de la date
                    intervalleReservation.borne_inf = atoi(dateFormatee);
                    dateFormatee[0] = '\0';
                    mois[0] = '\0';
                    jour[0] = '\0';
                    
                    do {
                        printf("Veuillez saisir le jour de fin de la reservation (JJ MM): \t");
                        scanf("%s %s", jour, mois);
                        if (atoi(jour)> 31 && atoi(jour)<0 && atoi(mois)<0 && atoi(mois)>12) {
                            printf("Veuillez saisir une date valide.\n");
                        }
                        //Validation entrée fin Reservation
                    } while (atoi(jour)> 31 && atoi(jour)<0 && atoi(mois)<0 && atoi(mois)>12);
                    //Assemblage de la date
                    strcat(dateFormatee, mois);
                    strcat(dateFormatee, jour);
                    intervalleReservation.borne_sup = atoi(dateFormatee);
                    
                    ajouter_noeud(&ABR, creer_noeud(idEntreprise, intervalleReservation));
                    printf("Le noeud a bien été créé.\n");
                }
                else{
                    printf("L'arbre n'a pas été créé pour l'instant !\n");
                }
                break;
            case 4:
            // Modifier une réservation
                if (boolArbre) {
                    dateFormatee[0] = '\0';
                    mois[0] = '\0';
                    jour[0] = '\0';
                    do {
                        printf("Veuillez saisir l'ID de l'entreprise: \t");
                        scanf("%d", &idEntreprise);
                        if (idEntreprise < 0) {
                            printf("Veuillez saisir un id d'entreprise supérieur ou égal à 0");
                        }
                        //Vérifie que l'utilisateur indique une bonne valeur idEntreprise
                    } while (idEntreprise <0);
/* -----------------------------Saisie de l'intervalle de base du noeud ------------------------------*/
                    printf("SAISIE DE L'INTERVALLE A MODIFIER: \n");
                    do {
                        printf("Veuillez saisir le jour de debut de la reservation (JJ MM): \t");
                        scanf("%s %s", jour, mois);
                        if (atoi(jour)> 31 && atoi(jour)<0 && atoi(mois)<0 && atoi(mois)>12) {
                            printf("Veuillez saisir une date valide.\n");
                        }
                        //Verification entrée Début Reservation
                    } while (atoi(jour)> 31 && atoi(jour)<0 && atoi(mois)<0 && atoi(mois)>12);
                    
                    if (mois[0] == '0') {
                        mois[0] = mois[1];
                        mois[1] = '\0';
                        //Reformatage de la date
                    }
                    strcat(dateFormatee, mois);
                    strcat(dateFormatee, jour);
                    //Assemblage de la date
                    intervalleReservation.borne_inf = atoi(dateFormatee);
                    dateFormatee[0] = '\0';
                    mois[0] = '\0';
                    jour[0] = '\0';
                    
                    do {
                        printf("Veuillez saisir le jour de fin de la reservation (JJ MM): \t");
                        scanf("%s %s", jour, mois);
                        if (atoi(jour)> 31 && atoi(jour)<0 && atoi(mois)<0 && atoi(mois)>12) {
                            printf("Veuillez saisir une date valide.\n");
                        }
                        //Validation entrée fin Reservation
                    } while (atoi(jour)> 31 && atoi(jour)<0 && atoi(mois)<0 && atoi(mois)>12);
                    //Assemblage de la date
                    strcat(dateFormatee, mois);
                    strcat(dateFormatee, jour);
                    intervalleReservation.borne_sup = atoi(dateFormatee);
                    dateFormatee[0] = '\0';
                    mois[0] = '\0';
                    jour[0] = '\0';
/* ------------------------- Saisie du nouvel interval ------------------------------------------------------------*/
                    printf("SAISIE DU NOUVEL INTERVALLE: \n");
                    do {
                        printf("Veuillez saisir le jour de debut de la reservation (JJ MM): \t");
                        scanf("%s %s", jour, mois);
                        if (atoi(jour)> 31 && atoi(jour)<0 && atoi(mois)<0 && atoi(mois)>12) {
                            printf("Veuillez saisir une date valide.\n");
                        }
                        //Verification entrée Début Reservation
                    } while (atoi(jour)> 31 && atoi(jour)<0 && atoi(mois)<0 && atoi(mois)>12);
                    
                    if (mois[0] == '0') {
                        mois[0] = mois[1];
                        mois[1] = '\0';
                        //Reformatage de la date
                    }
                    strcat(dateFormatee, mois);
                    strcat(dateFormatee, jour);
                    //Assemblage de la date
                    nouvelIntervalle.borne_inf = atoi(dateFormatee);
                    dateFormatee[0] = '\0';
                    mois[0] = '\0';
                    jour[0] = '\0';
                    
                    do {
                        printf("Veuillez saisir le jour de fin de la reservation (JJ MM): \t");
                        scanf("%s %s", jour, mois);
                        if (atoi(jour)> 31 && atoi(jour)<0 && atoi(mois)<0 && atoi(mois)>12) {
                            printf("Veuillez saisir une date valide.\n");
                        }
                        //Validation entrée fin Reservation
                    } while (atoi(jour)> 31 && atoi(jour)<0 && atoi(mois)<0 && atoi(mois)>12);
                    //Assemblage de la date
                    strcat(dateFormatee, mois);
                    strcat(dateFormatee, jour);
                    nouvelIntervalle.borne_sup = atoi(dateFormatee);
                    modif_noeud(ABR, intervalleReservation, idEntreprise, nouvelIntervalle);
                    dateFormatee[0] = '\0';
                    mois[0] = '\0';
                    jour[0] = '\0';
                }
                else {
                    printf("L'arbre n'a pas encore été créé pour l'instant.\n");
                }
                
                
                break;
            case 5:
            // Supprimer une réservation
                printf("Veuillez saisir l'id de l'entreprise\n");
                validation_entree_int(idEntreprise, 0, 5000);
                printf("SAISIE DE L'INTERVALLE A SUPPRIMER: \n");
                do {
                    printf("Veuillez saisir le jour de debut de la reservation (JJ MM): \t");
                    scanf("%s %s", jour, mois);
                    if (atoi(jour)> 31 && atoi(jour)<0 && atoi(mois)<0 && atoi(mois)>12) {
                        printf("Veuillez saisir une date valide.\n");
                    }
                    //Verification entrée Début Reservation
                } while (atoi(jour)> 31 && atoi(jour)<0 && atoi(mois)<0 && atoi(mois)>12);
                
                if (mois[0] == '0') {
                    mois[0] = mois[1];
                    mois[1] = '\0';
                    //Reformatage de la date
                }
                strcat(dateFormatee, mois);
                strcat(dateFormatee, jour);
                //Assemblage de la date
                intervalleReservation.borne_inf = atoi(dateFormatee);
                dateFormatee[0] = '\0';
                
                do {
                    printf("Veuillez saisir le jour de fin de la reservation (JJ MM): \t");
                    scanf("%s %s", jour, mois);
                    if (atoi(jour)> 31 && atoi(jour)<0 && atoi(mois)<0 && atoi(mois)>12) {
                        printf("Veuillez saisir une date valide.\n");
                    }
                    //Validation entrée fin Reservation
                } while (atoi(jour)> 31 && atoi(jour)<0 && atoi(mois)<0 && atoi(mois)>12);
                //Assemblage de la date
                strcat(dateFormatee, mois);
                strcat(dateFormatee, jour);
                intervalleReservation.borne_sup = atoi(dateFormatee);
                dateFormatee[0] = '\0';
                suppr_noeud(&ABR, intervalleReservation, idEntreprise);
                break;
            case 6:
            // Afficher les réservations d'une entreprise
                printf("Veuillez saisir l'ID de l'entreprise.\n");
                validation_entree_int(idEntreprise, 0, 5000);
                
                break;
            case 7:
            // Supprimer l'arbre
                detruire_arbre(&ABR);
                boolArbre = 0;
                break;    
            default:
                break;
        }
    }
    return 0;

}
