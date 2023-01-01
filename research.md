# random bullshit i've found

## Asset types
the file starts off with a list of the asset types. starting at exactly hex 20, it starts off with the amount of asset types, and then a bunch of (length-prefaced) strings.

## Strings
so it seems like strings are *always* prefaced by their length, outside of the header sometimes (all i've found though) they're prefaced by two bytes, the latter being the length and the former being the length of the string plus the one byte before it.

this may set a precident that objects are prefaced by length, and the string object already has a length

## Headers
Every .core file starts off with `RTTIBin<1.58>` and this is corroborated with it being in a `strings` output of the decrypted ELF binary.

0xFFFF *MAY* be a header for something, in `lumps/characters.hgh_grenadier.core` the chunks near the bottom of the file start with `0xFFFF`, and then *visually* some of the same data as one another, which could indicate an asset type (or texture data)

## Textures
importing the entire .core archive into gimp as raw data gives results *visually* similar to a `BC1_UNORM_SRGB` dds file. Could be correlated however I haven't looked yet.

Texture headers seem to end in 80 bytes of `0x50`, not sure why but at least it's consistent.

Textures vaguely appear to be in R6G5B6 format, with additional BCn compression on them, however just speculating that