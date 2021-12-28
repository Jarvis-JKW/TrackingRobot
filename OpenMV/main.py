import sensor, image, time
from pyb import UART
import json
from pyb import LED


thresholds = [(20, 80, 42, 76, 6, 64),
              (15, 100, -128, -18, -31, 20)]
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()
uart = UART(3, 115200)
def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob.pixels() > max_size:
            max_blob=blob
            max_size = blob.pixels()
    return max_blob
while True:
    img = sensor.snapshot()
    sensor.set_vflip(True)
    redblobs = img.find_blobs([thresholds[0]], pixels_threshold=100, area_threshold=100, merge=True)
    greenblobs = img.find_blobs([thresholds[1]], pixels_threshold=100, area_threshold=100, merge=True)
    if redblobs:
        max_blob=find_max(redblobs)
        print('area :', max_blob.area())
        if max_blob.area()>2000:
            img.draw_rectangle(max_blob.rect())
            img.draw_cross(max_blob.cx(), max_blob.cy())
            print("Red Detected!")
            if 70 < max_blob.cy():
                output_target="R"
                LED(2).off()
                LED(3).off()
                sensor.skip_frames(time = 100)
                LED(1).on()
                print("%c will be sent to UART3" % output_target)
                uart.write(output_target)
    elif greenblobs:
        max_blob = find_max(greenblobs)
        if max_blob.area() > 2000:
            img.draw_rectangle(max_blob.rect())
            img.draw_cross(max_blob.cx(), max_blob.cy())
            print("Green Detected!")
            if 70 < max_blob.cy():
                output_target="G"
                LED(1).off()
                LED(3).off()
                sensor.skip_frames(time = 100)
                LED(2).on()
                print("%c will be sent to UART3" % output_target)
                uart.write(output_target)
    else:
        LED(1).off()
        LED(2).off()
        sensor.skip_frames(time = 100)
        LED(3).on()
        output_target="N"
        print("%c will be sent to UART3" % output_target)
        uart.write(output_target)
