#include"huffman.h"
#include<math.h>

/* https://public.iutenligne.net/informatique/algorithme-et-programmation/priou/LangageC/47_oprateurs_de_manipulation_de_bits__masques_et_bit__bit_dcalage.html */

void creer_code(noeud *element, int code, int profondeur){
    noeud *courant = element;

    if (est_feuille(courant) == 1){
        /* courant->code >> 32; /\* on vide les bits *\/ */
        courant->code = code;
        courant->nb_bits = profondeur;
    } else {
        code = code << 1;
        creer_code(courant->f_g, (code = code | 0), profondeur+1);
        creer_code(courant->f_d, (code = code | 1), profondeur+1);
    }
}

void affichage_code(int nbr_bits, int codage){
    
}

int main(){
    int a = 010;

    printf("%d\n", a);
    
    exit(EXIT_SUCCESS);
}