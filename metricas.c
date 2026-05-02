#define _POSIX_C_SOURCE 200809L
#include "metricas.h"

double metricasAgora(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

double metricasMedia(double *tempos, int n) {
    if (n <= 0) return 0.0;
    double soma = 0.0;
    for (int i = 0; i < n; i++) soma += tempos[i];
    return soma / n;
}

void metricasImprimirTabela(const char *titulo,
                             double     *tempos,
                             int         n,
                             double      media) {
    printf("\n=== %s ===\n", titulo);
    printf("%-10s | %20s\n", "Execucao", "Tempo (s)");
    printf("%-10s-+-%20s\n", "----------", "--------------------");
    for (int i = 0; i < n; i++)
        printf("%-10d | %20.9f\n", i + 1, tempos[i]);
    printf("%-10s | %20.9f\n", "MEDIA", media);
}