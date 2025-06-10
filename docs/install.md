# OptiSim Installation Guide

Welcome to **OptiSim** – a modular optical simulator with C++, Python, and Java components. This guide will walk you through setting up the application and using it as a GUI program or as a library in your own projects.

## Prerequisites

Before you get started, make sure you have the following installed:

- **CMake** and **g++**
- **Python 3.12**
- **Java Development Kit (JDK)**
- A Linux-based OS (tested on Ubuntu)
- **pybind11** and **jpype** 

## Step 1: Clone the Repository

Clone the OptiSim repository from GitHub:
```bash
git clone https://github.com/VitusSzabolcs/OptiSim.git
```
## Step 2: Navigate to the Installer

Change directory to the OptiSim installer:
```bash
cd OptiSim/Run
```

## Step 3: Compile and Install

Run the installation script:

```bash
./run.sh
```
This script will:
- Compile all necessary components (C++, Python, Java)

- Add the CLI build directory to your PATH so you can run OptiSim from any terminal

- Create a desktop shortcut for launching the GUI version

> **_NOTE:_** If the script doesn't launch via double-click, ensure it's executable and trusted, or run it from a terminal.

## Using OptiSim as a C++ Library

You can integrate OptiSim into your own C++ programs.

### Include the Header

```cpp
#include "OptiSim.h"
```
### Compile Your Program

Replace `<full-path-to-OptiSim>` with the actual path to your cloned repository:

```bash
g++ your_program.cpp \
  -I<full-path-to-OptiSim>/CPP/include \
  -L<full-path-to-OptiSim>/CPP/build \
  -lOptiSimLib \
  -o example
```
## Using OptiSim as a Python Module

To use OptiSim in Python:

1. Copy the compiled shared object file to your working directory:
```bash
cp <full-path-to-OptiSim>/Python/optisim.cpython-312-x86_64-linux-gnu.so .
```

2. Import it in Python:
```python
import optisim
```
You can now access the OptiSim functionality directly in Python scripts or Jupyter notebooks.

## GUI Application

Once the installation completes:

- A desktop shortcut named "OptiSim" will appear on your desktop.

- Double-click it to launch the GUI application.

## Need Help?

If you run into any issues during installation or usage, feel free to open an issue on the [GitHub repository](https://github.com/VitusSzabolcs/OptiSim).