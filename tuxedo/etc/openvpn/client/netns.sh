#!/bin/bash

case "$script_type" in
		up)
				ip netns add vpn
				ip netns exec vpn ip link set dev lo up
				ip link set dev "$1" up netns vpn mtu "$2"
				ip netns exec vpn ip addr add dev "$1" "$4/${ifconfig_netmask:-30}" \
					${ifconfig_broadcast:+broadcast "$ifconfig_broadcast"}
				if [ -n "$ifconfig_ipv6_local" ]; then
					ip netns exec vpn ip addr add dev "$1" "$ifconfig_ipv6_local/112"
				fi
				;;
		route-up)
			ip netns exec vpn ip route add default via "$route_vpn_gateway"
			if [ -n "$ifconfig_ipv6_remote" ]; then
				ip netns exec vpn ip route add default via "$ifconfig_ipv6_remote"
			fi
			;;
		down)
			ip netns delete vpn
			;;
esac
