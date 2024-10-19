//
// Created by wangly on 2024/10/15.
//

#include "../../my_application/MyApplication.h"
#include <iostream>

int main() {
    MyApplication app;

    try {
        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
