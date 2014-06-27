#include <stdlib.h>
#include <unistd.h>
#include <bzlib.h>
#include <zlib.h>
#include <errno.h>
#include <string.h>

#define BUFLEN 4096

int main (int argc, char *argv[])
{
    if (argc > 1) {

        char isGzip = 1;  // Temp flag to set mode
        char buffer[BUFLEN];
        char *path = argv[1];
        int n;

        if (isGzip) {
             gzFile *gFile = gzopen(path, "rb");

             if (!gFile) {
                printf("Error openning %s\n", path);
                printf("%s\n", strerror(errno));
                exit(1);
             }

             while( (n = gzread(gFile, buffer, BUFLEN)) > 0) {
                 write(1, buffer,n );
             }
        }
        else {
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
        }

        // End output gracefully
        write(1, "\n", 1);
    }
    else {
        printf("Usage: bcat <bz2file>\n");
        printf("Displays the contents of a text file compressed under the bz2 compression algorithm.\n");
    }
}

