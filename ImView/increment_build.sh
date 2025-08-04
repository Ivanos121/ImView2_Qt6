#!/bin/bash
echo "Running update_version.sh" >&2
VERSION_FILE="version_hash.h"

GIT_HASH=$(git -C "$(pwd)" rev-parse --short HEAD)

echo "#define GIT_HASH \"$GIT_HASH\"" > "$VERSION_FILE"
