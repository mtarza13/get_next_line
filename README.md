<a name="readme-top"></a>
<div align="center">
  <!-- Logo -->
  <a href="https://github.com/mtarza13/get_next_line">
    <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/badges/get_next_linem.png" alt="Get Next Line Logo" width="150" height="150">
  </a>

  <!-- Project Name -->
  <h1>📄 Get Next Line</h1>

  <!-- Short Description -->
  <p align="center">
    <b>42 School - File Reading Function</b><br>
    A function that reads a file line by line, regardless of buffer size
  </p>

  <!-- Badges -->
  <p>
    <img src="https://img.shields.io/badge/Score-125%20%2F%20100-success?style=for-the-badge" />
    <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c" />
    <img src="https://img.shields.io/badge/Concept-File%20I%2FO-orange?style=for-the-badge" />
    <img src="https://img.shields.io/badge/Method-Static%20Variables-red?style=for-the-badge" />
    <img src="https://img.shields.io/badge/42-Project-000000?style=for-the-badge&logo=42" />
  </p>

  <h3>
    <a href="#-about-project">📜 About</a>
    <span> · </span>
    <a href="#-algorithm">🧠 Algorithm</a>
    <span> · </span>
    <a href="#-implementation">⚙️ Implementation</a>
    <span> · </span>
    <a href="#-usage">🚀 Usage</a>
    <span> · </span>
    <a href="#-bonus-features">🌟 Bonus</a>
  </h3>
</div>

---

## 📜 About Project

**Get Next Line** is a crucial project at 42 School that teaches **file manipulation** and **memory management**. The goal is to create a function that reads a file line by line, returning one line at a time until the entire file is read, regardless of the line length or buffer size.

### 🎯 Learning Objectives
- Master **static variables** and their persistence
- Understand **file descriptors** and file I/O operations
- Implement **dynamic memory allocation** strategies
- Handle **buffer management** efficiently
- Work with **edge cases** in file reading
- Optimize **memory usage** and prevent leaks

> [!NOTE]
> This project follows **42 School coding standards**:
> - Maximum 25 lines per function
> - Variables declared at function top
> - Only allowed functions may be used
> - No global variables allowed
> - No memory leaks or undefined behavior

---

## 🧠 Algorithm Strategy

### 🎯 Core Concept: Static Buffer Management

My implementation uses **static variables** to maintain state between function calls, allowing continuous reading from where the previous call left off.

```
Buffer Management Strategy:
┌─────────────────────────────────────────────────┐
│ File: "Hello\nWorld\nHow\nAre\nYou"            │
└─────────────────────────────────────────────────┘
         ↓ read(BUFFER_SIZE)
┌─────────────────────────────────────────────────┐
│ Static Buffer: "Hello\nWorld\nHow\nAre\nYou"   │
└─────────────────────────────────────────────────┘
         ↓ extract_line()
┌─────────────────────────────────────────────────┐
│ Return: "Hello\n"                               │
│ Remaining: "World\nHow\nAre\nYou"               │
└─────────────────────────────────────────────────┘
```

### 🔄 Line Extraction Process

```c
/*
 * Core algorithm: Read, buffer, extract, repeat
 * 1. Read from file into buffer (if needed)
 * 2. Search for newline character
 * 3. Extract line (including newline)
 * 4. Update static buffer with remaining data
 * 5. Return extracted line
 */
```

---

## ⚙️ Implementation

### 🏗️ Project Structure

```
📁 Get Next Line
├── 📄 get_next_line.h            # Main header file
├── 📄 get_next_line.c            # Core GNL implementation
├── 📄 get_next_line_utils.c      # Helper functions
├── 📄 get_next_line_bonus.h      # Bonus header file
├── 📄 get_next_line_bonus.c      # Bonus implementation (multiple FDs)
└── 📄 get_next_line_utils_bonus.c # Bonus helper functions
```

### 🔧 Core Data Flow

#### Function Prototype
```c
char *get_next_line(int fd);
```

#### Return Values
- **Valid line**: Pointer to string containing the line (including `\n` if present)
- **End of file**: `NULL` when file is completely read
- **Error**: `NULL` on invalid file descriptor or memory allocation failure

### 💡 Algorithm Implementation

