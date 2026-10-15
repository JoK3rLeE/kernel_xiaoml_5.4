# SPDX-License-Identifier: GPL-2.0

# Xiaomi Cepheus (SM8150) board DTBs.
dtb-$(CONFIG_ARCH_SM8150) += sm8150-xiaomi.dtb sm8150-v2-xiaomi.dtb

ifeq ($(CONFIG_BUILD_ARM64_DT_OVERLAY),y)
dtbo-$(CONFIG_ARCH_SM8150) += cepheus-sm8150-overlay.dtbo
cepheus-sm8150-overlay.dtbo-base := sm8150-xiaomi.dtb sm8150-v2-xiaomi.dtb
endif
