#!/bin/bash

#This is the quiet version (no prints to terminal)

#Cleans Previous Run
rm results.csv

wget -q https://www.ynetnews.com/category/3082
grep -oP "https://www.ynetnews.com/article/[a-zA-Z0-9]+" 3082 > list.text
cat list.text | sort | uniq > sorted.list


amount=$(wc -l < sorted.list)
general_bibi=0
general_bennett=0


#Opener Line For Output
echo $amount >> results.csv


#Loop
for line in $(cat sorted.list)
do

wget -q -O ps_website $line

grep -o "Netanyahu" ps_website > bibi_text
grep -o "Bennett" ps_website > bennett_text

bibi=$(wc -w < bibi_text)
bennett=$(wc -w < bennett_text)

general_bibi=$(($bibi + $general_bibi))
general_bennett=$(($bennett + $general_bennett))

#Fills Outpus Line
if [[ $bibi -eq 0 && $bennett -eq 0 ]]; then
echo $line',''-, , , , ' >> results.csv
else
echo $line', Netanyahu, '$bibi', Bennett, '$bennett >> results.csv
fi

done

#cleans trash files from directory
rm 3082
rm bennett_text
rm bibi_text
rm sorted.list
rm list.text
rm ps_website