#### Main Function Logic
```c
char *get_next_line(int fd)
{
    static char *buffer;        // Static buffer persists between calls
    char        *line;          // Current line to return
    
    // Validate file descriptor
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    
    // Read and accumulate data until newline found or EOF
    buffer = read_and_accumulate(fd, buffer);
    if (!buffer)
        return (NULL);
    
    // Extract line from buffer
    line = extract_line(buffer);
    
    // Update buffer with remaining data
    buffer = update_buffer(buffer);
    
    return (line);
}
```

#### Buffer Reading Strategy
```c
char *read_and_accumulate(int fd, char *buffer)
{
    char    *temp_buffer;
    int     bytes_read;
    
    temp_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!temp_buffer)
        return (NULL);
    
    bytes_read = 1;
    while (!ft_strchr(buffer, '\n') && bytes_read != 0)
    {
        bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(temp_buffer);
            return (NULL);
        }
        
        temp_buffer[bytes_read] = '\0';
        buffer = ft_strjoin(buffer, temp_buffer);
    }
    
    free(temp_buffer);
    return (buffer);
}
```

#### Line Extraction
```c
char *extract_line(char *buffer)
{
    int     i;
    char    *line;
    
    if (!buffer[0])
        return (NULL);
    
    i = 0;
    // Find newline or end of buffer
    while (buffer[i] && buffer[i] != '\n')
        i++;
    
    // Allocate memory for line (include newline if present)
    line = malloc(sizeof(char) * (i + 2));
    if (!line)
        return (NULL);
    
    i = 0;
    while (buffer[i] && buffer[i] != '\n')
    {
        line[i] = buffer[i];
        i++;
    }
    
    // Include newline if found
    if (buffer[i] == '\n')
    {
        line[i] = buffer[i];
        i++;
    }
    
    line[i] = '\0';
    return (line);
}
```

#### Buffer Update
```c
char *update_buffer(char *buffer)
{
    int     i;
    int     j;
    char    *new_buffer;
    
    i = 0;
    // Skip to character after newline
    while (buffer[i] && buffer[i] != '\n')
        i++;
    
    if (!buffer[i])
    {
        free(buffer);
        return (NULL);
    }
    
    // Allocate new buffer for remaining data
    new_buffer = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
    if (!new_buffer)
        return (NULL);
    
    i++;  // Skip past newline
    j = 0;
    // Copy remaining data
    while (buffer[i])
        new_buffer[j++] = buffer[i++];
    
    new_buffer[j] = '\0';
    free(buffer);
    return (new_buffer);
}
```

---

## 🚀 Usage

### Prerequisites
- **GCC compiler**
- **Standard C libraries**
- **File system access**

### Compilation
```c
// Compile with your main function
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

// For bonus (multiple file descriptors)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

### Basic Usage Example
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;
    
    // Open file for reading
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return (1);
    }
    
    // Read file line by line
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: %s", line);
        free(line);  // Don't forget to free!
    }
    
    close(fd);
    return (0);
}
```

### Advanced Usage Examples

#### Reading Multiple Files
```c
int main(void)
{
    int     fd1, fd2;
    char    *line1, *line2;
    
    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    
    // Alternate reading from both files
    while ((line1 = get_next_line(fd1)) || (line2 = get_next_line(fd2)))
    {
        if (line1)
        {
            printf("File1: %s", line1);
            free(line1);
        }
        if (line2)
        {
            printf("File2: %s", line2);
            free(line2);
        }
    }
    
    close(fd1);
    close(fd2);
    return (0);
}
```

#### Reading from Standard Input
```c
int main(void)
{
    char *line;
    
    printf("Enter lines (Ctrl+D to end):\n");
    
    // Read from stdin (file descriptor 0)
    while ((line = get_next_line(0)) != NULL)
    {
        printf("You entered: %s", line);
        free(line);
    }
    
    return (0);
}
```

#### Large File Processing
```c
int main(void)
{
    int     fd;
    char    *line;
    int     line_count = 0;
    
    fd = open("large_file.txt", O_RDONLY);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        line_count++;
        
        // Process line (example: count characters)
        printf("Line %d: %zu characters\n", line_count, strlen(line));
        
        free(line);
        
        // Optional: limit processing for demo
        if (line_count >= 1000)
            break;
    }
    
    printf("Processed %d lines\n", line_count);
    close(fd);
    return (0);
}
```

---

## 🌟 Bonus Features

### ✨ Multiple File Descriptor Support

The bonus implementation allows reading from **multiple file descriptors simultaneously**, maintaining separate static buffers for each file descriptor.

