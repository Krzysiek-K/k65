#

## Tutorial 2 - Using Data

This tutorial adds static and generated data blocks to drive animation.

- `raster_data` is a static color pattern.
- `sine_table` is generated at compile time using `for` and `eval`.
- `raster_bar` is an `inline` reused three times in one frame.

```c
/* Tutorial 02 - using data */

var anim = 0x80
var tmp = 0x81

data raster_data {
  0
  0xD0 0xD2 0xD4 0xD6 0xD8 0xDA 0xDC
  0xDE 0xDC 0xDA 0xD8 0xD6 0xD4 0xD2 0xD0
}

data sine_table {
  align 256
  for x=0..255 eval [ (sin(x/128*pi*2)*.499+.499)*178+1 ]
}

inline raster_bar {
  x=15
  {
    wsync
    a=raster_data,x
    cbg=a
    x--
  } !=
  cbg=a=0
}
```

---

_Source: [K65_Tutorial_2](http://devkk.net/wiki/index.php/K65_Tutorial_2)_

