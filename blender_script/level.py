import bpy

# 出力するファイル名を指定
output_filename = "D:/document/GitHub/Project_First_3DGame/Project_First_3DGame/object_properties.csv"

# ヘッダー行を作成
header = "\n"#"object_name,x,y,z,rotation_x,rotation_y,rotation_z,scale_x,scale_y,scale_z\n"

# 出力用の文字列を作成
output_string = header
for obj in bpy.data.objects:
    # 名前と座標、回転、大きさを取得
    name = obj.name
    x, y, z = obj.location
    rotation_x, rotation_y, rotation_z = obj.rotation_euler
    rotation_x -= 1.570796
    scale_x, scale_y, scale_z = obj.scale
    
    #親に設定されているオブジェクトの情報を考慮する
    parent_obj = obj.parent
    if parent_obj != None:
        px, py, pz = parent_obj.location
        rotation_px, rotation_py, rotation_pz = obj.rotation_euler
        rotation_px -= 1.570796
        scale_px, scale_py, scale_pz = obj.scale
        x+=px
        y+=py
        z+=pz
        rotation_x = rotation_px
        rotation_y = rotation_py
        rotation_z = rotation_pz
        scale_x *= scale_px
        scale_y *= scale_py
        scale_z *= scale_pz
    
    
    # CSV の 1 行分の文字列を作成
    line = f"{name},{x},{z},{y},{rotation_x},{rotation_z},{rotation_y},{scale_x},{scale_y},{scale_z}\n"
    # 出力用の文字列に追加
    output_string += line

# ファイルを開いて、出力用の文字列を書き込む
with open(output_filename, "w",encoding = 'shift_jis') as f:
    f.write(output_string)