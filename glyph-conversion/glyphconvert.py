import bdfparser
import kanji_lists
font = bdfparser.Font("unifont_jp-15.0.06.bdf")

def make_glyph_file(char: str):
    glyph = font.glyph(char)
    bitmap = glyph.draw(1)
    with open(f"glyphs/{ord(char)}.glyph", "wb") as f:
        f.write(bytes([bitmap.width(), bitmap.height()]))
        if bitmap.width() == 8:
            f.write(bytes(int(x, 16) for x in glyph.meta["hexdata"]))
        else:
            for i in range(bitmap.height()):
                f.write(bytes((int(glyph.meta["hexdata"][i][:2], 16), int(glyph.meta["hexdata"][i][2:], 16))))

for i in kanji_lists.JOYO:
    make_glyph_file(i)