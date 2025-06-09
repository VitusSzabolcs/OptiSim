#!/bin/bash

cd ..
# C++
cd CPP
if [ ! -d "build" ]; then
  echo "Creating build directory..."
  mkdir build
else
  echo "Directory 'build' already exists."
fi
cd build
cmake ..
cmake --build .
cd ../..

# Python
cd Python
if [ ! -d "build" ]; then
  echo "Creating build directory..."
  mkdir build
else
  echo "Directory 'build' already exists."
fi
cd build
cmake ..
cmake --build .
cp optisim.cpython-312-x86_64-linux-gnu.so ..
cp optisim.cpython-312-x86_64-linux-gnu.so ../../examples
cd ../..

# Java
cd Java
javac ./optisim_java/*.java
jar cf optisim_java.jar ./optisim_java/*.class
cd ..

# Create .desktop launcher

echo "Creating desktop launcher..."

DESKTOP_FILE=~/Desktop/OptiSim.desktop
SCRIPT_DIR="$(dirname "$(realpath "$0")")"
PYTHON_PATH=$(which python3)
echo "$SCRIPT_DIR"
echo "$PYTHON_PATH"

cat > "$DESKTOP_FILE" <<EOF
[Desktop Entry]
Type=Application
Name=OptiSim
Exec=bash -c "cd $SCRIPT_DIR/Python && $PYTHON_PATH OptiSim.py"
Icon=$SCRIPT_DIR/Run/icon.png
Terminal=false
EOF

chmod +x "$DESKTOP_FILE"

echo "Launcher created at $DESKTOP_FILE"