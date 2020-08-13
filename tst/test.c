#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    FILE *cdecl = popen(argv[1], "r");
    FILE *output = fopen(argv[2], "r");
    int print = argc >= 4 && !strcmp(argv[3], "print");

    while (1)
    {
        int in = fgetc(cdecl);
        int out = fgetc(output);

        if (in == EOF && in == out)
        {
            break;
        }

        if (print)
        {
            putchar(in);
            putchar(out);
        }

        if (in != out)
        {
            puts("[TEST FAILED]");
            return ~0;
        }
    }

    puts("[TEST PASSED]");
    return 0;
}