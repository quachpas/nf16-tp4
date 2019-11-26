/* <--------------- Déclaration structures  ---------------> */
typedef struct intervalle T_Inter;

struct intervalle { // Intervalle, la clé est borne_inf
    int borne_inf;
    int borne_sup;
};

typedef struct noeud T_Noeud;

struct noeud { // Noeud d'un arbre, pas de pointeur vers le père
    int id_entreprise;
    T_Inter intervalle;
    T_Noeud *fils_gauche; // Pointeurs vers les fils
    T_Noeud *fils_droit;
};

typedef T_Noeud* T_Arbre; // Pointeur vers un noeud (pointe vers la racine)

/* <--------------- Déclaration fonctions utiles  ---------------> */

int validation_entree_int(int cond, int inf, int sup); // Structure basique pour choix
void afficher_infos_choix_menu(int choix_menu, const char * CHOIX_MENU_TEXTE[]); // Afficher les informations du sous-menu
int cle(T_Inter intervalle); // Renvoie la clé d'un noeud
void parcours(T_Inter intervalle, T_Noeud *noeud_parcours); // On renvoie FG ou FD selon l'intervalle
int droite_intervalle(T_Noeud* noeud); // Renvoie borne_sup d'un intervalle d'un noeud
int intervalle_chevauche(T_Noeud *noeud_1, T_Arbre *ABR); // On parcourt l'arbre pour vérifier qu'aucun n'intervalle ne se chevauche
void afficher_reservation(T_Noeud *noeud); // Affichage réservation
void afficher_date(T_Inter intervalle); // Affichage date "JJ/MM"
int nombre_de_fils(T_Noeud *noeud); // Renvoie le nombre de fils d'un noeud
T_Noeud* plus_proche_successeur(T_Arbre ABR); // Renvoie l'intervalle min de l'arbre (sous-arbre droit)
T_Noeud* plus_proche_predecesseur(T_Arbre ABR); // Renvoie l'intervalle max de l'arbre (sous-arbre gauche)
T_Noeud* recherche_pere(T_Arbre ABR, T_Inter intervalle, int id_entreprise); // Renvoie le père du noeud recherché
/* <--------------- Déclaration fonctions de base---------------> */

T_Noeud* creer_noeud(int id_entreprise, T_Inter intervalle);
// Renvoie un pointeur vers le nouveau noeud

void ajouter_noeud(T_Arbre* ABR, T_Noeud* noeud);
// Ne pas modifier ABR

T_Noeud* recherche(T_Arbre ABR, T_Inter intervalle, int id_entreprise);
// Renvoie un pointeur vers la réservation recherchée, sinon NULL
// Ne pas modifier ABR

void suppr_noeud(T_Arbre *ABR, T_Inter intervalle, int id_entreprise);
// Ne pas modifier ABR
// 

void modif_noeud(T_Arbre ABR, T_Inter intervalle, int id_entreprise, T_Inter nouv_intervalle);
// Ne pas modifier ABR

void affiche_abr(T_Arbre ABR);
// Ne pas modifier ABR

void affiche_entr(T_Arbre ABR, int id_entreprise);
// Afficher toutes les réservations d'une entreprise 
// Parcours infixe (croissant)

void detruire_arbre (T_Arbre *ABR);
// Détruire un arbre
// Parcours postfixe (GDR)