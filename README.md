# Qt Arkanoid Game - interview training

A step-by-step project to learn Qt by building the classic Arkanoid/Breakout game. Each step introduces new Qt concepts while building towards a complete game.

## Project Structure

```text
TODO: tree output here
```

## core ideas to learn

- [ ] signals and slots
- [ ] event loop and qobject
- [ ] model/view
- [ ] threads
- [ ] build system (cmake)
- [ ] networking
- [ ] qt quick structure
- [ ] game loop with timer
- [ ] input via keys
- [ ] collision math and simple reflection
- [ ] data driven UI (hud bound to score/lives)
- [ ] reusable components (turn bricks/paddle into qml components later)
- [ ] optional c++ hooks (expose a GameController to qml)
- [ ] sound effects
- [ ] high-score saving
- [ ] json level loader in c++
- [ ] tiny QAbstractListModel for a high-score table

## step 0 apps

- [] minimal widgets app + signals/slots
- [] qml "hello" + integrate c++
- [] worker-object with qthread

## step 1 to n

- [ ] step 1 - Environment Setup & Hello Qt
  - [ ] Install Qt6 and CMake
  - [ ] Create `CMakeLists.txt` with Qt6 Widgets
  - [ ] Write minimal `main.cpp` with QApplication
  - [ ] Create empty window that shows and closes
  - [ ] Test build system works
- [ ] step 2 - Custom Game Window Class
  - [ ] Create `Game` class inheriting from `QMainWindow`
  - [ ] Set fixed window size (800x600)
  - [ ] Set window title "Qt Arkanoid"
  - [ ] Disable window resizing
  - [ ] Center window on screen
- [ ] step 3 - Basic Menu System
  - [ ] Add menu bar with "Game" and "Help" menus
  - [ ] Create "New Game", "Pause", "Exit" actions
  - [ ] Connect "Exit" to `QApplication::quit()` using signals/slots
  - [ ] Add "About Qt" dialog in Help menu
  - [ ] Test all menu interactions work
- [ ] step 4 - Custom Paint Widget (Game Scene)
  - [ ] Create `GameScene` class inheriting from `QWidget`
  - [ ] Override `paintEvent()` to draw game background
  - [ ] Draw a simple grid or background pattern
  - [ ] Set this widget as central widget in Game window
  - [ ] Experiment with different QPainter drawing commands
- [ ] step 5 - Game Coordinate System
  - [ ] Define game world coordinates (e.g., 0-800 x 0-600)
  - [ ] Create helper functions to convert between screen/game coordinates
  - [ ] Draw coordinate system guides (origin, axes)
  - [ ] Add game boundaries visualization
  - [ ] Test coordinate system with mouse clicks (show coordinates)
- [ ] step 6 - Paddle Object
  - [ ] Create `Paddle` class with position, size, and speed
  - [ ] Draw paddle as rectangle in GameScene
  - [ ] Implement keyboard input handling (A/D or Arrow keys)
  - [ ] Add smooth paddle movement with boundaries
  - [ ] Test paddle stays within screen bounds
- [ ] step 7 - Ball Object & Basic Physics
  - [ ] Create `Ball` class with position, velocity, and radius
  - [ ] Implement ball drawing (circle)
  - [ ] Add ball movement with velocity
  - [ ] Implement ball-boundary collision (wall bouncing)
  - [ ] Test ball bounces correctly off walls
- [ ] step 8 - Ball-Paddle Collision
  - [ ] Implement ball-paddle collision detection
  - [ ] Add ball reflection based on paddle hit position
  - [ ] Add "English" effect (ball angle changes based on where it hits paddle)
  - [ ] Test various paddle-ball interactions
  - [ ] Handle edge cases (ball hitting paddle corners)
- [ ] step 9 - Brick System
  - [ ] Create `Brick` class with position, size, and state
  - [ ] Create grid of bricks at top of screen
  - [ ] Draw all bricks with different colors/patterns
  - [ ] Implement ball-brick collision detection
  - [ ] Remove bricks when hit, update score
  - [ ] Test brick destruction and collision
