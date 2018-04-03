import sensor, image, time

# (L Min, L Max, A Min, A Max, B Min, B Max)
thresholds = [(30, 100, 15, 127, 15, 127),
              (30, 100, -64, -8, -32, 32),
              (0, 15, 0, 40, -80, -20)]

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
    for blob in img.find_blobs(thresholds):
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())
    print(clock.fps())
