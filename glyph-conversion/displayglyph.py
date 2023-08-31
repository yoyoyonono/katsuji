import os

for filename in os.listdir("glyphs"):
    with open(os.path.join("glyphs", filename), "rb") as glyph:
        width = int(int.from_bytes(glyph.read(1), "little")/8)
        height = int.from_bytes(glyph.read(1), "little")
        print(width, height)
        for i in range(height):
            print(format(int.from_bytes(glyph.read(width), "big"), "0" + str(width*8 + 2) + "b").replace('0', ' ').replace('1', '■'))