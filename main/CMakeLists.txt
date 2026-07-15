file(GLOB_RECURSE srcs "main.c" "src/*.c")

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "./include")

target_add_binary_data(${COMPONENT_LIB} "../server_certs/ca_cert.pem" TEXT)