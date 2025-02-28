#include "common.h"
#include "window.h"
#include "input.h"
#include "solver.h"

int main(int argc, char* argv[]) {
    init_window();
    while(1) {
        if(!process_input()) break;
        update_camera();
        draw();
        integration_step(implicit_trapezoidal_step, 0.001);
    }
    deinit_window();
    return 0;
}