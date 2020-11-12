#!/bin/sh
counter=1
number1=1
number2=$number1
echo $number1
echo $number2
while [ $counter -lt 20 ]; do
result=` expr $number1 + $number2 `
echo $result
number1=$number2
number2=$result
counter=` expr $counter + 1`
done