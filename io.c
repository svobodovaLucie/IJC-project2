// io.c
// Řešení IJC-DU2, příklad b), 08.04.2021
// Autor: Lucie Svobodová, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h> 
#include "io.h"

#define MAX_LEN 127

/**
 * @brief Funkce čte jedno slovo ze souboru f do zadaného pole znaků
 *        a vrátí délku slova (z delších slov načte prvních max-1 znaků,
 *        a zbytek přeskočí).
 * 
 * @param s pole znaků, do kterého je načtené slovo uloženo
 * @param max maximální délka slova
 * @param f soubor, ze kterého je slovo načteno
 * @return délka slova zapsaného do s
 */
int read_word(char *s, int max, FILE *f) {
    if (max > MAX_LEN) {
        fprintf(stderr, "Max length of a word is %d characters (limit).\n", MAX_LEN);
        max = MAX_LEN;
    }
    int i = 0;
    int c = fgetc(f);

    while (isspace(c)) {    // přeskočí všechny bílé znaky
        c = fgetc(f);
    }
    while(!isspace(c) && c != EOF && i < max) {    // načítání slova do pole s
        s[i++] = c;
        c = fgetc(f);
    }
    if (c == EOF)
        return c;
    if (i == max) {
        while (!isspace(c = fgetc(f))) ; // empty loop (dokončí čtení aktuálního slova)
    }
    s[i] = '\0';
    return strlen(s);
}
