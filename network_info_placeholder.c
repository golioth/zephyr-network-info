/*
 * Copyright (c) 2023 Golioth, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(golioth_iot, LOG_LEVEL_DBG);

#include <net/golioth/rpc.h>
#include <network_info.h>

int __attribute__((weak)) network_info_add_to_map(zcbor_state_t *response_detail_map)
{
	bool ok;

	ok = zcbor_tstr_put_lit(response_detail_map, "No Network Info") &&
	     zcbor_tstr_put_lit(response_detail_map,
				"Network reporting not implemented for this hardware");

	if (!ok) {
		LOG_ERR("Failed to encode value");
		return GOLIOTH_RPC_RESOURCE_EXHAUSTED;
	}

	return GOLIOTH_RPC_OK;
}

int __attribute__((weak)) network_info_log(void)
{
	LOG_DBG("====== Network Info ======");

	LOG_DBG("State: %s", "No Network Info;");
	LOG_DBG("%s", "Network reporting not implemented for this board");
	LOG_DBG("==========================");
	return 0;
}
