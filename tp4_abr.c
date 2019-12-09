#include "tp4_abr.h"
#include <stdio.h>
#include <stdlib.h>
/* <--------------- Définition fonctions utiles  ---------------> */

void afficher_infos_choix_menu(int choix_menu, const char* CHOIX_MENU_TEXTE[]) {
    printf("\n<-- %s -->", CHOIX_MENU_TEXTE[choix_menu - 1]);
    printf("\n");
}

int validation_entree_int(int cond, int inf, int sup) {
    // On initialise la valeur condition
    cond = inf -1;
    while(cond < inf || cond > sup) {
        fflush(stdin);
        scanf("%d", &cond);
        if(cond < inf || cond > sup) {
            printf("Merci de rentrer un choix valide.\n");
        }
    }

    // On stocke le choix dans uen variable intermédiaire
    int choix_final = cond;

    // On réinitialise à une valeur par défaut
    cond = -1;

    // On retourne le choix utilisateur
    return choix_final;
}

int cle(T_Inter intervalle) { // On récupère la clé de l'intervalle
    return intervalle.borne_inf;
}

T_Noeud* parcours(T_Inter intervalle, T_Noeud *noeud_du_parcours) {

    if (cle(intervalle) < cle(noeud_du_parcours->intervalle)) {
        // L'intervalle est "plus petit"/à gauche
        return noeud_du_parcours->fils_gauche;
    }
    if (cle(intervalle) > cle(noeud_du_parcours->intervalle)) {
        // L'intervalle est "plus grand"/à droite
        return noeud_du_parcours->fils_droit;
    }
    return NULL;
}
int droite_intervalle(T_Noeud *noeud) {
    return noeud->intervalle.borne_sup;
}

void afficher_date(T_Inter intervalle) {
    printf("%d\n",intervalle.borne_sup);
    if (sizeof(intervalle.borne_inf) == 3) {
        printf("/0%d",intervalle.borne_inf);
    }
    else {
        printf("%d", intervalle.borne_inf);
    }
    
}
void afficher_reservation(T_Noeud* noeud) {
    if (noeud) {
        printf("<--- RESERVATION --- >\n");
        printf("- ID Entreprise : %d\n",noeud->id_entreprise);
        printf("- Dates : ");
        afficher_date(noeud->intervalle);
        printf("\n\n");
    }
    else{
        printf("Il n'y a aucun noeud !\n");
    }
}   

int intervalle_chevauche(T_Noeud *noeud, T_Arbre *ABR) {
    T_Noeud* pnt = *ABR;

    while (nombre_de_fils(pnt) != 0) {
        // Des qu'on trouve un chevauchement, on renvoie vrai. 
        if (!(droite_intervalle(noeud) < cle(pnt->intervalle) || cle(noeud->intervalle) > droite_intervalle(pnt))) {
            // On cherche à savoir si deux intervales se chevauchent
            // Si I1 est à gauche de I2, I2 à droite de I1
            // OU
            // Si I1 est à droite de I2, I1 à gauche de I2
            // => Les intervalles ne se chevauchent pas 
            // On a couvert toutes les possibilités
            // On prend sa négation pour savoir s'il y a chevauchement
            printf("Erreur à la réservation suivante :\n");
            afficher_reservation(pnt);
            return 1;
        }
        
        // On parcourt l'arbre de façon logique
        // Si pas de chevauchement au noeud actuel, on va à droite si l'intervalle est supérieure, gauche sinon.
        // Il n'y a pas de chevauchement possible à gauche si l'intervalle est supérieure.
        pnt = parcours(noeud->intervalle, pnt);
    }
    // Sinon, les intervalles ne se chevauchent pas
    return 0;
}

int nombre_de_fils(T_Noeud *noeud) {
    if (noeud && !(noeud->fils_droit) && !(noeud->fils_gauche)) {
        return 2;
    }
    else if (noeud && (noeud->fils_droit || noeud->fils_gauche)) {
        return 1;
    }
    else return 0;   
}

T_Noeud* plus_proche_successeur(T_Arbre ABR) {
    // Renvoie l'intervalle min de l'arbre (sous-arbre droit)
    T_Noeud *pnt = ABR;
    T_Noeud *tmp;
    while (!pnt) {
        tmp = pnt;
        pnt = pnt->fils_gauche;
    };
    return tmp;
}
T_Noeud* plus_proche_predecesseur(T_Arbre ABR) {
    // Renvoie l'intervalle max de l'arbre (sous-arbre gauche)
    T_Noeud *pnt = ABR;
    T_Noeud *tmp;
    while (!pnt) {
        tmp = pnt;
        pnt = pnt->fils_droit;
    };
    return tmp;
}

