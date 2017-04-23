#include <emscripten/bind.h>
#include <xlnt/xlnt.hpp>

void run()
{
    xlnt::workbook wb;
    std::vector<std::uint8_t> bytes;
    wb.save(bytes);
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("run", &run);
}
