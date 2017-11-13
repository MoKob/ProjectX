set(testLIBS
  Xgraph
  Xio
  Xlogging
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

set(testINCLUDES
  )

add_unit_test(forward_star forward_star.cpp "${testLIBS}" "${testINCLUDES}")
add_unit_test(routing routing.cpp "${testLIBS}" "${testINCLUDES}")
add_unit_test(decorator decorator.cpp "${testLIBS}" "${testINCLUDES}")
