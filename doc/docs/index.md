# Welcome to K65

K65 is a compiler for [6502 CPU](https://en.wikipedia.org/wiki/MOS_Technology_6502) architecture. At this moment it supports **Atari 8-bit** (400/800/XL/XE), **Commodore 64** and **Atari 2600** as target platforms.

## Start Here (Navigation)

### Core

- [Syntax](syntax.md)
- [Instructions](instructions.md)
- [Evaluator](evaluator.md)
- [Examples](examples.md)

### Platforms

- [Atari 800/65 XE](platform-atari-8bit.md)
- [Atari 2600 / VCS (Examples)](examples.md)
- [Commodore 64](platform-c64.md)
- [Alternate VCS Definitions (Atari 2600)](alternate-vcs-definitions.md)

### Project Info

- [Downloads](downloads.md)
- [Changelog](changelog.md)
- [Tutorials](tutorials.md)
- [Projects](projects.md)
- [Known Bugs](known-bugs.md)
- [To Do](todo.md)

---

## Language Support

### Visual Studio Code

* Syntax Highlighting [Extension](https://marketplace.visualstudio.com/items?itemName=vscode-k65.vscode-k65)


---

## Downloads

### Current release

[K65 SDK version 0.2.1](http://devkk.net/files/k65-sdk-0.2.1.zip)

### Older releases

* [K65 SDK version 0.2.0](http://devkk.net/files/k65-release-0.2.0.zip)
* [K65 SDK version 0.1.2](http://devkk.net/files/k65-release.zip)

---

## Changelog

### SDK 0.2.1

* New example Atari 2600 demo sources included: Ascend and Derivative 2600 by Cluster & DMA
* Linker now reports final section sizes again
* Minor compiler bugfixes
* **FIX**: Atari XL/XE and C64 systems sometimes exported truncated images

---

## Local Preview (MkDocs)

```bash
mkdocs serve
```

After starting:

- `http://127.0.0.1:8000/`

## Common Commands

```bash
mkdocs serve
mkdocs build
mkdocs gh-deploy
```

## How to Update Content

1. Edit files in `doc/docs/*.md`.
2. If you add a new page, add it to `doc/mkdocs.yml` (`nav:`).
3. Verify locally with `mkdocs serve`.
4. Run `mkdocs build` before submitting changes.

## Reference Links

- Public documentation: [zbyti.github.io/k65-mkdocs](https://zbyti.github.io/k65-mkdocs/)
- Original K65 wiki: [devkk.net/wiki/index.php/K65](http://devkk.net/wiki/index.php/K65)
- K65 sources: [github.com/Krzysiek-K/k65](https://github.com/Krzysiek-K/k65)

---

*This documentation is currently being built.*