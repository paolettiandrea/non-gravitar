target_include_directories(non_gravitar PRIVATE .)

target_sources(non_gravitar PRIVATE

        CircularGradient.cpp
        CircularGradient.hpp

        EllipticGradient.cpp
        EllipticGradient.hpp

        Gradient.cpp
        Gradient.hpp

        ../../../../lib/SGE/include/SGE/utils/interpolation/Interpolator.cpp
        ../../../../lib/SGE/include/SGE/utils/interpolation/Interpolator.hpp
        )