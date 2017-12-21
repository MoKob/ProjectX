set(testLIBS
  Xgraph
  Xalgorithm
  Xlogging
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

set(testINCLUDES
  )

add_unit_test(scc scc.cpp "${testLIBS}" "${testINCLUDES}")
add_unit_test(dijkstra dijkstra.cpp "${testLIBS}" "${testINCLUDES}")
