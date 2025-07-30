 #!/bin/bash

MODE=$1

set -e  # エラーで即終了（トラブルを早期発見）




parent_dir_name=$(basename $(dirname $(pwd)))

if [ "$MODE" != "make" ]; then
  echo "🔄 Cleaning and configuring project..."
  rm -rf obj
  mkdir obj
  cd obj

  echo "⚙️  Running configure.rb..."
  ruby /home/tenma/EmbededPractice/TOPPERS_PROJECTS/asp3/configure.rb -T nucleo_f401re_gcc -a "../${parent_dir_name}_src" -A "${parent_dir_name}"
else
  echo "➡️ Skipping configure. Moving to obj/ and starting make..."
  cd obj
fi

echo "🔨 Building project..."
make
make asp.bin

echo "📦 Copying asp.bin to Windows..."


st-flash --connect-under-reset write  asp.bin 0x08000000

# WIN_DIR=/mnt/c/Users/tenma/Desktop/STM32BUILDER

# # フォルダがなければ作成
# if [ ! -d "$WIN_DIR" ]; then
#   echo "📁 Windowsフォルダが存在しないため作成中: $WIN_DIR"
#   mkdir -p "$WIN_DIR"
# fi

# # ファイルコピー
# cp asp.bin "$WIN_DIR"
# echo "✅ asp.bin copied to $WIN_DIR"

# echo "📤 Uploading asp.bin to STM32F401RE..."
# "/mnt/c/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe" \
#   -c port=SWD mode=UR \
#   -d C:\\Users\\tenma\\Desktop\\STM32BUILDER\\asp.bin 0x08000000 \
#   -rst
