#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <string>

int main(int argc, char *argv[])
{
    std::map<uint, uint> change_to_return;
    std::map<uint, std::string> denominations_cents = {
        {10000, "$100"},
        { 5000, "$50"},
        { 2000, "$20"},
        { 1000, "$10"},
        {  500, "$5"},
        {  100, "$1"},
        {   25, "$0.25"},
        {   10, "$0.10"},
        {    5, "$0.05"},
        {    1, "$0.01"}
    };
    float order_total = 102.34f, tendered = 200.00f; // User-provided data, just test values for now
    uint order_total_cents = ((uint)(order_total * 100)),
        tendered_cents = ((uint)(tendered * 100));
    float remaining_change = tendered - order_total;
    uint remaining_change_cent = tendered_cents - order_total_cents;

    printf("Calculating denominations to return $%.2f:\n", remaining_change);

    for (std::map<uint, std::string>::reverse_iterator rit = denominations_cents.rbegin(); rit != denominations_cents.rend(); ++rit)
    {
        if(remaining_change_cent >= rit->first)
        {
            do
            {
                remaining_change_cent -= rit->first;
                change_to_return[rit->first]++;
            } while (remaining_change_cent >= rit->first);
            printf("%5s - %lu\n", rit->second.c_str(), change_to_return[rit->first]);
        }
    }

    return 0;
}