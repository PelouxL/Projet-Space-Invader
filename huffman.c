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

void occurence(FILE *fic, int tab[N]){
  int c;

  while((c = fgetc(fic)) != EOF){
    tab[c] += 1;
  }
  
  /* On attribue a EOF le code 256 */
  tab[256] += 1;
  
}

/**********************************************/
/*     4.2 Creation de l'arbre de Huffman     */
/**********************************************/

noeud *creer_feuille(int tab_occ[N], int index){
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

void minimum(int tab_occ[N], int min[2]){
    int i;

    for (i=0; i < 2; i++){
        min[i] = -1;
    }

    for (i=0; i < N; i++){
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

void creer_noeud(noeud *huffman[N], int tab_occ[N], int taille){
    int min[2], i = 0;
    noeud *n;

    if (taille == 1){
        while(huffman[i] == NULL)
            i++;
        huffman[0] = huffman[i];
        huffman[i] = NULL;
        return;
    }

    /* Recherche des noeuds avec le moins d'occurence */
    minimum(tab_occ, min);

    /* Ajout du nb d'occurence de min[1] dans min[0] */
    tab_occ[min[0]] += tab_occ[min[1]];
    tab_occ[min[1]] = 0;

    /* Creation du nouveau noeud */
    if ((n = (noeud *) malloc(sizeof(noeud))) == NULL){
        printf("ERREUR creer_noeud: echec malloc\n");
        exit(EXIT_FAILURE);
    }
    
    /* total des occurence des min */
    n->occ = tab_occ[min[0]];
    n->nb_bits = 0;
    /* Les min deviennent les fils du nouveau noeud */
    if (min[0] != -1) n->f_g = huffman[min[0]];
    if (min[1] != -1) n->f_d = huffman[min[1]];

    /* Le nouveau noeud prend la place de min[0] dans huffman et min[1] est mis à null */
    huffman[min[0]] = n;
    huffman[min[1]] = NULL;

    printf("%c %c\n", huffman[min[0]]->f_d->car, huffman[min[0]]->f_g->car);

    /* Rappel de la fonction pour creer l'arbre recursivement */
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
  
