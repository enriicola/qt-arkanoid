# Qt Arkanoid Game - interview training

A step-by-step project to learn Qt by building the classic Arkanoid/Breakout game. Each step introduces new Qt concepts while building towards a complete game.

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

- [x] 0.1 hello world + cmake + qt6
- [x] 0.2 minimal widgets app + signals/slots
- [x] 0.3 qml "hello" + integrate c++ (created, may need Qt modules)
- [x] 0.4 worker-object with qthread

## step 1 to n

- [x] step 1 - Environment Setup & Hello Qt
  - [x] 1.1 - Install Qt6 and CMake
  - [x] 1.2 - Create `CMakeLists.txt` with Qt6 Widgets
  - [x] 1.3 - Write minimal `main.cpp` with QApplication
  - [x] 1.4 - Create empty window that shows and closes
  - [x] 1.5 - Test build system works
- [x] step 2 - Custom Game Window Class
  - [x] 2.1 - Create `Game` class inheriting from `QMainWindow`
  - [x] 2.2 - Set fixed window size (800x600)
  - [x] 2.3 - Set window title "Qt Arkanoid"
  - [x] 2.4 - Disable window resizing
  - [x] 2.5 - Center window on screen
- [x] step 3 - Basic Menu System
  - [x] 3.1 - Add menu bar with "Game" and "Help" menus
  - [x] 3.2 - Create "New Game", "Pause", "Exit" actions
  - [x] 3.3 - Connect "Exit" to `QApplication::quit()` using signals/slots
  - [x] 3.4 - Add "About Qt" dialog in Help menu
  - [x] 3.5 - Test all menu interactions work
- [x] step 4 - Custom Paint Widget (Game Scene)
  - [x] 4.1 - Create `GameScene` class inheriting from `QWidget`
  - [x] 4.2 - Override `paintEvent()` to draw game background
  - [x] 4.3 - Draw a simple grid or background pattern
  - [x] 4.4 - Set this widget as central widget in Game window
  - [x] 4.5 - Experiment with different QPainter drawing commands
- [x] step 5 - Game Coordinate System
  - [x] 5.1 - Define game world coordinates (e.g., 0-800 x 0-600)
  - [x] 5.2 - Create helper functions to convert between screen/game coordinates
  - [x] 5.3 - Draw coordinate system guides (origin, axes)
  - [x] 5.4 - Add game boundaries visualization
  - [x] 5.5 - Test coordinate system with mouse clicks (show coordinates)
- [x] step 6 - Paddle Object
  - [x] 6.1 - Create `Paddle` class with position, size, and speed
  - [x] 6.2 - Draw paddle as rectangle in GameScene
  - [x] 6.3 - Implement keyboard input handling (A/D or Arrow keys)
  - [x] 6.4 - Add smooth paddle movement with boundaries
  - [x] 6.5 - Test paddle stays within screen bounds
- [x] step 7 - Ball Object & Basic Physics
  - [x] 7.1 - Create `Ball` class with position, velocity, and radius
  - [x] 7.2 - Implement ball drawing (circle)
  - [x] 7.3 - Add ball movement with velocity
  - [x] 7.4 - Implement ball-boundary collision (wall bouncing)
  - [x] 7.5 - Test ball bounces correctly off walls
- [x] step 8 - Ball-Paddle Collision
  - [x] 8.1 - Implement ball-paddle collision detection
  - [x] 8.2 - Add ball reflection based on paddle hit position
  - [x] 8.3 - Add "English" effect (ball angle changes based on where it hits paddle)
  - [x] 8.4 - Test various paddle-ball interactions
  - [x] 8.5 - Handle edge cases (ball hitting paddle corners)
- [x] step 9 - Brick System
  - [x] 9.1 - Create `Brick` class with position, size, and state
  - [x] 9.2 - Create grid of bricks at top of screen
  - [x] 9.3 - Draw all bricks with different colors/patterns
  - [x] 9.4 - Implement ball-brick collision detection
  - [x] 9.5 - Remove bricks when hit, update score
  - [x] 9.6 - Test brick destruction and collision
- [x] step 10 - Game Loop & Timing
  - [x] 10.1 - Implement game loop using `QTimer`
  - [x] 10.2 - Set consistent frame rate (60 FPS)
  - [x] 10.3 - Add delta time for frame-independent movement
  - [x] 10.4 - Implement pause/resume functionality
  - [x] 10.5 - Add simple FPS counter for debugging
