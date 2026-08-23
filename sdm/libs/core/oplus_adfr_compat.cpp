/*
 * Compat shim for newer OnePlus vendor blobs.
 *
 * libsdmclient.so from recent OOS builds references two data symbols that the
 * oplus-patched sdm core exports for ADFR (adaptive display frame rate) panel
 * mode selection:
 *     sdm::g_oplus_adfr_panel_modes
 *     sdm::g_oplus_adfr_panel_modes_size
 *
 * Our core is built from CAF sources which have no such globals, and data
 * symbols are bound eagerly at load time -- leaving them undefined would make
 * hwcomposer's dlopen(libsdmclient) fail on device. Define them here with a
 * zero-size mode table: the linker requirement is satisfied and the blob sees
 * an empty panel-mode list (ADFR stays inert) instead of failing to load.
 * If real ADFR support is ported later, replace this file.
 */

namespace sdm {

// Element layout is opaque to us; consumers index it by g_oplus_adfr_panel_modes_size,
// so an empty table is safe regardless of the true element type.
// visibility("default"): some display defaults build with -fvisibility=hidden;
// without this the symbols never reach .dynsym and libsdmclient still fails.
__attribute__((visibility("default"), used))
unsigned char g_oplus_adfr_panel_modes[1] = {0};
__attribute__((visibility("default"), used))
unsigned int g_oplus_adfr_panel_modes_size = 0;

}  // namespace sdm
