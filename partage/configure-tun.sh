tun_name=$1
ip addr add fc00:1234:ffff::1/64 dev $tun_name
ip link set $tun_name up
#ip -6 route add default via fc00:1234:ffff::1 dev $tun_name