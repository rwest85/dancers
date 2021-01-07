#

### Some packets

```
Svarog:~ root# tcpdump  -i en0 -s 1500 -nn -vv -XX 'tcp port 53 || udp port 53'
tcpdump: listening on en0, link-type EN10MB (Ethernet), capture size 1500 bytes
20:58:48.474264 IP (tos 0x0, ttl 255, id 26954, offset 0, flags [none], proto UDP (17), length 56)
    192.168.1.44.58414 > 1.1.1.1.53: [udp sum ok] 58863+ A? google.com. (28)
	0x0000:  a84e 3fdf 4112 80e6 5024 c1f6 0800 4500  .N?.A...P$....E.
	0x0010:  0038 694a 0000 ff11 8e94 c0a8 012c 0101  .8iJ.........,..
	0x0020:  0101 e42e 0035 0024 5dc3 e5ef 0100 0001  .....5.$].......
	0x0030:  0000 0000 0000 0667 6f6f 676c 6503 636f  .......google.co
	0x0040:  6d00 0001 0001                           m.....
20:58:48.509304 IP (tos 0x0, ttl 59, id 11952, offset 0, flags [DF], proto UDP (17), length 72)
    1.1.1.1.53 > 192.168.1.44.58414: [udp sum ok] 58863 q: A? google.com. 1/0/0 google.com. A 216.58.217.46 (44)
	0x0000:  80e6 5024 c1f6 a84e 3fdf 4112 0800 4500  ..P$...N?.A...E.
	0x0010:  0048 2eb0 4000 3b11 4d1f 0101 0101 c0a8  .H..@.;.M.......
	0x0020:  012c 0035 e42e 0034 6b69 e5ef 8180 0001  .,.5...4ki......
	0x0030:  0001 0000 0000 0667 6f6f 676c 6503 636f  .......google.co
	0x0040:  6d00 0001 0001 c00c 0001 0001 0000 003c  m..............<
	0x0050:  0004 d83a d92e                           ...:..
20:59:08.123422 IP (tos 0x0, ttl 255, id 24979, offset 0, flags [none], proto UDP (17), length 72)
```

```
20:59:08.123422 IP (tos 0x0, ttl 255, id 24979, offset 0, flags [none], proto UDP (17), length 72)
    192.168.1.44.54725 > 1.1.1.1.53: [udp sum ok] 8775+ AAAA? e17437.dscb.akamaiedge.net. (44)
	0x0000:  a84e 3fdf 4112 80e6 5024 c1f6 0800 4500  .N?.A...P$....E.
	0x0010:  0048 6193 0000 ff11 963b c0a8 012c 0101  .Ha......;...,..
	0x0020:  0101 d5c5 0035 0034 df4c 2247 0100 0001  .....5.4.L"G....
	0x0030:  0000 0000 0000 0665 3137 3433 3704 6473  .......e17437.ds
	0x0040:  6362 0a61 6b61 6d61 6965 6467 6503 6e65  cb.akamaiedge.ne
	0x0050:  7400 001c 0001                           t.....
20:59:08.123627 IP (tos 0x0, ttl 255, id 39200, offset 0, flags [none], proto UDP (17), length 72)
    192.168.1.44.65077 > 1.1.1.1.53: [udp sum ok] 64136+ A? e17437.dscb.akamaiedge.net. (44)
	0x0000:  a84e 3fdf 4112 80e6 5024 c1f6 0800 4500  .N?.A...P$....E.
	0x0010:  0048 9920 0000 ff11 5eae c0a8 012c 0101  .H......^....,..
	0x0020:  0101 fe35 0035 0034 deb5 fa88 0100 0001  ...5.5.4........
	0x0030:  0000 0000 0000 0665 3137 3433 3704 6473  .......e17437.ds
	0x0040:  6362 0a61 6b61 6d61 6965 6467 6503 6e65  cb.akamaiedge.ne
	0x0050:  7400 0001 0001                           t.....
20:59:08.158459 IP (tos 0x0, ttl 59, id 4874, offset 0, flags [DF], proto UDP (17), length 128)
```

