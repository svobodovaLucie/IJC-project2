// wordcount.c
// Řešení IJC-DU2, příklad b), 08.04.2021
// Autor: Lucie Svobodová, FIT
// Přeloženo: gcc 9.3.0

#include <stdio.h>
#include "htab.h"
#include "io.h"

/**
 * Aby hashovací tabulka byla co nejefektivnější, mělo by vyhledávání v ní mít nejlépe 0(1) složitost.
 * Nevíme ale předem, jak velký soubor ke zpracování dostaneme. Měli bychom se snažit, aby byl každý 
 * prvek pole tabulky co nejméně zaplněn a aby byly zaplněny rovnoměrně. Dáváme přednost větší velikosti
 * pole před ušetřením místa v paměti, aby byla tabulka rychlejší.
 * Ideální velikost tabulky by měla být prvočíslem, které je co nejvíce vzdálené od mocnin čísla 2.
 * Průměrný počet unikátních slov ve větších knihách je kolem 10 000. Zvolila jsem proto velikost pole
 * tabulky 12 289 (mezi mocninami 2^13 a 2^14), protože toto číslo vyhovuje předchozím požadavkům.
 * Pro tabulku vytvořenou funkcí htab_move() jsem zvolila číslo 24 571, které opět vyhovuje požadavkům.
 * 
 * Použité zdroje:
 * https://medium.com/swlh/why-should-the-length-of-your-hash-table-be-a-prime-number-760ec65a75d1
 * http://www.tylervigen.com/literature-statistics
 */
#define HTAB_SIZE 12289         // počet prvků pole hlavní tabulky
#define HTAB_MOVE_SIZE 24571    // počet prvků pole tabulky testované v htab_move()
#define MAX_CHAR 128            // maximální délka slova (včetně koncové '\0')
//#define MOVETEST

/**
 * @brief Funkce vytiskne slovo a jeho počet výskytů.
 * 
 * @param data dvojice klíč a asociovaná data
 * @return void
 */
void print_info_about_word (htab_pair_t *data) {
    printf("%s\t%u\n", data->key, data->value);
}

int main(void) {
    htab_t *t = htab_init(HTAB_SIZE);
    if (t == NULL) {
        fprintf(stderr, "Error: htab_init: Not enough space for memory allocation.\n");
        return 1;
    }

    char buffer[MAX_CHAR] = {0};    // buffer pro uložení aktuálně načteného slova
    int word_len = 0;
    bool longer_word = false;
    while ((word_len = read_word(buffer, MAX_CHAR-1, stdin)) != EOF) {
        // kontrola, zda bylo slovo zkráceno
        if (!longer_word && word_len >= MAX_CHAR-1) {
            fprintf(stderr, "Warning: read_word: Max length of a word is %d characters.\n", MAX_CHAR-1);
            longer_word = true;
        }
        htab_pair_t *pair = htab_lookup_add(t, buffer);
        if (pair == NULL) {
            goto error_malloc;
        }
        pair->value++;  // zvýšení počtu výskytů slova
        memset(buffer, '\0', MAX_CHAR);
    }
    htab_for_each(t, print_info_about_word);

    #ifdef MOVETEST // testování funkce htab_move()
        htab_t *t_new = htab_move(HTAB_MOVE_SIZE, t);
        if (t_new == NULL) {
            goto error_malloc;
        }
        htab_for_each(t_new ,print_info_about_word);
        htab_free(t_new);
    #endif

    htab_free(t);
    return 0;

    error_malloc:
        fprintf(stderr, "Error: Not enough space for memory allocation.\n");
        htab_free(t);
        return 1;
}