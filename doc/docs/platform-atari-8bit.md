#

## Atari 800/65 XE Platform Notes

This page focuses on using **K65** with Atari 8-bit hardware features (ANTIC/GTIA/POKEY), with examples that show platform integration patterns.

## Minimal frame loop with WSYNC

This loop updates background color once per scanline.

```c
var COLBK = 0xD01A
var VCOUNT = 0xD40B
var WSYNC = 0xD40A

main {
  {
    a=VCOUNT
    COLBK=a
    WSYNC=a
  } always
}
```

## Display list setup (text mode)

Set your own display list and point ANTIC to it.

```c
var DLISTL = 0xD402
var DLISTH = 0xD403
var DMACTL = 0xD400

var screen = 0x9000

data my_dl {
  nocross
  0x70 0x70 0x70
  0x42 &<screen &>screen
  for x=0..21 eval [2]
  0x41 &<my_dl &>my_dl
}

main {
  DLISTL=a=&<my_dl
  DLISTH=a=&>my_dl
  DMACTL=a=0b00100010
  {} always
}
```

## DLI script pattern

A small DLI handler can change colors in selected display regions.

```c
var VDSLST = 0x0200
var NMIEN  = 0xD40E
var WSYNC  = 0xD40A
var COLPF2 = 0xD018

naked dli_fn {
  a!!
  WSYNC=a
  COLPF2=a=0x3A
  a??
  return_i
}

main {
  VDSLST=a=&<dli_fn
  VDSLST+1=a=&>dli_fn
  NMIEN=a=0xC0
  {} always
}
```

## Player/Missile Graphics quick init

Allocate PMG memory, enable DMA, and position one player.

```c
var PMBASE = 0xD407
var DMACTL = 0xD400
var GRACTL = 0xD01D
var HPOSP0 = 0xD000
var SIZEP0 = 0xD008
var COLPM0 = 0xD012

var pmg = 0xA000

main {
  PMBASE=a=&>pmg
  DMACTL=a=0b00111010
  GRACTL=a=0x03

  HPOSP0=a=120
  SIZEP0=a=0x01
  COLPM0=a=0x4E

  {} always
}
```

## Compile-time tables for Atari effects

K65 evaluator is practical for generating lookup tables used in runtime effects.

```c
data Sine128 {
  align 256
  for x=0..127 eval [ (sin(x/128*pi*2)*.5+.5)*255 ]
}
```

Use this with `VSCROL`, sprite positions, color gradients, or display list modulation.
