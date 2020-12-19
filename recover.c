#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2) //making sure there is a source file
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r"); //opening the file
    if (file == NULL) //making sure there are no errors
    {
        printf("Error opening the file\n");
        return 1;
    }
    int n = 0; // keeping track of image numbers
    unsigned char d[512]; //memory to read block into
    char buffer[8]; //for image name
    FILE *img = NULL;
    while (fread(d, 512, 1, file) == 1) //looping until whole source is checked
    {
        //checking if the start of a new jpeg
        if (d[0] == 0xff && d[1] == 0xd8 && d[2] == 0xff && (d[3] & 0xf0) == 0xe0)
        {
            n++;
            if (n > 1) //if not first jpeg
            {
                fclose(img);
            }
            sprintf(buffer, "%03i.jpg", n - 1);
            img = fopen(buffer, "w");
        }
        if (n > 0)
        {
            fwrite(d, 512, 1, img);
        }
    }
    fclose(img); //closing all opened files
    fclose(file);
}
