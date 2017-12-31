set(testLIBS
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

set(testINCLUDES
  )

add_unit_test("strong_typedef" "strong_typedef.cpp" "${testLIBS}" "${testINCLUDES}")
