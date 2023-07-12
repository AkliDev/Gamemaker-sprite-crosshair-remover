file(GLOB_RECURSE SRC CONFIGURE_DEPENDS 
	src/*.cpp 
	src/*.h
)

add_executable(CrosshairDestroyer ${SRC})

# Create the source groups for source tree with root at CMAKE_CURRENT_SOURCE_DIR.
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC})

set_target_properties(CrosshairDestroyer PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/CrosshairDestroyer)
set_target_properties(CrosshairDestroyer PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/CrosshairDestroyer)

#External includes
target_include_directories(CrosshairDestroyer PRIVATE
	src	
	Vendor/opencv/include	
)

#External links
target_link_libraries(CrosshairDestroyer PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Vendor/opencv/x64/vc16/lib/opencv_world480d.lib
)

add_custom_command(TARGET CrosshairDestroyer POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	${CMAKE_CURRENT_SOURCE_DIR}/Vendor/opencv/x64/vc16/bin/opencv_world480d.dll       
	$<TARGET_FILE_DIR:CrosshairDestroyer>
)

target_compile_definitions(CrosshairDestroyer PRIVATE _CRT_SECURE_NO_WARNINGS)
target_compile_definitions(CrosshairDestroyer PRIVATE $<$<CONFIG:DEBUG>:DEBUG>)
target_compile_definitions(CrosshairDestroyer PRIVATE $<$<CONFIG:RELEASE>:RELEASE>)