#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;
    int convert;
    int count;

    // Prompt User
    do
    {
        change = get_float("Change Please: ");
    }
    while (change < 0);

    // convert decimal into integer
    convert = round(change * 100);
    // var to store my change in coins
    count = 0;

    // keep count of coins
    while (convert >= 25)
    {
        count += 1;
        convert = convert - 25;
    }
    while (convert >= 10)
    {
        convert = convert - 10;
        count += 1;
    }
    while (convert >= 5)
    {
        convert = convert - 5;
        count += 1;
    }
    while (convert >= 1)
    {
        convert = convert - 1;
        count += 1;
    }
    // Display amount entered in coins
    printf("Coins: %i\n", count + convert);

}