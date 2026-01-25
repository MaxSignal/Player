#include "bitmapfont_external.h"

#include <cstdint>
#include <string>
#include <string_view>

#include "filefinder.h"
#include "output.h"
#include "filesystem_stream.h"

namespace {
	constexpr const char* kMagic = "BMF1";
	constexpr std::size_t kMagicLen = 4;

	Filesystem_Stream::InputStream OpenMaybeTns(const std::string& path) {
		auto is = FileFinder::Root().OpenInputStream(path);
		if (is) return is;
		return FileFinder::Root().OpenInputStream(path + ".tns");
	}

	bool LoadBmf(const std::string& path, std::vector<BitmapFontGlyph>& out) {
		auto is = OpenMaybeTns(path);
        Output::Debug("BMF open try: {}", path);
		if (!is) {
            Output::Warning("BMF open FAILED: {}", path);
			return false;
		}

		char magic[kMagicLen] = {};
		is.read(magic, static_cast<std::streamsize>(kMagicLen));
		if (!is || std::string_view(magic, kMagicLen) != std::string_view(kMagic, kMagicLen)) {
			Output::Warning("Invalid BMF header: {}", path);
			return false;
		}

		uint32_t count = 0;
		is.read(reinterpret_cast<char*>(&count), sizeof(count));
		if (!is) {
			return false;
		}

		// File format is little-endian:
		//   u16 code, u8 is_full, u8 pad, u16 data[12]
		out.clear();
		out.reserve(count);

		for (uint32_t i = 0; i < count; ++i) {
			BitmapFontGlyph g{};
			uint16_t code = 0;
			uint8_t is_full = 0;
			uint8_t pad = 0;

			is.read(reinterpret_cast<char*>(&code), sizeof(code));
			is.read(reinterpret_cast<char*>(&is_full), sizeof(is_full));
			is.read(reinterpret_cast<char*>(&pad), sizeof(pad));
			(void)pad;

			for (int j = 0; j < 12; ++j) {
				is.read(reinterpret_cast<char*>(&g.data[j]), sizeof(g.data[j]));
			}

			if (!is) {
				out.clear();
				return false;
			}

			g.code = code;
			g.is_full = (is_full != 0);
			out.push_back(g);
		}

		return true;
	}

	template <typename Loader>
	const std::vector<BitmapFontGlyph>& GetOnce(std::vector<BitmapFontGlyph>& cache, bool& loaded, Loader&& loader) {
		if (!loaded) {
			loaded = true;
			if (!loader()) {
				cache.clear();
			}
		}
		return cache;
	}

	// Default directory for external bitmap fonts.
	// Put files here (or with an additional .tns suffix on Nspire):
	//   /documents/easyrpg-player/fonts/shinonome_gothic.bmf
	constexpr const char* kDir = "/documents/easyrpg-player/fonts/";

	std::vector<BitmapFontGlyph> g_shino_g;
	std::vector<BitmapFontGlyph> g_shino_m;
	std::vector<BitmapFontGlyph> g_rmg2000;
	std::vector<BitmapFontGlyph> g_ttyp0;
	std::vector<BitmapFontGlyph> g_wqy;

	bool l_shino_g = false;
	bool l_shino_m = false;
	bool l_rmg2000 = false;
	bool l_ttyp0 = false;
	bool l_wqy = false;

	std::string Path(const char* leaf) {
		return std::string(kDir) + leaf;
	}
}

namespace BitmapFontExternal {
	const std::vector<BitmapFontGlyph>& ShinonomeGothic() {
		return GetOnce(g_shino_g, l_shino_g, [] { return LoadBmf(Path("shinonome_gothic.bmf"), g_shino_g); });
	}

	const std::vector<BitmapFontGlyph>& ShinonomeMincho() {
		return GetOnce(g_shino_m, l_shino_m, [] { return LoadBmf(Path("shinonome_mincho.bmf"), g_shino_m); });
	}

	const std::vector<BitmapFontGlyph>& Rmg2000() {
		return GetOnce(g_rmg2000, l_rmg2000, [] { return LoadBmf(Path("rmg2000.bmf"), g_rmg2000); });
	}

	const std::vector<BitmapFontGlyph>& Ttyp0() {
		return GetOnce(g_ttyp0, l_ttyp0, [] { return LoadBmf(Path("ttyp0.bmf"), g_ttyp0); });
	}

	const std::vector<BitmapFontGlyph>& Wqy() {
		return GetOnce(g_wqy, l_wqy, [] { return LoadBmf(Path("wqy.bmf"), g_wqy); });
	}
}
