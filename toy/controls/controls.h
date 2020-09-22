#pragma once
#include "../track_ball.h"
#include "../../support/GLFW/include/GLFW/glfw3.h"
namespace toy {
    static void scrollCallback(GLFWwindow* window, double xscroll, double yscroll)
    {
        std::cerr << "yscroll: " << yscroll << ",xscroll: " << xscroll << "\n";
        if (trackball.wheelEvent((int)yscroll))
            camera_changed = true;
    }
}