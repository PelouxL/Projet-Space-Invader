#include"huffman.h"
#include"code.h"

/* void entete(noeud *alphabet[256], FILE *fic, FILE *res){ */
/*     int i, nb_feuille = 0; */

/*     /\* Comptage du nombre de feuille *\/ */
/*     for (i=0; i < 256; i++){ */
/*         if (alphabet[i] != NULL){ */
/*             nb_feuille++;            */
/*         } */
/*     } */
    
/*     /\* ecrire le nombre de feuilles *\/ */
    
/*     /\* Code *\/ */
/*     for (i=0; i < 256; i++){ */
/*         if (alphabet[i] != NULL){ */
/*             fwrite(alphabet[i]->car, 1, 1, res); */
            
/*         } */
/*     } */
/* } */

int extraire_bit(int code, int index){
    int bit;
    
    bit = (code >> index)%2;
    return bit;
}

void contenu(noeud *alphabet[256], FILE *fic, FILE *res){
    int c, acc, bit, i;
    noeud *feuille;
    char paquet = 0;
    
    /* Initialisation */
    acc = 8; /* Nombre de bits dans un char */
    
    /* Parcours du fichier */
    while((c = fgetc(fic)) != EOF){
        feuille = alphabet[c];

        printf("%c : %d bits\n", c, feuille->nb_bits);
        
        /* on place le code dans le paquet de bits */
        for (i = feuille->nb_bits; i > 0; i--){
            bit = extraire_bit(feuille->code, i-1);

            printf("%d bit renvoyé : %d\n", i, bit);

            paquet = paquet | bit;
            paquet = paquet << 1;
            
            if (--acc == 0){
                /* fwrite(paquet, 1, 1, res); */
                fprintf(stdin, "%c", paquet);
                paquet = paquet << 8;
                acc = 8;
            }
        }
    }

    if (acc != 0 && acc != 8){
        paquet = paquet << acc;
        fprintf(stdin, "%c", paquet);
    }
        
}

void test(){
    char c;
    
    c = c | 1;
    c = c << 2;
    c = c | 1;
    c = c << 1;
    c = c | 1;
    c = c << 2;
    c = c | 1;

    printf("TEST : %c\n", c); /* 0010 1101 */
        
}

void compression(noeud *alphabet[256], FILE *fic){
    FILE *res = NULL;

    res = fopen("cmp.txt", "a");
    if ((fic = fopen("exemples.txt", "r")) == NULL){
        printf("JE SUIS VIDE ENCULE\n");
        return;
    }

    contenu(alphabet, fic, res);
    printf("\n");

    fclose(res);
    fclose(fic);
}

/* a = 00001001; */
/* b = 00001010; */

/* ab = 0000100100001010 */
    

/* c */
/* copie = c >> i */
/*     7 0 */

/*     001 */


/* 0000 0001 */

/*     0000 0101 */
    
/* abc */
/* a 01 */
/* b 11 */
/* c 00 */
/*     d 010 */

/* 011100 */

/* 0000 1111 << 4 */
/* 1111 0000 */

/* 001 1001 1010 */

/*     Une banane */


/*     3a01 */
/*     0100 0000 */
    
/*     b11c00;efkhhgkegneljn. */