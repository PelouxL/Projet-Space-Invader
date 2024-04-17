#include"huffman.h"
#include<math.h>

/* https://public.iutenligne.net/informatique/algorithme-et-programmation/priou/LangageC/47_oprateurs_de_manipulation_de_bits__masques_et_bit__bit_dcalage.html */


void affichage_code(int nb_bits, int code){

    if (nb_bits <= 0){
        return;
    }
    
    affichage_code(nb_bits-1, code >> 1);
    printf("%d", code%2);
}


void creer_code(noeud *element, int code, int profondeur){
    noeud *courant = element;

    if (est_feuille(courant) == 1){
        courant->code = code;
        courant->nb_bits = profondeur;
        printf("%c : ", courant->car);
        affichage_code(courant->nb_bits,  courant->code);
        printf("\n");
    } else {
        code = code << 1;
        creer_code(courant->f_g, (code | 0), profondeur+1);
        creer_code(courant->f_d, (code | 1), profondeur+1);
    }
}



int main(){
    noeud *huffman[256], *alphabet[256];
    FILE *fic = NULL;
    int g, i, *tab_occ, taille = 0;

    /* Initialisation */
    if ((fic = fopen("exemples.txt", "r")) == NULL ){
        printf("ERREUR main : lors de l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    if ((tab_occ = (int *) calloc(256, sizeof(int))) == NULL){
        printf("ERREUR main: echec calloc tab");
        exit(EXIT_FAILURE);
    }
    
    for(i = 0 ; i < 256 ; i++){
        huffman[i] = NULL; /* initialisation de Huffman */
        alphabet[i] = NULL; /* initialisation de alphabet */
    }
    
    /* Parcours du fichier et creation des noeuds */
    while((g = fgetc(fic)) != EOF ){
        tab_occ[g] += 1;
    }
    occurence(fic, tab_occ);

    for (i=0; i < 256; i++){
        if (tab_occ[i] > 0){
            if ((huffman[i] = (noeud *) malloc(sizeof(noeud))) == NULL){
                printf("ERREUR main: echec malloc huffman[%c]\n", i);
                exit(EXIT_FAILURE);
            }
            huffman[i] = creer_feuille(tab_occ, i);
            alphabet[i] = creer_feuille(tab_occ, i);
            taille++;
        }
    }

    /* Affichage des occurences des caracteres dans le fichier */
    /* for(i=0; i < 256; i++){ */
    /*     if(huffman[i] != NULL){ */
    /*         printf("%c : %d\n", huffman[i]->car, huffman[i]->occ); */
    /*     } */
    /* } */

    /* Création d'un nouveau noeud */
    creer_noeud(huffman, tab_occ, taille);

    /* Création du code de chaque caractere */
    creer_code(huffman[0], 0, 0);
    
    /* Liberation de l'espace alloue */
    for(i=0; i < 256; i++){
        if( huffman[i] != NULL){
            free(huffman[i]);
        }
    }
    exit(EXIT_SUCCESS);
}
  