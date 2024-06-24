BUILD_DIR = build
EXEC = $(BUILD_DIR)/fileCompare
TEST_EXEC = $(BUILD_DIR)/test/test_util

GTEST_DIR = googletest
GTEST_LIB = $(GTEST_DIR)/build/lib/libgtest.a
GTEST_MAIN_LIB = $(GTEST_DIR)/build/lib/libgtest_main.a

OPENSSL_DIR = openssl
OPENSSL_INCLUDE_DIR = $(OPENSSL_DIR)/include
OPENSSL_LIB_DIR = $(OPENSSL_DIR)/lib
OPENSSL_LIB = $(OPENSSL_LIB_DIR)/libssl.a
OPENSSL_CRYPTO_LIB = $(OPENSSL_LIB_DIR)/libcrypto.a

all: build

build: $(GTEST_LIB) $(GTEST_MAIN_LIB) #$(OPENSSL_LIB) $(OPENSSL_CRYPTO_LIB)
	cmake -S . -B $(BUILD_DIR) -DOPENSSL_ROOT_DIR=$(OPENSSL_DIR)
	cmake --build $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(GTEST_DIR) $(OPENSSL_DIR)

$(GTEST_LIB) $(GTEST_MAIN_LIB):
	@if [ ! -d "$(GTEST_DIR)" ]; then \
		echo "Downloading Google Test..."; \
		git clone https://github.com/google/googletest.git; \
	fi
	@mkdir -p $(GTEST_DIR)/build
	cd $(GTEST_DIR)/build && cmake .. && make

# $(OPENSSL_LIB) $(OPENSSL_CRYPTO_LIB):
#	@if [ ! -d "$(OPENSSL_DIR)" ]; then \
#		echo "Downloading OpenSSL..."; \
#		curl -O https://www.openssl.org/source/openssl-1.1.1k.tar.gz; \
#		tar -xzf openssl-1.1.1k.tar.gz; \
#		mv openssl-1.1.1k $(OPENSSL_DIR); \
#		cd $(OPENSSL_DIR) && ./config --prefix=$(PWD)/$(OPENSSL_DIR) && make && make install; \
#	fi

test: build
	$(TEST_EXEC)

run: build
	$(EXEC) $(ARGS)

.PHONY: all build clean test run
