# Golioth Zephyr Network Info Library

Helper library to query network information and return it as either a QCBOR map
(useful for Golioth Remote Procedure Calls) or as a Zephyr log message.

## Using this Libaray

1. Add this repository to your `west.yml` file `projects` section (be sure to
   update the revision number to newest/desired):

    ```yaml
    projects:
      - name: zephyr-network-info
        path: src/network_info
        revision: cc89936517900cf9142af48e06188240b99cd4b9
        url: https://github.com/golioth/zephyr-network-info
    ```
3. Add `network_info/` to your `.gitignore`
4. Add `add_subdirectory(src/network_info)` to your project CMakeLists.txt
5. Add `#include "network_info.h"` to your calling file
6. Call `network_info_init()` to initialize the library
7. Write network info to log files:

    ```c
    network_info_log()
    ```
8. Return network info as a Golioth RPC:

    ```c
    static enum golioth_rpc_status on_get_network_info(QCBORDecodeContext *request_params_array,
                            QCBOREncodeContext *response_detail_map,
                            void *callback_arg)
    {
        QCBORError qerr;

        qerr = QCBORDecode_GetError(request_params_array);
        if (qerr != QCBOR_SUCCESS) {
            LOG_ERR("Failed to decode array items: %d (%s)", qerr, qcbor_err_to_str(qerr));
            return GOLIOTH_RPC_INVALID_ARGUMENT;
        }

        network_info_add_to_map(response_detail_map);

        return GOLIOTH_RPC_OK;
    }
    ```

### Adding support for boards that use the Modem Info library

Boards that use Nordic's Modem Info library, like the nRF9160, can use this
network info library. After following the steps above, add the following symbols
to the conf file for your board in the boards directory:

```
# Add Network Info Support
CONFIG_MODEM_INFO=y
CONFIG_GOLIOTH_RPC_MAX_RESPONSE_LEN=512
```

## Adding a network_info file for a new board

This library holds device-specific files for returning network info. Only one of
these files should be built into a project. This is selected using the
CMakeLists.txt and Kconfg files.

1. Create the new C file
  1. add `#include <network_info.h>`
  2. implement required functions
    * `int network_info_init(void)`
    * `int network_info_add_to_map(QCBOREncodeContext *response_detail_map)`
    * `int network_info_log(void)`
2. Add C file to CMakeLists.txt gated by the Kconfig symbol for that file:

    ```
    zephyr_library_sources_ifdef(CONFIG_BOARD_NRF7002DK_NRF5340_CPUAPP network_info_nrf7002dk.c)
    zephyr_library_sources_ifdef(CONFIG_MODEM_INFO network_info_modem_info.c)
    ```
