#! /bin/bash



fmoy -x 3 -y 3 camgaussien.inr.gz camgaussien2.inr.gz
fmoy -x 5 -y 5 camgaussien.inr.gz camgaussien3.inr.gz
fmoy -x 7 -y 7 camgaussien.inr.gz camgaussien4.inr.gz

echo
echo
echo "Image d'origine"
echo
echo

xvis camgaussien.inr.gz 2>/dev/null

echo
echo
echo "Image après application d'un filtre moyenneur 3x3"
echo
echo


xvis camgaussien2.inr.gz 2>/dev/null

echo
echo
echo "Image après application d'un filtre moyenneur 5x5"
echo
echo


xvis camgaussien3.inr.gz 2>/dev/null

echo
echo
echo "Image après application d'un filtre moyenneur 7x7"
echo
echo


xvis camgaussien4.inr.gz 2>/dev/null

echo
echo
echo "Suppression des images créées"
echo
echo


rm -f camgaussien[2-4].inr.gz
