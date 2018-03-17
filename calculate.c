#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Must enter HASH_TABLE_SIZE.\n");
        exit(0);
    }

    int HAST_TABLE_SIZE = atoi(argv[1]);
    FILE* fp = fopen("opt.txt", "r");
    FILE* output = fopen("output.txt", "a");
    int i = 0;
    char append[50], find[50];

    if (!fp) {
        printf("ERROR opening input file opt.txt\n");
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
    fprintf(
        output, "%d %lf %lf\n", HAST_TABLE_SIZE, opt_sum_a / 100.0, opt_sum_f / 100.0);
    fclose(output);
    fclose(fp);
    return 0;
}
