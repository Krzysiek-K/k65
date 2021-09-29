#

* Accidential bank switching can occur when branch instruction jumps back from last bank to previous bank. Example: branch instruction at `$1F0C` jumps back to `$1EF4` because branching across page boundary is done in **6502** in two steps (first compute lower address, then higher), **CPU** does extra memory fetch from `$1FF4` (old high address byte, new low address). This can trigger unwanted bank switching. Currently there is no way of detecting this.
* **Far calls** placed in inline blocks do not work correctly if the inline is used in different bank that it was defined.
* Local labels can't be accessed across certain language constructs (like far calls). Local labels before and after such construct appear to be in different local namespaces.
* Code parser can hang on unexpected input characters.