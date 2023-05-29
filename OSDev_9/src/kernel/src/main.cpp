
#include "system.h"

// Define entry point in asm to prevent C++ mangling
extern "C"
{
    void kernel_main();
}

void clear_screen()
{
    char *vidptr = (char *)0xb8000; // video mem begins here.
    unsigned int j = 0;

    while (j < 80 * 25 * 2)
    {
        /* blank character */
        vidptr[j] = ' ';
        /* attribute-byte - light grey on black screen */
        vidptr[j + 1] = 0x07;
        j = j + 2;
    }
}

void terminal_write(const char *str)
{
    clear_screen();

    char *vidptr = (char *)0xb8000; // video mem begins here.

    unsigned int i = 0;
    unsigned int j = 0;

    /* this loop writes the string to video memory */
    while (str[j] != '\0')
    {
        /* the character's ascii */
        vidptr[i] = str[j];
        /* attribute-byte: give character black bg and light grey fg */
        vidptr[i + 1] = 0x07;
        ++j;
        i = i + 2;
    }
}

void kernel_main()
{
    terminal_write("Hello world, operative systems are fun! :)");

    while (1)
    {
    }
}
