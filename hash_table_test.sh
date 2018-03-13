# /bin/sh
rm output.txt
rm opt.txt

for ((i=1000;i<=350000;i+=5000)) ; do
	echo 3 | sudo tee /proc/sys/vm/drop_caches
    perf stat --repeat 100\
        -e cache-misses,cache-references,instructions,cycles\
    ./phonebook_opt $i
    ./calculate $i
    rm opt.txt
done
