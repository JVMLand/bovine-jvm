find_package(Python3 REQUIRED COMPONENTS Interpreter)
add_library(natives OBJECT)
target_link_libraries(natives PRIVATE vm)

function(add_classes_root DIRECTORY_NAME)
    file(GLOB_RECURSE CLASS_SOURCES CONFIGURE_DEPENDS "${DIRECTORY_NAME}/*.c")
    target_sources(natives PRIVATE ${CLASS_SOURCES})
    set(NATIVES_FILES ${NATIVES_FILES} ${CLASS_SOURCES} PARENT_SCOPE)
endfunction()

add_classes_root("share")

if (EMSCRIPTEN)
    add_classes_root("emscripten")
    target_compile_options(natives PRIVATE "-matomics")
endif ()

if (UNIX)
    add_classes_root("unix")
endif()

if (APPLE)
    add_classes_root("darwin")
endif()

list(JOIN NATIVES_FILES "\n" NATIVES_FILE_LIST)
set(native_file_list "${CMAKE_BINARY_DIR}/native-sources.txt")
file(GENERATE OUTPUT "${native_file_list}" CONTENT "${NATIVES_FILE_LIST}\n")
set(out_file "${CMAKE_BINARY_DIR}/natives_registration.c")
add_custom_command(
        OUTPUT  ${out_file}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/codegen/scan_native_declarations.py --file-list ${native_file_list} --output ${out_file}
        DEPENDS ${NATIVES_FILES} ${native_file_list} ${CMAKE_SOURCE_DIR}/codegen/scan_native_declarations.py
        COMMENT "Postprocessing natives files => ${out_file}"
        VERBATIM
)

add_custom_target(natives_registration_generate
        DEPENDS "${out_file}"
)

add_dependencies(natives natives_registration_generate)
target_sources(natives PRIVATE ${out_file})