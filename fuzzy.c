#include "fuzzy.h"
#include <string.h>

int LevenshteinDistance(char* str1, const size_t len1, char* str2, const size_t len2)
{
    int d[len1 + 1][len2 + 1];

    for (int i = 0; i < len1; ++i) {
        d[i][0] = i;
    }

    for (int i = 0; i < len2; ++i) {
        d[0][i] = i;
    }

    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                d[i][j] = d[i - 1][j - 1];
            } else {
                d[i][j] = minimun(d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + 1);
            }
        }
    }

    return d[len1][len2];
}

int min(const int x, const int y)
{
    if (x >= y)
        return x;
    return y;
}

int minimun(const int a, const int b, const int c)
{
    int temp = min(a, b);
    int ret = min(temp, c);
    return ret;
}

int max(const int x, const int y)
{
    if (x <= y)
        return y;
    return x;
}
