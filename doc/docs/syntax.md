#

## Comments

**K65**  uses **C**-like comments.

```c
// this is a line comment

/* this is a
   block comment */
```

## Variable declaration

Variables in **K65** are names given to chosen memory addresses.
Examples of variable declaration:

```c
var foo=0x80            // declares 'foo' at address 0x80
var foo2                // declares 'foo2' at address 0x81 (next after previous var)
var foo3, foo4          // multiple declarations per line allowed
var bar[10], bar2[10]   // [] specifies variable size in bytes (address increment for next var)
var bar3 ?              // adding '?' at the end of var declaration makes compiler print var addresses
```

## Constant declaration

The best way of defining constants is using the **evaluator**. Constants defined this way can be changed at any moment during compilation. Constants can be any value of floating point type. When used within **6502** instruction, they are converted to single byte by rounding to nearest integer and `AND`-ing with `0xFF` (this way negative values are represented in U2 form).

Examples:

```c
[                       // square brace starts evaluator expression
  MY_CONSTANT = 5,      // define constants
  SOME_NUMBER = 0x13
]                       // end of evaluator expression
```

## Numeric literals

K65 accepts decimal, hexadecimal and binary numeric literals.

```c
var dec = 42
var hex = 0x2A
var bin = 0b00101010
```

## Labels

A label can be placed at the beginning of a statement. During assembly, the label is assigned the current value of the active location counter and serves as an instruction operand. There are two types of labels: global and local. Examples are shown below.

### Global

```c
var SCREEN=0x400

main {
  x=0 {
    a=hello,x z-?{ SCREEN,x=a x++ }
  } z-?

  return
}

data text_data {
  charset ".ABCDEFGHIJKLMNOPQRSTUVWXYZ..... "

  hello: "HELLO WORLD" 0
}
```

### Local

```c
func draw_level {
  .LV_TO_DRAW+1=a=p_current_lv .LV_TO_DRAW+2=a=p_current_lv+1

  .LT+1=.LD+1=a=&<screen_1+224 .RT+1=.RD+1=a=&<screen_1+225
  .LT+2=.RT+2=a=&>screen_1+0x100 .LD+2=.RD+2=a=&>screen_2+0x100

  y=[LV_SIZE] {
    .LV_TO_DRAW: a=levels,y

    x=a .LT: screen_1=x x++ .RT: screen_1+1=x
    a|0x20
    x=a .LD: screen_2=x x++ .RD: screen_2+1=x

    c+ a=.LT+1 a-2 .LT+1=.LD+1=a c-?{ .LT+2-- .RT+2-- .LD+2-- .RD+2-- } x=a x++ .RT+1=.RD+1=x

    y--
  } !=
}
```

## Bank selection

While default bank can be chosen in file list for each file, a file can span across multiple banks. Active bank can be changed at any point in the file.

Example:

```c
bank my_bank            // from now on all code and data will go to 'my_bank'
```

## Raw data

You can use raw data to put (for example) unsupported opcodes or allocate certain memory for variables etc.

Example:

```c
var bcol=0xd020

main {
  data { 0xEA 0xEA 0xEA }
  { bcol++ } always
}

// produce this code:
//
//.C:0810  4C 13 08    JMP $0813
//.C:0813  EA          NOP
//.C:0814  EA          NOP
//.C:0815  EA          NOP
//.C:0816  EE 20 D0    INC $D020
//.C:0819  4C 16 08    JMP $0816
```

## Data block definition

Data blocks are defined using the `data` keyword. Defining a data block also defines a label for its first element, so the block is accessible using simple indexing, like `MyData,x`. Data blocks can have optional **alignment** or **no-page-crossing** restrictions enabled.

Examples:

