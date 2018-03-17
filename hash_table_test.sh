# /bin/sh

READFILE='./prime/primes.txt'
rm output.txt
rm opt.txt

while read line;do
	echo 3 | sudo tee /proc/sys/vm/drop_caches
    # perf stat --repeat 100\
        # -e cache-misses,cache-references,instructions,cycles\
    ./phonebook_opt $line
    # ./calculate $line
    # rm opt.txt
done < $READFILE
