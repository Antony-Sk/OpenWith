#include "api.h"

int main() {
    // For Demo purposes: registering pluma for .txt extension files
    ow::register_handler("txt", "/usr/bin/pluma", {});
    return 1;
}
