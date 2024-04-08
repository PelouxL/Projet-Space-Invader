#ifndef HUFFMAN_H
#define HUFFMAN_H

#include<stdio.h>
#include<stdlib.h>

typedef struct noeud{
    int car; /* code ASCII */
    int occ;
    int code;
    int nb_bits;
    struct noeud *f_g;
    struct noeud *f_d;
}noeud;

void aff_f(FILE *fic);
void aff_cont(FILE* fic);

/* Compte le nombre d'occurence de chaque caratere dans le fichier fic.
tab[i] = le nombre d'occurence de i */
void occurence(FILE *fic, int tab[256]);

/* creer un noeud avec où car = index et occ = tab_occ */
noeud *creer_feuille(int tab_occ[256], int index);

/* Trouve les 2 entiers minimum contenus dans tab_occ et les places dans min */
void minimum(int tab_occ[256], int min[2]);

/* creer récursivement l'arbre d'huffman à partir des noeud contenu dans le tableau de pointeurs huffman. tab_occ sert à trouver les noeuds avec le moins d'occurences à chaque itération et taille correspond au nombre de noeuds/feuilles total dans l'arbre */
void creer_noeud(noeud *huffman[256], int tab_occ[256], int taille);

/* renvoi 1 si n est une feuille et 0 sinon */
int est_feuille(noeud *n);


#endif