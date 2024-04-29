#include"decompression.h"

void lire_entete(noeud *alphabet[N], FILE *fic){
    int nb_feuille, i, a, bit, nb_bit_car,
        acc = 0;
    char car, code;

    /* Initialisation */
    for (i=0; i < N; i++){
        alphabet[i] = NULL;
    }

    /* Recuperation du nombre de feuilles differentes */
    nb_feuille = fgetc(fic);
    printf("nb feuille : %d\n", nb_feuille);

    while (acc < nb_feuille){

        /* Caractere */
        car = fgetc(fic);
        a = car;
        fprintf(stdout, "<%c> %d : ", car, a);

        if ((alphabet[a] = (noeud *) malloc(sizeof(noeud))) == NULL){
            printf("ERREUR lire_entete: echec malloc \n");
            exit(EXIT_FAILURE);
        }

        /* Nombre de bits */
        /* for(k = 4 ; k > 0 ;k++){ */
            /*  si 1 pow(1,k) */
        nb_bit_car = fgetc(fic); /* W */
        alphabet[a]->nb_bits = nb_bit_car;
        printf("%d\n", alphabet[a]->nb_bits);

        /* Code */
        fscanf(fic, "%c", &code);
        for (i = alphabet[a]->nb_bits; i > 0; i--){
            bit = extraire_bit(code, i-1);
            
            alphabet[a]->code = alphabet[a]->code << 1;
            alphabet[a]->code = alphabet[a]->code | bit;
        }

        acc++;
    }
} 

void decompression(FILE *fic){
    noeud *alphabet[N];
    int i;
    
    if ((fic = fopen("cmp2.txt", "r")) == NULL){
        printf("Badum tsss\n");
        return;
    }

    lire_entete(alphabet, fic);

    for (i=0; i < N; i++){
        if (alphabet[i] != NULL){
            printf("%c %c ", i, alphabet[i]->car);
            affichage_code(alphabet[i]->nb_bits, alphabet[i]->code);
        }
    }

    fclose(fic);
}