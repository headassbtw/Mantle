# random bullshit i've found

## Asset types
the file starts off with a list of the asset types. starting at exactly hex 20, it starts off with the amount of asset types, and then a bunch of (length-prefaced) strings.

## Strings
so it seems like strings are *always* prefaced by their length, outside of the header sometimes (all i've found though) they're prefaced by two bytes, the latter being the length and the former being the length of the string plus the one byte before it.

this may set a precident that objects are prefaced by length, and the string object already has a length

## Headers
0xFFFF *MAY* be a header for something, in `lumps/characters.hgh_grenadier.core` the chunks near the bottom of the file start with `0xFFFF`, and then *visually* some of the same data as one another, which could indicate an asset type

## Textures
importing the entire .core archive into gimp as raw data gives results *visually* similar to a `BC1_UNORM_SRGB` dds file. Could be correlated however I haven't looked yet.