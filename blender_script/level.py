import bpy

# 出力するファイル名を指定
output_filename = "object_properties.csv"

# ヘッダー行を作成
header = "object_name,x,y,z,rotation_x,rotation_y,rotation_z,scale_x,scale_y,scale_z\n"

# 出力用の文字列を作成
output_string = header
for obj in bpy.data.objects:
    # 名前と座標、回転、大きさを取得
    name = obj.name
    x, y, z = obj.location
    rotation_x, rotation_y, rotation_z = obj.rotation_euler
    scale_x, scale_y, scale_z = obj.scale
    # CSV の 1 行分の文字列を作成
    line = f"{name},{x},{y},{z},{rotation_x},{rotation_y},{rotation_z},{scale_x},{scale_y},{scale_z}\n"
    # 出力用の文字列に追加
    output_string += line

# ファイルを開いて、出力用の文字列を書き込む
with open(output_filename, "w") as f:
    f.write(output_string)