T_Noeud* recherche_pere(T_Arbre ABR, T_Inter intervalle, int id_entreprise) {
// Renvoie un pointeur vers le noeud père du noeud cherché, sinon NULL
// Ne pas modifier ABR

    T_Noeud *pnt = ABR;
    T_Noeud *noeud_pere;
    while(!pnt) {
        if (cle(intervalle) == cle(pnt->intervalle) && intervalle.borne_sup == droite_intervalle(pnt) && id_entreprise == pnt->id_entreprise) {
            // Si les bornes sont identiques, et l'id identique
            // => Bonne réservation    
            return noeud_pere;
        }
        else {
            noeud_pere = pnt;
            // On passage au noeud suivant de façon logique
            parcours(intervalle, pnt);
        }   
    }
    printf("Aucun noeud n'a été trouvé.");
    return NULL;
}

/* <--------------- Définition fonctions principales  ---------------> */

T_Noeud* creer_noeud(int id_entreprise, T_Inter intervalle) {
    // Renvoie un pointeur vers le nouveau noeud

    // Allocation mémoire
    T_Noeud* nouveau_noeud = malloc(sizeof(T_Noeud));
    
    // On initialise les variables
    nouveau_noeud->id_entreprise = id_entreprise;
    nouveau_noeud->intervalle=intervalle;
    nouveau_noeud->fils_droit = NULL;
    nouveau_noeud->fils_gauche = NULL;
    return nouveau_noeud;
}

void ajouter_noeud(T_Arbre* ABR, T_Noeud* noeud) { 
    // Ne pas modifier ABR
    if (*ABR == NULL) {
        //Cas trivial où l'ABR est vide
        *ABR = noeud;
        return;
    }

    // Récupérer le pointeur du premier noeud.
    T_Noeud *pnt = *ABR;
    
    // On vérifie que les intervalles ne se chevauchent pas
    if (intervalle_chevauche(noeud, ABR)) {
        afficher_reservation(noeud);
        printf("Les intervalles se chevauchent.");    
    }

    // S'ils ne se chevauchent pas, on l'ajoute à l'ABR
    else {
        // Variable de Stockage
        T_Noeud *tmp;

        // On parcourt l'arbre si aucune incompatibilité n'apparaît
        // On s'arrête lorsqu'on arrive à une feuille
        while (pnt) {
            // On sauvegarde le prédecesseur
            tmp = pnt;
            
            // On passe au noeud suivant
            if (nombre_de_fils(pnt) != 0) {
                pnt = parcours(noeud->intervalle, pnt);
            }
            else{
                pnt = NULL;
            }
            
        }

        // On ajoute le noeud après avoir vérifié où il doit se placer dans l'ABR
        // L'intervalle est "plus petit"/à gauche
        if (cle(tmp->intervalle) < cle(noeud->intervalle)) {
            tmp->fils_gauche = noeud;
        }
        // L'intervalle est "plus grand"/à droite
        if (cle(tmp->intervalle) > cle(noeud->intervalle)) {
            tmp->fils_droit = noeud;
        }
    }
}

T_Noeud* recherche(T_Arbre ABR, T_Inter intervalle, int id_entreprise) {
// Renvoie un pointeur vers la réservation recherchée, sinon NULL
// Ne pas modifier ABR
    T_Noeud *pnt = ABR;
    while(pnt) {
        if (cle(intervalle) == cle(pnt->intervalle) && intervalle.borne_sup == droite_intervalle(pnt) && id_entreprise == pnt->id_entreprise) {
            // Si les bornes sont identiques, et l'id identique
            // => Bonne réservation    
            return pnt;
        }
        else {
            // On passage au noeud suivant de façon logique
            parcours(intervalle, pnt);
        }   
    }
    printf("Aucun noeud n'a été trouvé.\n");
    return NULL;
}

