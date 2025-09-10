#!/system/bin/sh
while [ -z "$(getprop sys.boot_completed)" ]; do
	sleep 5
done
if pm list packages | grep -q com.riprog.toast; then
	pm uninstall com.riprog.toast
fi
