# FDF - Wireframe Viewer

A 3D wireframe viewer that renders height maps as beautiful wireframe models with multiple projections and interactive controls.

## 🌟 About

FDF (Fil de Fer) is a graphics project that takes height map files and renders them as 3D wireframe models. The program supports multiple projection modes, real-time transformations, and dynamic coloring based on elevation data.

## 🚀 Features

- **Multiple Projections**: Isometric and conic (perspective) projections
- **Interactive Controls**: Real-time manipulation with keyboard and mouse
- **Dynamic Coloring**: Height-based color schemes for better visualization
- **Zoom & Pan**: Smooth zooming and panning capabilities
- **Rotation Controls**: Rotate the model in real-time
- **Adaptive Rendering**: Automatically adjusts detail level based on map size
- **File Format Support**: Reads standard FDF height map files

## 🎮 Controls

### Movement
- **W/↑**: Move up
- **S/↓**: Move down  
- **A/←**: Move left
- **D/→**: Move right

### Zoom & View
- **+**: Zoom in
- **-**: Zoom out
- **P**: Switch projection mode (Isometric ↔ Conic)

### Rotation & Angles
- **I**: Rotate clockwise
- **K**: Rotate counter-clockwise
- **Q**: Increase isometric angle
- **E**: Decrease isometric angle

### Detail Level
- **R**: Increase detail (decrease step size)
- **T**: Decrease detail (increase step size)

### Mouse Controls
- **Left Click**: Zoom in
- **Right Click**: Zoom out
- **Mouse Wheel Up**: Increase Z-scale
- **Mouse Wheel Down**: Decrease Z-scale

### Exit
- **ESC**: Exit the application

## 🛠️ Requirements

- **MinilibX**: Graphics library for Linux/macOS
- **GCC**: C compiler
- **Make**: Build system
- **Math Library**: For trigonometric calculations

## 📦 Installation

1. **Clone the repository**:
   ```bash
   git clone [your-repo-url]
   cd fdf
   ```

2. **Compile the project**:
   ```bash
   make
   ```

3. **Run with a map file**:
   ```bash
   ./fdf maps/42.fdf
   ```

## 📁 Project Structure

```
fdf/
├── src/
│   ├── main.c              # Program entry point
│   ├── map.c               # Map parsing logic
│   ├── map_utils.c         # Map utilities
│   ├── parse.c             # File parsing
│   ├── parse_utils.c       # Parsing utilities
│   ├── validate.c          # Input validation
│   ├── draw_line.c         # Bresenham line drawing
│   ├── draw_wireframe.c    # Wireframe rendering
│   ├── projections.c       # 3D projections
│   ├── event_handle.c      # Event handling
│   └── color.c             # Color management
├── inc/
│   └── fdf.h               # Header file
├── lib/
│   ├── libft/              # Custom C library
│   └── get_next_line/      # Line reading utility
├── maps/                   # Sample map files
├── Makefile               # Build configuration
└── README.md              # This file
```

## 🗺️ Map File Format

FDF files contain height data in a simple text format:
```
0 0 0 0 0
0 1 2 1 0
0 2 3 2 0
0 1 2 1 0
0 0 0 0 0
```

- Each number represents the height (Z value) at that position
- Optional color values can be specified: `10,0xFF0000` (height 10, red color)
- Supports negative heights for valleys and depressions

## 🎨 Color Schemes

The program supports multiple color schemes:
- **Scheme 0**: Monochrome (white wireframe)
- **Scheme 1**: Blue to Red gradient based on height
- **Scheme 2**: Green to Magenta gradient based on height

## 🔧 Technical Details

### Algorithms Used
- **Bresenham's Line Algorithm**: For efficient line drawing
- **Isometric Projection**: For 3D visualization
- **Conic Projection**: For perspective view
- **Color Interpolation**: For smooth height-based coloring

### Performance Optimizations
- **Adaptive Step Size**: Reduces detail for large maps
- **Efficient Memory Management**: Careful allocation and cleanup
- **Optimized Rendering**: Skip pixels outside screen bounds

## 🐛 Error Handling

The program handles various error conditions:
- Invalid file formats
- Memory allocation failures
- File I/O errors
- Invalid map dimensions
- Malformed height data

## 🤝 Contributing

Contributions are welcome! Please feel free to:
- Report bugs and issues
- Suggest new features
- Submit pull requests
- Improve documentation

## 📝 License

This project is part of the 42 School curriculum and follows their guidelines.

## 🚀 Future Enhancements

- [ ] Add texture mapping support
- [ ] Implement smooth shading
- [ ] Add lighting effects
- [ ] Support for larger map files
- [ ] Animation and fly-through modes
- [ ] Export rendered images
- [ ] Additional projection types

---

**Create stunning 3D visualizations from height data!** 🏔️
