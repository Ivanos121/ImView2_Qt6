#!/bin/bash

echo "Current dir: $(pwd)"

VERSION_FILE="/home/elf/ImView2_Qt6/ImView/version.h"

# Получить текущий номер сборки
CURRENT_BUILD=$(grep '#define APP_BUILD_NUMBER' "$VERSION_FILE" | awk '{print $3}')

# Увеличить его на 1
NEW_BUILD=$((CURRENT_BUILD + 1))

# Обновить файл version.h
sed -i "s/#define APP_BUILD_NUMBER $CURRENT_BUILD/#define APP_BUILD_NUMBER $NEW_BUILD/" "$VERSION_FILE"
