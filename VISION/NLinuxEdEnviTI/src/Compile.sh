# Compilation des Fichiers
# gcc -c EdSimpleScan EdSimpleScan.c EdLibSimpleScan.c EdUtilities.c


#gcc -W EdClassicThr.c EdLibClassicThr.c EdUtilities.c -o ../bin/EdClassicThr

#echo "Compilation EdSimpleScan terminee"


#gcc -o EdScanVois3 EdScanVois3.c EdLibScanVois3.c EdUtilities.c
#mv EdScanVois3 ../bin/
##echo "Compilation EdScanVois3 terminee" 
#
#

#set  Filename = "MeanFiltring"
#gcc -W EdMeanFiltring.c EdLibMeanFiltring.c EdUtilities.c -o ../bin/EdMeanFiltring
#echo "Compilation EdMeanFiltring terminee"

set  Filename = "GaussFiltring"
gcc -W EdGaussFiltring.c EdLibGaussFiltring.c EdUtilities.c -o ../bin/EdGaussFiltring
echo "Compilation GaussFiltring terminee"

gcc -W EdMedianFiltring.c EdLibMedianFiltring.c EdUtilities.c -o ../bin/EdMedianFiltring
echo "Compilation MedianFiltring terminee"





