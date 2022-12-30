# random bullshit i've found

## Strings
so it seems like strings are *always* prefaced by their length, outside of the header sometimes (all i've found though) they're prefaced by two bytes, the latter being the length and the former being the length of the string plus the one byte before it.

this may set a precident that objects are prefaced by length, and the string object already has a length