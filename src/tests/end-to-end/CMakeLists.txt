#bigobj support needed for windows compilation
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif(MSVC)

add_executable(tests-simple-study
			simple-study.cpp)

target_link_libraries(tests-simple-study
						PRIVATE
						libantares-core
						libantares-solver-main-economy
						libantares-solver-main-adequacy-draft
						libantares-solver-main-adequacy
						libantares-solver-hydro
						libantares-solver-aleatoire
						libantares-solver-variable
						libantares-solver-simulation
						libantares-solver-ts-generator
						Boost::unit_test_framework
			)
			
target_include_directories(tests-simple-study
							PRIVATE
							${CMAKE_SOURCE_DIR}/solver
							)

add_test(NAME end-to-end-simple-study COMMAND tests-simple-study)

# Storing tests-simple-study under the folder Unit-tests in the IDE
set_target_properties(tests-simple-study PROPERTIES FOLDER Unit-tests)