```c
data MyData1 {
  align 16              // align to 16 byte boundary
  1 2 3 4 5 6 7 8       // data bytes follow
}

data MyData2 {
  align 256 + 8         // align to 8 bytes after page boundary (lower address byte will be 0x08)
  1 2 3 4 5 6 7 8       // data bytes follow
}

data MyData3 {
  nocross               // the data will fit completely inside single page, but can be at any offset within it
  1 2 3 4 5 6 7 8       // data bytes follow
}

data MyData4 {
  address 0x5000        // fixed memory address
  1 2 3 4 5 6 7 8       // data bytes follow
}

data MyData5 {
  0 0 code { a=x }
}

data sprite {
  align 256
  // image <file> <x0> <y0> <byte> <repeat> - gather bits from image
  //  <file>    - file name without ".bmp" extension
  //  <x0> <y0> - first pixel to scan
  //  <byte>    - scanning mode for each single byte starting with MSB (count+direction)
  //  <repeat>  - scanning mode for consecutive bytes (count+direction)

  image sprites  0 0 8> 16v   // start at pixel (0,0), each byte is 8 bits to the right, repeat 16 times going up
  image sprites 10 0 8> 16v   // do the same from (10,0)
  image sprites 20 0 8> 16v   // and again starting at (20,0)
}

data fonts {
    address 0x5000
    image "data/font" 0 0  8> 8v tiles 8 0 31
    image "data/font" 0 8  8> 8v tiles 8 0 31
    image "data/font" 0 16 8> 8v tiles 8 0 31
    image "data/font" 0 24 8> 8v tiles 8 0 31
}

data table {
  address 0x2000
  binary "table.bin"
}

data SineX {
  align 256
  0
  for x=0..213 eval [ (sin(x/212*pi*2)*.499+.499)*130 ]
}

data SineY {
  align 256
  0
  for x=0..255 eval [ (sin(x/256*pi*2)*.499+.499)*180+1 ]
}

data InfoScript {
  charset " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!'-?:/()acelnosxz&"

  "CONNECTED TO THE INTERVIEW" 0xFE
  "WITH THIS GREAT" 0xFE
  "ARTIST." 0xFE 0xF0
  0xFE
}
```

## Image declarations for evaluator

You can declare an image as an evaluator source and then read its pixels in evaluator expressions.

```c
image World = "files/world.bmp"

data WorldMask {
  for i=0..99 eval [
    x=i%10,
    y=floor(i/10),
    (World[x,y] & 0x80) ? 1 : 0
  ]
}
```

This is different from `image ...` used inside `data` blocks. Here, the image is exposed to the evaluator as a 2D source (`ImageName[x,y]`).

## `nocross` for code blocks

`nocross` can also be used with a code block to force the whole block to stay inside one memory page. This is useful for timing-critical loops and self-modifying code patterns.

```c
nocross {
  y=4 {
    lda_table,y
    y--
  } >=0
}
```

If the block cannot fit in one page, compilation fails.

## Compile-time Evaluator

The **K65** compiler has an embedded evaluator that always executes at compile time. The evaluator can perform arbitrary math operations whose results are inlined in the final code as immediates. The evaluator can also set and use global compiler constants.

The evaluator is explained in detail on [K65 Evaluator](evaluator.md) page.

## Code sections

Executable code in the K65 compiler is specified in sections. The currently supported types of code sections are:

### `main`

This function is the program entry point.

```c
main {
  a=0        // set accumulator to 0
  {} always  // loop forever
}
```

### `func`

User defined function, that can be called from the code.

```c
func inc_x {
  x++        // increments X register and returns
}            // RTS is added automatically
```

### `naked`

Just like `func`, but no `RTS` is added automatically at the end.

```c
naked inc_x_twice {
  x++        // increments X register
  goto inc_x // jump to previously defined inc_x (saves stack)
}            // no RTS here; make sure function never reaches here
```

### `inline`

User defined `macro` that is inlined in the code when used.

```c
inline inc_y {
  y++
}
```

Functions and inlines are used simply by specifying their names, which places `JSR` opcode or inlines the code. Function and inline calls do not pass any parameters. Any potential parameter and return value handling must be handled explicitly by the programmer using either registers, stack or predetermined memory locations.

```c
func test {
  inc_x      // this will use JSR instruction to call 'inc_x' defined earlier
  inc_y      // this will inline the 'inc_y' inline - note that it will not add any overhead compared to simple 'y++'
}
```

## `else`

In practice, this creates (in branch code) a jump to a generated label outside the `else` block.

Example:

```c
inline check_if_key_or_doors {
  a?60 == {gamestate_keys++}
  else {
    a?62 == {
        ptr_doors=a=x
        temp1=a=1
    }
  }
}
```

## Far calls

Functions can also be called with the `far` prefix to mark that the target function is in another bank than the current one. The bank-switching mechanism used is defined by the linker. Inlines do not use the `far` prefix, because the code is simply inlined.

**NOTE**: If a far call is used within an inline, use such inline with care. Inlining it in another bank will copy the inline code directly, which usually results in improper bank switching and a program crash.

```c
func test2_in_different_bank {
  far inc_x
}
```

---

*This page is still under construction - much of the information is still to be filled.*
