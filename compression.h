#ifndef COMPRESSION_H
#define COMPRESSION_H

#include"huffman.h"
#include"code.h"

/* Compresse fic dans un nouveau fichier avec une entete et le contenu separes par un retour a la ligne */
void compression(noeud *alphabet[N], FILE *fic);

int extraire_bit(int code, int index);

void test();

#endif