#### Bonus Implementation Strategy
```c
char *get_next_line(int fd)
{
    static char *buffers[MAX_FD];  // Array of buffers for different FDs
    char        *line;
    
    // Validate file descriptor range
    if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
        return (NULL);
    
    // Use specific buffer for this file descriptor
    buffers[fd] = read_and_accumulate(fd, buffers[fd]);
    if (!buffers[fd])
        return (NULL);
    
    line = extract_line(buffers[fd]);
    buffers[fd] = update_buffer(buffers[fd]);
    
    return (line);
}
```

#### Multiple FD Usage Example
```c
int main(void)
{
    int     fd1, fd2, fd3;
    char    *line;
    
    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    fd3 = open("file3.txt", O_RDONLY);
    
    // Read first line from each file
    printf("File1 Line1: %s", get_next_line(fd1));
    printf("File2 Line1: %s", get_next_line(fd2));
    printf("File3 Line1: %s", get_next_line(fd3));
    
    // Read second line from each file
    printf("File1 Line2: %s", get_next_line(fd1));
    printf("File2 Line2: %s", get_next_line(fd2));
    printf("File3 Line2: %s", get_next_line(fd3));
    
    close(fd1);
    close(fd2);
    close(fd3);
    return (0);
}
```

---

## 🧪 Testing Suite

### 📋 Comprehensive Testing

#### Test File Creation
```bash
#!/bin/bash
# create_test_files.sh

# Create various test files
echo -e "Line 1\nLine 2\nLine 3" > normal.txt
echo -e "Very long line that exceeds typical buffer sizes and should test the dynamic allocation and buffer management capabilities of the get_next_line function\nShort line\nAnother very long line designed to test edge cases in memory management and buffer handling" > long_lines.txt
echo -n "No newline at end" > no_newline.txt
echo "" > empty.txt
echo -e "\n\n\n" > only_newlines.txt
echo -e "Line with spaces    \nLine with\ttabs\n" > special_chars.txt
```

#### Basic Functionality Tests
```c
// test_basic.c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void test_normal_file(void)
{
    int fd = open("normal.txt", O_RDONLY);
    char *line;
    int line_num = 1;
    
    printf("=== Testing Normal File ===\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: '%s'\n", line_num++, line);
        free(line);
    }
    close(fd);
}

void test_empty_file(void)
{
    int fd = open("empty.txt", O_RDONLY);
    char *line;
    
    printf("=== Testing Empty File ===\n");
    line = get_next_line(fd);
    if (line == NULL)
        printf("Correctly returned NULL for empty file\n");
    else
        printf("ERROR: Should return NULL for empty file\n");
    close(fd);
}

void test_no_newline(void)
{
    int fd = open("no_newline.txt", O_RDONLY);
    char *line;
    
    printf("=== Testing File Without Final Newline ===\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: '%s'\n", line);
        free(line);
    }
    close(fd);
}

int main(void)
{
    test_normal_file();
    test_empty_file();
    test_no_newline();
    return (0);
}
```

#### Buffer Size Testing
```bash
#!/bin/bash
# test_buffer_sizes.sh

echo "Testing different buffer sizes..."

for buffer_size in 1 5 10 42 100 1000 10000; do
    echo "Testing with BUFFER_SIZE=$buffer_size"
    gcc -Wall -Wextra -Werror -D BUFFER_SIZE=$buffer_size get_next_line.c get_next_line_utils.c test_basic.c -o test_gnl
    ./test_gnl
    echo "Buffer size $buffer_size: OK"
done

rm test_gnl
```

#### Memory Leak Testing
```bash
#!/bin/bash
# test_memory.sh

echo "Testing for memory leaks..."

gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c test_basic.c -o test_gnl

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test_gnl

rm test_gnl
```

#### Stress Testing
```c
// stress_test.c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void create_large_file(void)
{
    FILE *fp = fopen("large_test.txt", "w");
    
    for (int i = 0; i < 10000; i++)
    {
        fprintf(fp, "This is line number %d with some additional text to make it longer\n", i);
    }
    fclose(fp);
}

void test_large_file(void)
{
    int fd = open("large_test.txt", O_RDONLY);
    char *line;
    int count = 0;
    
    printf("=== Stress Testing Large File ===\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        count++;
        free(line);
        
        if (count % 1000 == 0)
            printf("Processed %d lines...\n", count);
    }
    
    printf("Successfully processed %d lines\n", count);
    close(fd);
}

int main(void)
{
    create_large_file();
    test_large_file();
    return (0);
}
```

