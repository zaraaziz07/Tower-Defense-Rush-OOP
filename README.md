# Tower Defense Rush 🎮

A 2D strategy-based Tower Defense game developed in **C++** using the **SFML (Simple and Fast Multimedia Library)** framework.  
Defend your base against waves of enemies by placing different types of towers strategically across the battlefield.

---

# 📸 Game Preview

<!-- Add your game screenshot here -->
(assets/screenshots.png)

---

# 🚀 Features

✅ Multiple enemy types with unique abilities  
✅ Multiple tower types with different attack styles  
✅ Wave-based enemy spawning system  
✅ Dynamic waypoint enemy movement  
✅ Tower placement validation system  
✅ Coin & life management system  
✅ Health bars for enemies and towers  
✅ Sound effects and animated screens  
✅ Fullscreen SFML gameplay  
✅ Different enemy speeds, HP, and mechanics  
✅ Strategic tower defense gameplay  

---

# 🛠️ Technologies Used

- **C++**
- **SFML Graphics**
- **SFML Audio**

---

# 📂 Project Structure

```bash
├── assets/
├── Entity.h
├── Enemy.h
├── Tower.h
├── Variables.h
├── main.cpp
└── README.md
```

---

# 🎮 Gameplay

- Place towers strategically to defend the path.
- Enemies move through predefined waypoints.
- Destroy enemies to earn coins.
- Buy additional lives using coins.
- Survive all waves to win the game.

---

# 👾 Enemy Types

---

## 🟢 Basic Enemy

- **HP:** `100`
- **Speed:** `1.0`
- **Reward:** `10 Coins`

### Features
- Balanced enemy
- Follows waypoint path
- Standard movement and health

```diff
+ Beginner enemy with balanced stats
```

---

## 🔵 Fast Enemy

- **HP:** `50`
- **Speed:** `1.5`
- **Reward:** `20 Coins`

### Features
- Very fast movement
- Lower health
- Harder to hit with slow-firing towers

```diff
+ High speed enemy
- Low HP
```

---

## 🟤 Tank Enemy

- **HP:** `350`
- **Speed:** `0.7`
- **Reward:** `50 Coins`

### Features
- Extremely high health
- Slow movement
- Designed to absorb heavy damage

```diff
+ Massive HP
- Very slow
```

---

## 🔷 Flying Enemy

- **HP:** `60`
- **Speed:** `1.8`
- **Reward:** `35 Coins`

### Features
- Ignores the waypoint path
- Flies directly to the exit
- Faster than most enemies

```diff
+ Air enemy
+ Direct movement
```

---

## 🟣 Omega Enemy (Boss)

- **HP:** `500`
- **Speed:** `0.5 → 3.2`
- **Reward:** `100 Coins`

### Features
- Boss enemy
- Speed increases as HP decreases
- Very dangerous in late stages

### Omega Evolution

| HP Remaining | Speed |
|---|---|
| 100% - 75% | 0.5 |
| 75% - 50% | 1.5 |
| 50% - 25% | 2.2 |
| Below 25% | 3.2 |

```diff
+ Boss enemy
+ Rage mode mechanic
+ Dynamic speed scaling
```

---

# 🏰 Tower Types

---

## ⚫ Cannon Tower

- **Damage:** `60`
- **Range:** `100`
- **Fire Rate:** `2.0s`
- **Tower HP:** `200`

### Features
- Balanced damage tower
- Medium range
- Reliable against all enemy types

```diff
+ Strong balanced tower
```

---

## 🔵 Sniper Tower

- **Damage:** `65`
- **Range:** `150`
- **Fire Rate:** `3.0s`
- **Tower HP:** `200`

### Features
- Very long range
- High damage shots
- Excellent for tank enemies

```diff
+ Longest range
+ High damage
- Slow fire rate
```

---

## 🟡 Machine Gun Tower

- **Damage:** `8`
- **Range:** `125`
- **Fire Rate:** `0.2s`
- **Tower HP:** `200`

### Features
- Extremely fast attacks
- Best against fast enemies
- Continuous rapid fire

```diff
+ Very high attack speed
- Low single-shot damage
```

---

## 🔷 Slow Tower

- **Range:** `140`
- **Slow Effect:** `50% speed reduction`
- **Tower HP:** `200`

### Features
- Slows enemies inside range
- Supports nearby towers
- Constant area control

```diff
+ Crowd control tower
+ Support tower
```

---

## 🔥 Bomb Tower

- **Damage:** `30`
- **Range:** `140`
- **Explosion Radius:** `70`
- **Chain Explosions:** `3`
- **Fire Rate:** `2.5s`
- **Tower HP:** `200`

### Features
- Area damage attacks
- Chain explosion mechanic
- Damages multiple enemies together

```diff
+ Splash damage
+ Chain explosion attacks
```

---

# 🌊 Wave System

The game contains **5 waves** of increasing difficulty.

| Wave | Enemies |
|---|---|
| Wave 1 | Basic Enemies |
| Wave 2 | Basic + Fast |
| Wave 3 | Tank Enemies Introduced |
| Wave 4 | Flying Enemies Introduced |
| Wave 5 | Omega Boss Appears |

---

# ⚙️ Installation

## 1️⃣ Clone Repository

```bash
git clone https://github.com/your-username/tower-defense-rush.git
```

---

## 2️⃣ Install SFML

Download SFML:

https://www.sfml-dev.org/download.php

---

## 3️⃣ Build Project

Compile using:
- Visual Studio
- CodeBlocks
- CLion

Configure:
- SFML Include Path
- SFML Library Path

---

# 🎮 Controls

| Action | Input |
|---|---|
| Place Tower | Left Mouse Click |
| Exit Game | ESC |

---

# 🧠 OOP Concepts Used

✅ Inheritance  
✅ Polymorphism  
✅ Abstraction  
✅ Encapsulation  

### Examples

- `Enemy` base class with derived enemy classes
- `Tower` base class with specialized tower behaviors
- Virtual functions for rendering, attacking, and movement

---

# 🔥 Special Mechanics

## Omega Rage System
Omega enemy becomes faster as its health decreases.

## Slow Tower Effect
Enemies inside the slow tower radius move at reduced speed.

## Bomb Chain Explosion
Bomb tower explosions spread between nearby enemies.

---

# 📌 Future Improvements

- Main Menu
- Tower Upgrades
- Multiple Maps
- Save System
- Background Music
- Better Visual Effects
- More Boss Enemies
- Multiplayer Mode

---

# 👨‍💻 Developer

Developed by **Zara Aziz**

---

# 📜 License

This project is for educational purposes.