- [x] step 11 - Game States & Logic
  - [x] 11.1 - Create `GameState` enum (Menu, Playing, Paused, GameOver, Victory)
  - [x] 11.2 - Implement state transitions and state-specific rendering
  - [x] 11.3 - Add "Game Over" when ball falls below paddle
  - [x] 11.4 - Add "Victory" when all bricks are destroyed
  - [x] 11.5 - Add restart functionality
- [x] step 12 - Score & UI Overlay
  - [x] 12.1 - Add score tracking system
  - [x] 12.2 - Draw score, lives, level on screen
  - [x] 12.3 - Create nice UI overlay (semi-transparent panels)
  - [x] 12.4 - Add custom fonts for game text
  - [x] 12.5 - Test UI doesn't interfere with gameplay
- [ ] step 13 - Multiple Lives System
  - [ ] 13.1 - Add lives counter (start with 3 lives)
  - [ ] 13.2 - Reset ball/paddle position when life lost
  - [ ] 13.3 - Add brief invulnerability period after losing life
  - [ ] 13.4 - Visual feedback for life loss
  - [ ] 13.5 - Game over when no lives remaining
- [ ] step 14 - Power-ups System
  - [ ] 14.1 - Create `PowerUp` base class
  - [ ] 14.2 - Implement different power-up types (bigger paddle, multi-ball, etc.)
  - [ ] 14.3 - Random power-up drops from destroyed bricks
  - [ ] 14.4 - Power-up collection and effects
  - [ ] 14.5 - Visual effects for active power-ups
- [ ] step 15 - Sound System
  - [ ] 15.1 - Create `SoundManager` class
  - [ ] 15.2 - Add sound effects (ball hit, brick break, power-up, etc.)
  - [ ] 15.3 - Implement background music
  - [ ] 15.4 - Add volume controls
  - [ ] 15.5 - Efficient audio resource management
- [ ] step 16 - Visual Effects & Animations
  - [ ] 16.1 - Add particle effects for brick destruction
  - [ ] 16.2 - Smooth animations for power-up effects
  - [ ] 16.3 - Ball trail effect
  - [ ] 16.4 - Screen shake for big impacts
  - [ ] 16.5 - Brick destruction animations
- [ ] step 17 - Settings & Configuration
  - [ ] 17.1 - Create settings dialog for controls, audio, graphics
  - [ ] 17.2 - Save/load settings using `QSettings`
  - [ ] 17.3 - Implement high score system with persistent storage
  - [ ] 17.4 - Add level editor (bonus!)
  - [ ] 17.5 - Customizable controls
- [ ] step 18 - Multiple Levels
  - [ ] 18.1 - Design level data format (JSON or custom)
  - [ ] 18.2 - Create multiple brick layouts
  - [ ] 18.3 - Progressive difficulty (ball speed, brick strength)
  - [ ] 18.4 - Level transition animations
  - [ ] 18.5 - Save game progress
- [ ] step 19 - Resource Management & Assets
  - [ ] 19.1 - Create `resources.qrc` file for all game assets
  - [ ] 19.2 - Optimize image formats and sizes
  - [ ] 19.3 - Implement asset loading error handling
  - [ ] 19.4 - Create game icon and application metadata
  - [ ] 19.5 - Test resource loading
- [ ] step 20 - Performance Optimization
  - [ ] 20.1 - Profile game performance (identify bottlenecks)
  - [ ] 20.2 - Optimize rendering (reduce unnecessary redraws)
  - [ ] 20.3 - Optimize collision detection algorithms
  - [ ] 20.4 - Memory usage optimization
  - [ ] 20.5 - Add debug/performance overlay
- [ ] step 21 - Cross-Platform Testing & Deployment
  - [ ] 21.1 - Test on different operating systems
  - [ ] 21.2 - Create application packaging (AppImage, installer)
  - [ ] 21.3 - Handle platform-specific issues
  - [ ] 21.4 - Create user documentation
  - [ ] 21.5 - Prepare for distribution

## documentation to read :D

- **Before steps 1-3:** Qt Documentation on QApplication and basic widgets
- **Before steps 4-5:** QPainter documentation and examples
- **Before steps 6-8:** Qt event system and input handling
- **Before steps 9-11:** QTimer and animation classes
- **Before steps 12-14:** Qt resource system and QSettings
- **Before steps 15-18:** Qt Multimedia and animation framework
- **Before steps 19-21:** Qt deployment documentation

## future improvements

- [ ] Add networking for multiplayer
- [ ] Port to Qt Quick/QML for modern UI
- [ ] Add level editor with drag-and-drop
- [ ] Implement different ball types with special properties
- [ ] Add achievements system
- [ ] Create replay system
- [ ] Add AI paddle opponent
