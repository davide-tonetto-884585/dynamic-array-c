#include <stdio.h>
#include "dynarr.h"

/*struct per testare*/
typedef struct Prova {
    int intVal;
    float floatVal;
} Prova;

void provaToString(Prova p) {
    printf("prova.intVal = %d, prova.floatVal = %f\n", p.intVal, p.floatVal);
}

bool equalsProva(const void *elem1, const void *elem2) {
    if ((((Prova *) elem1)->intVal == ((Prova *)elem2)->intVal)
    && (((Prova *) elem1)->floatVal == ((Prova *)elem2)->floatVal))
        return true;

    return false;
}

bool equalsInt(const void *elem1, const void *elem2){
    if (*((int *) elem1) == *((int *) elem2))
        return true;

    return false;
}

int main() {
    dyn_arr_create(int) array;
    //dyn_arr_init(array, 10);
    dyn_arr_init_default(array);

    for (int i = 0; i < 10; ++i) {
        dyn_arr_push(array, i);
    }

    int element = 8;
    printf("\nl'elemento %d si trova in posizione %d\n\n", element, dyn_arr_index_of_elem(array, element, equalsInt));

    dyn_arr_remove_elem(array, 4);
    dyn_arr_remove_specific_elem(array, element, equalsInt);
    for (int i = 0; i < dyn_arr_get_size(array); ++i) {
        printf("array[%d] = %d\n", i, dyn_arr_get_elem(array, i));
    }

    printf("\n");

    /*test con struct*/
    dyn_arr_create(Prova) arrayProve;
    dyn_arr_init(arrayProve, 2);

    Prova prova = {12, 12.34f};
    dyn_arr_push(arrayProve, prova);
    prova.floatVal = 1.23f;
    dyn_arr_push(arrayProve, prova);
    prova.intVal = 999;
    dyn_arr_push(arrayProve, prova);

    dyn_arr_get_elem_secure(arrayProve, 2, prova);
    provaToString(prova);
    printf("size: %zu, capacity: %zu\n", dyn_arr_get_size(arrayProve), dyn_arr_get_capacity(arrayProve));

    printf("\n");

    Prova prova2;
    if (dyn_arr_pop(arrayProve, prova2)) {
        provaToString(prova2);
        printf("%zu\n", dyn_arr_get_size(arrayProve));
    } else {
        printf("array vuoto");
    }

    printf("\n");

    for (int i = 0; i < dyn_arr_get_size(arrayProve); ++i) {
        provaToString(dyn_arr_get_elem(arrayProve, i));
    }

    dyn_arr_remove_elem(arrayProve, 1);
    printf("\n");

    for (int i = 0; i < dyn_arr_get_size(arrayProve); ++i) {
        provaToString(dyn_arr_get_elem(arrayProve, i));
    }

    dyn_arr_push(arrayProve, prova);
    if (dyn_arr_contains_elem(arrayProve, prova, equalsProva))
        printf("\nelemento trovato\n");
    else
        printf("elemento non trovato\n");

    /*free memory*/
    dyn_arr_destroy(array);
    dyn_arr_destroy(arrayProve);

    return 0;
}
