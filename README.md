*This project has been created as part of the 42 curriculum by [rokuni].*

# ft_printf

## Description

`ft_printf` is a partial reimplementation of the C standard library function `printf()`, built as a static library `libftprintf.a`. The goal is to understand how variadic functions work in C — functions that accept a variable number of arguments — and to practise building and linking static libraries from scratch.

The library exposes a single public function:

```c
int ft_printf(const char *, ...);
```

It parses a format string and dispatches each conversion specifier (`%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, `%%`) to a dedicated handler, writing output directly to stdout via `write()`. It returns the total number of characters written, matching the behaviour of the original `printf()`.

Buffer management (as implemented in glibc's `printf`) is intentionally not implemented.

---

## Project Structure

The implementation is split into dedicated handler files for clarity and modularity:

| File | Purpose |
|------|---------|
| `ft_printf.c` | Main dispatcher; parses format string and routes conversions to handlers |
| `ft_printf_char.c` | Handles `%c` — single character output |
| `ft_printf_str.c` | Handles `%s` — null-terminated string output (includes NULL case) |
| `ft_printf_nbr.c` | Handles `%d` and `%i` — signed integer output (includes INT_MIN case) |
| `ft_printf_unsigned.c` | Handles `%u` — unsigned integer output |
| `ft_printf_hex.c` | Handles `%x` and `%X` — hexadecimal output (case-sensitive) |
| `ft_printf_ptr.c` | Handles `%p` — pointer address output (includes NULL case) |
| `ft_printf.h` | Header file with function prototypes and required includes |

---

## Instructions

### Compilation

```bash
# Clone the repository
git clone https://github.com/OK-Ro/ft_printf
cd ft_printf

# Build the library
make

# This produces libftprintf.a at the root of the repository
```

### Linking into your project

```bash
cc your_file.c -L. -lftprintf -o your_program
```

### Makefile rules

| Rule | Effect |
|------|--------|
| `make` / `make all` | Compile all `.c` files and archive into `libftprintf.a` |
| `make clean` | Remove all `.o` object files |
| `make fclean` | Remove `.o` files and `libftprintf.a` |
| `make re` | Full rebuild from scratch |

### Running the tests

A test file `test_ft_printf.c` is included at the root. It runs each specifier against the original `printf()` and compares return values.

```bash
make
cc test_ft_printf.c -L. -lftprintf -o test
./test
```

---

## Supported Conversions

| Specifier | Output |
|-----------|--------|
| `%c` | Single character |
| `%s` | Null-terminated string |
| `%p` | Pointer address in hexadecimal (`0x…`) |
| `%d` | Signed decimal integer |
| `%i` | Signed integer in base 10 |
| `%u` | Unsigned decimal integer |
| `%x` | Unsigned integer in hexadecimal lowercase |
| `%X` | Unsigned integer in hexadecimal uppercase |
| `%%` | Literal percent sign |

---

## Example Usage

```c
#include "ft_printf.h"

int main(void)
{
	char			c = 'A';
	char			*str = "Hello";
	int				num = 42;
	int				neg = -100;
	unsigned int	unsign = 4294967295;
	int				*ptr = NULL;
	int				chars;

	// Character and string
	ft_printf("%c %s\n", c, str);

	// Signed integers
	ft_printf("Number: %d (or %i)\n", num, num);
	ft_printf("Negative: %d\n", neg);

	// Unsigned integer
	ft_printf("Unsigned: %u\n", unsign);

	// Hexadecimal
	ft_printf("Hex lowercase: %x\n", 255);
	ft_printf("Hex UPPERCASE: %X\n", 255);

	// Pointer
	ft_printf("Pointer NULL: %p\n", ptr);
	ft_printf("Pointer address: %p\n", &num);
	//if null
	    // NULL
    printf("printf:    %p\n", NULL);
    ft_printf("ft_printf: %p\n", NULL);

	// Percent sign
	ft_printf("Progress: %d%%\n", 100);

	// Return value (number of characters printed)
	chars = ft_printf("Test\n");
	ft_printf("Characters printed: %d\n", chars);

	return (0);
}
```

---

## Algorithm and Data Structure

### Parsing approach

`ft_printf` uses a **single-pass linear scan** of the format string. It iterates character by character using an index. When it encounters a regular character it writes it directly with `write()`. When it encounters a `%` it reads the next character and dispatches to the appropriate handler via a chain of `if` statements inside a `handle_conversion()` function.

This approach was chosen over a lookup table or function pointer array because it is simple, readable, and has no overhead for a function of this scope. The format string is never copied or tokenised — it is read in-place, which keeps memory usage at zero allocations.

```
ft_printf("Hello %s, you are %d years old", name, age)
          │                │
          └─ write chars   └─ dispatch to ft_print_str, ft_print_nbr
```

### Return value tracking

Each internal handler returns the number of bytes it wrote (always the return value of `write()`). The dispatcher accumulates these into a running `total` and returns it at the end. This mirrors the contract of the real `printf()`.

### Variadic argument handling

Arguments are accessed using the `<stdarg.h>` macros:

- `va_start(ap, fmt)` — initialises the argument list after the last named parameter
- `va_arg(ap, type)` — retrieves the next argument as the given type
- `va_end(ap)` — cleans up; always called before returning

The `va_list` is initialised once in `ft_printf()` and passed directly to `handle_conversion()` on each `%` encountered. This means the list advances naturally through each argument in order, matching the specifiers left to right in the format string.

### Numeric conversion (base conversion)

All numeric printers (`%d`, `%u`, `%x`, `%X`) use **recursion** to extract and print digits in the correct order without allocating a buffer:

```
ft_print_uint(255)
  └─ ft_print_uint(25)   → prints '2'
       └─ ft_print_uint(2) → prints '2' ... wait, let me show it correctly:

ft_print_uint(255):
  255 >= 10 → recurse with 25
    25 >= 10 → recurse with 2
      2 < 10  → write '2'
    write '5'
  write '5'
  → output: 255 ✓
```

This avoids `malloc` entirely. The recursion depth is at most 10 levels for a 32-bit integer (log10 of UINT_MAX ≈ 9.6), which is negligible stack usage.

### Internal handler functions

Each conversion specifier is handled by a dedicated function (private, not in header):

- **`ft_printf_char()`** — writes a single character via `write()`, returns 1
- **`ft_printf_str()`** — writes a string character-by-character, handles NULL (`"(null)"`)
- **`ft_printf_nbr()`** — writes signed 32-bit integer, recursively extracts digits, handles INT_MIN separately
- **`ft_printf_unsigned()`** — writes unsigned 32-bit integer, recursively extracts digits
- **`ft_printf_hex()`** — writes unsigned int as hex with optional uppercase flag (0 = lowercase, 1 = uppercase)
- **`ft_printf_ptr()`** — casts `void*` to `unsigned long` and formats with `0x` prefix, handles NULL (`"(nil)"`)

All handlers return the number of bytes written (return value of `write()`).

### Special cases

- **`INT_MIN`** (`-2147483648`) cannot be negated as a signed 32-bit int — doing so causes undefined behaviour due to overflow. It is handled as a hardcoded string write before the general signed logic runs.
- **NULL `%s`** prints `"(null)"` to match the behaviour of the real `printf()`.
- **NULL `%p`** prints `"(nil)"` to match the behaviour of the real `printf()`.
- **`%p`** casts the pointer to `unsigned long` before printing, ensuring correct 64-bit address width on modern systems.

---

## Notes & Limitations

### What is NOT implemented (intentional)

- **Format modifiers** (`-`, `+`, `0`, `.`, `*`, width/precision flags) — not required by the 42 assignment
- **Buffer management** — output is written directly to stdout via `write()` with no internal buffering
- **float/double conversions** (`%f`, `%e`, `%g`) — not required
- **Locale-specific formatting** — not needed for this scope

### Edge cases handled correctly

- `INT_MIN` (`-2,147,483,648`) — cannot be negated as a 32-bit signed int; handled with hardcoded string write
- `UINT_MAX` (`4,294,967,295`) — correctly printed by unsigned handler via recursion
- NULL pointers in `%s` and `%p` — print `"(null)"` and `"(nil)"` respectively, matching glibc behaviour
- Empty format string — returns 0
- Lone `%` at end of format string — undefined behaviour (matches real `printf()` in this case)
- `%%` escape sequence — prints a single literal `%`

### Performance characteristics

- **Time complexity:** O(n + m) where n = format string length, m = total digits/characters across all arguments
- **Space complexity:** O(1) — only uses a `va_list` and tracking variables; no allocations
- **Recursion depth:** Maximum ~10 levels for integer printing (log10 of UINT_MAX)
- **write() calls:** One per character (no buffering) — may be slow for very large output

---

## Resources

### Official documentation

- [printf(3) — Linux man page](https://man7.org/linux/man-pages/man3/printf.3.html)
- [stdarg(3) — va_list macros](https://man7.org/linux/man-pages/man3/stdarg.3.html)
- [write(2) — system call](https://man7.org/linux/man-pages/man2/write.2.html)
- [ar(1) — static library archiver](https://man7.org/linux/man-pages/man1/ar.1.html)

### Articles and tutorials

- [How printf works internally — Eli Bendersky's blog](https://eli.thegreenplace.net/2011/09/06/stack-frame-layout-on-x86-64) — useful background on calling conventions
- [Variadic functions in C — cppreference](https://en.cppreference.com/w/c/variadic)
- [Static libraries in C — cs.colby.edu](http://cs.colby.edu/maxwell/courses/tutorials/maketutor/)
- [42 Norm v4](https://github.com/42School/norminette) — style rules your code must follow

### AI usage

Claude (Anthropic) was used during this project for the following tasks:

- **Project understanding** — summarising the subject requirements and clarifying what does and does not need to be implemented (e.g. no buffer management, no width/precision flags in mandatory part).
- **Documentation** — generating the implementation guide document and this README structure.
- **Test generation** — producing the `test_ft_printf.c` file covering all 9 specifiers and edge cases (INT_MIN, UINT_MAX, NULL pointers, return value checks).
- **Debugging** — identifying bugs in the Makefile (missing `ar rcs` flags, space in substitution macro, empty `SRC` variable, typo in `-lftprintf`).
- **Code review** — checking the header file for missing prototypes (`ft_print_uint`, `ft_print_hex`) and unnecessary includes (`stdio.h`, `stdlib.h`).

