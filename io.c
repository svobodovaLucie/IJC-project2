#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "io.h"
// Napište funkci

// int read_word(char *s, int max, FILE *f);

// která čte jedno slovo ze souboru f do zadaného pole znaků
// a vrátí délku slova (z delších slov načte prvních max-1 znaků,
// a zbytek přeskočí). Funkce vrací EOF, pokud je konec souboru.
// Umístěte ji do zvláštního modulu "io.c" (nepatří do knihovny).
// Poznámka: Slovo je souvislá posloupnost znaků oddělená isspace znaky.
// Omezení: řešení v C bude tisknout jinak uspořádaný výstup
// a je povoleno použít implementační limit na maximální
// délku slova (např. 127 znaků), delší slova se ZKRÁTÍ a program
// při prvním delším slovu vytiskne varování na stderr (max 1 varování).

// Poznámka: Vhodný soubor pro testování je například seznam slov
// v souboru /usr/share/dict/words
// nebo texty z http://www.gutenberg.org/
// případně výsledek příkazu:  "seq 1000000 2000000|shuf"


#define MAX_LEN 128

int read_word(char *s, int max, FILE *f) {
    if (max > MAX_LEN) {
        fprintf(stderr, "Max length of a word is %d characters (limit).\n", MAX_LEN);
        max = MAX_LEN;
    }
    int i = 0;
    int c = fgetc(f);

    while (isspace(c)) {    // cyklus preskace vsechny bile znaky
        c = fgetc(f);
    }

    while(!isspace(c) && c != EOF && i <= max) {
        s[i++] = c;
        c = fgetc(f);
    }
    if (c == EOF)
        return c;

    if (i == max) {
        fprintf(stderr, "Max length of a word is %d characters.\n", max);
        s[i] = '\0';
        while (!isspace(c = fgetc(f))) ; // empty loop (dojede na konec slova)
    }
    return strlen(s);
}