/*
 * Copyright (c) 2023 Golioth, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(net_info, LOG_LEVEL_DBG);

#include <golioth/rpc.h>
#include <network_info.h>

/*
 * This WiFi utility is a file located in the golioth/zephyr-training repository. It is specific to
 * using WiFi with the nRF7002. However, we blieve there is work in progress to add the 7002 to the
 * Zephyr WiFi abstraction layer which would remove the need to use this helper file.
 */
#include <wifi_util.h>

int network_info_add_to_map(zcbor_state_t *response_detail_map)
{
	bool ok;
	struct wifi_iface_status w_status = { 0 };

	cmd_wifi_status(&w_status);

	ok = zcbor_tstr_put_lit(response_detail_map, "State") &&
		zcbor_tstr_put_term(response_detail_map, wifi_state_txt(w_status.state), 128);
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
				         wifi_mode_txt(w_status.iface_mode), 128);
		if (!ok) {
			goto rpc_exhausted;
		}
		ok = zcbor_tstr_put_lit(response_detail_map, "Link Mode") &&
		     zcbor_tstr_put_term(response_detail_map,
				         wifi_link_mode_txt(w_status.link_mode), 128);
		if (!ok) {
			goto rpc_exhausted;
		}
		ok = zcbor_tstr_put_lit(response_detail_map, "SSID") &&
		     zcbor_tstr_put_term(response_detail_map, w_status.ssid, 128);
		if (!ok) {
			goto rpc_exhausted;
		}
		ok = zcbor_tstr_put_lit(response_detail_map, "BSSID") &&
		     zcbor_tstr_put_term(response_detail_map, mac_string_buf, 128);
		if (!ok) {
			goto rpc_exhausted;
		}
		ok = zcbor_tstr_put_lit(response_detail_map, "Band") &&
		     zcbor_tstr_put_term(response_detail_map,
				         wifi_band_txt(w_status.band), 128);
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
				         wifi_security_txt(w_status.security), 128);
		if (!ok) {
			goto rpc_exhausted;
		}
		ok = zcbor_tstr_put_lit(response_detail_map, "MFP") &&
		     zcbor_tstr_put_term(response_detail_map,
				         wifi_mfp_txt(w_status.mfp), 128);
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
