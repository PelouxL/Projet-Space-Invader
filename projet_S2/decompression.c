#include"decompression.h"

void lire_entete(noeud *alphabet[N], FILE *fic){
    int i, j, a, *p,
        bit,         /* Bit qu'on reupere dans le paquet */
        nb_feuille,
        index = 7,   /* La ou on en est dans le paquet */
        acc = 0;     /* Nombre de feuille trouvees */
    char paquet, code = 0;

    /* Initialisation */
    for (i=0; i < N; i++){
        alphabet[i] = NULL;
    }

    /* Recuperation du nombre de feuilles differentes */
    nb_feuille = fgetc(fic);
    printf("nb feuille : %d\n", nb_feuille);
    
    /* Lecture des paquets */
    paquet = fgetc(fic);
    while (acc < nb_feuille){
        for (i=0; i < 3; i++){
            
            /* 0 : Caractere
               1 : Nombre de bits 
               2 : Code */

            /* Valeur de n en fonction de j */
            switch(j){
            case 0:
                n = 8;
                break;
            case 1:
                n = 3; /* ou 4? car 256 car avec EOF */
                break;
            case 2:
                n = feuille->nb_bits;
                break;
            }

            for (j = n; j > 0; j--){
                bit = extraire_bit(paquet, index);

                switch(j){
                case 0:
                    break;
                case 1:
                    d
                }

                /* Si on a fini de parcourir le paquet */
                if (--index < 0){
                    paquet = fgetc(fic); /* On prend u nouveau paquet */
                    index = 7;
                }
            }
        }

        
        car = fgetc(fic);

        /* Caractere */
        car = fgetc(fic);
        a = car;
        fprintf(stdout, "< %c > %d : ", car, a);

        /* Creation de la feuille correspondante */
        if ((alphabet[a] = (noeud *) malloc(sizeof(noeud))) == NULL){
            printf("ERREUR lire_entete: echec malloc \n");
            exit(EXIT_FAILURE);
        }

        /* Nombre de bits */
        alphabet[a]->nb_bits = 0;
        index = 3;
        car = fgetc(fic);
        for(i=4 ; i > 0 ; i--){
            bit = extraire_bit(car, index+i);
            printf("%d", bit);
            if (bit == 1){
                alphabet[a]->nb_bits += pow(2, i-1);
            }
        }
            
        printf(" %d\n", alphabet[a]->nb_bits);

        /* Code */
        alphabet[a]->code = 0;
        for (i = alphabet[a]->nb_bits; i > 0; i--){

            if (index == 0){
                fgetc(fic);
                index = 8;
            }
            
            bit = extraire_bit(code, index);
            
            alphabet[a]->code = alphabet[a]->code << 1;
            alphabet[a]->code = alphabet[a]->code | bit;

            index--;
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