void suppr_noeud(T_Arbre *ABR, T_Inter intervalle, int id_entreprise) {
// Ne pas modifier ABR

// Suppression d'une feuille  : facile 
// Suppression d'un noeud à un fils : On remplace le noeud par son fils
// Supression d'un noeud à deux fils : On remplace le noeud par le MAX du sous-arbre gauche OU sous-arbre droit.
// Pour ne pas déséquilbirer, on peut utiliser rand, pour soit choisir à gauche, soit à droite.
// Il faut écrire la fonction intervalle_extremum(T_Arbre ABR) qui renvoie l'intervalle le plus grand d'un sous arbre.

    // On initialise un pointeur sur le noeud à supprimer et son père
    T_Noeud *noeud_pere = recherche_pere(*ABR, intervalle, id_entreprise);
    T_Noeud *noeud_a_supprimer = recherche(*ABR, intervalle, id_entreprise);
    T_Noeud *predecesseur, *successeur;

    // On compte son nombre de fils
    int nombre_fils = nombre_de_fils(noeud_a_supprimer);

    switch (nombre_fils) {
        case 0:
            // S'il n'a pas de fils, on le supprime.

            // Il faut savoir s'il est le fils droit ou gauche
            if (noeud_pere->fils_droit == noeud_a_supprimer) {
                noeud_pere->fils_droit = NULL;
            }
            else {
                noeud_pere->fils_gauche = NULL;
            }
            free(noeud_a_supprimer);
            break;
        case 1:
            // On remplace le noeud à supprimer par son fils
            // 1) Relier le noeud père au fils du noeud à supprimer
            // 2) On doit pour cela libérer l'espace mémoire du noeud

            // Si on doit remplacer le noeud par son fils droit
            if (noeud_a_supprimer->fils_droit) {
                // Si le noeud à supprimer est le fils droit
                if (noeud_pere->fils_droit == noeud_a_supprimer) {
                    // On remplace le fils droit du pere par le fils droit du noeud à supprimer
                    noeud_pere->fils_droit = noeud_a_supprimer->fils_droit;
                }
                // Sinon, le noeud à supprimer est le fils gauche
                else {
                    // Sinon, on remplace le fils gauche du pere par le fils droit du noeud à supprimer
                    noeud_pere->fils_gauche = noeud_a_supprimer->fils_droit;
                }
            }
            // Sinon, on doit remplacer le noeud par son fils gauche
            else {
                // Si le noeud à supprimer est le fils droit
                if (noeud_pere->fils_droit == noeud_a_supprimer) {
                    // On remplace le fils droit du pere par le fils gauche du noeud à supprimer
                    noeud_pere->fils_droit = noeud_a_supprimer->fils_gauche;
                }
                // Sinon, le noeud à supprimer est le fils gauche
                else {
                    // On remplace le fils gauche du pere par le fils gauche du noeud à supprimer
                    noeud_pere->fils_gauche = noeud_a_supprimer->fils_gauche;
                }
            }

            // On libère l'espace mémoire alloué
            free(noeud_a_supprimer);
            break;
        case 2:
            // Nombre aléatoire 0 ou 1 pour équilibrer au maximum l'ABR
            if (rand() % 2) {
                // 0, FAUX : on remplace par le prédecesseur (arbre gauche)
                
                // On récupère le noeud concerné
                predecesseur = plus_proche_predecesseur(noeud_a_supprimer->fils_gauche);
                
                // On "échange" les deux noeuds en gardant intact les filsG et filsD
                noeud_a_supprimer->id_entreprise = predecesseur->id_entreprise;
                noeud_a_supprimer->intervalle.borne_inf = predecesseur->intervalle.borne_inf;
                noeud_a_supprimer->intervalle.borne_sup = predecesseur->intervalle.borne_sup;

                // On supprime le noeud qu'on a copié
                suppr_noeud(ABR, predecesseur->intervalle, predecesseur->id_entreprise);
            }
            else {
                // 1, VRAI : on remplace par le successeur(arbre droit)
                successeur = plus_proche_successeur(noeud_a_supprimer->fils_droit);
                
                // On "échange" les deux noeuds en gardant intact les filsG et filsD
                noeud_a_supprimer->id_entreprise = successeur->id_entreprise;
                noeud_a_supprimer->intervalle.borne_inf = successeur->intervalle.borne_inf;
                noeud_a_supprimer->intervalle.borne_sup = successeur->intervalle.borne_sup;

                // On supprime le noeud qu'on a copié
                suppr_noeud(ABR, successeur->intervalle, successeur->id_entreprise);
            }
            break;
        default:
            printf("Erreur, nombre de fils");
            break;
    }
}

void modif_noeud(T_Arbre ABR, T_Inter intervalle, int id_entreprise, T_Inter nouv_intervalle) {
// Ne pas modifier ABR
    T_Noeud *pnt = recherche(ABR, intervalle, id_entreprise);
    if (pnt) {
        pnt->intervalle.borne_inf = nouv_intervalle.borne_inf;
        pnt->intervalle.borne_sup = nouv_intervalle.borne_sup;
    }
}

void affiche_abr(T_Arbre ABR) {
// Ne pas modifier ABR
// Parcours Infixe GRD (croissant)

    T_Noeud *pnt = ABR;
    if (pnt) {
        if (nombre_de_fils(pnt) != 0) {
            affiche_abr(pnt->fils_gauche);
        }
        afficher_reservation(pnt);
        if (nombre_de_fils(pnt) != 0) {
            affiche_abr(pnt->fils_droit);
        }
    }
}

void affiche_entr(T_Arbre ABR, int id_entreprise) {
    T_Noeud *pnt = ABR;
    // Si le pointeur est non nul
    // Affichage des réservations en infixe (croissant)
    if (pnt) {
        affiche_entr(ABR->fils_gauche, id_entreprise);
        if(pnt->id_entreprise == id_entreprise) {
            afficher_reservation(pnt);
        }
        affiche_entr(ABR->fils_droit, id_entreprise);
    }
}

void detruire_arbre (T_Arbre *ABR) {
    T_Noeud *pnt = *ABR;
    if(pnt && nombre_de_fils(pnt) == 0) {
        free(pnt);
    }
    else {
        // Postfixe
        detruire_arbre(&pnt->fils_gauche);
        detruire_arbre(&pnt->fils_droit);
        detruire_arbre(&pnt);
    }
}
