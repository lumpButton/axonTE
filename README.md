# AxonTE

A lightweight, feature-rich terminal-based text editor written in C using the ncurses library. AxonTE provides essential text editing functionality with a clean, minimalist interface designed for efficient text manipulation and comfortable viewing.

## Features

### Core Editing
- **Text Editing**: Insert and delete characters with real-time cursor positioning
- **Smart Line Management**: Automatic line splitting on Enter and merging on Backspace
- **Cursor Navigation**: Move seamlessly through text with arrow keys, including line wrapping
- **Visual Cursor**: Highlighted cursor position with reverse video display

### File Operations
- **File I/O**: Load and save text files with command-line file specification
- **Dirty State Tracking**: Visual indicator when file has unsaved changes
- **Auto-loading**: Automatically loads specified file on startup or defaults to test.txt

### Display Features
- **Vertical Scrolling**: Smart viewport management for large files
- **Line Numbers**: Zero-padded line numbering with consistent width
- **Status Bar**: Real-time display of cursor position, file state, and buffer info
- **Debug Mode**: Character code inspection with Ctrl+T for development
- **Responsive Layout**: Dynamic adjustment to terminal size

## Prerequisites

- GCC compiler with C11 support
- ncurses development library

### Installing ncurses:

**Ubuntu/Debian:**
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

**Fedora/RHEL:**
```bash
sudo dnf install ncurses-devel
```

**Arch Linux:**
```bash
sudo pacman -S ncurses
```

## Building

```bash
make
```

This creates the executable at `build/axonTE`.

### Additional Make targets:
- `make clean` - Remove entire build directory
- `make install` - Install to `/usr/local/bin/axonTE` (requires sudo)
- `make uninstall` - Remove installed binary
- `make make_install` - Build and install in one command

## Usage

```bash
# Edit a specific file
./build/axonTE filename.txt

# Edit default file (test.txt)
./build/axonTE
```

## Key Bindings

### Control Keys
| Key | Action |
|-----|--------|
| **Ctrl+Q** | Exit editor |
| **Ctrl+S** | Save file (clears dirty state) |
| **Ctrl+T** | Toggle debug mode (shows character codes and line lengths) |

### Navigation
| Key | Action |
|-----|--------|
| **Left Arrow** | Move cursor left (wraps to previous line end) |
| **Right Arrow** | Move cursor right (wraps to next line start) |
| **Up Arrow** | Move cursor up (preserves horizontal position when possible) |
| **Down Arrow** | Move cursor down (preserves horizontal position when possible) |

### Editing
| Key | Action |
|-----|--------|
| **Backspace** | Delete character at cursor (merges lines when at line start) |
| **Enter** | Create new line (splits current line at cursor position) |
| **Any character** | Insert character at cursor position |

## Interface

### Layout Components
- **Header Bar**: Application title, filename, and key command reference (reverse video)
- **Line Numbers**: Zero-padded line numbers with consistent width formatting
- **Text Area**: Scrollable content area with visual cursor highlighting
- **Debug Info**: Optional line length display in debug mode
- **Status Bar**: Comprehensive status information (reverse video)

### Status Bar Information
The bottom status bar displays:
- Total lines in buffer
- Current line number (0-indexed internally, 1-indexed display)
- Current cursor position within line
- Vertical scroll offset for large files
- Current viewport position
- Available display lines
- Dirty state indicator (shows "dirty" when file has unsaved changes)

## Technical Details

### Capacity Limits
- **Buffer Size**: 5,000 lines capacity (BUFFER_SIZE)
- **Line Size**: 1,000 characters per line (LINE_SIZE)
- **Memory Management**: Dynamic line allocation with proper cleanup

### Architecture
- **Modular Design**: Clean separation of concerns across components
- **Line-Based Storage**: Each line stored as separate Line struct with length tracking
- **Global Buffer State**: Centralized buffer management with position tracking
- **Viewport Management**: Efficient scrolling with y_offset and current_y tracking

### Display System
- **Input Mode**: Raw mode with no echo for immediate key response
- **Cursor Display**: System cursor disabled, uses reverse video highlighting
- **Smart Scrolling**: Automatic viewport adjustment to keep cursor visible
- **Dynamic Layout**: Responsive to terminal resize events

### Data Structures
```c
typedef struct {
    char* line;          // Dynamic string storage
    int length;          // Current line length
} Line;

typedef struct {
    Line* lines[BUFFER_SIZE];  // Array of line pointers
    int amount_lines;          // Total lines in buffer
    int current_line;          // Current line index
    int current_pos;           // Current position in line
    int current_y_offset;      // Scroll offset for viewport
    int current_y;             // Current display line
} Buffer;
```

## Project Structure

```
axonTE/
├── src/
│   ├── main.c          # Main program loop and input handling
│   ├── buffer.c        # Core text buffer management and cursor operations
│   ├── file.c          # File I/O operations (load/save)
│   ├── editor.c        # Display rendering and UI management
│   └── ui.c            # Additional UI components (minimal/placeholder)
├── include/
│   ├── buffer.h        # Buffer data structures and function declarations
│   ├── file.h          # File operation interfaces
│   ├── editor.h        # Display function interfaces
│   └── ui.h            # UI component interfaces (minimal)
├── build/
│   ├── objects/        # Compiled object files
│   └── axonTE          # Final executable
├── Makefile            # Build system configuration
└── README.md           # This file
```

### Component Responsibilities

#### `main.c` - Program Entry and Input Loop
- Initializes ncurses environment with raw mode
- Manages main input loop with key handling
- Controls program lifecycle and command-line argument processing
- Handles dirty state tracking for unsaved changes

#### `buffer.c` - Text Buffer Management
- Implements line-based buffer system with dynamic allocation
- Provides character insertion (`add_char`) and deletion (`rem_char`)
- Manages 4-directional cursor movement with line wrapping
- Handles viewport scrolling with y_offset tracking
- Memory management for Line structs

#### `file.c` - File Operations
- Loads files character by character into buffer system
- Saves buffer content with proper line termination
- Handles file existence and access patterns

#### `editor.c` - Display and Rendering
- Manages ncurses display with scrollable viewport
- Renders line numbers with zero-padding
- Handles cursor visualization with reverse video
- Provides debug mode with character code display
- Status bar rendering with comprehensive information

## License

Open source project.