#!/bin/bash
tunname=$1

#echo Activation de l\'interface $tunname
ip link set $tunname up
#echo Attribution de l\'adresse IP 172.16.2.1/28 à $tunname
ip addr add 172.16.2.1/28 dev $tunname
#echo Attribution d\'une route par défaut vers $tunname
ip route add default via 172.16.2.1
#echo Configuarion de $tunname terminée
