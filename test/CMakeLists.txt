macro(add_unit_test target source libs includes)
    add_executable("${target}" ${source})

    target_link_libraries("${target}"
        ${libs}
        ${MAYBE_COVERAGE_LIBRARIES})

    target_include_directories("${target}" SYSTEM PUBLIC
          ${includes})

    add_test(NAME "${target}"
             COMMAND "${target}"
             WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endmacro()

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK) 

add_subdirectory(graph)
