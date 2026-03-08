#

## Tutorial 1 - Simple Raster Bar Animation

This tutorial shows a minimal Atari 2600 frame loop with color animation.

- It uses `_defs.k65` helper inlines (`init`, `sync1`, `sync2`, `sync3`, `wsync`).
- It animates background color by incrementing a RAM variable each frame.

```c
/* Tutorial 01 - simple raster bar animation */

var anim = 0x80

main {
  init

  {
    sync1
    sync2
    sync3

    x=224
    y=anim
    {
      wsync
      cbg=y
      y++
      x--
    } !=

    cbg=a=0
    anim++
  } always
}
```

---

_Source: [K65_Tutorial_1](http://devkk.net/wiki/index.php/K65_Tutorial_1)_

