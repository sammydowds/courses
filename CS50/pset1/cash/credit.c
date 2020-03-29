#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

int main(void)
{
    int counter = 1;
    int summed_digs = 0;
    int summed_digs_2 = 0;
    int check_passed = 0;
    long long cc_number;
    int cc_num_len;
    long long cc;



    do
    {
        //code determines whether the cc number put in is valid or not
        cc_number = get_long_long("Number: ");
        cc = cc_number;

        //loop to loop through each number of the cc number
        while (cc_number != 0)

        {
            //obtaining the last digit of the new cc number
            unsigned int last = cc_number % 10;


            //updating the counter to help determine which digit of the number we are on
            counter++;


            //if-else statement to determine if counter is on last digit or on second to last digit (even numbers = started on last digit, odds = started on second from last)
            if (counter % 2 == 0)
            {
                //summing every other number starting from the last number into "summed_digs"
                summed_digs = summed_digs + last;
            }
            else
            {
                //multiplying this digit by 2
                int digit = last * 2;
                //a loop to separate the digits and add them together in "summed_digs_2"
                while (digit != 0)
                {
                    int last_2 = digit % 10;
                    summed_digs_2 = summed_digs_2 + last_2;
                    digit = digit / 10;
                }
            }
            cc_number = cc_number / 10;
        }
        //this divides the number by 10, and cuts off the last digit we just analyzed (this works because when dividing integers in c, it disregards any fraction/decimal).

        int sum_check = summed_digs + summed_digs_2;
        if (sum_check % 10 == 0)
        {
            check_passed = 1;
        }
        else
        {
            printf("This is not a valid credit card number, please enter number again\n");
        }
    }
    while (check_passed == 0);


    //This code runs below IF you have a valid credit card number according to Luhn's algorithm

    //length of the number
    cc_num_len = counter - 1;

    //calculating first two digits
    long long div_10 = pow(10, counter - 3);
    long long first_two = cc / div_10;

    //Begin checking criteria of credit card based on length of number and first two integers of number
    if (cc_num_len == 16)
    {
        if (first_two / 10 == 4)
        {
            printf("VISA\n");
        }

        if (first_two == 51 || first_two == 52 || first_two == 53 || first_two == 54 || first_two == 55)
        {
            printf("MasterCard\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else if (cc_num_len == 15 && (first_two == 34 || first_two == 37))
    {
        printf("AMEX\n");
    }
    else if (cc_num_len == 13 && first_two / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }














}

