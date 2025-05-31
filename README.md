# 🖼️ ASCII Generator

**ASCII Generator** is a C++ tool that converts images into expressive ASCII art using only `stb_image.h`. It reads images (like JPEG or PNG), calculates pixel brightness, and maps them to ASCII characters — creating stunning terminal-style visuals.

---

## ✨ Features

- 🖼️ Load `.jpg`, `.png`, and other formats via `stb_image.h`
- 🎨 Outputs ASCII representation directly in terminal or to a file
- 📏 Adjustable resolution and scaling
- 💡 Customizable character sets
- 🔧 Lightweight and dependency-free (besides `stb_image.h`)

---

## 📁 Project Structure

```bash
ascii-generator/
├── include/              # Header files (AsciiEngine.h, stb_image.h)
├── src/                  # Source files (AsciiEngine.cpp, main.cpp)
├── bin/                  # Compiled binary output
└── Makefile              # Easy build configuration
```

---

## 🛠️ Building the Project

Make sure you have a C++ compiler (e.g., `g++` or `clang++`) installed.

```bash
git clone https://github.com/zmn17/ascii-generator.git
cd ascii-generator
make
```

Alternatively:

```bash
g++ -std=c++17 -Iinclude -o bin/ascii-art src/*.cpp
```

---

## 🚀 Usage

```bash
./bin/ascii-art path/to/image.jpg
```

Optionally, customize brightness mapping and resolution via the code or command-line (if implemented).

---

## 🧪 Sample Output

```text
@##%%==--...
++==--::..
  ...    
```

> ✨ Want colorized ASCII in terminal? Check out `\033[1;Xm` escape codes in C++.

---

## 📦 Dependencies

- [`stb_image.h`](https://github.com/nothings/stb) (included in repo)

---

## 🧩 Todo / Roadmap

- [ ] Add grayscale image saving
- [ ] Add CLI support for resolution and output path
- [ ] Add more character set presets
- [ ] Export colored ASCII to HTML or SVG

---

## 📄 License

Licensed under the [MIT License](LICENSE).  
Credit to [nothings/stb](https://github.com/nothings/stb) for image loading.
