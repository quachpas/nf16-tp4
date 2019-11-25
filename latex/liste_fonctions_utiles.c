typedef struct Date Date;

struct Date {
    char Jour[3];
    char Mois[3];
    char Annee[5];
};

void afficher_infos_choix_menu(int choix_menu, Date CHOIX_DATE, const char* CHOIX_MENU_TEXTE[]);
 // Afficher les informations du sous-menu + date courante
void afficher_infos_transaction(int id_etu, float montant, char* descr);
 // Affiche les infos d'une transaction
void free_BlockChain(BlockChain bc);
 // Libere l'espace memoire alloue
void changement_date(Date * DateDuJour);
 // Change la date 
int validation_entree_int(int cond, int inf, int sup);
 // Choix utilisateur conditionne
int nombreDeBlock(BlockChain bc);
 // Renvoie le nombre de bloc dans la blockchain
int bc_init(BlockChain bc);
 // Renvoie 1 si bc n'est pas initialise, sinon 0.
float validation_entree_float(float cond, float inf, float sup);
 // Choix utilisateur conditionne
T_Block * RechercherBlock(BlockChain bc, int id_block);
 // Retourne le bloc correspond a l'id donne
