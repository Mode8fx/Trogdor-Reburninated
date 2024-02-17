cmake_minimum_required(VERSION 3.2)
project(trogdorrb CXX)

add_executable(trogdorrb
	"src/main.cpp"
	"src/main.h"
	"src/classes.cpp"
	"src/classes.h"
	"src/config.cpp"
	"src/config.h"
	"src/cutscenes.cpp"
	"src/cutscenes.h"
	"src/general.cpp"
	"src/general.h"
	"src/include.h"
	"src/input.cpp"
	"src/input.h"
	"src/level_data.h"
	"src/media_objects_init.cpp"
	"src/media_objects_init.h"
	"src/menu.cpp"
	"src/menu.h"
	"src/on_open_and_close.cpp"
	"src/on_open_and_close.h"
	"src/sound_logic.cpp"
	"src/sound_logic.h"
	"src/sprite_objects.cpp"
	"src/sprite_objects.h"
	"src/text_objects.cpp"
	"src/text_objects.h"
	"src/window.cpp"
	"src/window.h"
	"src/fonts_h/29_NOKIA_5110_FontSet.cpp"
	"src/fonts_h/29_NOKIA_5110_FontSet.h"
	"src/fonts_h/Commodore_Pixelized_v1_2.cpp"
	"src/fonts_h/Commodore_Pixelized_v1_2.h"
	"src/fonts_h/serif_v01.cpp"
	"src/fonts_h/serif_v01.h"
	"src/graphics_h/archer.cpp"
	"src/graphics_h/archer.h"
	"src/graphics_h/arrow.cpp"
	"src/graphics_h/arrow.h"
	"src/graphics_h/arrow_funnyjoke.cpp"
	"src/graphics_h/arrow_funnyjoke.h"
	"src/graphics_h/backgrounds"
	"src/graphics_h/bm_empty.cpp"
	"src/graphics_h/bm_empty.h"
	"src/graphics_h/bm_full.cpp"
	"src/graphics_h/bm_full.h"
	"src/graphics_h/burninate_message_fire.cpp"
	"src/graphics_h/burninate_message_fire.h"
	"src/graphics_h/burninate_text.cpp"
	"src/graphics_h/burninate_text.h"
	"src/graphics_h/cottage.cpp"
	"src/graphics_h/cottage.h"
	"src/graphics_h/cottage_fire.cpp"
	"src/graphics_h/cottage_fire.h"
	"src/graphics_h/death_message.cpp"
	"src/graphics_h/death_message.h"
	"src/graphics_h/end_of_level_flash.cpp"
	"src/graphics_h/end_of_level_flash.h"
	"src/graphics_h/end_of_level_trogdor.cpp"
	"src/graphics_h/end_of_level_trogdor.h"
	"src/graphics_h/game_over_banner.cpp"
	"src/graphics_h/game_over_banner.h"
	"src/graphics_h/game_over_text.cpp"
	"src/graphics_h/game_over_text.h"
	"src/graphics_h/game_over_trogdor.cpp"
	"src/graphics_h/game_over_trogdor.h"
	"src/graphics_h/heart.cpp"
	"src/graphics_h/heart.h"
	"src/graphics_h/jonathan_howe.cpp"
	"src/graphics_h/jonathan_howe.h"
	"src/graphics_h/kerrek.cpp"
	"src/graphics_h/kerrek.h"
	"src/graphics_h/kerrek_smoked.cpp"
	"src/graphics_h/kerrek_smoked.h"
	"src/graphics_h/knight.cpp"
	"src/graphics_h/knight.h"
	"src/graphics_h/knight_funnyjoke.cpp"
	"src/graphics_h/knight_funnyjoke.h"
	"src/graphics_h/level_beaten_smoke.cpp"
	"src/graphics_h/level_beaten_smoke.h"
	"src/graphics_h/level_beaten_trogdor_scaled.cpp"
	"src/graphics_h/level_beaten_trogdor_scaled.h"
	"src/graphics_h/loot.cpp"
	"src/graphics_h/loot.h"
	"src/graphics_h/menu_cursor.cpp"
	"src/graphics_h/menu_cursor.h"
	"src/graphics_h/options_menu.cpp"
	"src/graphics_h/options_menu.h"
	"src/graphics_h/overlays"
	"src/graphics_h/peasant.cpp"
	"src/graphics_h/peasant.h"
	"src/graphics_h/peasantometer.cpp"
	"src/graphics_h/peasantometer.h"
	"src/graphics_h/strong_bad.cpp"
	"src/graphics_h/strong_bad.h"
	"src/graphics_h/strong_bad_ending.cpp"
	"src/graphics_h/strong_bad_ending.h"
	"src/graphics_h/title_screen.cpp"
	"src/graphics_h/title_screen.h"
	"src/graphics_h/trogdor.cpp"
	"src/graphics_h/trogdor.h"
	"src/graphics_h/trogdor_bighead.cpp"
	"src/graphics_h/trogdor_bighead.h"
	"src/graphics_h/trogdor_dead.cpp"
	"src/graphics_h/trogdor_dead.h"
	"src/graphics_h/trogdor_ending.cpp"
	"src/graphics_h/trogdor_ending.h"
	"src/graphics_h/trogdor_fire.cpp"
	"src/graphics_h/trogdor_fire.h"
	"src/graphics_h/trogdor_flexing.cpp"
	"src/graphics_h/trogdor_flexing.h"
	"src/graphics_h/trogdor_logo.cpp"
	"src/graphics_h/trogdor_logo.h"
	"src/graphics_h/videlectrix_logo_big.cpp"
	"src/graphics_h/videlectrix_logo_big.h"
	"src/graphics_h/backgrounds/bg_1.cpp"
	"src/graphics_h/backgrounds/bg_1.h"
	"src/graphics_h/backgrounds/bg_2.cpp"
	"src/graphics_h/backgrounds/bg_2.h"
	"src/graphics_h/backgrounds/bg_3.cpp"
	"src/graphics_h/backgrounds/bg_3.h"
	"src/graphics_h/backgrounds/bg_4.cpp"
	"src/graphics_h/backgrounds/bg_4.h"
	"src/graphics_h/backgrounds/bg_treasure_hut.cpp"
	"src/graphics_h/backgrounds/bg_treasure_hut.h"
	"src/graphics_h/overlays/basement_bottom.cpp"
	"src/graphics_h/overlays/basement_bottom.h"
	"src/graphics_h/overlays/basement_left.cpp"
	"src/graphics_h/overlays/basement_left.h"
	"src/graphics_h/overlays/basement_right.cpp"
	"src/graphics_h/overlays/basement_right.h"
	"src/graphics_h/overlays/basement_top.cpp"
	"src/graphics_h/overlays/basement_top.h"
)
find_package(PkgConfig REQUIRED)

