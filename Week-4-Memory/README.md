**CS50x Week 4: Memory**

This folder contains my implementations for the Week 4 Problem Set, focusing on low-level memory management, pointer arithmetic, and file I/O in C.

**📂 Projects**
1. Volume
Goal: Adjust the volume of a .wav audio file by a scaling factor.

Implementation: Reads the 44-byte WAV header into a buffer, followed by iterating through 16-bit audio samples, scaling them, and writing to a new file.

File: volume.c

2. **Filter (Less)**
Goal: A command-line utility to apply image filters to BMP files.

Implementation: Manipulated 2D arrays of RGBTRIPLE structs to achieve:

Grayscale: Averaging RGB channels.

Sepia: Applying an algorithmic color transformation.

Reflection: Horizontal pixel swapping.

Blur: 3×3 box blur via neighbor-averaging.

File: helpers.c

3. Recover
Goal: A forensic tool that recovers "deleted" JPEGs from a memory card image.

Implementation: Scans a .raw file in 512-byte blocks, identifying JPEG start signatures (0xff 0xd8 0xff) and carving out files until the next signature is found.

File: recover.c

🛠️ **Usage**
Each program can be compiled using the make command provided in the CS50 environment:

Bash
 Example: Compiling and running Filter
make filter
./filter -g input.bmp output.bmp

 Example: Compiling and running Recover
make recover
./recover card.raw

🔍 **Memory Safety**
All programs have been tested with Valgrind to ensure:

No memory leaks (all malloc'd memory is free'd).

No invalid reads or writes.

🎓 **Learning Outcomes**
By completing these challenges, I have gained a deep understanding of:

Memory Addressing: Understanding how data is physically stored in RAM and how to use the address-of (&) and dereference (*) operators.

The Heap vs. The Stack: Managing dynamic memory allocation and understanding the lifecycle of variables.

Buffer Management: Learning how to read chunks of data (blocks) into buffers and process them without overflowing memory.

Hexadecimal and Binary Data: Working directly with raw bytes, specifically identifying file signatures (magic bytes) and headers.

Defensive Programming: Using tools like Valgrind to detect memory leaks and ensuring all file pointers are correctly closed.

Correct handling of file pointers to prevent segmentation faults.
