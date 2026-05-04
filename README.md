<img width="1355" height="631" alt="image" src="https://github.com/user-attachments/assets/5b7f722b-ce0f-4f39-8f36-35967b3a06c2" /># Arduino Tic-Tac-Toe with AI & PvP Modes

A fully interactive Tic-Tac-Toe game built with **Arduino Uno**. This project features a smart AI opponent, a 2-player local mode, and a visual interface using an LCD display and LEDs.

## 🚀 Features
*   **Dual Modes:** Choose between Player vs Player (PvP) or Player vs Computer (PvC).
*   **Smart AI:** The computer can block your moves and try to win using a strategic logic.
*   **Visual Feedback:**
    *   **Blue LED:** Indicates Player X's turn or victory.
    *   **Red LED:** Indicates Player O's turn or victory.
*   **Real-time Display:** 16x2 LCD shows the game board status and the current winner.
*   **Keypad Control:** 3x3 Matrix Keypad for simple and intuitive move selection (Keys 1-9).

## 🛠️ Hardware Connection (Pin Mapping)
Based on the circuit design, here are the pin connections:

| Component | Arduino Pin |
| :--- | :--- |
| **LCD RS** | 12 |
| **LCD Enable** | 11 |
| **LCD D4-D7** | 5, 4, 3, 2 |
| **Keypad Rows** | 10, 9, 8 |
| **Keypad Cols** | 7, 6, 13 |
| **Blue LED (X)** | A1 |
| **Red LED (O)** | A0 |

## 📸 Circuit Diagram
![Circuit Diagram](<img width="1355" height="631" alt="image" src="https://github.com/user-attachments/assets/7731ca7b-0299-42f7-9065-8e87df60112f" />

) 
*(Note: Ensure your image file is named correctly or update the path above)*

## 🕹️ How to Play
1.  **Start:** Upon powering up, select your mode using the keypad.
2.  **Mode Select:** Press `1` for PvP or `2` for PvC.
3.  **Gameplay:** Press keys `1-9` to place your mark on the corresponding board cell.
4.  **Win/Draw:** The game will automatically detect a winner or a draw, flash the LEDs, and display the result on the LCD.
5.  **Restart:** Press any key after the game ends to go back to the main menu.

## 🔗 Live Simulation
You can test and run the project directly in your browser via Tinkercad:
👉 **[View Simulation on Tinkercad](https://www.tinkercad.com/things/dQEOr15xMka-tic-tac-toe)**

## 💻 Tech Stack
*   **Language:** C++ (Arduino Sketch)
*   **Platform:** Tinkercad / Arduino IDE
*   **Libraries:** `LiquidCrystal.h`, `Keypad.h`
