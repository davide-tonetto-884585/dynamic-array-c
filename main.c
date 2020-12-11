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

bool_t equalsProva(const void *elem1, const void *elem2) {
    if ((((Prova *) elem1)->intVal == ((Prova *)elem2)->intVal)
    && (((Prova *) elem1)->floatVal == ((Prova *)elem2)->floatVal))
        return TRUE;

    return FALSE;
}

bool_t equalsInt(const void *elem1, const void *elem2){
    if (*((int *) elem1) == *((int *) elem2))
        return TRUE;

    return FALSE;
}

DYN_ARR_CREATE(int);
DYN_ARR_CREATE(Prova);

int main() {

    struct dyn_arr_int array;

    //dyn_arr_init(array, 10);
    DYN_ARR_INIT_DEFAULT(array);

    for (int i = 0; i < 10; ++i) {
        DYN_ARR_PUSH(array, i);
    }

    int element = 8;
    printf("\nl'elemento %d si trova in posizione %d\n\n", element, DYN_ARR_INDEX_OF_ELEM(array, element, equalsInt));

    DYN_ARR_REMOVE_ELEM(array, 4);
    DYN_aRR_REMOVE_SPECIFIC_ELEM(array, element, equalsInt);
    for (int i = 0; i < DYN_ARR_GET_SIZE(array); ++i) {
        printf("array[%d] = %d\n", i, DYN_ARR_GET_ELEM(array, i));
    }

    printf("\n");

    /*test con struct*/
    struct dyn_arr_Prova arrayProve;
    DYN_ARR_INIT(arrayProve, 2);

    Prova prova = {12, 12.34f};
    DYN_ARR_PUSH(arrayProve, prova);
    prova.floatVal = 1.23f;
    DYN_ARR_PUSH(arrayProve, prova);
    prova.intVal = 999;
    DYN_ARR_PUSH(arrayProve, prova);

    DYN_ARR_GET_ELEM_SECURE(arrayProve, 2, prova);
    provaToString(prova);
    printf("size: %zu, capacity: %zu\n", DYN_ARR_GET_SIZE(arrayProve), DYN_ARR_GET_CAPACITY(arrayProve));

    printf("\n");

    Prova prova2;
    if (DYN_ARR_POP(arrayProve, prova2)) {
        provaToString(prova2);
        printf("%zu\n", DYN_ARR_GET_SIZE(arrayProve));
    } else {
        printf("array vuoto");
    }

    printf("\n");

    for (int i = 0; i < DYN_ARR_GET_SIZE(arrayProve); ++i) {
        provaToString(DYN_ARR_GET_ELEM(arrayProve, i));
    }

    DYN_ARR_REMOVE_ELEM(arrayProve, 1);
    printf("\n");

    for (int i = 0; i < DYN_ARR_GET_SIZE(arrayProve); ++i) {
        provaToString(DYN_ARR_GET_ELEM(arrayProve, i));
    }

    DYN_ARR_PUSH(arrayProve, prova);
    if (DYN_ARR_CONTAINS_ELEM(arrayProve, prova, equalsProva))
        printf("\nelemento trovato\n");
    else
        printf("elemento non trovato\n");

    /*free memory*/
    DYN_ARR_DESTROY(array);
    DYN_ARR_DESTROY(arrayProve);

    return 0;
}
