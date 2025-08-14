#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
echo "このファイルの存在するパス: $SCRIPT_DIR"

SCRIPT_PATH="$SCRIPT_DIR/$(basename "${BASH_SOURCE[0]}")"
echo "このファイルの完全パス: $SCRIPT_PATH"

# reset.sh と Makefile を除く、すべてのファイル・ディレクトリを削除
find "$SCRIPT_DIR" -mindepth 1 -maxdepth 1 \
    ! -name "reset.sh" \
    ! -name "Makefile" \
    -exec rm -rf {} \;

# objsディレクトリがなければ再作成
if [ ! -d "$SCRIPT_DIR/objs" ]; then
    mkdir "$SCRIPT_DIR/objs"
    echo "objsディレクトリを作成しました"
else
    echo "objsディレクトリは既に存在します"
fi
