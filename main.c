#include"huffman.h"
#include"code.h"
#include"compression.h"
#include"decompression.h"


int main(){
    noeud *huffman[N], *alphabet[N];
    FILE *fic = NULL;
    int g, i, *tab_occ, taille = 0;

    /* Initialisation */
    if ((fic = fopen("exemples.txt", "r")) == NULL ){
        printf("ERREUR main : lors de l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    if ((tab_occ = (int *) calloc(N, sizeof(int))) == NULL){
        printf("ERREUR main: echec calloc tab");
        exit(EXIT_FAILURE);
    }
    
    for(i = 0 ; i < N ; i++){
        huffman[i] = NULL; /* initialisation de Huffman */
        alphabet[i] = NULL; /* initialisation de alphabet */
    }
    
    /* Parcours du fichier et creation des noeuds */
    while((g = fgetc(fic)) != EOF ){
        tab_occ[g] += 1;
    }
    occurence(fic, tab_occ);

    for (i=0; i < N; i++){
        if (tab_occ[i] > 0){
            if ((huffman[i] = (noeud *) malloc(sizeof(noeud))) == NULL){
                printf("ERREUR main: echec malloc huffman[%c]\n", i);
                exit(EXIT_FAILURE);
            }
            huffman[i] = creer_feuille(tab_occ, i);
            alphabet[i] = huffman[i];
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
    for(i=0; i < N; i++){
        if( huffman[i] != NULL){
            free(huffman[i]);
        }
    }

    fclose(fic);
    fic = NULL;

    compression(alphabet, fic);
    decompression(fic);
        
    exit(EXIT_SUCCESS);
}
  