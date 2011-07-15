set(zuip_edit_SRCS zuipedit.cpp main.cpp)
set(zuip_edit_UI zuipedit.ui)

qt4_automoc(${zuip_edit_SRCS})
qt4_wrap_ui(zuip_edit_UI_H ${zuip_edit_UI})

add_executable(zuipEdit ${zuip_edit_SRCS} ${zuip_edit_UI_H})
target_link_libraries(zuipEdit ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTSVG_LIBRARY})

