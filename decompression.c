#include"decompression.h"

void lire_entete(noeud *alphabet[N], FILE *fic){
    int i, j,
        n,           /* Nombre de bit a recuperer */
        bit,         /* Bit qu'on reupere dans le paquet */
        nb_feuille,
        index = 7,   /* La ou on en est dans le paquet */
        acc = 0;     /* Nombre de feuille trouvees */
    unsigned char paquet;
    noeud *feuille;

    /* Initialisation */
    for (i=0; i < N; i++){
        alphabet[i] = NULL;
    }

    /* Recuperation du nombre de feuilles differentes */
    nb_feuille = fgetc(fic);
    
    /* Lecture des paquets */
    paquet = fgetc(fic);
    while (acc < nb_feuille){

        /* Initialisation de la feuille */
        if ((feuille = (noeud *) malloc(sizeof(noeud))) == NULL){
            fprintf(stderr, "ERREUR lire_entete : echec malloc feuille\n");
            exit(EXIT_FAILURE);
        }
        feuille->car = 0;
        feuille->nb_bits = 0;
        feuille->code = 0;

        /* Recuperation caractere -> nb_bits -> code */
        for (i=0; i < 3; i++){
            
            /* 0 : Caractere
               1 : Nombre de bits 
               2 : Code */

            /* Valeur de n en fonction de i */
            switch(i){
            case 0:
                if (acc == nb_feuille-1){
                    n = 9;
                } else {
                    n = 8;
                }
                break;
            case 1:
                n = 3; /* ou 4? car 256 car avec EOF */
                break;
            case 2:
                n = feuille->nb_bits;
                break;
            }
            
            for (j = n; j > 0; j--){
                bit =  extraire_bit(paquet, index);
                bit = abs(bit);

                /* Insertion du bit dans la bonne variable */
                switch(i){
                case 0:
                    feuille->car = feuille->car << 1;
                    feuille->car = feuille->car | bit;
                    break;
                case 1:
                    feuille->nb_bits += bit * (int)pow(2, j-1);
                    break;
                case 2:                 
                    feuille->code = feuille->code << 1;
                    feuille->code = feuille->code | bit;
                    break;
                }

                /* Si on a fini de parcourir le paquet */
                if (--index < 0){
                    paquet = fgetc(fic); /* On prend u nouveau paquet */
                    index = 7;
                }
            }
        }

        /* Ajout de la feuille a alphabet */
        alphabet[feuille->car] = feuille;
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

    printf("------- DEBUT LIRE ENTETE ------- \n");
    lire_entete(alphabet, fic);

    /* Contenu de l'alphabet */
    for (i=0; i < N; i++){
        if (alphabet[i] != NULL){
            printf("%d < %c > ", i, alphabet[i]->car);
            affichage_code(alphabet[i]->nb_bits, alphabet[i]->code);
            printf("\n");
        }
    }
    printf("-------- FIN LIRE ENTETE -------- \n");

    fclose(fic);
}