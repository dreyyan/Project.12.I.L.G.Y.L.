# I.L.G.Y.L.
_If Life Gives You Lemons: A Gamified Lemonade Business Tycoon Simulation System_

**I.L.G.Y.L. (If Life Gives You Lemons)** is a lighthearted, strategic C++ game that transforms a simple lemonade stand into a thriving beverage empire. Built with a Text User Interface (TUI) and enhanced by SFML for audio and graphics, players manage resources, upgrade their stand, and navigate challenges to maximize profits. This tycoon simulation blends entertainment with strategic decision-making, teaching resource management concepts in a fun, engaging way.

The primary purpose of I.L.G.Y.L. is to provide an interactive gaming experience that appeals to casual players and strategists alike, while serving as an educational tool for learning C++ programming, TUI design, and game development.

## FEATURES
✅ **Resource Management** – Manage finances, lemons, and production to grow your lemonade business.  
✅ **Strategic Upgrades** – Upgrade your stand to increase efficiency and profits.  
✅ **Interactive TUI** – Navigate using intuitive keyboard controls with a character-based UI.  
✅ **Cutscenes & Savefiles** – Enjoy narrative-driven cutscenes and save progress for continued play.  
✅ **Exciting Gameplay** – Face dynamic challenges to test your business acumen.  

## FUTURE IMPLEMENTATIONS
🚀 **Expanded Gameplay** – Add new business ventures, like expanding to other beverages or locations.  
🚀 **Enhanced Graphics** – Incorporate more SFML graphics for richer visuals in the TUI.  
🚀 **Multiplayer Mode** – Compete or collaborate with other players in business challenges.  
🚀 **Difficulty Levels** – Introduce adjustable difficulty for varied player skill levels.  

## UPDATES
🔄 Core gameplay with resource management and upgrades implemented.  
🔄 SFML audio and graphics integration for immersive cutscenes.  
🔄 Optimized TUI for 72x30 console size.  

## PROJECT DETAILS
📌 **Author:** dreyyan  
📌 **Started:** 2025-04-07  
📌 **Finished:**  

## TECH STACK
🛠️ **Language:** C++  
🛠️ **Libraries:** SFML (Audio, Graphics, Window, System)  

## INSTALLATION
### Prerequisites
- C++ compiler (e.g., g++ with MinGW for Windows)
- SFML library installed (version compatible with your system)
- Create a development environment:
  - Windows: Install MinGW and SFML via package manager or manual download.
  - Linux/macOS: Install SFML via package manager (e.g., `sudo apt install libsfml-dev` on Ubuntu).

### Install Dependencies
Download and configure SFML:
- Windows: Follow [SFML setup guide](https://www.sfml-dev.org/tutorials/2.6/start-vc.php).
- Linux: Install via `sudo apt install libsfml-dev` (or equivalent for your distro).
- macOS: Install via `brew install sfml`.

### Compilation
Compile the project using the provided command:
```
g++ -o test main.cpp Utility.cpp GUI.cpp prep.cpp Scenes.cpp Station.cpp -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
```

### Verify Installation
Ensure SFML is linked correctly by running the compiled executable. Check for errors related to missing SFML libraries.

## USAGE
### Running the Application
Set the command prompt size to 72x30 for optimal display:
- On Windows: `mode con: cols=72 lines=30`
- On Unix/macOS: Adjust terminal size to 72 columns by 30 rows.

Run the executable in an external console:
- **CMD**:
  ```
  Start-Process "cmd.exe" -ArgumentList "/k", "C:\Users\dreyyan\Downloads\code\Projects\Project.12.ILGYL\test.exe"
  ```
- **PowerShell**:
  ```
  Start-Process "powershell.exe" -ArgumentList "-NoExit", "-Command", "C:\Users\dreyyan\Downloads\code\Projects\Project.12.ILGYL\test.exe"
  ```

### Example Workflow
1. **Launch the Game**: Run `test.exe` in the configured console.
2. **Navigate TUI**: Use navigation keys to make business decisions, manage resources, and upgrade your stand.
3. **Experience Cutscenes**: Enjoy narrative-driven interludes that enhance the storyline.
4. **Save Progress**: Save your game to continue your tycoon journey later.

### Configuration
- Ensure the console size is set to 72x30 for proper display.
- Adjust SFML audio or graphics settings via code or configuration files (if implemented).

## DEBUGGING
For issues, check console output for errors related to SFML or game logic. Run with:
```
./test  # Linux/macOS
test.exe  # Windows
```
Report issues via GitHub Issues for detailed troubleshooting.

## PROJECT STRUCTURE
- `main.cpp`: Entry point for the application.
- `Utility.cpp`: Helper functions for game logic and TUI rendering.
- `GUI.cpp`: TUI rendering and interface management.
- `prep.cpp`: Game setup and initialization logic.
- `Scenes.cpp`: Cutscene and narrative management.
- `Station.cpp`: Lemonade stand mechanics and resource management.

## CONTRIBUTING
Contributions are welcome! Fork the repo, make changes, and submit a pull request:
1. Create a feature branch: `git checkout -b feature/new-feature`
2. Commit changes: `git commit -m "Add new feature"`
3. Push: `git push origin feature/new-feature`
4. Open a pull request

Report issues or suggest features via GitHub Issues.

## LICENSE
This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.