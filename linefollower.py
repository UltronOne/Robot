import sensor, image, time, pyb
from pyb import UART


sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
#sensor.set_autogain(False)
sensor.set_auto_whitebal(False)
uart = UART(3, 9600)
led1 = pyb.LED(1)
led2 = pyb.LED(2)
led3 = pyb.LED(3)

color_threshold = (42, 93, -58, -27, 11, 56)
color_threshold2 =(56, 80, -32, -17, 17, 43)
color_threshold3 =(9, 100, -127, -15, 5, 127)

clock = time.clock()

while True:
    led1.on()
    led2.on()
    led3.on()
    img = sensor.snapshot()
    blobs = img.find_blobs([color_threshold3], pixels_threshold=200, merge=True)
    for blob in blobs:
        position = blob.cx()
        img.draw_line(position, int(img.height()/2), position, img.height(), color=(255, 0, 0), thickness=10)
        img.draw_line(int(img.width()/2), 0, int(img.width()/2), img.height(),color=(0, 255, 0), thickness=2)
        print(position)


    if len(blobs) ==0:
        position= 999

    clock.tick()
    #print(clock.fps())
    print(position)
    uart.write(str(position)+"\n")
    time.sleep(50)
