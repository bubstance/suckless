#!/bin/sh

cat <<EOF | xmenu
[M] monocle			0
[]= tile			1
[D]= deck			2
[@] spiral			3
[\\] dwindle		4
TTT bstack			5
=== bstackhoriz		6
HHH grid			7
### nrowgrid		8
--- horizgrid		9
::: gaplessgrid		10
|M| centeredmaster	11
>M> centeredfloatingmaster	12
><> float			13
EOF
