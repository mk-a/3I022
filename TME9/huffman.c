#include <stdlib.h>
#include <string.h>
#include "huffman.h"

struct node {
  unsigned char v;
  float f;
  struct node *b0,*b1;
};


/* procedure qui creee un noeud */
static struct node *nouv_noeud( unsigned char var, float freq,
				struct node *b0, struct node *b1) {
  struct node *n = (struct node*)malloc(sizeof(struct node));
  n->b0=b0; n->b1=b1;
  n->v=var; n->f=freq;
  return n;
}

/* cherche le min parmi les elements du tableau des noeuds */
static struct node* cherche_noeud( int *index, struct node **tn, int L) {
  float min = 2;
  int i;

  for( i=0; i<L; i++)
    /* les entrees a NULL correspondent a des noeuds deja
     * fusionnes: on ne les visite pas */
    if( tn[i] && tn[i]->f < min) {
      min=tn[i]->f;
      *index=i;
    }
  return tn[*index];
}

/**
 * Créer l'arbre de Huffman à partir d'un histogramme normalisé
 * @param his histogramme normalisé
 * @param L taille du tableau his
 * @return la racine de l'arbre de Huffman
 */

static struct node *creer_arbre( float *his, int L) {
  struct node **tn, *n1, *n2;
  int imin1, imin2, i;

  /* init */
  tn = (struct node **) malloc(sizeof(struct node*)*L);
  for( i=0; i<L;i++)
    tn[i] = nouv_noeud( i, his[i], NULL, NULL);

  /* creation de l'arbre */
  for(;;) {
    n1 = cherche_noeud( &imin1, tn, L);
    tn[imin1] = NULL;
    n2 = cherche_noeud( &imin2, tn, L);
    /* -1 est non signifiant ici */
    if( n2) tn[imin2] = nouv_noeud( -1, n1->f+n2->f, n1, n2);
    else break;
  }
  return n1;
}

/**
 * Parcours de l'arbre de Huffman pour remplir
 * la table.
 * @param n arbre de Huffman
 * @param table table de Huffman
 * @param code tableau auxiliaire
 */

static void litcode( struct node *n, char **table, char *code) {
  char cp[100];

  if( n->b0) {
    strcpy(cp,code);
    litcode(n->b0, table, strcat(code,"0"));
    strcpy(code,cp);
    litcode(n->b1, table, strcat(code,"1"));
  } else
    table[n->v] = strdup(code);

  /* on libere apres parcours */
  free(n);
}

/**
 * Calcul la table de Huffman à partir d'un histogramme normalisé
 * @param his histogramme
 * @param table table de Huffman
 * @param L taille du tableau his
 */

void hufftable( float *his, char **table, int L) {
  struct node *n;
  char code[100];

  n = creer_arbre( his, L);
  *code = 0;
  litcode( n, table, code);
}

void freecode( char **table, int L) {
  int i;
  for( i=0;i<L;i++)
    free(table[i]);
}

/**
 * Ecrit un bit dans un tampon.
 * @param s tampon.
 * @param val valeur du bit a ecrire ('0' ou '1').
 * @param b position absolue dans le tampon s du bit a ecrire.
 * Les bits dans s sont numerotes ainsi:
 * 0       1       2
 * 01234567012345670123 ...
 */

static void ecritbit( unsigned char *s, long b, char val) {
  int byte = b / 8;
  int bit = 7 - b % 8;

  s += byte;
  if( val == '1')
    *s |= (1<<bit);
  else
    *s &= ~(1<<bit);
}


/**
 * Encoder un tampon en utilisant la table de Huffman.
 * @param out tampon a ecrire
 * @param in tampon a encoder
 * @param size taille du tampon in
 * @param table de Huffman
 * @return nombre de bits effectivement écrit dans out
 */

int huffenc( unsigned char *out, unsigned char *in,
	     long size, char **table) {
  char *bit;
  long nbits=0;

  while( size --) {
    for( bit = table[*in]; *bit; bit ++)
      ecritbit( out, nbits++, *bit);
    in++;
  }
  return nbits;
}


/**
 * lit un bit dans un tampon
 */

static
char litbit( unsigned char *s, long b) {
  int byte = b / 8;
  int bit = 7 - b % 8;
  return (*(s+byte) & (1<<bit)) ? '1':'0';
}


/**
 * Cherche un element dans la table de Huffman
 */
static int findcode( char *bit, char **code, int n) {
  int i;
  for( i=0; i<n; i++)
    if( !strcmp(bit,code[i]))
      return i;
  return -1;
}

/**
 * decode un tampon compresse par Huffman
 * @param out tampon decode
 * @param in  tampon encode
 * @param sin taille du tampon in
 * @param table table de Huffman
 * @param ncode taille de la table de Huffman
 */
void huffdec( unsigned char *out, unsigned char *in,
	      long sin, char **table, int ncode) {
  long bit = 0;
  char c[20], v[2]= "0";
  int n;

  while( bit<sin) {
    *c = 0;
    do {
      v[0] = litbit( in, bit++);
      strcat(c, v);
    } while( (n=findcode(c, table, ncode)) == -1) ;
    *out++ = n;
  }
}
