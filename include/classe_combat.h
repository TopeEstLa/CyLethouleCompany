//
// Created by Paul Morille on 15/05/2024.
//

#ifndef CYLETHOULECOMPANY_CLASSE_COMBAT_H
#define CYLETHOULECOMPANY_CLASSE_COMBAT_H
typedef enum material {
    COUPE,
    EPEE,
    CRANE,
} Material;


typedef struct {
    char* name;
    int capacite;
    int quantite;
    Material* material;
} Inventaire;
#endif //CYLETHOULECOMPANY_CLASSE_COMBAT_H
