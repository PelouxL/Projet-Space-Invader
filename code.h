#ifndef CODE_H
#define CODE_H

#include"huffman.h"
#include<math.h>

/* Affiche le code entree en parametre de maniere recursive bit par bit */
void affichage_code(int nb_bits, int code);

/* Construit l'arbre d'huffman et donne un code a chaque caractere avec au moins une occurence */
void creer_code(noeud *element, int code, int profondeur);

#endif