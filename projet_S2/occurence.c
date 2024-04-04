#include <stdlib.h>
#include <stdio.h>

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
    return;
}


void aff_cont(FILE* fic){
  int g;

  while( (g=fgetc(fic)) != EOF ){
    printf("%c", g);
  }
  return ;
}



void occurence(FILE *fic, int tab[256]){
  int g, i;

  while( (g=fgetc(fic)) != EOF ){
    tab[g]+=1;
  }
  for(i=0 ; i< 256 ; i++){
    printf("%c : %d\n", i,tab[i]);
  }
  return ;
}


   

int main(){
  FILE * fic;
  int tab[256], i;

  for ( i = 0 ; i < 256 ; i++){ /* Initialisation de tab à 0 */
    tab[i]=0;
  }
  
  fic= fopen("exemples.txt", "r");
  if (fic == NULL ){
    printf("ERREUR main : lors de l'ouverture du fichier\n");
    exit(EXIT_FAILURE);
  }
  /* Affichage du contenue de fic */
  /*
  aff_f(fic);
  aff_cont(fic);
  */

  /* Prompt les occurences des caracteres de fic */
  occurence(fic, tab);

  fclose(fic);
  exit(EXIT_SUCCESS);
}
