# README for `nws` (No White Spaces)

## Description

`nws` is a command-line utility written in C++ that replaces whitespaces with hyphens in filenames. It can process either a single file or all files in a directory (with optional file extension filtering).

## Installation

### Prerequisites
- C++17 compatible compiler (GCC 8+, Clang 7+, or MSVC 2017+)
- CMake (optional, for build system)

### Building from source

1. Clone the repository or download the source code
2. Compile the program:

```bash
g++ -std=c++17 nws.cpp -o nws
```

Or with CMake:

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

3. (Optional) Install system-wide:

```bash
sudo cp nws /usr/local/bin/
```

## Usage

```
Usage: nws [options]
Options:
  --path, -p <directory>  Specify target directory (required for batch processing)
  --type, -t <extension>  Filter files by extension (e.g., html, cpp)
  --file, -f <filename>   Process a single file
  --help, -h              Show this help message

Examples:
  nws --path /path/files/ --type html
  nws --file "archivo con espacios.cpp"
```

### Examples

1. Process all HTML files in a directory:
```bash
nws --path ./documents/ --type html
```

2. Process all files in a directory (regardless of extension):
```bash
nws --path ./downloads/
```

3. Process a single file:
```bash
nws --file "my document.txt"
```

4. Show help message:
```bash
nws --help
```

## Features

- Processes files in bulk or individually
- Optional file extension filtering
- Preserves file extensions
- Reports all rename operations
- Handles errors gracefully (nonexistent files, permission issues, etc.)

## Contributing

Contributions are welcome! Please open an issue or pull request for any bugs or feature requests.
