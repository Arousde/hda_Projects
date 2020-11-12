#!/bin/bash
# dvdcopy.sh - A sample shell script to display a progress bar
# set counter to 0 
typeset -i age=18
typeset -i var=0
typeset -i days=56
typeset -i plage=6
typeset -i counter=0
typeset -i no=1
dcounter=0
money=5
 
(
while [ $age -lt 70  ]
do
bldate=$(date +%Y-%m-%d -d "$var days")
cat <<EOF
XXX
$dcounter
NO : $no   date : $bldate    Age : $age  $money Euro
XXX
EOF
counter=$counter+1 
if [ $counter -eq 6 ] ; then
age=$age+1 
counter=0
if [ $dcounter -lt 100 ] ; then
(( dcounter+=2 ))
fi
fi
var=$var+56 
no=$no+1
(( money+=5 ))
sleep 0.5
done
)|
dialog --title "blood donation" --gauge "Please wait" 7 70 0

#$'Donation No\tDate of Donation\tAge'
#$no $'\t\t' $bldate $'\t\t' $age ( $dcounter%):


# dcounter=0
# (
# # set infinite while loop
# while :
# do
# cat <<EOF
# XXX
# $dcounter
# Disk copy /dev/dvd to /home/data ( $dcounter%):
# XXX
# EOF
# # increase counter by 10
# (( dcounter+=10 ))
# [ $dcounter -eq 100 ] && break
# # delay it a specified amount of time i.e 1 sec
# done
# ) |
# dialog --title "File Copy" --gauge "Please wait" 7 70 0
