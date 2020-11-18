# Configuration eth1
# RAPPEL: eth0 est à vagrant, ne pas y toucher

## Désactivation de network-manager
NetworkManager:
  service:
    - dead
    - enable: False
    
## Suppression de la passerelle par défaut
ip route del default:
  cmd:
    - run

## Configuration de VM2
eth1:
  network.managed:
    - enabled: True
    - type: eth
    - proto: none
    - enable_ipv4: false
    - ipv6proto: static
    - enable_ipv6: true
    - ipv6_autoconf: no
    - ipv6ipaddr: fc00:1234:1::26
    - ipv6netmask: 64

eth2:
  network.managed:
    - enabled: True
    - type: eth
    - proto: none
    - enable_ipv4: false
    - ipv6proto: static
    - enable_ipv6: true
    - ipv6_autoconf: no
    - ipv6ipaddr: fc00:1234:2::26
    - ipv6netmask: 64

## Todo: Configuration de la route vers: LAN3-6 via VM1-6(eth1), LAN1 via VM1-6(eth1), 
##                                       LAN4-6 via VM3-6(eth2), LAN2 via VM3-6(eth2)

routes:
  network.routes:
    - name: eth1
    - routes:
      - name: LAN3-6
        ipaddr: fc00:1234:3::/64
        gateway: fc00:1234:1::16
      - name: LAN1
        ipaddr: 172.16.2.128/28
        gateway: fc00:1234:1::16

    - name: eth2
    - routes:
      - name: LAN4-6
        ipaddr: fc00:1234:4::/64
        gateway: fc00:1234:2::36
      - name: LAN2
        ipaddr: 172.16.2.160/28
        gateway: fc00:1234:2::36

## But enable ipv6 forwarding
net.ipv6.conf.all.forwarding:
  sysctl:
    - present
    - value: 1
