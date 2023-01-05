# random bullshit i've found

## Asset types
the file starts off with a list of the asset types. starting at exactly hex 20, it starts off with the amount of asset types, and then a bunch of (length-prefaced) strings.

there MAY be a section afterward listing how many of each asset type there is, the amount of bytes with the uint8 corresponding to the position in the list. doesn't work in a lot of larger files however in smaller ones it appears to be correct. the chunk of bytes looks like a gradient and stops short in larger files.

## Strings
so it seems like strings are *always* prefaced by their length, outside of the header sometimes (all i've found though) they're prefaced by two bytes, the latter being the length and the former being the length of the string plus the one byte before it.

this may set a precident that objects are prefaced by length, and the string object already has a length

sometimes there are string "chunks". most times they start with a uint8 of how many strings, but sometimes they start with a uint16

## Headers
Every .core file starts off with `RTTIBin<1.58>` followed by two bytes of `0x20`. The game specifically checks this in the file; brackets, `0x20`, and all. I find this odd

0xFFFF *MAY* be a header for something, in `lumps/characters.hgh_grenadier.core` the chunks near the bottom of the file start with `0xFFFF`, and then *visually* some of the same data as one another, which could indicate an asset type (or texture data)

most character models have a `0x80` after the file types, however this is not consistent, even between others of the same type, so it could either be the first filetype, or a total fluke, i'm  gonna chock it up to being the latter, however it could also indicate a potential count of something

## Textures
importing the entire .core archive into gimp as raw data gives results *visually* similar to a `BC1_UNORM_SRGB` dds file. Could be correlated however I haven't looked yet.

structure goes kinda like this

three bytes, varying content depending on the header type (and likely compression), followed by various data, including but not always: the size of the texture data (all mipmaps) in bytes, the x and y resolution, as well as the mipmap count (speculative)

after that, 80 bytes of `0x50`, then the texture data, finished up with 72 bytes of `0xEE`

this is not always the case, as some textures (like those found in `lumps/assets_description.loading.loadingpicture_1_loadingpicture_1.core`) have considerably modified headers, with no ending block of `0xEE` (however the `0x50` is retained)

Textures vaguely appear to be in RGB565 format, with additional BCn compression on them, however just speculating that

more details in [the ImHex pattern file](https://github.com/headassbtw/Mantle/blob/main/ImHex_Patterns/rtti_texture.hexpat)

