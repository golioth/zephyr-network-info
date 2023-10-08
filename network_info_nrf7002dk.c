/*
 * Copyright (c) 2023 Golioth, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(net_info, LOG_LEVEL_DBG);

#include <net/golioth/rpc.h>
#include <network_info.h>
#include <zephyr/net/wifi_mgmt.h>
#include <zcbor_encode.h>

int __attribute__((weak)) cmd_wifi_status(struct wifi_iface_status *status)
{
	/* Rely on the app to implement this function */
	return 0;
}

char __attribute__((weak)) *net_sprint_ll_addr_buf(const uint8_t *ll, uint8_t ll_len,
						   char *buf, int buflen)
{
	/* This is already extern in net/ip/net_private.h */
	return "ERR";
}

int network_info_add_to_map(zcbor_state_t *response_detail_map)
{
	bool ok;
	struct wifi_iface_status w_status = { 0 };

	cmd_wifi_status(&w_status);

	if (w_status.state >= WIFI_STATE_ASSOCIATED) {
		uint8_t mac_string_buf[sizeof("xx:xx:xx:xx:xx:xx")];
		net_sprint_ll_addr_buf(w_status.bssid,
				       WIFI_MAC_ADDR_LEN,
				       mac_string_buf,
				       sizeof(mac_string_buf));

		ok = zcbor_tstr_put_lit(response_detail_map, "Interface Mode") &&
		     zcbor_tstr_put_term(response_detail_map,
				         wifi_mode_txt(w_status.iface_mode)) &&
		     zcbor_tstr_put_lit(response_detail_map, "Link Mode") &&
		     zcbor_tstr_put_term(response_detail_map,
				         wifi_link_mode_txt(w_status.link_mode)) &&
		     zcbor_tstr_put_lit(response_detail_map, "SSID") &&
		     zcbor_tstr_put_term(response_detail_map, w_status.ssid) &&
		     zcbor_tstr_put_lit(response_detail_map, "BSSID") &&
		     zcbor_tstr_put_term(response_detail_map, mac_string_buf) &&
		     zcbor_tstr_put_lit(response_detail_map, "Band") &&
		     zcbor_tstr_put_term(response_detail_map,
				         wifi_band_txt(w_status.band)) &&
		     zcbor_tstr_put_lit(response_detail_map, "Channel") &&
		     zcbor_uint32_put(response_detail_map, w_status.channel) &&
		     zcbor_tstr_put_lit(response_detail_map, "Security") &&
		     zcbor_tstr_put_term(response_detail_map,
				         wifi_security_txt(w_status.security)) &&
		     zcbor_tstr_put_lit(response_detail_map, "MFP") &&
		     zcbor_tstr_put_term(response_detail_map,
				         wifi_mfp_txt(w_status.mfp)) &&
		     zcbor_tstr_put_lit(response_detail_map, "RSSI") &&
		     zcbor_int32_put(response_detail_map, w_status.rssi);

		if (!ok) {
			LOG_ERR("Failed to encode value");
			return GOLIOTH_RPC_RESOURCE_EXHAUSTED;
		}
	}

	return GOLIOTH_RPC_OK;
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
		LOG_DBG("Securit: %sy", wifi_security_txt(w_status.security));
		LOG_DBG("MFP: %s", wifi_mfp_txt(w_status.mfp));
		LOG_DBG("RSSI: %d", w_status.rssi);
	}
	LOG_DBG("===============================");
	return 0;
}
