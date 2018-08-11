import sensor, image, time
from pyb import UART, LED
robot = 1

# (L Min, L Max, A Min, A Max, B Min, B Max)
if robot == 1:
    ball = [(36, 70, 37, 91, 31, 77)]#[(37, 62, 36, 86, 33, 60)]
    blueGoal = [(52, 64, -23, 1, -54, -28)]#[(28,40,0,62,-90,-30)]
    yellowGoal = [(45, 66, -4, 33, 14, 79)]#[(72,86,-24,18,23,67)]
else:
    ball = [(53, 69, 52, 81, 25, 57)]#[(55, 70, 36, 73, 5, 49)]
    blueGoal = [(40,60,-20,4,-49,-23)]#[(36, 54, -26, 8, -47, -18)]
    yellowGoal = [(70,87,-9,22,25,73)]#[(71,95,-25,24,10,78)]

uart = UART(3, 9600, timeout_char = 1000)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_windowing((40,0,240,240))

LED(1).on()
time.sleep(100)
LED(1).off()
sensor.set_saturation(3)
sensor.set_brightness(-2)
sensor.set_contrast(0)

#clock = time.clock()
def largestBlob(lBlob):
    if not lBlob:
        return None
    maxBlob = lBlob[0]
    for blob in lBlob:
        if blob.area() > maxBlob.area():
            maxBlob = blob
    return maxBlob

while(True):
    #clock.tick()
    sendBuffer = [255,0,0,0,0,0,0]

    img = sensor.snapshot()
    #img.draw_cross(120,120)
    ballBlob = largestBlob(img.find_blobs(ball))
    blueBlob = largestBlob(img.find_blobs(blueGoal,x_stride=6,y_stride=4,merge=True,margin=34,area_threshold=15))
    yellowBlob = largestBlob(img.find_blobs(yellowGoal,x_stride=6,y_stride=4,merge=True,margin=34,area_threshold=15))

    if ballBlob:
        #img.draw_line((120, 120, ballBlob.cx(), ballBlob.cy()))
        sendBuffer[1] = ballBlob.cx()
        sendBuffer[2] = ballBlob.cy()

    if blueBlob:
        #img.draw_line((120, 120, blueBlob.cx(), blueBlob.cy()))
        sendBuffer[3] = blueBlob.cx()
        sendBuffer[4] = blueBlob.cy()

    if yellowBlob:
        #img.draw_line((120, 120, yellowBlob.cx(), yellowBlob.cy()))
        sendBuffer[5] = yellowBlob.cx()
        sendBuffer[6] = yellowBlob.cy()

    for i in sendBuffer:
        try:
            uart.writechar(i)
        except Exception as E:
            print(E)
    #print(clock.fps())
