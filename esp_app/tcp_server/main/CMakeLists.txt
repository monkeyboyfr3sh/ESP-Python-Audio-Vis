idf_component_register(
            SRCS    "main.c"
                    "src/UDP_thread.c" "src/TCP_thread.c" "src/LED_thread.c" 
                    INCLUDE_DIRS "." "inc/")
