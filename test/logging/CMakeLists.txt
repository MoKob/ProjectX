set(testLIBS
  Xlogging
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

set(testINCLUDES
  )

add_unit_test(logging logging.cpp "${testLIBS}" "${testINCLUDES}")
