# Compatibility design notes

## Goals

Support modern platforms and C99
Support IPv4/IPv6

Allow requests to be cancelled
Allow setting of local address for net traffic

Allow configuring non-standard ports for upstream resolvers
 - 1.2.3.4
 - 1.2.3.4:54
 - [2001:4860:4860::8888]:1053
 - 2001:4860:4860::8888

(for an ipv6 with a default port, can omit the `[]`)
(use inet_pton... does it handle `[`?)

## Secure Protocols

General security note: if config selects *any* secure protocol, then
all insecure fallback is disabled.  If you need to mix secure/insecure
resolution, create 2 instances of the client; one secure-only, one insecure-only

### rfc 7858 dns over tls

- tls:1.2.3.4     (default port 853)
- tls:1.2.3.4:853 
- tls:1.2.3.4:53  (error: recommended against in rfc7858)

### server certificate validation
- and public key pinning
- allow specification of pin set


RFC 7858
```
   Upon successful TLS connection and handshake, the client computes the
   SPKI Fingerprints for the public keys found in the validated server's
   certificate chain (or in the raw public key, if the server provides
   that instead).  If a computed fingerprint exactly matches one of the
   configured pins, the client continues with the connection as normal.
   Otherwise, the client MUST treat the SPKI validation failure as a
   non-recoverable error.  Appendix A provides a detailed example of how
   this authentication could be performed in practice.
```

## EDNS0 timeout

- support on TCP / TLS etc

## Stretch

punycode/idna (is this a higher-level concern?)
support search domains/resolv.conf
Do not generate invalid queries

### rfc 8484 DNS over https

- doh:

requires an http library
default port 443

2 modes:
 - GET (URI + ?dns=<base64url-encoded>)
 - PUT set content-length header, send raw bytes

suggest HTTP/2
revocation checks (?require DNS - deadlock)


### rfc?? oblivious dns over https

- odoh:

requires an http library AND public-key crypto

## Non-goals

Win95 support

# Config structure

```
typedef struct dancers_config {
  char *resolv_conf_path;
  char *....
} dancers_config;
```

default value for all options is `0` so that you get a default config by initializing with `{0}` or `calloc`, this way:

```
{
  dancers_config config = {0};
  dancers_resolver *resolver = NULL;

  /* configure with reasonable defaults */
  int rc = dancers_init(&resolver, &config);

}

