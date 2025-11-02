#!/system/bin/sh
sleep 2
ui_print "Author:"
ui_print "Telegram: @RiProG | Channel: @RiOpSo | Group: @RiOpSoDisc"
ui_print "Support me on Sociabuzz:"
ui_print "http://sociabuzz.com/RiProG/tribe"
sleep 2
ui_print "Extracting module files"
architecture=$(uname -m)
if [ -f "$MODPATH/system/bin/RPB" ]; then
	ui_print "Default binary detected. Skipping architecture detection."
else
	ui_print "Detected architecture: $architecture"
	case "$architecture" in
	armv7l | armv8l)
		ui_print "Architecture $architecture is supported."
		ui_print "Installation continues."
		cp "$MODPATH/system/bin/RPB_arm" "$MODPATH/system/bin/RPB"
		;;
	aarch64)
		ui_print "Architecture $architecture is supported."
		ui_print "Installation continues."
		cp "$MODPATH/system/bin/RPB_arm64" "$MODPATH/system/bin/RPB"
		;;
	*)
		ui_print "Architecture $architecture is not supported."
		ui_print "Installation aborted."
		rm -rf "$MODPATH"
		exit 1
		;;
	esac
fi
chmod +x "$MODPATH/system/bin/RPB"
rm -f "$MODPATH/system/bin/RPB_arm"
rm -f "$MODPATH/system/bin/RPB_arm64"
if [ ! -z "$AXERON" ]; then
	ui_print "----------------------------------------"
	ui_print "⚠️  WARNING:"
	ui_print "- AXERON mode detected."
	ui_print "- This module runs with SU privileges."
	ui_print "----------------------------------------"
	sleep 2
fi
exec 3>&1 4>&2
exec >/dev/null 2>&1
if [ -z "$AXERON" ]; then
	applist=/storage/emulated/0/Android/RPB_applist.txt
	echo "debug.riprog.RPB=standard" >"$MODPATH/system.prop"
	pm disable-user --user 0 com.android.vending
	if ! pm list packages | grep -q com.riprog.toast; then
		pm install "$MODPATH/toast.apk" >/dev/null 2>&1
		if ! pm list packages | grep -q com.riprog.toast; then
			cp "$MODPATH/toast.apk" /data/local/tmp >/dev/null 2>&1
			pm install /data/local/tmp/toast.apk >/dev/null 2>&1
			rm /data/local/tmp/toast.apk
		fi
		rm "$MODPATH/toast.apk"
	fi
	pm enable --user 0 com.android.vending
else
	applist=/data/data/com.android.shell/AxManager/bin/added_apps.txt
	echo "debug.riprog.RPB=axeron" >"$MODPATH/system.prop"
	rm "$MODPATH/uninstall.sh"
fi
exec 1>&3 2>&4
if [ -z "$AXERON" ]; then
	ui_print "App list saved to $applist"
	ui_print "Edit applist manually if you want to add or remove apps."
else
	ui_print "You can add or remove apps in AxManager applist"
fi
ui_print "Adding template gamelist to applist"
echo "com.example.gamelist" >"$applist"
counter=1
package_list=$(pm list packages | cut -f 2 -d :)
app_list=$(cat "$MODPATH/gamelist.txt")
echo "$app_list" | while IFS= read -r applist_line; do
	line=$(echo "$applist_line" | grep -v " ")
	if echo "$package_list" | grep -q "$line"; then
		ui_print "  $counter. $line"
		counter=$((counter + 1))
	else
		sed -i "/$line/d" "$MODPATH/gamelist.txt"
	fi
done
cat "$MODPATH/gamelist.txt" >>"$applist"
sed -i '$!N; /^\(.*\)\n\1$/!P; D' "$applist"
rm "$MODPATH/gamelist.txt"
