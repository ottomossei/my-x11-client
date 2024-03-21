# my-x11-client

This README details the steps to compile and execute the C and C++ examples included in this repository, which utilize the X11 library to create basic graphical interfaces.

## Prerequisites

Ensure the following tools and libraries are installed on your system before starting:

- CMake (version 3.0 or higher)
- A C and C++ compiler (such as GCC or Clang)
- The X11 development libraries
- Python (optional, for using the provided script to automate building and running)

## Manual Compilation and Execution

### Compiling the C Example

1. Create and navigate to a new build directory:

   ```sh
   mkdir build && cd build
   ```

2. Execute CMake to configure and build the project:

   ```sh
   cmake .. && make example_c
   ```

3. Run the compiled C example:

   ```sh
   ./example_c
   ```

### Compiling the C++ Example

1. If not already in the `build` directory, create it and navigate there:

   ```sh
   mkdir build && cd build
   ```

2. Configure and build the C++ example using CMake:

   ```sh
   cmake .. && make example_cpp
   ```

3. Execute the compiled C++ program:

   ```sh
   ./example_cpp
   ```

## Building and Running with the Python Script

The `run.py` script simplifies the process of building and running the examples.

1. Verify Python is installed on your system.
2. Execute the script specifying the example type (`c` for C or `cpp` for C++):

   ```sh
   python run.py type=c
   ```

   or

   ```sh
   python run.py type=cpp
   ```

The script will clean up any previous build, compile the chosen example, and run the resulting binary.

## Additional Notes

- Confirm that the X11 development libraries are installed properly on your machine. The package is typically named `libx11-dev` or something similar, depending on your OS.
- While the Python script offers a convenient way to build and run the examples, you can manually compile and execute them using CMake and your preferred build system.

For any issues, ensure your setup is appropriate for X11 development and all necessary dependencies are in place.