#

Evaluator in **K65** is compile-time executed expression language very similar to **C/C++** expressions.

## Introduction

In every place where the compiler expects a single number, you can invoke the evaluator by simply using square brackets.

```c
data NumberFour {
  [2+2]
}
```

The evaluator can be also invoked freely outside any section body, e.g. to set variables:

```c
[ FOUR = 4 ]
```

which can be later used freely as compiler constants and within further evaluator expressions:

```c
data FourFiveSix {
  FOUR             // value of variable FOUR defined earlier
  [FIVE = FOUR+1]  // defines variable FIVE and returns its value
  [FIVE+1]         // uses recently set FIVE value
}
```

## Operators

Available operators and their precedence levels are similar to operators in **C** and **C++**, operators are sorted by precedence from highest to lowest:

### Precedence 2

Associativity: **left-to-right**

Operator|Description
:---:|:---
`++`<br/>`--`<br/>`()`<br/>`[]`<br/>`.` |suffix incremen<br/>suffix decrement<br/>function call<br/>array subscripting<br/>single argument function call

---

### Precedence 3

Associativity: **right-to-left**

Operator|Description
:---:|:---
`++`<br/>`--`<br/>`+`<br/>`-`<br/>`!`<br/>`~`|prefix increment<br/>prefix decrement<br/>unary plus<br/>unary minus<br/>logical NOT<br/>bitwise NOT (One's Complement)

---

### Precedence 5

Associativity: **left-to-right**

Operator|Description
:---:|:---
`*`<br/>`/`<br/>`%`|multiplication<br/>division<br/>modulo (remainder)

---

### Precedence 6

Associativity: **left-to-right**

Operator|Description
:---:|:---
`+`<br/>`-`|addition<br/>subtraction

---

### Precedence 7

Associativity: **left-to-right**

Operator|Description
:---:|:---
`<<`<br/>`>>`|bitwise left shift<br/>bitwise right shift

---

### Precedence 8

Associativity: **left-to-right**

Operator|Description
:---:|:---
`<`<br/>`<=`<br/>`>`<br/>`>=`<br/>`?>`<br/>`?<`|less than<br/>less than or equal to<br/>greater than<br/>greater than or equal to<br/>select greater value (maximum)<br/>select smaller value (minimum)

---

### Precedence 9

Associativity: **left-to-right**

Operator|Description
:---:|:---
`==`<br/>`!=`|equal to<br/>not equal to

---

### Precedence 10

Associativity: **left-to-right**

Operator|Descriptiont
:---:|:---
`&`|bitwise AND

---

### Precedence 11

Associativity: **left-to-right**

Operator|Description
:---:|:---
`^`|bitwise XOR (exclusive or)

---

### Precedence 12

Associativity: **left-to-right**

Operator|Description
:---:|:---
`|`|bitwise OR (inclusive or)

---

### Precedence 13

Associativity: **left-to-right**

Operator|Description
:---:|:---
`&&`|logical AND

---

### Precedence 14

Associativity: **left-to-right**

Operator|Description
:---:|:---
`||`|logical OR

---

### Precedence 15

Associativity: **right-to-left**

Operator|Description
:---:|:---
`?:`|lternary conditional

---

### Precedence 16

Associativity: **right-to-left**

Operator|Description
:---:|:---
`=`<br/>`+=`<br/>`-=`<br/>`*=`<br/>`/=`<br/>`%=`<br/>`<<=`<br/>`>>=`<br/>`&=`<br/>`^=`<br/>`|=`<br/>|direct assignment<br/>assignment by sum<br/>assignment by difference<br/>assignment by product<br/>assignment by quotient<br/>assignment by remainder<br/>assignment by bitwise left shift<br/>assignment by bitwise right shift<br/>assignment by bitwise AND<br/>assignment by bitwise XOR<br/>assignment by bitwise OR<br/>

---

### Precedence 18

Associativity: **left-to-right**

Operator|Description
:---:|:---
`,`|expression list (executes in sequence, returns value of the last)

---

## Functions

### `acos( x )`

Arcus cosinus

---

### `addbyte( sec, b )`

Add byte b to section sec

---

### `asin( x )`

Arcus sinus

---

### `ceil( x )`

Round up to nearest integer

---

### `clamp( x, min, max )`

Clamp x to range min to max

---

### `color( r, g, b )`

Return palette index for nearest color to color (r,g,b)

---

### `color( x )`

Return palette index for nearest color specified in format 0xRRGGBB

---

### `cos( x )`

Cosinus

---

### `error( err )`

Print error message err ane terminate compilation

---

### `floor( x )`

Round down to nearest integer

---

### `frac( x )`

Get fractional part ( x-floor(x) )

---

### `index( tab, x )`

1-dimensional indexing operator ( same as tab[x] )

---

### `index( tab, x, y )`

2-dimensional indexing operator ( same as tab[x,y] )

---

### `max( a, b )`

Maximum

---

### `min( a, b )`

Minimum

---

### `pow( x, y )`

Power function

---

### `print( msg )`

Print message msg

---

### `rnd( )`

Random value 0 <= x < 1

---

### `round( x )`

Round to nearest integer

---

### `sin( x )`

Sinus

---

### `size( sec )`

Current size of section sec

---

### `sqrt( x )`

Square root