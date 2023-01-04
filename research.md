# random bullshit i've found

## Asset types
the file starts off with a list of the asset types. starting at exactly hex 20, it starts off with the amount of asset types, and then a bunch of (length-prefaced) strings.

## Strings
so it seems like strings are *always* prefaced by their length, outside of the header sometimes (all i've found though) they're prefaced by two bytes, the latter being the length and the former being the length of the string plus the one byte before it.

this may set a precident that objects are prefaced by length, and the string object already has a length

## Headers
Every .core file starts off with `RTTIBin<1.58>` and this is corroborated with it being in a `strings` output of the decrypted ELF binary.

0xFFFF *MAY* be a header for something, in `lumps/characters.hgh_grenadier.core` the chunks near the bottom of the file start with `0xFFFF`, and then *visually* some of the same data as one another, which could indicate an asset type (or texture data)

most character models have a `0x80` after the file types, however this is not consistent, even between others of the same type, so it could either be the first filetype, or a total fluke, i'm  gonna chock it up to being the latter, however it could also indicate a potential count of something

## Textures
importing the entire .core archive into gimp as raw data gives results *visually* similar to a `BC1_UNORM_SRGB` dds file. Could be correlated however I haven't looked yet.

structure goes kinda like this

three bytes, `0x00`,`0x01`,`0x80`, followed by various data, including but not always: the size of the texture data (all mipmaps) in bytes, the x and y resolution, as well as the mipmap count (speculative)

after that, 80 bytes of `0x50`, then the texture data, finished up with 72 bytes of `0x50`

Textures vaguely appear to be in RGB565 format, with additional BCn compression on them, however just speculating that

more details in [the ImHex pattern file](https://github.com/headassbtw/Mantle/blob/main/ImHex_Patterns/rtti_texture.hexpat)

