#pragma once
#ifndef FIXTURES_H
#define FIXTURES_H

const uint8_t fixture_header[] = {0x84, 0xd9, 0x85, 0x00, 0x00, 0x01,
                                  0x00, 0x05, 0x00, 0x00, 0x00, 0x01};

const uint8_t __fixtures_packets_packet1_bin[] = {
    0x80,       0xe6, 0x50, 0x24, 0xc1,       0xf6, 0xa8, 0x4e, 0x3f, 0xdf,
    0x41,       0x12, 0x08, 0x00, 0x45,       0x00, 0x00, 0xdd, 0x01, 0x06,
    0x00,       0x00, 0xf6, 0x11, 0x72,       0x1f, 0xcd, 0xfb, 0xc1, 0x1a,
    0xc0,       0xa8, 0x01, 0x2c, 0x00,       0x35, 0xc1, 0xab, 0x00, 0xc9,
    0xbd,       0xa0, 0xc2, 0xaa, 0x85,       0x00, 0x00, 0x01, 0x00, 0x04,
    0x00,       0x00, 0x00, 0x01, /*1*/ 0x0f, 0x64, 0x65, 0x6c, 0x65, 0x67,
    0x61,       0x74, 0x69, 0x6f, 0x6e,       0x2d, 0x74, 0x65, 0x73, 0x74,
    0x05,       0x76, 0x65, 0x6e, 0x74,       0x78, 0x02, 0x64, 0x65, 0x00,
    0x00,       0x02, 0x00, 0x01, 0xc0,       0x0c, 0x00, 0x02, 0x00, 0x01,
    0x00,       0x02, 0xa3, 0x00, 0x00,       0x17,
    /*2*/ 0x07, 0x6e, 0x73, 0x2d, 0x31,       0x35, 0x32, 0x37, 0x09, 0x61,
    0x77,       0x73, 0x64, 0x6e, 0x73,       0x2d, 0x36, 0x32, 0x03, 0x6f,
    0x72,       0x67, 0x00, 0xc0, 0x0c,       0x00, 0x02, 0x00, 0x01, 0x00,
    0x02,       0xa3, 0x00, 0x00, 0x19,       0x07, 0x6e, 0x73, 0x2d, 0x31,
    0x39,       0x32, 0x36, 0x09, 0x61,       0x77, 0x73, 0x64, 0x6e, 0x73,
    0x2d,       0x34, 0x38, 0x02, 0x63,       0x6f, 0x02, 0x75, 0x6b, 0x00,
    0xc0,       0x0c, 0x00, 0x02, 0x00,       0x01, 0x00, 0x02, 0xa3, 0x00,
    0x00,       0x16, 0x06, 0x6e, 0x73,       0x2d, 0x32, 0x38, 0x32, 0x09,
    0x61,       0x77, 0x73, 0x64, 0x6e,       0x73, 0x2d, 0x33, 0x35, 0x03,
    0x63,       0x6f, 0x6d, 0x00, 0xc0,       0x0c, 0x00, 0x02, 0x00, 0x01,
    0x00,       0x02, 0xa3, 0x00, 0x00,       0x16, 0x06, 0x6e, 0x73, 0x2d,
    0x36,       0x37, 0x30, 0x09, 0x61,       0x77, 0x73, 0x64, 0x6e, 0x73,
    0x2d,       0x31, 0x39, 0x03, 0x6e,       0x65, 0x74, 0x00, 0x00, 0x00,
    0x29,       0x10, 0x00, 0x00, 0x00,       0x00, 0x00, 0x00, 0x00};
const size_t __fixtures_packets_packet1_bin_len = 235;

