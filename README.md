
# Mantis

A colorfully cutthroat card game of **RAINBOWS** and **REVENGE**.

## Gameplay 
<table>
  <tr>
    <td>
      <img src="https://i.ibb.co/SX0bg99k/main-menu.jpg" alt="main-menu" height = "250" width="500" />
    </td>
    <td>
      <img src="https://i.ibb.co/FLFCGFpW/player-selection.jpg" alt="player-selection" height = "250" width="500" />
    </td>
  </tr>
</table>

<div align="center">
<table>
   <tr>
    <td text-align: center>
      <img src="https://i.ibb.co/kCmdcp3/game-play.jpg" alt="game-play" height = "350" width="350" />
    </td>
  </tr>
</table>
</div>

## Description
A terminal-based recreation of the card game Mantis in C. This served as our final project for CCPROG2 (Programming with Structured Data Types).

## Requirements
- Operating System: Windows / Linux / macOS
- Compiler: GCC (or any C99-compliant compiler)

## How to Compile
```bash
gcc -Wall -std=c99 mp.c -o mantis.exe
```

## How to Run
```bash
./mantis    # Linux / macOS
mantis      # Windows
```

## Controls
| Key       | Action        |
|-----------|---------------|
| W / S     | Navigate up/down |
| A / D     | Navigate left/right |
| Enter     | Select option |

## How To Play?

There are only two rules: **Score** or **Steal**.

### Try to Score
- A player scores a point if any of the card in their tank has the same color as the drawn card.

### Try to Steal
- A player can steal cards from other players, if the opposing player's tank has a card that matches the drawing player's drawn card.

## Game Data File

### Required Files 
- `mantis.txt` - Master list containing all 84 cards
- `players.txt` - Contains all the saved player data
- `settings.txt` - Game configuration of Mantis

### Mantis File Format
```
<front color> | <back color 1><back color 2><back color 3> <point value><newline>
```
#### Example Mantis File Format
```
R | RGB 3
```

### Players File Format
```
<username>,<wins>,<score>
```

#### Example Player File Format
```
damon,10,250
```

### Settings File Format
```
<winning_points>\n
<shuffle_seed>
```

#### Example Settings File Format
```
50
67
```

## File Structure
```
CCPROG2-MP-MANTIS/
├── mp.c
├── player.c
├── game.c
├── game_display.c
├── leaderboard.c
├── settings.c
├── data.c
├── random.c
├── interface.c
├── game.c
├── defs.h
├── conio_alt.h
├── mantis.txt
├── players.txt
├── settings.txt
└── README.md
```

## Sample Run

