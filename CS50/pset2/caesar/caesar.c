#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    int n = argc;
    printf("%i", argc);
    if (n != 2)
    {
        printf("\nError 1, you must supply one number for the key");
        return 1;
    }
    else
    {
        int k = atoi(argv[1]);
        string p = get_string("Please enter what you want to encrypt: ");
        int plain_len = strlen(p);
        char c[plain_len];

        // char new_char;

        for (int i = 0; i < plain_len; i++)
        {
            if (isalpha(p[i]))
            {

                if (isupper(p[i]))
                {
                    //converting to an alphabetical index (a = 0, b = 1, etc..)
                    char charact = (p[i] - 65 + k) % 26;
                    c[i] = charact + 65;
                }
                if (islower(p[i]))
                {
                    char charact = (p[i] - 97 + k) % 26;
                    c[i] = charact + 97;

                }




            }
            else
            {
                c[i] = p[i];
            }
            printf("%c", c[i]);





        }

    }
}