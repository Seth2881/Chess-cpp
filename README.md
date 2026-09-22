# C++ Chess Core & Bitboard Engine

A modern C++ chess engine project focused on low-level board state representation, bitboard attack generation, and Object-Oriented piece management. Built to sharpen C++ system programming and algorithmic problem-solving skills, with future goals of engine integration and visual UI rendering.

---

## 🌟 Key Features

* **Bitboard Attack Generation:** Uses 64-bit integer (`uint64_t`) bitmasks and bitwise operations (`<<`, `>>`, `&`, `|`, `^`) to generate attack maps for Rooks, Bishops, Queens, Knights, Kings, and Pawns.
* **FEN (Forsyth–Edwards Notation) Parser:** Parses standard FEN strings into active game states (piece placement, active color, castling rights, en passant targets, halfmove clock, fullmove number).
* **Object-Oriented Architecture:** Base polymorphic `Piece` class leveraging `std::unique_ptr` dynamic dispatch alongside modern C++ features (`std::views::split`, `std::ranges::to`).
* **Bitwise State Encoding:** Encodes piece types and colors efficiently using 5-bit flags (e.g., `0b01000` for White, `0b10000` for Black, `0b001` for Pawn).

---

## 📂 Project Structure

```text
Chess-cpp/
├── chessboard/
│   ├── img_board/               # UI textures for board representation
│   │   ├── Dark_green_square.jpg
│   │   ├── Light_gray_square.jpg
│   │   └── select_square.webp
│   └── board.cpp                # Board class, FEN parsing, and game initialization
├── pieces/
│   ├── Chess_pieces_sprite.png  # Piece sprite sheet
│   ├── bitboards.cpp            # Bitwise calculations & attack pattern functions
│   └── pieces.cpp               # Polymorphic Piece class & individual piece implementations
├── main.cpp                     # Entry point
└── README.md                    # Project documentation
