CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99
CFLAGS_orig = -O0
CFLAGS_opt  = -O0

EXEC = phonebook_orig phonebook_mempool phonebook_fuzzy phonebook_avltree phonebook_smaz phonebook_hash phonebook_opt

GIT_HOOKS := .git/hooks/applied
.PHONY: all
all: $(GIT_HOOKS) $(EXEC)

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

SRCS_common = main.c

phonebook_orig: $(SRCS_common) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

phonebook_opt: $(SRCS_common) phonebook_opt.c phonebook_opt.h hash_function.o mem_pool.o avltree.o smaz/smaz.o
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c hash_function.o mem_pool.o avltree.o smaz/smaz.o

phonebook_hash: $(SRCS_common) phonebook_hash.c phonebook_hash.h hash_function.o
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DIMPL="\"$@.h\"" -DHASH -o $@ \
		$(SRCS_common) $@.c hash_function.o

phonebook_mempool: $(SRCS_common) phonebook_mempool.c phonebook_mempool.h mem_pool.o
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DIMPL="\"$@.h\"" -DMEM_POOL -o $@ \
		$(SRCS_common) $@.c mem_pool.o

phonebook_fuzzy: fuzzyfind.c phonebook_fuzzy.c phonebook_fuzzy.h fuzzy.o
	$(CC) $(CFLAGS_common) -g $(CFLAGS_opt) \
		-DIMPL="\"$@.h\"" -DFUZZY -o $@ \
		fuzzyfind.c $@.c fuzzy.o

phonebook_avltree: $(SRCS_common) phonebook_avltree.c phonebook_avltree.h avltree.o
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DIMPL="\"$@.h\"" -DAVLTREE -o $@ \
		$(SRCS_common) $@.c avltree.o

phonebook_smaz: $(SRCS_common) phonebook_smaz.c phonebook_smaz.h smaz/smaz.o
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DIMPL="\"$@.h\"" -DSMAZ -o $@ \
		$(SRCS_common) $@.c smaz/smaz.o

run: $(EXEC)
	echo 3 | sudo tee /proc/sys/vm/drop_caches
	watch -d -t "./phonebook_orig && echo 3 | sudo tee /proc/sys/vm/drop_caches"

cache-test: $(EXEC)
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_orig
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_opt

output.txt: cache-test calculate
	./calculate

plot: output.txt
	gnuplot scripts/runtime.gp

calculate: calculate.c
	$(CC) $(CFLAGS_common) $^ -o $@

clear_cache:
	@echo 1 | sudo tee /proc/sys/vm/drop_caches

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.* \
	      	calculate orig.txt opt.txt output.txt runtime.png
