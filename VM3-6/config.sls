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

##Configuration de VM3
eth1:
  network.managed:
    - enabled: True
    - type: eth
    - proto: none
    - enable_ipv4: false
    - ipv6proto: static
    - enable_ipv6: true
    - ipv6_autoconf: no
    - ipv6ipaddr: fc00:1234:2::36
    - ipv6netmask: 64

##Configuration de VM3-6 Lan4-6
eth2:
  network.managed:
    - enabled: True
    - type: eth
    - proto: none
    - enable_ipv4: false
    - ipv6proto: static
    - enable_ipv6: true
    - ipv6_autoconf: no
    - ipv6ipaddr: fc00:1234:4::36
    - ipv6netmask: 64

## Configuration de la route vers LAN1-6 via VM2-6
## Todo: Configuration de la route vers: LAN2 via VM3, LAN1 via VM3, LAN3-6 via VM3(eth1)
routes:
  network.routes:
    - name: eth1
    - routes:
      - name: LAN1-6
        ipaddr: fc00:1234:1::/64
        gateway: fc00:1234:2::26
      - name: LAN3-6
        ipaddr: fc00:1234:3::/64
        gateway: fc00:1234:2::26
    - name: eth2
    - routes:
      - name: LAN2
        ipaddr: 172.16.2.160/28
        gateway: fc00:1234:4::3
      - name: LAN1
        ipaddr: 172.16.2.128/28
        gateway: fc00:1234:4::3
        
## But enable ipv6 forwarding
net.ipv6.conf.all.forwarding:
  sysctl:
    - present
    - value: 1
