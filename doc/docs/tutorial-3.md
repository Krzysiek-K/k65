#

## Tutorial 3 - Data... Continued (Embedding Images)

This tutorial combines image-imported sprite data with generated sine tables.

- `image` directives extract sprite bytes from a bitmap source.
- `SineX` and `SineY` are compile-time generated lookup tables.
- The main loop computes sprite frame, horizontal position, and vertical position.

```c
/* Tutorial 03 - data... continued */

var anim=0x80, cntX, cntY

data sprite {
  align 256
  image sprites  0 0 8> 16v
  image sprites 10 0 8> 16v
  image sprites 20 0 8> 16v
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
```

## Local Reference

- Local sample: `k65/workdir/a2600-tutorial-03/main.k65`
- Local helper definitions: `k65/workdir/a2600-tutorial-03/_defs.k65`

---

_Source: [K65_Tutorial_3](http://devkk.net/wiki/index.php/K65_Tutorial_3)_

