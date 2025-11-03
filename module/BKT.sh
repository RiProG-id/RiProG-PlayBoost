#!/system/bin/sh
while [ -z "$(getprop sys.boot_completed)" ]; do
	sleep 5
done
BACKDIR="$(pwd)"
if [ ! -d /data/adb/modules/BKT ]; then
	if pm list packages | grep -q com.riprog.toast; then
		pm uninstall com.riprog.toast
	fi
fi
ME="$(cd "$(dirname "$0")" && pwd)/$(basename "$0")"
cd "$BACKDIR" || exit
rm -f "$ME"
