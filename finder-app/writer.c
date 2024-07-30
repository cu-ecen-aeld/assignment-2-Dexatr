#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file> <string>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *string = argv[2];

    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("fopen");
        syslog(LOG_ERR, "Error opening file %s", filename);
        return 1;
    }

    if (fprintf(file, "%s", string) < 0) {
        perror("fprintf");
        syslog(LOG_ERR, "Error writing to file %s", filename);
        fclose(file);
        return 1;
    }

    syslog(LOG_DEBUG, "Writing %s to %s", string, filename);
    fclose(file);
    return 0;
}

