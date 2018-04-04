import sensor, image, time
from pyb import UART

# (L Min, L Max, A Min, A Max, B Min, B Max)
ball = [(38, 55, 32, 66, 17, 50)]
blue_goal = [(29, 35,-6,3,-23,-11)]
yellow_goal = [(49,56,-3,9,11,30)]

uart = UART(3, 9600, timeout_char = 1000)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()

while(True):
    clock.tick()
    img = sensor.snapshot()
    for blob in img.find_blobs(yellow_goal):
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())
    uart.writechar(100)
    print(clock.fps())
