#ifndef EP_BITMAPFONT_EXTERNAL_H
#define EP_BITMAPFONT_EXTERNAL_H

#include <vector>
#include "bitmapfont_glyph.h"

namespace BitmapFontExternal {
	// Lazy-loaded bitmap font glyphsets from external *.bmf files.
	// If a font file is missing, the returned vector is empty.
	const std::vector<BitmapFontGlyph>& ShinonomeGothic();
	const std::vector<BitmapFontGlyph>& ShinonomeMincho();
	const std::vector<BitmapFontGlyph>& Rmg2000();
	const std::vector<BitmapFontGlyph>& Ttyp0();
	const std::vector<BitmapFontGlyph>& Wqy();
}

#endif // EP_BITMAPFONT_EXTERNAL_H
