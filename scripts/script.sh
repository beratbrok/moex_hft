#!/bin/bash

route add -net 1.1.1.0 netmask 255.255.255.0 gateway         1.1.4.248
route add -net 239.192.0.0 netmask 255.255.0.0 gateway       1.1.4.248
route add -net 10.50.129.200 netmask 255.255.255.255 gateway 1.1.4.248
route add -net 10.50.129.90 netmask 255.255.255.255 gateway  1.1.4.248
route add -net 1.1.7.200 netmask 255.255.255.255 gateway     1.1.4.248

