#!/bin/bash
typeset -i yer1
typeset -i yer2

echo "population gnuplot"
echo "please enter a county code "
read code 
codlen=${#code} 
if [ $codlen -ne 3 ] ; then 
echo "county code should only contain 3 character"
exit 1 
fi
echo "please enter a range in years in this form 1960-2014"
read years 
yerlen=${#years} 
if [ $yerlen -ne 9 ] ; then 
echo "bad input"
exit 1 
fi


read yer1 <<< $(echo $years|awk -F'[-]' '{  print $1}' )
read yer2 <<< $(echo $years|awk -F'[-]' '{  print $2}' )
if [ $yer1 -lt 1960 ] ; then 
echo "between 1960 and 2014"
exit 1 
fi
if [ $yer2 -gt 2014 ] ; then 
echo "between 1960 and 2014"
exit 1 
fi
awk -v wkcode=$code -v wkyer1=$yer1 -v wkyer2=$yer2  -F'[,]' '{ if ($2 == wkcode && $3 >= wkyer1  && $3 <= wkyer2) print $1 " " $2 " " $3 " " $4 " " }' population.csv > stat.txt
cat plot.conf | gnuplot
