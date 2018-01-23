PLATFORM = photon
FIRMWAREBIN = photon_firmware*.bin
TARGET=firmware.bin

SOURCES = $(wildcard src/*.ino src/*.cpp)

$(info SOURCES ="$(SOURCES)")

BIN = ./bin

TARGET=platform.bin

$(info PLATFORM="$(PLATFORM)")

all : $(BIN)/$(TARGET) 

$(BIN)/$(TARGET):$(SOURCES) $(BIN)/
	particle compile $(PLATFORM) $(SOURCES) --saveTo $(BIN)/$(TARGET)

$(BIN)/:
	mkdir -p $(BIN);

#used to flash firmware over usb using dfu
usbflash : $(BIN)/$(TARGET) 
	particle flash --usb $(BIN)/$(TARGET)

#used to flash firmware to DEVICE_NAME over cloud
cloudflash: $(BIN)/$(TARGET) 
ifdef DEVICE_NAME
	particle flash $(DEVICE_NAME) $(BIN)/$(TARGET)
else
	$(error DEVICE_NAME is not set)
endif	

PHONY = .clean 
clean:
	rm -f ./bin/*
