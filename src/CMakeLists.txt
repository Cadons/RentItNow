cmake_minimum_required(VERSION 3.5)

project(RentItNow VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        rentitnowmainwindow.cpp
        rentitnowmainwindow.h
        rentitnowmainwindow.ui


)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RentItNow
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        model/car.h model/car.cpp
        model/user.h model/user.cpp
        model/ecocar.h model/ecocar.cpp
        model/midclasscar.h model/midclasscar.cpp
        model/deluxecar.h model/deluxecar.cpp
        model/cartype.h model/cartype.cpp

        service/ICrud.h
        service/carmanagementservice.h service/carmanagementservice.cpp
        model/location.h model/location.cpp
        carmanager.h carmanager.cpp carmanager.ui
        service/ICarManager.h
        tables/carmodel.h tables/carmodel.cpp
        model/CarTypeName.h
        carform.h carform.cpp carform.ui
        repository/carsrepository.h repository/carsrepository.cpp
        repository/IRepository.h
        repository/repositoryutils.h repository/repositoryutils.cpp
        repository/usersrepository.h repository/usersrepository.cpp
        service/usermanagementservice.h service/usermanagementservice.cpp
        service/IUserManager.h
        usermanager.h usermanager.cpp usermanager.ui
        userform.h userform.cpp userform.ui
        tables/usermodel.h tables/usermodel.cpp
        service/rentingservice.h service/rentingservice.cpp
        service/IRentingService.h
        model/circle.h model/circle.cpp
        model/rentresearchresult.h model/rentresearchresult.cpp
        model/simpletown.h model/simpletown.cpp
        userrentform.h userrentform.cpp userrentform.ui
        model/bank.h model/bank.cpp

        threadworker.h threadworker.cpp
        carserviceworker.h carserviceworker.cpp
        repository/bankrepository.h repository/bankrepository.cpp
        repository/ISingleDataRepository.h












    )

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET RentItNow APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(RentItNow SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(RentItNow
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(RentItNow PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.RentItNow)
endif()
set_target_properties(RentItNow PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS RentItNow
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RentItNow)
endif()
