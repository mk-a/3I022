Author: 



l'executable ./hough prend en entrée (premier paramètre ou entrée standard) une image de contour, et ecrit dans le second paramètre ou sa sortie standard l'accumulateur. Elle affiche dans sa sortie standard les points d'intersectios des droites trouvées et des bords de l'images. Des options peuvent être spécifiées:
-t : tolérance
-st : pas d'incrémentation de theta
-sr : pas d'incrémentation de r
-n  :  nombre de droites à afficher

le script ex1.sh prend une image, calcul ses contours et ensuite affiche l'image avec les droites trouvées dans cette image

l'executable ./houghCircle prend en entré une image de contours et de la même facon que ./hough cherche les cercles présents dans l'image.
