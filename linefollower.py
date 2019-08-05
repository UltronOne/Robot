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

clock = time.clock()

while True:
    led1.on()
    led2.on()
    led3.on()
    img = sensor.snapshot()
    blobs = img.find_blobs([color_threshold], pixels_threshold=200, merge=True)
    for blob in blobs:
        #img.draw_rectangle(blob.rect())
        position = blob.cx()
        img.draw_line(position, 120, position, 240, color=(255, 0, 0), thickness=10)
        img.draw_line(160, 0, 160, 240,color=(0, 255, 0), thickness=2)

        print(position)
    if len(blobs) ==0:
        position= 99999
    clock.tick()
    #print(clock.fps())
    print(position)
    uart.write(str(position)+"\n")
    time.sleep(500)