if (WIIU)
	include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)
	add_definitions(-DWII_U)

	target_link_libraries(trogdorrb -L${DEVKITPRO}/portlibs/wiiu/lib -L${DEVKITPRO}/portlibs/ppc/lib -L${DEVKITPRO}/wut/lib)
	pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET SDL2)
	pkg_check_modules(SDL2_image REQUIRED IMPORTED_TARGET SDL2_image)
	pkg_check_modules(SDL2_mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
	pkg_check_modules(SDL2_ttf REQUIRED IMPORTED_TARGET SDL2_ttf)
	pkg_check_modules(SDL2_gfx REQUIRED IMPORTED_TARGET SDL2_gfx)
	# target_link_libraries(trogdorrb PkgConfig::SDL2 PkgConfig::SDL2_image PkgConfig::SDL2_mixer PkgConfig::SDL2_ttf PkgConfig::SDL2_gfx)
	target_link_libraries(trogdorrb -lSDL2_ttf -lSDL2_mixer -lmodplug -lvorbisfile -lvorbis -logg -lSDL2_gfx -lSDL2_image -lSDL2 -lfreetype -lpng -lmpg123 -lbz2 -ljpeg -lz -lwut)

	set(SDL2_INCLUDE_DIRS
	"${DEVKITPRO}/portlibs/wiiu/include/SDL2;\
	${DEVKITPRO}/portlibs/ppc/include;\
	${DEVKITPRO}/wut/include;\
	${DEVKITPRO}/devkitPPC/powerpc-eabi/include;"
	)
	include_directories(${SDL2_INCLUDE_DIRS})

	wut_create_rpx(trogdorrb)

	install(FILES "${CMAKE_CURRENT_BINARY_DIR}/trogdorrb.rpx"
			DESTINATION "${CMAKE_INSTALL_PREFIX}")

elseif (VITA)
	include("${VITASDK}/share/vita.cmake" REQUIRED)
	add_definitions(-DVITA)
	
	set(VITA_APP_NAME "Trogdor: Reburninated")
	set(VITA_TITLEID  "TROG73287")
	set(VITA_VERSION  "01.00")

	target_link_libraries(trogdorrb SDL2_ttf SDL2_mixer SDL2_image SDL2_gfx SDL2 freetype png png16 bz2 jpeg z mikmod mpg123 FLAC vorbisfile vorbis ogg webp pthread)
	# find_package(SDL2 REQUIRED)
	# target_link_libraries(trogdorrb SDL2_ttf SDL2_mixer SDL2_image SDL2_gfx SDL2)
	target_link_libraries(trogdorrb
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

	vita_create_self(trogdorrb.self trogdorrb)
	vita_create_vpk(trogdorrb.vpk ${VITA_TITLEID} trogdorrb.self
		VERSION ${VITA_VERSION}
		NAME ${VITA_APP_NAME}
		FILE release-resources/logo_icon_vita.png sce_sys/icon0.png
		FILE release-resources/background_vita.png sce_sys/livearea/contents/bg.png
		FILE release-resources/logo_startup_vita.png sce_sys/livearea/contents/startup.png
		FILE release-resources/template_vita.xml sce_sys/livearea/contents/template.xml
	)

else()
	if (LINUX)
		add_definitions(-DLINUX)
	endif()
	PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
	PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
	PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
	PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
	INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES} ${SDL2TTF_LIBRARIES})

endif()

unset(WIIU CACHE)
unset(VITA CACHE)
unset(LINUX CACHE)