# ft_ssl_md5

A C implementation of cryptographic hash functions, recreating the behavior of OpenSSL's message digest commands.

## 📋 Project Overview

This project is part of the 42 school curriculum and implements several cryptographic hash algorithms from scratch. The program mimics the functionality of OpenSSL's `md5`, `sha256`, and related commands, providing both command-line and interactive interfaces.

## 🎯 Implemented Algorithms

- **MD5** - 128-bit hash function
- **SHA-224** - 224-bit hash function (SHA-2 family)
- **SHA-256** - 256-bit hash function (SHA-2 family)
- **SHA-384** - 384-bit hash function (SHA-2 family)
- **SHA-512** - 512-bit hash function (SHA-2 family)

## 🔧 Features

### Input Methods
- **String hashing**: Hash text directly from command line with `-s` flag
- **File hashing**: Hash file contents
- **Standard input**: Read from stdin/pipe
- **Interactive mode**: No arguments launches interactive prompt

### Command-Line Options
- `-h` : Print help and exit
- `-p` : Echo stdin to stdout and append hash
- `-q` : Quiet mode - only output the hash
- `-r` : Reverse output format (hash before filename)
- `-s <string>` : Hash the provided string

### Output Formats
```bash
# Default format
MD5 ("hello") = 5d41402abc4b2a76b9719d911017c592

# Quiet mode (-q)
5d41402abc4b2a76b9719d911017c592

# Reverse format (-r)
5d41402abc4b2a76b9719d911017c592 "hello"
```

## 🏗️ Project Structure

```
.
├── Makefile
├── README.md
├── libft/                 # Custom C library
│   ├── gnl/               # Get Next Line for interactive mode
│   ├── printf/            # Printf custom implementation
│   └── str/mem/is/to/     # String/Memory utilities
└── srcs/
    ├── incs/              # Header files
    │   ├── ft_ssl.h
    │   ├── md5.h
    │   ├── sha224.h
    │   ├── sha256.h
    │   ├── sha384.h
    │   ├── sha512.h
    │   └── types.h
    ├── main.c             # Entry point
    ├── parser.c           # Command-line argument parsing
    ├── md5.c              # MD5 implementation
    ├── sha224.c           # SHA-224 implementation
    ├── sha256.c           # SHA-256 implementation
    ├── sha384.c           # SHA-384 implementation
    ├── sha512.c           # SHA-512 implementation
    ├── bitwise_utils.c    # Bitwise operations (rotations, endianness)
    ├── print_utils.c      # Output formatting
    └── interactive.c      # Interactive mode handling
```

## 🚀 Installation & Usage

### Compilation
```bash
make                   # Compile the project
make clean             # Remove object files
make fclean            # Remove all build artifacts
make re                # Rebuild everything
make norm              # Check code style (42 norminette)
```

### Program Usage

```
Usage
  ./ft_ssl <command> [flags] [file]

Options:
  command     md5, sha224, sha256, sha384 or sha512
  -h          print help and exit
  -p          echo STDIN to STDOUT and append the checksum to STDOUT
  -q          quiet mode
  -r          reverse the format of the output
  -s <string> print the sum of the given string
```

### Basic Usage

```bash
# Print help
./ft_ssl -h

# Hash a string
./ft_ssl md5 -s "hello world"
./ft_ssl sha256 -s "hello world"

# Hash a file
./ft_ssl md5 file.txt
./ft_ssl sha256 /etc/passwd

# Hash from pipe
echo "hello" | ./ft_ssl md5
cat file.txt | ./ft_ssl sha512

# Interactive mode
./ft_ssl md5
> hello world
^D

# Combine options
./ft_ssl sha256 -q -s "test"           # Quiet mode
./ft_ssl md5 -r file.txt               # Reverse format
echo "test" | ./ft_ssl sha256 -p       # Echo stdin

# Multiple hashes in one command
echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" Makefile
```

## 🔬 Technical Implementation

### Algorithm Details

**MD5 (Message Digest 5)**
- Block size: 512 bits (64 bytes)
- Output size: 128 bits (16 bytes)
- Operates on 32-bit words
- Uses 4 auxiliary functions and 64 constants

**SHA-256 / SHA-224**
- Block size: 512 bits (64 bytes)
- Output size: 256 bits (32 bytes) / 224 bits (28 bytes)
- Operates on 32-bit words
- Uses 8 working variables and 64 constants
- SHA-224 is a truncated version of SHA-256 with different initial hash values

**SHA-512 / SHA-384**
- Block size: 1024 bits (128 bytes)
- Output size: 512 bits (64 bytes) / 384 bits (48 bytes)
- Operates on 64-bit words
- Uses 8 working variables and 80 constants
- SHA-384 is a truncated version of SHA-512 with different initial hash values

### Key Features
- Message padding with length encoding
- Endianness handling for cross-platform compatibility
- Memory-mapped file I/O for efficient large file processing
- Support for messages up to 2^64 bits
- Zero external crypto libraries (pure C implementation)

## 🧪 Testing

```bash
# Compare with system md5sum/sha256sum
echo "test" | ./ft_ssl md5
echo "test" | md5sum

# Test all algorithms
./ft_ssl md5 -s "42"
./ft_ssl sha224 -s "42"
./ft_ssl sha256 -s "42"
./ft_ssl sha384 -s "42"
./ft_ssl sha512 -s "42"

# Test with files
./ft_ssl sha256 /bin/ls
sha256sum /bin/ls
```

## 📝 License

This project is part of 42 School curriculum and is intended for educational purposes.

---

*Note: MD5 and SHA-1 are considered cryptographically broken and should not be used for security purposes. This implementation is for educational purposes only.*
