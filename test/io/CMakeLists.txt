set(testLIBS
  Xio
  Xlogging
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

set(testINCLUDES
  )

add_unit_test("file" "file.cpp" "${testLIBS}" "${testINCLUDES}")