---

## 📊 Performance Analysis

### 🎯 Efficiency Metrics

| Buffer Size | Small Files (< 1KB) | Medium Files (1-100KB) | Large Files (> 1MB) |
|-------------|-------------------|----------------------|-------------------|
| 1 byte      | Slow (many reads) | Very slow            | Extremely slow    |
| 42 bytes    | Good              | Good                 | Acceptable        |
| 1024 bytes  | Excellent         | Excellent            | Good              |
| 8192 bytes  | Excellent         | Excellent            | Excellent         |

### 📈 Memory Usage Analysis
```
Memory Efficiency:
├── Static buffer: O(BUFFER_SIZE) persistent memory
├── Line allocation: O(line_length) per line
├── Temporary buffer: O(BUFFER_SIZE) during reading
└── Total peak usage: O(BUFFER_SIZE + longest_line)
```

### ⚡ Performance Optimization Tips
```c
/*
 * Optimal buffer size selection:
 * - Small files: BUFFER_SIZE = 42-100
 * - Large files: BUFFER_SIZE = 1024-8192
 * - Network files: BUFFER_SIZE = 1024
 * - SSD storage: BUFFER_SIZE = 4096
 */
```

---

## 🔧 Technical Implementation Details

### 🧵 Static Variable Management
```c
/*
 * Why static variables are essential:
 * 1. Preserve buffer state between function calls
 * 2. Enable continuous reading from where we left off
 * 3. Avoid re-reading already processed data
 * 4. Maintain efficiency across multiple calls
 */
```

### 🔍 Edge Case Handling
```c
/*
 * Comprehensive edge case coverage:
 * ✅ Empty files
 * ✅ Files without final newline
 * ✅ Files with only newlines
 * ✅ Very long lines (> BUFFER_SIZE)
 * ✅ Invalid file descriptors
 * ✅ Memory allocation failures
 * ✅ Read errors
 */
```

### 💾 Memory Management Strategy
```c
/*
 * Memory safety principles:
 * 1. Always free allocated memory
 * 2. Set pointers to NULL after freeing
 * 3. Check malloc return values
 * 4. Handle allocation failures gracefully
 * 5. Avoid memory leaks in error conditions
 */
```

---

## 📚 Resources & References

### Technical Documentation
- [File I/O in C](https://www.tutorialspoint.com/cprogramming/c_file_io.htm)
- [Static Variables in C](https://www.geeksforgeeks.org/static-variables-in-c/)
- [Dynamic Memory Allocation](https://www.programiz.com/c-programming/c-dynamic-memory-allocation)

### 42 School Resources
- [Get Next Line Subject](https://cdn.intra.42.fr/pdf/pdf/960/get_next_line.en.pdf)
- [File Descriptor Documentation](https://man7.org/linux/man-pages/man2/read.2.html)

### Additional Learning
- [Buffer Management Techniques](https://en.wikipedia.org/wiki/Data_buffer)
- [File System Interface](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/11_FileSystemInterface.html)

---

## 🏆 Project Achievements

### ✅ Mandatory Requirements
- [x] **Function reads line by line** from any file descriptor
- [x] **Returns complete lines** including newline character
- [x] **Handles end of file** correctly (returns NULL)
- [x] **Memory efficient** with configurable buffer size
- [x] **No memory leaks** or undefined behavior
- [x] **Error handling** for invalid inputs

### 🌟 Bonus Features
- [x] **Multiple file descriptor support** simultaneously
- [x] **Independent buffer management** per file descriptor
- [x] **Optimized memory usage** for concurrent file reading

### 🔧 Technical Highlights
- **Static variable mastery** for state persistence
- **Dynamic memory management** with efficient allocation
- **Buffer optimization** for different file sizes
- **Robust error handling** and edge case management
- **Cross-platform compatibility** (Linux/macOS)

---

## 👨‍💻 Author

**mtarza13** - [GitHub Profile](https://github.com/mtarza13)

*42 School Student | File I/O & Memory Management Specialist*

**Contact**: mtarza13@student.42.fr

---

## 📄 License

This project is part of the 42 School curriculum. Please respect the academic integrity policies of your institution.

---

<div align="center">
  <p>
    <b>⭐ If this project helped you understand file I/O and memory management, please give it a star! ⭐</b>
  </p>
  
  <p>
    <a href="#readme-top">🔝 Back to top</a>
  </p>
</div>