echo $1

# プロジェクトディレクトリを作成
cp -r ./template ./$1
FOLDER=$1
# $2以降の引数を処理
shift
for filename in "$@"; do
    if [ -n "$filename" ]; then
        cp ./template/src/main.c ./$FOLDER/src/$filename.c
        echo "作成: $filename.c"
    fi
done