const uint8_t bind_systemtest_000a60e489e7_pkt[] = {
    0x31, 0x32, 0x84, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03,
    0x0a, 0x7a, 0x6f, 0x6e, 0x65, 0x30, 0x30, 0x30, 0x30, 0x30, 0x34, 0x07,
    0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x00, 0x00, 0x06, 0x00, 0x01,
    0xc0, 0x0c, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x01, 0x2c, 0x00, 0x1b,
    0x03, 0x6e, 0x73, 0x31, 0xc0, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x01, 0x2c, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x0e, 0x10, 0x00,
    0x01, 0x51, 0x80, 0xc0, 0x0c, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x01,
    0x2c, 0x00, 0x02, 0xc0, 0x30, 0xc0, 0x0c, 0x00, 0x02, 0x00, 0x01, 0x00,
    0x00, 0x01, 0x2c, 0x00, 0x06, 0x03, 0x6e, 0x73, 0x32, 0xc0, 0x0c, 0xc0,
    0x30, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x2c, 0x00, 0x04, 0x0a,
    0x35, 0x00, 0x01, 0xc0, 0x65, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01,
    0x2c, 0x00, 0x04, 0x0a, 0x35, 0x00, 0x02, 0x00, 0x00, 0x29, 0x10, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const size_t bind_systemtest_000a60e489e7_pkt_len = 150;

const uint8_t fixtures_packets_id_000000_sig_11_src_000002_op_havoc_rep_16[] = {
    0x31, 0x33, 0xa4, 0x64, 0xef, 0x01, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xd4,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x04, 0x74, 0x6c, 0x44, 0x00, 0x00,
    0x00, 0x04, 0xfe, 0x61, 0x61, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x04, 0x00, 0x04,
    0x74, 0x6c, 0x44, 0x32, 0x13, 0x12, 0xed, 0x00};
const size_t fixtures_packets_id_000000_sig_11_src_000002_op_havoc_rep_16_len =
    80;

/* txt response */
const uint8_t fixtures_google_com_txt_response[] = {
    0x8a, 0x01, 0x81, 0x80, 0x00, 0x01, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01,
    0x06, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00,
    0x00, 0x10, 0x00, 0x01, 0xc0, 0x0c, 0x00, 0x10, 0x00, 0x01, 0x00, 0x00,
    0x0e, 0x0e, 0x00, 0x3c, 0x3b, 0x66, 0x61, 0x63, 0x65, 0x62, 0x6f, 0x6f,
    0x6b, 0x2d, 0x64, 0x6f, 0x6d, 0x61, 0x69, 0x6e, 0x2d, 0x76, 0x65, 0x72,
    0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x3d, 0x32, 0x32,
    0x72, 0x6d, 0x35, 0x35, 0x31, 0x63, 0x75, 0x34, 0x6b, 0x30, 0x61, 0x62,
    0x30, 0x62, 0x78, 0x73, 0x77, 0x35, 0x33, 0x36, 0x74, 0x6c, 0x64, 0x73,
    0x34, 0x68, 0x39, 0x35, 0xc0, 0x0c, 0x00, 0x10, 0x00, 0x01, 0x00, 0x00,
    0x01, 0x2a, 0x00, 0x2e, 0x2d, 0x64, 0x6f, 0x63, 0x75, 0x73, 0x69, 0x67,
    0x6e, 0x3d, 0x31, 0x62, 0x30, 0x61, 0x36, 0x37, 0x35, 0x34, 0x2d, 0x34,
    0x39, 0x62, 0x31, 0x2d, 0x34, 0x64, 0x62, 0x35, 0x2d, 0x38, 0x35, 0x34,
    0x30, 0x2d, 0x64, 0x32, 0x63, 0x31, 0x32, 0x36, 0x36, 0x34, 0x62, 0x32,
    0x38, 0x39, 0xc0, 0x0c, 0x00, 0x10, 0x00, 0x01, 0x00, 0x00, 0x01, 0x2a,
    0x00, 0x2e, 0x2d, 0x64, 0x6f, 0x63, 0x75, 0x73, 0x69, 0x67, 0x6e, 0x3d,
    0x30, 0x35, 0x39, 0x35, 0x38, 0x34, 0x38, 0x38, 0x2d, 0x34, 0x37, 0x35,
    0x32, 0x2d, 0x34, 0x65, 0x66, 0x32, 0x2d, 0x39, 0x35, 0x65, 0x62, 0x2d,
    0x61, 0x61, 0x37, 0x62, 0x61, 0x38, 0x61, 0x33, 0x62, 0x64, 0x30, 0x65,
    0xc0, 0x0c, 0x00, 0x10, 0x00, 0x01, 0x00, 0x00, 0x0e, 0x0e, 0x00, 0x41,
    0x40, 0x67, 0x6c, 0x6f, 0x62, 0x61, 0x6c, 0x73, 0x69, 0x67, 0x6e, 0x2d,
    0x73, 0x6d, 0x69, 0x6d, 0x65, 0x2d, 0x64, 0x76, 0x3d, 0x43, 0x44, 0x59,
    0x58, 0x2b, 0x58, 0x46, 0x48, 0x55, 0x77, 0x32, 0x77, 0x6d, 0x6c, 0x36,
    0x2f, 0x47, 0x62, 0x38, 0x2b, 0x35, 0x39, 0x42, 0x73, 0x48, 0x33, 0x31,
    0x4b, 0x7a, 0x55, 0x72, 0x36, 0x63, 0x31, 0x6c, 0x32, 0x42, 0x50, 0x76,
    0x71, 0x4b, 0x58, 0x38, 0x3d, 0xc0, 0x0c, 0x00, 0x10, 0x00, 0x01, 0x00,
    0x00, 0x0e, 0x0e, 0x00, 0x24, 0x23, 0x76, 0x3d, 0x73, 0x70, 0x66, 0x31,
    0x20, 0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64, 0x65, 0x3a, 0x5f, 0x73, 0x70,
    0x66, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x63, 0x6f, 0x6d,
    0x20, 0x7e, 0x61, 0x6c, 0x6c, 0x00, 0x00, 0x29, 0x04, 0xd0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};
const size_t fixtures_google_com_txt_response_len =
    (sizeof fixtures_google_com_txt_response) / sizeof(char);

/*
                 84d9 8500 0001 0005 0000 0001  .8.`............
        0x0050:  0667 6f6f 676c 6503 636f 6d00 0010 0001  .google.com.....
        0x0060:  c00c 0010 0001 0000 0e10 0024 2376 3d73  ...........$#v=s
        0x0070:  7066 3120 696e 636c 7564 653a 5f73 7066  pf1.include:_spf
        0x0080:  2e67 6f6f 676c 652e 636f 6d20 7e61 6c6c  .google.com.~all
        0x0090:  c00c 0010 0001 0000 012c 002e 2d64 6f63  .........,..-doc
        0x00a0:  7573 6967 6e3d 3035 3935 3834 3838 2d34  usign=05958488-4
        0x00b0:  3735 322d 3465 6632 2d39 3565 622d 6161  752-4ef2-95eb-aa
        0x00c0:  3762 6138 6133 6264 3065 c00c 0010 0001  7ba8a3bd0e......
        0x00d0:  0000 0e10 003c 3b66 6163 6562 6f6f 6b2d  .....<;facebook-
        0x00e0:  646f 6d61 696e 2d76 6572 6966 6963 6174  domain-verificat
        0x00f0:  696f 6e3d 3232 726d 3535 3163 7534 6b30  ion=22rm551cu4k0
        0x0100:  6162 3062 7873 7735 3336 746c 6473 3468  ab0bxsw536tlds4h
        0x0110:  3935 c00c 0010 0001 0000 0e10 0041 4067  95...........A@g
        0x0120:  6c6f 6261 6c73 6967 6e2d 736d 696d 652d  lobalsign-smime-
        0x0130:  6476 3d43 4459 582b 5846 4855 7732 776d  dv=CDYX+XFHUw2wm
        0x0140:  6c36 2f47 6238 2b35 3942 7348 3331 4b7a  l6/Gb8+59BsH31Kz
        0x0150:  5572 3663 316c 3242 5076 714b 5838 3dc0  Ur6c1l2BPvqKX8=.
        0x0160:  0c00 1000 0100 0001 2c00 2e2d 646f 6375  ........,..-docu
        0x0170:  7369 676e 3d31 6230 6136 3735 342d 3439  sign=1b0a6754-49
        0x0180:  6231 2d34 6462 352d 3835 3430 2d64 3263  b1-4db5-8540-d2c
        0x0190:  3132 3636 3462 3238 3900 0029 0200 0000  12664b289..)....
        0x01a0:  0000 0000                                ..
        */

const uint8_t nlnetlabs_q[] = {
    0x00, 0x22, 0x01, 0x20, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x09, 0x6e, 0x6c, 0x6e, 0x65, 0x74, 0x6c, 0x61, 0x62, 0x73, 0x02, 0x6e,
    0x6c, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x29, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x06, 0xfd, 0xe9, 0x00, 0x02, 0xc0, 0x01};
const size_t nlnetlabs_q_len = sizeof(nlnetlabs_q);

const uint8_t nlnetlabs_r[] = {
    0x00, 0x22, 0x85, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x03, 0x00, 0x03,
    0x09, 0x6e, 0x6c, 0x6e, 0x65, 0x74, 0x6c, 0x61, 0x62, 0x73, 0x02, 0x6e,
    0x6c, 0x00, 0x00, 0x01, 0x00, 0x01, 0xc0, 0x0c, 0x00, 0x01, 0x00, 0x01,
    0x00, 0x00, 0x27, 0xd8, 0x00, 0x04, 0xb9, 0x31, 0x8c, 0x0a, 0xc0, 0x0c,
    0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x05, 0x02, 0x6e,
    0x73, 0xc0, 0x0c, 0xc0, 0x0c, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00,
    0xf0, 0x00, 0x0f, 0x05, 0x61, 0x6e, 0x79, 0x6e, 0x73, 0x03, 0x70, 0x63,
    0x68, 0x03, 0x6e, 0x65, 0x74, 0x00, 0xc0, 0x0c, 0x00, 0x02, 0x00, 0x01,
    0x00, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0x07, 0x6e, 0x73, 0x2d, 0x65, 0x78,
    0x74, 0x31, 0x04, 0x73, 0x69, 0x64, 0x6e, 0xc0, 0x16, 0xc0, 0x3a, 0x00,
    0x01, 0x00, 0x01, 0x00, 0x00, 0x27, 0xd8, 0x00, 0x04, 0xb9, 0x31, 0x8c,
    0x3c, 0xc0, 0x3a, 0x00, 0x1c, 0x00, 0x01, 0x00, 0x00, 0x27, 0xd8, 0x00,
    0x10, 0x2a, 0x04, 0xb9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x29, 0x04, 0xd0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00};
const size_t nlnetlabs_r_len = sizeof(nlnetlabs_r);

const uint8_t probit_q[] = {
    0xcb, 0x85,                                     /* qid */
    0x01, 0x20,                                     /* flags */
    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, /* counts */
    0x04, 0x6d, 0x61, 0x69, 0x6c,                   /* mail */
    0x0a, 0x5f, 0x64, 0x6f, 0x6d, 0x61, 0x69, 0x6e,
    0x6b, 0x65, 0x79,                         /* _domainkey */
    0x06, 0x70, 0x72, 0x6f, 0x62, 0x69, 0x74, /* probit */
    0x02, 0x63, 0x61,                         /* ca */
    0x00,                                     /* root, empty */
    0x00, 0x10,                               /* TXT? */
    0x00, 0x01,                               /* IN */
    0x00,                                     /* '' */
    0x00, 0x29,                               /* OPT */
    0x10, 0x00,                               /* cls = max */
    0x00, 0x00, 0x00, 0x00,                   /* ttl = ext rcode */
    0x00, 0x00                                /* rdlen */
};
const size_t probit_q_len = sizeof(probit_q);

const uint8_t probit_r[] = {
    0xcb, 0x85, 0x81, 0x80, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
    0x04, 0x6d, 0x61, 0x69, 0x6c, 0x0a, 0x5f, 0x64, 0x6f, 0x6d, 0x61, 0x69,
    0x6e, 0x6b, 0x65, 0x79, 0x06, 0x70, 0x72, 0x6f, 0x62, 0x69, 0x74, 0x02,
    0x63, 0x61, 0x00, 0x00, 0x10, 0x00, 0x01, 0xc0, 0x0c, 0x00, 0x10, /* TXT */
    0x00, 0x01,                                                       /* IN */
    0x00, 0x00, 0x01, 0x0f,                                           /* TTL */
    0x01, 0x94, /* rdlen */
    0xff,       /* strlen */
    0x76, 0x3d, 0x44, 0x4b, 0x49, 0x4d, 0x31, 0x3b, 0x70, 0x3d, 0x4d, 0x49,
    0x49, 0x42, 0x49, 0x6a, 0x41, 0x4e, 0x42, 0x67, 0x6b, 0x71, 0x68, 0x6b,
    0x69, 0x47, 0x39, 0x77, 0x30, 0x42, 0x41, 0x51, 0x45, 0x46, 0x41, 0x41,
    0x4f, 0x43, 0x41, 0x51, 0x38, 0x41, 0x4d, 0x49, 0x49, 0x42, 0x43, 0x67,
    0x4b, 0x43, 0x41, 0x51, 0x45, 0x41, 0x37, 0x4a, 0x6f, 0x37, 0x6f, 0x5a,
    0x36, 0x35, 0x32, 0x47, 0x74, 0x76, 0x7a, 0x45, 0x73, 0x30, 0x78, 0x78,
    0x37, 0x4c, 0x6c, 0x59, 0x67, 0x4b, 0x48, 0x71, 0x42, 0x48, 0x37, 0x50,
    0x52, 0x32, 0x54, 0x67, 0x51, 0x76, 0x79, 0x37, 0x2b, 0x73, 0x35, 0x69,
    0x30, 0x38, 0x77, 0x70, 0x6f, 0x7a, 0x2f, 0x43, 0x69, 0x61, 0x53, 0x32,
    0x54, 0x53, 0x45, 0x57, 0x61, 0x63, 0x78, 0x66, 0x39, 0x41, 0x53, 0x42,
    0x6a, 0x4c, 0x72, 0x30, 0x66, 0x56, 0x68, 0x51, 0x6e, 0x2b, 0x68, 0x78,
    0x46, 0x59, 0x30, 0x52, 0x45, 0x4c, 0x47, 0x32, 0x76, 0x4b, 0x6d, 0x4b,
    0x6b, 0x4e, 0x52, 0x38, 0x41, 0x51, 0x46, 0x49, 0x54, 0x72, 0x6d, 0x38,
    0x4b, 0x77, 0x47, 0x6c, 0x33, 0x36, 0x62, 0x77, 0x58, 0x4a, 0x37, 0x32,
    0x76, 0x72, 0x61, 0x4a, 0x71, 0x77, 0x5a, 0x56, 0x6f, 0x2f, 0x52, 0x46,
    0x61, 0x59, 0x52, 0x34, 0x45, 0x52, 0x4a, 0x52, 0x6a, 0x47, 0x32, 0x6d,
    0x4b, 0x48, 0x74, 0x54, 0x37, 0x35, 0x55, 0x49, 0x35, 0x56, 0x45, 0x34,
    0x65, 0x46, 0x59, 0x33, 0x43, 0x78, 0x55, 0x70, 0x75, 0x79, 0x58, 0x4f,
    0x70, 0x6a, 0x4f, 0x68, 0x73, 0x30, 0x50, 0x48, 0x4c, 0x61, 0x63, 0x4b,
    0x74, 0x6d, 0x7a, 0x33, 0x6b, 0x5a, 0x69, 0x2f, 0x55, 0x6d, 0x65, 0x49,
    0x4f, 0x41, 0x75, 0x65, 0x62, 0x77, 0x41, 0x4a, 0x59, 0x62, 0x46, 0x53,
    0x51, 0x32, 0x79, 0x93, /* strlen */
    0x37, 0x4b, 0x7a, 0x58, 0x30, 0x51, 0x53, 0x66, 0x63, 0x63, 0x73, 0x6d,
    0x37, 0x5a, 0x48, 0x45, 0x4d, 0x34, 0x7a, 0x55, 0x52, 0x51, 0x2b, 0x78,
    0x48, 0x50, 0x4b, 0x36, 0x6b, 0x64, 0x6c, 0x4e, 0x77, 0x54, 0x68, 0x68,
    0x6b, 0x54, 0x6b, 0x62, 0x45, 0x57, 0x6f, 0x6c, 0x4e, 0x4c, 0x54, 0x43,
    0x6a, 0x4b, 0x31, 0x67, 0x50, 0x74, 0x54, 0x53, 0x5a, 0x6b, 0x5a, 0x6a,
    0x33, 0x75, 0x77, 0x47, 0x57, 0x33, 0x6e, 0x36, 0x38, 0x55, 0x68, 0x56,
    0x75, 0x62, 0x6a, 0x49, 0x68, 0x69, 0x44, 0x54, 0x41, 0x54, 0x49, 0x56,
    0x4d, 0x6b, 0x39, 0x47, 0x6b, 0x30, 0x57, 0x30, 0x64, 0x53, 0x4f, 0x66,
    0x57, 0x4b, 0x39, 0x30, 0x50, 0x32, 0x48, 0x38, 0x4f, 0x56, 0x65, 0x76,
    0x35, 0x77, 0x56, 0x53, 0x55, 0x4b, 0x32, 0x76, 0x58, 0x38, 0x43, 0x35,
    0x70, 0x74, 0x2b, 0x6e, 0x67, 0x49, 0x41, 0x78, 0x44, 0x33, 0x66, 0x67,
    0x50, 0x35, 0x2f, 0x76, 0x56, 0x36, 0x2f, 0x39, 0x51, 0x49, 0x44, 0x41,
    0x51, 0x41, 0x42,
    /* option */
    0x00, 0x00, 0x29, 0x04, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const size_t probit_r_len = sizeof(probit_r);

const uint8_t option[] = {0x00, 0x00, 0x29, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x06, 0xfd, 0xe9, 0x00, 0x02, 0xc0, 0x01};
const size_t option_len = sizeof(option);

// example
// fromhttps://en.wikipedia.org/w/index.php?title=NAPTR_record&oldid=987860282
// 100 10 "U" "E2U+sip" "!^.*$!sip:customer-service@example.com!" .
const uint8_t fixture_naptr[] =
    {
        0x07, 'e',  'x',  'a',  'm', 'p', 'l', 'e', 0x03, 'c', 'o',
        'm',  0x00, 0x00, 35,                       /* t_naptr */
        0x00, 0x01,                                 /* CLS_IN */
        0x00, 0x00, 0x00, 0x64,                     /* TTL = 100 */
        0x00, 0x37,                                 /* rdlen */
        0x00, 0x64,                                 /* order = 100 */
        0x00, 0x0a,                                 /* preference = 10 */
        0x01, 'U',                                  /* flags = "U" */
        0x07, 'E',  '2',  'U',  '+', 's', 'i', 'p', /* service = "E2U+sip" */
        0x27, '!',  '^',  '.',  '*', '$', '!', 's', 'i',  'p', ':',
        'c',  'u',  's',  't',  'o', 'm', 'e', 'r', '-',  's', 'e',
        'r',  'v',  'i',  'c',  'e', '@', 'e', 'x', 'a',  'm', 'p',
        'l',  'e',  '.',  'c',  'o', 'm', '!', /* regexp =
                                                  "!^.*$!sip:customer-service@example.com!"
                                                */
        0x00,                                  /* replacement = "" aka . */
};
const size_t fixture_naptr_len = sizeof(fixture_naptr);

const uint8_t goog_caa_q[] = {
    0xf7, 0x77, 0x01, 0x20, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x06, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f,
    0x6d, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x29, 0x10, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x60, 0xf3, 0x5f, 0xd5,
    0x2d, 0x09, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00};
const size_t goog_caa_q_len = sizeof(goog_caa_q);

const uint8_t goog_caa_r[] = {
    0xf7, 0x77, 0x81, 0x80, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x06, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f,
    0x6d, 0x00, 0x01, 0x01, 0x00, 0x01, 0xc0, 0x0c, 0x01, 0x01, 0x00,
    0x01, 0x00, 0x01, 0x51, 0x4b, 0x00, 0x0f, 0x00, 0x05, 0x69, 0x73,
    0x73, 0x75, 0x65, 0x70, 0x6b, 0x69, 0x2e, 0x67, 0x6f, 0x6f, 0x67,
    0x00, 0x00, 0x29, 0x04, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const size_t goog_caa_r_len = sizeof(goog_caa_r);

#endif /* FIXTURES_H */
