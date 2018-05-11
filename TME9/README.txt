Compte rendu du TME:

Test de compression sur muscle.pgm, car le format pgm n'est pas compressé.
muscle.pgm pèse 65 551 o

avec l'utilisation de l'encodage de Huffman

commande utilisée:        ./inr2huff img/muscle.pgm img/test.inr
l'image pèse :            61 914 o
taux de compression :     1,058742772
commande pour décoder:    ./huff2inr img/test.inr img/muscle.inr

avec utilisation d'un prédicteur spatial et de l'encodage de Huffman

commande utilisée:        ./mat2lpc img/muscle.pgm | ./inr2huff >img/test.inr
l'image pèse :            47 554 o
taux de compression :     1,378453968
commande pour décoder :   ./huff2inr img/test.inr | ./lpc2mat > img/muscle.inr
