#!/usr/bin/env bash
set -euo pipefail

packages=(
    qt6-base-dev
    qt6-declarative-dev
    qml6-module-qtquick
    qml6-module-qtquick-controls
    qml6-module-qtquick-layouts
    qml6-module-qtquick-templates
    qml6-module-qtquick-window
    qml6-module-qtqml-workerscript
)

echo "Updating package index..."
sudo apt-get update -qq

echo "Installing Qt 6 runtime and development packages..."
sudo apt-get install -y "${packages[@]}"

echo "Qt 6 dependencies installed successfully."
