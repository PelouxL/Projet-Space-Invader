#include"decompression.h"

void lire_entete(noeud *alphabet[N], FILE *fic){
    int nb_feuille, i, a, bit,
        acc = 0;
    char car, code, c;

    /* Initialisation */
    for (i=0; i < N; i++){
        alphabet[i] = NULL;
    }

    /* Recuperation du nombre de feuilles differentes */
    fscanf(fic, "%c", &c);
    nb_feuille = c;

    printf("nb feuille : %d\n", nb_feuille);

    while (acc < nb_feuille){
        
        /* Caractere */
        fscanf(fic, "%c", &car);
        a = car;
        printf("%c ", car);

        /* Nombre de bits */
        fscanf(fic, "%c", &c); /* W */
        alphabet[a]->nb_bits = c;
        printf("%d\n ", alphabet[a]->nb_bits);

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