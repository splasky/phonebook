#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(HASH_COMPARE)
char* hash_txt[] = { "aphash.txt", "bkdrhash.txt", "dekhash.txt", "djbhash.txt",
                     "elfhash.txt", "jshash.txt", "pjwhash.txt", "rshash.txt", "sdbmhash.txt"
                   };
#define num_of_hash_files 9
#endif

#ifdef OPT
#define OUT_FILE "opt.txt"
#endif

#ifdef HASH
#define OUT_FILE "hash.txt"
#endif

#ifdef MEM_POOL
#define OUT_FILE "mempool.txt"
#endif

#define OUT_PUT "output.txt"

int main(void)
{
    FILE* fp = fopen("orig.txt", "r");
    FILE* output = fopen(OUT_PUT, "w");
    if (!fp) {
        printf("ERROR opening input file orig.txt\n");
        exit(0);
    }
    int i = 0;
    char append[50], find[50];
    double orig_sum_a = 0.0, orig_sum_f = 0.0, orig_a, orig_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find, &orig_a, &orig_f);
        orig_sum_a += orig_a;
        orig_sum_f += orig_f;
    }
    fclose(fp);

#if defined(HASH_COMPARE)
    double opt_sum_a_v[num_of_hash_files] = { 0 };
    double opt_sum_f_v[num_of_hash_files] = { 0 };

    for (int j = 0; j < num_of_hash_files; ++j) {

        char file_name[50] = "hash_output/";
        char* file = hash_txt[j];
        strcat(file_name, file);

        fp = fopen(file_name, "r");
        if (!fp) {
            printf("ERROR opening input file %s\n", file_name);
            exit(0);
        }
        double opt_sum_a = 0.0, opt_sum_f = 0.0, opt_a, opt_f;
        for (i = 0; i < 100; i++) {
            if (feof(fp)) {
                printf("ERROR: You need 100 datum instead of %d\n", i);
                printf("run 'make run' longer to get enough information\n\n");
                exit(0);
            }
            fscanf(fp, "%s %s %lf %lf\n", append, find, &opt_a, &opt_f);
            opt_sum_a += opt_a;
            opt_sum_f += opt_f;
        }
        opt_sum_a_v[j] = opt_sum_a / 100.0;
        opt_sum_f_v[j] = opt_sum_f / 100.0;
        fclose(fp);
    }

    fprintf(output, "append() %lf ", orig_sum_a / 100.0);
    for (int i = 0; i < num_of_hash_files; ++i) {
        fprintf(output, "%lf ", opt_sum_a_v[i]);
    }
    fprintf(output, "\n");

    fprintf(output, "findName() %lf ", orig_sum_f / 100.0);
    for (int i = 0; i < num_of_hash_files; ++i) {
        fprintf(output, "%lf ", opt_sum_f_v[i]);
    }
#else
    fp = fopen("opt.txt", "r");
    if (!fp) {
        fp = fopen("orig.txt", "r");
        if (!fp) {
            printf("ERROR opening input file opt.txt\n");
            exit(0);
        }
    }
    double opt_sum_a = 0.0, opt_sum_f = 0.0, opt_a, opt_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find, &opt_a, &opt_f);
        opt_sum_a += opt_a;
        opt_sum_f += opt_f;
    }
    fclose(fp);
    fprintf(output, "append() %lf %lf\n", orig_sum_a / 100.0, opt_sum_a / 100.0);
    fprintf(output, "findName() %lf %lf\n", orig_sum_f / 100.0, opt_sum_f / 100.0);
#endif
    fclose(output);
    return 0;
}
