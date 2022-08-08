cmake_minimum_required(VERSION 3.5)
project(Linux_APUE)

set(EASYMQTT_ROOT ./)
include_directories(${EASYMQTT_ROOT})
include_directories(${EASYMQTT_ROOT}/EasyMqtt)
include_directories(${EASYMQTT_ROOT}/ThirdPart/Mqtt/common)
include_directories(${EASYMQTT_ROOT}/ThirdPart/Mqtt/mqtt)
include_directories(${EASYMQTT_ROOT}/ThirdPart/Mqtt/mqttclient)
include_directories(${EASYMQTT_ROOT}/ThirdPart/Mqtt/network)
include_directories(${EASYMQTT_ROOT}/ThirdPart/Mqtt/network/mbedtls/configs)
include_directories(${EASYMQTT_ROOT}/ThirdPart/Mqtt/network/mbedtls/include)
include_directories(${EASYMQTT_ROOT}/ThirdPart/Mqtt/network/mbedtls/wrapper)
include_directories(${EASYMQTT_ROOT}/ThirdPart/Mqtt/platform/linux)

aux_source_directory(${EASYMQTT_ROOT}/EasyMqtt              			EASYMQTT)
aux_source_directory(${EASYMQTT_ROOT}/ThirdPart/Mqtt/common              	MQTT_COMMON)
aux_source_directory(${EASYMQTT_ROOT}/ThirdPart/Mqtt/mqtt            		MQTT)
aux_source_directory(${EASYMQTT_ROOT}/ThirdPart/Mqtt/mqttclient             	MQTTCLIENT)
aux_source_directory(${EASYMQTT_ROOT}/ThirdPart/Mqtt/network             	MQTTNETWORK)
aux_source_directory(${EASYMQTT_ROOT}/ThirdPart/Mqtt/network/mbedtls/library    MQTTMBEDTLS_LIB)
aux_source_directory(${EASYMQTT_ROOT}/ThirdPart/Mqtt/network/mbedtls/wrapper    MQTTMBEDTLS_WRAPPER)
aux_source_directory(${EASYMQTT_ROOT}/ThirdPart/Mqtt/platform/linux        	MQTTPLATFORMINTERFACE)

set(EASYMQTT_SRC
    ${EASYMQTT}
    ${MQTT_COMMON} 
    ${MQTT} 
    ${MQTTCLIENT} 
    ${MQTTNETWORK} 
    ${MQTTMBEDTLS_LIB} 
    ${MQTTMBEDTLS_WRAPPER}
    ${MQTTPLATFORMINTERFACE}
)

set(APP_SRCS 
    ${EASYMQTT_ROOT}main.c
    ${EASYMQTT_SRC}
)

add_compile_options(-std=gnu99 -Wall -O3 -g -Wno-discarded-qualifiers -Wmaybe-uninitialized)
add_executable(a.out ${APP_SRCS})
target_link_libraries(a.out pthread rt)
