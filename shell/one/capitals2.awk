function colheader() {
        printf (" \n %-50s  %20s  %30s  %20s  \n " , "CountryName" , "Population" , "Capital", "\tContinent Name \n"); 

}
BEGIN	{
    FS=",";
    lines = 0 
    colheader()
}
{
    #print $1"\t"$2"\t"$3"\t"$4
    printf (" %-50s  %20s  %30s  %20s \n " , $1 , $2 , $3 , $4)  
    if (NR >= 30) {
            colheader()
            NR = 0 
    }
        lines = lines + 1

} 

END	{
    print "\nEND OF FILE\n"
    print  "File name : "FILENAME "\t" "Number of lines : "lines "\n"
} 
