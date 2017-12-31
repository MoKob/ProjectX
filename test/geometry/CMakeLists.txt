set(testLIBS
  Xgeometry
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

set(testINCLUDES
  )

add_unit_test(coordinate coordinate.cpp "${testLIBS}" "${testINCLUDES}")
add_unit_test(projection projection.cpp "${testLIBS}" "${testINCLUDES}")
