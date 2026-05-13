// Recovers JPEGs from a forensic image

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "rb");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];
    FILE *img = NULL;
    int count = 0;
    char filename[8]; // "###.jpg\0" = 8 bytes

    // Read one block at a time
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // Check for JPEG signature
        int is_jpeg = (buffer[0] == 0xff &&
                       buffer[1] == 0xd8 &&
                       buffer[2] == 0xff &&
                       (buffer[3] & 0xf0) == 0xe0);

        if (is_jpeg)
        {
            // Close previous JPEG if one is open
            if (img != NULL)
            {
                fclose(img);
            }

            // Open a new JPEG file
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "wb");
            count++;
        }

        // Write block to current JPEG if we've found one
        if (img != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    // Close any remaining open files
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);

    return 0;
}
