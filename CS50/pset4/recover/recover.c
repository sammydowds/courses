//functions we need: fread, fwrite, fopen --> stdio.h

#include <stdio.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Please enter only 1 command line argument: file to open");
        return 0;
    }

    char *file_n = argv[1];
    FILE *infile = fopen(file_n, "r");

    if (infile == NULL)
    {
        fprintf(stderr, "File cannot be found");
        return 1;
    }

    //initializing variables

    //declaring file strucutre for image, and initially setting it to null
    FILE *img = NULL;
    //initiallizing an array buffer, with 512 byte size (defined above)
    unsigned char buffer[BUFFER_SIZE];
    //initializing jpeg count and jpeg found state
    int jpeg_count = 0;
    int jpeg_found = 0;


    //while loop to loop over file until end of file which returns something other than 1-- if it doesnt succesfully read in 1 chunk, it will not return 1
    while (fread(buffer, BUFFER_SIZE, 1, infile) == 1)
    {

        //bitwise and operator to detect beginning of JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if we previously found a jpeg, we need to close it
            if (jpeg_found == 1)
            {
               fclose(img);
            }

            else
            {
                jpeg_found = 1;
            }

            //need to create a new file for jpeg just found
            char filename[8];
            sprintf(filename, "%03i.jpg", jpeg_count);
            img = fopen(filename, "a");
            jpeg_count++;

        }
        //if we have found a jpeg we need to write these bytes to the new img file
        if(jpeg_found == 1)
        {

            fwrite(&buffer, BUFFER_SIZE, 1, img);

        }





    }
    fclose(infile);
    fclose(img);
    return 0;








}