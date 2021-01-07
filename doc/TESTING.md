# Test design notes

## Goals

### Coverage

100% code coverage.  Track coverage from the beginning.
Design for coverage first.

### Fuzzing

Everything that takes untrusted input (eg data from network, but also /etc/resolv.conf,...) must be isolated and fuzz tested, starting from known good/known bad inputs.

### Non-goals

We trust the caller to give valid memory addresses for read/write/execution,
and to not lie about the size of a memory block.