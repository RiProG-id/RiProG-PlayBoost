#!/system/bin/sh
while [ -z "$(getprop sys.boot_completed)" ]; do
	sleep 5
done
if [ ! -d /data/adb/modules/RPB ]; then
	BACKDIR="$(pwd)"
	if pm list packages | grep -q com.riprog.toast; then
		pm uninstall com.riprog.toast
	fi
	ME="$(cd "$(dirname "$0")" && pwd)/$(basename "$0")"
	cd "$BACKDIR" || exit
	rm -f "$ME"
fi