```
21:08:47.055989 IP (tos 0x0, ttl 64, id 38261, offset 0, flags [none], proto UDP (17), length 81)
    192.168.1.44.49579 > 205.251.193.26.53: [udp sum ok] 49834+ [1au] NS? delegation-test.ventx.de. ar: . OPT UDPsize=4096 (53)
	0x0000:  a84e 3fdf 4112 80e6 5024 c1f6 0800 4500  .N?.A...P$....E.
	0x0010:  0051 9575 0000 4011 943c c0a8 012c cdfb  .Q.u..@..<...,..
	0x0020:  c11a c1ab 0035 003d bde4 c2aa 0120 0001  .....5.=........
	0x0030:  0000 0000 0001 0f64 656c 6567 6174 696f  .......delegatio
	0x0040:  6e2d 7465 7374 0576 656e 7478 0264 6500  n-test.ventx.de.
	0x0050:  0002 0001 0000 2910 0000 0000 0000 00    ......)........
21:08:47.178453 IP (tos 0x0, ttl 246, id 262, offset 0, flags [none], proto UDP (17), length 221)
    205.251.193.26.53 > 192.168.1.44.49579: [udp sum ok] 49834*- q: NS? delegation-test.ventx.de. 4/0/1 delegation-test.ventx.de. NS ns-1527.awsdns-62.org., delegation-test.ventx.de. NS ns-1926.awsdns-48.co.uk., delegation-test.ventx.de. NS ns-282.awsdns-35.com., delegation-test.ventx.de. NS ns-670.awsdns-19.net. ar: . OPT UDPsize=4096 (193)
	0x0000:  80e6 5024 c1f6 a84e 3fdf 4112 0800 4500  ..P$...N?.A...E.
	0x0010:  00dd 0106 0000 f611 721f cdfb c11a c0a8  ........r.......
	0x0020:  012c 0035 c1ab 00c9 bda0 c2aa 8500 0001  .,.5............
	0x0030:  0004 0000 0001 0f64 656c 6567 6174 696f  .......delegatio
	0x0040:  6e2d 7465 7374 0576 656e 7478 0264 6500  n-test.ventx.de.
	0x0050:  0002 0001 c00c 0002 0001 0002 a300 0017  ................
	0x0060:  076e 732d 3135 3237 0961 7773 646e 732d  .ns-1527.awsdns-
	0x0070:  3632 036f 7267 00c0 0c00 0200 0100 02a3  62.org..........
	0x0080:  0000 1907 6e73 2d31 3932 3609 6177 7364  ....ns-1926.awsd
	0x0090:  6e73 2d34 3802 636f 0275 6b00 c00c 0002  ns-48.co.uk.....
	0x00a0:  0001 0002 a300 0016 066e 732d 3238 3209  .........ns-282.
	0x00b0:  6177 7364 6e73 2d33 3503 636f 6d00 c00c  awsdns-35.com...
	0x00c0:  0002 0001 0002 a300 0016 066e 732d 3637  ...........ns-67
	0x00d0:  3009 6177 7364 6e73 2d31 3903 6e65 7400  0.awsdns-19.net.
	0x00e0:  0000 2910 0000 0000 0000 00              ..)........
```

