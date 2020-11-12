#!/bin/bash
typeset -i age=18
typeset -i var=0
typeset -i days=56
typeset -i plage=6
typeset -i counter=0
typeset -i no=1
echo $'Donation No\tDate of Donation\tAge'
echo " "
while [ $age -lt 70  ]
do
bldate=$(date +%Y-%m-%d -d "$var days")
echo $no $'\t\t' $bldate $'\t\t' $age
counter=$counter+1 
if [ $counter -eq 6 ] ; then
age=$age+1 
counter=0
fi
var=$var+56 
no=$no+1
done
