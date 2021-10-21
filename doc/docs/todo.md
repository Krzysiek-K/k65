#

Here is my current list of things still to be done in **K65** compiler.

## Simple

* signal errors on undefined character in string
* \#if's within data
* \#if's within code
* support for binary numbers
* report error when section names are reused (e.g. in **inline** section)
* correct support of `<flag>+?` and `<flag>-?` branch operators
* `>={...}>=` loops and similar
* support for negative eval results
* extend binary operations in eval
* change `^` operator to bitwise `xor` in eval
* 256-byte data section should work with nocross
* add fixed address option for sections
* add option to place sections in multiple banks
* fix lexer hanging on invalid input

## Medium

* support for custom palettes
* mark section as referenced if ANY of its labels are referenced
* array support
* option to force full addressing with zeropage addresses
* include raw binary data from file
* extend computation on labels (compute `Label1 - Label2 + Offset`)
* switch to external image loader library (OpenIL?)

## Hard/large

* macros
* pure assembly sections
* alternate bankswitching schemes
* alternate platforms
* per-instruction bank bits
* linker refactoring
* generalized linker
* bank blocks jumping
* bank checking when getting addresses
* option to override `ORG` and `RORG` execution address
* *lazy* code sections
* target files and names `.bin` `.lst` `.sym` in config file
* make `LST` files compatible with **DASM/Stella**
* language reference document