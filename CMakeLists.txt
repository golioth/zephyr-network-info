if(CONFIG_NETWORK_INFO)
  zephyr_library_sources(network_info_placeholder.c)

  zephyr_library_sources_ifdef(CONFIG_BOARD_NRF7002DK_NRF5340_CPUAPP network_info_nrf7002dk.c)
  zephyr_library_sources_ifdef(CONFIG_MODEM_INFO network_info_modem_info.c)

  zephyr_include_directories(include)
endif()
