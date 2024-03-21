import sys
import os
import subprocess

# コマンドライン引数からタイプを取得し、適切なTARGETを設定
arg = sys.argv[1]
_, type_value = arg.split('=')

if type_value == 'c':
    target = 'example_c'
elif type_value == 'cpp':
    target = 'example_cpp'
else:
    print("Invalid type. Please specify type=c or type=cpp.")
    sys.exit(0)

# buildディレクトリを削除し、再作成して移動
build_dir = "./build"
if os.path.exists(build_dir):
    subprocess.run(['rm', '-r', build_dir], check=True)
os.makedirs(build_dir)
os.chdir(build_dir)

# CMakeとninjaを使ってビルド
subprocess.run(['cmake', '..', '-G', 'Ninja'], check=True)
subprocess.run(['ninja', target], check=True)

# 元のディレクトリに戻る
os.chdir('..')

# ビルドしたプログラムを実行
subprocess.run([os.path.join(build_dir, target)])
