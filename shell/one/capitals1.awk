
BEGIN	{
    print "countryName  population  capital  continentName\n"
}
{print $0 }
END	{
    print "\nEND OF FILE"
} 

