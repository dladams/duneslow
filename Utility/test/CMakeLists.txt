# duneslow/Utility/test/CMakeLists.txt

# Test for utiltity.
add_executable(test_DuneSlowData test_DuneSlowData.cxx)
target_link_libraries(test_DuneSlowData ${PKGLIB})
install(TARGETS test_DuneSlowData DESTINATION test)

# Test for dictionary.
install(FILES test_dict_DuneSlowData.C DESTINATION test)
