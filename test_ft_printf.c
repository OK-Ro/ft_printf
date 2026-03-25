#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

/* ========================================================================== */
/*  Helpers                                                                     */
/* ========================================================================== */

static int g_pass = 0;
static int g_fail = 0;

/* Each TEST macro:
 *   - calls the real printf and ft_printf with the same args
 *   - compares return values
 *   - prints PASS / FAIL
 *
 * Because both functions write to stdout the outputs are interleaved;
 * redirect to separate files when you need a byte-for-byte diff:
 *   ./test_ft_printf 1>out_ft.txt  (swap printf↔ft_printf to get out_orig.txt)
 */

#define TEST(label, fmt, ...)                                          \
    do {                                                               \
        printf("\n--- %s ---\n", label);                              \
        printf("  orig : ");                                           \
        int r1 = printf(fmt, ##__VA_ARGS__);                          \
        printf("\n");                                                  \
        printf("  mine : ");                                           \
        int r2 = ft_printf(fmt, ##__VA_ARGS__);                       \
        printf("\n");                                                  \
        if (r1 == r2) {                                                \
            printf("  ret  : orig=%d  mine=%d  [PASS]\n", r1, r2);   \
            g_pass++;                                                   \
        } else {                                                       \
            printf("  ret  : orig=%d  mine=%d  [FAIL]\n", r1, r2);   \
            g_fail++;                                                   \
        }                                                              \
    } while (0)

/* ========================================================================== */
/*  %c  – single character                                                      */
/* ========================================================================== */

void test_char(void)
{
    printf("\n========== %%c ==========\n");
    TEST("char basic a",       "%c", 'a');
    TEST("char basic Z",       "%c", 'Z');
    TEST("char space",         "%c", ' ');
    TEST("char newline",       "%c", '\n');
    TEST("char tab",           "%c", '\t');
    TEST("char null byte",     "%c", '\0');
    TEST("char digit",         "%c", '9');
    TEST("char special !",     "%c", '!');
    TEST("char high ascii 127","%c", 127);
    TEST("char in string",     "hello%cworld", '!');
    TEST("char multiple",      "%c%c%c", 'a', 'b', 'c');
}

/* ========================================================================== */
/*  %s  – string                                                                */
/* ========================================================================== */

void test_string(void)
{
    printf("\n========== %%s ==========\n");
    TEST("str basic",          "%s", "hello");
    TEST("str empty",          "%s", "");
    TEST("str NULL",           "%s", (char *)NULL);
    TEST("str spaces",         "%s", "hello world");
    TEST("str newline inside", "%s", "line1\nline2");
    TEST("str numbers",        "%s", "12345");
    TEST("str special chars",  "%s", "!@#$%^&*()");
    TEST("str long",           "%s", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    TEST("str multiple",       "%s %s", "foo", "bar");
    TEST("str with fmt text",  "prefix %s suffix", "middle");
    TEST("str single char",    "%s", "x");
}

/* ========================================================================== */
/*  %d / %i  – signed decimal integer                                           */
/* ========================================================================== */

void test_decimal(void)
{
    printf("\n========== %%d / %%i ==========\n");
    TEST("d zero",             "%d", 0);
    TEST("d positive",         "%d", 42);
    TEST("d negative",         "%d", -42);
    TEST("d INT_MAX",          "%d", INT_MAX);
    TEST("d INT_MIN",          "%d", INT_MIN);
    TEST("d large pos",        "%d", 1000000);
    TEST("d large neg",        "%d", -1000000);
    TEST("d one",              "%d", 1);
    TEST("d minus one",        "%d", -1);
    TEST("d multiple",         "%d %d %d", 1, -2, 3);

    TEST("i zero",             "%i", 0);
    TEST("i positive",         "%i", 42);
    TEST("i negative",         "%i", -42);
    TEST("i INT_MAX",          "%i", INT_MAX);
    TEST("i INT_MIN",          "%i", INT_MIN);
    TEST("i multiple",         "%i %i", 100, -200);
}

/* ========================================================================== */
/*  %u  – unsigned decimal                                                      */
/* ========================================================================== */

void test_unsigned(void)
{
    printf("\n========== %%u ==========\n");
    TEST("u zero",             "%u", 0u);
    TEST("u basic",            "%u", 42u);
    TEST("u UINT_MAX",         "%u", UINT_MAX);
    TEST("u large",            "%u", 4000000000u);
    TEST("u from neg cast",    "%u", (unsigned int)-1);
    TEST("u one",              "%u", 1u);
    TEST("u multiple",         "%u %u", 100u, 200u);
    TEST("u INT_MAX as uint",  "%u", (unsigned int)INT_MAX);
}

/* ========================================================================== */
/*  %x / %X  – hexadecimal                                                      */
/* ========================================================================== */

void test_hex(void)
{
    printf("\n========== %%x / %%X ==========\n");
    TEST("x zero",             "%x", 0);
    TEST("x basic",            "%x", 255);
    TEST("x deadbeef",         "%x", 0xdeadbeef);
    TEST("x INT_MAX",          "%x", INT_MAX);
    TEST("x UINT_MAX",         "%x", UINT_MAX);
    TEST("x one",              "%x", 1);
    TEST("x 16",               "%x", 16);
    TEST("x all letters",      "%x", 0xabcdef);
    TEST("x multiple",         "%x %x", 0xab, 0xcd);

    TEST("X zero",             "%X", 0);
    TEST("X basic",            "%X", 255);
    TEST("X deadbeef",         "%X", 0xDEADBEEF);
    TEST("X INT_MAX",          "%X", INT_MAX);
    TEST("X UINT_MAX",         "%X", UINT_MAX);
    TEST("X all letters",      "%X", 0xABCDEF);
    TEST("X multiple",         "%X %X", 0xAB, 0xCD);
    TEST("x vs X same val",    "%x %X", 0xff, 0xff);
}

/* ========================================================================== */
/*  %p  – pointer                                                               */
/* ========================================================================== */

void test_pointer(void)
{
    printf("\n========== %%p ==========\n");
    int    n     = 42;
    char   c     = 'a';
    void  *vp    = (void *)0x1;
    void  *large = (void *)0x7fffffffffff;

    TEST("p stack var int",    "%p", (void *)&n);
    TEST("p stack var char",   "%p", (void *)&c);
    TEST("p NULL",             "%p", (void *)NULL);
    TEST("p value 0x1",        "%p", vp);
    TEST("p large addr",       "%p", large);
    TEST("p multiple",         "%p %p", (void *)&n, (void *)&c);
}

/* ========================================================================== */
/*  %%  – literal percent sign                                                  */
/* ========================================================================== */

void test_percent(void)
{
    printf("\n========== %%%% ==========\n");
    TEST("percent alone",      "%%");
    TEST("percent start",      "%%%s", "hello");
    TEST("percent end",        "%s%%", "hello");
    TEST("percent middle",     "50%%off");
    TEST("percent multiple",   "%%%%");
    TEST("percent with args",  "%d%% done", 99);
}

/* ========================================================================== */
/*  Mixed / edge cases                                                          */
/* ========================================================================== */

void test_mixed(void)
{
    printf("\n========== Mixed ==========\n");
    TEST("mixed all types",
        "%c %s %d %i %u %x %X %%",
        'A', "hi", -1, -2, 42u, 0xff, 0xFF);

    TEST("mixed no specifiers",  "hello world");
    TEST("mixed only newline",   "\n");
    TEST("mixed empty string",   "");
    TEST("mixed consecutive fmt","%d%d%d%d", 1, 2, 3, 4);
    TEST("mixed interleaved",    "a%cb%sc%dd", 'X', "YY", 99);

    /* return value edge cases */
    TEST("ret single char",      "a");
    TEST("ret fmt string only",  "%s", "hello");
    TEST("ret zero val int",     "%d", 0);
}

/* ========================================================================== */
/*  main                                                                        */
/* ========================================================================== */

int main(void)
{
    printf("==============================================\n");
    printf("         ft_printf  vs  printf  TESTS        \n");
    printf("==============================================\n");

    test_char();
    test_string();
    test_decimal();
    test_unsigned();
    test_hex();
    test_pointer();
    test_percent();
    test_mixed();

    printf("\n==============================================\n");
    printf("  RESULTS:  %d passed  |  %d failed\n", g_pass, g_fail);
    printf("==============================================\n");

    return (g_fail > 0 ? 1 : 0);
}