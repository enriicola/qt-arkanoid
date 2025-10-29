# Qt Arkanoid Resources

This directory contains all game assets bundled via Qt's resource system.

## Directory Structure

- **levels/** - Level data files in JSON format
- **images/** - Game graphics, sprites, and icons
- **sounds/** - Sound effects and background music (when implemented)
- **fonts/** - Custom fonts (when needed)

## Adding New Resources

1. Add your asset file to the appropriate subdirectory
2. Update `resources.qrc` in the project root to include the new file
3. Rebuild the project (CMake will automatically compile resources via AUTORCC)
4. Access resources in code using the `:/prefix/path` syntax

## Resource Paths

Resources are accessed with the following prefixes:
- Levels: `:/levels/resources/levels/`
- Images: `:/images/resources/images/`
- Sounds: `:/sounds/resources/sounds/`
- Fonts: `:/fonts/resources/fonts/`

## Level Format

Levels are stored as JSON files with the following structure:

```json
{
    "levelNumber": 1,
    "name": "Level Name",
    "description": "Level description",
    "ballSpeed": 300.0,
    "bricks": [
        {
            "row": 0,
            "col": 0,
            "color": "#FF6464",
            "hitPoints": 1
        }
    ]
}
```

## Image Formats

- **Icon**: SVG format for scalability
- Recommended formats: SVG, PNG (with transparency)
- Keep file sizes optimized for quick loading

## Notes

- All resources are embedded into the executable at compile time
- Resources are read-only at runtime
- No external files needed for distribution (except optional external levels)
