/*
 * Copyright (c) 2023 Golioth, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __NETWORK_INFO_H__
#define __NETWORK_INFO_H__

#include <qcbor/qcbor.h>

/**
 * @brief Initialize the Network Info file for this board
 *
 * @retval 0 On success
 * @retval <0 On failure
 */
int network_info_init(void);

/**
 * @brief Populate a QCBOR map with Network Information
 *
 * Query the network information for this board and write the results to a QCBOR
 * map.
 *
 * @param response_detail_map Pointer to a QCBOR map where network information
 * should be written
 *
 * @retval 0 On success
 * @retval <0 On failure
 */
int network_info_add_to_map(QCBOREncodeContext *response_detail_map);

#ifdef CONFIG_MODEM_INFO

/**
 * @brief Write modem signal strength as a LOG message
 */
void modem_info_log_rsrp(void);

/**
 * @brief Write modem current LTE band as a LOG message
 */
void modem_info_log_cur_band(void);

/**
 * @brief Write modem supported LTE bands as a LOG message
 */
void modem_info_log_sup_band(void);

/**
 * @brief Write modem tracking area code as a LOG message
 */
void modem_info_log_area_code(void);

/**
 * @brief Write modem current mode as a LOG message
 */
void modem_info_log_ue_mode(void);

/**
 * @brief Write modem current operator name as a LOG message
 */
void modem_info_log_operator(void);

/**
 * @brief Write modem cell ID as a LOG message
 */
void modem_info_log_cell_id(void);

/**
 * @brief Write modem IP address as a LOG message
 */
void modem_info_log_ip_address(void);

/**
 * @brief Write modem firmware version as a LOG message
 */
void modem_info_log_fw_version(void);

/**
 * @brief Write modem LTE-M support mode as a LOG message
 */
void modem_info_log_lte_mode(void);

/**
 * @brief Write modem NB-IoT support mode as a LOG message
 */
void modem_info_log_nbiot_mode(void);

/**
 * @brief Write modem GPS support mode as a LOG message
 */
void modem_info_log_gps_mode(void);

/**
 * @brief Write modem mobile network time and date as a LOG message
 */
void modem_info_log_date_time(void);

#endif /* CONFIG_MODEM_INFO */

/**
 * @brief Write network information as a LOG message
 *
 * @retval 0 On success
 * @retval <0 On failure
 */
int network_info_log(void);

#endif /* __NETWORK_INFO_H__ */
