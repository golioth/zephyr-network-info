<!-- Copyright (c) 2023 Golioth, Inc. -->
<!-- SPDX-License-Identifier: Apache-2.0 -->

# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.1.0] 2024-02-02

### Changed
- Use Golioth Firmware SDK

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
