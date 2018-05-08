ADRIEN MAINKA 3407003

J'ai implémenté le filtre de Harris en C.

Le travail demandé pour les exercices 1 et 2 se trouve dans les fichier harris.c et functions.c (pour l'exercice 1) et sloc.c (pour l'exercice 2), tout

Pour harris, on peut lui donner en paramètres les valeurs de Kappa, sigma et t avec les options -K -s -t réspectivement, sinon les paramètres par défaut sont kappa = 0.02, sigma = 2, t=0.001.

Pour sloc on peut choisir un seuil avec l'option -n, qui est par défaut à 0.5.

Pour l'exercice 3, j'ai réussi en chainant les commandes à dessiner des points avec xvisdraw et la sortie de sloc, mais je n'ai pas réussi à paramétrer la couleur et dessiner des lignes, c'est pourquoi j'ai modifié sloc pour qu'il ecrive dans la sortie standard chaque pixel de chaque croix.


Le script test.sh permet de lancer un test de detection de coin, avec des paramètres. Il peut etre modifier.
