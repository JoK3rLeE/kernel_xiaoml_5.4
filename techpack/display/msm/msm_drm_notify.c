// SPDX-License-Identifier: GPL-2.0
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/notifier.h>
#include <linux/msm_drm_notify.h>
#include <drm/drm_panel.h>

static BLOCKING_NOTIFIER_HEAD(msm_drm_notifier_list);

int msm_drm_register_client(struct notifier_block *nb)
{
	return blocking_notifier_chain_register(&msm_drm_notifier_list, nb);
}
EXPORT_SYMBOL_GPL(msm_drm_register_client);

int msm_drm_unregister_client(struct notifier_block *nb)
{
	return blocking_notifier_chain_unregister(&msm_drm_notifier_list, nb);
}
EXPORT_SYMBOL_GPL(msm_drm_unregister_client);

/*
 * The legacy touchscreen interface expects MSM_DRM_BLANK_* values. Translate
 * the 5.4 DRM panel notifier values instead of forwarding incompatible enums.
 */
int msm_drm_notifier_call_chain(unsigned long val, void *v)
{
	struct drm_panel_notifier *panel_event = v;
	struct msm_drm_notifier event;
	int blank;

	if (!panel_event || !panel_event->data)
		return -EINVAL;

	switch (*(int *)panel_event->data) {
	case DRM_PANEL_BLANK_UNBLANK:
		blank = MSM_DRM_BLANK_UNBLANK;
		break;
	case DRM_PANEL_BLANK_POWERDOWN:
		blank = MSM_DRM_BLANK_POWERDOWN;
		break;
	case DRM_PANEL_BLANK_LP:
		blank = MSM_DRM_BLANK_LP1;
		break;
	default:
		return NOTIFY_DONE;
	}

	event.id = MSM_DRM_PRIMARY_DISPLAY;
	event.data = &blank;
	return blocking_notifier_call_chain(&msm_drm_notifier_list, val, &event);
}
EXPORT_SYMBOL_GPL(msm_drm_notifier_call_chain);
