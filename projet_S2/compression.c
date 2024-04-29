#include"compression.h"

int extraire_bit(int code, int index){
    int bit;
    
    bit = (code >> index)%2;
    return bit;
}

void entete(noeud *alphabet[N], FILE *res){
    int i, j, acc, bit, nb_feuille = 0, reste, op=0;
    noeud *feuille = NULL;
    char paquet = 0;

    /* Initialisation */
    acc = 8; /* Nombre de places dans le paquet (8 bits = 1 octet) */

    /* Comptage du nombre de feuille */
    for (i=0; i < N; i++){
        if (alphabet[i] != NULL){
            nb_feuille++;
        }
    }
    fprintf(res, "%c", nb_feuille);
    
    /* Caractere et code associe */
    for (i=0; i < N; i++){
        if ((feuille = alphabet[i]) != NULL){

            /* Caractere */
            fprintf(res, "%c", feuille->car);

            /* Nombre de bits sur les 4 1er bits du paquet */
            for (j=3; j >= 0; j--){
                reste = feuille->nb_bits;

                op=reste / pow(2, j);
                paquet = paquet << 1;
                paquet = paquet | op;
                
                reste %= pow(2, j) == 1;       
            }
            acc -= 4;

            /* Code */
            for (j = feuille->nb_bits; j > 0; j--){
                bit = extraire_bit(feuille->code, j-1);

                paquet = paquet << 1;
                paquet = paquet | bit;
                
                /* Verification de s'il reste de la place dans le paquet */
                if (--acc == 0){
                    fprintf(stdout, "%c\n", paquet); /* On ecrit le caractere dans res */
                    acc = 8;
                }
                
            }
        
            /* S'il reste encore de la place dans le paquet apres avoir ecrit le code */
            if (acc != 0 && acc != 8){
                paquet = paquet << acc; /* On rempli les places restantes */
                fprintf(res, "%c", paquet); /* On ecrit le caractere correspondant dans res */
            }
        }
    }
}

void contenu(noeud *alphabet[N], FILE *fic, FILE *res){
    int c, acc, bit, i;
    noeud *feuille = NULL;
    char paquet = 0;
    
    /* Initialisation */
    acc = 8; /* Nombre de places dans le paquet (8 bits = 1 octet) */
    
    /* Parcours du fichier */
    while((c = fgetc(fic)) != EOF){
        feuille = alphabet[c];

        printf("%c : %d bits\n", c, feuille->nb_bits);
        
        /* on place le code dans le paquet de bits */
        for (i = feuille->nb_bits; i > 0; i--){
            bit = extraire_bit(feuille->code, i-1);

            printf("%d bit renvoyé : %d\n", i, bit);

            /* Creation d'une place + insertion du bit dans le paquet */
            paquet = paquet << 1;
            paquet = paquet | bit;

            /* Verification de s'il reste de la place dans le paquet */
            if (--acc == 0){
                fprintf(res, "%c", paquet); /* On ecrit le caractere dans res */
                acc = 8;
            }
        }
    }

    /* Traitement de EOF de la maniere que les autres caracteres */
    feuille = alphabet[256]; /* 256 = code de EOF */
    for (i = feuille->nb_bits; i > 0; i--){
        
        bit = extraire_bit(feuille->code, i-1);
        
        printf("%d bit renvoyé : %d\n", i, bit);

        /* Creation d'une place + insertion du bit dans le paquet */
        paquet = paquet << 1;
        paquet = paquet | bit;

        if (--acc == 0){
            fprintf(res, "%c", paquet);
            acc = 8;
        }
    }
    
    /* S'il reste encore de la place dans le paquet */
    if (acc != 0 && acc != 8){
        paquet = paquet << acc; /* On rempli les places restantes */
        fprintf(res, "%c", paquet); /* On ecrit le caractere correspondant dans res */
        fprintf(stdout, "paquet plein : %c\n", paquet);
    }
        
}

void test(){
    char c = 0;
    
    c = c | 1;
    c = c << 2;
    c = c | 1;
    c = c << 1;
    c = c | 1;
    c = c << 2;
    c = c | 1;

    printf("TEST : %c\n", c); /* 0010 1101 */
        
}

void compression(noeud *alphabet[N], FILE *fic){
    FILE *res = NULL;

    res = fopen("cmp2.txt", "w+");
    if ((fic = fopen("exemples.txt", "r")) == NULL){
        printf("JE SUIS VIDE COMME TES COUILLES ENCULE\n");
        return;
    }

    entete(alphabet, res);
    contenu(alphabet, fic, res);

    fclose(res);
    fclose(fic);
}