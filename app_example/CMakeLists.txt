# Please refer to path/to/your/ameba_sdk/cmake/CMakeLists-template.cmake
set(private_sources)
ameba_list_append(private_sources app_main.c gpio_button_demo.c)
ameba_add_internal_library(app_example gpio_button_demo
    p_SOURCES
	    ${private_sources}
)
    