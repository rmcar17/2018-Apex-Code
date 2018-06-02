import sensor, image, time
from pyb import UART, LED

# (L Min, L Max, A Min, A Max, B Min, B Max)
ball = [(50,67,24,62,0,40)]
blueGoal = [(37,51,-18,1,-24,-9)]
yellowGoal = [(49,74,-7,15,8,48)]

uart = UART(3, 9600, timeout_char = 1000)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)

LED(1).on()
time.sleep(200)
LED(1).off()
#sensor.set_saturation(3)
#sensor.set_brightness(1)

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
    sendBuffer = [1,0,0,0,0,0,0,0,0,0]

    img = sensor.snapshot()
    img.draw_cross(160,120)
    ballBlob = largestBlob(img.find_blobs(ball,roi=(27,0,252,240)))
    blueBlob = largestBlob(img.find_blobs(blueGoal,roi=(27,0,252,240),x_stride=8,y_stride=4,merge=True,margin=34,area_threshold=80))
    yellowBlob = largestBlob(img.find_blobs(yellowGoal,roi=(27,0,252,240),x_stride=8,y_stride=4,merge=True,margin=34,area_threshold=80))

    if ballBlob:
        #img.draw_line((160, 120, ballBlob.cx(), ballBlob.cy()))
        #print((((ballBlob.cx()-160)**2+(ballBlob.cy()-120)**2)**0.5))
        if ballBlob.cx() >= 255:
            sendBuffer[1] = 255
        sendBuffer[2] = ballBlob.cx() % 255
        sendBuffer[3] = ballBlob.cy()

    if blueBlob:
        #img.draw_line((160, 120, blueBlob.cx(), blueBlob.cy()))
        if blueBlob.cx() >= 255:
            sendBuffer[4] = 255
        sendBuffer[5] = blueBlob.cx() % 255
        sendBuffer[6] = blueBlob.cy()

    if yellowBlob:
        #img.draw_line((160, 120, yellowBlob.cx(), yellowBlob.cy()))
        if yellowBlob.cy() >= 255:
            sendBuffer[7] = 255
        sendBuffer[8] = yellowBlob.cx() % 255
        sendBuffer[9] = yellowBlob.cy()

    for i in range(1,len(sendBuffer)):
        if sendBuffer[i] == 1:
            sendBuffer[i] = 2
    for i in sendBuffer:
        try:
            uart.writechar(i)
        except Exception as E:
            print(E)
    #print(clock.fps())
