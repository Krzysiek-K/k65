#

## Alternate VCS Definitions

File `_defs.k65` provides alternate definitions of Atari 2600 registers.

Using this file is optional (standard VCS register names are predefined), but it is useful for fast prototyping because aliases are shorter and easier to type.

## Key Register Aliases

### TIA (write)

- `NUSIZ0 -> ns0`, `NUSIZ1 -> ns1`
- `COLUP0 -> cp0`, `COLUP1 -> cp1`, `COLUPF -> cpf`, `COLUBK -> cbg`
- `CTRLPF -> ctpf`
- `REFP0 -> rep0`, `REFP1 -> rep1`
- `PF0 -> pf0`, `PF1 -> pf1`, `PF2 -> pf2`
- `RESP0 -> rp0`, `RESP1 -> rp1`, `RESM0 -> rm0`, `RESM1 -> rm1`, `RESBL -> rb`
- `GRP0 -> gp0`, `GRP1 -> gp1`
- `ENAM0 -> em0`, `ENAM1 -> em1`, `ENABL -> eb`
- `HMP0 -> hp0`, `HMP1 -> hp1`, `HMM0 -> hm0`, `HMM1 -> hm1`, `HMBL -> hb`
- `VDELP0 -> vdp0`, `VDELP1 -> vdp1`, `VDELBL -> vdb`
- `RESMP0 -> rmp0`, `RESMP1 -> rmp1`
- `HMOVE -> hmove`, `HMCLR -> hmclr`
- `AUDC0 -> ac0`, `AUDC1 -> ac1`, `AUDF0 -> af0`, `AUDF1 -> af1`, `AUDV0 -> av0`, `AUDV1 -> av1`

### PIA

- `SWCHA -> swcha`
- `SWCHB -> swchb`

## Special Macros

- `init` - clears zero page, sets stack top, disables interrupts and decimal mode
- `timwait` - waits until PIA timer reaches zero
- `wsync` - waits for horizontal blank (`WSYNC=a`)
- `sync1` - starts overscan timing
- `sync2` - pulses `VSYNC` and starts vertical blank timing
- `sync3` - starts visible screen period

## Local Reference

- Example implementation: `k65/workdir/a2600-tutorial-03/_defs.k65`

---

_Source: [Alternate_VCS_definitions](http://devkk.net/wiki/index.php/Alternate_VCS_definitions)_
