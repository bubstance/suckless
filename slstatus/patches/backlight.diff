diff --git a/Makefile b/Makefile
index 3be46cc..93dc2c5 100644
--- a/Makefile
+++ b/Makefile
@@ -6,6 +6,7 @@ include config.mk
 
 REQ = util
 COM =\
+	components/backlight\
 	components/battery\
 	components/cpu\
 	components/datetime\
diff --git a/components/backlight.c b/components/backlight.c
new file mode 100644
index 0000000..74f4c08
--- /dev/null
+++ b/components/backlight.c
@@ -0,0 +1,59 @@
+/* See LICENSE file for copyright and license details. */
+
+#include <stddef.h>
+
+#include "../util.h"
+
+#if defined(__linux__)
+	#include <limits.h>
+
+	#define BRIGHTNESS_MAX "/sys/class/backlight/%s/max_brightness"
+	#define BRIGHTNESS_CUR "/sys/class/backlight/%s/brightness"
+
+	const char *
+	backlight_perc(const char *card)
+	{
+		char path[PATH_MAX];
+		int max, cur;
+
+		if (esnprintf(path, sizeof (path), BRIGHTNESS_MAX, card) < 0 ||
+			pscanf(path, "%d", &max) != 1) {
+			return NULL;
+		}
+
+		if (esnprintf(path, sizeof (path), BRIGHTNESS_CUR, card) < 0 ||
+			pscanf(path, "%d", &cur) != 1) {
+			return NULL;
+		}
+
+		if (max == 0) {
+			return NULL;
+		}
+
+		return bprintf("%d%%", cur * 100 / max);
+	}
+#elif defined(__OpenBSD__)
+	#include <fcntl.h>
+	#include <sys/ioctl.h>
+	#include <sys/time.h>
+	#include <dev/wscons/wsconsio.h>
+
+	const char *
+	backlight_perc(const char *unused)
+	{
+		int fd, err;
+		struct wsdisplay_param wsd_param = {
+			.param = WSDISPLAYIO_PARAM_BRIGHTNESS
+		};
+
+		if ((fd = open("/dev/ttyC0", O_RDONLY)) < 0) {
+			warn("could not open /dev/ttyC0");
+			return NULL;
+		}
+		if ((err = ioctl(fd, WSDISPLAYIO_GETPARAM, &wsd_param)) < 0) {
+			warn("ioctl 'WSDISPLAYIO_GETPARAM' failed");
+			return NULL;
+		}
+		return bprintf("%d", wsd_param.curval * 100 / wsd_param.max);
+	}
+#endif
diff --git a/config.def.h b/config.def.h
index 5f6c114..69c5d50 100644
--- a/config.def.h
+++ b/config.def.h
@@ -12,6 +12,9 @@ static const char unknown_str[] = "n/a";
 /*
  * function            description                     argument (example)
  *
+ * backlight_perc      backlight percentage            device name
+ *                                                     (intel_backlight)
+ *                                                     NULL on OpenBSD
  * battery_perc        battery percentage              battery name (BAT0)
  *                                                     NULL on OpenBSD/FreeBSD
  * battery_state       battery charging state          battery name (BAT0)
diff --git a/slstatus.h b/slstatus.h
index f3b4979..e1759a0 100644
--- a/slstatus.h
+++ b/slstatus.h
@@ -1,5 +1,8 @@
 /* See LICENSE file for copyright and license details. */
 
+/* backlight */
+const char *backlight_perc(const char *);
+
 /* battery */
 const char *battery_perc(const char *);
 const char *battery_state(const char *);