**Player Count: 4**  
**Winning Points: 20**  
**Shuffle Seed: 67**  
``` 
P1 => [ R:3 | O:0 | Y:0 | G:0 | B:0 | I:0 | V:1 ] Score: 0  
P2 => [ R:1 | O:0 | Y:1 | G:1 | B:0 | I:0 | V:1 ] Score: 0  
P3 => [ R:0 | O:0 | Y:1 | G:2 | B:0 | I:0 | V:1 ] Score: 0  
P4 => [ R:1 | O:2 | Y:1 | G:0 | B:0 | I:0 | V:0 ] Score: 0 
Top Deck: OGR (68 left)

P1 tries to score

P1 => [ R:3 | O:1 | Y:0 | G:0 | B:0 | I:0 | V:1 ] Score: 0  
P2 => [ R:1 | O:0 | Y:1 | G:1 | B:0 | I:0 | V:1 ] Score: 0  
P3 => [ R:0 | O:0 | Y:1 | G:2 | B:0 | I:0 | V:1 ] Score: 0  
P4 => [ R:1 | O:2 | Y:1 | G:0 | B:0 | I:0 | V:0 ] Score: 0 
Top Deck: OYI (67 left)

P2 tries to score

P1 => [ R:3 | O:1 | Y:0 | G:0 | B:0 | I:0 | V:1 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:1 | B:0 | I:0 | V:1 ] Score: 0  
P3 => [ R:0 | O:0 | Y:1 | G:2 | B:0 | I:0 | V:1 ] Score: 0  
P4 => [ R:1 | O:2 | Y:1 | G:0 | B:0 | I:0 | V:0 ] Score: 0 
Top Deck: BYI (66 left)

P3 tries to score

P1 => [ R:3 | O:1 | Y:0 | G:0 | B:0 | I:0 | V:1 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:1 | B:0 | I:0 | V:1 ] Score: 0  
P3 => [ R:0 | O:0 | Y:1 | G:2 | B:1 | I:0 | V:1 ] Score: 0  
P4 => [ R:1 | O:2 | Y:1 | G:0 | B:0 | I:0 | V:0 ] Score: 0 
Top Deck: ROI (65 left)

P4 tries to score

P1 => [ R:3 | O:1 | Y:0 | G:0 | B:0 | I:0 | V:1 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:1 | B:0 | I:0 | V:1 ] Score: 0  
P3 => [ R:0 | O:0 | Y:1 | G:2 | B:1 | I:0 | V:1 ] Score: 0  
P4 => [ R:1 | O:0 | Y:1 | G:0 | B:0 | I:0 | V:0 ] Score: 3 
Top Deck: BIV (64 left)

P1 tries to steal from P3

P1 => [ R:3 | O:1 | Y:0 | G:0 | B:0 | I:0 | V:3 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:1 | B:0 | I:0 | V:1 ] Score: 0  
P3 => [ R:0 | O:0 | Y:1 | G:2 | B:1 | I:0 | V:0 ] Score: 0  
P4 => [ R:1 | O:0 | Y:1 | G:0 | B:0 | I:0 | V:0 ] Score: 3 
Top Deck: BYR (63 left)

P2 tries to steal from P3

P1 => [ R:3 | O:1 | Y:0 | G:0 | B:0 | I:0 | V:3 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:1 | B:2 | I:0 | V:1 ] Score: 0  
P3 => [ R:0 | O:0 | Y:1 | G:2 | B:0 | I:0 | V:0 ] Score: 0  
P4 => [ R:1 | O:0 | Y:1 | G:0 | B:0 | I:0 | V:0 ] Score: 3 
Top Deck: GYR (62 left)

P3 tries to score

P1 => [ R:3 | O:1 | Y:0 | G:0 | B:0 | I:0 | V:3 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:1 | B:2 | I:0 | V:1 ] Score: 0  
P3 => [ R:1 | O:0 | Y:1 | G:2 | B:0 | I:0 | V:0 ] Score: 0  
P4 => [ R:1 | O:0 | Y:1 | G:0 | B:0 | I:0 | V:0 ] Score: 3 
Top Deck: BYI (61 left)

P4 tries to score

P1 => [ R:3 | O:1 | Y:0 | G:0 | B:0 | I:0 | V:3 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:1 | B:2 | I:0 | V:1 ] Score: 0  
P3 => [ R:1 | O:0 | Y:1 | G:2 | B:0 | I:0 | V:0 ] Score: 0  
P4 => [ R:1 | O:0 | Y:1 | G:0 | B:0 | I:1 | V:0 ] Score: 3 
Top Deck: BYR (60 left)

P1 tries to score

P1 => [ R:3 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:3 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:1 | B:2 | I:0 | V:1 ] Score: 0  
P3 => [ R:1 | O:0 | Y:1 | G:2 | B:0 | I:0 | V:0 ] Score: 0  
P4 => [ R:1 | O:0 | Y:1 | G:0 | B:0 | I:1 | V:0 ] Score: 3 
Top Deck: GIY (59 left)

P2 tries to score

P1 => [ R:3 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:3 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:0 | B:2 | I:0 | V:1 ] Score: 5  
P3 => [ R:1 | O:0 | Y:1 | G:2 | B:0 | I:0 | V:0 ] Score: 0  
P4 => [ R:1 | O:0 | Y:1 | G:0 | B:0 | I:1 | V:0 ] Score: 3 
Top Deck: OVB (58 left)

P3 tries to score

P1 => [ R:3 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:3 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:0 | B:2 | I:0 | V:1 ] Score: 5  
P3 => [ R:1 | O:0 | Y:1 | G:2 | B:1 | I:0 | V:0 ] Score: 0  
P4 => [ R:1 | O:0 | Y:1 | G:0 | B:0 | I:1 | V:0 ] Score: 3 
Top Deck: VYR (57 left)

P4 tries to steal from P1

P1 => [ R:3 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:0 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:0 | B:2 | I:0 | V:1 ] Score: 5  
P3 => [ R:1 | O:0 | Y:1 | G:2 | B:1 | I:0 | V:0 ] Score: 0  
P4 => [ R:1 | O:0 | Y:1 | G:0 | B:0 | I:1 | V:4 ] Score: 3 
Top Deck: BGI (56 left)

P1 tries to score

P1 => [ R:3 | O:1 | Y:1 | G:1 | B:0 | I:0 | V:0 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:0 | B:2 | I:0 | V:1 ] Score: 5  
P3 => [ R:1 | O:0 | Y:1 | G:2 | B:1 | I:0 | V:0 ] Score: 0  
P4 => [ R:1 | O:0 | Y:1 | G:0 | B:0 | I:1 | V:4 ] Score: 3 
Top Deck: BYO (55 left)

P2 tries to score

P1 => [ R:3 | O:1 | Y:1 | G:1 | B:0 | I:0 | V:0 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:1 ] Score: 10  
P3 => [ R:1 | O:0 | Y:1 | G:2 | B:1 | I:0 | V:0 ] Score: 0  
P4 => [ R:1 | O:0 | Y:1 | G:0 | B:0 | I:1 | V:4 ] Score: 3 
Top Deck: GIY (54 left)

P3 tries to steal from P4

P1 => [ R:3 | O:1 | Y:1 | G:1 | B:0 | I:0 | V:0 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:1 ] Score: 10  
P3 => [ R:1 | O:0 | Y:1 | G:2 | B:1 | I:2 | V:0 ] Score: 0  
P4 => [ R:1 | O:0 | Y:1 | G:0 | B:0 | I:0 | V:4 ] Score: 3 
Top Deck: OGR (53 left)

P4 tries to score

P1 => [ R:3 | O:1 | Y:1 | G:1 | B:0 | I:0 | V:0 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:1 ] Score: 10  
P3 => [ R:1 | O:0 | Y:1 | G:2 | B:1 | I:2 | V:0 ] Score: 0  
P4 => [ R:0 | O:0 | Y:1 | G:0 | B:0 | I:0 | V:4 ] Score: 6 
Top Deck: OVB (52 left)

P1 tries to score

P1 => [ R:3 | O:1 | Y:1 | G:1 | B:0 | I:0 | V:1 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:1 ] Score: 10  
P3 => [ R:1 | O:0 | Y:1 | G:2 | B:1 | I:2 | V:0 ] Score: 0  
P4 => [ R:0 | O:0 | Y:1 | G:0 | B:0 | I:0 | V:4 ] Score: 6 
Top Deck: OBR (51 left)

P2 tries to score

P1 => [ R:3 | O:1 | Y:1 | G:1 | B:0 | I:0 | V:1 ] Score: 0  
P2 => [ R:1 | O:0 | Y:1 | G:0 | B:0 | I:0 | V:1 ] Score: 15  
P3 => [ R:1 | O:0 | Y:1 | G:2 | B:1 | I:2 | V:0 ] Score: 0  
P4 => [ R:0 | O:0 | Y:1 | G:0 | B:0 | I:0 | V:4 ] Score: 6 
Top Deck: IGO (50 left)

P3 tries to steal from P2

P1 => [ R:3 | O:1 | Y:1 | G:1 | B:0 | I:0 | V:1 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:1 ] Score: 15  
P3 => [ R:1 | O:0 | Y:1 | G:2 | B:1 | I:2 | V:0 ] Score: 0  
P4 => [ R:0 | O:0 | Y:1 | G:0 | B:0 | I:0 | V:4 ] Score: 6 
Top Deck: GOB (49 left)

P4 tries to score

P1 => [ R:3 | O:1 | Y:1 | G:1 | B:0 | I:0 | V:1 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:1 ] Score: 15  
P3 => [ R:1 | O:0 | Y:1 | G:2 | B:1 | I:2 | V:0 ] Score: 0  
P4 => [ R:0 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:4 ] Score: 6 
Top Deck: IGR (48 left)

P1 tries to steal from P2

P1 => [ R:3 | O:1 | Y:1 | G:1 | B:0 | I:0 | V:1 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:0 | B:0 | I:1 | V:1 ] Score: 15  
P3 => [ R:1 | O:0 | Y:1 | G:2 | B:1 | I:2 | V:0 ] Score: 0  
P4 => [ R:0 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:4 ] Score: 6 
Top Deck: BIV (47 left)

P2 tries to score

P1 => [ R:3 | O:1 | Y:1 | G:1 | B:0 | I:0 | V:1 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:1 ] Score: 19  
P3 => [ R:1 | O:0 | Y:1 | G:2 | B:1 | I:2 | V:0 ] Score: 0  
P4 => [ R:0 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:4 ] Score: 6 
Top Deck: OVB (46 left)

P3 tries to score

P1 => [ R:3 | O:1 | Y:1 | G:1 | B:0 | I:0 | V:1 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:1 ] Score: 19  
P3 => [ R:1 | O:1 | Y:1 | G:2 | B:1 | I:2 | V:0 ] Score: 0  
P4 => [ R:0 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:4 ] Score: 6 
Top Deck: VGB (45 left)

P4 tries to steal from P2

P1 => [ R:3 | O:1 | Y:1 | G:1 | B:0 | I:0 | V:1 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:0 | B:1 | I:0 | V:1 ] Score: 19  
P3 => [ R:1 | O:1 | Y:1 | G:2 | B:1 | I:2 | V:0 ] Score: 0  
P4 => [ R:0 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:4 ] Score: 6 
Top Deck: BGI (44 left)

P1 tries to score

P1 => [ R:3 | O:1 | Y:1 | G:1 | B:1 | I:0 | V:1 ] Score: 0  
P2 => [ R:1 | O:1 | Y:1 | G:0 | B:1 | I:0 | V:1 ] Score: 19  
P3 => [ R:1 | O:1 | Y:1 | G:2 | B:1 | I:2 | V:0 ] Score: 0  
P4 => [ R:0 | O:1 | Y:1 | G:0 | B:0 | I:0 | V:4 ] Score: 6 
Top Deck: BIV (43 left)

P2 tries to score

P2 WINS
P2: 23 pts
P4: 6 pts
P1: 0 pts
P3: 0 pts 
```
