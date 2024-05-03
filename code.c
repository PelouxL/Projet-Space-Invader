#include"code.h"

void affichage_code(int nb_bits, int code){
    
    if (nb_bits <= 0){
        return;
    }

    affichage_code(nb_bits-1, code >> 1);
    printf("%d", code%2);
}

void creer_code(noeud *element, int code, int profondeur){
    noeud *courant = element;

    /* Attribution du code si courant est une feuille */ 
    if (est_feuille(courant) == 1){
        courant->code = code;
        courant->nb_bits = profondeur;
        printf("< %c > %d : ", courant->car, courant->car);
        affichage_code(courant->nb_bits,  courant->code);
        printf(" sur %d bits\n", courant->nb_bits);
    }
    
    /* Rappel recursif = on descend dans l'arbre d'Huffman */
    else {
        code = code << 1;
        creer_code(courant->f_g, (code | 0), profondeur+1);
        creer_code(courant->f_d, (code | 1), profondeur+1);
    }
}