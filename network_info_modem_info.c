/*
 * Copyright (c) 2023 Golioth, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(net_info, LOG_LEVEL_DBG);

#include <network_info.h>
#include <modem/modem_info.h>

int network_info_init(void)
{
	int err = modem_info_init();
	if (err) {
		LOG_ERR("Failed to initialize modem info: %d", err);
		return err;
	}
	return 0;
}

int network_info_add_to_map(QCBOREncodeContext *response_detail_map)
{
	char sbuf[128];
	modem_info_string_get(MODEM_INFO_RSRP, sbuf, sizeof(sbuf));
	QCBOREncode_AddSZStringToMap(response_detail_map,
				     "Signal strength",
				     sbuf);
	modem_info_string_get(MODEM_INFO_CUR_BAND, sbuf, sizeof(sbuf));
	QCBOREncode_AddSZStringToMap(response_detail_map,
				     "Current LTE band",
				     sbuf);
	modem_info_string_get(MODEM_INFO_SUP_BAND, sbuf, sizeof(sbuf));
	QCBOREncode_AddSZStringToMap(response_detail_map,
				     "Supported LTE bands",
				     sbuf);
	modem_info_string_get(MODEM_INFO_AREA_CODE, sbuf, sizeof(sbuf));
	QCBOREncode_AddSZStringToMap(response_detail_map,
				     "Tracking area code",
				     sbuf);
	modem_info_string_get(MODEM_INFO_UE_MODE, sbuf, sizeof(sbuf));
	QCBOREncode_AddSZStringToMap(response_detail_map,
				     "Current mode",
				     sbuf);
	modem_info_string_get(MODEM_INFO_OPERATOR, sbuf, sizeof(sbuf));
	QCBOREncode_AddSZStringToMap(response_detail_map,
				     "Current operator name",
				     sbuf);
	modem_info_string_get(MODEM_INFO_CELLID, sbuf, sizeof(sbuf));
	QCBOREncode_AddSZStringToMap(response_detail_map,
				     "Cell ID of the device",
				     sbuf);
	modem_info_string_get(MODEM_INFO_IP_ADDRESS, sbuf, sizeof(sbuf));
	QCBOREncode_AddSZStringToMap(response_detail_map,
				     "IP address of the device",
				     sbuf);
	modem_info_string_get(MODEM_INFO_FW_VERSION, sbuf, sizeof(sbuf));
	QCBOREncode_AddSZStringToMap(response_detail_map,
				     "Modem firmware version",
				     sbuf);
	modem_info_string_get(MODEM_INFO_LTE_MODE, sbuf, sizeof(sbuf));
	QCBOREncode_AddSZStringToMap(response_detail_map,
				     "LTE-M support mode",
				     sbuf);
	modem_info_string_get(MODEM_INFO_NBIOT_MODE, sbuf, sizeof(sbuf));
	QCBOREncode_AddSZStringToMap(response_detail_map,
				     "NB-IoT support mode",
				     sbuf);
	modem_info_string_get(MODEM_INFO_GPS_MODE, sbuf, sizeof(sbuf));
	QCBOREncode_AddSZStringToMap(response_detail_map,
				     "GPS support mode",
				     sbuf);
	modem_info_string_get(MODEM_INFO_DATE_TIME, sbuf, sizeof(sbuf));
	QCBOREncode_AddSZStringToMap(response_detail_map,
				     "Mobile network time and date",
				     sbuf);

	return 0;
}

void modem_info_log_rsrp(void)
{
	char sbuf[128];
	modem_info_string_get(MODEM_INFO_RSRP, sbuf, sizeof(sbuf));
	LOG_DBG("Signal strength: %s", sbuf);
}

void modem_info_log_cur_band(void)
{
	char sbuf[128];
	modem_info_string_get(MODEM_INFO_CUR_BAND, sbuf, sizeof(sbuf));
	LOG_DBG("Current LTE band: %s", sbuf);
}

void modem_info_log_sup_band(void)
{
	char sbuf[128];
	modem_info_string_get(MODEM_INFO_SUP_BAND, sbuf, sizeof(sbuf));
	LOG_DBG("Supported LTE bands: %s", sbuf);
}

void modem_info_log_area_code(void)
{
	char sbuf[128];
	modem_info_string_get(MODEM_INFO_AREA_CODE, sbuf, sizeof(sbuf));
	LOG_DBG("Tracking area code: %s", sbuf);
}

void modem_info_log_ue_mode(void)
{
	char sbuf[128];
	modem_info_string_get(MODEM_INFO_UE_MODE, sbuf, sizeof(sbuf));
	LOG_DBG("Current mode: %s", sbuf);
}

void modem_info_log_operator(void)
{
	char sbuf[128];
	modem_info_string_get(MODEM_INFO_OPERATOR, sbuf, sizeof(sbuf));
	LOG_DBG("Current operator name: %s", sbuf);
}

void modem_info_log_cell_id(void)
{
	char sbuf[128];
	modem_info_string_get(MODEM_INFO_CELLID, sbuf, sizeof(sbuf));
	LOG_DBG("Cell ID of the device: %s", sbuf);
}

void modem_info_log_ip_address(void)
{
	char sbuf[128];
	modem_info_string_get(MODEM_INFO_IP_ADDRESS, sbuf, sizeof(sbuf));
	LOG_DBG("IP address of the device: %s", sbuf);
}

void modem_info_log_fw_version(void)
{
	char sbuf[128];
	modem_info_string_get(MODEM_INFO_FW_VERSION, sbuf, sizeof(sbuf));
	LOG_DBG("Modem firmware version: %s", sbuf);
}

void modem_info_log_lte_mode(void)
{
	char sbuf[128];
	modem_info_string_get(MODEM_INFO_LTE_MODE, sbuf, sizeof(sbuf));
	LOG_DBG("LTE-M support mode: %s", sbuf);
}

void modem_info_log_nbiot_mode(void)
{
	char sbuf[128];
	modem_info_string_get(MODEM_INFO_NBIOT_MODE, sbuf, sizeof(sbuf));
	LOG_DBG("NB-IoT support mode: %s", sbuf);
}

void modem_info_log_gps_mode(void)
{
	char sbuf[128];
	modem_info_string_get(MODEM_INFO_GPS_MODE, sbuf, sizeof(sbuf));
	LOG_DBG("GPS support mode: %s", sbuf);
}

void modem_info_log_date_time(void)
{
	char sbuf[128];
	modem_info_string_get(MODEM_INFO_DATE_TIME, sbuf, sizeof(sbuf));
	LOG_DBG("Mobile network time and date: %s", sbuf);
}

int network_info_log(void)
{
	LOG_DBG("====== Cell Network Info ======");
	modem_info_log_rsrp();
	modem_info_log_cur_band();
	modem_info_log_sup_band();
	modem_info_log_area_code();
	modem_info_log_ue_mode();
	modem_info_log_operator();
	modem_info_log_cell_id();
	modem_info_log_ip_address();
	modem_info_log_fw_version();
	modem_info_log_lte_mode();
	modem_info_log_nbiot_mode();
	modem_info_log_gps_mode();
	modem_info_log_date_time();
	LOG_DBG("===============================");

	return 0;
}
