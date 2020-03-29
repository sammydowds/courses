#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //global var, n for number of arguments passed
    //string length of arg v (number of letters used to encript)
    int n = argc;
    string k = argv[1];
    int k_len = strlen(k);



    //validating that only two arguments were passed in the command line
    if (n != 2)
    {
        printf("\nError 1, you must supply one number for the key");
        return 1;
    }




    //validating that all argv keys are letters
    else
    {
        for (int i = 0; i < k_len; i++)

            if (isalpha(k[i]) == false)
            {
            printf("\nError 1, you must supply a letter");
            return 1;

            }

    }


    //code below runs when both argv's are letters and no more than two arguments are passed via the command line

    //getting user input on what to encript
    string p = get_string("Please enter what you want to encrypt: ");
    int plain_len = strlen(p);
    char c[plain_len];


    // new array to hold shift for capitilized or non-caplitized letters in key
    int alpha_key[1000];
    //Loop to calculate key shift (If upper vs lower)
    for (int i = 0; i < k_len; i++)
    {
        if (isupper(k[i]))
        {
            alpha_key[i] = (k[i]-65);
        }
        else
        {
            alpha_key[i] = (k[i]-97);
        }
    }




    //need an internal counter (j) so we can keep track when we skip spaces or non-alpha
    int j = 0;

    //For loop for encription
    for (int i = 0; i < plain_len; i++)
    {
        if (isalpha(p[i]))
        {



            if (isupper(p[i]))
            {
                //converting to an alphabetical index (a = 0, b = 1, etc..)
                char charact = (p[i] - 65 + alpha_key[j % k_len]) % 26;
                //converting back to ASCII
                c[i] = charact + 65;
                j++;
            }
            else
            {
                //converting to an alphabetical index
                char charact = (p[i] - 97 + alpha_key[j % k_len]) % 26;
                //converting back to ASCII
                c[i] = charact + 97;
                j++;

            }
        }
        else
        {
            c[i] = p[i];
        }

        printf("%c", c[i]);





    }


}