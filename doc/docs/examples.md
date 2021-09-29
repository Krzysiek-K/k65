#

## Scripts

### Project example files

`main.k65proj`

```none
-system AtariXL
-lowAddr 0x2000

../../include/defs.k65  main
main.k65                main

-o main.xex

-link
!atari800 main.xex
```

`make`

```none
K65=${K65_HOME}/bin/k65

all: main clean

main:
  $(K65) @main.k65proj

clean:
  rm main.gmap main.lst main.sym
```

## Atari 800 XL

### Rainbow

```c
main {
  {
    COLPF2=a=VCOUNT
    WSYNC=a
  } always
}
```

### Starfield

```c
var PCOLR0 = 0x02C0

data stars {
  align 256
  for x=0..255 eval [ rnd() & 255 ]
}

data speed {
  align 256
  for x=0..255 eval [ (rnd() & 3) + 1 ]
}

main {
  PCOLR0=a=14 GRAFM=a
  {
    a=0 { a?VCOUNT } !=
    x=0 {
      WSYNC=a
      HPOSM0=a=stars,x
      a=stars,x a+speed,x stars,x=a
      x++
    } !=
  } always
}
```

### DLI example

```c
var VDSLST = 0x0200
var SDLST  = 0x0230

var screen = 0x8000

data displist {
  nocross
  0x70 0x70 0x70
  0x42 &<screen &>screen
  2 2 2
  0xF0
  2 2 2 2
  0x41 &<displist &>displist
}

naked dli {
  a!!
  COLPF2=a=0xDE WSYNC=a
  a??
  return_i
}

main {
  SDLST=a=&<displist SDLST+1=a=&>displist
  VDSLST=a=&<dli VDSLST+1=a=&>dli
  NMIEN=a=0xC0
  {} always
}

```

### Flame

```c
//------------------------------------------------------------------------------
// Flame by koalka/bbsl/karzelki
//------------------------------------------------------------------------------

var RTCLOK = 0x0014
var SDLSTL = 0x0230
var SDLSTH = 0x0231
var SDMCTL = 0x022F
var GPRIOR = 0x026F
var COLOR4 = 0x02C8
var CHBAS  = 0x02F4

var fonts  = 0x6000
var screen = 0x6400

data dl {
  nocross
  0x42  &<screen &>screen
  for x=0..19 eval [2]
  0x41  &<dl &>dl
}

inline pause {
  a=RTCLOK { a?RTCLOK } ==
}

main {
  COLOR4=a=0x20 CHBAS=a=&>fonts
  SDLSTL=a=&<dl SDLSTH=a=&>dl
  GPRIOR=a=0x40 SDMCTL=a=0x21

  a=0 x=a y=a

  {
    screen,x=a
    screen+0x100,x=a
    screen+0x200,x=a
    screen+0x300,x=a
    x++
  } !=

  {
    { fonts,x=a x++ y++ y?8 } !=
    y=0 c- a+0x11
  } <

  {
    {
      a=screen-1,y c-
      a+screen,y a+screen+1,y a+screen+32,y a>> a>>
      screen-31,y=a

      a=screen+0xFF,y c-
      a+screen+0x100,y a+screen+0x101,y a+screen+0x120,y a>> a>>
      screen+0xE1,y=a

      a=screen+0x1FF,y c-
      a+screen+0x200,y a+screen+0x201,y a+screen+0x220,y a>> a>>
      screen+0x1E1,y=a

      y++
    } !=

    COLBK=a=10 pause

    x=0x1F {
      a=RANDOM a&15 screen+0x2E0,x=a
      x--
    } >=0

  } always
}
```

### Mode 9++/10++

```c
// Mode 9++  GPRIOR=a=0x40
// Mode 10++ GPRIOR=a=0x81

var VDSLST=0x0200, SDLSTL=0x0230, SDMCTL=0x022F, GPRIOR=0x026F

var screen = 0xF000

data dl {
  nocross
  0x90 0x6F &<screen &>screen
  for x=1..58 eval [ x&1 ? 0x8F : 0x2F ]
  0x41 &<dl &>dl
}

naked dli {
  a!!
  WSYNC=a VSCROL=a=13 VSCROL=a=3
  a??
  return_i
}

main {
  VDSLST=a=&<dli VDSLST+1=a=&>dli
  SDLSTL=a=&<dl SDLSTL+1=a=&>dl
  SDMCTL=a=0x22 GPRIOR=a=0x40 NMIEN=a=0xC0
  {} always
}
```

### Quatari landscape

```c
//------------------------------------------------------------------------------
// This is a part of Quatari 256B intro
// https://demozoo.org/productions/280623
// for 8bit AtariXL, OS Rev 2
//------------------------------------------------------------------------------

var CURSOR_Y = 0x54
var CURSOR_X = 0x55
var PREV_Y   = 0x5A
var PREV_X   = 0x5B

var iter     = 0x80

var COLOR4   = 0x02C8
var COLOR    = 0x02FB
var RND      = 0xD20A
var openmode = 0xEF9C
var drawto   = 0xF9C2

data colorHeight {
  170 150 144 144 122 122 110 110 94 94 86 86 82 80
}

main {
  a=9 call openmode
  COLOR4=a=0xB0

  iter=a=79 {
    CURSOR_X=a=iter PREV_X=a
    PREV_Y=a=1 COLOR=a=13
    {
      x=COLOR
      CURSOR_Y=a=colorHeight,x
      a=RND <0 { colorHeight,x++ }
      a=RND <0 { colorHeight,x-- }
      call drawto
      COLOR--
    } >=0
    iter--
  } !=

  {} always
}
```

### Screensaver

```c
var LNFLG = 0, RTCLOK = 0x14, tmp = 0x80

main {
  a=0x3f tmp=a
  a=0xff x=0xf { HPOSP0,x=a x-- } >=0

  {
.start:
    WSYNC=a
    a=LNFLG LNFLG++
    a^0x20 HPOSP0=a a^tmp HPOSP1=a
    a=VCOUNT COLPM0=a a^0xff COLPM1=a
    a=VCOUNT a?0x40 < goto .jump
    LNFLG-- LNFLG--
.jump:
    a=VCOUNT != goto .start
    a=RTCLOK LNFLG=a a&0x7f != goto .start
    tmp++
  } always
}
```
