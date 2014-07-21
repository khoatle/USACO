/*
ID: khoatat2
LANG: C++
TASK: sort3
*/

#include <algorithm>
#include <stdio.h>
 
int main() {
    int i, j, t, n, res = 0, c1 = 0, c2 = 0, a[1000];
 
    FILE *in = fopen("sort3.in", "r");
    fscanf(in, "%d", &n);
 
    for (i = 0; i < n; i++) {
        fscanf(in, "%d", &a[i]);
        if (a[i] == 1)
            ++c1;
        else if (a[i] == 2)
            ++c2;
    }
    fclose(in);
 
    for (i = c1; i < n; i++) {
        if (a[i] == 1) {
            for (j = t = 0; j < c1; j++) {
                if (a[j] == 2) {
                    t = j;
                    break;
                } else if (a[j] == 3) {
                    t = j;
                }
            }
            std::swap(a[i], a[t]);
            ++res;
        }
    }
 
    for (i = c1 + c2; i < n; i++)
        if (a[i] == 2)
            ++res;
 
    FILE *out = fopen("sort3.out", "w");
    fprintf(out, "%d\n", res);
    fclose(out);
    return 0;
}