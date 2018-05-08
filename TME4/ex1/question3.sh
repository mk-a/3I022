#! /bin/bash



fmoy -x 3 -y 3 rectangle.inr.gz rectangle2.inr.gz
fmoy -x 5 -y 5 rectangle.inr.gz rectangle3.inr.gz
fmoy -x 7 -y 7 rectangle.inr.gz rectangle4.inr.gz

echo
echo
echo "Image d'origine"
echo
echo

xvis rectangle.inr.gz 2>/dev/null

echo "Profil des niveaux de la ligne 64 de l'image d'origine"
extg rectangle.inr.gz -iy 64 -y 1 | tpr -l 1 -c | nl | xgraph 2>/dev/null
echo
echo



echo
echo
echo "Image après application d'un filtre moyenneur 3x3"
echo
echo


xvis rectangle2.inr.gz 2>/dev/null
echo "Profil des niveaux de la ligne 64 de l'image après application d'un filtre moyenneur 3x3"
extg rectangle.inr.gz -iy 64 -y 1 | tpr -l 1 -c | nl | xgraph 2>/dev/null
echo
echo


echo
echo
echo "Image après application d'un filtre moyenneur 5x5"
echo
echo


xvis rectangle3.inr.gz 2>/dev/null
echo "Profil des niveaux de la ligne 64 de l'image après application d'un filtre moyenneur 5x5"
extg rectangle.inr.gz -iy 64 -y 1 | tpr -l 1 -c | nl | xgraph 2>/dev/null
echo
echo


echo
echo
echo "Image après application d'un filtre moyenneur 7x7"
echo
echo


xvis rectangle4.inr.gz 2>/dev/null
echo "Profil des niveaux de la ligne 64 de l'image après application d'un filtre moyenneur 7x7"
extg rectangle.inr.gz -iy 64 -y 1 | tpr -l 1 -c | nl | xgraph 2>/dev/null
echo
echo


echo
echo
echo "Suppression des images créées"
echo
echo


rm -f rectangle[2-4].inr.gz
