

SET(SRC_APPLICATION

		# Menu
		application/recentfiles.h
		application/recentfiles.cpp
		application/menus.h application/menus.cpp

		application/main/fwd.h
		application/main/cleaner.cpp
		application/main/events.cpp
		application/main/events.file.cpp
		application/main/events.edit.cpp
		application/main/events.simulation.cpp

		application/main/paste-from-clipboard.cpp

		application/main/internal-data.h
		application/main/internal-ids.h
		application/main/internal-data.cpp
		application/main/help.cpp
		application/main/processevent.cpp
		application/main/menu.cpp
		application/main/refresh.cpp
		application/main/notes.cpp
		application/main/clean-swap-files.cpp
		application/main/options.cpp
		application/main/analyzer.cpp
		application/main/constraintsbuilder.cpp
		application/main/main.h
		application/main/main.hxx
		application/main/disabler.h
		application/main/main.cpp
		application/main/create.cpp
		application/main/check-license-at-startup.hxx
		application/main/drag-drop.hxx
		application/main/wip.cpp
		application/main/statusbar.cpp
		application/main/build/standard-page.hxx
		application/main/build/load.cpp
		application/main/build/solar.cpp
		application/main/build/wind.cpp
		application/main/build/hydro.cpp
		application/main/build/notes.cpp
		application/main/build/sets.cpp
		application/main/build/economic-optimization.cpp
		application/main/build/scenario-builder.cpp
		application/main/logs.cpp
		application/wait.h
		application/wait.cpp
		application/main.h

		# Application
		application/application.h
		application/application.cpp
		application/study.h
		application/study.cpp

		# The main
		../common/winmain.hxx
		main.cpp
)



add_library(libantares-ui-application
	${SRC_APPLICATION})

target_link_libraries(libantares-ui-application PRIVATE ${wxWidgets_LIBRARIES})
target_link_libraries(libantares-ui-application PRIVATE libantares-ui-common)

