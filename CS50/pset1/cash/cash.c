#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;
    int n;
    int quarter_c = 0;
    int dime_c = 0;
    int nickel_c = 0;
    int penny_c = 0;

    do
    {
         float k = get_float("Change owed: ");
         n = round(k * 100);
    }while (n < 0);

    int change_total = 0;
    int diff = n - change_total;
    int coin_count = 0;
    while (diff > 0)
    {

        if (diff % quarter != diff)
        {
            coin_count++;
            change_total = change_total + quarter;
            quarter_c++;
        }
        else if (diff % dime != diff)
        {
            coin_count++;
            change_total = change_total + dime;
            dime_c++;
        }
        else if (diff % nickel != diff)
        {
            coin_count++;
            change_total = change_total + nickel;
            nickel_c++;
        }
        else if (diff % penny != diff)
        {
            coin_count++;
            change_total = change_total + penny;
            penny_c++;
        }
        diff = n-change_total;
    }
    printf("Number of coins given back: %i, change total: %i cents, quarters: %i, dimes: %i, nickels: %i, pennies: %i", coin_count, change_total, quarter_c, dime_c, nickel_c, penny_c);

}