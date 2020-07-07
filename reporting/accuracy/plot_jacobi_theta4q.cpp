
#include <iostream>
#include <boost/math/tools/ulps_plot.hpp>
#include <boost/core/demangle.hpp>
#include <boost/math/special_functions/jacobi_theta.hpp>

using boost::math::tools::ulps_plot;

int main() {
    using PreciseReal = long double; // boost::multiprecision::float128;
    using CoarseReal = double;

    auto jacobi_theta_coarse = [](CoarseReal q) {
        return boost::math::jacobi_theta4<CoarseReal>(0.0, q);
    };
    auto jacobi_theta_precise = [](PreciseReal q) {
        return boost::math::jacobi_theta4<PreciseReal>(0.0, q);
    };

    std::string filename = "jacobi_theta4q_" + boost::core::demangle(typeid(CoarseReal).name()) + ".svg";
    int samples = 2500;
    int width = 1100;
    PreciseReal clip = 100;
    auto plot = ulps_plot<decltype(jacobi_theta_precise), PreciseReal, CoarseReal>(jacobi_theta_precise, CoarseReal(0), CoarseReal(0.9999999), samples);
    plot.clip(clip).width(width);
    std::string title = "jacobi_theta4q ULP plot at " + boost::core::demangle(typeid(CoarseReal).name()) + " precision";
    //plot.title(title);
    plot.vertical_lines(10);
    plot.add_fn(jacobi_theta_coarse);
    plot.write(filename);
}
