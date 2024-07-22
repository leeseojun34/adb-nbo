#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

uint32_t add_nbo(const char* filename, int* error) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        *error = errno;
        return 0;
    }

    uint32_t n;
    size_t read_size = fread(&n, 1, sizeof(n), fp);
    fclose(fp);

    if (read_size < sizeof(n)) {
        *error = EINVAL;  // Invalid argument (file too small)
        return 0;
    }

    *error = 0;
    return ntohl(n);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    int error;
    uint32_t n1 = add_nbo(argv[1], &error);
    if (error != 0) {
        fprintf(stderr, "Error reading %s: %s\n", argv[1], strerror(error));
        return 1;
    }

    uint32_t n2 = add_nbo(argv[2], &error);
    if (error != 0) {
        fprintf(stderr, "Error reading %s: %s\n", argv[2], strerror(error));
        return 1;
    }

    uint32_t sum = n1 + n2;  // Overflow is ignored as requested

    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", n1, n1, n2, n2, sum, sum);

    return 0;
}