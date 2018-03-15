QT += qml quick

CONFIG(release, debug|release): DEFINES += NDEBUG
CONFIG += c++11

win32:LIBS += -lws2_32

INCLUDEPATH += "../utils/network"

SOURCES += main.cpp \
    server/ble_device.cpp \
    server/core_device.cpp \
    server/device_client.cpp \
    server/callibri_device.cpp \
    server/device_processor.cpp \
    server/callibri_main_module.cpp \
    server/callibri_command.cpp \
    server/callibri_module.cpp \
    server/callibri_common_parameters.cpp \
    server_presenter.cpp \
    device_list_model.cpp \
    ui_device.cpp \
    brainbit_impl.cpp \
    callibri_impl.cpp \
    device_list.cpp \
    property_page_model.cpp \
    brainbit_model.cpp \
    callibri_common_model.cpp \
    callibri_signal_model.cpp \
    server/callibri_signal_module.cpp \
    sine_generator.cpp \
    server/emulation_server.cpp \
    ../utils/network/windows/win_socket.cpp \
    ../utils/network/posix/posix_socket.cpp \
    ../utils/network/udp_socket.cpp \
    ../utils/network/tcp_socket.cpp \
    ../utils/network/base_socket.cpp \
    server/callibri_data_packet.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    server/emulation_server.h \
    server/server_device_interface.h \
    server/ble_device.h \
    server/core_device.h \
    server/nes_types.h \
    server/device_client.h \
    server/callibri_device.h \
    server/device_processor.h \
    server/callibri_module.h \
    server/callibri_module_container.h \
    server/callibri_main_module.h \
    server/callibri_command.h \
    server/callibri_generic_module.h \
    server/callibri_common_parameters.h \
    server_presenter.h \
    device_list_model.h \
    device_list.h \
    ui_device.h \
    ui_device_impl.h \
    device_type.h \
    brainbit_impl.h \
    callibri_impl.h \
    saturation_cast.h \
    property_page_model.h \
    brainbit_model.h \
    callibri_common_model.h \
    callibri_signal_model.h \
    server/callibri_signal_module.h \
    server/signal_generator.h \
    sine_generator.h \
    ../utils/network/posix/posix_socket.h \
    ../utils/network/windows/win_socket.h \
    ../utils/network/net_types.h \
    ../utils/network/socket.h \
    server/callibri_data_packet.h
