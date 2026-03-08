#

## Commodore 64 Platform Notes

This page shows practical **K65** patterns for C64 hardware integration (VIC-II/CIA/SID oriented workflows).

## Build profile for C64

A minimal project profile usually starts with the C64 target and output PRG.

```none
-system C64
-o demo.prg

main.k65  main
```

## Raster IRQ skeleton

Typical C64 effects are driven by raster interrupts.

```c
var IRQADL  = 0xFFFE
var IRQADH  = 0xFFFF
var VICIRQ  = 0xD019
var IRQMASK = 0xD01A
var RASTER  = 0xD012
var CIAICR  = 0xDC0D
var CI2ICR  = 0xDD0D

var frame = 0x20

naked irq_raster {
  a!!
  a=VICIRQ
  a&1 != {
    VICIRQ=a=1
    frame++
  }
  a??
  return_i
}

main {
  i+
  CIAICR=a=0x7F
  CI2ICR=a=0x7F
  a=CIAICR a=CI2ICR

  IRQADL=a=&<irq_raster
  IRQADH=a=&>irq_raster
  RASTER=a=250
  IRQMASK=a=1
  i-

  {} always
}
```

## VIC-II screen/bitmap mapping

You can place bitmap and screen buffers in explicit memory blocks and point VIC-II to them.

```c
var VMCSB = 0xD018
var CI2PRA = 0xDD00

var SCREEN = 0xC000
var BITMAP = 0xE000

main {
  a=CI2PRA
  a&0xFC
  CI2PRA=a

  VMCSB=a=0b00001000
  {} always
}
```

## Fast memory fill with pointers

Pointer-driven loops are a common K65 idiom on C64.

```c
var ptrA[2] = 0x40
var SCREEN  = 0x0400

inline clear_1k {
  ptrA=a=&<SCREEN
  ptrA+1=a=&>SCREEN
  x=4 {
    y=0 { (ptrA),y=a y++ } !=
    ptrA+1++
    x--
  } !=
}
```

## CIA timer tick pattern

CIA timer interrupts are often used for periodic jobs (for example music playback).

```c
var TIMALO = 0xDC04
var TIMAHI = 0xDC05
var CIACRA = 0xDC0E
var CIAICR = 0xDC0D

inline cia_timer_start {
  TIMALO=a=0x89
  TIMAHI=a=0x49
  CIACRA=a=0b10010001
  CIAICR=a=0b10000001
}
```

## Notes

- Keep IRQ handlers short and deterministic.
- Acknowledge VIC/CIA interrupt sources explicitly.
- For time-critical raster code, consider small `naked` handlers with explicit save/restore.

---

Reference inspiration: [k65-examples/c64-escape](https://github.com/Krzysiek-K/k65-examples/tree/master/c64-escape)
