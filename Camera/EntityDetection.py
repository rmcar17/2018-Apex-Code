import sensor, image, time

# (L Min, L Max, A Min, A Max, B Min, B Max)
ball = [(38, 55, 32, 66, 17, 50)]

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
    for blob in img.find_blobs(ball):
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())
    print(clock.fps())
