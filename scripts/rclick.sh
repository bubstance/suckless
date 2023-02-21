#!/bin/sh

xmenu <<EOF | sh &
applications
	accessories
		IMG:$HOME/.config/xmenu/icons/calc.png		calculator	xcalc
		IMG:$HOME/.config/xmenu/icons/emacs.png		emacs		emacs
		IMG:$HOME/.config/xmenu/icons/helix.png		helix		st -e hx
		IMG:$HOME/.config/xmenu/icons/htop.png		htop		st -e htop
		IMG:$HOME/.config/xmenu/icons/ranger.png	lf		st -e lfub
		IMG:$HOME/.config/xmenu/icons/nvim.png		neovim		st -e nvim
	audio + video
		IMG:$HOME/.config/xmenu/icons/ncmpcpp.png	ncmpcpp		st -e ncmpcpp
		IMG:$HOME/.config/xmenu/icons/mediainfo.xpm	mediainfo		mediainfo-gui
		IMG:$HOME/.config/xmenu/icons/mpv.png	mpv		mpv --player-operation-mode=pseudo-gui
	graphics
		IMG:$HOME/.config/xmenu/icons/gimp.png		gimp		gimp
		IMG:$HOME/.config/xmenu/icons/scrot.png		screenshooter		maimpick
	internet
		IMG:$HOME/.config/xmenu/icons/librewolf.png	librewolf	librewolf
		IMG:$HOME/.config/xmenu/icons/links.png		links		st -e links
		IMG:$HOME/.config/xmenu/icons/web.png		lynx		st -e lynx
		IMG:$HOME/.config/xmenu/icons/netsurf.xpm		netsurf		netsurf-gtk3
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
	settings
		volume mixer		st -e alsamixer
		compositor settings	st -e nvim $HOME/.config/picom/picom.conf
open terminal...
	IMG:$HOME/.config/xmenu/icons/st.png		st 	st
	IMG:$HOME/.config/xmenu/icons/st.png		st (tabbed) 	tabterm
	IMG:$HOME/.config/xmenu/icons/xterm-color.png		xterm 	xterm
kill window...		xkill
EOF
