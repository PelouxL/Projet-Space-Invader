#include"huffman.h"

/*********************************************/
/*       4.1 Occurences des caractères       */
/*********************************************/

void aff_f(FILE *fic){
    char s[20];
    
    if(fread(&s, sizeof(s), 1, fic) < 1){ 
      printf("erreur lors du fread.\n");
      return ;
    }
    printf("%s\n" ,s); 
}

void aff_cont(FILE* fic){
  int g;

  while((g=fgetc(fic)) != EOF){
    printf("%c", g);
  }
}

void occurence(FILE *fic, int tab[256]){
  int c;

  while((c = fgetc(fic)) != EOF){
    tab[c] += 1;
  }
}

/**********************************************/
/*     4.2 Creation de l'arbre de Huffman     */
/**********************************************/

noeud *creer_feuille(int tab_occ[256], int index){
    noeud *f = NULL;

    if ((f = (noeud *) malloc(sizeof(noeud))) == NULL){
        printf("ERREUR creer_feuille: echec malloc \n");
        exit(EXIT_FAILURE);
    }

    f->car = index;
    f->occ = tab_occ[index];
    f->nb_bits = 0;
    f->f_g = NULL;
    f->f_d = NULL;

    return f;
}

void minimum(int tab_occ[256], int min[2]){
    int i;

    for (i=0; i < 2; i++){
        min[i] = -1;
    }

    for (i=0; i < 256; i++){
        if (tab_occ[i] != 0){
            /* initialisation des min */
            if (min[0] == -1){
                min[0] = i;
            } else if (min[1] == -1){
                min[1] = i;
            } else {
                /* recherche des plus petit */
                if (tab_occ[i] < tab_occ[min[0]]){
                    if (tab_occ[min[0]] < tab_occ[min[1]]){
                        min[1] = i;
                    } else {
                        min[0] = i;
                    }
                } else if (tab_occ[i] < tab_occ[min[1]]){
                    min[1] = i;
                }       
            }   
        }
    }
}

void creer_noeud(noeud *huffman[256], int tab_occ[256], int taille){
    int min[2];
    noeud *n;

    if (taille == 1){
        return;
    }
    
    minimum(tab_occ, min);

    tab_occ[min[0]] += tab_occ[min[1]];
    tab_occ[min[1]] = 0;
        
    if ((n = (noeud *) malloc(sizeof(noeud))) == NULL){
        printf("ERREUR creer_noeud: echec malloc\n");
        exit(EXIT_FAILURE);
    }

    n->occ = tab_occ[min[0]];
    n->nb_bits = 0;
    if (min[0] != -1) n->f_g = huffman[min[0]];
    if (min[1] != -1) n->f_d = huffman[min[1]];

    huffman[min[0]] = n;
    huffman[min[1]] = NULL;

    printf("%c %c\n", huffman[min[0]]->f_d->car, huffman[min[0]]->f_g->car);

    creer_noeud(huffman, tab_occ, taille-1);
}

/**********************************************/
/*          Fonctions supplémentaires         */
/**********************************************/

int est_feuille(noeud *n){
    if (n->f_g == NULL && n->f_d == NULL){
        return 1;
    }
    return 0;
}
      
/* int main(){ */
/*     noeud *huffman[256]; */
/*     FILE *fic = NULL; */
/*     int g, i, *tab_occ, taille = 0; */

/*     /\* Initialisation *\/ */
/*     if ((fic = fopen("exemples.txt", "r")) == NULL ){ */
/*         printf("ERREUR main : lors de l'ouverture du fichier\n"); */
/*         exit(EXIT_FAILURE); */
/*     } */

/*     if ((tab_occ = (int *) calloc(256, sizeof(int))) == NULL){ */
/*         printf("ERREUR main: echec calloc tab"); */
/*         exit(EXIT_FAILURE); */
/*     } */
    
/*     for(i = 0 ; i < 256 ; i++){ */
/*         huffman[i] = NULL; /\* initialisation de Huffman *\/ */
/*     } */

/*     /\* Parcours du fichier et creation des noeuds *\/ */
/*     while((g = fgetc(fic)) != EOF ){ */
/*         tab_occ[g] += 1; */
/*     } */
/*     occurence(fic, tab_occ); */

/*     for (i=0; i < 256; i++){ */
/*         if (tab_occ[i] > 0){ */
/*             if ((huffman[i] = (noeud *) malloc(sizeof(noeud))) == NULL){ */
/*                 printf("ERREUR main: echec malloc huffman[%c]\n", i); */
/*                 exit(EXIT_FAILURE); */
/*             } */
/*             huffman[i] = creer_feuille(tab_occ, i); */
/*             taille++; */
/*         } */
/*     } */

/*     /\* Affichage des occurences des caracteres dans le fichier *\/ */
/*     for(i=0; i < 256; i++){ */
/*         if(huffman[i] != NULL){ */
/*             printf("%c : %d\n", huffman[i]->car, huffman[i]->occ); */
/*         } */
/*     } */

/*     /\* Création d'un nouveau noeud *\/ */
/*     creer_noeud(huffman, tab_occ, taille); */
    
/*     /\* Liberation de l'espace allouer *\/ */
/*     for(i=0; i < 256; i++){ */
/*         if( huffman[i] != NULL){ */
/*             free(huffman[i]); */
/*         } */
/*     } */
/*     exit(EXIT_SUCCESS); */
/* } */
  
