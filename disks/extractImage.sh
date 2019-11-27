# this program extracts a 77 track, single side, 26 sector 128 byte disk from the InterMedia for Windows format and converts it into a raw sector dump. 
# Two parameters. First is the input IMW disk and the second is the output raw disk image.
#!/bin/bash
echo $0
dd if=$1 skip=69 bs=1 of=$1.header_removed
split -b 3416 $1.header_removed $1.track
for i in $1.track* 
do 
    echo $i
    dd if=$i skip=62 bs=1 of=$i.header_removed
    split -b 129 $i.header_removed $i.sector.
    for j in $i.sector.*
    do
	echo $j
	dd if=$j bs=1 skip=1 of=$j.sector.stripped
	cat $j.sector.stripped >> $2
	rm $j.sector.stripped
	rm $j
    done
    rm $i
    rm $i.header_removed
done  