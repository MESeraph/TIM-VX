add_subdirectory("benchmark_test")
if(${TIM_VX_ENABLE_CUSTOM_OP})
    add_subdirectory("custom_op_test")
    add_subdirectory("custom_lenet")
endif()

add_subdirectory("lenet")
if(${TIM_VX_ENABLE_VIPLITE})
    add_subdirectory("lenet_lite")
endif()

if(NOT ANDROID_TOOLCHAIN)
    add_subdirectory("multi_thread_test")
endif()

if(TIM_VX_ENABLE_NBG_PARSER)
    add_subdirectory("nbg_runner")
endif()

if(TIM_VX_ENABLE_PLATFORM)
    add_subdirectory("lenet_multi_device")
    add_subdirectory("multi_device")
endif()
