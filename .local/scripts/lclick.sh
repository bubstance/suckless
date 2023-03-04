#!/bin/sh

xmenu <<EOF | sh &
applications
	accessories
		IMG:$HOME/.config/xmenu/icons/calc.png		calculator	galculator
		IMG:$HOME/.config/xmenu/icons/htop.png		htop		st -e htop
		IMG:$HOME/.config/xmenu/icons/ranger.png	lf		st -e lfub
		IMG:$HOME/.config/xmenu/icons/nvim.png		neovim		st -e nvim
		IMG:$HOME/.config/xmenu/icons/system-file-manager.png	pcmanfm		pcmanfm > /dev/null 2>&1
	audio + video
		IMG:$HOME/.config/xmenu/icons/ncmpcpp.png	ncmpcpp		st -e ncmpcpp
		IMG:$HOME/.config/xmenu/icons/mediainfo.xpm	mediainfo		mediainfo-gui
		IMG:$HOME/.config/xmenu/icons/mpv.png	mpv		mpv --player-operation-mode=pseudo-gui
	graphics
		IMG:$HOME/.config/xmenu/icons/gimp.png		gimp		gimp
		IMG:$HOME/.config/xmenu/icons/scrot.png		screenshooter		maimpick
	internet
		IMG:$HOME/.config/xmenu/icons/librewolf.png	librewolf	librewolf > /dev/null 2>&1
		IMG:$HOME/.config/xmenu/icons/thunderbird.png	thunderbird	thunderbird-bin > /dev/null 2>&1
		IMG:$HOME/.config/xmenu/icons/web.png		w3m		st -e w3m duckduckgo.com
	office
		IMG:$HOME/.config/xmenu/icons/libreoffice.png	LibreOffice	libreoffice
		IMG:$HOME/.config/xmenu/icons/libreoffice-base.png	LibreOffice Base	libreoffice --base
		IMG:$HOME/.config/xmenu/icons/libreoffice-calc.png	LibreOffice Calc	libreoffice --calc
		IMG:$HOME/.config/xmenu/icons/libreoffice-draw.png	LibreOffice Draw	libreoffice --draw
		IMG:$HOME/.config/xmenu/icons/libreoffice-impress.png	LibreOffice Impress	libreoffice --impress
		IMG:$HOME/.config/xmenu/icons/libreoffice-math.png	LibreOffice Math	libreoffice --math
		IMG:$HOME/.config/xmenu/icons/libreoffice-writer.png	LibreOffice Writer	libreoffice --writer
		IMG:$HOME/.config/xmenu/icons/sc-im.png	sc-im	st -e sc-im
		IMG:$HOME/.config/xmenu/icons/zathura.svg	zathura	zathura
	plan9 tools
		IMG:$HOME/.config/xmenu/icons/9.png		9term 	9 9term rc
		IMG:$HOME/.config/xmenu/icons/9.png		acme	acme
		IMG:$HOME/.config/xmenu/icons/9.png		ivy 	9 9term ivy -prompt "%> "
		IMG:$HOME/.config/xmenu/icons/9.png		sam 	sam
open terminal...
	IMG:$HOME/.config/xmenu/icons/st.png		st 	st
	IMG:$HOME/.config/xmenu/icons/st.png		st (multiplexed) 	st -e tmux
	IMG:$HOME/.config/xmenu/icons/st.png		st (tabbed) 	tabterm
settings
	set wallpaper		wallpick
	volume mixer		st -e alsamixer
	compositor settings	st -e nvim $HOME/.config/picom/picom.conf
kill window...		xkill
run...			dmenu_run -F -c -l 10 -g 5 -p "Run:" -nb "#191724" -nf "#e0def4" -sb "#31748f" -sf "#e0def4" -nhb "#191724" -nhf "#31748f" -shb "#31748f" -shf "#eb6f92"

lock			slock
reboot			sudo reboot
shutdown		sudo poweroff
EOF