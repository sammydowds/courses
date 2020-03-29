#include <stdio.h>
#include <cs50.h>



int main(void)
{
    int n;
    bool bool1;
    bool bool2;
    bool validity;
    do
    {
        n = get_int("Number of rows: ");
        bool1 = n <= 0;
        bool2 = n > 23;
        validity = bool1||bool2;
    }while (validity);
    for (int i = 0; i < n; i++)
        {
            int spaces = n-i-1;
            int hashes = n-spaces;

            for (int j = 0; j <= spaces; j++)
            {
                printf(" ");
            }
            for (int k = 0; k <= hashes; k++)
            {
                printf("#");
            }
            printf("\n");
        }

}
