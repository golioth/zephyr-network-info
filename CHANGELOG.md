<!-- Copyright (c) 2023 Golioth, Inc. -->
<!-- SPDX-License-Identifier: Apache-2.0 -->

# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.2.1] 2024-10-28

### Changed

- Remove need to use application-based WiFi manager

## [1.2.0] 2024-09-04

### Changed
- Update zcbor syntax to work with ZCBOR v0.8.0 (NCS v2.7.0, Golioth Firmware SDK v0.15.0)

## [1.1.1] 2024-03-21

### Breaking Changes
- This library requires Golioth Firmware SDK v0.11.1 or newer which implements
  CONFIG_GOLIOTH_RPC_MAX_RESPONSE_LEN

### Changed
- Better checks and logs when zcbor encoding runs out of memory

## [1.1.0] 2024-02-09

### Changed
- Use Golioth Firmware SDK

### Fixed
- Fix zcbor calls in nRF7002 support

## [1.0.1] 2023-08-15

### Fixed
- Only build if the `CONFIG_NETWORK_INFO symbol is set`
- Make `ZCBOR` a dependency

## [1.0.0] 2023-08-15

### Breaking Changes
- This repo should now be added as a Zephyr module. For existing builds, this means:
  - Remove `add_subdirectory(src/network_info)` from CMakeLists.txt
  - In west.yml use a path like `modules/lib/network_info`
  - Include the library in your build: `CONFIG_NETWORK_INFO=y`

### Added
- Changelog

### Changed
- Use zcbor instead of qcbor
