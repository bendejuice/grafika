# Pixel Paint - SDL2 alapú pixelgrafikus rajzprogram

Ez egy egyszerű, mégis menő pixelgrafikus rajzprogram C nyelven, SDL2-vel. A program lehetővé teszi rétegek kezelését, színpalettából való választást, ecset/radír használatát és még sok mást!

##  Fő funkciók

-  **Színpaletta**: kattints a képernyő alján lévő színekre
-  **Pixeles rajz**: 32x32-es vászon
-  **Ecset és radír mód**:
  - `B`: ecset mód
  - `E`: radír mód (fehér színnel fest)


## 🧰 Követelmények

- C fordító (pl. `gcc`)
- [SDL2](https://libsdl.org)
- [SDL2_ttf](https://wiki.libsdl.org/SDL_ttf)

## 🔧 Fordítás

A projekt Makefile-lal építhető:

```bash


make
./pixel_paint

project/
├── src/
│   ├── main.c
│   ├── canvas.c/h     # vászon és rétegek kezelése
│   ├── input.c/h      # eseménykezelés
│   ├── palette.c/h    # színpaletta
├── Makefile
├── README.md


✨ Tervezett fejlesztések

Rétegek
✅ Színpaletta
Egyéni színválasztó (RGB csúszkák)
Mentés / betöltés .png vagy .json formátumban
Export kép fájlba
Réteg törlése, másolása



