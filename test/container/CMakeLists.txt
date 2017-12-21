set(testLIBS
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

set(testINCLUDES
  )

add_unit_test(kary_heap kary_heap.cpp "${testLIBS}" "${testINCLUDES}")
