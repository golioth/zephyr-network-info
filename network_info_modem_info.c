/*
 * Copyright (c) 2023 Golioth, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(net_info, LOG_LEVEL_DBG);

#include <modem/modem_info.h>
#include <net/golioth/rpc.h>
#include <network_info.h>
#include <zephyr/init.h>

static int network_info_init(void)
{
	int err = modem_info_init();
	if (err) {
		LOG_ERR("Failed to initialize modem info: %d", err);
		return err;
	}
	return 0;
}
SYS_INIT(network_info_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

int network_info_add_to_map(zcbor_state_t *response_detail_map)
{
	char sbuf[128];
	bool ok;

	modem_info_string_get(MODEM_INFO_RSRP, sbuf, sizeof(sbuf));
	ok = zcbor_tstr_put_lit(response_detail_map, "Signal strength") &&
	     zcbor_tstr_put_term(response_detail_map, sbuf);
	if (!ok) {
		goto rpc_exhausted;
	}

	modem_info_string_get(MODEM_INFO_CUR_BAND, sbuf, sizeof(sbuf));
	ok = zcbor_tstr_put_lit(response_detail_map, "Current LTE band") &&
	     zcbor_tstr_put_term(response_detail_map, sbuf);
	if (!ok) {
		goto rpc_exhausted;
	}

	modem_info_string_get(MODEM_INFO_SUP_BAND, sbuf, sizeof(sbuf));
	ok = zcbor_tstr_put_lit(response_detail_map, "Supported LTE bands") &&
	     zcbor_tstr_put_term(response_detail_map, sbuf);
	if (!ok) {
		goto rpc_exhausted;
	}

	modem_info_string_get(MODEM_INFO_AREA_CODE, sbuf, sizeof(sbuf));
	ok = zcbor_tstr_put_lit(response_detail_map, "Tracking area code") &&
	     zcbor_tstr_put_term(response_detail_map, sbuf);
	if (!ok) {
		goto rpc_exhausted;
	}

	modem_info_string_get(MODEM_INFO_UE_MODE, sbuf, sizeof(sbuf));
	ok = zcbor_tstr_put_lit(response_detail_map, "Current mode") &&
	     zcbor_tstr_put_term(response_detail_map, sbuf);
	if (!ok) {
		goto rpc_exhausted;
	}

	modem_info_string_get(MODEM_INFO_OPERATOR, sbuf, sizeof(sbuf));
	ok = zcbor_tstr_put_lit(response_detail_map, "Current operator name") &&
	     zcbor_tstr_put_term(response_detail_map, sbuf);
	if (!ok) {
		goto rpc_exhausted;
	}

	modem_info_string_get(MODEM_INFO_CELLID, sbuf, sizeof(sbuf));
	ok = zcbor_tstr_put_lit(response_detail_map, "Cell ID of the device") &&
	     zcbor_tstr_put_term(response_detail_map, sbuf);
	if (!ok) {
		goto rpc_exhausted;
	}

	modem_info_string_get(MODEM_INFO_IP_ADDRESS, sbuf, sizeof(sbuf));
	ok = zcbor_tstr_put_lit(response_detail_map, "IP address of the device") &&
	     zcbor_tstr_put_term(response_detail_map, sbuf);
	if (!ok) {
		goto rpc_exhausted;
	}

	modem_info_string_get(MODEM_INFO_FW_VERSION, sbuf, sizeof(sbuf));
	ok = zcbor_tstr_put_lit(response_detail_map, "Modem firmware version") &&
	     zcbor_tstr_put_term(response_detail_map, sbuf);
	if (!ok) {
		goto rpc_exhausted;
	}

	modem_info_string_get(MODEM_INFO_LTE_MODE, sbuf, sizeof(sbuf));
	ok = zcbor_tstr_put_lit(response_detail_map, "LTE-M support mode") &&
	     zcbor_tstr_put_term(response_detail_map, sbuf);
	if (!ok) {
		goto rpc_exhausted;
	}

	modem_info_string_get(MODEM_INFO_NBIOT_MODE, sbuf, sizeof(sbuf));
	ok = zcbor_tstr_put_lit(response_detail_map, "NB-IoT support mode") &&
	     zcbor_tstr_put_term(response_detail_map, sbuf);
	if (!ok) {
		goto rpc_exhausted;
	}

	modem_info_string_get(MODEM_INFO_GPS_MODE, sbuf, sizeof(sbuf));
	ok = zcbor_tstr_put_lit(response_detail_map, "GPS support mode") &&
	     zcbor_tstr_put_term(response_detail_map, sbuf);
	if (!ok) {
		goto rpc_exhausted;
	}

	modem_info_string_get(MODEM_INFO_DATE_TIME, sbuf, sizeof(sbuf));
	ok = zcbor_tstr_put_lit(response_detail_map, "Mobile network time and date") &&
	     zcbor_tstr_put_term(response_detail_map, sbuf);
	if (!ok) {
		goto rpc_exhausted;
	}

	return GOLIOTH_RPC_OK;

rpc_exhausted:
	LOG_ERR("Failed to encode value");
	return GOLIOTH_RPC_RESOURCE_EXHAUSTED;
}

int network_info_log(void)
{
	LOG_DBG("====== Cell Network Info ======");
	char sbuf[128];
	modem_info_string_get(MODEM_INFO_RSRP, sbuf, sizeof(sbuf));
	LOG_DBG("Signal strength: %s", sbuf);

	modem_info_string_get(MODEM_INFO_CUR_BAND, sbuf, sizeof(sbuf));
	LOG_DBG("Current LTE band: %s", sbuf);

	modem_info_string_get(MODEM_INFO_SUP_BAND, sbuf, sizeof(sbuf));
	LOG_DBG("Supported LTE bands: %s", sbuf);

	modem_info_string_get(MODEM_INFO_AREA_CODE, sbuf, sizeof(sbuf));
	LOG_DBG("Tracking area code: %s", sbuf);

	modem_info_string_get(MODEM_INFO_UE_MODE, sbuf, sizeof(sbuf));
	LOG_DBG("Current mode: %s", sbuf);

	modem_info_string_get(MODEM_INFO_OPERATOR, sbuf, sizeof(sbuf));
	LOG_DBG("Current operator name: %s", sbuf);

	modem_info_string_get(MODEM_INFO_CELLID, sbuf, sizeof(sbuf));
	LOG_DBG("Cell ID of the device: %s", sbuf);

	modem_info_string_get(MODEM_INFO_IP_ADDRESS, sbuf, sizeof(sbuf));
	LOG_DBG("IP address of the device: %s", sbuf);

	modem_info_string_get(MODEM_INFO_FW_VERSION, sbuf, sizeof(sbuf));
	LOG_DBG("Modem firmware version: %s", sbuf);

	modem_info_string_get(MODEM_INFO_LTE_MODE, sbuf, sizeof(sbuf));
	LOG_DBG("LTE-M support mode: %s", sbuf);

	modem_info_string_get(MODEM_INFO_NBIOT_MODE, sbuf, sizeof(sbuf));
	LOG_DBG("NB-IoT support mode: %s", sbuf);

	modem_info_string_get(MODEM_INFO_GPS_MODE, sbuf, sizeof(sbuf));
	LOG_DBG("GPS support mode: %s", sbuf);

	modem_info_string_get(MODEM_INFO_DATE_TIME, sbuf, sizeof(sbuf));
	LOG_DBG("Mobile network time and date: %s", sbuf);

	LOG_DBG("===============================");

	return 0;
}
