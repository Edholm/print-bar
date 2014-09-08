#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

const string DEFAULT_TICK_FULL = "▣";
const string DEFAULT_TICK_EMPTY = "▢";
const int BAR_WIDTH = 10;


void print_bar(int usage, int width, string tick_full, string tick_empty) {
    string bar;

    int scaledusage = rint(usage * width / 100);

    int i;
    for (i = 0; i < scaledusage; i++)
        bar.append(tick_full);

    for (; i < width; i++)
        bar.append(tick_empty);

    cout << bar;
}

int main(int argc, char *argv[])
{
    if(argc != 2) {
        fprintf(stderr, "Illegal number of arguments. Expected 1, got %i\n",
                argc-1);
        return 1;
    }
    if(!isdigit(argv[1][0])) {
        fprintf(stderr, "You did not supply a correct usage integer. \n\
                Expected value between 0-100. Got: %s\n", argv[1]);
        return 1;
    }

    int usage = atoi(argv[1]);
    if(usage < 0)
        usage = 0;
    else if(usage > 100)
        usage = 100;


    print_bar(usage, BAR_WIDTH, DEFAULT_TICK_FULL, DEFAULT_TICK_EMPTY);
    return 0;
}
