#include <tp4_abr.h>
/* <--------------- Définition fonctions utiles  ---------------> */

void afficher_infos_choix_menu(int choix_menu, const char* CHOIX_MENU_TEXTE[]) {
    printf("\n<-- %s -->", CHOIX_MENU_TEXTE[choix_menu - 1]);
    printf("\n");
}

int validation__entree_int(int cond, int inf, int sup) {
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

void parcours(T_Inter intervalle, T_Noeud *noeud_du_parcours) {
    if (cle(intervalle) < cle(noeud_du_parcours->intervalle)) {
        // L'intervalle est "plus petit"/à gauche
        noeud_du_parcours = noeud_du_parcours->fils_gauche;
    }
    if (cle(intervalle) > cle(noeud_du_parcours->intervalle)) {
        // L'intervalle est "plus grand"/à droite
        noeud_du_parcours = noeud_du_parcours->fils_droit;
    }
}
int droite_intervalle(T_Noeud *noeud) {
    return noeud->intervalle.borne_sup;
}

void afficher_date(T_Inter intervalle) {
    printf("%d",intervalle.borne_sup);
    if (sizeof(intervalle.borne_inf) == 3) {
        printf("/0%d",intervalle.borne_inf);
    }
    else {
        printf("%d", intervalle.borne_inf);
    }
    
}
void afficher_reservation(T_Noeud* noeud) {
    printf("<--- RESERVATION --- >\n");
    printf("- ID Entreprise : %d\n",noeud->id_entreprise);
    printf("- Dates : ");
    afficher_date(noeud->intervalle);
    printf("\n\n");
}   

int intervalle_chevauche(T_Noeud *noeud, T_Arbre *ABR) {
    T_Noeud* pnt = ABR;

    while (!pnt) {
        
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
        parcours(noeud->intervalle, pnt);    
    }
    // Sinon, les intervalles ne se chevauchent pas
    return 0;
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
}

void ajouter_noeud(T_Arbre* ABR, T_Noeud* noeud) { 
    // Ne pas modifier ABR

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
        T_Noeud *pred = malloc(sizeof(T_Noeud));    

        // On parcourt l'arbre si aucune incompatibilité n'apparaît
        // On s'arrête lorsqu'on arrive à une feuille
        while (!pnt) {
            // On sauvegarde le prédecesseur
            pred = pnt;
            
            // On passe au noeud suivant
            parcours(noeud->intervalle, pnt);
        }

        // On ajoute le noeud après avoir vérifié où il doit se placer dans l'ABR
        // L'intervalle est "plus petit"/à gauche
        if (cle(pred->intervalle) < cle(noeud->intervalle)) {
            pred->fils_gauche = noeud;
        }
        // L'intervalle est "plus grand"/à droite
        if (cle(pred->intervalle) > cle(noeud->intervalle)) {
            pred->fils_droit = noeud;
        }
    }
}

T_Noeud* recherche(T_Arbre ABR, T_Inter intervalle, int id_entreprise) {
// Renvoie un pointeur vers la réservation recherchée, sinon NULL
// Ne pas modifier ABR
    T_Noeud *pnt = ABR;
    while(!pnt) {
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
    printf("Aucun noeud n'a été trouvé.");
    return NULL;
}

void suppr_noeud(T_Arbre *ABR, T_Inter intervalle, int id_entreprise) {
// Ne pas modifier ABR

// Suppression d'une feuille  : facile 
// Suppression d'un noeud à un fils : On remplace le noeud par son fils
// Supression d'un noeud à deux fils : On remplace le noeud par le MAX du sous-arbre gauche OU sous-arbre droit.
// Pour ne pas déséquilbirer, on peut utiliser rand, pour soit choisir à gauche, soit à droite.
// Il faut écrire la fonction max_intervalle(T_Arbre ABR) qui renvoie l'intervalle le plus grand d'un sous arbre.


}

void modif_noeud(T_Arbre ABR, T_Inter intervalle, int id_entreprise, T_Inter nouv_intervalle) {
// Ne pas modifier ABR

}

void affiche_abr(T_Arbre ABR) {
// Ne pas modifier ABR
// Parcours Infixe GRD (croissant)
}