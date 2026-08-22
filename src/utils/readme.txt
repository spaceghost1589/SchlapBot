sc2utils (Utilities)

sc2utils contains general-purpose, low-level helper tools that are largely game-agnostic.

What goes here:
- Platform-Specific Wrappers
- Basic Math Functions
- Geometry Primitives (vectors, points),
- String Manipulation
- Logging Helpers.

Characteristics:
- Zero or minimal dependency on StarCraft II game logic.
- A function in sc2utils shouldn't care whether it's dealing with a Zerling or a chess piece;
    it just performs a pure utility task (e.g., calculating distance between two coordinates or pausing execution).