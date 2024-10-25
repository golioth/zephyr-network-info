/*
 * Copyright (c) 2023 Golioth, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(net_info, LOG_LEVEL_DBG);

#include <golioth/rpc.h>
#include <network_info.h>
#include <zephyr/net/net_if.h>
/* For net_sprint_ll_addr_buf */
#include "net_private.h"
#include <zephyr/net/wifi_mgmt.h>


#define MAX_WIFI_STR_LEN 64

int cmd_wifi_status(struct wifi_iface_status *status)
{
	struct net_if *iface = net_if_get_default();

	if (net_mgmt(NET_REQUEST_WIFI_IFACE_STATUS, iface, status,
				sizeof(struct wifi_iface_status))) {
		LOG_INF("Status request failed");

		return -ENOEXEC;
	}
	return 0;
}

int network_info_add_to_map(zcbor_state_t *response_detail_map)
{
	bool ok;
	struct wifi_iface_status w_status = { 0 };

	cmd_wifi_status(&w_status);

	ok = zcbor_tstr_put_lit(response_detail_map, "State") &&
		zcbor_tstr_put_term(response_detail_map, wifi_state_txt(w_status.state), MAX_WIFI_STR_LEN);
	if (!ok) {
		goto rpc_exhausted;
	}

	if (w_status.state >= WIFI_STATE_ASSOCIATED) {
		uint8_t mac_string_buf[sizeof("xx:xx:xx:xx:xx:xx")];
		net_sprint_ll_addr_buf(w_status.bssid,
				       WIFI_MAC_ADDR_LEN,
				       mac_string_buf,
				       sizeof(mac_string_buf));

		ok = zcbor_tstr_put_lit(response_detail_map, "Interface Mode") &&
		     zcbor_tstr_put_term(response_detail_map,
				         wifi_mode_txt(w_status.iface_mode), MAX_WIFI_STR_LEN);
		if (!ok) {
			goto rpc_exhausted;
		}
		ok = zcbor_tstr_put_lit(response_detail_map, "Link Mode") &&
		     zcbor_tstr_put_term(response_detail_map,
				         wifi_link_mode_txt(w_status.link_mode), MAX_WIFI_STR_LEN);
		if (!ok) {
			goto rpc_exhausted;
		}
		ok = zcbor_tstr_put_lit(response_detail_map, "SSID") &&
		     zcbor_tstr_put_term(response_detail_map, w_status.ssid, MAX_WIFI_STR_LEN);
		if (!ok) {
			goto rpc_exhausted;
		}
		ok = zcbor_tstr_put_lit(response_detail_map, "BSSID") &&
		     zcbor_tstr_put_term(response_detail_map, mac_string_buf, MAX_WIFI_STR_LEN);
		if (!ok) {
			goto rpc_exhausted;
		}
		ok = zcbor_tstr_put_lit(response_detail_map, "Band") &&
		     zcbor_tstr_put_term(response_detail_map,
				         wifi_band_txt(w_status.band), MAX_WIFI_STR_LEN);
		if (!ok) {
			goto rpc_exhausted;
		}
		ok = zcbor_tstr_put_lit(response_detail_map, "Channel") &&
		     zcbor_uint32_put(response_detail_map, w_status.channel);
		if (!ok) {
			goto rpc_exhausted;
		}
		ok = zcbor_tstr_put_lit(response_detail_map, "Security") &&
		     zcbor_tstr_put_term(response_detail_map,
				         wifi_security_txt(w_status.security), MAX_WIFI_STR_LEN);
		if (!ok) {
			goto rpc_exhausted;
		}
		ok = zcbor_tstr_put_lit(response_detail_map, "MFP") &&
		     zcbor_tstr_put_term(response_detail_map,
				         wifi_mfp_txt(w_status.mfp), MAX_WIFI_STR_LEN);
		if (!ok) {
			goto rpc_exhausted;
		}
		ok = zcbor_tstr_put_lit(response_detail_map, "RSSI") &&
		     zcbor_int32_put(response_detail_map, w_status.rssi);
		if (!ok) {
			goto rpc_exhausted;
		}
	}

	return GOLIOTH_RPC_OK;

rpc_exhausted:
	LOG_ERR("Failed to encode some values; response might be too long (CONFIG_GOLIOTH_RPC_MAX_RESPONSE_LEN: %d)",
		CONFIG_GOLIOTH_RPC_MAX_RESPONSE_LEN);
	return GOLIOTH_RPC_RESOURCE_EXHAUSTED;
}

int network_info_log(void)
{
	struct wifi_iface_status w_status = { 0 };

	cmd_wifi_status(&w_status);

	LOG_DBG("====== WiFi Network Info ======");
	LOG_DBG("State: %s", wifi_state_txt(w_status.state));

	if (w_status.state >= WIFI_STATE_ASSOCIATED) {
		uint8_t mac_string_buf[sizeof("xx:xx:xx:xx:xx:xx")];
		LOG_DBG("Interface Mode: %s", wifi_mode_txt(w_status.iface_mode));
		LOG_DBG("Link Mode: %s", wifi_link_mode_txt(w_status.link_mode));
		LOG_DBG("SSID: %s", w_status.ssid);
		LOG_DBG("BSSID: %s",
			net_sprint_ll_addr_buf(w_status.bssid,
					       WIFI_MAC_ADDR_LEN,
					       mac_string_buf,
					       sizeof(mac_string_buf))
					       );
		LOG_DBG("Band: %s", wifi_band_txt(w_status.band));
		LOG_DBG("Channel: %d", w_status.channel);
		LOG_DBG("Security: %s", wifi_security_txt(w_status.security));
		LOG_DBG("MFP: %s", wifi_mfp_txt(w_status.mfp));
		LOG_DBG("RSSI: %d", w_status.rssi);
	}
	LOG_DBG("===============================");
	return 0;
}
