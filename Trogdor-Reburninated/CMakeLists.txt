cmake_minimum_required(VERSION 3.2)
project(trogdorbeta CXX)

add_executable(trogdorbeta
	"src/main.cpp"
	"src/main.h"
	"src/classes.h"
	"src/config.cpp"
	"src/config.h"
	"src/general.cpp"
	"src/general.h"
	"src/include.h"
	"src/input.h"
	"src/level_data.h"
	"src/media_objects_init.cpp"
	"src/media_objects_init.h"
	"src/sound_logic.cpp"
	"src/sound_logic.h"
	"src/sprite_objects.cpp"
	"src/sprite_objects.h"
	"src/text_objects.cpp"
	"src/text_objects.h"
	"src/window.cpp"
	"src/window.h"
)

if (WIIU)
	include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)
	find_package(PkgConfig REQUIRED)
	add_definitions(-DWII_U)

	target_link_libraries(trogdorbeta -L${DEVKITPRO}/portlibs/wiiu/lib -L${DEVKITPRO}/portlibs/ppc/lib -L${DEVKITPRO}/wut/lib)
	# target_link_libraries(trogdorbeta -lSDL2_ttf -lSDL2_mixer -lmodplug -lvorbisfile -lvorbis -logg -lSDL2_gfx -lSDL2_image -lSDL2 -lfreetype -lpng -lmpg123 -lbz2 -ljpeg -lz -lwut)
	pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET SDL2)
	pkg_check_modules(SDL2_image REQUIRED IMPORTED_TARGET SDL2_image)
	pkg_check_modules(SDL2_mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
	pkg_check_modules(SDL2_ttf REQUIRED IMPORTED_TARGET SDL2_ttf)
	pkg_check_modules(SDL2_gfx REQUIRED IMPORTED_TARGET SDL2_gfx)
	target_link_libraries(trogdorbeta PkgConfig::SDL2 PkgConfig::SDL2_image PkgConfig::SDL2_mixer PkgConfig::SDL2_ttf PkgConfig::SDL2_gfx)

	set(SDL2_INCLUDE_DIRS
	"${DEVKITPRO}/portlibs/wiiu/include/SDL2;\
	${DEVKITPRO}/portlibs/ppc/include;\
	${DEVKITPRO}/wut/include;\
	${DEVKITPRO}/devkitPPC/powerpc-eabi/include;"
	)
	include_directories(${SDL2_INCLUDE_DIRS})

	wut_create_rpx(trogdorbeta)

	install(FILES "${CMAKE_CURRENT_BINARY_DIR}/trogdorbeta.rpx"
			DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()

if (VITA)
	include("${VITASDK}/share/vita.cmake" REQUIRED)
	# find_package(PkgConfig REQUIRED)
	add_definitions(-DVITA)
	
	set(VITA_APP_NAME "Trogdor Beta")
	set(VITA_TITLEID  "TROG23820")
	set(VITA_VERSION  "01.00")

	target_link_libraries(trogdorbeta SDL2_ttf SDL2_mixer SDL2_image SDL2_gfx SDL2 freetype png png16 bz2 jpeg z mikmod mpg123 FLAC vorbisfile vorbis ogg webp pthread)
	# find_package(SDL2 REQUIRED)
	# target_link_libraries(trogdorbeta SDL2_ttf SDL2_mixer SDL2_image SDL2_gfx SDL2)
	target_link_libraries(trogdorbeta
		SceDisplay_stub
		SceCtrl_stub
		SceAudio_stub
		SceSysmodule_stub
		SceGxm_stub
		SceCommonDialog_stub
		SceAppMgr_stub
		SceTouch_stub
		SceMotion_stub
		SceHid_stub
		m
	)

	include_directories("${VITASDK}/arm-vita-eabi/include;${VITASDK}/arm-vita-eabi/include/SDL2;")

	vita_create_self(trogdorbeta.self trogdorbeta)
	vita_create_vpk(trogdorbeta.vpk ${VITA_TITLEID} trogdorbeta.self
		VERSION ${VITA_VERSION}
		NAME ${VITA_APP_NAME}
		FILE release-resources/logo_icon_vita.png sce_sys/icon0.png
		FILE release-resources/background_vita.png sce_sys/livearea/contents/bg.png
		FILE release-resources/logo_startup_vita.png sce_sys/livearea/contents/startup.png
		FILE release-resources/template_vita.xml sce_sys/livearea/contents/template.xml
	)
endif()

unset(WIIU CACHE)
unset(VITA CACHE)