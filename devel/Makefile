# assumptions reflect personal dev machine
all:

CLANG := clang
ASAN := -fsanitize=address

FUZZDIR := /usr/local/Cellar/afl-fuzz/2.57b_1/bin
FUZZCLANG := $(FUZZDIR)/afl-clang
FUZZER  := $(FUZZDIR)/afl-fuzz

DEPS :=  ../include/* ../src/*
SOURCES :=  ../src/dancers.c
TEST_DEPS := $(DEPS) ../test/src/fixtures.h
TEST_SOURCES := ../test/src/main.c ../test/src/test-parser.c
FUZZ_SOURCES := ../test/fuzz-dns.c $(SOURCES)

export LLVM_PROFILE_FILE := /dev/null

check: test
qc: quickcheck
quickcheck: ../out/test-dancers
	../out/test-dancers

qct: ../out/test-dancers-td
	../out/test-dancers-td

test: ../out/test-dancers ../out/test-asan ../out/test-optimized
	../out/test-dancers && ../out/test-asan && ../out/test-optimized

fuzz: ../out/packet-fuzzer
	$(FUZZER) -i ../fixtures/packets -o ../out -- ../out/packet-fuzzer

format: always
	clang-format -style=Google -i ../**/*.[ch]

../out/packet-fuzzer: $(FUZZ_SOURCES) $(DEPS)
	rm -f $@ && AFL_HARDEN=1 $(FUZZCLANG) -g $(FUZZ_SOURCES) -o $@

../out/packet-asan: $(FUZZ_SOURCES) $(DEPS)
	rm -f $@ && $(CLANG) $(ASAN) -g $(FUZZ_SOURCES) -o $@

../out/test-dancers: $(TEST_SOURCES) $(TEST_DEPS)
	rm -f $@ && $(CLANG) -g -O0 -Wall $(CFLAGS) -fcoverage-mapping -fprofile-instr-generate $(TEST_SOURCES) -lcheck -o $@

../out/test-dancers-td: always $(TEST_SOURCES) $(TEST_DEPS)
	rm -f $@ && $(CLANG) -g -O0 -DTRACE_ON=1 -DDEBUG_ON=1 $(TEST_SOURCES) -lcheck -o $@

../out/test-asan: $(TEST_SOURCES) $(TEST_DEPS)
	rm -f $@ && $(CLANG) -g -O0 $(ASAN) $(TEST_SOURCES) -lcheck -o $@

../out/test-optimized: $(TEST_SOURCES) $(TEST_DEPS)
	rm -f $@ && $(CLANG) -O3 $(TEST_SOURCES) -lcheck -o $@

fuzz-cmin: ../out/packet-fuzzer
	rm -fr ../out/npackets ; mkdir -p ../out/npackets
	$(FUZZDIR)/afl-cmin -i ../fixtures/packets -o ../out/npackets -m 1000000 -t 400000 -- ../out/packet-fuzzer
	rm -f ../fixtures/packets/*
	cp -vr ../out/npackets/* ../fixtures/packets

#fuzz-tmin: ../out/packet-fuzzer
#	rm -fr ../out/npackets ; mkdir -p ../out/npackets
#	for f in ../fixtures/packets/*; x=`basename $$f`; do $(FUZZDIR)/afl-tmin -i $${f} -o out/npackets/$${x} -- ../out/packet-fuzzer ; done
#	cp -vr out/npackets/* ../fixtures/packets

fuzz-refresh: ../out/packet-fuzzer
	rm -fr out/npackets
	$(FUZZDIR)/afl-cmin -i ../../dns-fuzzing/packet -o out/npackets -m 1000000 -t 400000 -- ../out/packet-fuzzer
	cp -vr out/npackets/* ../fixtures/packets

cover: ../out/test-dancers
	LLVM_PROFILE_FILE="../out/dancers.profraw" ../out/test-dancers
	xcrun llvm-profdata merge -sparse ../out/dancers.profraw -o ../out/dancers.profdata
	xcrun llvm-cov report ../out/test-dancers -instr-profile=../out/dancers.profdata -ignore-filename-regex=test* -ignore-filename-regex=usr/local/include/check.h
	xcrun llvm-cov show -format=html -output-dir=../out/cover_html -show-line-counts-or-regions -show-expansions ../out/test-dancers -instr-profile=../out/dancers.profdata -ignore-filename-regex=test* -ignore-filename-regex=usr/local/include/check.h

always:

.PHONY: test check clean fuzz cover always