```
17:29:24.323016 IP (tos 0x0, ttl 64, id 45185, offset 0, flags [none], proto UDP (17), length 67)
    192.168.1.44.61442 > 1.1.1.1.53: [udp sum ok] 35329+ [1au] TXT? google.com. ar: . OPT UDPsize=4096 (39)
	0x0000:  a84e 3fdf 4112 80e6 5024 c1f6 0800 4500  .N?.A...P$....E.
	0x0010:  0043 b081 0000 4011 0653 c0a8 012c 0101  .C....@..S...,..
	0x0020:  0101 f002 0035 002f 8487 8a01 0120 0001  .....5./........
	0x0030:  0000 0000 0001 0667 6f6f 676c 6503 636f  .......google.co
	0x0040:  6d00 0010 0001 0000 2910 0000 0000 0000  m.......).......
	0x0050:  00
```
    1.1.1.1.53 > 192.168.1.44.61442: [udp sum ok] 35329 q: TXT? google.com. 5/0/1 google.com. TXT "facebook-domain-verification=22rm551cu4k0ab0bxsw536tlds4h95", google.com. TXT "docusign=1b0a6754-49b1-4db5-8540-d2c12664b289", google.com. TXT "docusign=05958488-4752-4ef2-95eb-aa7ba8a3bd0e", google.com. TXT "globalsign-smime-dv=CDYX+XFHUw2wml6/Gb8+59BsH31KzUr6c1l2BPvqKX8=", google.com. TXT "v=spf1 include:_spf.google.com ~all" ar: . OPT UDPsize=1232 (352)
	0x0000:  80e6 5024 c1f6 a84e 3fdf 4112 0800 4500  ..P$...N?.A...E.
	0x0010:  017c 6496 4000 3b11 1605 0101 0101 c0a8  .|d.@.;.........
	0x0020:  012c 0035 f002 0168 9eb4 8a01 8180 0001  .,.5...h........
	0x0030:  0005 0000 0001 0667 6f6f 676c 6503 636f  .......google.co
	0x0040:  6d00 0010 0001 c00c 0010 0001 0000 0e0e  m...............
	0x0050:  003c 3b66 6163 6562 6f6f 6b2d 646f 6d61  .<;facebook-doma
	0x0060:  696e 2d76 6572 6966 6963 6174 696f 6e3d  in-verification=
	0x0070:  3232 726d 3535 3163 7534 6b30 6162 3062  22rm551cu4k0ab0b
	0x0080:  7873 7735 3336 746c 6473 3468 3935 c00c  xsw536tlds4h95..
	0x0090:  0010 0001 0000 012a 002e 2d64 6f63 7573  .......*..-docus
	0x00a0:  6967 6e3d 3162 3061 3637 3534 2d34 3962  ign=1b0a6754-49b
	0x00b0:  312d 3464 6235 2d38 3534 302d 6432 6331  1-4db5-8540-d2c1
	0x00c0:  3236 3634 6232 3839 c00c 0010 0001 0000  2664b289........
	0x00d0:  012a 002e 2d64 6f63 7573 6967 6e3d 3035  .*..-docusign=05
	0x00e0:  3935 3834 3838 2d34 3735 322d 3465 6632  958488-4752-4ef2
	0x00f0:  2d39 3565 622d 6161 3762 6138 6133 6264  -95eb-aa7ba8a3bd
	0x0100:  3065 c00c 0010 0001 0000 0e0e 0041 4067  0e...........A@g
	0x0110:  6c6f 6261 6c73 6967 6e2d 736d 696d 652d  lobalsign-smime-
	0x0120:  6476 3d43 4459 582b 5846 4855 7732 776d  dv=CDYX+XFHUw2wm
	0x0130:  6c36 2f47 6238 2b35 3942 7348 3331 4b7a  l6/Gb8+59BsH31Kz
	0x0140:  5572 3663 316c 3242 5076 714b 5838 3dc0  Ur6c1l2BPvqKX8=.
	0x0150:  0c00 1000 0100 000e 0e00 2423 763d 7370  ..........$#v=sp
	0x0160:  6631 2069 6e63 6c75 6465 3a5f 7370 662e  f1.include:_spf.
	0x0170:  676f 6f67 6c65 2e63 6f6d 207e 616c 6c00  google.com.~all.
	0x0180:  0029 04d0 0000 0000 0000                 .)........
```


Probit domainkey

```
➜  dancers git:(main) ✗ dig txt mail._domainkey.probit.ca >a 2>b
06:45:32.638419 IP (tos 0x0, ttl 64, id 26998, offset 0, flags [none], proto UDP (17), length 82)
    192.168.1.44.62076 > 1.1.1.1.53: [udp sum ok] 52101+ [1au] TXT? mail._domainkey.probit.ca. ar: . OPT UDPsize=4096 (54)
	0x0000:  a84e 3fdf 4112 80e6 5024 c1f6 0800 4500  .N?.A...P$....E.
	0x0010:  0052 6976 0000 4011 4d4f c0a8 012c 0101  .Riv..@.MO...,..
	0x0020:  0101 f27c 0035 003e d26b cb85 0120 0001  ...|.5.>.k......
	0x0030:  0000 0000 0001 046d 6169 6c0a 5f64 6f6d  .......mail._dom
	0x0040:  6169 6e6b 6579 0670 726f 6269 7402 6361  ainkey.probit.ca
	0x0050:  0000 1000 0100 0029 1000 0000 0000 0000  .......)........
