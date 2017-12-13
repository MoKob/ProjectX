set(testLIBS
  Xgraph
  Xio
  Xlogging
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

set(testINCLUDES
  )

add_unit_test(graph graph.cpp "${testLIBS}" "${testINCLUDES}")
add_unit_test(conversion conversion.cpp "${testLIBS}" "${testINCLUDES}")
