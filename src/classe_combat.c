#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 50

typedef enum class {
    ARCHER,
    SORCIER,
    GUERRIER,
} Class;

typedef struct{
    char* nom;
    Class current_class;
    int attaque;
    int defense;
    int esquive;
    int vie;
    int exp;
} Joueur;
void flush(){
    int  a;
    char c;
    do{
        a = scanf("%c", &c);
    } while(a==1 && c != '\n' );
}
Joueur* creerJoueur(){
    Joueur* j = NULL;
    int size = 0;
    // Malloc struct
    j = malloc(sizeof(Joueur));
    if( j == NULL){
        exit(1);
    }
    // Create first name
    char tab[256];
    int res = 0;
    do{
        res = 0;
        printf("Saissisez le nom du joueur\n");
        res = scanf("%[^\n]", tab);
        flush();
    } while (res != 1);
    if (tab == NULL){
        exit(404);
    }
    (*j).nom = malloc((strlen(tab) + 1) * sizeof(char));
    if ((*j).nom == NULL){
        exit(404);
    }
    strcpy((*j).nom, tab);
    // Vie
    j->vie = 150;
    // Exp
    j->exp = 0;
    // Return result
    return j;
}

//Inventaire

typedef struct{
    char* nom[SIZE];
    int nombre;
} Info;


typedef enum material {
    SWORD,
    PICKAXE,
} Material;

typedef struct item_stack {
    char name[SIZE];
    Material material;
    int count;
} Item_Stack;


typedef struct{
    Info* item;
    int capacite;
    int quantite;
} Inventaire;

// Fonction pour initialiser l'inventaire (capacité de 3 item)

Inventaire* initialiserInv(){
    Inventaire* p = NULL;
    p = malloc(sizeof(Inventaire));
    if( p == NULL){
        exit(2);
    }
    p->capacite = 3;
    p->item = malloc(sizeof(Inventaire) * p->capacite);
    if( p->item == NULL){
        exit(3);
    }


}

// FOnction pour ajouter item

void ajoutItem(Inventaire* p, Info nom){
    if (p->quantite <= p->capacite){
        p->item[p->quantite] = nom;
        p->quantite++;
    }
    else{
        printf("Inventaire chargé !");
    }
}


//Fonction pour verifier son inventaire

void afficheInv(Inventaire* p){
    printf("Voici votre inventaire :\n");
    for(int i = 0; i < p->quantite; i++){
        printf("%s", p->item[i].nom);
    }
}


// Creation Abilité


void resetData(Joueur* j){
    switch(j->current_class){
        case ARCHER:
            j->attaque = rand()%5 + 8;
            j->defense = rand()%3 + 3;
            j->esquive = rand()%12 + 5;
            break;
        case SORCIER:
            j->attaque = rand()%7 + 4;
            j->defense = rand()%5 + 8;
            j->esquive = rand()%9 + 8;
            break;
        case GUERRIER:
            j->attaque = rand()%4 + 12;
            j->defense = rand()%4 + 5;
            j->esquive = rand()%14 + 3;

    }
}

// Reset archer

void resetArcher(Joueur* a, Joueur* b) {
    a->current_class = ARCHER;
    resetData(a);

    b->current_class = GUERRIER;
    resetData(b);
}

// Reset wizard
void resetSorcier(Joueur* a, Joueur* b) {
    a->current_class = SORCIER;
    resetData(a);

    b->current_class = GUERRIER;
    resetData(b);
}

// Reset Warrior
void resetGuerrier(Joueur* a, Joueur* b) {
    a->current_class = GUERRIER;
    resetData(a);

    b->current_class = ARCHER;
    resetData(b);
}



// Creation Combat


void combat(Joueur* a, Joueur* b, int N){

    printf("Voici les différentes classes :\n");
    printf("1 : Archer :\n Attaque : 8 à 12\n Defense : 3 à 5\n Esquive: 5 à 16\n");
    printf("2 : Sorcier :\n Attaque : 4 à 10\n Defense : 8 à 12\n Esquive: 8 à 16\n");
    printf("3 : Guerrier :\n Attaque : 12 à 15\n Defense : 5 à 8\n Esquive: 3 à 16\n");


    int res = 0;
    do {
        res = 0;
        printf("Quelle classe voulait vous choisir ? : ");
        res = scanf("%d", &N);
    } while (res != 1 || N < 1 || N > 3);

    switch (N) {
        case 1:
            resetArcher(a, b);
            break;
        case 2:
            resetSorcier(a, b);
            break;
        case 3:
            resetGuerrier(a, b);
            break;
        default:
            printf("Choix inexistant\n");
            return;
    }


    printf("Debut du combat ! :\n");



    while (a->vie > 0 && b->vie > 0) {

        resetData(a);
        resetData(b);

        if (a->attaque < b->esquive) {
            printf("%s esquive l'attaque de %s!\n", b->nom, a->nom);
        } else {
            int degats = a->attaque - b->defense;
            if (degats < 0) degats = 0;
            b->vie -= degats;
            printf("%s attaque %s et lui inflige %d points de degats!\n", a->nom, b->nom, degats);
        }

        if (b->vie <= 0) {
            printf("%s tombe, %s gagne le combat!\n", b->nom, a->nom);
            a->exp += 1;
            break;

        }


        if (b->attaque < a->esquive) {
            printf("%s esquive l'attaque de %s!\n", a->nom, b->nom);
        } else {
            int degats = b->attaque - a->defense;
            if (degats < 0) degats = 0;
            a->vie -= degats;
            printf("%s attaque %s et lui inflige %d points de degats!\n", b->nom, a->nom, degats);
        }

        if (a->vie <= 0) {
            printf("%s tombe, %s gagne le combat!\n", a->nom, b->nom);
            b->exp +=1;
            break;
        }
    }
}




int main() {

    srand(time(NULL));

    Joueur*  j1    = NULL;
    Joueur*  j2     = NULL;
    int degats = 0;
    int N = 0;

    j1  = creerJoueur();
    j2  = creerJoueur();

    combat(j1, j2, N);

    printf("Exp : %d", j1->exp);

    free(j1);
    free(j2);

    return 0;
}