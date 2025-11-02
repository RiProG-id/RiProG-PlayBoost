#!/system/bin/sh
(
	# Wait until boot completed
	while [ -z "$(getprop sys.boot_completed)" ]; do
		sleep 5
	done

	# Remove package if installed
	if pm list packages | grep -q com.riprog.toast; then
		pm uninstall com.riprog.toast
	fi
) &
