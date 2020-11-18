# Configuration eth1 et eth2
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
    - ipaddr: 172.16.2.132
    - netmask: 28

eth2:
  network.managed:
    - enabled: True
    - type: eth
    - proto: none
    - ipaddr: 172.16.2.162
    - netmask: 28

## Add routes: 
## Todo: Configuration de la route vers: LAN3-6 via VM1(eth1), LAN1-6 via VM1(eth1), 
##                                       LAN4-6 via VM3(eth2), LAN2-6 via VM3(eth2)

routes:
  network.routes:
    - name: eth1
    - routes:
      - name: LAN3-6
        ipaddr: fc00:1234:3::/64
        gateway: 172.16.2.128/28
      - name: LAN1-6
        ipaddr: fc00:1234:1::/64
        gateway: 172.16.2.128/28

    - name: eth2
    - routes:
      - name: LAN4-6
        ipaddr: fc00:1234:4::/64
        gateway: 172.16.2.163
      - name: LAN2-6
        ipaddr: fc00:1234:2::/64
        gateway: 172.16.2.163


## But enable ipv4 forwarding
net.ipv4.ip_forward:
  sysctl:
    - present
    - value: 1





