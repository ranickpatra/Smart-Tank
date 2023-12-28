# avrdude -p atmega328p -c stk500v1 -P /dev/ttyACM0 -b 19200 -U flash:w:./.pio/build/ATmega328/firmware.hex

ENV=ATmega328P
BOARD=atmega328p
UPLOAD_PROTOCOL=stk500v1
UPLOAD_PORT=/dev/ttyACM0
UPLOAD_SPEED=19200

avrdude -p $BOARD -c $UPLOAD_PROTOCOL -P $UPLOAD_PORT -b $UPLOAD_SPEED -U flash:w:./.pio/build/$ENV/firmware.hex
