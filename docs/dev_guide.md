# Developer Guide

This guide is intended for anyone who wishes to contribute to the OptiSim project, build it from source, or understand its internal architecture and development practices. It covers environment setup, build procedures, coding standards, testing, and contribution workflows.

## 1. Getting Started

Before diving into development, ensure you have met all the [Requirements](requirement.md) specified for developers. This section will guide you through setting up your local development environment.

### 1.1. Cloning the Repository

To begin, obtain the OptiSim source code from its Git repository.

### 1.2. Setting Up the Python Virtual Environment

Working within a Python virtual environment is crucial to manage dependencies and avoid conflicts with your system's Python installation. This involves creating the environment, activating it, and then installing all necessary Python packages.

## 2. Building the Project

The entire build process for OptiSim's C++ backend and Python bindings is automated via a dedicated shell script.

### 2.1. Standard Build Process

To build the project, navigate to the project root directory and execute the provided build script. This script handles all necessary steps, including CMake configuration, compilation of the C++ components, and generation of the Python module.

### 2.2. Building the Python Module

The Python module (e.g., `optisim.cpython-312-x86_64-linux-gnu.so`) is compiled and prepared for use as part of the automated build script. Ensure it is placed in a directory accessible by Python's import mechanism.

## 3. Project Structure

Understanding the project's directory layout is essential for navigation and contribution.

* **`/` (Project Root):** Contains main configuration files such as `CMakeLists.txt`, `mkdocs.yml`, and the primary documentation folder.
* **`/CPP/`:** (Or `/src/`, `/core/` etc.) Source code for the core C++ OptiSim library.
* **`/Python/`:** Python-specific code, `pybind11` binding definitions, and potentially pure Python modules that interface with the C++ backend.
* **`/Java/`:** (If applicable) Java source code, along with relevant build configuration files.
* **`/docs/`:** Contains the MkDocs documentation source files, including this guide.
* **`/tests/`:** Unit and integration tests for both C++ and Python components.
* **`/Run/`:** Contains the shell file necessary for compilation.
* **`/examples/`:** Python and CPP example files and basic applications.  

## 4. Coding Guidelines and Style

Maintaining a consistent code style is vital for readability and collaboration.

### 4.1. C++ Coding Style

* Follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) 

### 4.2. Python Coding Style

* Adhere to [PEP 8](https://www.python.org/dev/peps/pep-0008/) for Python code.

### 4.3. Java Coding Style

* Follow the [Google Java Style Guide](https://google.github.io/styleguide/javaguide.html) 

### 4.4. Documentation Style

* **C++:** Use [Doxygen](https://www.doxygen.nl/manual/docblocks.html) style comments for C++ code.
* **Python:** Use [NumPy style](https://numpydoc.readthedocs.io/en/latest/format.html) docstrings for all Python functions, classes, and modules, as configured in `mkdocstrings`.

## 5. Documentation

Well-maintained documentation is crucial for user adoption and developer collaboration.

### 5.1. Building Local Documentation

To build the project website locally, use MkDocs. This typically starts a local development server, allowing you to preview changes.

### 5.2. Contributing to Documentation

* **Website Content:** Modifications to the project's website content are made by editing Markdown files within the `/docs/` directory.
* **Python API Docs:** Updates to Python API documentation are achieved by modifying docstrings directly within the Python code (or `pybind11` C++ files). These are automatically rendered by `mkdocstrings`.
* **C++ API Docs:** C++ API documentation is updated by adding or modifying Doxygen comments in the C++ header and source files.

### 5.3. Generating C++ Doxygen Documentation

Standalone C++ API documentation can be generated using Doxygen, provided a `Doxyfile` is correctly configured for your C++ source code.

## 6. Contribution Workflow

We welcome contributions and encourage developers to follow these guidelines:

1.  **Fork the Repository:** Create a personal fork of the OptiSim repository on the chosen Git platform.
2.  **Create a Feature Branch:** For each new feature or bug fix, create a new branch from the main development branch (e.g., `main` or `develop`).
3.  **Implement Changes:** Develop your code, ensuring adherence to the project's [Coding Guidelines](#4-coding-guidelines-and-style) and proper testing.
4.  **Test Your Changes:** Thoroughly run relevant unit and integration tests to validate your modifications.
5.  **Document Your Changes:** Update docstrings, inline comments, and relevant sections of user or developer guides to reflect your changes.
6.  **Commit Your Changes:** Provide clear, concise, and descriptive commit messages.
7.  **Push Your Branch:** Upload your local feature branch to your forked repository.
8.  **Create a Pull Request (PR):** Open a pull request from your branch to the main development branch of the central repository. Include a detailed description of your changes and reference any associated issues.
9.  **Address Feedback:** Actively participate in the code review process, addressing comments and making requested adjustments.

## 7. Logging

* **Logging:** Implement comprehensive logging mechanisms in both C++ and Python components to assist in tracing execution flow and identifying issues.