06:45:32.673441 IP (tos 0x0, ttl 59, id 45484, offset 0, flags [DF], proto UDP (17), length 498)
    1.1.1.1.53 > 192.168.1.44.62076: [udp sum ok] 52101 q: TXT? mail._domainkey.probit.ca. 1/0/1 mail._domainkey.probit.ca. TXT "v=DKIM1;p=MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA7Jo7oZ652GtvzEs0xx7LlYgKHqBH7PR2TgQvy7+s5i08wpoz/CiaS2TSEWacxf9ASBjLr0fVhQn+hxFY0RELG2vKmKkNR8AQFITrm8KwGl36bwXJ72vraJqwZVo/RFaYR4ERJRjG2mKHtT75UI5VE4eFY3CxUpuyXOpjOhs0PHLacKtmz3kZi/UmeIOAuebwAJYbFSQ2y" "7KzX0QSfccsm7ZHEM4zURQ+xHPK6kdlNwThhkTkbEWolNLTCjK1gPtTSZkZj3uwGW3n68UhVubjIhiDTATIVMk9Gk0W0dSOfWK90P2H8OVev5wVSUK2vX8C5pt+ngIAxD3fgP5/vV6/9QIDAQAB" ar: . OPT UDPsize=1232 (470)
	0x0000:  80e6 5024 c1f6 a84e 3fdf 4112 0800 4500  ..P$...N?.A...E.
	0x0010:  01f2 b1ac 4000 3b11 c878 0101 0101 c0a8  ....@.;..x......
	0x0020:  012c 0035 f27c 01de c74d cb85 8180 0001  .,.5.|...M......
	0x0030:  0001 0000 0001 046d 6169 6c0a 5f64 6f6d  .......mail._dom
	0x0040:  6169 6e6b 6579 0670 726f 6269 7402 6361  ainkey.probit.ca
	0x0050:  0000 1000 01c0 0c00 1000 0100 0001 0f01  ................
	0x0060:  94ff 763d 444b 494d 313b 703d 4d49 4942  ..v=DKIM1;p=MIIB
	0x0070:  496a 414e 4267 6b71 686b 6947 3977 3042  IjANBgkqhkiG9w0B
	0x0080:  4151 4546 4141 4f43 4151 3841 4d49 4942  AQEFAAOCAQ8AMIIB
	0x0090:  4367 4b43 4151 4541 374a 6f37 6f5a 3635  CgKCAQEA7Jo7oZ65
	0x00a0:  3247 7476 7a45 7330 7878 374c 6c59 674b  2GtvzEs0xx7LlYgK
	0x00b0:  4871 4248 3750 5232 5467 5176 7937 2b73  HqBH7PR2TgQvy7+s
	0x00c0:  3569 3038 7770 6f7a 2f43 6961 5332 5453  5i08wpoz/CiaS2TS
	0x00d0:  4557 6163 7866 3941 5342 6a4c 7230 6656  EWacxf9ASBjLr0fV
	0x00e0:  6851 6e2b 6878 4659 3052 454c 4732 764b  hQn+hxFY0RELG2vK
	0x00f0:  6d4b 6b4e 5238 4151 4649 5472 6d38 4b77  mKkNR8AQFITrm8Kw
	0x0100:  476c 3336 6277 584a 3732 7672 614a 7177  Gl36bwXJ72vraJqw
	0x0110:  5a56 6f2f 5246 6159 5234 4552 4a52 6a47  ZVo/RFaYR4ERJRjG
	0x0120:  326d 4b48 7454 3735 5549 3556 4534 6546  2mKHtT75UI5VE4eF
	0x0130:  5933 4378 5570 7579 584f 706a 4f68 7330  Y3CxUpuyXOpjOhs0
	0x0140:  5048 4c61 634b 746d 7a33 6b5a 692f 556d  PHLacKtmz3kZi/Um
	0x0150:  6549 4f41 7565 6277 414a 5962 4653 5132  eIOAuebwAJYbFSQ2
	0x0160:  7993 374b 7a58 3051 5366 6363 736d 375a  y.7KzX0QSfccsm7Z
	0x0170:  4845 4d34 7a55 5251 2b78 4850 4b36 6b64  HEM4zURQ+xHPK6kd
	0x0180:  6c4e 7754 6868 6b54 6b62 4557 6f6c 4e4c  lNwThhkTkbEWolNL
	0x0190:  5443 6a4b 3167 5074 5453 5a6b 5a6a 3375  TCjK1gPtTSZkZj3u
	0x01a0:  7747 5733 6e36 3855 6856 7562 6a49 6869  wGW3n68UhVubjIhi
	0x01b0:  4454 4154 4956 4d6b 3947 6b30 5730 6453  DTATIVMk9Gk0W0dS
	0x01c0:  4f66 574b 3930 5032 4838 4f56 6576 3577  OfWK90P2H8OVev5w
	0x01d0:  5653 554b 3276 5838 4335 7074 2b6e 6749  VSUK2vX8C5pt+ngI
	0x01e0:  4178 4433 6667 5035 2f76 5636 2f39 5149  AxD3fgP5/vV6/9QI
	0x01f0:  4441 5141 4200 0029 04d0 0000 0000 0000  DAQAB..)........
```

