add_library(tiva_utils
            peripheral_utils.cpp
            pin_utils.cpp
            pwm_utils.cpp
            general_timer.cpp)
target_include_directories(tiva_utils PUBLIC .)
