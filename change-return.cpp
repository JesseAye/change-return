#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <string>

struct change {
    uint total_change;
    std::map<uint, uint> change_to_return = {
        {10000, 0},
        { 5000, 0},
        { 2000, 0},
        { 1000, 0},
        {  500, 0},
        {  100, 0},
        {   25, 0},
        {   10, 0},
        {    5, 0},
        {    1, 0}
    };
};

change calculate_change(float order_total, float tendered)
{
    change result;
    uint order_total_cents = ((uint)(order_total * 100)),
        tendered_cents = ((uint)(tendered * 100));
    uint remaining_change_cent = result.total_change = tendered_cents - order_total_cents;
    
    for (std::map<uint, uint>::reverse_iterator rit = result.change_to_return.rbegin(); rit != result.change_to_return.rend(); ++rit)
    {
        if(remaining_change_cent >= rit->first)
        {
            do
            {
                remaining_change_cent -= rit->first;
                rit->second++;
            } while (remaining_change_cent >= rit->first);
        }
    }

    return result;
}

int main(int argc, char *argv[])
{
    float order_total = 102.34f, tendered = 200.00f; // User-provided data, just test values for now

    change order_return = calculate_change(order_total, tendered);
    printf("Total to return: $%.2f\n", (((float)order_return.total_change)/100.00f));
    for (std::map<uint, uint>::reverse_iterator rit = order_return.change_to_return.rbegin(); rit != order_return.change_to_return.rend(); ++rit)
    {
        printf("$%6.2f - %lu\n", (((float)rit->first)/100.00f), rit->second);
    }

    return 0;
}