- [ ] step 10 - Game Loop & Timing
  - [ ] Implement game loop using `QTimer`
  - [ ] Set consistent frame rate (60 FPS)
  - [ ] Add delta time for frame-independent movement
  - [ ] Implement pause/resume functionality
  - [ ] Add simple FPS counter for debugging
- [ ] step 11 - Game States & Logic
  - [ ] Create `GameState` enum (Menu, Playing, Paused, GameOver, Victory)
  - [ ] Implement state transitions and state-specific rendering
  - [ ] Add "Game Over" when ball falls below paddle
  - [ ] Add "Victory" when all bricks are destroyed
  - [ ] Add restart functionality
- [ ] step 12 - Score & UI Overlay
  - [ ] Add score tracking system
  - [ ] Draw score, lives, level on screen
  - [ ] Create nice UI overlay (semi-transparent panels)
  - [ ] Add custom fonts for game text
  - [ ] Test UI doesn't interfere with gameplay
- [ ] step 13 - Multiple Lives System
  - [ ] Add lives counter (start with 3 lives)
  - [ ] Reset ball/paddle position when life lost
  - [ ] Add brief invulnerability period after losing life
  - [ ] Visual feedback for life loss
  - [ ] Game over when no lives remaining
- [ ] step 14 - Power-ups System
  - [ ] Create `PowerUp` base class
  - [ ] Implement different power-up types (bigger paddle, multi-ball, etc.)
  - [ ] Random power-up drops from destroyed bricks
  - [ ] Power-up collection and effects
  - [ ] Visual effects for active power-ups
- [ ] step 15 - Sound System
  - [ ] Create `SoundManager` class
  - [ ] Add sound effects (ball hit, brick break, power-up, etc.)
  - [ ] Implement background music
  - [ ] Add volume controls
  - [ ] Efficient audio resource management
- [ ] step 16 - Visual Effects & Animations
  - [ ] Add particle effects for brick destruction
  - [ ] Smooth animations for power-up effects
  - [ ] Ball trail effect
  - [ ] Screen shake for big impacts
  - [ ] Brick destruction animations
- [ ] step 17 - Settings & Configuration
  - [ ] Create settings dialog for controls, audio, graphics
  - [ ] Save/load settings using `QSettings`
  - [ ] Implement high score system with persistent storage
  - [ ] Add level editor (bonus!)
  - [ ] Customizable controls
- [ ] step 18 - Multiple Levels
  - [ ] Design level data format (JSON or custom)
  - [ ] Create multiple brick layouts
  - [ ] Progressive difficulty (ball speed, brick strength)
  - [ ] Level transition animations
  - [ ] Save game progress
- [ ] step 19 - Resource Management & Assets
  - [ ] Create `resources.qrc` file for all game assets
  - [ ] Optimize image formats and sizes
  - [ ] Implement asset loading error handling
  - [ ] Create game icon and application metadata
  - [ ] Test resource loading
- [ ] step 20 - Performance Optimization
  - [ ] Profile game performance (identify bottlenecks)
  - [ ] Optimize rendering (reduce unnecessary redraws)
  - [ ] Optimize collision detection algorithms
  - [ ] Memory usage optimization
  - [ ] Add debug/performance overlay
- [ ] step 21 - Cross-Platform Testing & Deployment
  - [ ] Test on different operating systems
  - [ ] Create application packaging (AppImage, installer)
  - [ ] Handle platform-specific issues
  - [ ] Create user documentation
  - [ ] Prepare for distribution

## documentation to read :D

1. **Before steps 1-3:** Qt Documentation on QApplication and basic widgets
2. **Before steps 4-5:** QPainter documentation and examples
3. **Before steps 6-8:** Qt event system and input handling
4. **Before steps 9-11:** QTimer and animation classes
5. **Before steps 12-14:** Qt resource system and QSettings
6. **Before steps 15-18:** Qt Multimedia and animation framework
7. **Before steps 19-21:** Qt deployment documentation

## future improvements

- [ ] Add networking for multiplayer
- [ ] Port to Qt Quick/QML for modern UI
- [ ] Add level editor with drag-and-drop
- [ ] Implement different ball types with special properties
- [ ] Add achievements system
- [ ] Create replay system
- [ ] Add AI paddle opponent
