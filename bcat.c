#include <stdlib.h>
#include <unistd.h>
#include <bzlib.h>
#include <zlib.h>
#include <errno.h>
#include <string.h>

#define BUFLEN 4096

void get_extension(char *path, char *result) {
    int i = 0;
    int rindex = -1;
    char c;

    while( (c = path[i++]) != '\0') {
        if (c == '.') {
            rindex = 0;
        } else if (rindex != -1) {
            result[rindex++] = c;
        }
    }
    result[rindex] = '\0';
}

int main (int argc, char *argv[])
{
    if (argc > 1) {


        char buffer[BUFLEN];
        char extension[10];
        char *path = argv[1];
        int n;

        get_extension(path, extension);

        // Determine compression type based on file extension
        char isGzip = strcmp(extension, "gz") == 0;
        char isBz2 = strcmp(extension, "bz2") == 0;

        if (isGzip) {
             gzFile gFile = gzopen(path, "rb");

             if (!gFile) {
                printf("Error openning %s\n", path);
                printf("%s\n", strerror(errno));
                exit(1);
             }

             while( (n = gzread(gFile, buffer, BUFLEN)) > 0) {
                 write(1, buffer,n );
             }
        }
        else if (isBz2) {
            int bzError;

            FILE *file = fopen(path, "r");

            if (!file) {
                printf("Error openning %s\n", path);
                printf("%s\n", strerror(errno));
                exit(1);
            }

            BZFILE *bzFile = BZ2_bzReadOpen(&bzError, file, 0, 0, NULL, 0);

            if (bzError != BZ_OK) {
                printf("Error openning Bz2 file %s\n", path);
                printf("%s\n", strerror(errno));
                exit(1);
            }

            while ((n = BZ2_bzRead(&bzError, bzFile, buffer, BUFLEN)) > 0) {
                write(1, buffer, n);  // Write to stdout
            }
        } else {
            printf("ERROR: Not a compressed file!");
        }

        // End output gracefully
        write(1, "\n", 1);
    }
    else {
        printf("Usage: bcat <cfile>\n");
        printf("Displays the contents of a file compressed using bz2 or gzip.\n");
    }
}

