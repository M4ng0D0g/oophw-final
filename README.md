# 2048 Variant - Combo & Dimension Mechanism

A customized version of 2048 with combo, zero tile, and dimension mechanics.

## Features

- Player can move the tiles using `W`, `A`, `S`, `D` keys.
- When two identical tiles collide, they merge into one.

### Combo System

- Introduced **combo system** to create more strategic merges:
  - The first merge applies addition.
  - If a newly merged tile merges again in the next move, it uses multiplication.
  - If two multiplication tiles merge, they perform exponentiation.
  - Special case: `0^0` creates a **Dimension Tile**.

### Zero Tile Mechanism

- **Zero Tile (`0`)** is introduced as an extra mechanic:
  - During normal merges, zero tiles can only reduce the number of tiles but cannot be completely eliminated.
  - They act as obstacles, limiting merge flexibility and increasing board complexity.

### Dimension System

- **Dimension Tiles** provide unique effects depending on the merge direction:
  - Horizontal merge: flips the sign (positive/negative).
  - Vertical merge: switches between real and imaginary types.
  - Certain dimension merges may shift the board state into other dimensions, creating complex and challenging scenarios.

## Version

- **v1.0.0**:
  - Supports four dimensions.
  - Includes zero tile and dimension tile mechanics.
  - Some merges may generate undefined tiles under certain extreme conditions.

## Technical Notes

- The tile merging and collision logic is handled using a **double pointer algorithm** to efficiently process merges and state transitions.

## Controls

- `W` / `A` / `S` / `D`: Move tiles up, left, down, and right.

## Author

**M4ng0D0g**

## Disclaimer

This is a personal project implementing advanced merging mechanics inspired by 2048.

---

