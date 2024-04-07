#include<stdlib.h>
#include<stdio.h>

typedef struct noeud{
  char r;
  int occ;
  int *code;
  int nb_bits;
  struct noeud *f_g;
  struct noeud *f_d;
}noeud;

typedef noeud * arbre;

void creer_feuille(char c, arbre huffman[256]){

  int i;
  i=c;
  huffman[i] = (arbre ) malloc(sizeof(noeud));
  if( huffman[i] == NULL){
    printf("ERREUR d'allocation mémoire lors de la creation du noeud pour %c\n", c);
    exit(EXIT_FAILURE);
  }
  huffman[i]->r = c;
  huffman[i]->occ = 1;
  huffman[i]->f_g = NULL;
  huffman[i]->f_d = NULL;
  return ;
  
}

void creer_noeud

void plusPetit(arbre huffman[256]){
  int i;
  arbre min1, min2;
  min1 = NULL;
  min2 = NULL;
  for( i = 2 ; i < 256 ; i++ ){
    if (huffman[i] != NULL){
      if(min1 == NULL && min2 == NULL){
	min1 = huffman[i];
	min2 = huffman[i];
      }
      if(huffman[i]->occ < min1->occ){
	
	if(huffman[i]->occ < min2->occ){
	  
	  if(min1->occ < min2->occ){
	    min2 = huffman[i];
	  }else{
	    min1 = huffman[i];
	  }
	  
	}else{
	  min1 = huffman[i];
	}
      }else{
	if( huffman[i]->occ < min2->occ){
	  min2 = huffman[i];
	}
	  
      }
      
    }
  }
  printf(" min1 : %c et min2 : %c\n",min1->r, min2->r);
  return ;
}


  
      
int main(){
  arbre huffman[256];
  FILE * fic = NULL;
  int g, i;

  fic = fopen("exemples.txt", "r");
  if (fic == NULL ){
    printf("ERREUR main : lors de l'ouverture du fichier\n");
    exit(EXIT_FAILURE);
  }

  /* initialisation de Huffman */
  for( i = 0 ; i < 256 ; i++){
    huffman[i] = NULL;
  }

  /* parcours du fichier et creation des noeuds */
  while((g = fgetc(fic)) != EOF ){
    if(huffman[g] == NULL){
      creer_feuille(g, huffman);
    }else{
      huffman[g]->occ+=1;
    } 
  }

  /* Affichage des occurences des caracteres dans le fichier */
  for( i = 0 ; i < 256 ; i++){
    if(huffman[i] != NULL){
      printf("%c : %d\n", huffman[i]->r, huffman[i]->occ);
    }
  }

  plusPetit(huffman);
  
  /* Liberation de l'espace allouer */
  for( i = 0 ; i < 256 ; i++){
    if( huffman[i] != NULL){
      free(huffman[i]);
    }
  }
  exit(EXIT_SUCCESS);
}
  
