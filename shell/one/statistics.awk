BEGIN	{
    FS=",";
    totalcitizens=0
    maxpop=0
    maxpopname=""
    minpopname=""
    minpop=1
    x = 0
}

{
#total
totalcitizens = $2 + totalcitizens
#max pop
if (maxpop < $2) {
    maxpop = $2
    maxpopname = $1
}
#minpop
if (minpop > $2) {
    minpop = $2
    minpopname = $1
}
#most capitals
if (map[$4]!= "") {
    map[$4]= map[$4]+1
}else {
    map[$4] = 1 
}

#citizens per continent
if (citizens[$4]!= "") {
    citizens[$4]= citizens[$4]+ $2
}else {
    citizens[$4] = $2 
}

}

END	{
    print " statistics for : \t" FILENAME   
    print "\n the total number of citizens in all capitals is :\t" totalcitizens  
    print "\n the city with the biggest population is :\t" maxpopname  
    print "\n the city with the smallest population is :\t" minpopname
    print "\n"
    print " the continent with most capitals : \n"
    for (x in map) {
        sortedmap[map[x]] = x
    }
    for (x in sortedmap) {
         most = x 
    }
    print " "sortedmap[x] "\t" ":  " most 
    
    print "\n number of citizens per continent : \n"
    for (x in citizens)
    print " " x " " ":" " " citizens[x]
}