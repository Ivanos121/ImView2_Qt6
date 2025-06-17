#!/bin/bash
VERSION_FILE="../ImView/version_hash.h"

GIT_HASH=$(git -C "$(pwd)" rev-parse --short HEAD)

echo "#define GIT_HASH \"$GIT_HASH\"" > "$VERSION_FILE"
