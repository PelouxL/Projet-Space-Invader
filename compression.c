#include"compression.h"

int extraire_bit(int code, int index){
    int bit;
    bit = (code >> index)%2;
  
    return bit;
}

void entete(noeud *alphabet[N], FILE *res){
    int i, j, k,
        reste = 0,
        nb_feuille = 0,
        n,          /* Nombre de bit a inserer dans le paquet */
        bit,        /* Bit (0 ou 1) que l'on insere dans le paquet */
        place = 8;  /* Nombre de places dans un octet */
    noeud *feuille = NULL;
    char paquet = 0;

    /* Comptage du nombre de feuille */
    for (i=0; i < N; i++){
        if (alphabet[i] != NULL){
            nb_feuille++;
        }
    }
    fputc(nb_feuille, res);
    
    /* Caractere et code associe */
    for (i=0; i < N; i++){
        if ((feuille = alphabet[i]) != NULL){
            for (j=0; j < 3; j++){
                
                /* 0 : Caractere
                   1 : Nombre de bits 
                   2 : Code */

                /* Valeur de n en fonction de j */
                switch(j){
                case 0:
                    if (i == N-1){
                        n = 9;
                    } else {
                        n = 8;
                    }
                    break;
                case 1:
                    n = 3; /* ou 4? car 256 car avec EOF */
                    reste = feuille->nb_bits;
                    break;
                case 2:
                    n = feuille->nb_bits;
                    break;
                }
                
                for (k = n-1; k >= 0; k--){
                    /* Valeur de bit en fontion de j */
                    switch (j){
                    case 0 :
                        bit = extraire_bit(feuille->car, k);
                        break;
                    case 1 :
                        bit = reste / (int)pow(2, k);
                        reste %= (int)pow(2, k);
                        break;
                    case 2 :
                        bit = extraire_bit(feuille->code, k);
                        break;
                    }

                    /* Insertion du bit dans le paquet */
                    paquet = paquet << 1;
                    paquet = paquet | bit;
            
                    /* Verification de s'il reste de la place dans le paquet */
                    if (--place == 0){
                        fputc(paquet, res); /* On ecrit le caractere dans res */
                        place = 8;
                    }
                }
                
            }
        }
    }
    
    /* Si l'entete est finie mais qu'il reste des bits dans le paquet */
    if (place < 8){
        paquet = paquet << place; /* On "utilise" les places restantes */
        fputc(paquet, res); /* On ecrit le caractere correspondant dans res */
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

        /* printf("%c : %d bits\n", c, feuille->nb_bits); */
        
        /* on place le code dans le paquet de bits */
        for (i = feuille->nb_bits; i > 0; i--){
            bit = extraire_bit(feuille->code, i-1);

            /* printf("%d bit renvoyé : %d\n", i, bit); */

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
        
        /* printf("%d bit renvoyé : %d\n", i, bit); */

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